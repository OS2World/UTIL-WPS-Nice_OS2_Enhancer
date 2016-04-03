#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>
#include <StdLib.h>

#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// ��� �ਫ������ ���

INT main( VOID )
{
 // ��।��塞 �ਫ������ � ��⥬�.
 HAB Application = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Application == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   return 0;
  }

 // ������� ��।� ᮮ�饭��.
 HMQ Message_queue = WinCreateMsgQueue( Application, 0 );

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Message_queue == NULLHANDLE )
  {
   // ��� - �訡��.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // ��室.
   WinTerminate( Application ); return 0;
  }

 // ������ ࠡ�稩 ��⠫��.
 CHAR Current_directory[ SIZE_OF_PATH ] = "";

 ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
 DosQueryCurrentDisk( &Current_drive, &Drive_map );
 Current_directory[ 0 ] = (CHAR) Current_drive + 64;
 Current_directory[ 1 ] = ':';
 Current_directory[ 2 ] = '\\';
 DosQueryCurrentDir( 0, &Current_directory[ 3 ], &Length );

 // ��室�� 䠩� ����⥫� � ����᪠�� ���.
 for( INT Count = 0; Count < 2; Count ++ )
  {
   // �஡㥬 ���� 䠩�.
   CHAR Path[ SIZE_OF_PATH ] = ""; strcpy( Path, Current_directory ); CutNameInPath( Path );

   if( Count == 0 ) strcat( Path, "\\Enhancer" );
   if( Count == 1 ) strcat( Path, "\\Nice\\Enhancer" );

   CHAR Exe_file[ SIZE_OF_PATH ] = ""; strcpy( Exe_file, Path ); strcat( Exe_file, "\\" );
   CHAR Exe_name[] = "Nice-os2.exe"; strcat( Exe_file, Exe_name );

   // �᫨ 䠩� ������ - ����᪠�� ����⥫�.
   if( FileExists( Exe_file ) )
    {
     CHAR Parameters[ SIZE_OF_PATH ] = "";
     strcpy( Parameters, Exe_name );
     strcat( Parameters, "|" );
     strcat( Parameters, "launcher" );
     strchg( Parameters, '|', 0x00 );

     DosSetDefaultDisk( DriveNumberFromPath( Path ) ); DosSetCurrentDir( Path );
     CHAR Error_string[ 1 ] = ""; RESULTCODES Return_codes;
     DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_ASYNC, Parameters, NULL, &Return_codes, Exe_file );
    }
  }

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Application ); return 0;
}
