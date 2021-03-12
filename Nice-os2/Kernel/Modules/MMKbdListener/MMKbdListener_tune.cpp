
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID MMKbdListener_Tune (HINI Ini_file)
{
  // Запоминаем, что поток должен быть создан.
  Enhancer.Modules.MMKbdListener->Required = 1;

  // Возврат.
  return;
}
