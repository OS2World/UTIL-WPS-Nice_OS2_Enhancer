// Постоянные величины.
#include "..\\..\\Nice-os2\\Shared\\General.h"
#include "..\\..\\Nice-os2\\Shared\\Scan_codes.h"

// Вызовы C/C++.
#include "..\\..\\Nice-os2\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\StdLib.cpp"

// Работа со строками.
#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

// Работа с файлами.
#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// Данные приложения.
typedef struct _NAMES
 {
  // Приложение.
  HAB Application;

  // Окно рамки (и оно же - окно диалога).
  HWND Frame_window;
  CHAR Frame_window_title[ SIZE_OF_TITLE ];

  typedef struct _SETTINGS
   {
    // Страна, в которой работает приложение.
    ULONG Code_page; CHAR DBCS_line[ 12 ];

    // Рабочий каталог приложения.
    CHAR Current_directory[ SIZE_OF_PATH ];
    // Имя файла, в котором расположены настройки.
    CHAR Ini_file[ SIZE_OF_PATH ];

    // Поле ввода занято.
    BYTE InputField_is_locked;
    // Настройки были изменены.
    BYTE Settings_are_changed;
   }
  SETTINGS; SETTINGS Settings;

  typedef struct _HELP
   {
    // Обозреватель для просмотра руководства.
    CHAR Viewer[ SIZE_OF_PATH ];
   }
  HELP; HELP Help;

  // Что надо сделать.
  typedef struct _TASK
   {
    // Привести имена к правильному виду?
    BYTE Convert_names;
    // Исправить расхождения в именах?
    BYTE Revise_differences;
    // Удалить изображения?
    BYTE Remove_images;
    // Удалить сведения о типе?
    BYTE Remove_types;
    // Сбросить свойство "Только для чтения"?
    BYTE Turn_OFF_ReadOnly;

    // Каталог, с которого надо начать обработку.
    CHAR Root_directory[ SIZE_OF_PATH ];
   }
  TASK; TASK Task;

  // Идет обработка файлов.
  BYTE Processing;
 }
NAMES; NAMES Names;

// Строки и изображения.
#include "Resources\\StrConst.h"

// Внутренние сообщения.
#define MY_INITDLG        ( WM_USER +  1 )

#define MY_SHOW_SETTINGS  ( WM_USER + 10 )
#define MY_ENABLE_BUTTONS ( WM_USER + 20 )

// Функции для запуска потоков приложения.
#include "Threads\\ProcessorThread.h"

// Окна приложения.
#include "Pages\\DialogWindow\\DialogWindow.h"
#include "Pages\\DialogWindow\\DialogWindow_form.cpp"
#include "Pages\\DialogWindow.cpp"

// Потоки приложения.
#include "Threads\\ProcessorThread.c"

#include "Threads\\Routines\\Attrs.c"
#include "Threads\\Routines\\Permissions.c"

// Внутренние функции
VOID ParseArg( INT, PCHAR, PCHAR );

// ─── Приложение ───

INT main( INT argc, PCHAR argv[] )
{
 // Сбрасываем свойства приложения.
 bzero( &Names, sizeof( Names ) );

 // Определяем приложение в системе.
 Names.Application = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Names.Application == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   return 0;
  }

 // Создаем очередь сообщений.
 HMQ Message_queue = WinCreateMsgQueue( Names.Application, 0 );

 // Если очередь создать не удалось - выход.
 if( Message_queue == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   WinTerminate( Names.Application ); return 0;
  }

 // Запускаем составляющие приложения.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 // Если окно приложения уже есть - выход.
 {
  CHAR Semaphore_name[] = "\\SEM32\\FNAMES";
  HMTX hmtxAlreadyRunning = NULLHANDLE;

  if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR )
   {
    WinDestroyMsgQueue( Message_queue );
    WinTerminate( Names.Application );
    return 0;
   }
  else
   {
    DosCreateMutexSem( Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1 );
   }
 }

 // Разбираем параметры и заполняем структуры данных приложения.
 ParseArg( argc, argv[ 0 ], argv[ 1 ] );

 // Заполняем структуры данных, используемых окнами.
 DialogWindow_Start();

 // Загружаем диалог. У диалогов не бывает рабочей области, так что окно диалога будет окном рамки.
 // Название/расположение окна будет задано внутри обработчика сообщений при получении "MY_INITDLG".
 Names.Frame_window = WinLoadDlg( HWND_DESKTOP, NULLHANDLE, DialogWindow_DlgProc, NULLHANDLE, ID_MAINWNDFORM, NULL );
 if( Names.Frame_window == NULLHANDLE )
  {
   WinDestroyMsgQueue( Message_queue );
   WinTerminate( Names.Application );
   return 0;
  }

 // Начинаем диалог и ждем его завершения.
 // Обработка сообщений будет прекращена вызовом "WinDismissDlg()".
 WinProcessDlg( Names.Frame_window );

 // Закрываем окно диалога. Поля ввода оно удалит самостоятельно.
 WinDestroyWindow( Names.Frame_window );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Names.Application ); return 0;
}

// ─── Разбирает параметры ───

VOID ParseArg( INT argc, PCHAR argv_1, PCHAR argv_2 )
{
 // Узнаем страну, в которой работает приложение.
 if( argc == 2 && strifind( "english", argv_2 ) )
  {
   Names.Settings.Code_page = ENGLISH;
  }
 else
  {
   ULONG Size_of_list = 0; COUNTRYCODE Country = {0};
   DosQueryCp( sizeof( Names.Settings.Code_page ), &Names.Settings.Code_page, &Size_of_list );

   Country.codepage = Names.Settings.Code_page;
   DosQueryDBCSEnv( 12, &Country, Names.Settings.DBCS_line );
  }

 // Узнаем рабочий каталог.
 {
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
  DosQueryCurrentDisk( &Current_drive, &Drive_map );
  Names.Settings.Current_directory[ 0 ] = (CHAR) Current_drive + 64;
  Names.Settings.Current_directory[ 1 ] = ':';
  Names.Settings.Current_directory[ 2 ] = '\\';
  DosQueryCurrentDir( 0, &Names.Settings.Current_directory[ 3 ], &Length );
 }

 // Задаем имя файла, в котором расположены настройки.
 {
  strcpy( Names.Settings.Ini_file, Names.Settings.Current_directory );
  strcat( Names.Settings.Ini_file, "\\Names.ini" );
 }

 // Запоминаем путь к приложению для просмотра руководства.
 {
  strcpy( Names.Help.Viewer, "View.exe" );
 }

 // Возврат.
 return;
}
