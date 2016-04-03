
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Definer_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &Definer.Settings.Keys, sizeof( KEYS ) );
  }

 if( Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD )
  {
   Definer.Settings.Define_keys = 1;

   Definer.Settings.Define_common_keys = 1;
   Definer.Settings.Define_win_keys = 1;
   Definer.Settings.Define_function_keys = 0;
   Definer.Settings.Define_quick_keys = 1;
   Definer.Settings.Define_numeric_keys = 1;
   Definer.Settings.Define_pointer_keys = 0;
   Definer.Settings.Define_power_keys = 0;
   Definer.Settings.Define_multimedia_keys = 1;
   Definer.Settings.Define_toolkit_keys = 1;
   Definer.Settings.Define_internet_keys = 1;
   Definer.Settings.Define_scrolling_keys = 0;
   Definer.Settings.Define_user_keys = 0;
   Definer.Settings.Define_Cherry_keys = 1;
   Definer.Settings.Define_Compaq_keys = 1;

   Definer.Settings.Keys.F11 = 0;
   Definer.Settings.Keys.Shift_F11 = 0;
   Definer.Settings.Keys.F12 = 0;
   Definer.Settings.Keys.Shift_F12 = 0;

   Definer.Settings.Keys.PrtScr = SHOW_IMAGE_VIEWER;
   Definer.Settings.Keys.SysRq = SHOW_TASK_MANAGER;
   Definer.Settings.Keys.Pause = 0;

   Definer.Settings.Keys.Right_Alt = 0;
   Definer.Settings.Keys.Shift_Right_Alt = 0;

   Definer.Settings.Keys.Left_WinKey = SHOW_EPAGER;
   Definer.Settings.Keys.Right_WinKey = SHOW_ECENTER;
   Definer.Settings.Keys.TaskList = SHOW_WINDOW_LIST;

   Definer.Settings.Keys.F1 = 0;
   Definer.Settings.Keys.F2 = CHAR_CTRL_S;
   Definer.Settings.Keys.F3 = CHAR_CTRL_F;
   Definer.Settings.Keys.F4 = CHAR_CTRL_R;
   Definer.Settings.Keys.F5 = 0;
   Definer.Settings.Keys.F6 = CHAR_CTRL_L;
   Definer.Settings.Keys.F7 = CHAR_CTRL_F;
   Definer.Settings.Keys.F8 = CHAR_CTRL_R;
   Definer.Settings.Keys.F9 = CHAR_CTRL_H;
   Definer.Settings.Keys.F10 = CHAR_ALT_F4;

   Definer.Settings.Keys.WinKey_Backslash = SHOW_VIO_COMMANDER;
   Definer.Settings.Keys.WinKey_Backspace = SHOW_WEB_BROWSER;

   Definer.Settings.Keys.WinKey_Num_Slash = MM_VOLUME_DECREMENT;
   Definer.Settings.Keys.WinKey_Num_Multiple = MM_VOLUME_INCREMENT;
   Definer.Settings.Keys.WinKey_Num_Minus = MM_STOP;
   Definer.Settings.Keys.WinKey_Num_Plus = MM_REPEAT;
   Definer.Settings.Keys.WinKey_Num_Enter = SHOW_MUSIC_PLAYER;

   Definer.Settings.Keys.WinKey_F1 = 0;
   Definer.Settings.Keys.WinKey_F2 = 0;
   Definer.Settings.Keys.WinKey_F3 = 0;
   Definer.Settings.Keys.WinKey_F4 = 0;
   Definer.Settings.Keys.WinKey_F5 = 0;
   Definer.Settings.Keys.WinKey_F6 = 0;
   Definer.Settings.Keys.WinKey_F7 = 0;
   Definer.Settings.Keys.WinKey_F8 = 0;
   Definer.Settings.Keys.WinKey_F9 = 0;
   Definer.Settings.Keys.WinKey_F10 = SHOW_VIO_SSH_TERMINAL;
   Definer.Settings.Keys.WinKey_F11 = SHOW_FTP_BROWSER;
   Definer.Settings.Keys.WinKey_F12 = SHOW_PM_COMMANDER;

   Definer.Settings.Keys.WinKey_A = 0;
   Definer.Settings.Keys.WinKey_B = 0;
   Definer.Settings.Keys.WinKey_C = 0;
   Definer.Settings.Keys.WinKey_D = 0;
   Definer.Settings.Keys.WinKey_E = 0;
   Definer.Settings.Keys.WinKey_F = 0;
   Definer.Settings.Keys.WinKey_G = 0;
   Definer.Settings.Keys.WinKey_H = 0;
   Definer.Settings.Keys.WinKey_I = 0;
   Definer.Settings.Keys.WinKey_J = 0;
   Definer.Settings.Keys.WinKey_K = 0;
   Definer.Settings.Keys.WinKey_L = 0;
   Definer.Settings.Keys.WinKey_M = 0;
   Definer.Settings.Keys.WinKey_N = 0;
   Definer.Settings.Keys.WinKey_O = 0;
   Definer.Settings.Keys.WinKey_P = 0;
   Definer.Settings.Keys.WinKey_Q = 0;
   Definer.Settings.Keys.WinKey_R = 0;
   Definer.Settings.Keys.WinKey_S = 0;
   Definer.Settings.Keys.WinKey_T = 0;
   Definer.Settings.Keys.WinKey_U = 0;
   Definer.Settings.Keys.WinKey_V = 0;
   Definer.Settings.Keys.WinKey_W = 0;
   Definer.Settings.Keys.WinKey_X = 0;
   Definer.Settings.Keys.WinKey_Y = 0;
   Definer.Settings.Keys.WinKey_Z = 0;

   Definer.Settings.Keys.Power = SHOW_DRIVES;
   Definer.Settings.Keys.Sleep = SHOW_WEB_BROWSER;
   Definer.Settings.Keys.WakeUp = SHOW_VIO_COMMANDER;

   Definer.Settings.Keys.Play = MM_PAUSE;
   Definer.Settings.Keys.Stop = MM_STOP;
   Definer.Settings.Keys.Previous_track = MM_PREVIOUS;
   Definer.Settings.Keys.Next_track = MM_NEXT;
   Definer.Settings.Keys.Volume_decrement = MM_VOLUME_DECREMENT;
   Definer.Settings.Keys.Volume_increment = MM_VOLUME_INCREMENT;
   Definer.Settings.Keys.Mute = MM_REPEAT;
   Definer.Settings.Keys.Media = SHOW_MUSIC_PLAYER;

   Definer.Settings.Keys.Terminal = SHOW_VIO_SSH_TERMINAL;
   Definer.Settings.Keys.Calculator = SHOW_CALCULATOR;
   Definer.Settings.Keys.Browser = SHOW_WEB_BROWSER;
   Definer.Settings.Keys.Mail_reader = 0;
   Definer.Settings.Keys.Search = SHOW_PM_COMMANDER;
   Definer.Settings.Keys.Bookmarks = SHOW_FTP_BROWSER;

   Definer.Settings.Keys.Back = 0;
   Definer.Settings.Keys.Forward = 0;
   Definer.Settings.Keys.Cancel = 0;
   Definer.Settings.Keys.Refresh = 0;

   Definer.Settings.Keys.PageLeft = 0;
   Definer.Settings.Keys.PageRight = 0;

   Definer.Settings.Keys.UserKey_1 = 0;
   Definer.Settings.Keys.UserKey_2 = 0;
   Definer.Settings.Keys.UserKey_3 = 0;
   Definer.Settings.Keys.UserKey_4 = 0;
   Definer.Settings.Keys.UserKey_5 = 0;
   Definer.Settings.Keys.UserKey_6 = 0;
   Definer.Settings.Keys.UserKey_7 = 0;
   Definer.Settings.Keys.UserKey_8 = 0;
   Definer.Settings.Keys.UserKey_9 = 0;
   Definer.Settings.Keys.UserKey_A = 0;
   Definer.Settings.Keys.UserKey_B = 0;
   Definer.Settings.Keys.UserKey_C = 0;
   Definer.Settings.Keys.UserKey_D = 0;
   Definer.Settings.Keys.UserKey_E = 0;
   Definer.Settings.Keys.UserKey_F = 0;

   Definer.Settings.Keys.Compaq_i = SHOW_DRIVES;
   Definer.Settings.Keys.Compaq_Home = SHOW_MUSIC_PLAYER;
   Definer.Settings.Keys.Compaq_Search = SHOW_VIO_COMMANDER;
   Definer.Settings.Keys.Compaq_Mail = 0;
   Definer.Settings.Keys.Compaq_People = SHOW_WEB_BROWSER;
   Definer.Settings.Keys.Compaq_Bench = SHOW_FTP_BROWSER;
   Definer.Settings.Keys.Compaq_Chat = 0;
   Definer.Settings.Keys.Compaq_Reading = SHOW_VIO_SSH_TERMINAL;

   if( Division != SET_ALL_SETTINGS )
    {
     if( QuerySystemCodePage() == RUSSIAN )
      {
       Definer.Settings.Keys.Right_Alt = SHOW_PREV_WINDOW;
       Definer.Settings.Keys.Shift_Right_Alt = SHOW_NEXT_WINDOW;
      }

     if( !SystemWindowIsPresent( FIND_ECENTER ) )
      {
       Definer.Settings.Keys.Left_WinKey = SHOW_LAUNCHPAD;
       Definer.Settings.Keys.Right_WinKey = SHOW_WARPCENTER;
      }

     {
      INT Volume_control = 0;
      if( ShowCommandCanBeUsed( SHOW_MMOS2_VOLUME ) || ShowCommandCanBeUsed( SHOW_UNIAUDIO_MIXER ) )
       {
        Definer.Settings.Keys.Volume_decrement = MM_VOLUME_DECREMENT_MMOS2;
        Definer.Settings.Keys.Volume_increment = MM_VOLUME_INCREMENT_MMOS2;
       }
     }

     {
      INT Mail_reader = 0;
      if( ShowCommandCanBeUsed( SHOW_TEXT_EDITOR ) ) Mail_reader = SHOW_TEXT_EDITOR;
      if( ShowCommandCanBeUsed( SHOW_ICQ_PAGER ) ) Mail_reader = SHOW_ICQ_PAGER;
      if( ShowCommandCanBeUsed( SHOW_INTERNET_CHAT ) ) Mail_reader = SHOW_INTERNET_CHAT;
      if( ShowCommandCanBeUsed( SHOW_MAIL_READER ) ) Mail_reader = SHOW_MAIL_READER;
      Definer.Settings.Keys.Mail_reader = Mail_reader;
      Definer.Settings.Keys.Compaq_Mail = Mail_reader;
     }

     {
      INT Internet_chat = 0;
      if( ShowCommandCanBeUsed( SHOW_ICQ_PAGER ) ) Internet_chat = SHOW_ICQ_PAGER;
      if( ShowCommandCanBeUsed( SHOW_INTERNET_CHAT ) ) Internet_chat = SHOW_INTERNET_CHAT;
      Definer.Settings.Keys.Compaq_Chat = Internet_chat;
     }
    }
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Definer_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Int = 0; ULONG Byte_data = 0; ULONG Int_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define keys", &Byte_data, &Byte ) ) Definer.Settings.Define_keys = Byte_data;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define common keys", &Byte_data, &Byte ) ) Definer.Settings.Define_common_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define win keys", &Byte_data, &Byte ) ) Definer.Settings.Define_win_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define function keys", &Byte_data, &Byte ) ) Definer.Settings.Define_function_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define quick keys", &Byte_data, &Byte ) ) Definer.Settings.Define_quick_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define numeric keys", &Byte_data, &Byte ) ) Definer.Settings.Define_numeric_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define pointer keys", &Byte_data, &Byte ) ) Definer.Settings.Define_pointer_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define power keys", &Byte_data, &Byte ) ) Definer.Settings.Define_power_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define multimedia keys", &Byte_data, &Byte ) ) Definer.Settings.Define_multimedia_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define toolkit keys", &Byte_data, &Byte ) ) Definer.Settings.Define_toolkit_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define internet keys", &Byte_data, &Byte ) ) Definer.Settings.Define_internet_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define scrolling keys", &Byte_data, &Byte ) ) Definer.Settings.Define_scrolling_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define user keys", &Byte_data, &Byte ) ) Definer.Settings.Define_user_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define Cherry keys", &Byte_data, &Byte ) ) Definer.Settings.Define_Cherry_keys = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define Compaq keys", &Byte_data, &Byte ) ) Definer.Settings.Define_Compaq_keys = Byte_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F11", &Int_data, &Int ) ) Definer.Settings.Keys.F11 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F12", &Int_data, &Int ) ) Definer.Settings.Keys.F12 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Shift + F11", &Int_data, &Int ) ) Definer.Settings.Keys.Shift_F11 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Shift + F12", &Int_data, &Int ) ) Definer.Settings.Keys.Shift_F12 = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "PrintScreen", &Int_data, &Int ) ) Definer.Settings.Keys.PrtScr = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "SysRq", &Int_data, &Int ) ) Definer.Settings.Keys.SysRq = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Pause", &Int_data, &Int ) ) Definer.Settings.Keys.Pause = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Right Alt", &Int_data, &Int ) ) Definer.Settings.Keys.Right_Alt = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Shift + Right Alt", &Int_data, &Int ) ) Definer.Settings.Keys.Shift_Right_Alt = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Left WinKey", &Int_data, &Int ) ) Definer.Settings.Keys.Left_WinKey = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Right WinKey", &Int_data, &Int ) ) Definer.Settings.Keys.Right_WinKey = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "TaskList", &Int_data, &Int ) ) Definer.Settings.Keys.TaskList = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F1", &Int_data, &Int ) ) Definer.Settings.Keys.F1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F2", &Int_data, &Int ) ) Definer.Settings.Keys.F2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F3", &Int_data, &Int ) ) Definer.Settings.Keys.F3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F4", &Int_data, &Int ) ) Definer.Settings.Keys.F4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F5", &Int_data, &Int ) ) Definer.Settings.Keys.F5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F6", &Int_data, &Int ) ) Definer.Settings.Keys.F6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F7", &Int_data, &Int ) ) Definer.Settings.Keys.F7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F8", &Int_data, &Int ) ) Definer.Settings.Keys.F8 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F9", &Int_data, &Int ) ) Definer.Settings.Keys.F9 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "F10", &Int_data, &Int ) ) Definer.Settings.Keys.F10 = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Backslash", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Backslash = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Backspace", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Backspace = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Num Slash", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Num_Slash = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Num Multiple", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Num_Multiple = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Num Minus", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Num_Minus = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Num Plus", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Num_Plus = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Num Enter", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Num_Enter = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F1", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F2", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F3", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F4", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F5", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F6", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F7", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F8", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F8 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F9", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F9 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F10", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F10 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F11", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F11 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F12", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F12 = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK A", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_A = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK B", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_B = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK C", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_C = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK D", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_D = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK E", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_E = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK F", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_F = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK G", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_G = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK H", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_H = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK I", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_I = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK J", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_J = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK K", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_K = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK L", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_L = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK M", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_M = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK N", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_N = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK O", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_O = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK P", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_P = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Q", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Q = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK R", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_R = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK S", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_S = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK T", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_T = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK U", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_U = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK V", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_V = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK W", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_W = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK X", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_X = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Y", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Y = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WK Z", &Int_data, &Int ) ) Definer.Settings.Keys.WinKey_Z = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Power", &Int_data, &Int ) ) Definer.Settings.Keys.Power = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Sleep", &Int_data, &Int ) ) Definer.Settings.Keys.Sleep = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "WakeUp", &Int_data, &Int ) ) Definer.Settings.Keys.WakeUp = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Play", &Int_data, &Int ) ) Definer.Settings.Keys.Play = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Stop", &Int_data, &Int ) ) Definer.Settings.Keys.Stop = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Previous track", &Int_data, &Int ) ) Definer.Settings.Keys.Previous_track = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Next track", &Int_data, &Int ) ) Definer.Settings.Keys.Next_track = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Volume decrement", &Int_data, &Int ) ) Definer.Settings.Keys.Volume_decrement = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Volume increment", &Int_data, &Int ) ) Definer.Settings.Keys.Volume_increment = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Mute", &Int_data, &Int ) ) Definer.Settings.Keys.Mute = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Media", &Int_data, &Int ) ) Definer.Settings.Keys.Media = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Terminal", &Int_data, &Int ) ) Definer.Settings.Keys.Terminal = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Calculator", &Int_data, &Int ) ) Definer.Settings.Keys.Calculator = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Browser", &Int_data, &Int ) ) Definer.Settings.Keys.Browser = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Mail reader", &Int_data, &Int ) ) Definer.Settings.Keys.Mail_reader = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Search", &Int_data, &Int ) ) Definer.Settings.Keys.Search = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Bookmarks", &Int_data, &Int ) ) Definer.Settings.Keys.Bookmarks = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Back", &Int_data, &Int ) ) Definer.Settings.Keys.Back = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Forward", &Int_data, &Int ) ) Definer.Settings.Keys.Forward = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Cancel", &Int_data, &Int ) ) Definer.Settings.Keys.Cancel = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Refresh", &Int_data, &Int ) ) Definer.Settings.Keys.Refresh = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "PageLeft", &Int_data, &Int ) ) Definer.Settings.Keys.PageLeft = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "PageRight", &Int_data, &Int ) ) Definer.Settings.Keys.PageRight = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq i", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_i = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Home", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Home = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Search", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Search = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Mail", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Mail = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq People", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_People = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Bench", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Bench = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Chat", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Chat = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "Compaq Reading", &Int_data, &Int ) ) Definer.Settings.Keys.Compaq_Reading = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 1", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 1 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 2", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 2 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 3", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 3 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 4", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 4 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 5", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 5 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 6", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 6 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 7", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 7 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 8", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_8 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 8 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_8 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 9", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_9 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey 9 code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_9 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey A", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_A = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey A code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_A = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey B", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_B = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey B code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_B = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey C", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_C = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey C code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_C = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey D", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_D = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey D code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_D = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey E", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_E = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey E code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_E = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey F", &Int_data, &Int ) ) Definer.Settings.Keys.UserKey_F = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Keys", "UserKey F code", &Int_data, &Int ) ) Definer.Settings.Keys.SC_UserKey_F = Int_data;

 // Возврат.
 return;
}
