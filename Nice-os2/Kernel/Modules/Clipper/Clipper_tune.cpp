
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Clipper_Tune( HINI Ini_file )
{
 // Читаем настройки.
 Clipper_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Clipper_ReadSettings( Ini_file );

 // Запоминаем, что поток должен быть создан.
 if( Clipper.Settings.CopyPaste_keys_in_VIO || Clipper.Settings.Mouse_in_VIO ) Enhancer.Modules.Clipper->Required = 1;

 // Возврат.
 return;
}
