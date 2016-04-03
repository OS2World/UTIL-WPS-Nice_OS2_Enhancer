// Постоянные величины.
#include "..\\Shared\\General.h"
#pragma pack(4)

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

// Расположение окон.
#include "..\\Shared\\WindowTree.h"
#include "..\\Shared\\WindowTree\\WindowTree_code.cpp"
#include "..\\Shared\\WindowTree.cpp"

#include "..\\Shared\\Layout.h"
#include "..\\Shared\\Layout\\Layout_data.cpp"
#include "..\\Shared\\Layout\\Layout_list.cpp"
#include "..\\Shared\\Layout\\Layout_code.cpp"
#include "..\\Shared\\Layout.cpp"

// Свойства окружения.
#include "..\\Shared\\SysState.h"
#pragma pack(4)

// Клавиши.
#include "..\\Shared\\Scan_codes.h"

// Переменные среды.
#define INCLUDED_BY_SHELL

#include "..\\Shared\\Environment\\Environment_data.cpp"
#include "..\\Shared\\Environment\\Environment_code.cpp"
#include "..\\Shared\\Environment.cpp"

#include "..\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\Shared\\EnhancerProperties.cpp"

// Окна и поля ввода.
#include "..\\Shared\\Repository.h"
#include "..\\Shared\\Repository\\Repository_data.cpp"
#include "..\\Shared\\Repository\\Repository_base.cpp"
#include "..\\Shared\\Repository\\Repository_code.cpp"
#include "..\\Shared\\Repository.cpp"

// Поиск окон.
#include "..\\Shared\\Searcher.h"
#include "..\\Shared\\Searcher\\Searcher_code.cpp"
#include "..\\Shared\\Searcher.cpp"

// Список окон.
#include "..\\Shared\\WindowList\\WindowList_code.cpp"
#include "..\\Shared\\WindowList.cpp"

// Составляющие приложения.
#include "..\\Shared\\Settings.h"

#include "Core\\HelpPages\\HelpPages_code.cpp"
#include "Core\\HelpPages.cpp"

#include "Core\\WindowList\\WindowList_code.cpp"
#include "Core\\WindowList.cpp"

// Сообщения для окна рабочей области расширителя.
#define SM_SET_FRAME_ICON              ( WM_USER +   1 )
#define SM_ADD_SWITCH_ENTRY            ( WM_USER +   2 )
#define SM_CREATE_LAYOUT               ( WM_USER +   3 )
#define SM_APPLY_LAYOUT                ( WM_USER +   4 )

#define SM_INITDLG                     ( WM_USER +   5 )

#define SM_READ_LIST                   ( WM_USER +  10 )
#define SM_UPDATE_LIST                 ( WM_USER +  11 )

#define SM_SHOW_SETTINGS               ( WM_USER +  20 )
#define SM_CHECK_OTHER_SETTINGS        ( WM_USER +  21 )
#define SM_SET_PRESENTATION_PARAMETERS ( WM_USER +  22 )
#define SM_RECOGNIZE_THEME             ( WM_USER +  23 )

#define SM_RECOGNIZE_SELECTION         ( WM_USER +  30 )
#define SM_RECOGNIZE_L2_SELECTION      ( WM_USER +  31 )

// Внешние сообщения.
#include "..\\Shared\\Messages4Daemon.h"

// Список страниц с настройками в окне закладок.
typedef VOID ( PAGEPROC_CREATEPAGE     ) ( VOID );
typedef VOID ( PAGEPROC_SETDEFSETTINGS ) ( LONG );
typedef VOID ( PAGEPROC_READSETTINGS   ) ( HINI );

typedef struct _PAGE
 {
  // Длина структуры.
  ULONG cb;

  // Страница в наборе закладок.
  HWND Window; BYTE Present;
  // Вид закладки и надпись на ней.
  LONG Style;
  CHAR Name[ SIZE_OF_NAME ];
  CHAR Icon_name[ SIZE_OF_NAME ];

  // Настройки, показываемые на странице.
  // Используется для добавления только требуемых страниц и вызова руководства.
  ULONG Settings_to_show;

  // Расположение полей ввода.
  LTWALL Layout;

  // Указатели на вызовы.
  PAGEPROC_CREATEPAGE* CreatePage;
  PAGEPROC_SETDEFSETTINGS* SetDefSettings;
  PAGEPROC_SETDEFSETTINGS* SetDefSettings_Ext1;
  PAGEPROC_SETDEFSETTINGS* SetDefSettings_Ext2;
  PAGEPROC_SETDEFSETTINGS* SetDefSettings_Ext3;
  PAGEPROC_READSETTINGS* ReadSettings;
  PAGEPROC_READSETTINGS* ReadSettings_Ext1;
  PAGEPROC_READSETTINGS* ReadSettings_Ext2;
  PAGEPROC_READSETTINGS* ReadSettings_Ext3;
 }
