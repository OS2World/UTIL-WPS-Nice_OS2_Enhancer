
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Clicker_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD )
  {
   Clicker.Settings.Keyboard_echo = 0;
   Clicker.Settings.Keyboard_echo_for_IRC = 0;
   Clicker.Settings.Keyboard_echo_for_ICQ = 0;

   Clicker.Settings.Cache_echo_file = 1;
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Clicker_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Byte_data = 0; ULONG Name = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Keyboard echo", &Byte_data, &Byte ) ) Clicker.Settings.Keyboard_echo = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Keyboard echo for IRC", &Byte_data, &Byte ) ) Clicker.Settings.Keyboard_echo_for_IRC = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Keyboard echo for ICQ", &Byte_data, &Byte ) ) Clicker.Settings.Keyboard_echo_for_ICQ = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Cache echo file", &Byte_data, &Byte ) ) Clicker.Settings.Cache_echo_file = Byte_data;

 // Возврат.
 return;
}