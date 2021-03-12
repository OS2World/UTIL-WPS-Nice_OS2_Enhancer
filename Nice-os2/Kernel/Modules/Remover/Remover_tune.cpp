
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Remover_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Remover_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Remover_ReadSettings (Ini_file);

  // Запоминаем, что поток должен быть создан.
  if (Remover.Settings.Remove_items_from_Window_list) Enhancer.Modules.Remover->Required = 1;

  // Возврат.
  return;
}
