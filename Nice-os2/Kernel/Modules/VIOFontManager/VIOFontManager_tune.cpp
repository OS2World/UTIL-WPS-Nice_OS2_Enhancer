
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID VIOFontManager_Tune( HINI Ini_file )
{
 // Читаем настройки.
 VIOFontManager_SetPreDefinedSettings( SET_ALL_SETTINGS );
 VIOFontManager_ReadSettings( Ini_file );

 // Запоминаем, какие потоки еще должны быть созданы.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) Enhancer.Modules.VIOMonitor->Required = 1;

 // Возврат.
 return;
}
