#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSERRORS

#include <OS2.h>
#include <StdLib.h>
#include <Limits.h>
#include <Math.h>

// Процессор.
#define I386_ARCHITECTURE
#pragma pack(4)

// Названия данных.
#define CONST   const
#define FLOAT   float
#define DOUBLE  double
#define POINT   POINTL
#define PPOINT  PPOINTL
#define RECT    RECTL
#define PRECT   PRECTL
#define SIZE    SIZEL
#define PSIZE   PSIZEL
#define PPCSZ   PCSZ*

// Повторный вызов.
#define RECURSIVE_CALLING 1

// Русская и английская раскладка.
#define RUSSIAN 866
#define ENGLISH 850

// Ответ на "WM_INITDLG".
#define DLG_NOFOCUS ((MRESULT) TRUE)
// Ответ на "WM_CLOSE".
#define DLG_NOCLOSE ((MRESULT) TRUE)

// Не определены в PMWin.h.
#define KC_VKEY                    KC_VIRTUALKEY
#define DP_MINIICON                4
#define SV_FULLWINDOWDRAG          99
#define SV_ALTTABSWITCHWIN         100
#define SV_VIOMOUSEACTIONS         101
#define SV_ASYNCFOCUSCHANGE        102
#define SV_FOCUSCHANGESENS         103

#define HK_RESERVED_RETURN_VALUE   0

#define MAKERGB( Red, Green, Blue ) ( MAKELONG( MAKESHORT( Blue, Green ), MAKESHORT( Red, 0 ) ) )
#define REDFROMRGB( Color )         ( CHAR3FROMMP( Color ) )
#define GREENFROMRGB( Color )       ( CHAR2FROMMP( Color ) )
#define BLUEFROMRGB( Color )        ( CHAR1FROMMP( Color ) )

#undef RGB
#undef COLOR

#ifndef RGB_WHITE
   #define RGB_WHITE                   ( MAKERGB( 255, 255, 255 ) )
#endif
#ifndef RGB_PALEGRAY
   #define RGB_PALEGRAY                ( MAKERGB( 204, 204, 204 ) )
#endif
#ifndef RGB_DARKGRAY
   #define RGB_DARKGRAY                ( MAKERGB( 128, 128, 128 ) )
#endif
#ifndef RGB_DARKRED
   #define RGB_DARKRED                 ( MAKERGB( 128,   0,   0 ) )
#endif
#ifndef RGB_DARKGREEN
   #define RGB_DARKGREEN               ( MAKERGB(   0, 128,   0 ) )
#endif
#ifndef RGB_DARKBLUE
   #define RGB_DARKBLUE                ( MAKERGB(   0,   0,  128) )
#endif

#define PP_NOTEBOOKBACKGROUNDCOLOR         69
#define PP_NOTEBOOKMAJORTABFOREGROUNDCOLOR 70
#define PP_NOTEBOOKMAJORTABBACKGROUNDCOLOR 71
#define PP_NOTEBOOKMINORTABFOREGROUNDCOLOR 72
#define PP_NOTEBOOKMINORTABBACKGROUNDCOLOR 73

#define SHORT1FROMLONG( Value )     ( SHORT1FROMMP( (MPARAM) Value ) )
#define SHORT2FROMLONG( Value )     ( SHORT2FROMMP( (MPARAM) Value ) )

#define HK_PREACCEL 17

#define OPEN_DEFAULT        0
#define SHOW_EXISTING       1

#define SM_RESTORE      32766
#define SM_MOVE         32769
#define SM_SIZE         32768
#define SM_MINIMIZE     32770
#define SM_MAXIMIZE     32771
#define SM_HIDE         32810
#define SM_CLOSE        32772
#define SM_WINDOW_LIST  32785

#define SM_VIO_HELP     150
#define SM_VIO_FONT     153
#define SM_VIO_SCROLL   155
#define SM_VIO_MARK     156
#define SM_VIO_COPY     157
#define SM_COPY_ALL     158
#define SM_VIO_PASTE    159
#define SM_VIO_MOUSE    163

#define INCLUDE_SUBMENUS 1

#define FDLG_OK_BUTTON        1
#define FDLG_CANCEL_BUTTON    2
#define FDLG_ENTRY_FIELD    258

#define MSGBOX_OK_BUTTON        1
#define MSGBOX_TITLE_TEXT     400
#define MSGBOX_MESSAGE_TEXT   200

typedef struct _SYSCLR_ENTRY
 {
  LONG index;
  LONG color;
 }
SYSCLR_ENTRY;

typedef struct _SYSVAL_ENTRY
 {
  LONG index;
  LONG value;
 }
