
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Controller_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Controller_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Controller_ReadSettings (Ini_file);

  // Проверяем настройки.
  {
    BYTE Settings_are_correct = 0;

    if (Controller.Settings.Keyboard_rate == (12 * 2)) Settings_are_correct = 1;
    if (Controller.Settings.Keyboard_rate == (12 * 3)) Settings_are_correct = 1;

    if (!Settings_are_correct) Controller.Settings.SpeedUp_keyboard = 0;
  }

  // Запоминаем, что поток должен быть создан.
  if (Controller.Settings.Turn_Num_Lock || 
      Controller.Settings.SpeedUp_keyboard ||
      Controller.Settings.Suppress_CtrlAltDel) Enhancer.Modules.Controller->Required = 1;

  // Возврат.
  return;
}
