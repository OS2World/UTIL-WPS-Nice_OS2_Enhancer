// ����ﭭ� ����稭�.
#include "..\\..\\Nice-os2\\Shared\\General.h"
#include "..\\..\\Nice-os2\\Shared\\Scan_codes.h"

// �맮�� C/C++.
#include "..\\..\\Nice-os2\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\StdLib.cpp"

// ����� � ��ப���.
#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

// ����� � 䠩����.
#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// ����� �ਫ������.
typedef struct _NAMES
 {
  // �ਫ������.
  HAB Application;

  // ���� ࠬ�� (� ��� �� - ���� �������).
  HWND Frame_window;
  CHAR Frame_window_title[ SIZE_OF_TITLE ];

  typedef struct _SETTINGS
   {
    // ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
    ULONG Code_page; CHAR DBCS_line[ 12 ];

    // ����稩 ��⠫�� �ਫ������.
    CHAR Current_directory[ SIZE_OF_PATH ];
    // ��� 䠩��, � ���஬ �ᯮ������ ����ன��.
    CHAR Ini_file[ SIZE_OF_PATH ];

    // ���� ����� �����.
    BYTE InputField_is_locked;
    // ����ன�� �뫨 ��������.
    BYTE Settings_are_changed;
   }
  SETTINGS; SETTINGS Settings;

  typedef struct _HELP
   {
    // ����ॢ�⥫� ��� ��ᬮ�� �㪮����⢠.
    CHAR Viewer[ SIZE_OF_PATH ];
   }
  HELP; HELP Help;

  // �� ���� ᤥ����.
  typedef struct _TASK
   {
    // �ਢ��� ����� � �ࠢ��쭮�� ����?
    BYTE Convert_names;
    // ��ࠢ��� ��宦����� � ������?
    BYTE Revise_differences;
    // ������� ����ࠦ����?
    BYTE Remove_images;
    // ������� ᢥ����� � ⨯�?
    BYTE Remove_types;
    // ������ ᢮��⢮ "���쪮 ��� �⥭��"?
    BYTE Turn_OFF_ReadOnly;

    // ��⠫��, � ���ண� ���� ����� ��ࠡ���.
    CHAR Root_directory[ SIZE_OF_PATH ];
   }
  TASK; TASK Task;

  // ���� ��ࠡ�⪠ 䠩���.
  BYTE Processing;
 }
NAMES; NAMES Names;

// ��ப� � ����ࠦ����.
#include "Resources\\StrConst.h"

// ����७��� ᮮ�饭��.
#define MY_INITDLG        ( WM_USER +  1 )

#define MY_SHOW_SETTINGS  ( WM_USER + 10 )
#define MY_ENABLE_BUTTONS ( WM_USER + 20 )

// �㭪樨 ��� ����᪠ ��⮪�� �ਫ������.
#include "Threads\\ProcessorThread.h"

// ���� �ਫ������.
#include "Pages\\DialogWindow\\DialogWindow.h"
#include "Pages\\DialogWindow\\DialogWindow_form.cpp"
#include "Pages\\DialogWindow.cpp"

// ��⮪� �ਫ������.
#include "Threads\\ProcessorThread.c"

#include "Threads\\Routines\\Attrs.c"
#include "Threads\\Routines\\Permissions.c"

// ����७��� �㭪樨
VOID ParseArg( INT, PCHAR, PCHAR );

// ��� �ਫ������ ���

INT main( INT argc, PCHAR argv[] )
{
 // ����뢠�� ᢮��⢠ �ਫ������.
 bzero( &Names, sizeof( Names ) );

 // ��।��塞 �ਫ������ � ��⥬�.
 Names.Application = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Names.Application == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   return 0;
  }

 // ������� ��।� ᮮ�饭��.
 HMQ Message_queue = WinCreateMsgQueue( Names.Application, 0 );

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Message_queue == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   WinTerminate( Names.Application ); return 0;
  }

 // ����᪠�� ��⠢���騥 �ਫ������.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 // �᫨ ���� �ਫ������ 㦥 ���� - ��室.
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

 // �����ࠥ� ��ࠬ���� � ������塞 �������� ������ �ਫ������.
 ParseArg( argc, argv[ 0 ], argv[ 1 ] );

 // ������塞 �������� ������, �ᯮ��㥬�� ������.
 DialogWindow_Start();

 // ����㦠�� ������. � �������� �� �뢠�� ࠡ�祩 ������, ⠪ �� ���� ������� �㤥� ����� ࠬ��.
 // ��������/�ᯮ������� ���� �㤥� ������ ����� ��ࠡ��稪� ᮮ�饭�� �� ����祭�� "MY_INITDLG".
 Names.Frame_window = WinLoadDlg( HWND_DESKTOP, NULLHANDLE, DialogWindow_DlgProc, NULLHANDLE, ID_MAINWNDFORM, NULL );
 if( Names.Frame_window == NULLHANDLE )
  {
   WinDestroyMsgQueue( Message_queue );
   WinTerminate( Names.Application );
   return 0;
  }

 // ��稭��� ������ � ���� ��� �����襭��.
 // ��ࠡ�⪠ ᮮ�饭�� �㤥� �४�饭� �맮��� "WinDismissDlg()".
 WinProcessDlg( Names.Frame_window );

 // ����뢠�� ���� �������. ���� ����� ��� 㤠��� ᠬ����⥫쭮.
 WinDestroyWindow( Names.Frame_window );

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Names.Application ); return 0;
}

// ��� �����ࠥ� ��ࠬ���� ���

VOID ParseArg( INT argc, PCHAR argv_1, PCHAR argv_2 )
{
 // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
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

 // ������ ࠡ�稩 ��⠫��.
 {
  ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
  DosQueryCurrentDisk( &Current_drive, &Drive_map );
  Names.Settings.Current_directory[ 0 ] = (CHAR) Current_drive + 64;
  Names.Settings.Current_directory[ 1 ] = ':';
  Names.Settings.Current_directory[ 2 ] = '\\';
  DosQueryCurrentDir( 0, &Names.Settings.Current_directory[ 3 ], &Length );
 }

 // ������ ��� 䠩��, � ���஬ �ᯮ������ ����ன��.
 {
  strcpy( Names.Settings.Ini_file, Names.Settings.Current_directory );
  strcat( Names.Settings.Ini_file, "\\Names.ini" );
 }

 // ���������� ���� � �ਫ������ ��� ��ᬮ�� �㪮����⢠.
 {
  strcpy( Names.Help.Viewer, "View.exe" );
 }

 // ������.
 return;
}
