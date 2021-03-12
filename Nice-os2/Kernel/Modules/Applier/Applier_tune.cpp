
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Applier_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Applier_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Applier_ReadSettings (Ini_file);

  Applier_ReadDialogList (Ini_file);

  // Запоминаем, что поток должен быть создан.
  if (Applier.Settings.Script_after_Logon || 
      Applier.Settings.Remember_dialog_fields || 
      Applier.Settings.Send_Yes) Enhancer.Modules.Applier->Required = 1;

  // Возврат.
  return;
}
