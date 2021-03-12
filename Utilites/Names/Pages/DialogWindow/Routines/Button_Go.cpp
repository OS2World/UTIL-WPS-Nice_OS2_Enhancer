
// ��� �믮���� ����⢨� ���

VOID DialogWindow_GoButton (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // �᫨ ��⮪ 㦥 ࠡ�⠥� - ������.
  if (Names.Processing)
  {
    WinAlarm (HWND_DESKTOP, WA_NOTE);
    return;
  }

  // ���������� ��⠫��, � ���ண� ���� ����� ��ࠡ���.
  Names.Task.Root_directory[0] = 0;
  WinQueryDlgItemText (Window, ID_MAINWNDFORM_PATH_FIELD, SIZE_OF_PATH, Names.Task.Root_directory);

  // �᫨ ��� �� 㪠��� - ������.
  if (Names.Task.Root_directory[0] == 0 || Names.Task.Root_directory[1] != ':') return;

  // ������ ����� �㪢� ���������.
  Names.Task.Root_directory[1] = 0;
  UpperCase (Names.Task.Root_directory);
  Names.Task.Root_directory[1] = ':';

  {
    // �᫨ ��� �஢����� ����� - ������.
    INT Length = strlen (Names.Task.Root_directory);

    if (Length == 2 || Length == 3)
     if (!PermissionForDriveCheck (Names.Task.Root_directory, 1))
      return;

    // �᫨ ��� ������㯥� - ������.
    if (!DriveIsAvailable (Names.Task.Root_directory))
    {
      if (Names.Settings.Code_page == RUSSIAN)
       WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Drive_is_unavailable, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
      else
       WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Drive_is_unavailable, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);

      return;
    }

    // ���ࠥ� ࠧ����⥫� � ���� ��ப�.
    CutLastSlash (Names.Task.Root_directory);
  }

  // ��ࠡ��뢠�� 䠩��.
  StartProcessing ();

  // ������.
  return;
}

