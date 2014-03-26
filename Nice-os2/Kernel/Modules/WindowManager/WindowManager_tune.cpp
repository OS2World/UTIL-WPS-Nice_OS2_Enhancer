
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID WindowManager_Tune( HINI Ini_file )
{
 // Запоминаем, что поток должен быть создан.
 Enhancer.Modules.WindowManager->Required = 1;

 // Возврат.
 return;
}
