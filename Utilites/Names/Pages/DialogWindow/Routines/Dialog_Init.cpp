
// ─── Выполняет действие ───

VOID DialogWindow_Init( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0 )
{
 // Задаем заголовок окна.
 if( Names.Settings.Code_page == RUSSIAN ) strcpy( Names.Frame_window_title, StrConst_RU_Window_title );
 else strcpy( Names.Frame_window_title, StrConst_EN_Window_title );

 WinSetWindowText( Window, Names.Frame_window_title );

 // Устанавливаем картинку в левом верхнем углу окна.
 WinSendMsg( Window, WM_SETICON, (MPARAM) WinLoadPointer( HWND_DESKTOP, NULLHANDLE, 1 ), 0 );

 // Задаем расположение окна.
 {
  INT X_Screen = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
  INT Y_Screen = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

  SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

  INT Window_position_X = ( X_Screen - Window_placement.cx ) / 2;
  INT Window_position_Y = ( Y_Screen - Window_placement.cy ) / 2 + ( Y_Screen - Window_placement.cy ) / 4 / 2;

  WinSetWindowPos( Window, HWND_TOP, Window_position_X, Window_position_Y, Window_placement.cx, Window_placement.cy, SWP_ZORDER | SWP_MOVE | SWP_NOADJUST );
  WinSetActiveWindow( HWND_DESKTOP, Window );
 }

 // Добавляем его в список окон.
 {
  SWCNTRL Task; HSWITCH Switch_handle = NULLHANDLE;

  bzero( &Task, sizeof( SWCNTRL ) );
  Task.hwnd = Window;
  Task.hwndIcon = (HPOINTER) WinSendMsg( Window, WM_QUERYICON, 0, 0 );
  WinQueryWindowProcess( Window, &Task.idProcess, NULL );
  strcpy( Task.szSwtitle, Names.Frame_window_title );

  Task.uchVisibility = SWL_VISIBLE;
  Task.fbJump = SWL_JUMPABLE;

  Switch_handle = WinCreateSwitchEntry( Names.Application, &Task );
  WinChangeSwitchEntry( Switch_handle, &Task );
 }

 // Передвигаем картинку.
 {
  SWP Window_placement = {0};
  WinQueryWindowPos( Window, &Window_placement );

  if( Window_placement.cx > MAINWNDFORM_WIDTH && Window_placement.cy > MAINWNDFORM_HEIGHT )
   {
    HWND Bitmap = WinWindowFromID( Window, ID_MAINWNDFORM_BITMAP );
    HWND Checkbox = WinWindowFromID( Window, ID_MAINWNDFORM_NAMES_CHECKBOX );

    SWP Bitmap_placement = {0}; WinQueryWindowPos( Bitmap, &Bitmap_placement );
    SWP Checkbox_placement = {0}; WinQueryWindowPos( Checkbox, &Checkbox_placement );

    Bitmap_placement.y = ( Window_placement.cy - Bitmap_placement.cy ) / 2;
    Bitmap_placement.x = ( Checkbox_placement.x - Bitmap_placement.cx ) / 2;

    WinSetWindowPos( Bitmap, HWND_TOP, Bitmap_placement.x, Bitmap_placement.y, Bitmap_placement.cx, Bitmap_placement.cy, SWP_ZORDER | SWP_MOVE | SWP_NOADJUST );
   }
 }

 // Задаем текст полей ввода.
 if( Names.Settings.Code_page == RUSSIAN )
  {
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_VERSION_LABEL ), StrConst_RU_Version );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_TITLE_LABEL ), StrConst_RU_Title );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_SUBTITLE_LABEL ), StrConst_RU_Subtitle );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_NAMES_CHECKBOX ), StrConst_RU_Fix_names );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_LONGNAMES_CHECKBOX ), StrConst_RU_Fix_longnames );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_ICONS_CHECKBOX ), StrConst_RU_Fix_icons );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_TYPE_CHECKBOX ), StrConst_RU_Fix_type );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_READONLY_CHECKBOX ), StrConst_RU_Fix_readonly );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_RU_Path );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_START_BUTTON ), StrConst_RU_Go );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_HELP_BUTTON ), StrConst_RU_Help );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Exit );
  }
 else
  {
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_VERSION_LABEL ), StrConst_EN_Version );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_TITLE_LABEL ), StrConst_EN_Title );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_SUBTITLE_LABEL ), StrConst_EN_Subtitle );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_NAMES_CHECKBOX ), StrConst_EN_Fix_names );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_LONGNAMES_CHECKBOX ), StrConst_EN_Fix_longnames );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_ICONS_CHECKBOX ), StrConst_EN_Fix_icons );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_TYPE_CHECKBOX ), StrConst_EN_Fix_type );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_READONLY_CHECKBOX ), StrConst_EN_Fix_readonly );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_EN_Path );

   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_START_BUTTON ), StrConst_EN_Go );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_HELP_BUTTON ), StrConst_EN_Help );
   WinSetWindowText( WinWindowFromID( Window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Exit );
  }

 {
  // Открываем файл настроек.
  HINI Ini_file = OpenIniProfile( Names.Application, Names.Settings.Ini_file );

  // Читаем настройки.
  if( Ini_file )
   {
    ULONG Byte; ULONG Path;
    Byte = sizeof( BYTE ); PrfQueryProfileData( Ini_file, "Settings", "Convert names", &Names.Task.Convert_names, &Byte );
    Byte = sizeof( BYTE ); PrfQueryProfileData( Ini_file, "Settings", "Revise differences", &Names.Task.Revise_differences, &Byte );
    Byte = sizeof( BYTE ); PrfQueryProfileData( Ini_file, "Settings", "Remove images", &Names.Task.Remove_images, &Byte );
    Byte = sizeof( BYTE ); PrfQueryProfileData( Ini_file, "Settings", "Remove types", &Names.Task.Remove_types, &Byte );
    Byte = sizeof( BYTE ); PrfQueryProfileData( Ini_file, "Settings", "Turn OFF ReadOnly", &Names.Task.Turn_OFF_ReadOnly, &Byte );

    Path = SIZE_OF_PATH;   PrfQueryProfileData( Ini_file, "Settings", "Root directory", &Names.Task.Root_directory, &Path );

    // Закрываем файл настроек.
    PrfCloseProfile( Ini_file );
   }

  // Если не задан каталог, с которого надо начать обработку - его должен задать пользователь.
  if( Names.Task.Root_directory[ 0 ] == 0 )
   {
    if( Names.Settings.Code_page == RUSSIAN )
     strncpy( Names.Task.Root_directory, StrConst_RU_Type_dirname, SIZE_OF_PATH );
    else
     strncpy( Names.Task.Root_directory, StrConst_EN_Type_dirname, SIZE_OF_PATH );
   }

  // Если задана строка DBCS - отключаем преобразование имен.
  if( Names.Settings.DBCS_line[ 0 ] != 0 )
   {
    Names.Task.Convert_names = 0;
    WinShowWindow( WinWindowFromID( Window, ID_MAINWNDFORM_NAMES_CHECKBOX ), 0 );
    WinEnableWindow( WinWindowFromID( Window, ID_MAINWNDFORM_NAMES_CHECKBOX ), 0 );
   }

  // Запоминаем, что настройки не изменены.
  Names.Settings.Settings_are_changed = 0;
 }

 // Возврат.
 return;
}

