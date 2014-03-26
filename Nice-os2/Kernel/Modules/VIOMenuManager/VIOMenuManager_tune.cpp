
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID VIOMenuManager_Tune( HINI Ini_file )
{
 // Читаем настройки.
 VIOMenuManager_SetPreDefinedSettings( SET_ALL_SETTINGS );
 VIOMenuManager_ReadSettings( Ini_file );

 // Запоминаем, что поток должен быть создан.
 if( VIOMenuManager.Settings.SSH_Commands ) Enhancer.Modules.VIOMenuManager->Required = 1;

 // Возврат.
 return;
}

