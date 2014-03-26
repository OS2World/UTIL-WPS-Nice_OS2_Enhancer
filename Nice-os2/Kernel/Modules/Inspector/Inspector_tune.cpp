
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Inspector_Tune( HINI Ini_file )
{
 // Читаем настройки.
 Inspector_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Inspector_ReadSettings( Ini_file );

 // Запоминаем, что поток должен быть создан.
 Enhancer.Modules.Inspector->Required = 1;

 // Возврат.
 return;
}