PAGE; typedef PAGE* PPAGE;

#define PAGELIST_LENGTH 48

typedef struct _PAGE_POINTERS
 {
  // Уже подключенные страницы.
  PPAGE Log;
  PPAGE Scrolling_settings;
  PPAGE Scrolling_exceptions;
  PPAGE Drawing_themes;
  PPAGE Drawing_restrictions;
  PPAGE Drawing_titlebars;
  PPAGE Drawing_buttons;
  PPAGE Drawing_exceptions;
  PPAGE Rooms_colors;
  PPAGE Rooms_allocations;
  PPAGE Rooms_exceptions;
  PPAGE Keyboard_keys;
  PPAGE Keyboard_actions;
  PPAGE Keyboard_ffx;
  PPAGE Keyboard_break;
  PPAGE Keyboard_various;
  PPAGE Keyboard_VIO;
  PPAGE Keyboard_speed;
  PPAGE Keyboard_echo;
  PPAGE Mouse_buttons;
  PPAGE Mouse_VIO;
  PPAGE Mouse_clipboard;
  PPAGE Mouse_focus;
  PPAGE Mouse_menus;
  PPAGE Placement_settings;
  PPAGE Dialogs_logon;
  PPAGE Dialogs_fields;
  PPAGE Dialogs_boxes;
  PPAGE Priority_variable;
  PPAGE Priority_sedative;
  PPAGE WinList_settings;
  PPAGE VIOWindows_fonts;
  PPAGE VIOWindows_SSH_prompts;
  PPAGE SysPatches_settings;
  PPAGE SysPatches_background;

  // Страницы "на будущее".
  PPAGE Page_pointer_37;
  PPAGE Page_pointer_38;
  PPAGE Page_pointer_39;
  PPAGE Page_pointer_40;
  PPAGE Page_pointer_41;
  PPAGE Page_pointer_42;
  PPAGE Page_pointer_43;
  PPAGE Page_pointer_44;
  PPAGE Page_pointer_45;
  PPAGE Page_pointer_46;
  PPAGE Page_pointer_47;

  PPAGE Page_pointer_at_PageListLength;
 }
PAGE_POINTERS;

// Окно определителя.
typedef struct _DETECTOR_DIALOG
 {
  // Вызывано окно для составления списка исключений.
  BYTE Detector_is_running;

  // Переменные для окна (задаются страницами).
  HWND Customer_window;
  BYTE Include_shell_windows;
  BYTE Include_VIO_windows_only;

  PCHAR Window_name_1; PCHAR Window_name_2; PCHAR Window_name_3; PCHAR Window_name_4;
  PCHAR Window_name_5; PCHAR Window_name_6; PCHAR Window_name_7; PCHAR Window_name_8;

  PINT Key_code;

  BYTE Scan_dialog;
  BYTE Scan_logon_dialog;
  BYTE Scan_fields_in_dialog;
  BYTE Scan_message_box_dialog;
 }
DETECTOR_DIALOG;

// Приложение.
typedef struct _ENHANCER
 {
  // Приложение.
  HAB Application;

  BYTE Nice_is_minimized;
  HWND Remote_window;

  // Страна, в которой работает приложение.
  ULONG Code_page;

  // Какие настройки надо показать.
  ULONG Settings_to_show;

  // Запущенный загрузчиком расширитель завершился успешно.
  BYTE Enhancer_is_terminated_normally;

  // Окно рамки.
  HWND Frame_window;
  // Окно рабочей области.
  HWND Client_window; LTWALL Client_layout;

  // Окно с закладками.
  HWND Notebook_window;
  // Страницы в наборе закладок.
  PAGE PageList[ PAGELIST_LENGTH ]; PAGE_POINTERS Pages;

  // Окно определителя.
  DETECTOR_DIALOG Detector_dialog;
 }
