
// ─── Выполняет действие ───

VOID DialogWindow_Close (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Если работает поток - завершаем его.
  if (Names.Processing)
  {
    // Поток должен быть завершен.
    Names.Processing = 0;

    // Сообщение.
    if (Names.Settings.Code_page == RUSSIAN)
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
    else
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
  }

  // Убираем окно из списка окон.
  WinRemoveSwitchEntry (WinQuerySwitchHandle (Window, 0));

  // Если настройки были изменены:
  if (Names.Settings.Settings_are_changed)
  {
    // Запоминаем каталог, с которого надо начать обработку.
    WinQueryDlgItemText (Window, ID_MAINWNDFORM_PATH_FIELD, SIZE_OF_PATH, Names.Task.Root_directory);

    // Открываем файл настроек.
    HINI Ini_file = OpenIniProfile (Names.Application, Names.Settings.Ini_file);

    // Записываем настройки.
    if (Ini_file != NULLHANDLE)
    {
      PrfWriteProfileData (Ini_file, "Settings", "Convert names", &Names.Task.Convert_names, sizeof (BYTE));
      PrfWriteProfileData (Ini_file, "Settings", "Revise differences", &Names.Task.Revise_differences, sizeof (BYTE));
      PrfWriteProfileData (Ini_file, "Settings", "Remove images", &Names.Task.Remove_images, sizeof (BYTE));
      PrfWriteProfileData (Ini_file, "Settings", "Remove types", &Names.Task.Remove_types, sizeof (BYTE));
      PrfWriteProfileData (Ini_file, "Settings", "Turn OFF ReadOnly", &Names.Task.Turn_OFF_ReadOnly, sizeof (BYTE));

      PrfWriteProfileData (Ini_file, "Settings", "Root directory", NULL, 0);

      if (Names.Task.Root_directory[0] != '-' && 
          Names.Task.Root_directory[strlen (Names.Task.Root_directory) - 1] != '-')
      {
        PrfWriteProfileData (Ini_file, "Settings", "Root directory", &Names.Task.Root_directory, strlen (Names.Task.Root_directory) + 1);
      }

      // Закрываем файл настроек.
      PrfCloseProfile (Ini_file);
    }
  }

  // Возврат.
  return;
}

