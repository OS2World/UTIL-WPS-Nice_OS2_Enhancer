// ��� ������� ���ﭨ� ���������� ��� ���뫪� ᮮ�饭�� � ����⨨ ������ ���

// Message - ᮮ�饭��, Scan_code - ������, Modifiers - ������ Ctrl, Alt � Shift.
// Post_marker_message ����砥�, �� � ��।� ���� ���� ���ࠢ��� ᮮ�饭�� WM_MARK.
// �᫨ ��६����� Message �� ������ - ���� ����� ������ � ��室��� ���ﭨ�.
VOID KbdState_ChangePMKeyboardState (PQMSG Message, SHORT Scan_code, SHORT Modifiers, BYTE Post_marker_message = 1)
{
  // ������ ���ﭨ� ����������.
  HWND Desktop = QueryDesktopWindow ();

  BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
  WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

  // ����砥� ��� �몫�砥� Ctrl, Alt � Shift.
  if (Message != NULL)
  {
    if (Scan_code == SC_INSERT) Keyboard_state[VK_INSERT] = SET_KEY_PRESSED; else Keyboard_state[VK_INSERT] = 0;
    if (Scan_code == SC_DELETE) Keyboard_state[VK_DELETE] = SET_KEY_PRESSED; else Keyboard_state[VK_DELETE] = 0;
    if (Scan_code == SC_BACKSPACE) Keyboard_state[VK_BACKSPACE] = SET_KEY_PRESSED; else Keyboard_state[VK_BACKSPACE] = 0;

    if (Modifiers & KC_CTRL) Keyboard_state[VK_CTRL] = SET_KEY_PRESSED; else Keyboard_state[VK_CTRL] = 0;
    if (Modifiers & KC_ALT) Keyboard_state[KC_ALT] = SET_KEY_PRESSED; else Keyboard_state[KC_ALT] = 0;
    if (Modifiers & KC_SHIFT) Keyboard_state[VK_SHIFT] = SET_KEY_PRESSED; else Keyboard_state[VK_SHIFT] = 0;
  }
  // ��� ����⠭�������� �����騥 ���祭��.
  else
  {
    if (KeyIsPressed (SC_INSERT)) Keyboard_state[VK_INSERT] = SET_KEY_PRESSED; else Keyboard_state[VK_INSERT] = 0;
    if (KeyIsPressed (SC_DELETE)) Keyboard_state[VK_DELETE] = SET_KEY_PRESSED; else Keyboard_state[VK_DELETE] = 0;
    if (KeyIsPressed (SC_BACKSPACE)) Keyboard_state[VK_BACKSPACE] = SET_KEY_PRESSED; else Keyboard_state[VK_BACKSPACE] = 0;

    if (CtrlIsPressed ()) Keyboard_state[VK_CTRL] = SET_KEY_PRESSED; else Keyboard_state[VK_CTRL] = 0;
    if (AltIsPressed ()) Keyboard_state[KC_ALT] = SET_KEY_PRESSED; else Keyboard_state[KC_ALT] = 0;
    if (ShiftIsPressed ()) Keyboard_state[VK_SHIFT] = SET_KEY_PRESSED; else Keyboard_state[VK_SHIFT] = 0;
  }

  // ����뢠�� �� ᢥ����� � ������� ���. �� ����室��� �� ��⠢�� ⥪�� � �������
  // �।��� ������, ����� ᮮ�饭�� ���뢠����, � �����, �� ������ �����, �������.
  Keyboard_state[VK_BUTTON1] = 0;
  Keyboard_state[VK_BUTTON2] = 0;
  Keyboard_state[VK_BUTTON3] = 0;

  // ��⠭�������� ����� ���ﭨ� ����������.
  WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);

  // ����������, �� ���ﭨ� ���������� ��������.
  if (Message != NULL)
  {
    // ����������, �� ���ﭨ� ���������� ��������.
    KbdState.Keyboard_state_is_changed = 1;

    // �᫨ � ��।� ���� ���� ���ࠢ��� ᮮ�饭��:
    if (Post_marker_message)
    {
      // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���ﭨ� ����� �㤥� ������ �����.
      HMQ Message_queue = WinQueryWindowULong (Message->hwnd, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_KBD_MODIFIERS, 0);
    }
  }
  // ��� ����������, �� ���ﭨ� ���������� ����⠭������.
  else
  {
    // ����������, �� ���ﭨ� ���������� ����⠭������.
    KbdState.Keyboard_state_is_changed = 0;
  }

  // ������.
  return;
}

// ��� ����⠭�������� ���ﭨ� ���������� ���

VOID KbdState_RestorePMKeyboardState (VOID)
{
  // ����⠭�������� ���ﭨ� ����������.
  if (KbdState.Keyboard_state_is_changed) KbdState_ChangePMKeyboardState (NULL, 0, 0);

  // ������.
  return;
}

// ��� ������, �������� �� ���ﭨ� ���������� ���

BYTE KbdState_PMKeyboardStateIsChanged (VOID)
{
  // �஢��塞, �������� �� ���ﭨ� ����������.
  if (KbdState.Keyboard_state_is_changed) return 1;

  // ������.
  return 0;
}