ENHANCER; ENHANCER Enhancer;

// Загрузчик.
#include "Core\\Connector\\Connector_code.cpp"
#include "Core\\Connector.cpp"

// Строки приложения.
#include "Resources\\StrConst.h"

// Работа с клавиатурой и мышью.
#include "..\\Shared\\KbdMouse.h"
#include "..\\Shared\\KbdMouse\\KbdMouse_code.cpp"
#include "..\\Shared\\KbdMouse.cpp"

// Страницы настроек.
#include "Core\\PageList\\PageList_code.cpp"
#include "Core\\PageList.cpp"

#include "Pages\\Controls.h"

#include "Core\\TabWindow\\TabWindow_code.cpp"
#include "Core\\TabWindow.cpp"

#include "Core\\TabPage\\TabPage_code.cpp"
#include "Core\\TabPage.cpp"

#include "Pages\\Detector\\Detector.h"
#include "Pages\\Detector\\Detector_data.cpp"
#include "Pages\\Detector\\Detector_base.cpp"
#include "Pages\\Detector\\Detector_form.cpp"
#include "Pages\\Detector\\Detector_code.cpp"
#include "Pages\\Detector.cpp"

#include "..\\Kernel\\Modules\\Scroller\\Scroller_data.cpp"
#include "..\\Kernel\\Modules\\Scroller\\Scroller_init.cpp"
#include "Pages\\Scrolling\\Scrolling_settings_data.cpp"
#include "Pages\\Scrolling\\Scrolling_settings_page.cpp"
#include "Pages\\Scrolling\\Scrolling_settings_open.cpp"
#include "Pages\\Scrolling\\Scrolling_exceptions_data.cpp"
#include "Pages\\Scrolling\\Scrolling_exceptions_page.cpp"
#include "Pages\\Scrolling\\Scrolling_exceptions_open.cpp"
#include "Pages\\Scrolling.cpp"

#include "..\\Kernel\\Modules\\Painter\\Painter_data.cpp"
#include "..\\Kernel\\Modules\\Painter\\Painter_init.cpp"
#include "..\\Kernel\\Modules\\PainterAndRooms.cpp"

#include "Core\\Themes.h"
#include "Core\\Themes\\Themes_code.cpp"
#include "Core\\Themes.cpp"

#include "Pages\\Drawing\\Drawing_themes_data.cpp"
#include "Pages\\Drawing\\Drawing_themes_page.cpp"
#include "Pages\\Drawing\\Drawing_themes_open.cpp"
#include "Pages\\Drawing\\Drawing_restrictions_data.cpp"
#include "Pages\\Drawing\\Drawing_restrictions_page.cpp"
#include "Pages\\Drawing\\Drawing_restrictions_open.cpp"
#include "Pages\\Drawing\\Drawing_titlebars_data.cpp"
#include "Pages\\Drawing\\Drawing_titlebars_page.cpp"
#include "Pages\\Drawing\\Drawing_titlebars_open.cpp"
#include "Pages\\Drawing\\Drawing_buttons_data.cpp"
#include "Pages\\Drawing\\Drawing_buttons_page.cpp"
#include "Pages\\Drawing\\Drawing_buttons_open.cpp"
#include "Pages\\Drawing\\Drawing_exceptions_data.cpp"
#include "Pages\\Drawing\\Drawing_exceptions_page.cpp"
#include "Pages\\Drawing\\Drawing_exceptions_open.cpp"
#include "Pages\\Drawing.cpp"

#include "..\\Kernel\\Modules\\Rooms\\Rooms_data.cpp"
#include "..\\Kernel\\Modules\\Rooms\\Rooms_init.cpp"
#include "Pages\\Rooms\\Rooms_colors_data.cpp"
#include "Pages\\Rooms\\Rooms_colors_page.cpp"
#include "Pages\\Rooms\\Rooms_colors_open.cpp"
#include "Pages\\Rooms\\Rooms_allocations_data.cpp"
#include "Pages\\Rooms\\Rooms_allocations_page.cpp"
#include "Pages\\Rooms\\Rooms_allocations_open.cpp"
#include "Pages\\Rooms\\Rooms_exceptions_data.cpp"
#include "Pages\\Rooms\\Rooms_exceptions_page.cpp"
#include "Pages\\Rooms\\Rooms_exceptions_open.cpp"
#include "Pages\\Rooms.cpp"

