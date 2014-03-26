
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID VIOMonitor_Tune( HINI Ini_file )
{
 // Запоминаем, что поток должен быть создан.
 if( FontsCanBeChangedInVIOWindows() ) Enhancer.Modules.VIOMonitor->Required = 1;

 // Возврат.
 return;
}
