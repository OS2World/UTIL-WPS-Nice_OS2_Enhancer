#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

// �������� ������.
#define POINT  POINTL
#define PPOINT PPOINTL

#include <OS2.h>
#include <StdLib.h>

#include "..\\Shared\\General.h"
#pragma pack(4)

#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// Scan-���� ������.
#define SC_NUM_8   72
#define SC_NUM_4   75
#define SC_NUM_5   76
#define SC_NUM_6   77
#define SC_NUM_2   80

// ����饭�� ��� ����.
#define WM_MARK          WM_NULL
#define MRK_GO_TO_ROOM   0x00FACE00

// ��� �ਫ������ ���

INT main( INT argc, CHAR *argv[] )
{
 // ������ �������, � ������ ���� ��४�������.
 BYTE Scan_code = 0; SHORT Key = 0;

 if( argc == 2 )
  {
   if( stristr( "north", argv[ 1 ] ) ) { Scan_code = SC_NUM_8; Key = VK_UP;    }
   if( stristr( "west",  argv[ 1 ] ) ) { Scan_code = SC_NUM_4; Key = VK_LEFT;  }
   if( stristr( "east",  argv[ 1 ] ) ) { Scan_code = SC_NUM_6; Key = VK_RIGHT; }
   if( stristr( "south", argv[ 1 ] ) ) { Scan_code = SC_NUM_2; Key = VK_DOWN;  }
   if( stristr( "desk",  argv[ 1 ] ) ) { Scan_code = SC_NUM_5; Key = 0;        }
  }

 // �᫨ ������ �������⭠ - ��室.
 if( Scan_code == 0 ) if( Key == 0 ) return 0;

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

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = WinQueryDesktopWindow( Application, NULLHANDLE );

 // ���뫠�� ��� ᮮ�饭�� WM_MARK.
 WinPostMsg( Desktop, WM_MARK, (MPARAM) MRK_GO_TO_ROOM, (MPARAM) Scan_code );

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Application ); return 0;
}
