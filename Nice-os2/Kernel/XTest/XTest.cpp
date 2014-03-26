#define DEBUG_VERSION
#include "Nice-os2.cpp"

// ─── Приложение ───

VOID XTest( HAB Application )
{

 // Узнаем высоту заголовка и картинки.
 INT TitleBar_height = WinQuerySysValue( QueryDesktopWindow(), SV_CYMINMAXBUTTON );

 Log( TitleBar_height );


 /*
 // Узнаем содержимое Clipboard.
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
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ...
  }
 WinEndEnumWindows( Enumeration );
 */

 // Возврат.
 return;
}

INT main( INT argc, CHAR *argv[] )
{
 // Определяем приложение в системе.
 HAB Application = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Application == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   return 0;
  }

 // Создаем очередь сообщений.
 HMQ Message_queue = WinCreateMsgQueue( Application, 0 );

 // Если очередь создать не удалось - выход.
 if( Message_queue == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   WinTerminate( Application ); return 0;
  }

 /*
 InitKernel( Application, 0, NULLHANDLE );
 SetPreDefinedSettings( SET_ALL_SETTINGS );
 */

 // Выполняем действие.
 DosForceDelete( "_log.txt" );
 Enhancer.Application = Application; XTest( Application );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Application ); return 0;
}
