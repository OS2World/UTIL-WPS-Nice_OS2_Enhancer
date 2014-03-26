
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Inspector_SetPreDefinedSettings( LONG Division )
{
 // Задаем действия для списка известных приложений.
 if( Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD )
  {
   Inspector.Settings.Check_Repository = 1;
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Inspector_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Byte_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Repository", "Check Repository", &Byte_data, &Byte ) ) Inspector.Settings.Check_Repository = Byte_data;

 // Возврат.
 return;
}
