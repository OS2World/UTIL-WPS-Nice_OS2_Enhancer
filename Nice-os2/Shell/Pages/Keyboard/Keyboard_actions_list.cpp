{
 /* * */

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Заполняем список клавиш.
 {
   // Задаем строки.
   INT Max_strings = MAX_KEYS; PCHAR Strings[ MAX_KEYS ]; INT Count; INT Point = -1;
   for( Count = 0; Count < Max_strings; Count ++ ) DosAllocMem( (PPVOID) &Strings[ Count ], 256, PAG_ALLOCATE );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F11" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + F11" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F12" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + F12" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "PrtScr" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "SysRq (Alt + PrtScr)" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Pause" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Right Alt" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + Right Alt" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Left WinKey" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Right WinKey" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "TaskList" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F1" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F2" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F3" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F4" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F5" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F6" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F7" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F8" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F9" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "F10" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + \\" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + <-" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + [ / ]" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + [ * ]" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + [ - ]" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + [ + ]" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + [  ]" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F1" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F2" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F3" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F4" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F5" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F6" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F7" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F8" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F9" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F10" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F11" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F12" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + A" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + B" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + C" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + D" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + E" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + F" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + G" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + H" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + I" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + J" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + K" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + L" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + M" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + N" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + O" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + P" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + Q" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + R" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + S" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + T" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + U" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + V" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + W" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + X" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + Y" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Shift + WinKey + Z" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Power" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Sleep" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "WakeUp" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Play" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Stop" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Previous track" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Next track" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Volume decrement" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Volume increment" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Mute" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Media" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Terminal" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Calculator" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Browser" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Mail" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Search" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Bookmarks" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Back" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Forward" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Cancel" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Refresh" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "PageLeft" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "PageRight" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 1" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 2" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 3" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 4" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 5" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 6" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 7" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 8" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 9" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 10" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 11" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 12" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 13" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 14" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "UserKey 15" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: ( i )" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Home" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Search" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Mail" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: People" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Bench" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Chat" );
   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "Compaq: Reading" );

   Point ++; if( Point < MAX_KEYS ) strcpy( Strings[ Point ], "" );

   // Передаем строки окну списка.
   {
    HWND List_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Key_list_ID );

    Keyboard_Actions.Settings.Key_list_is_locked = 1; WinShowWindow( List_window, 0 );
    for( Count = 0; Count < Max_strings; Count ++ ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Strings[ Count ] ) );
    Keyboard_Actions.Settings.Key_list_is_locked = 0; WinShowWindow( List_window, 1 );
   }

   // Освобождаем память.
   for( Count = 0; Count < Max_strings; Count ++ ) { DosFreeMem( Strings[ Count ] ); Strings[ Count ] = NULL; }
 }

 // Заполняем список действий.
 {
  // Задаем строки.
  INT Max_strings = MAX_ACTIONS; PCHAR Strings[ MAX_ACTIONS ]; INT Count; INT Point = -1;
  for( Count = 0; Count < Max_strings; Count ++ ) DosAllocMem( (PPVOID) &Strings[ Count ], 256, PAG_ALLOCATE );

  if( Code_page == RUSSIAN )
   {
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Оставить как есть" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Список окон" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Следующее окно" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Предыдущее окно" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Устройства" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Задания на печать" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Принтеры" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Скрытые окна" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Часы (WPS Clock)" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Занятость системы" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Управление питанием" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "eCenter" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "ePager" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "WarpCenter" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "LaunchPad" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SysBar" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "FileBar" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SysTray" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Task Manager" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Сетевые устройства" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Модемная звонилка" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Работа с диском - VIO" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Работа с диском - PM" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Цифровая камера" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Поиск файлов" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Сетевой обозреватель" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Чтение почты" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "IRC-чат" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "ICQ" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Просмотр FTP" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Терминал SSH - VIO" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Терминал SSH - PM" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Удалённый доступ, VNC" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Удалённый доступ, RDP" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Текстовый редактор" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Калькулятор" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Просмотр изображений" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Проигрыватель MP3" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Проигрыватель видео" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Проигрыватель MOD" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "FM радио" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 1" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 2" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 3" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 4" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 5" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 6" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 7" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 8" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 9" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 10" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 11" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 12" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 13" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 14" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Приложение 15" );
   }
  else
   {
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Do not define" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Window List" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Next window" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Previous window" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Drives" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Spooler" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Printers" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Minimized windows" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "WPS Clock" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Pulse" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Battery status" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "eCenter" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "ePager" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "WarpCenter" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "LaunchPad" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SysBar" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "FileBar" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SysTray" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Task Manager" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "NetDrive" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Internet dialer" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "File Manager - VIO" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "File Manager - PM" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Digital Camera" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "File Search" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Web Browser" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Mail Reader" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Internet Chat (IRC)" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "ICQ Pager" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "FTP Browser" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SSH console - VIO" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "SSH console - PM" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Remote Desktop, VNC" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Remote Desktop, RDP" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Text editor" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Calculator" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Image viewer" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "MP3 player" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "MPEG player" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "MOD/S3M player" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "FM Tuner" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 1" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 2" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 3" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 4" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 5" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 6" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 7" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 8" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 9" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 10" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 11" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 12" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 13" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 14" );
    Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Application 15" );
   }

  {
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Esc" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F1" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F2" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F3" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F4" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F5" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F6" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F7" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F8" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F9" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F10" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F11" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F12" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F1" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F2" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F3" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F4" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F5" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F6" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F7" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F8" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F9" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F10" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F11" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F12" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + " );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + " );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + A" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + B" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + C" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + D" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + E" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + F" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + G" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + H" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + I" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + J" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + K" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + L" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + M" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + N" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + O" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + P" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + Q" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + R" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + S" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + T" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + U" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + V" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + W" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + X" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + Y" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Ctrl + Z" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + A" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + B" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + C" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + D" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + E" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + F" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + G" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + H" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + I" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + J" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + K" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + L" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + M" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + N" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + O" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + P" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + Q" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + R" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + S" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + T" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + U" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + V" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + W" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + X" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + Y" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Alt + Z" );
  }

 if( Code_page == RUSSIAN )
  {
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Увеличить громкость" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Уменьшить громкость" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Увеличить громкость (MMOS2)" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Уменьшить громкость (MMOS2)" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Вкл/выкл повторение" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Остановка / продолжение" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Следующая дорожка" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Предыдущая дорожка" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Остановить воспроизведение" );
  }
 else
  {
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Volume increment" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Volume decrement" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Volume increment (MMOS2)" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Volume decrement (MMOS2)" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Switch repeat" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Pause / Resume" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Next track" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Previous track" );
   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "Stop play" );

   Point ++; if( Point < MAX_ACTIONS ) strcpy( Strings[ Point ], "" );
  }

  // Передаем строки окну списка.
  {
   HWND List_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Action_list_ID );

   Keyboard_Actions.Settings.Action_list_is_locked = 1; WinShowWindow( List_window, 0 );
   for( Count = 0; Count < Max_strings; Count ++ ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Strings[ Count ] ) );
   Keyboard_Actions.Settings.Action_list_is_locked = 0; WinShowWindow( List_window, 1 );
  }

  // Освобождаем память.
  for( Count = 0; Count < Max_strings; Count ++ ) { DosFreeMem( Strings[ Count ] ); Strings[ Count ] = NULL; }
 }

 // Задаем список клавиш.
 {
  INT Point = -1; INT Previous_point = 0;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F11;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Shift_F11;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F12;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Shift_F12;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.PrtScr;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.SysRq;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Pause;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Right_Alt;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Shift_Right_Alt;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_common_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Left_WinKey;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Right_WinKey;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.TaskList;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_win_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F1;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F2;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F3;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F4;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F5;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F6;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F7;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F8;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F9;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.F10;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_function_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Backslash;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Backspace;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_quick_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Num_Slash;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Num_Multiple;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Num_Minus;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Num_Plus;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Num_Enter;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_numeric_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F1;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F2;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F3;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F4;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F5;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F6;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F7;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F8;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F9;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F10;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F11;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F12;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_A;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_B;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_C;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_D;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_E;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_F;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_G;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_H;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_I;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_J;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_K;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_L;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_M;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_N;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_O;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_P;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Q;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_R;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_S;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_T;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_U;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_V;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_W;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_X;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Y;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WinKey_Z;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_pointer_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Power;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Sleep;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.WakeUp;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_power_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Play;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Stop;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Previous_track;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Next_track;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Volume_decrement;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Volume_increment;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Mute;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Media;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_multimedia_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Terminal;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Calculator;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Browser;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Mail_reader;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Search;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Bookmarks;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_toolkit_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Back;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Forward;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Cancel;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Refresh;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_internet_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.PageLeft;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.PageRight;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_scrolling_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_1;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_1;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_2;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_2;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_3;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_3;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_4;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_4;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_5;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_5;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_6;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_6;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_7;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_7;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_8;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_8;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_9;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_9;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_A;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_A;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_B;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_B;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_C;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_C;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_D;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_D;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_E;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_E;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.UserKey_F;            if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Scan_code = &Definer.Settings.Keys.SC_UserKey_F;

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_user_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_i;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Home;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Search;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Mail;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_People;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Bench;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Chat;
  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = &Definer.Settings.Keys.Compaq_Reading;

  { INT Count; for( Count = Previous_point; Count <= Point; Count ++ ) { if( Count < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Count ].Permission = &Definer.Settings.Define_Compaq_keys; } Previous_point = Point; }

  Point ++; if( Point < MAX_KEYS ) Keyboard_Actions.Settings.Actions.Keys[ Point ].Key = EMPTY_KEY_ITEM;                              
 }

 // Задаем список действий.
 {
  INT Point = -1;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = DO_NOT_DEFINE;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_WINDOW_LIST;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_NEXT_WINDOW;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PREV_WINDOW;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_DRIVES;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PRINTER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PRINTERS;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_WINVIEWER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_WPS_CLOCK;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PULSE;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_POWER_MGR;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_ECENTER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_EPAGER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_WARPCENTER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_LAUNCHPAD;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_SYSBAR;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_FILEBAR;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_SYSTRAY;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_TASK_MANAGER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_NETWORK;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_DIALER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_VIO_COMMANDER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PM_COMMANDER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_DIGITAL_CAMERA;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_FINDER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_WEB_BROWSER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_MAIL_READER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_INTERNET_CHAT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_ICQ_PAGER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_FTP_BROWSER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_VIO_SSH_TERMINAL;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_PM_SSH_TERMINAL;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_REMOTE_DESKTOP_VNC;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_REMOTE_DESKTOP_RDP;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_TEXT_EDITOR;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_CALCULATOR;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_IMAGE_VIEWER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_MUSIC_PLAYER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_VIDEO_PLAYER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_MOD_PLAYER;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_FM_TUNER;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_1;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_2;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_3;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_4;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_5;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_6;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_7;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_8;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_9;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_A;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_B;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_C;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_D;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_E;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = SHOW_USER_TOOL_F;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ESC;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F1;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F2;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F3;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F4;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F5;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F6;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F7;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F8;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F9;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F10;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F11;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F12;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F1;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F2;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F3;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F4;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F5;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F6;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F7;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F8;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F9;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F10;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F11;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F12;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_LEFT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_RIGHT;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_A;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_B;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_C;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_D;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_E;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_F;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_G;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_H;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_I;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_J;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_K;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_L;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_M;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_N;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_O;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_P;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_Q;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_R;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_S;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_T;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_U;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_V;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_W;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_X;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_Y;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_CTRL_Z;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_A;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_B;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_C;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_D;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_E;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_F;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_G;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_H;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_I;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_J;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_K;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_L;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_M;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_N;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_O;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_P;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_Q;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_R;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_S;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_T;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_U;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_V;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_W;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_X;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_Y;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = CHAR_ALT_Z;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_VOLUME_INCREMENT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_VOLUME_DECREMENT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_VOLUME_INCREMENT_MMOS2;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_VOLUME_DECREMENT_MMOS2;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_REPEAT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_PAUSE;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_NEXT;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_PREVIOUS;
  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = MM_STOP;

  Point ++; if( Point < MAX_ACTIONS ) Keyboard_Actions.Settings.Actions.Actions[ Point ] = EMPTY_ACTION_ITEM;
 }

 /* * */
}