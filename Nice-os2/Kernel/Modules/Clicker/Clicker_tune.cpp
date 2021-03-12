
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Clicker_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Clicker_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Clicker_ReadSettings (Ini_file);

  // Если звук будет нужен:
  if (Clicker.Settings.Keyboard_echo)
  {
    // Задаем имена файлов.
    GetCurrentPath (Clicker.RTSettings.Keyboard_wav);
    strcat (Clicker.RTSettings.Keyboard_wav, "\\Audio\\Keyboard.wav");

    GetCurrentPath (Clicker.RTSettings.Keyboard_exe);
    strcat (Clicker.RTSettings.Keyboard_exe, "\\Audio\\Keyboard.exe");

    // Если файлов нет - отключаем настройку.
    if (!FileExists (Clicker.RTSettings.Keyboard_wav) ||
        !FileExists (Clicker.RTSettings.Keyboard_exe)) Clicker.Settings.Keyboard_echo = 0;

    // Переносим файл со звуком от клавиатуры на диск в памяти.
    if (Clicker.Settings.Keyboard_echo)
     if (Clicker.Settings.Cache_echo_file) Clicker_CopyEchoFileToRAMDrive ();
  }

  // Запоминаем, что поток должен быть создан.
  if (Clicker.Settings.Keyboard_echo) Enhancer.Modules.Clicker->Required = 1;

  // Возврат.
  return;
}