SYSVAL_ENTRY;

// Не определены в PMStdDlg.h.
#ifndef CSM_QUERYVALUE
   #define CSM_QUERYRANGE           0x053D
   #define CSM_SETRANGE             0x053E
   #define CSM_QUERYVALUE           0x053F
   #define CSM_SETVALUE             0x0540
   #define CSM_QUERYRADIUS          0x0541
   #define CSM_SETINCREMENT         0x0542
   #define CSM_QUERYINCREMENT       0x0543
   #define CSM_SETBITMAPDATA        0x0544

   #define CSN_SETFOCUS             0x0548
   #define CSN_CHANGED              0x0549
   #define CSN_TRACKING             0x054A
   #define CSN_QUERYBACKGROUNDCOLOR 0x054B

   #define CSS_NOBUTTON             0x0001
   #define CSS_NOTEXT               0x0002
   #define CSS_NONUMBER             0x0004
   #define CSS_POINTSELECT          0x0008
   #define CSS_360                  0x0010
   #define CSS_MIDPOINT             0x0020
   #define CSS_PROPORTIONALTICKS    0x0040
   #define CSS_NOTICKS              0x0080
   #define CSS_CIRCULARVALUE        0x0100
#endif

// Не определены в Bsedos.h.
#define NO_ERROR 0

#define STD_IN        0
#define STD_OUT       1
#define STD_ERR       2

#define PAG_ALLOCATE         ( PAG_COMMIT | PAG_READ | PAG_WRITE )
#define QSV_NUMPROCESSORS    26

#define PRTYD_NORMAL         0
#define PRTYD_QUICK          ( PRTYD_MAXIMUM / 2 )

#define FILE_COMMON_ATTRIBUTES ( FILE_NORMAL | FILE_ARCHIVED )
#define FILE_ALL_ATTRIBUTES    ( FILE_NORMAL | FILE_ARCHIVED | FILE_READONLY | FILE_SYSTEM | FILE_HIDDEN | FILE_DIRECTORY )
#define FILE_PIPE_ATTRIBUTES   FILE_NORMAL

#define DEA_GET_ATTRS ((ULONG) -1)

#define SUPPRESS_POPUPS ( 0x1 | 0x2 )

#define BEGIN_LIBPATH 1
#define END_LIBPATH   2

APIRET APIENTRY DosSuppressPopUps ( ULONG Flags, ULONG Drive );
APIRET APIENTRY DosDumpProcess ( ULONG Action, ULONG Drive, PID Pid );
APIRET APIENTRY DosReplaceModule ( PSZ OldModule, PSZ NewModule, PSZ BackModule );
APIRET APIENTRY DosVerifyPidTid ( ULONG Pid, ULONG Tid );
APIRET APIENTRY DosSetExtLIBPATH( PSZ pszExtLIBPATH, ULONG flags );
APIRET APIENTRY DosQueryExtLIBPATH( PSZ pszExtLIBPATH, ULONG flags );

// Длина строки для имени файла. Меньше 256 задавать нежелательно.
#define SIZE_OF_PATH         1024
// Длина строки для имени окна. Менять нежелательно.
#define SIZE_OF_NAME         25
// Длина строки для заголовка окна.
#define SIZE_OF_TITLE        MAXNAMEL
// Длина строки для строки списка.
#define SIZE_OF_ITEM_TEXT    255
// Длина строки для поля ввода в окне диалога.
#define SIZE_OF_DIALOG_FIELD 50
// Длина названия настройки приложения.
#define SIZE_OF_SETTING_NAME 25
// Длина строки для общения с другими приложениями.
#define SIZE_OF_PIPE_COMMAND 25

// Комнаты. Эти значения записываются в INI, менять их нежелательно.
#define NORTHERN_ROOM   8
#define SOUTHERN_ROOM   2
#define WESTERN_ROOM    4
#define EASTERN_ROOM    6
#define SHELL_ROOM      5

#define CURRENT_ROOM    1
#define NO_ROOM         0

// Упрощенный список видимых приложений, который может быть получен из списка окон.
typedef struct _VISIBLEPROCESS
 {
  // Приложение и окно.
  PID Process_ID;
  HWND Frame_window;

  LONG Program_type;
  CHAR Title[ SIZE_OF_TITLE ];

  // Приоритет для него.
  LONG Priority_class;
  LONG Priority_delta;
 }
VISIBLEPROCESS; typedef VISIBLEPROCESS* PVISIBLEPROCESS;

// Размер списка видимых приложений.
#define SIZE_OF_VISPROCLIST 500