#include "..\\Kernel\\Modules\\VIOFontManager\\VIOFontManager_data.cpp"
#include "..\\Kernel\\Modules\\VIOFontManager\\VIOFontManager_init.cpp"
#include "Pages\\VIOWindows\\VIOWindows_fonts_data.cpp"
#include "Pages\\VIOWindows\\VIOWindows_fonts_page.cpp"
#include "Pages\\VIOWindows\\VIOWindows_fonts_open.cpp"
#include "..\\Kernel\\Modules\\VIOMenuManager\\VIOMenuManager_data.cpp"
#include "..\\Kernel\\Modules\\VIOMenuManager\\VIOMenuManager_init.cpp"
#include "Pages\\VIOWindows\\VIOWindows_SSH_prompts_data.cpp"
#include "Pages\\VIOWindows\\VIOWindows_SSH_prompts_page.cpp"
#include "Pages\\VIOWindows\\VIOWindows_SSH_prompts_open.cpp"
#include "Pages\\VIOWindows.cpp"

#include "..\\Kernel\\Modules\\Definer\\Definer_data.cpp"
#include "..\\Kernel\\Modules\\Definer\\Definer_init.cpp"
#include "Pages\\Keyboard\\Keyboard_keys_data.cpp"
#include "Pages\\Keyboard\\Keyboard_keys_page.cpp"
#include "Pages\\Keyboard\\Keyboard_keys_open.cpp"
#include "Pages\\Keyboard\\Keyboard_actions_data.cpp"
#include "Pages\\Keyboard\\Keyboard_actions_page.cpp"
#include "Pages\\Keyboard\\Keyboard_actions_open.cpp"
#include "..\\Kernel\\Modules\\KeyMapper\\KeyMapper_data.cpp"
#include "..\\Kernel\\Modules\\KeyMapper\\KeyMapper_init.cpp"
#include "..\\Kernel\\Modules\\Controller\\Controller_data.cpp"
#include "..\\Kernel\\Modules\\Controller\\Controller_init.cpp"
#include "..\\Kernel\\Modules\\Clipper.h"
#include "..\\Kernel\\Modules\\Clipper\\Clipper_data.cpp"
#include "..\\Kernel\\Modules\\Clipper\\Clipper_init.cpp"
#include "Pages\\Keyboard\\Keyboard_ffx_data.cpp"
#include "Pages\\Keyboard\\Keyboard_ffx_page.cpp"
#include "Pages\\Keyboard\\Keyboard_ffx_open.cpp"
#include "Pages\\Keyboard\\Keyboard_break_data.cpp"
#include "Pages\\Keyboard\\Keyboard_break_page.cpp"
#include "Pages\\Keyboard\\Keyboard_break_open.cpp"
#include "Pages\\Keyboard\\Keyboard_various_data.cpp"
#include "Pages\\Keyboard\\Keyboard_various_page.cpp"
#include "Pages\\Keyboard\\Keyboard_various_open.cpp"
#include "Pages\\Keyboard\\Keyboard_VIO_data.cpp"
#include "Pages\\Keyboard\\Keyboard_VIO_page.cpp"
#include "Pages\\Keyboard\\Keyboard_VIO_open.cpp"
#include "..\\Kernel\\Modules\\Clicker\\Clicker_data.cpp"
#include "..\\Kernel\\Modules\\Clicker\\Clicker_init.cpp"
#include "Pages\\Keyboard\\Keyboard_speed_data.cpp"
#include "Pages\\Keyboard\\Keyboard_speed_page.cpp"
#include "Pages\\Keyboard\\Keyboard_speed_open.cpp"
#include "Pages\\Keyboard\\Keyboard_echo_data.cpp"
#include "Pages\\Keyboard\\Keyboard_echo_page.cpp"
#include "Pages\\Keyboard\\Keyboard_echo_open.cpp"
#include "Pages\\Keyboard.cpp"

