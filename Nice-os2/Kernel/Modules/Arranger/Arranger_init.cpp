
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Arranger_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  if (Division == SET_ALL_SETTINGS || Division == SET_PLACEMENT)
  {
    Arranger.Settings.Arrange_VIO_windows     = 0;
    Arranger.Settings.Arrange_FC2_windows     = 1;
    Arranger.Settings.Arrange_WindowList      = 1;
    Arranger.Settings.Arrange_WPS_windows     = 0;
    Arranger.Settings.Arrange_Browser_windows = 0;
    Arranger.Settings.Arrange_Network_windows = 0;
    Arranger.Settings.Arrange_XWP_windows     = 0;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Arranger_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange VIO windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_VIO_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange FC2 windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_FC2_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange WindowList",      &Byte_data, &Byte)) Arranger.Settings.Arrange_WindowList      = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange WPS windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_WPS_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange Browser windows", &Byte_data, &Byte)) Arranger.Settings.Arrange_Browser_windows = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange Network windows", &Byte_data, &Byte)) Arranger.Settings.Arrange_Network_windows = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange XWP windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_XWP_windows     = Byte_data;

  // Возврат.
  return;
}