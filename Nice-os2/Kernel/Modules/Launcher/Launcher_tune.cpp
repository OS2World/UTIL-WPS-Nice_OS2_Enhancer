
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Launcher_Tune( HINI Ini_file )
{
 // Запоминаем, что поток должен быть создан.
 Enhancer.Modules.Launcher->Required = 1;

 // Возврат.
 return;
}
