// Постоянные величины.
#include "..\\Shared\\General.h"

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

// Свойства окружения.
#include "..\\Shared\\SysState.h"

// Переменные среды.
#define INCLUDED_BY_SHELL

#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// Сообщения для окна рабочей области расширителя.
#define SM_HIDE_ENHANCER          ( WM_USER + 1 )

// Внешние сообщения.
#include "..\\Shared\\Messages4Daemon.h"

// Приложение.
typedef struct _ENHANCER
 {
  // Приложение.
  HAB Application;

  BYTE Enhancer_mode;
  BYTE Launcher_mode;

  // Отчет о завершении.
  BYTE Enhancer_is_terminated_normally;

  // Окно рамки.
  HWND Frame_window;
  // Окно рабочей области.
  HWND Client_window;
 }
ENHANCER; ENHANCER Enhancer;

VOID CheckSystemConfig( VOID );

// Строки приложения.
#include "Resources\\StrConst.h"

// Загрузчик.
#include "Core\\Loader\\Loader_data.cpp"
#include "Core\\Loader\\Loader_code.cpp"
#include "Core\\Loader.cpp"

#include "Core\\Threads.h"

#include "Core\\Launcher\\Launcher_code.cpp"
#include "Core\\Launcher.cpp"

// Главное окно приложения.
#include "Frame\\MainWindow\\MainWindow_code.cpp"
#include "Frame\\MainWindow.cpp"

// ─── Приложение ───

INT main( INT argc, PCHAR argv[] )
{
 // Сбрасываем свойства приложения.
 bzero( &Enhancer, sizeof( ENHANCER ) );

 // Определяем приложение в системе.
 Enhancer.Application = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Enhancer.Application == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   DosExit( EXIT_PROCESS, 0 );
  }

 // Создаем очередь сообщений.
 HMQ Message_queue = WinCreateMsgQueue( Enhancer.Application, 0 );

 // Если очередь создать не удалось - выход.
 if( Message_queue == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // Проверяем системные настройки.
 CheckSystemConfig();

 // Запускаем составляющие приложения.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 Environment_Start();
 EnhancerProperties_Start();

 Loader_Start();
 Launcher_Start();

 // Узнаем, что надо сделать.
 if( argc == 2 )
  {
   if( strifind( "hide",    argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "mini",    argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "launch",  argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "enhance", argv[ 1 ] ) ) Enhancer.Enhancer_mode = 1;
  }

 // Возможно, надо вызвать окно настроек.
 if( argc == 2 )
  {
   if( strfind( "ControlCenter", argv[ 1 ] ) )
    {
     CHAR Path_to_ControlCenter[ SIZE_OF_PATH ] = "";
     GetCurrentPath( Path_to_ControlCenter );
     strcat( Path_to_ControlCenter, "\\Nice-eCS.exe" );

     Execute( Path_to_ControlCenter, argv[ 1 ] );

     WinDestroyMsgQueue( Message_queue );
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }
  }

 // Если действие не распознано - выход.
 if( !Enhancer.Enhancer_mode && !Enhancer.Launcher_mode )
  {
   WinDestroyMsgQueue( Message_queue );
   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // Если окно приложения уже есть - выход.
 {
  CHAR Semaphore_name[] = "\\SEM32\\NICE-OS2!L"; HMTX hmtxAlreadyRunning = NULLHANDLE;
  if( Enhancer.Enhancer_mode ) Semaphore_name[ strlen( Semaphore_name ) - 1 ] = 'E';

  if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR )
   {
    WinDestroyMsgQueue( Message_queue );
    WinTerminate( Enhancer.Application );
    DosExit( EXIT_PROCESS, 0 );
   }
  else
   {
    DosCreateMutexSem( Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1 );
   }
 }

 // Загрузчик должен запускаться до расширителя.
 if( Enhancer.Launcher_mode )
  {
   CHAR Semaphore_name[] = "\\SEM32\\NICE-OS2!E"; HMTX hmtxAlreadyRunning = NULLHANDLE;

   if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR )
    {
     WinDestroyMsgQueue( Message_queue );
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }
  }

 // Расширитель должен запускаться после загрузчика
 if( Enhancer.Enhancer_mode )
  {
   CHAR Semaphore_name[] = "\\SEM32\\NICE-OS2!L"; HMTX hmtxAlreadyRunning = NULLHANDLE;

   if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) != NO_ERROR )
    {
     WinDestroyMsgQueue( Message_queue );
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }
  }

 // Если надо вызвать загрузчик:
 if( Enhancer.Launcher_mode )
  {
   // Создаем поток для запуска расширителя.
   DosCreateThread( &Threads.Launcher, (PFNTHREAD) LauncherThread, 0, 0, STACK_SIZE );
  }

 // Если надо вызвать расширитель:
 if( Enhancer.Enhancer_mode )
  {
   // Пробуем найти окно загрузчика.
   HWND Launcher_window = NULLHANDLE; CHAR Launcher_title[] = "Nice-OS2!L";

   // Перебираем окна в окне рабочего стола.
   HENUM Enumeration = WinBeginEnumWindows( WinQueryDesktopWindow( Enhancer.Application, NULLHANDLE ) ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Узнаем заголовок окна.
     CHAR Window_title[ SIZE_OF_TITLE ] = "";
     WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Window_title );

     // Если это окно расширителя - запоминаем его.
     if( strcmp( Window_title, Launcher_title ) == EQUALLY )
      {
       Launcher_window = Window;
       break;
      }
    }
   WinEndEnumWindows( Enumeration );

   // Если загрузчика нет - выход.
   // Вообще-то он должен быть, раз найден семафор, но кто знает...
   if( !Launcher_window )
    {
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }

   // Создаем потоки, устанавливаем обработчики событий.
   BYTE Success = NiceLoadEnhancer( Enhancer.Application, 0, Launcher_window );

   // Если это сделать не удалось - выход.
   if( !Success )
    {
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }

   // Читаем настройки и загружаем изображения в расширитель.
   // Этот метод выполняется внутри Nice-os2.dll, но так как DLL использует
   // адресное пространство приложения, все данные остаются в этом приложении.
   NiceReadSettings( 0 );

   // Включаем слежение за сообщениями.
   NiceRunEnhancer();
  }

 // Создаем окно рабочей области.
 CHAR Class_name[] = "NiceOS2WndClass!L";
 if( Enhancer.Enhancer_mode ) Class_name[ strlen( Class_name ) - 1 ] = 'E';
 WinRegisterClass( Enhancer.Application, Class_name, (PFNWP) Enhancer_MainWindowProc, 0, 0 );

 // Создаем окно рамки.
 CHAR MainWindow_title[] = "Nice-OS2!L";
 if( Enhancer.Enhancer_mode ) Class_name[ strlen( Class_name ) - 1 ] = 'E';

 ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU;
 Enhancer.Frame_window = WinCreateStdWindow( HWND_DESKTOP, CS_FRAME, &Creation_flags, Class_name, MainWindow_title, 0, NULLHANDLE, 0, &Enhancer.Client_window );
 WinShowWindow( Enhancer.Frame_window, 0 );

 // Выбираем сообщения из очереди.
 QMSG Message; bzero( &Message, sizeof( QMSG ) );
 while( WinGetMsg( Enhancer.Application, &Message, 0, 0, 0 ) ) WinDispatchMsg( Enhancer.Application, &Message );

 // Закрываем окна.
 WinDestroyWindow( Enhancer.Client_window );
 WinDestroyWindow( Enhancer.Frame_window );

 // Если вызван расширитель:
 if( Enhancer.Enhancer_mode )
  {
   // Отключаем обработчики событий, завершаем работу потоков.
   NiceReleaseEnhancer( Enhancer.Application, 0 );
  }

 // Удаляем файлы отладочной версии.
 DosForceDelete( "_log.txt" ); DosForceDelete( "XTest.exe" );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Enhancer.Application );
 DosExit( EXIT_PROCESS, 0 );
}

