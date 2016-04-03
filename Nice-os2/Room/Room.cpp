#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

// Названия данных.
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

// Scan-коды клавиш.
#define SC_NUM_8   72
#define SC_NUM_4   75
#define SC_NUM_5   76
#define SC_NUM_6   77
#define SC_NUM_2   80

// Сообщение для окна.
#define WM_MARK          WM_NULL
#define MRK_GO_TO_ROOM   0x00FACE00

// ─── Приложение ───

INT main( INT argc, CHAR *argv[] )
{
 // Узнаем комнату, в которую надо переключиться.
 BYTE Scan_code = 0; SHORT Key = 0;

 if( argc == 2 )
  {
   if( stristr( "north", argv[ 1 ] ) ) { Scan_code = SC_NUM_8; Key = VK_UP;    }
   if( stristr( "west",  argv[ 1 ] ) ) { Scan_code = SC_NUM_4; Key = VK_LEFT;  }
   if( stristr( "east",  argv[ 1 ] ) ) { Scan_code = SC_NUM_6; Key = VK_RIGHT; }
   if( stristr( "south", argv[ 1 ] ) ) { Scan_code = SC_NUM_2; Key = VK_DOWN;  }
   if( stristr( "desk",  argv[ 1 ] ) ) { Scan_code = SC_NUM_5; Key = 0;        }
  }

 // Если комната неизвестна - выход.
 if( Scan_code == 0 ) if( Key == 0 ) return 0;

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

 // Узнаем окно рабочего стола.
 HWND Desktop = WinQueryDesktopWindow( Application, NULLHANDLE );

 // Посылаем ему сообщение WM_MARK.
 WinPostMsg( Desktop, WM_MARK, (MPARAM) MRK_GO_TO_ROOM, (MPARAM) Scan_code );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Application ); return 0;
}
