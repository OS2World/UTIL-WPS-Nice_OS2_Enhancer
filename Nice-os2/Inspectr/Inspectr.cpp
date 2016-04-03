// Постоянные величины.
#include "..\\Shared\\General.h"
#pragma pack(4)

// Вызовы C/C++.
#include "..\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\Shared\\StdLib.cpp"

// Работа со строками.
#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// Работа с файлами.
#include "..\\Shared\\Files\\Files_code.cpp"
#include "..\\Shared\\Files.cpp"

// Расположение окон.
#include "..\\Shared\\WindowTree.h"
#include "..\\Shared\\WindowTree\\WindowTree_code.cpp"
#include "..\\Shared\\WindowTree.cpp"

#include "..\\Shared\\Layout.h"
#include "..\\Shared\\Layout\\Layout_data.cpp"
#include "..\\Shared\\Layout\\Layout_list.cpp"
#include "..\\Shared\\Layout\\Layout_code.cpp"
#include "..\\Shared\\Layout.cpp"

// Свойства окружения.
#include "..\\Shared\\SysState.h"
#pragma pack(4)

// Переменные среды.
#define INCLUDED_BY_SHELL

#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// Окна и поля ввода.
#include "..\\Shared\\Repository.h"
#include "..\\Shared\\Repository\\Repository_data.cpp"
#include "..\\Shared\\Repository\\Repository_base.cpp"
#include "..\\Shared\\Repository\\Repository_code.cpp"
#include "..\\Shared\\Repository.cpp"

// Данные приложения.
typedef struct _INSPECTOR
 {
  // Приложение.
  HAB Application;

  // Страна, в которой работает приложение.
  ULONG Code_page;

  // Окно рамки.
  HWND Frame_window;
  CHAR Frame_window_title[ SIZE_OF_TITLE ];
  // Окно рабочей области.
  HWND Client_window;

  // Каталог приложения.
  CHAR Current_directory[ SIZE_OF_PATH ];

  // Настройки должны быть записаны.
  BYTE Write_settings;

  // Работают потоки.
  BYTE Processing;
  BYTE Observing;
  BYTE ObserverReportReading;

  // Безымянные PIPE-соединения STD_*.
  HFILE Saved_StdInHandle;  
  HFILE Saved_StdOutHandle; 
  HFILE Saved_StdErrHandle; 

  HPIPE Pipe_ReadHandle_1; HPIPE Pipe_WriteHandle_1;
  HPIPE Pipe_ReadHandle_2; HPIPE Pipe_WriteHandle_2;
 }
INSPECTOR; INSPECTOR Inspector;

// Строки приложения.
#include "Resources\\StrConst.h"

// Внутренние сообщения.
#define MY_CREATE       ( WM_USER +  1 )

#define MY_APPLY_LAYOUT ( WM_USER + 10 )
#define MY_START_THREAD ( WM_USER + 11 )

// Внешние сообщения.
#include "..\\Shared\\Messages4Daemon.h"

// Функции для запуска потоков приложения.
#include "Threads\\Threads.h"

// Окна приложения.
#include "Pages\\Controls.h"

#include "Pages\\ClientWindow\\ClientWindow_data.cpp"
#include "Pages\\ClientWindow\\ClientWindow_open.cpp"
#include "Pages\\ClientWindow\\ClientWindow_page.cpp"
#include "Pages\\ClientWindow.cpp"

// Потоки приложения.
#include "Threads\\Limits.h"
#include "Threads\\Methods.c"
#include "Threads\\ObserverEThread.h"
#include "Threads\\ObserverEThread.c"
#include "Threads\\ObserverRThread.c"
#include "Threads\\ProcessorThread.h"
#include "Threads\\ProcessorThread.c"

// ─── Приложение ───

