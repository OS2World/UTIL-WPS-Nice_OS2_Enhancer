
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID PriorityManager_Tune (HINI Ini_file)
{
  // ����������, ���� �� �뫮 ������ �ਮ����.
  BYTE Dynamic_priority = PriorityManager.Settings.Dynamic_priority;

  // ��⠥� ����ன��.
  PriorityManager_SetPreDefinedSettings (SET_ALL_SETTINGS);
  PriorityManager_ReadSettings (Ini_file);

  // ��⠭�������� �ਮ���� ��� ��� �ਫ������.
  if (Dynamic_priority) if (!PriorityManager.Settings.Dynamic_priority) PriorityManager_SetDynamicPriorityLevels (SDPL_RESTORE_ALL_PROCESSES);
  if (!Dynamic_priority) if (PriorityManager.Settings.Dynamic_priority) PriorityManager_SetDynamicPriorityLevels (SDPL_FORCE_ACTIVE_PROCESS);

  // ������.
  return;
}