// ─── Проверяет системные настройки ───

VOID CheckSystemConfig( VOID )
{
 // Проверяем настройки в файле "Config.sys".
 CHAR File_name[ SIZE_OF_NAME ] = "*:\\Config.sys"; ULONG Boot_drive = 0;
 DosQuerySysInfo( QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PULONG) &Boot_drive, sizeof( Boot_drive ) );
 File_name[ 0 ] = (CHAR) Boot_drive + 64;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READONLY;

 HFILE File = NULLHANDLE; ULONG Report = 0;
 APIRET RC = DosOpen( File_name, &File, &Report, 0, FILE_NORMAL, Action, Mode, NULL );

 // Если файл был открыт:
 if( RC == NO_ERROR )
  {
   // Отводим память для текста.
   PCHAR Text = NULL; ULONG Length = 65536;
   if( DosAllocMem( (PPVOID) &Text, Length, PAG_ALLOCATE ) != NO_ERROR )
    {
     DosClose( File );
     DosExit( EXIT_PROCESS, 0 );
    }

   // Читаем настройки.
   memset( Text, 0, Length );
   DosRead( File, Text, Length, &Length );

   // Проверяем, есть ли в настройках путь к каталогу расширителя.
   BYTE Path_is_present = 1; if( !strifind( "NICE\\ENHANCER", Text ) ) Path_is_present = 0;

   // Освобождаем память.
   DosFreeMem( Text ); Text = NULL;

   // Закрываем файл.
   DosClose( File ); File = NULLHANDLE;

   // Если настройки заданы неправильно:
   if( !Path_is_present )
    {
     // Показываем сообщение.
     CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );

     if( QuerySystemCodePage() == RUSSIAN )
      WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_No_path_in_Config_sys, Title, NULLHANDLE, NULLHANDLE );
     else
      WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_No_path_in_Config_sys, Title, NULLHANDLE, NULLHANDLE );

     // Выход.
     DosExit( EXIT_PROCESS, 0 );
    }
  }

 // Возврат.
 return;
}
