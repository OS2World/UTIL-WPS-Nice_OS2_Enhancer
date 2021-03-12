
// ��� ����砥� �뤥����� ��ப � ⥪�⮢�� ���� ���

// Frame_window - ⥪�⮢�� ����.
VOID Clipper_BeginVIOMarking (HWND Frame_window)
{
  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // �᫨ ���� ��� - ������.
  if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

  // �᫨ � ���� ���� ��ப� ��� ����祭�� �뤥����� � ����⢨� � �����:
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK) &&
      MenuItemIsPresent (SysMenu_window, SM_VIO_MOUSE))
  {
    // �᫨ ��ப� ���� ��� ����祭�� �뤥����� �� ��࠭�:
    if (!MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
    {
      // ����砥� �뤥����� � ������� ���.
      WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MOUSE, MPFROM2SHORT (CMDSRC_MENU, 0));

      // �᫨ ���� �� �����:
      if (!MouseIsBusy ())
      {
        // ����砥� �뤥����� � ������� ����������.
        WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MARK, MPFROM2SHORT (CMDSRC_MENU, 0));

        // ����뢠�� 㪠��⥫� ��� � ���ﭨ� �� 㬮�砭��, �⮡� ���짮��⥫� ����⨫, �� �뤥����� ��砫���.
        ShakePointer (QueryDesktopWindow ());
      }
    }
  }

  // ������.
  return;
}

// ��� ���뫠�� � ���� ������ "Ctrl + V" ���

VOID Clipper_PostCtrlV (HWND Input_window)
{
  // �᫨ ���� �� ������ ��� ��� ��� - ������.
  if (!Input_window) return;
  if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

  // ������ ��⠭�� ������.
  CHAR New_character_code = 'V';
  BYTE New_scan_code = SC_V;
  LONG New_modifiers = KC_CTRL;

  // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
  MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
  MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

  ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers);

  // ���塞 ���ﭨ� ���������� �� �६� ����⢨� ᮮ�饭��.
  QMSG Message; bzero (&Message, sizeof (Message));
  Message.msg = WM_CHAR; Message.hwnd = Input_window;
  ChangePMKeyboardState (&Message, New_scan_code, New_modifiers);

  // ���뫠�� � ���� ᮮ�饭�� � ����⨨ ������.
  WinPostMsg (Input_window, WM_CHAR, First_parameter_1, Second_parameter_1);

  // ���뫠�� � ���� ᮮ�饭�� �� �⦠⨨ ������.
  WinPostMsg (Input_window, WM_CHAR, First_parameter_2, Second_parameter_2);

  // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, Clipboard ����� �㤥� ����⠭�����.
  HMQ Message_queue = WinQueryWindowULong (Input_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_RESTORE_CLIPBOARD, 0);

  // ������.
  return;
}
