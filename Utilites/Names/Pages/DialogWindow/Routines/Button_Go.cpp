
// ─── Выполняет действие ───

VOID DialogWindow_GoButton (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Если поток уже работает - возврат.
  if (Names.Processing)
  {
    WinAlarm (HWND_DESKTOP, WA_NOTE);
    return;
  }

  // Запоминаем каталог, с которого надо начать обработку.
  Names.Task.Root_directory[0] = 0;
  WinQueryDlgItemText (Window, ID_MAINWNDFORM_PATH_FIELD, SIZE_OF_PATH, Names.Task.Root_directory);

  // Если диск не указан - возврат.
  if (Names.Task.Root_directory[0] == 0 || Names.Task.Root_directory[1] != ':') return;

  // Делаем первую букву заглавной.
  Names.Task.Root_directory[1] = 0;
  UpperCase (Names.Task.Root_directory);
  Names.Task.Root_directory[1] = ':';

  {
    // Если диск проверять нельзя - возврат.
    INT Length = strlen (Names.Task.Root_directory);

    if (Length == 2 || Length == 3)
     if (!PermissionForDriveCheck (Names.Task.Root_directory, 1))
      return;

    // Если диск недоступен - возврат.
    if (!DriveIsAvailable (Names.Task.Root_directory))
    {
      if (Names.Settings.Code_page == RUSSIAN)
       WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Drive_is_unavailable, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
      else
       WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Drive_is_unavailable, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);

      return;
    }

    // Убираем разделитель в конце строки.
    CutLastSlash (Names.Task.Root_directory);
  }

  // Обрабатываем файлы.
  StartProcessing ();

  // Возврат.
  return;
}

