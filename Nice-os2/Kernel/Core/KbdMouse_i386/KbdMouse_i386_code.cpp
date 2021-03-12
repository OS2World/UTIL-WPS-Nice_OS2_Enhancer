#ifndef INCLUDED_BY_SHELL

// ��� �����頥� ��ன ��� ������ ���

// Scan_code - ��� ������.
INT Krnl_KbdMouse_i386_GetVKFromSC (INT Scan_code)
{
  // �����頥� ��� VK_* ���� ��� SC_*.
  switch (Scan_code)
  {
    case SC_ESC:         return VK_ESC;       break;

    case SC_F1:          return VK_F1;        break;
    case SC_F2:          return VK_F2;        break;
    case SC_F3:          return VK_F3;        break;
    case SC_F4:          return VK_F4;        break;
    case SC_F5:          return VK_F5;        break;
    case SC_F6:          return VK_F6;        break;
    case SC_F7:          return VK_F7;        break;
    case SC_F8:          return VK_F8;        break;
    case SC_F9:          return VK_F9;        break;
    case SC_F10:         return VK_F10;       break;
    case SC_F11:         return VK_F11;       break;
    case SC_F12:         return VK_F12;       break;

    case SC_PRSCR:       return VK_PRINTSCRN; break;
    case SC_SYSRQ:       return VK_SYSRQ;     break;
    case SC_SCRLLOCK:    return VK_SCRLLOCK;  break;
    case SC_PAUSE:       return VK_PAUSE;     break;
    case SC_BREAK:       return VK_BREAK;     break;

    case SC_BACKSPACE:   return VK_BACKSPACE; break;

    case SC_TAB:         return VK_TAB;       break;
    case SC_NEWLINE:     return VK_NEWLINE;   break;

    case SC_CAPSLOCK:    return VK_CAPSLOCK;  break;

    case SC_LEFT_SHIFT:  return VK_SHIFT;     break;
    case SC_RIGHT_SHIFT: return VK_SHIFT;     break;

    case SC_LEFT_CTRL:   return VK_CTRL;      break;
    case SC_LEFT_ALT:    return VK_ALT;       break;
    case SC_SPACE:       return VK_SPACE;     break;
    case SC_RIGHT_ALT:   return VK_ALTGRAF;   break;
    case SC_RIGHT_CTRL:  return VK_CTRL;      break;

    case SC_LEFT:        return VK_LEFT;      break;
    case SC_DOWN:        return VK_DOWN;      break;
    case SC_RIGHT:       return VK_RIGHT;     break;
    case SC_UP:          return VK_UP;        break;

    case SC_INSERT:      return VK_INSERT;    break;
    case SC_HOME:        return VK_HOME;      break;
    case SC_PAGEUP:      return VK_PAGEUP;    break;
    case SC_DELETE:      return VK_DELETE;    break;
    case SC_END:         return VK_END;       break;
    case SC_PAGEDOWN:    return VK_PAGEDOWN;  break;

    case SC_NUMLOCK:     return VK_NUMLOCK;   break;
    case SC_NUM_ENTER:   return VK_ENTER;     break;
  }

  // ������.
  return 0;
}

// ��� ���⠢��� ᮮ�饭�� WM_CHAR ���

// ��६���� 㪠�뢠�� �� ���� ᮮ�饭�� WM_CHAR, ��� ������ � �㪢�.
VOID Krnl_KbdMouse_i386_ComposeWMCharMessage (PMPARAM mp1_down, PMPARAM mp2_down, PMPARAM mp1_up, PMPARAM mp2_up, INT Scan_code, BYTE Character, LONG Modifiers)
{
  // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
  SHORT State = KC_SCANCODE; if (Character != 0) State |= KC_CHAR;
  Modifiers &= (KC_CTRL | KC_ALT | KC_SHIFT); State |= Modifiers;

  SHORT Count_and_scan_code = MAKESHORT (1, Scan_code);
  SHORT Key = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code); if (Key != 0) State |= KC_VKEY;

  if (mp1_down != NULL) *mp1_down = MRFROM2SHORT (State, Count_and_scan_code);
  if (mp2_down != NULL) *mp2_down = MRFROM2SHORT (Character, Key);

  // ���⠢�塞 ᮮ�饭�� �� �⦠⨨ ������.
  State |= KC_KEYUP; if (!Modifiers) State |= KC_LONEKEY;

  if (mp1_up != NULL) *mp1_up = MRFROM2SHORT (State, Count_and_scan_code);
  if (mp2_up != NULL) *mp2_up = MRFROM2SHORT (Character, Key);

  // ������.
  return;
}

// ��� ���⠢��� ᮮ�饭�� WM_CHAR ��� ⥪�⮢��� ���� ���

// ��६���� 㪠�뢠�� �� ���� ᮮ�饭�� WM_CHAR, ��� ������ � �㪢�.
VOID Krnl_KbdMouse_i386_ComposeWMCharMessageForVIOWindow (PMPARAM mp1_down, PMPARAM mp2_down, INT Scan_code, BYTE Character)
{
  // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
  // C���饭�� �� �⦠⨨ ������ ���뫠�� �����.
  SHORT Fixed_state_for_VIO = KC_SCANCODE;

  SHORT Count_and_scan_code = MAKESHORT (1, Scan_code);
  SHORT Key = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code);

  if (mp1_down != NULL) *mp1_down = MRFROM2SHORT (Fixed_state_for_VIO, Count_and_scan_code);
  if (mp2_down != NULL) *mp2_down = MRFROM2SHORT (Character, Key);

  // ������.
  return;
}

