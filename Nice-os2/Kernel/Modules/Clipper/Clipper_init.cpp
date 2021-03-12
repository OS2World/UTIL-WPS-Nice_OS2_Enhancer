
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Clipper_SetPreDefinedSettings (LONG Division)
{
  // ������ ����ன��.
  if (Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD || Division == SET_MOUSE)
  {
    Clipper.Settings.CopyPaste_keys_in_VIO = 1;

    Clipper.Settings.Mouse_in_VIO = 0;
    Clipper.Settings.Mouse_in_VIO_requires_Shift = 1;
    Clipper.Settings.Mouse_in_VIO_sends_Copy = 1;
  }

  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Clipper_ReadSettings (HINI Ini_file)
{
  // ��⠥� ����ன��.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", INI_CLIPPER_VIO_COPYPASTE, &Byte_data, &Byte)) Clipper.Settings.CopyPaste_keys_in_VIO = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", INI_CLIPPER_VIO_MOUSE, &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Mouse in VIO requires Shift", &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO_requires_Shift = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Mouse in VIO sends Copy", &Byte_data, &Byte)) Clipper.Settings.Mouse_in_VIO_sends_Copy = Byte_data;

  // ������.
  return;
}