
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Remover_Tune (HINI Ini_file)
{
  // ��⠥� ����ன��.
  Remover_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Remover_ReadSettings (Ini_file);

  // ����������, �� ��⮪ ������ ���� ᮧ���.
  if (Remover.Settings.Remove_items_from_Window_list) Enhancer.Modules.Remover->Required = 1;

  // ������.
  return;
}
