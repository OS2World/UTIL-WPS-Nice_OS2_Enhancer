
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Patcher_Tune( HINI Ini_file )
{
 // Читаем настройки.
 Patcher_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Patcher_ReadSettings( Ini_file );

 // Отключаем заставку для окна оболочки.
 if( Patcher.Settings.Limited_animation ) Patcher_DisableAnimation( GetDetectedShellWindow() );

 // Возврат.
 return;
}