
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Controller_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD )
  {
   Controller.Settings.Turn_Num_Lock = 1;
   Controller.Settings.Define_Num_keys = 1;

   Controller.Settings.Reset_Shift_keys = 0;

   Controller.Settings.SpeedUp_keyboard = 1;
   Controller.Settings.Keyboard_rate = ( 12 * 3 );

   Controller.Settings.Suppress_CtrlAltDel = 0;
   Controller.Settings.Suppress_CtrlBreak = 0;
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Controller_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Byte_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Turn Num Lock", &Byte_data, &Byte ) ) Controller.Settings.Turn_Num_Lock = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Define Num keys", &Byte_data, &Byte ) ) Controller.Settings.Define_Num_keys = Byte_data;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Reset Shift keys", &Byte_data, &Byte ) ) Controller.Settings.Reset_Shift_keys = Byte_data;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Speed up keyboard", &Byte_data, &Byte ) ) Controller.Settings.SpeedUp_keyboard = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Keyboard rate", &Byte_data, &Byte ) ) Controller.Settings.Keyboard_rate = Byte_data;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Suppress Ctrl+Alt+Del", &Byte_data, &Byte ) ) Controller.Settings.Suppress_CtrlAltDel = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Suppress Ctrl+Break", &Byte_data, &Byte ) ) Controller.Settings.Suppress_CtrlBreak = Byte_data;

 // Возврат.
 return;
}