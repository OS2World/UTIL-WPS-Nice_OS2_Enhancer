// ��� ��⠭�������� ��४���⥫� �� ��������� ���

VOID Controller_SetNumLock (VOID)
{
  //
  // ��� ��⮤ ����� ��뢠�� ⮫쪮 � ��⮪� ����⥫�, �� �� � ��ࠡ��稪�� ᮮ�饭��,
  // ���ࠢ�塞�� �����, ⠪ ��� �᫨ �����-� �ਫ������ �㤥� ����饭� �� ������� "Detach",
  // ��⮤ DosDevIOCtl ࠡ���� �� �㤥�, � �� ��������� ���ﭨ� ��४���⥫�� ��� ⠪ �
  // ��⠭���� �몫�祭�묨. ����ﭨ� ��� ��⠫��� ������ ����� ������ ��� 㣮���.
  //

  // ��ࢮ� ����⢨�: ���頥��� � �ࠩ���� ���������� "KBD$".
  {
    // ��⠭�������� ᮥ������� � �ࠩ��஬.
    ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
    ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

    HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
    DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

    // �᫨ �ࠩ��� �����:
    if (Keyboard)
    {
      // ������ ���ﭨ� ����������.
      SHIFTSTATE Shift_state = {0}; ULONG Length = sizeof (Shift_state); ULONG No_data = 0; APIRET Result = ERROR_OPEN_FAILED;
      Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_GETSHIFTSTATE, NULL, 0, &No_data, &Shift_state, sizeof (Shift_state), &Length);

      // �᫨ ��� ����祭�:
      if (Result == NO_ERROR)
      {
        // ����砥� ��� �몫�砥� Num Lock.
        if (Controller.Settings.Turn_Num_Lock == 1) Shift_state.fsState |=  NUMLOCK_ON;
        if (Controller.Settings.Turn_Num_Lock == 2) Shift_state.fsState &= ~NUMLOCK_ON;

        // �몫�砥� CapsLock � ScrollLock (���� ������� �����窠 ����� ���⠢��� �� "������").
        Shift_state.fsState &= ~CAPSLOCK_ON;
        Shift_state.fsState &= ~SCROLLLOCK_ON;

        // ����砥� Insert.
        Shift_state.fsState |= INSERT_ON;

        // ��⠭�������� ����� ���ﭨ� ����������.
        ULONG Length = sizeof (Shift_state); ULONG No_data = 0;
        DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSHIFTSTATE, &Shift_state, sizeof (Shift_state), &Length, NULL, 0, &No_data);
      }

      DosClose (Keyboard); Keyboard = NULLHANDLE;
    }
  }

  // ��஥ ����⢨�: ���塞 ����ன�� ������� �����窨.
  {
    // ������ ���ﭨ� ����������.
    HWND Desktop = QueryDesktopWindow ();

    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

    // ����뢠�� ���ﭨ� ��� ��४���⥫�� (���� ������� �����窠 ����� ���⠢��� �� "������").
    Keyboard_state[VK_NUMLOCK]  = 0;
    Keyboard_state[VK_CAPSLOCK] = 0;
    Keyboard_state[VK_SCRLLOCK] = 0;
    Keyboard_state[VK_INSERT]   = 0;

    // ����砥� ��� �몫�砥� Num Lock.
    if (Controller.Settings.Turn_Num_Lock == 1) Keyboard_state[VK_NUMLOCK] |= SET_KEY_TOGGLED;

    // ��⠭�������� ����� ���ﭨ� ����������.
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);

    // ��⠭�������� ����ன�� OS/2.
    WinSetSysValue (Desktop, SV_INSERTMODE, 1);
    WinSetSysValue (Desktop, SV_SETLIGHTS, 1);
  }

  // ������.
  return;
}

// ��� �몫�砥� ������ "Shift" �� ��������� ���

VOID Controller_ResetShiftKeys (VOID)
{
  //
  // ��� ��⮤ ���� ��뢠�� � ��⮪� ����⥫�, ���� "DosDevIOCtl" �� ࠡ�⠥�.
  //

  // ��ࢮ� ����⢨�: ���頥��� � �ࠩ���� ���������� "KBD$".
  {
    // ��⠭�������� ᮥ������� � �ࠩ��஬.
    ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
    ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

    HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
    DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

    // �᫨ �ࠩ��� �����:
    if (Keyboard)
    {
      // ������ ���ﭨ� ����������.
      SHIFTSTATE Shift_state = {0}; ULONG Length = sizeof (Shift_state); ULONG No_data = 0; APIRET Result = ERROR_OPEN_FAILED;
      Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_GETSHIFTSTATE, NULL, 0, &No_data, &Shift_state, sizeof (Shift_state), &Length);

      // �᫨ ��� ����祭�:
      if (Result == NO_ERROR)
      {
        // �몫�砥� Shift.
        Shift_state.fsState &= ~LEFTSHIFT;
        Shift_state.fsState &= ~RIGHTSHIFT;

        // ��⠭�������� ����� ���ﭨ� ����������.
        ULONG Length = sizeof (Shift_state); ULONG No_data = 0;
        DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSHIFTSTATE, &Shift_state, sizeof (Shift_state), &Length, NULL, 0, &No_data);
      }

      DosClose (Keyboard); Keyboard = NULLHANDLE;
    }
  }

  // ��஥ ����⢨�: ���塞 ����ன�� ������� �����窨.
  {
    // ������ ���ﭨ� ����������.
    HWND Desktop = QueryDesktopWindow ();

    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

    // ����뢠�� ���ﭨ� Shift.
    Keyboard_state[VK_SHIFT] = 0;

    // ��⠭�������� ����� ���ﭨ� ����������.
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);
  }

  // ������.
  return;
}

// ��� �믮���� "ࠧ���" ���������� ���

VOID Controller_SpeedUpKeyboard (VOID)
{
  //
  // ��� ��⮤ ���� ��뢠�� � ��⮪� ����⥫�, ���� "DosDevIOCtl" �� ࠡ�⠥�.
  //

  // ��⠭�������� ᮥ������� � �ࠩ��஬ ����������.
  ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

  HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
  DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

  // �᫨ �ࠩ��� �����:
  if (Keyboard)
  {
    // ������ ���ﭨ� ����������.
    RATEDELAY RateDelay = {0};
    RateDelay.usRate = Controller.Settings.Keyboard_rate;
    RateDelay.usDelay = 0;

    ULONG Length = sizeof (RateDelay); ULONG No_data = 0;
    DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETTYPAMATICRATE, &RateDelay, sizeof (RateDelay), &Length, NULL, 0, &No_data);

    DosClose (Keyboard); Keyboard = NULLHANDLE;
  }

  // ������.
  return;
}

// ��� ��⠭�������� ��४���⥫� �� ��������� ��� ���� VIO ���

VOID Controller_SetVIONumLock (VOID)
{
  //
  // ���� VIO �ਭ������� OS/2 Presentation Manager, �� ᠬ� �ਫ������ �ᯮ�������
  // � ��㡨�� OS/2, � ��४���⥫� ��� ��� ����� ��⠭����� ⮫쪮 �ਫ������ VIO.
  //

  // ��뢠�� �ਫ������.
  CHAR NumLock_exe[SIZE_OF_PATH] = ""; GetCurrentPath (NumLock_exe); strcat (NumLock_exe, "\\Control\\NumLock.exe");
  CHAR Error_string[1] = ""; RESULTCODES Return_codes;
  DosResetBuffer (-1); DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, NULL, NULL, &Return_codes, NumLock_exe);

  // ������.
  return;
}
