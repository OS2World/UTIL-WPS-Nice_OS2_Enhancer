
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Changer_Tune( HINI Ini_file )
{
 // Запоминаем, что поток должен быть создан.
 Enhancer.Modules.Changer->Required = 1;

 // Возврат.
 return;
}