// ��� �����ࠥ� ���室�騩 �᪮�⥫� ��� ᮮ�饭�� WM_CHAR, �᫨ ��� ����� �८�ࠧ����� � WM_COMMAND ���

// Main_window - ������� ���� �ਫ������, Scan_code - ��� ������, Modifiers - �������⥫�� ������.
LONG Krnl_KbdMouse_i386_FindRelatedWMCommandAccelerator (HWND Main_window, INT Scan_code, LONG Modifiers)
{
  // �᫨ ���� �� 㪠���� - ������.
  if (Main_window == NULLHANDLE) return 0;

  // ������ �ਫ������, ᮧ���襥 ����.
  HAB Application = WinQueryAnchorBlock (Main_window);

  // ������, ������ �� �᪮�⥫� ��� �⮣� ����.
  HACCEL Accelerators = WinQueryAccelTable (Application, Main_window);

  // �᫨ ��� ����:
  if (Accelerators != NULLHANDLE)
  {
    // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
    MPARAM First_parameter = 0; MPARAM Second_parameter = 0;
    Krnl_KbdMouse_i386_ComposeWMCharMessage (&First_parameter, &Second_parameter, NULL, NULL, Scan_code, 0, Modifiers);

    // �஡㥬 �८�ࠧ����� ���.
    QMSG WMCommand = { Main_window, WM_CHAR, First_parameter, Second_parameter, 0, 0, 0 };
    WinTranslateAccel (Application, Main_window, Accelerators, &WMCommand);

    // �᫨ �� 㤠���� ᤥ���� - �����頥� �᪮�⥫�.
    if (WMCommand.msg == WM_COMMAND) return (LONG) WMCommand.mp1;
  }

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� ������ ���

// Scan_code - ��� ������.
BYTE Krnl_KbdMouse_i386_KeyIsPressed (INT Scan_code)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ������ ����� - �� � ���浪�.
  // �஢����� V-��� ����� �����, ⠪ ��� ��� ���ﭨ� ������ ����� ᠬ ����⥫�.
  // �� 㤠������ �믮������ �ਫ������ (remote access) ��� ��⮤ �ᥣ�� ��୥� "���".
  if (WinGetPhysKeyState (Desktop, Scan_code) & KEY_IS_PRESSED) return 1;

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� ��४���⥫� ���

// Scan_code - ��� ������.
BYTE Krnl_KbdMouse_i386_KeyIsToggled (INT Scan_code)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // ������ V-��� ������.
  // �஢�ઠ �����饣� ���� ࠡ���� �� �㤥�.
  INT VK_Code = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code);

  // �᫨ �� �����⥭ - �஢��塞 ������� ��ன ࠧ.
  if (VK_Code != 0) if (WinGetKeyState (Desktop, VK_Code) & KEY_IS_TOGGLED) return 1;

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� �� �� ������ Ctrl ���

BYTE Krnl_KbdMouse_i386_CtrlIsPressed (VOID)
{
  // �஢��塞 ��� ������.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_CTRL) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_CTRL)) return 1;

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� �� �� ������ Alt ���

BYTE Krnl_KbdMouse_i386_AltIsPressed (VOID)
{
  // �஢��塞 ��� ������.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_ALT) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_ALT)) return 1;

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� �� �� ������ Shift ���

BYTE Krnl_KbdMouse_i386_ShiftIsPressed (VOID)
{
  // �஢��塞 ��� ������.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_SHIFT) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_SHIFT)) return 1;

  // ������.
  return 0;
}

// ��� ������ ���ﭨ� �� �� ������ WinKey ���

BYTE Krnl_KbdMouse_i386_WinKeyIsPressed (VOID)
{
  // �஢��塞 ��� ������.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_WINKEY) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_WINKEY)) return 1;

  // ������.
  return 0;
}

// ��� ������, ����� �� ���� � �뫠 �� ��� ����� � ��᫥���� �६� ���

// �����頥��� ���祭��: 1 ��� 0.
BYTE Krnl_KbdMouse_i386_MouseCanBeBusy (VOID)
{
  // �᫨ �����⭮ �६�, ����� ���� � ��᫥���� ࠧ �뫠 �����:
  if (Krnl_KbdMouse_i386.Last_mouse_busy_time)
  {
    // ������ ⥪�饥 �६�.
    LONG Current_time = WinGetCurrentTime (Enhancer.Application);

    // �஢��塞 ���.
    if (Current_time >= Krnl_KbdMouse_i386.Last_mouse_busy_time)
     if (Current_time - Krnl_KbdMouse_i386.Last_mouse_busy_time < 100)
      return 1;
  }

  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ���� �⪫�祭� - ������.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS))
  {
    // ��⠥�, �� �६� ��᫥����� ������ �� ���� �������⭮.
    Krnl_KbdMouse_i386.Last_mouse_busy_time = 0;

    // ������.
    return 0;
  }

  // �᫨ ��� �� ���� ������ ��� ����� - ��⠥�, �� ���� �����.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED)
  {
    // ���������� ⥪�饥 �६�.
    Krnl_KbdMouse_i386.Last_mouse_busy_time = WinGetCurrentTime (Enhancer.Application);

    // ������.
    return 1;
  }

  // ��⠥�, �� �६� ��᫥����� ������ �� ���� �������⭮.
  Krnl_KbdMouse_i386.Last_mouse_busy_time = 0;

  // ������.
  return 0;
}

#endif

