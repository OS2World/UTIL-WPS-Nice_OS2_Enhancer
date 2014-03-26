// Сообщения для потоков.
#define SM_PRIORITY                   ( WM_USER + 00 )
#define SM_WRITE_SETTINGS             ( WM_USER + 01 )

#define SM_CHECK_REPOSITORY           ( WM_USER + 10 )
#define SM_CHECK_VIO_EXENAME          ( WM_USER + 11 )

#define SM_SC_BEGIN                   ( WM_USER + 20 )
#define SM_SC_DRAG                    ( WM_USER + 21 )
#define SM_SC_END                     ( WM_USER + 22 )
#define SM_SC_LINE                    ( WM_USER + 23 )

#define SM_DRAW_FRAME                 ( WM_USER + 30 )
#define SM_DRAW_SYSMENU               ( WM_USER + 31 )
#define SM_DRAW_BUTTONS               ( WM_USER + 32 )
#define SM_PREPARE_CONTROLS           ( WM_USER + 33 )
#define SM_UPDATE_FRAME               ( WM_USER + 34 )
#define SM_UPDATE_ALL_FRAMES          ( WM_USER + 35 )

#define SM_CHECK_FRAME                ( WM_USER + 40 )
#define SM_QUERY_PROPERTIES           ( WM_USER + 41 )
#define SM_CHECK_CONTROLS             ( WM_USER + 42 )

#define SM_CHANGE_ICON                ( WM_USER + 50 )
#define SM_FREE_FILE_ICON             ( WM_USER + 51 )
#define SM_SET_JUMPABLE               ( WM_USER + 52 )
#define SM_CHANGE_VIO_FONT            ( WM_USER + 53 )
#define SM_APPLY_VIO_FONT             ( WM_USER + 54 )
#define SM_SHOW_AND_ARRANGE           ( WM_USER + 55 )

#define SM_CHECK_ALL_COMMANDS         ( WM_USER + 60 )
#define SM_POST_VIO_MENU_ITEM         ( WM_USER + 62 )

#define SM_PERFORM_ACTION             ( WM_USER + 70 )
#define SM_HIDE_WINDOW_AWAY           ( WM_USER + 71 )
#define SM_ACTIVATE_ANYTHING          ( WM_USER + 72 )
#define SM_RETARD_AND_ACTIVATE        ( WM_USER + 73 )

#define SM_DO_SYSTEM_ACTION           ( WM_USER + 80 )
#define SM_SHOW_LAUNCHPAD             ( WM_USER + 81 )
#define SM_SHOW_WINDOW_LIST           ( WM_USER + 82 )
#define SM_HIDE_WINDOW_LIST           ( WM_USER + 83 )
#define SM_HIDE_WARPCENTER            ( WM_USER + 84 )

#define SM_WAIT_MMKBD_EVENTS          ( WM_USER + 90 )

#define SM_SET_NUM_LOCK               ( WM_USER + 100 )
#define SM_RESET_SHIFT_KEYS           ( WM_USER + 101 )
#define SM_SPEEDUP_KEYBOARD           ( WM_USER + 102 )
#define SM_SET_CTRL_ALT_DEL           ( WM_USER + 103 )

#define SM_CLICK                      ( WM_USER + 110 )

#define SM_GO_TO_ROOM                 ( WM_USER + 120 )
#define SM_HOLD_SHELL_WINDOW          ( WM_USER + 121 )
#define SM_CHECK_WINDOW               ( WM_USER + 122 )
#define SM_FILL_DESKTOP               ( WM_USER + 123 )

#define SM_REMOVE_ITEMS               ( WM_USER + 130 )

#define SM_ARRANGE_VIO                ( WM_USER + 140   )
#define SM_ARRANGE_VIO_IN_ROOM        ( WM_USER + 141   )
#define SM_ARRANGE_FC2                ( WM_USER + 142   )
#define SM_ARRANGE_WPS                ( WM_USER + 143   )
#define SM_ARRANGE_WIN_LIST           ( WM_USER + 144   )

#define SM_ARRANGE_FIRST              ( SM_ARRANGE_VIO      )
#define SM_ARRANGE_LAST               ( SM_ARRANGE_WIN_LIST )

#define SM_LOGON_WINDOW               ( WM_USER + 150 )
#define SM_LOGON_VALUES               ( WM_USER + 151 )
#define SM_LOGON_ACTION               ( WM_USER + 152 )
#define SM_LOGON_CHECK                ( WM_USER + 153 )
#define SM_COMPLETE_DIALOG            ( WM_USER + 154 )
#define SM_SEND_YES                   ( WM_USER + 155 )
#define SM_FIND_DIALOG_WINDOWS        ( WM_USER + 156 )

#define SM_BEGIN_VIO_MARKING          ( WM_USER + 160 )
#define SM_END_VIO_MARKING            ( WM_USER + 161 )
#define SM_COPY_VIO_TEXT              ( WM_USER + 162 )
#define SM_PASTE_VIO_TEXT             ( WM_USER + 163 )
#define SM_MB_CLICK                   ( WM_USER + 164 )
#define SM_MB_DOUBLECLICK             ( WM_USER + 165 )
#define SM_RESTORE_CLIPBOARD          ( WM_USER + 166 )

#define SM_FFX_PASTE_DASH             ( WM_USER + 170 )
#define SM_FFX_PASTE_QUOTES_1         ( WM_USER + 171 )
#define SM_FFX_PASTE_QUOTES_2         ( WM_USER + 172 )

#define SM_FFX_PASTE_FIRST            SM_FFX_PASTE_DASH
#define SM_FFX_PASTE_LAST             SM_FFX_PASTE_QUOTES_2

#define SM_MONITOR_VIO                ( WM_USER + 180 )

#define SM_CLOSE_SCREEN_SAVER         ( WM_USER + 190 )

#define SM_WAIT_SOME_TIME             ( WM_USER + 200 )
#define SM_WAITING_COMPLETE           ( WM_USER + 201 )
#define SM_WAIT_STARTING_PROCESS      ( WM_USER + 202 )
#define SM_STARTING_PROCESS_APPEARED  ( WM_USER + 203 )
#define SM_WAIT_EXISTING_PROCESS      ( WM_USER + 204 )
#define SM_LOGON_PROCESS_STOPPED      ( WM_USER + 205 )
#define SM_ESCORT_LOGON               ( WM_USER + 206 )
