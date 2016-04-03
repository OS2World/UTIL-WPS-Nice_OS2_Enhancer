// ����ﭭ� ����稭�.
#include "..\\Shared\\General.h"
#pragma pack(4)

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

// ��ᯮ������� ����.
#include "..\\Shared\\WindowTree.h"
#include "..\\Shared\\WindowTree\\WindowTree_code.cpp"
#include "..\\Shared\\WindowTree.cpp"

#include "..\\Shared\\Layout.h"
#include "..\\Shared\\Layout\\Layout_data.cpp"
#include "..\\Shared\\Layout\\Layout_list.cpp"
#include "..\\Shared\\Layout\\Layout_code.cpp"
#include "..\\Shared\\Layout.cpp"

// �����⢠ ���㦥���.
#include "..\\Shared\\SysState.h"
#pragma pack(4)

// ��६���� �।�.
#define INCLUDED_BY_SHELL

#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// ���� � ���� �����.
#include "..\\Shared\\Repository.h"
#include "..\\Shared\\Repository\\Repository_data.cpp"
#include "..\\Shared\\Repository\\Repository_base.cpp"
#include "..\\Shared\\Repository\\Repository_code.cpp"
#include "..\\Shared\\Repository.cpp"

// ����� �ਫ������.
typedef struct _INSPECTOR
 {
  // �ਫ������.
  HAB Application;

  // ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
  ULONG Code_page;

  // ���� ࠬ��.
  HWND Frame_window;
  CHAR Frame_window_title[ SIZE_OF_TITLE ];
  // ���� ࠡ�祩 ������.
  HWND Client_window;

  // ��⠫�� �ਫ������.
  CHAR Current_directory[ SIZE_OF_PATH ];

  // ����ன�� ������ ���� ����ᠭ�.
  BYTE Write_settings;

  // ������� ��⮪�.
  BYTE Processing;
  BYTE Observing;
  BYTE ObserverReportReading;

  // ����ﭭ� PIPE-ᮥ������� STD_*.
  HFILE Saved_StdInHandle;  
  HFILE Saved_StdOutHandle; 
  HFILE Saved_StdErrHandle; 

  HPIPE Pipe_ReadHandle_1; HPIPE Pipe_WriteHandle_1;
  HPIPE Pipe_ReadHandle_2; HPIPE Pipe_WriteHandle_2;
 }
INSPECTOR; INSPECTOR Inspector;

// ��ப� �ਫ������.
#include "Resources\\StrConst.h"

// ����७��� ᮮ�饭��.
#define MY_CREATE       ( WM_USER +  1 )

#define MY_APPLY_LAYOUT ( WM_USER + 10 )
#define MY_START_THREAD ( WM_USER + 11 )

// ���譨� ᮮ�饭��.
#include "..\\Shared\\Messages4Daemon.h"

// �㭪樨 ��� ����᪠ ��⮪�� �ਫ������.
#include "Threads\\Threads.h"

// ���� �ਫ������.
#include "Pages\\Controls.h"

#include "Pages\\ClientWindow\\ClientWindow_data.cpp"
#include "Pages\\ClientWindow\\ClientWindow_open.cpp"
#include "Pages\\ClientWindow\\ClientWindow_page.cpp"
#include "Pages\\ClientWindow.cpp"

// ��⮪� �ਫ������.
#include "Threads\\Limits.h"
#include "Threads\\Methods.c"
#include "Threads\\ObserverEThread.h"
#include "Threads\\ObserverEThread.c"
#include "Threads\\ObserverRThread.c"
#include "Threads\\ProcessorThread.h"
#include "Threads\\ProcessorThread.c"

// ��� �ਫ������ ���

INT main( INT argc, PCHAR argv[] )
{
 // ����뢠�� ᢮��⢠ �ਫ������.
 bzero( &Inspector, sizeof( INSPECTOR ) );

 // ��।��塞 �ਫ������ � ��⥬�.
 Inspector.Application = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Inspector.Application == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   return 0;
  }

 // ������� ��।� ᮮ�饭��.
 HMQ Message_queue = WinCreateMsgQueue( Inspector.Application, 0 );

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Message_queue == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   WinTerminate( Inspector.Application ); return 0;
  }

 // ����᪠�� ��⠢���騥 �ਫ������.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 WindowTree_Start();
 Layout_Start();
 Environment_Start();
 EnhancerProperties_Start();

 Repository_Start();

 // �᫨ ���� �ਫ������ 㦥 ���� - ��室.
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

 // ������ ࠡ�稩 ��⠫��.
 {
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
  DosQueryCurrentDisk( &Current_drive, &Drive_map );
  Inspector.Current_directory[ 0 ] = (CHAR) Current_drive + 64;
  Inspector.Current_directory[ 1 ] = ':';
  Inspector.Current_directory[ 2 ] = '\\';
  DosQueryCurrentDir( 0, &Inspector.Current_directory[ 3 ], &Length );
 }

 // �ਫ������ ����� ���� �맢��� �� ��� ��⠫��� ����� ����⥫�.
 // ���室�� � ��� �����騩 ��⠫��.
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

 // ���뢠�� 䠩� ����஥�.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = "";
 {
  strcpy( Settings_file_name, Inspector.Current_directory );
  CutNameInPath( Settings_file_name ); strcat( Settings_file_name, "\\Nice-os2.ini" );
 }
 HINI Ini_file = OpenIniProfile( Inspector.Application, Settings_file_name );

 // ��⠥� ᯨ᮪ �ਫ������.
 if( Ini_file ) ReadRepository( Ini_file );

 // ����뢠�� 䠩� ����஥�.
 if( Ini_file ) PrfCloseProfile( Ini_file );

 // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
 Inspector.Code_page = QuerySystemCodePage();

 // ������塞 �������� ������, �ᯮ��㥬�� ������.
 ClientWindow_Start();

 // ������� ���� ࠡ�祩 ������.
 CHAR Class_name[] = "InspectrWndClass";
 WinRegisterClass( Inspector.Application, Class_name, (PFNWP) Inspector_ClientWindowProc, 0, 0 );

 // ������� ���� ࠬ��.
 ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU | FCF_BORDER | FCF_NOBYTEALIGN;
 Inspector.Frame_window = WinCreateStdWindow( HWND_DESKTOP, CS_FRAME | WS_VISIBLE, &Creation_flags, Class_name, StrConst_EN_Title, 0, NULLHANDLE, 0, &Inspector.Client_window );

 // ����᪠�� ��⮪ ��� �믮������ ����⢨�.
 WinPostMsg( Inspector.Client_window, MY_START_THREAD, 0, 0 );

 // �롨ࠥ� ᮮ�饭�� �� ��।�.
 QMSG Message; bzero( &Message, sizeof( QMSG ) );
 while( WinGetMsg( Inspector.Application, &Message, 0, 0, 0 ) ) WinDispatchMsg( Inspector.Application, &Message );

 // ����뢠�� ����.
 WinDestroyWindow( Inspector.Client_window );
 WinDestroyWindow( Inspector.Frame_window );

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Inspector.Application ); return 0;
}
