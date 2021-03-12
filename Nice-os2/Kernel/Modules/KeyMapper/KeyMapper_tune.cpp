
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID KeyMapper_Tune (HINI Ini_file)
{
  // Читаем настройки.
  KeyMapper_SetPreDefinedSettings (SET_ALL_SETTINGS);
  KeyMapper_ReadSettings (Ini_file);

  // Возврат.
  return;
}