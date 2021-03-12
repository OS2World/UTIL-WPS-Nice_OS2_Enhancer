
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Arranger_SetPreDefinedSettings (LONG Division)
{
  // ������ ����ன��.
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

  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Arranger_ReadSettings (HINI Ini_file)
{
  // ��⠥� ����ன��.
  ULONG Byte = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange VIO windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_VIO_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange FC2 windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_FC2_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange WindowList",      &Byte_data, &Byte)) Arranger.Settings.Arrange_WindowList      = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange WPS windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_WPS_windows     = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange Browser windows", &Byte_data, &Byte)) Arranger.Settings.Arrange_Browser_windows = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange Network windows", &Byte_data, &Byte)) Arranger.Settings.Arrange_Network_windows = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Arrange XWP windows",     &Byte_data, &Byte)) Arranger.Settings.Arrange_XWP_windows     = Byte_data;

  // ������.
  return;
}