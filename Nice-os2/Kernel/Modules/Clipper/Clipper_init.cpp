
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Clipper_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  if (Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD || Division == SET_MOUSE)
  {
    Clipper.Settings.CopyPaste_keys_in_VIO = 1;

    Clipper.Settings.Mouse_in_VIO = 0;
    Clipper.Settings.Mouse_in_VIO_requires_Shift = 1;
    Clipper.Settings.Mouse_in_VIO_sends_Copy = 1;
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Clipper_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", INI_CLIPPER_VIO_COPYPASTE, &Byte_data, &Byte)) Clipper.Settings.CopyPaste_keys_in_VIO = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", INI_CLIPPER_VIO_MOUSE, &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Mouse in VIO requires Shift", &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO_requires_Shift = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Mouse in VIO sends Copy", &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO_sends_Copy = Byte_data;

  // Возврат.
  return;
}