#include "..\\Kernel\\Modules\\MouseMapper\\MouseMapper_data.cpp"
#include "..\\Kernel\\Modules\\MouseMapper\\MouseMapper_init.cpp"
#include "Pages\\Mouse\\Mouse_buttons_data.cpp"
#include "Pages\\Mouse\\Mouse_buttons_page.cpp"
#include "Pages\\Mouse\\Mouse_buttons_open.cpp"
#include "Pages\\Mouse\\Mouse_VIO_data.cpp"
#include "Pages\\Mouse\\Mouse_VIO_page.cpp"
#include "Pages\\Mouse\\Mouse_VIO_open.cpp"
#include "Pages\\Mouse\\Mouse_clipboard_data.cpp"
#include "Pages\\Mouse\\Mouse_clipboard_page.cpp"
#include "Pages\\Mouse\\Mouse_clipboard_open.cpp"
#include "Pages\\Mouse\\Mouse_focus_data.cpp"
#include "Pages\\Mouse\\Mouse_focus_page.cpp"
#include "Pages\\Mouse\\Mouse_focus_open.cpp"
#include "Pages\\Mouse\\Mouse_menus_data.cpp"
#include "Pages\\Mouse\\Mouse_menus_page.cpp"
#include "Pages\\Mouse\\Mouse_menus_open.cpp"
#include "Pages\\Mouse.cpp"

#include "..\\Kernel\\Modules\\Arranger\\Arranger_data.cpp"
#include "..\\Kernel\\Modules\\Arranger\\Arranger_init.cpp"
#include "Pages\\Placement\\Placement_settings_data.cpp"
#include "Pages\\Placement\\Placement_settings_page.cpp"
#include "Pages\\Placement\\Placement_settings_open.cpp"
#include "Pages\\Placement.cpp"

#include "..\\Shared\\DlgBoxes.h"
#include "..\\Kernel\\Modules\\Applier\\Applier_data.cpp"
#include "..\\Kernel\\Modules\\Applier\\Applier_init.cpp"
#include "..\\Kernel\\Modules\\Applier\\Applier_list.cpp"
#include "..\\Kernel\\Modules\\ApplierList.cpp"
#include "Pages\\Dialogs\\Dialogs_logon_data.cpp"
#include "Pages\\Dialogs\\Dialogs_logon_page.cpp"
#include "Pages\\Dialogs\\Dialogs_logon_open.cpp"
#include "Pages\\Dialogs\\Dialogs_fields_data.cpp"
#include "Pages\\Dialogs\\Dialogs_fields_page.cpp"
#include "Pages\\Dialogs\\Dialogs_fields_open.cpp"
#include "Pages\\Dialogs\\Dialogs_boxes_data.cpp"
#include "Pages\\Dialogs\\Dialogs_boxes_page.cpp"
#include "Pages\\Dialogs\\Dialogs_boxes_open.cpp"
#include "Pages\\Dialogs.cpp"

#include "..\\Kernel\\Modules\\PriorityManager\\PriorityManager_data.cpp"
#include "..\\Kernel\\Modules\\PriorityManager\\PriorityManager_init.cpp"

#include "Pages\\Priority\\Priority_variable_data.cpp"
#include "Pages\\Priority\\Priority_variable_page.cpp"
#include "Pages\\Priority\\Priority_variable_open.cpp"
#include "Pages\\Priority\\Priority_sedative_data.cpp"
#include "Pages\\Priority\\Priority_sedative_page.cpp"
#include "Pages\\Priority\\Priority_sedative_open.cpp"
#include "Pages\\Priority.cpp"

#include "..\\Kernel\\Modules\\Remover\\Remover_data.cpp"
#include "..\\Kernel\\Modules\\Remover\\Remover_init.cpp"
#include "Pages\\WinList\\WinList_settings_data.cpp"
#include "Pages\\WinList\\WinList_settings_page.cpp"
#include "Pages\\WinList\\WinList_settings_open.cpp"
#include "Pages\\WinList.cpp"

#include "..\\Kernel\\Modules\\Patcher\\Patcher_data.cpp"
#include "..\\Kernel\\Modules\\Patcher\\Patcher_init.cpp"
#include "Pages\\SysPatches\\SysPatches_settings_data.cpp"
#include "Pages\\SysPatches\\SysPatches_settings_page.cpp"
#include "Pages\\SysPatches\\SysPatches_settings_open.cpp"
#include "..\\Shared\\Images\\Images_code.cpp"
#include "..\\Shared\\Images.cpp"
#include "Pages\\SysPatches\\SysPatches_background_data.cpp"
#include "Pages\\SysPatches\\SysPatches_background_page.cpp"
#include "Pages\\SysPatches\\SysPatches_background_open.cpp"
#include "Pages\\SysPatches.cpp"

