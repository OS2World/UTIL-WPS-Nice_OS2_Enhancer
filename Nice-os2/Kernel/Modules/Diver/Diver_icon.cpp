
// ��� ������ ���箪 ���� ���

// Frame_window - ���� ࠬ��.
HPOINTER Diver_QueryWindowIcon (HWND Frame_window)
{
  // ��� �������� ���� ���� ���窨 �� 㬮�砭��, �� ��⠭�������� �� �����.
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

  // ��� �������� ���� ���窨 �� 㬮�砭�� ����� ��⠭����� ࠧ � ���ᥣ��, ��ࠢ�� ᮮ�饭�� � ����.
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

  // �᫨ ���箪 �� ��࠭ - �⠢�� � �����頥� ���.
  if (Icon != NULLHANDLE)
  {
    if (DrawSystemMenusSettingIsON ())
    {
      WinPostQueueMsg (Enhancer.Modules.Changer->Message_queue, SM_CHANGE_ICON, (MPARAM) Frame_window, (MPARAM) Icon);
    }

    return Icon;
  }

  // ������ ���箪 ����.
  Icon = (HPOINTER) WinSendMsg (Frame_window, WM_QUERYICON, 0, 0);

  // �᫨ �� ���⮩ ���箪 - �⠢�� ����ࠦ���� �� 㬮�砭��.
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

  // �᫨ ���箪 �������⥭ - �����頥� ���箪 ��������, �������� ����, ��� ���箪 �� 㬮�砭��.
  // ������ ���箪 �� ��� ����� ����� - ����� ���������� ����ﭭ�� �ᮢ����, ���஥ �룫廊� ��� "�������" ࠬ��.
  if (Icon == NULLHANDLE)
  {
    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = QueryDesktopWindow ();

    // ��ᬠ�ਢ��� ��� �������楢.
    HWND Owner_window = WinQueryWindow (Frame_window, QW_FRAMEOWNER);

    while (Owner_window != Desktop && Owner_window != NULLHANDLE)
    {
      // �᫨ �������� - ���� ࠬ��:
      if (IsFrameWindow (Owner_window))
      {
        // ������ ��� ���箪.
        Icon = (HPOINTER) WinSendMsg (Owner_window, WM_QUERYICON, 0, 0);

        // �᫨ �� ���� - �����頥� ���.
        if (Icon != NULLHANDLE) return Icon;
      }

      // ������ ᫥���饣� ��������.
      Owner_window = WinQueryWindow (Owner_window, QW_FRAMEOWNER);
    }

    // ������ ������� ���� �ਫ������.
    HWND Main_window = QueryMainWindow (Frame_window);

    // �᫨ �� ��㣮� ����:
    if (Main_window != Frame_window)
    {
      // ������ ��� ���箪.
      Icon = (HPOINTER) WinSendMsg (Main_window, WM_QUERYICON, 0, 0);

      // �᫨ �� ���� - �����頥� ���.
      if (Icon != NULLHANDLE) return Icon;
    }

    // ������ ��।� ᮮ�饭�� ����.
    HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);

    // ������ ���� �����窨.
    HWND Shell_window = GetDetectedShellWindow ();

    if (Shell_window != NULLHANDLE)
    {
      // ������ ��।� ᮮ�饭�� ��� ���� �����窨.
      HMQ Shell_queue = WinQueryWindowULong (Shell_window, QWL_HMQ);

      // �᫨ ��।� ᮢ������ - �����頥� ��� ���箪.
      if (Shell_queue == Message_queue) return (HPOINTER) WinSendMsg (Shell_window, WM_QUERYICON, 0, 0);

      // �᫨ �� ���-����� ����� ��⠭�����, �� ���� ᮧ���� �����窮� - �����頥� ���箪 ���� �����窨.
      if (IsWorkplaceShellWindow (Frame_window)) return (HPOINTER) WinSendMsg (Shell_window, WM_QUERYICON, 0, 0);
    }

    {
      // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
      HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
      while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
      {
        // �᫨ �� � �� ᠬ�� ���� - �த������ ��ॡ�� ����.
        if (Window == Frame_window) continue;

        // ������ �ᯮ������� ���� � ��� ���ﭨ�.
        SWP Window_state = {0}; WinQueryWindowPos (Window, &Window_state);

        // �᫨ ���� �� ���� � �� 㬥��襭� � ���箪:
        if (!(Window_state.fl & SWP_HIDE)) if (!(Window_state.fl & SWP_MINIMIZE))
        {
          // �᫨ � �� ���� ����� ��४������� - �த������ ��ॡ�� ����.
          if (!PermissionForSwitching (Window)) continue;
        }

        // ������ ��।� ᮮ�饭�� ����.
        HMQ Window_queue = WinQueryWindowULong (Window, QWL_HMQ);

        // �᫨ ��।� ᮢ������ - 㧭��� ��� ���箪.
        if (Window_queue == Message_queue)
        {
          // ������ ���箪 ����.
          Icon = (HPOINTER) WinSendMsg (Window, WM_QUERYICON, 0, 0);

          // �᫨ �� ���� - �����頥� ���.
          if (Icon != NULLHANDLE)
          {
            // �����蠥� ��ॡ�� ����.
            WinEndEnumWindows (Enumeration);

            // �����頥� ���箪.
            return Icon;
          }
        }
      }
      WinEndEnumWindows (Enumeration);
    }

    // ������ ���� � �ਫ������, ᮧ���襬� ����.
    CHAR Path[SIZE_OF_PATH] = ""; GetDetectedExePath (Frame_window, Path);

    // �᫨ ��� 㤠���� ��।�����:
    if (Path[0] != 0)
    {
      // ������ ��� �ਫ������, ᮧ���襣� ����.
      CHAR Name[SIZE_OF_PATH] = ""; GetDetectedExeName (Frame_window, Name);

      // ���⠢�塞 ����� ����.
      strcat (Path, "\\"); strcat (Path, Name);

      // ����㦠�� ���箪 ��� 䠩�� �ਫ������.
      Icon = WinLoadFileIcon (Path, 0);

      // ����㧪� ������ �����, ���⮬� � �⮬ ��砥 ���� �������� ���箪 ����. ��
      // ����୮� ����㧪� �������� ��窠 �����, ⠪ �� ���� ᤥ���� �� ����������,
      // �� ���뫠� ᮮ�饭�� � ��⮪ Changer.
      WinSendMsg (Frame_window, WM_SETICON, (MPARAM) Icon, 0);

      // ����������, �� ���箪 �� ����㦥� � ��᪠.
      BYTE Icon_was_loaded = 1; SetProperty (Frame_window, PRP_ICON_WAS_LOADED, &Icon_was_loaded);

      // �����頥� ���箪.
      return Icon;
    }

    // ��� ���� ����ﭭ��� ࠧ��� �롨ࠥ� ���⮩ ���箪.
    if (WindowIsDialog (Frame_window))
    {
      return Resources.Default_icons[ICON_LEAF];
    }
    // ��� ��⠫��� ���� - �� ������ �� ⮣�, ����� �� ��४������� � ����.
    else
    {
      HSWITCH Switch_handle = WinQuerySwitchHandle (Frame_window, NULLHANDLE);

      if (Switch_handle != NULLHANDLE) return Resources.Default_icons[ICON_LEAVES];
      else return Resources.Default_icons[ICON_LEAF];
    }

    // � �������, ���箪 ��� ���� ����� � ᢮��⢠� ࠭��.
    FindProperty (Frame_window, PRP_ICON, &Icon);
  }

  // ������.
  return Icon;
}
