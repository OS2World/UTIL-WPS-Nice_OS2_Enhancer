
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID PriorityManager_Tune (HINI Ini_file)
{
  // Запоминаем, надо ли было менять приоритеты.
  BYTE Dynamic_priority = PriorityManager.Settings.Dynamic_priority;

  // Читаем настройки.
  PriorityManager_SetPreDefinedSettings (SET_ALL_SETTINGS);
  PriorityManager_ReadSettings (Ini_file);

  // Устанавливаем приоритеты для всех приложений.
  if (Dynamic_priority) if (!PriorityManager.Settings.Dynamic_priority) PriorityManager_SetDynamicPriorityLevels (SDPL_RESTORE_ALL_PROCESSES);
  if (!Dynamic_priority) if (PriorityManager.Settings.Dynamic_priority) PriorityManager_SetDynamicPriorityLevels (SDPL_FORCE_ACTIVE_PROCESS);

  // Возврат.
  return;
}