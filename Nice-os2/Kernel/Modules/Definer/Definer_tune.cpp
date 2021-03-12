
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Definer_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Definer_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Definer_ReadSettings (Ini_file);

  // Возврат.
  return;
}