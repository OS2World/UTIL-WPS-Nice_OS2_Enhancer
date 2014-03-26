// ����ﭭ� ����稭�.
#include "..\\Shared\\General.h"

// �맮�� C/C++.
#include "..\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\Shared\\StdLib.cpp"

// ����� � ��ப���.
#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// ����� � 䠩����.
#include "..\\Shared\\Files\\Files_code.cpp"
#include "..\\Shared\\Files.cpp"

// �����⢠ ���㦥���.
#include "..\\Shared\\SysState.h"

// ��६���� �।�.
#define INCLUDED_BY_SHELL

#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// ����饭�� ��� ���� ࠡ�祩 ������ ����⥫�.
#define SM_HIDE_ENHANCER          ( WM_USER + 1 )

// ���譨� ᮮ�饭��.
#include "..\\Shared\\Messages4Daemon.h"

// �ਫ������.
typedef struct _ENHANCER
 {
  // �ਫ������.
  HAB Application;

  BYTE Enhancer_mode;
  BYTE Launcher_mode;

  // ���� � �����襭��.
  BYTE Enhancer_is_terminated_normally;

  // ���� ࠬ��.
  HWND Frame_window;
  // ���� ࠡ�祩 ������.
  HWND Client_window;
 }
ENHANCER; ENHANCER Enhancer;

VOID CheckSystemConfig( VOID );

// ��ப� �ਫ������.
#include "Resources\\StrConst.h"

// �����稪.
#include "Core\\Loader\\Loader_data.cpp"
#include "Core\\Loader\\Loader_code.cpp"
#include "Core\\Loader.cpp"

#include "Core\\Threads.h"

#include "Core\\Launcher\\Launcher_code.cpp"
#include "Core\\Launcher.cpp"

// ������� ���� �ਫ������.
#include "Frame\\MainWindow\\MainWindow_code.cpp"
#include "Frame\\MainWindow.cpp"

// ��� �ਫ������ ���

INT main( INT argc, PCHAR argv[] )
{
 // ����뢠�� ᢮��⢠ �ਫ������.
 bzero( &Enhancer, sizeof( ENHANCER ) );

 // ��।��塞 �ਫ������ � ��⥬�.
 Enhancer.Application = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Enhancer.Application == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   DosExit( EXIT_PROCESS, 0 );
  }

 // ������� ��।� ᮮ�饭��.
 HMQ Message_queue = WinCreateMsgQueue( Enhancer.Application, 0 );

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Message_queue == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // �஢��塞 ��⥬�� ����ன��.
 CheckSystemConfig();

 // ����᪠�� ��⠢���騥 �ਫ������.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 Environment_Start();
 EnhancerProperties_Start();

 Loader_Start();
 Launcher_Start();

 // ������, �� ���� ᤥ����.
 if( argc == 2 )
  {
   if( strifind( "hide",    argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "mini",    argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "launch",  argv[ 1 ] ) ) Enhancer.Launcher_mode = 1;
   if( strifind( "enhance", argv[ 1 ] ) ) Enhancer.Enhancer_mode = 1;
  }

 // ��������, ���� �맢��� ���� ����஥�.
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

 // �᫨ ����⢨� �� �ᯮ����� - ��室.
 if( !Enhancer.Enhancer_mode && !Enhancer.Launcher_mode )
  {
   WinDestroyMsgQueue( Message_queue );
   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // �᫨ ���� �ਫ������ 㦥 ���� - ��室.
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

 // �����稪 ������ ����᪠���� �� ����⥫�.
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

 // �����⥫� ������ ����᪠���� ��᫥ �����稪�
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

 // �᫨ ���� �맢��� �����稪:
 if( Enhancer.Launcher_mode )
  {
   // ������� ��⮪ ��� ����᪠ ����⥫�.
   DosCreateThread( &Threads.Launcher, (PFNTHREAD) LauncherThread, 0, 0, STACK_SIZE );
  }

 // �᫨ ���� �맢��� ����⥫�:
 if( Enhancer.Enhancer_mode )
  {
   // �஡㥬 ���� ���� �����稪�.
   HWND Launcher_window = NULLHANDLE; CHAR Launcher_title[] = "Nice-OS2!L";

   // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
   HENUM Enumeration = WinBeginEnumWindows( WinQueryDesktopWindow( Enhancer.Application, NULLHANDLE ) ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // ������ ��������� ����.
     CHAR Window_title[ SIZE_OF_TITLE ] = "";
     WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Window_title );

     // �᫨ �� ���� ����⥫� - ���������� ���.
     if( strcmp( Window_title, Launcher_title ) == EQUALLY )
      {
       Launcher_window = Window;
       break;
      }
    }
   WinEndEnumWindows( Enumeration );

   // �᫨ �����稪� ��� - ��室.
   // �����-� �� ������ ����, ࠧ ������ ᥬ���, �� �� �����...
   if( !Launcher_window )
    {
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }

   // ������� ��⮪�, ��⠭�������� ��ࠡ��稪� ᮡ�⨩.
   BYTE Success = NiceLoadEnhancer( Enhancer.Application, 0, Launcher_window );

   // �᫨ �� ᤥ���� �� 㤠���� - ��室.
   if( !Success )
    {
     WinTerminate( Enhancer.Application );
     DosExit( EXIT_PROCESS, 0 );
    }

   // ��⠥� ����ன�� � ����㦠�� ����ࠦ���� � ����⥫�.
   // ��� ��⮤ �믮������ ����� Nice-os2.dll, �� ⠪ ��� DLL �ᯮ����
   // ���᭮� ����࠭�⢮ �ਫ������, �� ����� ������� � �⮬ �ਫ������.
   NiceReadSettings( 0 );

   // ����砥� ᫥����� �� ᮮ�饭�ﬨ.
   NiceRunEnhancer();
  }

 // ������� ���� ࠡ�祩 ������.
 CHAR Class_name[] = "NiceOS2WndClass!L";
 if( Enhancer.Enhancer_mode ) Class_name[ strlen( Class_name ) - 1 ] = 'E';
 WinRegisterClass( Enhancer.Application, Class_name, (PFNWP) Enhancer_MainWindowProc, 0, 0 );

 // ������� ���� ࠬ��.
 CHAR MainWindow_title[] = "Nice-OS2!L";
 if( Enhancer.Enhancer_mode ) Class_name[ strlen( Class_name ) - 1 ] = 'E';

 ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU;
 Enhancer.Frame_window = WinCreateStdWindow( HWND_DESKTOP, CS_FRAME, &Creation_flags, Class_name, MainWindow_title, 0, NULLHANDLE, 0, &Enhancer.Client_window );
 WinShowWindow( Enhancer.Frame_window, 0 );

 // �롨ࠥ� ᮮ�饭�� �� ��।�.
 QMSG Message; bzero( &Message, sizeof( QMSG ) );
 while( WinGetMsg( Enhancer.Application, &Message, 0, 0, 0 ) ) WinDispatchMsg( Enhancer.Application, &Message );

 // ����뢠�� ����.
 WinDestroyWindow( Enhancer.Client_window );
 WinDestroyWindow( Enhancer.Frame_window );

 // �᫨ �맢�� ����⥫�:
 if( Enhancer.Enhancer_mode )
  {
   // �⪫�砥� ��ࠡ��稪� ᮡ�⨩, �����蠥� ࠡ��� ��⮪��.
   NiceReleaseEnhancer( Enhancer.Application, 0 );
  }

 // ����塞 䠩�� �⫠��筮� ���ᨨ.
 DosForceDelete( "_log.txt" ); DosForceDelete( "XTest.exe" );

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Enhancer.Application );
 DosExit( EXIT_PROCESS, 0 );
}

