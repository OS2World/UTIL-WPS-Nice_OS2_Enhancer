
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Krnl_Repository_Tune( HINI Ini_file )
{
 // Читаем настройки.
 Krnl_Repository_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Krnl_Repository_ReadSettings( Ini_file );

 // Запоминаем, что список приложений был прочтен.
 Krnl_Repository.RTSettings.Repository_is_ready = 1;

 // Возврат.
 return;
}