
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Patcher_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  if (Division == SET_ALL_SETTINGS || Division == SET_SYS_PATCHES)
  {
    Patcher.Settings.Restore_windows_before_closing = 1;
    Patcher.Settings.Limited_animation = 1;
    Patcher.Settings.Patch_WarpCenter = 0;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Patcher_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Restore windows before closing", &Byte_data, &Byte)) Patcher.Settings.Restore_windows_before_closing = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Limited animation", &Byte_data, &Byte)) Patcher.Settings.Limited_animation = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Patch WarpCenter", &Byte_data, &Byte)) Patcher.Settings.Patch_WarpCenter = Byte_data;

  // Возврат.
  return;
}