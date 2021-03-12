
// ��� ������, ᢮����� �� ���� ���

// �����頥��� ���祭��: 1 ��� 0.
BYTE KbdMouse_MouseIsBusy (VOID)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ���� �⪫�祭� - ������.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS))
  {
    // ������.
    return 0;
  }

  // �᫨ ��� �� ���� ������ ��� ����� - ��⠥�, �� ���� �����.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED)
  {
    // ������.
    return 1;
  }

  // ������.
  return 0;
}

// ��� ������, ������ �� ��᪮�쪮 ������ ��� ���

// �����頥��� ���祭��: 1 ��� 0.
BYTE KbdMouse_MouseIsUnderPressure (VOID)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ���� �⪫�祭� - ������.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS)) return 0;

  // ������, ᪮�쪮 ������ �����.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED)
  {
    if (WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
        WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED) return 1;
  }

  // ������.
  return 0;
}

// ��� ������, ����� �� ������ ���{1} ���

// Button_number - ����� ������: 1, 2 ��� 3.
BYTE KbdMouse_MouseButtonIsPressed (INT Button_number)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ���� �⪫�祭� - ������.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS)) return 0;

  {
    // ������, ����� �� ������.
    INT Button_VK_Code = VK_BUTTON1;

    switch (Button_number)
    {
      case 1: Button_VK_Code = VK_BUTTON1; break;
      case 2: Button_VK_Code = VK_BUTTON2; break;
      case 3: Button_VK_Code = VK_BUTTON3; break;
    }

    if (WinGetKeyState (Desktop, Button_VK_Code) & KEY_IS_PRESSED) return 1;
  }

  // ������.
  return 0;
}

// ��� ������, ����� �� ������ ���{2} ���

BYTE KbdMouse_MouseButtonIsPressed (VOID)
{
  // �஢��塞 �� ������.
  if (KbdMouse_MouseButtonIsPressed (1) ||
      KbdMouse_MouseButtonIsPressed (2) ||
      KbdMouse_MouseButtonIsPressed (3)) return 1;

  return 0; 
}

// ��� ��⠭�������� 㪠��⥫� ��� ⠪��, ����� �� ������ ���� ��� ���� ��� ��� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID KbdMouse_ShakePointer (HWND Desktop)
{
  // � ����, ��� ����� �ᯮ����� 㪠��⥫�, ������ ���� ��᫠�� ᮮ�饭��
  // WM_MOUSEMOVE. �� �⮬ �㤥� ��⠭����� 㪠��⥫� ��� �⮣� ����.
  WinSetCapture (Desktop, WinQueryActiveWindow (Desktop));
  WinSetCapture (Desktop, NULLHANDLE);

  // ������.
  return;
}

// ��� ��⠭�������� 㪠��⥫� ��� �� 㬮�砭�� ���

VOID KbdMouse_ResetPointer (VOID)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �����⥫� ����� ���� �� �����. �����뢠�� ���.
  LONG Pointer_is_hidden = WinQuerySysValue (Desktop, SV_POINTERLEVEL);
  if (Pointer_is_hidden) WinShowPointer (Desktop, 1);

  // ��⠭�������� 㪠��⥫� "��५��".
  WinSetPointer (Desktop, WinQuerySysPointer (Desktop, SPTR_ARROW, 0));

  // �����뢠�� 㪠��⥫� ���, ������� ��� ����, ��� ����� �� �ᯮ�����.
  KbdMouse_ShakePointer (Desktop);

  // ������.
  return;
}
