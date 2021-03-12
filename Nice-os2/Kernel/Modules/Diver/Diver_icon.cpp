
// ─── Узнает значок окна ───

// Frame_window - окно рамки.
HPOINTER Diver_QueryWindowIcon (HWND Frame_window)
{
  // Для некоторых окон есть значки по умолчанию, но устанавливать их нельзя.
  if (IsEPMEditorWindow (Frame_window) || WindowIsCreatedBy (APP_EPM, Frame_window))
  {
    if (Diver.RTSettings.EPM_icon == NULLHANDLE)
    {
      ULONG Boot_drive = 0;
      DosQuerySysInfo (QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PULONG) &Boot_drive, sizeof (Boot_drive));

      if (Boot_drive)
      {
        CHAR Path[SIZE_OF_PATH] = "*:";
        Path[0] = (CHAR) Boot_drive + 64; strcat (Path, "\\OS2\\Apps\\Epm.exe");

        if (FileExists (Path)) Diver.RTSettings.EPM_icon = WinLoadFileIcon (Path, 0);
      }
    }

    if (Diver.RTSettings.EPM_icon != NULLHANDLE) return Diver.RTSettings.EPM_icon;
    else return Resources.Default_icons[ICON_VIEWDOC];
  }

  // Для некоторых окон значки по умолчанию можно установить раз и навсегда, отправив сообщение в окно.
  HPOINTER Icon = NULLHANDLE;

  if (Icon == NULLHANDLE)
  {
    if (IsWinListWindow (Frame_window)) Icon = Resources.Default_icons[ICON_WINLIST];
  }

  if (Icon == NULLHANDLE)
  {
    if (WindowIsCreatedBy (APP_VIEWDOC, Frame_window)) Icon = Resources.Default_icons[ICON_VIEWDOC];
  }

  if (Icon == NULLHANDLE)
  {
    if (WindowIsCreatedBy (APP_PMCHKDSK, Frame_window))
    {
      if (Diver.RTSettings.HDD_icon == NULLHANDLE)
      {
        ULONG Boot_drive = 0;
        DosQuerySysInfo (QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PULONG) &Boot_drive, sizeof (Boot_drive));

        if (Boot_drive)
        {
          CHAR Path[SIZE_OF_PATH] = "*:";
          Path[0] = (CHAR) Boot_drive + 64; strcat (Path, "\\eCS\\Bin\\PMFormat.exe");
          if (FileExists (Path)) Diver.RTSettings.HDD_icon = WinLoadFileIcon (Path, 0);
        }
      }

      if (Diver.RTSettings.HDD_icon == NULLHANDLE)
      {
        CHAR Path[SIZE_OF_PATH] = "";
        HOBJECT WPDrives_object = QueryWPSObject ("<WP_DRIVES>");
        if (WPDrives_object != NULLHANDLE) WinQueryObjectPath (WPDrives_object, Path, SIZE_OF_PATH);
        if (Path[0] != 0) Diver.RTSettings.HDD_icon = WinLoadFileIcon (Path, 0);
      }

      if (Diver.RTSettings.HDD_icon != NULLHANDLE) Icon = Diver.RTSettings.HDD_icon;
    }
  }

  if (Icon == NULLHANDLE)
  {
    if (WindowIsCreatedBy (APP_APPLETVIEWER, Frame_window))
    {
      HWND Related_window = FindRelatedFrameWindow (Frame_window, &IsHotJavaBrowserWindow);

      if (Related_window != NULLHANDLE)
      {
        Icon = (HPOINTER) WinSendMsg (Related_window, WM_QUERYICON, 0, 0);
      }
    }
  }

  // Если значок был выбран - ставим и возвращаем его.
  if (Icon != NULLHANDLE)
  {
    if (DrawSystemMenusSettingIsON ())
    {
      WinPostQueueMsg (Enhancer.Modules.Changer->Message_queue, SM_CHANGE_ICON, (MPARAM) Frame_window, (MPARAM) Icon);
    }

    return Icon;
  }

  // Узнаем значок окна.
  Icon = (HPOINTER) WinSendMsg (Frame_window, WM_QUERYICON, 0, 0);

  // Если это пустой значок - ставим изображение по умолчанию.
  HWND Desktop = QueryDesktopWindow ();

  if (Icon == WinQuerySysPointer (Desktop, SPTR_APPICON, 0))
  {
    Icon = WinQuerySysPointer (Desktop, SPTR_PROGRAM, 0);

    if (DrawSystemMenusSettingIsON ())
    {
      WinPostQueueMsg (Enhancer.Modules.Changer->Message_queue, SM_CHANGE_ICON, (MPARAM) Frame_window, (MPARAM) Icon);
    }

    return Icon;
  }

  // Если значок неизвестен - возвращаем значок владельца, главного окна, или значок по умолчанию.
  // Менять значок во всех случаях нельзя - может возникнуть постоянное рисование, которое выглядит как "мигание" рамки.
  if (Icon == NULLHANDLE)
  {
    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Просматриваем всех владельцев.
    HWND Owner_window = WinQueryWindow (Frame_window, QW_FRAMEOWNER);

    while (Owner_window != Desktop && Owner_window != NULLHANDLE)
    {
      // Если владелец - окно рамки:
      if (IsFrameWindow (Owner_window))
      {
        // Узнаем его значок.
        Icon = (HPOINTER) WinSendMsg (Owner_window, WM_QUERYICON, 0, 0);

        // Если он есть - возвращаем его.
        if (Icon != NULLHANDLE) return Icon;
      }

      // Узнаем следующего владельца.
      Owner_window = WinQueryWindow (Owner_window, QW_FRAMEOWNER);
    }

    // Узнаем главное окно приложения.
    HWND Main_window = QueryMainWindow (Frame_window);

    // Если это другое окно:
    if (Main_window != Frame_window)
    {
      // Узнаем его значок.
      Icon = (HPOINTER) WinSendMsg (Main_window, WM_QUERYICON, 0, 0);

      // Если он есть - возвращаем его.
      if (Icon != NULLHANDLE) return Icon;
    }

    // Узнаем очередь сообщений окна.
    HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);

    // Узнаем окно оболочки.
    HWND Shell_window = GetDetectedShellWindow ();

    if (Shell_window != NULLHANDLE)
    {
      // Узнаем очередь сообщений для окна оболочки.
      HMQ Shell_queue = WinQueryWindowULong (Shell_window, QWL_HMQ);

      // Если очереди совпадают - возвращаем его значок.
      if (Shell_queue == Message_queue) return (HPOINTER) WinSendMsg (Shell_window, WM_QUERYICON, 0, 0);

      // Если еще как-нибудь можно установить, что окно создано оболочкой - возвращаем значок окна оболочки.
      if (IsWorkplaceShellWindow (Frame_window)) return (HPOINTER) WinSendMsg (Shell_window, WM_QUERYICON, 0, 0);
    }

    {
      // Перебираем окна в окне рабочего стола.
      HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
      while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
      {
        // Если это то же самое окно - продолжаем перебор окон.
        if (Window == Frame_window) continue;

        // Узнаем расположение окна и его состояние.
        SWP Window_state = {0}; WinQueryWindowPos (Window, &Window_state);

        // Если окно не скрыто и не уменьшено в значок:
        if (!(Window_state.fl & SWP_HIDE)) if (!(Window_state.fl & SWP_MINIMIZE))
        {
          // Если в это окно нельзя переключиться - продолжаем перебор окон.
          if (!PermissionForSwitching (Window)) continue;
        }

        // Узнаем очередь сообщений окна.
        HMQ Window_queue = WinQueryWindowULong (Window, QWL_HMQ);

        // Если очереди совпадают - узнаем его значок.
        if (Window_queue == Message_queue)
        {
          // Узнаем значок окна.
          Icon = (HPOINTER) WinSendMsg (Window, WM_QUERYICON, 0, 0);

          // Если он есть - возвращаем его.
          if (Icon != NULLHANDLE)
          {
            // Завершаем перебор окон.
            WinEndEnumWindows (Enumeration);

            // Возвращаем значок.
            return Icon;
          }
        }
      }
      WinEndEnumWindows (Enumeration);
    }

    // Узнаем путь к приложению, создавшему окно.
    CHAR Path[SIZE_OF_PATH] = ""; GetDetectedExePath (Frame_window, Path);

    // Если его удалось определить:
    if (Path[0] != 0)
    {
      // Узнаем имя приложения, создавшего окно.
      CHAR Name[SIZE_OF_PATH] = ""; GetDetectedExeName (Frame_window, Name);

      // Составляем полный путь.
      strcat (Path, "\\"); strcat (Path, Name);

      // Загружаем значок для файла приложения.
      Icon = WinLoadFileIcon (Path, 0);

      // Загрузка длится долго, поэтому в этом случае надо заменить значок окна. При
      // повторной загрузке возможна утечка памяти, так что лучше сделать это немедленно,
      // не посылая сообщений в поток Changer.
      WinSendMsg (Frame_window, WM_SETICON, (MPARAM) Icon, 0);

      // Запоминаем, что значок был загружен с диска.
      BYTE Icon_was_loaded = 1; SetProperty (Frame_window, PRP_ICON_WAS_LOADED, &Icon_was_loaded);

      // Возвращаем значок.
      return Icon;
    }

    // Для окон постоянного размера выбираем простой значок.
    if (WindowIsDialog (Frame_window))
    {
      return Resources.Default_icons[ICON_LEAF];
    }
    // Для остальных окон - он зависит от того, можно ли переключиться в окно.
    else
    {
      HSWITCH Switch_handle = WinQuerySwitchHandle (Frame_window, NULLHANDLE);

      if (Switch_handle != NULLHANDLE) return Resources.Default_icons[ICON_LEAVES];
      else return Resources.Default_icons[ICON_LEAF];
    }

    // И наконец, значок мог быть задан в свойствах раньше.
    FindProperty (Frame_window, PRP_ICON, &Icon);
  }

  // Возврат.
  return Icon;
}
