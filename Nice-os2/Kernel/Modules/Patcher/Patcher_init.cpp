
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Patcher_SetPreDefinedSettings (LONG Division)
{
  // ������ ����ன��.
  if (Division == SET_ALL_SETTINGS || Division == SET_SYS_PATCHES)
  {
    Patcher.Settings.Restore_windows_before_closing = 1;
    Patcher.Settings.Limited_animation = 1;
    Patcher.Settings.Patch_WarpCenter = 0;
  }

  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Patcher_ReadSettings (HINI Ini_file)
{
  // ��⠥� ����ன��.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Restore windows before closing", &Byte_data, &Byte)) Patcher.Settings.Restore_windows_before_closing = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Limited animation", &Byte_data, &Byte)) Patcher.Settings.Limited_animation = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Patch WarpCenter", &Byte_data, &Byte)) Patcher.Settings.Patch_WarpCenter = Byte_data;

  // ������.
  return;
}