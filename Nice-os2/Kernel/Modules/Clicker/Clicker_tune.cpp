
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Clicker_Tune (HINI Ini_file)
{
  // ��⠥� ����ன��.
  Clicker_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Clicker_ReadSettings (Ini_file);

  // �᫨ ��� �㤥� �㦥�:
  if (Clicker.Settings.Keyboard_echo)
  {
    // ������ ����� 䠩���.
    GetCurrentPath (Clicker.RTSettings.Keyboard_wav);
    strcat (Clicker.RTSettings.Keyboard_wav, "\\Audio\\Keyboard.wav");

    GetCurrentPath (Clicker.RTSettings.Keyboard_exe);
    strcat (Clicker.RTSettings.Keyboard_exe, "\\Audio\\Keyboard.exe");

    // �᫨ 䠩��� ��� - �⪫�砥� ����ன��.
    if (!FileExists (Clicker.RTSettings.Keyboard_wav) ||
        !FileExists (Clicker.RTSettings.Keyboard_exe)) Clicker.Settings.Keyboard_echo = 0;

    // ��७�ᨬ 䠩� � ��㪮� �� ���������� �� ��� � �����.
    if (Clicker.Settings.Keyboard_echo)
     if (Clicker.Settings.Cache_echo_file) Clicker_CopyEchoFileToRAMDrive ();
  }

  // ����������, �� ��⮪ ������ ���� ᮧ���.
  if (Clicker.Settings.Keyboard_echo) Enhancer.Modules.Clicker->Required = 1;

  // ������.
  return;
}