// ��� �஢���� ��⥬�� ����ன�� ���

VOID CheckSystemConfig( VOID )
{
 // �஢��塞 ����ன�� � 䠩�� "Config.sys".
 CHAR File_name[ SIZE_OF_NAME ] = "*:\\Config.sys"; ULONG Boot_drive = 0;
 DosQuerySysInfo( QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PULONG) &Boot_drive, sizeof( Boot_drive ) );
 File_name[ 0 ] = (CHAR) Boot_drive + 64;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READONLY;

 HFILE File = NULLHANDLE; ULONG Report = 0;
 APIRET RC = DosOpen( File_name, &File, &Report, 0, FILE_NORMAL, Action, Mode, NULL );

 // �᫨ 䠩� �� �����:
 if( RC == NO_ERROR )
  {
   // �⢮��� ������ ��� ⥪��.
   PCHAR Text = NULL; ULONG Length = 65536;
   if( DosAllocMem( (PPVOID) &Text, Length, PAG_ALLOCATE ) != NO_ERROR )
    {
     DosClose( File );
     DosExit( EXIT_PROCESS, 0 );
    }

   // ��⠥� ����ன��.
   memset( Text, 0, Length );
   DosRead( File, Text, Length, &Length );

   // �஢��塞, ���� �� � ����ன��� ���� � ��⠫��� ����⥫�.
   BYTE Path_is_present = 1; if( !strifind( "NICE\\ENHANCER", Text ) ) Path_is_present = 0;

   // �᢮������� ������.
   DosFreeMem( Text ); Text = NULL;

   // ����뢠�� 䠩�.
   DosClose( File ); File = NULLHANDLE;

   // �᫨ ����ன�� ������ ���ࠢ��쭮:
   if( !Path_is_present )
    {
     // �����뢠�� ᮮ�饭��.
     CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );

     if( QuerySystemCodePage() == RUSSIAN )
      WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_No_path_in_Config_sys, Title, NULLHANDLE, NULLHANDLE );
     else
      WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_No_path_in_Config_sys, Title, NULLHANDLE, NULLHANDLE );

     // ��室.
     DosExit( EXIT_PROCESS, 0 );
    }
  }

 // ������.
 return;
}
