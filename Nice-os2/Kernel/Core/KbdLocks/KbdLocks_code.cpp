
// ��� ��뢠�� �ࠩ��� ���������� ���

BYTE KbdLocks_CallKeyboardDriverForToggleCAD (VOID)
{
  //
  // ��� � SetNumLock, ��� ��⮤ ����� ��뢠�� ⮫쪮 � ��⮪� ����⥫�, ⠪ ���
  // ��⮤ DosDevIOCtl ����砥� ����� � ���ன�⢠� ⮫쪮 �᫨ �� �맢�� �ਫ�������
  // ��� Presentation Manager. � ��ࠡ��稪�� ᮡ�⨩ �� �� ᬮ��� ࠡ���� �ࠢ��쭮,
  // �᫨ ���� ᮧ���� �ਫ�������, ���஥ ����饭� �� ������� "Detach".
  //

  // ��뢠�� �ࠩ���.
  HOTKEY Keyboard_parameters = { 0, 0, 0, 0xFFFF };

  ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

  HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
  DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

  ULONG Length = sizeof (Keyboard_parameters); ULONG No_data = 0;
  APIRET Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSESMGRHOTKEY, &Keyboard_parameters, Length, &Length, NULL, 0, &No_data);

  DosClose (Keyboard); Keyboard = NULLHANDLE;

  // �᫨ �ந��諠 �訡�� - �����頥� 0.
  if (Result != NO_ERROR) return 0;

  // �� � ���浪�, ������.
  return 1;
}

// ��� ����蠥� ��� ����頥� Ctrl + Alt + Del ���

// Allow_CAD - ࠧ���� ��� ������� ������.
VOID KbdLocks_SetCtrlAltDel (BYTE Allow_CAD)
{
  // Ctrl + Alt + Del ����� ⮫쪮 ��४�����.
  BYTE Toggle_CAD = 0;

  // �᫨ ������ ����祭� - �� ����� �⪫����.
  if (!KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) if (!Allow_CAD) Toggle_CAD = 1;

  // �᫨ ������ �몫�祭� - �� ����� �������.
  if (KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) if (Allow_CAD) Toggle_CAD = 1;

  // ��४��砥� Ctrl + Alt + Del.
  if (Toggle_CAD)
  {
    // ��४��砥� ������ � ���������� ����� ���ﭨ�.
    if (KbdLocks_CallKeyboardDriverForToggleCAD ())
    {
      if (KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled = 0;
      else KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled = 1;
    }
  }

  // ������.
  return;
}