INT main( INT argc, PCHAR argv[] )
{
 // Сбрасываем свойства приложения.
 bzero( &Inspector, sizeof( INSPECTOR ) );

 // Определяем приложение в системе.
 Inspector.Application = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Inspector.Application == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   return 0;
  }

 // Создаем очередь сообщений.
 HMQ Message_queue = WinCreateMsgQueue( Inspector.Application, 0 );

 // Если очередь создать не удалось - выход.
 if( Message_queue == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   WinTerminate( Inspector.Application ); return 0;
  }

 // Запускаем составляющие приложения.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 WindowTree_Start();
 Layout_Start();
 Environment_Start();
 EnhancerProperties_Start();

 Repository_Start();

 // Если окно приложения уже есть - выход.
 {
  CHAR Semaphore_name[] = "\\SEM32\\N2ENSPECTR";
  HMTX hmtxAlreadyRunning = NULLHANDLE;

  if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR )
   {
    WinDestroyMsgQueue( Message_queue );
    WinTerminate( Inspector.Application );
    return 0;
   }
  else
   {
    DosCreateMutexSem( Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1 );
   }
 }

 // Узнаем рабочий каталог.
 {
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
  DosQueryCurrentDisk( &Current_drive, &Drive_map );
  Inspector.Current_directory[ 0 ] = (CHAR) Current_drive + 64;
  Inspector.Current_directory[ 1 ] = ':';
  Inspector.Current_directory[ 2 ] = '\\';
  DosQueryCurrentDir( 0, &Inspector.Current_directory[ 3 ], &Length );
 }

 // Приложение может быть вызвано из любого каталога внутри расширителя.
 // Переходим в его настоящий каталог.
 if( !stristr( "\\Enhancer\\Inspectr", Inspector.Current_directory ) )
  {
   if( stristr( "\\Enhancer", Inspector.Current_directory ) ||
       stristr( "\\Install", Inspector.Current_directory ) )
    {
     CutNameInPath( Inspector.Current_directory );
     strcat( Inspector.Current_directory, "\\Enhancer\\Inspectr" );
    }
   else
    {
     strcat( Inspector.Current_directory, "\\Enhancer\\Inspectr" );
    }

   DosSetCurrentDir( Inspector.Current_directory );
  }

 // Открываем файл настроек.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = "";
 {
  strcpy( Settings_file_name, Inspector.Current_directory );
  CutNameInPath( Settings_file_name ); strcat( Settings_file_name, "\\Nice-os2.ini" );
 }
 HINI Ini_file = OpenIniProfile( Inspector.Application, Settings_file_name );

 // Читаем список приложений.
 if( Ini_file ) ReadRepository( Ini_file );

 // Закрываем файл настроек.
 if( Ini_file ) PrfCloseProfile( Ini_file );

 // Узнаем страну, в которой работает приложение.
 Inspector.Code_page = QuerySystemCodePage();

 // Заполняем структуры данных, используемых окнами.
 ClientWindow_Start();

 // Создаем окно рабочей области.
 CHAR Class_name[] = "InspectrWndClass";
 WinRegisterClass( Inspector.Application, Class_name, (PFNWP) Inspector_ClientWindowProc, 0, 0 );

 // Создаем окно рамки.
 ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU | FCF_BORDER | FCF_NOBYTEALIGN;
 Inspector.Frame_window = WinCreateStdWindow( HWND_DESKTOP, CS_FRAME | WS_VISIBLE, &Creation_flags, Class_name, StrConst_EN_Title, 0, NULLHANDLE, 0, &Inspector.Client_window );

 // Запускаем поток для выполнения действия.
 WinPostMsg( Inspector.Client_window, MY_START_THREAD, 0, 0 );

 // Выбираем сообщения из очереди.
 QMSG Message; bzero( &Message, sizeof( QMSG ) );
 while( WinGetMsg( Inspector.Application, &Message, 0, 0, 0 ) ) WinDispatchMsg( Inspector.Application, &Message );

 // Закрываем окна.
 WinDestroyWindow( Inspector.Client_window );
 WinDestroyWindow( Inspector.Frame_window );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Inspector.Application ); return 0;
}
