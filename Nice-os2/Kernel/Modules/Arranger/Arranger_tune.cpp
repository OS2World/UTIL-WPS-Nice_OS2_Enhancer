
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Arranger_Tune( HINI Ini_file )
{
 // Читаем настройки.
 Arranger_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Arranger_ReadSettings( Ini_file );

 // Запоминаем, что поток должен быть создан.
 Enhancer.Modules.Arranger->Required = 1;

 // Возврат.
 return;
}
