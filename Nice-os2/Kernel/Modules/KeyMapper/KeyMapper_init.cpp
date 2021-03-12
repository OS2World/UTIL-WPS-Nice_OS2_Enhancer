
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID KeyMapper_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  // Клавиша "|\" иногда располагается рядом рядом с клавишей "Enter", поэтому настройки лучше отключить.
  if (Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD)
  {
    KeyMapper.Settings.Define_Ctrl_CV = 1;
    KeyMapper.Settings.Define_Dash = 0;
    KeyMapper.Settings.Define_Ctrl_Dash = 0;
    KeyMapper.Settings.Define_Enter = 1;
    KeyMapper.Settings.Define_Alt_F9 = 1;
    KeyMapper.Settings.Discard_F3 = 1;
    KeyMapper.Settings.Enable_WMKeys_in_VIO = 1;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID KeyMapper_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Define Ctrl + C/V", &Byte_data, &Byte)) KeyMapper.Settings.Define_Ctrl_CV = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Define Dash", &Byte_data, &Byte)) KeyMapper.Settings.Define_Dash = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Define Ctrl + Dash", &Byte_data, &Byte)) KeyMapper.Settings.Define_Ctrl_Dash = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Define Enter", &Byte_data, &Byte)) KeyMapper.Settings.Define_Enter = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Define Alt + F9", &Byte_data, &Byte)) KeyMapper.Settings.Define_Alt_F9 = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Discard F3", &Byte_data, &Byte)) KeyMapper.Settings.Discard_F3 = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Enable WMKeys in VIO", &Byte_data, &Byte)) KeyMapper.Settings.Enable_WMKeys_in_VIO = Byte_data;

  // Возврат.
  return;
}