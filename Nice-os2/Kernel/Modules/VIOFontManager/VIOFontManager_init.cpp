
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID VIOFontManager_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &VIOFontManager.Settings.VIOFontMetrics, sizeof( VIOFONTMETRICS ) );
  }

 if( Division == SET_ALL_SETTINGS || Division == SET_VIO_WINDOWS )
  {
   VIOFontManager.Settings.Change_VIO_font_metrics = 0;
   VIOFontManager.Settings.Change_fonts_for_known_applications = 1;
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID VIOFontManager_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Int = 0; ULONG Name = 0; ULONG Byte_data = 0; ULONG Int_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Change VIO font metrics", &Byte_data, &Byte ) ) VIOFontManager.Settings.Change_VIO_font_metrics = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Change fonts for known applications", &Byte_data, &Byte ) ) VIOFontManager.Settings.Change_fonts_for_known_applications = Byte_data;

 {
  CHAR Item[ SIZE_OF_PATH ] = "";

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 1 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 2 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 3 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 4 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 5 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 6 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 7 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "FontMetrics", "Shell 8 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Item ); Item[ 0 ] = 0; }
 }

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 1", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 2", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 3", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 4", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 5", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 6", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 7", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "X 8", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.X_8 = Int_data;

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 1", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 2", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 3", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 4", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 5", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 6", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 7", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "FontMetrics", "Y 8", &Int_data, &Int ) ) VIOFontManager.Settings.VIOFontMetrics.Y_8 = Int_data;

 // Возврат.
 return;
}