// Проверка настроек PM и запись отчета в окно "Log".
#include "Pages\\Log\\Log_data.cpp"
#include "Pages\\Log\\Log_open.cpp"
#include "Pages\\Log\\Log_link.cpp"
#include "Pages\\Log.cpp"

#include "Core\\SysCheck\\SysCheck_code.cpp"
#include "Core\\SysCheck.cpp"

// Главное окно приложения.
#include "Core\\MainWindow\\MainWindow_code.cpp"
#include "Core\\MainWindow.cpp"

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

 // Запускаем составляющие приложения.
 StdLib_Start();
 Strings_Start();
 Files_Start();

 Environment_Start();
 EnhancerProperties_Start();
 Repository_Start();
 WindowTree_Start();
 Layout_Start();
 WindowList_Start();

 TabPage_Start();
 TabWindow_Start();
 Themes_Start();
 Detector_Start();
 HelpPages_Start();
 Shell_WindowList_Start();

 Connector_Start();

 // Узнаем страну, в которой работает приложение.
 if( argc >= 3 && stristr( "english", argv[ 2 ] ) ) Enhancer.Code_page = ENGLISH;
 else Enhancer.Code_page = QuerySystemCodePage();

 // Узнаем, как должно должно выглядеть окно приложения.
 Enhancer.Settings_to_show = SET_ALL_SETTINGS;

 if( argc >= 2 )
  {
   if( stristr( "icon", argv[ 1 ] ) || stristr( "min", argv[ 1 ] ) )
    {
     Enhancer.Nice_is_minimized = 1;
    }

   if( stristr( "center", argv[ 1 ] ) )
    {
     if( stristr( "_scrolling", argv[ 1 ] ) )        Enhancer.Settings_to_show = SET_SCROLLING;
     if( stristr( "_drawing", argv[ 1 ] ) )          Enhancer.Settings_to_show = SET_DRAWING;
     if( stristr( "_rooms", argv[ 1 ] ) )            Enhancer.Settings_to_show = SET_ROOMS;
     if( stristr( "_keyboard", argv[ 1 ] ) )         Enhancer.Settings_to_show = SET_KEYBOARD;
     if( stristr( "_mouse", argv[ 1 ] ) )            Enhancer.Settings_to_show = SET_MOUSE;
     if( stristr( "_windowplacement", argv[ 1 ] ) )  Enhancer.Settings_to_show = SET_PLACEMENT;
     if( stristr( "_dialogboxes", argv[ 1 ] ) )      Enhancer.Settings_to_show = SET_DIALOG_BOXES;
     if( stristr( "_priority", argv[ 1 ] ) )         Enhancer.Settings_to_show = SET_PRIORITY;
     if( stristr( "_winlist", argv[ 1 ] ) )          Enhancer.Settings_to_show = SET_WINLIST;
     if( stristr( "_vio", argv[ 1 ] ) )              Enhancer.Settings_to_show = SET_VIO_WINDOWS;
     if( stristr( "_syspatches", argv[ 1 ] ) )       Enhancer.Settings_to_show = SET_SYS_PATCHES;
    }
  }

 // Если окно приложения уже есть - запоминаем его.
 {
  CHAR Enhancer_title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Enhancer_title );

  {
   // Перебираем окна в окне рабочего стола.
   HENUM Enumeration = WinBeginEnumWindows( WinQueryDesktopWindow( Enhancer.Application, NULLHANDLE ) ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Если окно создано расширителем - запоминаем его.
     if( IsFrameWindow( Window ) && WindowIsCreatedBy( APP_NICE, Window ) )
      {
       CHAR Window_name[ SIZE_OF_NAME ] = "";
       WinQueryClassName( WinWindowFromID( Window, FID_CLIENT ), SIZE_OF_NAME, Window_name );

       if( strc( Window_name, "NiceOS2WndClass!E" ) )
        {
         Enhancer.Remote_window = Window;
         break;
        }
      }
    }
   WinEndEnumWindows( Enumeration );
  }
 }

 // Если надо вызвать настройки, но не задана страница для них - пробуем открыть окно WPS.
 if( Enhancer.Remote_window ) if( Enhancer.Settings_to_show == SET_ALL_SETTINGS )
  {
   HOBJECT Control_center = QueryWPSObject( "<WP_NICE_OS2>" );
   if( Control_center != NULLHANDLE ) WinOpenObject( Control_center, OPEN_DEFAULT, SHOW_EXISTING );

   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // Если окна расширителя нет - выход.
 if( !Enhancer.Remote_window )
  {
   CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );

   if( QuerySystemCodePage() == RUSSIAN )
    WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Launch_Enhancer_first, Title, NULLHANDLE, NULLHANDLE );
   else
    WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Launch_Enhancer_first, Title, NULLHANDLE, NULLHANDLE );

   WinTerminate( Enhancer.Application );
   DosExit( EXIT_PROCESS, 0 );
  }

 // Создаем окно рабочей области.
 CHAR Class_name[] = "NiceOS2WndClass";
 WinRegisterClass( Enhancer.Application, Class_name, (PFNWP) Enhancer_MainWindowProc, 0, 0 );

 // Создаем окно рамки.
 ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_SIZEBORDER | FCF_NOBYTEALIGN;
 Enhancer.Frame_window = WinCreateStdWindow( HWND_DESKTOP, CS_FRAME, &Creation_flags, Class_name, "", 0, NULLHANDLE, 0, &Enhancer.Client_window );
 WinShowWindow( Enhancer.Frame_window, 0 );

 // Если надо показывать настройки:
 if( Enhancer.Remote_window )
  {
   // Устанавливаем указатели в списке страниц расширителя.
   PAGE_POINTERS Page_pointers =
    {
     &Enhancer.PageList[  0 ],
     &Enhancer.PageList[  1 ],
     &Enhancer.PageList[  2 ],
     &Enhancer.PageList[  3 ],
     &Enhancer.PageList[  4 ],
     &Enhancer.PageList[  5 ],
     &Enhancer.PageList[  6 ],
     &Enhancer.PageList[  7 ],
     &Enhancer.PageList[  8 ],
     &Enhancer.PageList[  9 ],
     &Enhancer.PageList[ 10 ],
     &Enhancer.PageList[ 11 ],
     &Enhancer.PageList[ 12 ],
     &Enhancer.PageList[ 13 ],
     &Enhancer.PageList[ 14 ],
     &Enhancer.PageList[ 15 ],
     &Enhancer.PageList[ 16 ],
     &Enhancer.PageList[ 17 ],
     &Enhancer.PageList[ 18 ],
     &Enhancer.PageList[ 19 ],
     &Enhancer.PageList[ 20 ],
     &Enhancer.PageList[ 21 ],
     &Enhancer.PageList[ 22 ],
     &Enhancer.PageList[ 23 ],
     &Enhancer.PageList[ 24 ],
     &Enhancer.PageList[ 25 ],
     &Enhancer.PageList[ 26 ],
     &Enhancer.PageList[ 27 ],
     &Enhancer.PageList[ 28 ],
     &Enhancer.PageList[ 29 ],
     &Enhancer.PageList[ 30 ],
     &Enhancer.PageList[ 31 ],
     &Enhancer.PageList[ 32 ],
     &Enhancer.PageList[ 33 ],
     &Enhancer.PageList[ 34 ],

     &Enhancer.PageList[ 35 ],
     &Enhancer.PageList[ 36 ],
     &Enhancer.PageList[ 37 ],
     &Enhancer.PageList[ 38 ],

     &Enhancer.PageList[ 39 ]
    };

   memcpy( &Enhancer.Pages, &Page_pointers, sizeof( PAGE_POINTERS ) );

   // Создаем страницы.
   Log_Start();

   Scrolling_Start( Enhancer.Settings_to_show );
   Drawing_Start( Enhancer.Settings_to_show );
   Rooms_Start( Enhancer.Settings_to_show );
   Keyboard_Start( Enhancer.Settings_to_show );
   Mouse_Start( Enhancer.Settings_to_show );
   Placement_Start( Enhancer.Settings_to_show );
   Dialogs_Start( Enhancer.Settings_to_show );
   Priority_Start( Enhancer.Settings_to_show );
   WinList_Start( Enhancer.Settings_to_show );
   VIOWindows_Start( Enhancer.Settings_to_show );
   SysPatches_Start( Enhancer.Settings_to_show );

   Enhancer.Pages.Log->Present = 1;

   for( INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
    {
     PPAGE Page = GetPageListEntry( Page_count );
     if( Page != NULL )
      if( Page->Window == NULLHANDLE )
       {
        if( Enhancer.Settings_to_show == SET_ALL_SETTINGS ||
            Enhancer.Settings_to_show == Page->Settings_to_show ) Page->Present = 1;

        if( Page->Present )
         if( Page->CreatePage )
          {
           Page->CreatePage();

           if( Page->Window )
            {
             WinSetOwner( Page->Window, NULLHANDLE );
             WinSetParent( Page->Window, NULLHANDLE, 0 );
             WinShowWindow( Page->Window, 0 );
            }
          }
       }
    }

   SysCheck_Start();
   CheckPMSettingsAndWriteLog();
   if( Enhancer.Settings_to_show == SET_PRIORITY ) CheckPrioritySettingsAndWriteLog();
   if( !LogIsEmpty() ) AddCompletiveLogMessage();
   if( LogIsEmpty() ) Enhancer.Pages.Log->Present = 0;

   // Открываем файл настроек.
   CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
   HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

   // Если его не удалось открыть - возврат.
   if( !Ini_file ) return 0;

   // Читаем настройки. При этом следим за тем, чтобы ни один метод не вызывался дважды.
   typedef struct _PAGEPROC_POINTER
    {
     PAGEPROC_SETDEFSETTINGS* SetDefSettings;
     PAGEPROC_READSETTINGS* ReadSettings;
    }
   PAGEPROC_POINTER;

   PAGEPROC_POINTER Used_procedures[ PAGELIST_LENGTH ]; bzero( Used_procedures, sizeof( Used_procedures ) );

   for( Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
    {
     PPAGE Page = GetPageListEntry( Page_count );
     if( Page != NULL )
      if( Page->Present && Page->Window )
       {
        if( Page->SetDefSettings && Page->ReadSettings )
         {
          BYTE Already_used = 0;

          for( INT Used_procedures_count = 0; Used_procedures_count < PAGELIST_LENGTH; Used_procedures_count ++ )
           {
            if( Used_procedures[ Used_procedures_count ].SetDefSettings == Page->SetDefSettings ||
                Used_procedures[ Used_procedures_count ].ReadSettings   == Page->ReadSettings )
             {
              Already_used = 1;
              break;
             }
           }

          if( !Already_used )
           {
            Page->SetDefSettings( Enhancer.Settings_to_show );
            Page->ReadSettings( Ini_file );

            Used_procedures[ Page_count ].SetDefSettings = Page->SetDefSettings;
            Used_procedures[ Page_count ].ReadSettings   = Page->ReadSettings;

            {
             if( Page->SetDefSettings_Ext1 != NULL ) Page->SetDefSettings_Ext1( Enhancer.Settings_to_show );
             if( Page->SetDefSettings_Ext2 != NULL ) Page->SetDefSettings_Ext2( Enhancer.Settings_to_show );
             if( Page->SetDefSettings_Ext3 != NULL ) Page->SetDefSettings_Ext3( Enhancer.Settings_to_show );

             if( Page->ReadSettings_Ext1 != NULL ) Page->ReadSettings_Ext1( Ini_file );
             if( Page->ReadSettings_Ext2 != NULL ) Page->ReadSettings_Ext2( Ini_file );
             if( Page->ReadSettings_Ext3 != NULL ) Page->ReadSettings_Ext3( Ini_file );
            }
           }
         }
       }
    }

   // Читаем список приложений.
   ReadRepository( Ini_file );

   // Закрываем файл настроек.
   PrfCloseProfile( Ini_file );

   // Отображаем настройки на страницах.
   BroadcastRSMessages();
  }

 // Выбираем сообщения из очереди.
 QMSG Message; bzero( &Message, sizeof( QMSG ) );
 while( WinGetMsg( Enhancer.Application, &Message, 0, 0, 0 ) ) WinDispatchMsg( Enhancer.Application, &Message );

 // Закрываем окна.
 WinDestroyWindow( Enhancer.Client_window );
 WinDestroyWindow( Enhancer.Frame_window );

 // Удаляем файлы отладочной версии.
 DosForceDelete( "_log.txt" ); DosForceDelete( "XTest.exe" );

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Enhancer.Application );
 DosExit( EXIT_PROCESS, 0 );
}
