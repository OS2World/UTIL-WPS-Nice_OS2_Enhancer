
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID KeyMapper_Tune (HINI Ini_file)
{
  // ��⠥� ����ன��.
  KeyMapper_SetPreDefinedSettings (SET_ALL_SETTINGS);
  KeyMapper_ReadSettings (Ini_file);

  // ������.
  return;
}