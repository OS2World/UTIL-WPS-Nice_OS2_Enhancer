#define DEBUG_VERSION
#include "Nice-os2.cpp"

// ��� �ਫ������ ���

VOID XTest( HAB Application )
{

 // ������ ����� ��������� � ���⨭��.
 INT TitleBar_height = WinQuerySysValue( QueryDesktopWindow(), SV_CYMINMAXBUTTON );

 Log( TitleBar_height );


 /*
 // ������ ᮤ�ন��� Clipboard.
 BYTE Common_string[ 1024 ] = "";
 LONG Common_string_length = 1024;
 BYTE UCS2LittleEndian_format[] = "text/unicode";
 BYTE UCS2LittleEndian_string[ 2048 ] = "";
 LONG UCS2LittleEndian_string_length = 2048;

 GetStringFromClipboard( Application,
                         Common_string,
                         Common_string_length,
                         UCS2LittleEndian_string,
                         UCS2LittleEndian_string_length,
                         UCS2LittleEndian_format
 );

 Log( Common_string );

 Log( UCS2LittleEndian_string[ 0 ] );
 Log( UCS2LittleEndian_string[ 1 ] );
 Log( UCS2LittleEndian_string[ 2 ] );
 Log( UCS2LittleEndian_string[ 3 ] );
 Log( UCS2LittleEndian_string[ 4 ] );
 Log( UCS2LittleEndian_string[ 5 ] );
 Log( UCS2LittleEndian_string[ 6 ] );
 Log( UCS2LittleEndian_string[ 7 ] );
 Log( UCS2LittleEndian_string[ 8 ] );
 */

 /*
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ...
  }
 WinEndEnumWindows( Enumeration );
 */

 // ������.
 return;
}

INT main( INT argc, CHAR *argv[] )
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

 /*
 InitKernel( Application, 0, NULLHANDLE );
 SetPreDefinedSettings( SET_ALL_SETTINGS );
 */

 // �믮��塞 ����⢨�.
 DosForceDelete( "_log.txt" );
 Enhancer.Application = Application; XTest( Application );

 // ����뢠�� ��।� ᮮ�饭��.
 WinDestroyMsgQueue( Message_queue );

 // ��室.
 WinTerminate( Application ); return 0;
}
