// ─── Заменяет состояние клавиатуры для посылки сообщения о нажатии клавиши ───

// Message - сообщение, Scan_code - клавиша, Modifiers - клавиши Ctrl, Alt и Shift.
// Post_marker_message означает, что в очередь окна надо направить сообщение WM_MARK.
// Если переменная Message не задана - надо сбросить клавиши в исходное состояние.
VOID KbdState_ChangePMKeyboardState (PQMSG Message, SHORT Scan_code, SHORT Modifiers, BYTE Post_marker_message = 1)
{
  // Узнаем состояние клавиатуры.
  HWND Desktop = QueryDesktopWindow ();

  BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
  WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

  // Включаем или выключаем Ctrl, Alt и Shift.
  if (Message != NULL)
  {
    if (Scan_code == SC_INSERT) Keyboard_state[VK_INSERT] = SET_KEY_PRESSED; else Keyboard_state[VK_INSERT] = 0;
    if (Scan_code == SC_DELETE) Keyboard_state[VK_DELETE] = SET_KEY_PRESSED; else Keyboard_state[VK_DELETE] = 0;
    if (Scan_code == SC_BACKSPACE) Keyboard_state[VK_BACKSPACE] = SET_KEY_PRESSED; else Keyboard_state[VK_BACKSPACE] = 0;

    if (Modifiers & KC_CTRL) Keyboard_state[VK_CTRL] = SET_KEY_PRESSED; else Keyboard_state[VK_CTRL] = 0;
    if (Modifiers & KC_ALT) Keyboard_state[KC_ALT] = SET_KEY_PRESSED; else Keyboard_state[KC_ALT] = 0;
    if (Modifiers & KC_SHIFT) Keyboard_state[VK_SHIFT] = SET_KEY_PRESSED; else Keyboard_state[VK_SHIFT] = 0;
  }
  // Или восстанавливаем настоящие значения.
  else
  {
    if (KeyIsPressed (SC_INSERT)) Keyboard_state[VK_INSERT] = SET_KEY_PRESSED; else Keyboard_state[VK_INSERT] = 0;
    if (KeyIsPressed (SC_DELETE)) Keyboard_state[VK_DELETE] = SET_KEY_PRESSED; else Keyboard_state[VK_DELETE] = 0;
    if (KeyIsPressed (SC_BACKSPACE)) Keyboard_state[VK_BACKSPACE] = SET_KEY_PRESSED; else Keyboard_state[VK_BACKSPACE] = 0;

    if (CtrlIsPressed ()) Keyboard_state[VK_CTRL] = SET_KEY_PRESSED; else Keyboard_state[VK_CTRL] = 0;
    if (AltIsPressed ()) Keyboard_state[KC_ALT] = SET_KEY_PRESSED; else Keyboard_state[KC_ALT] = 0;
    if (ShiftIsPressed ()) Keyboard_state[VK_SHIFT] = SET_KEY_PRESSED; else Keyboard_state[VK_SHIFT] = 0;
  }

  // Сбрасываем все сведения о кнопках мыши. Это необходимо при вставке текста с помощью
  // средней кнопки, когда сообщения сбрасываются, и данные, что кнопка нажата, остаются.
  Keyboard_state[VK_BUTTON1] = 0;
  Keyboard_state[VK_BUTTON2] = 0;
  Keyboard_state[VK_BUTTON3] = 0;

  // Устанавливаем новое состояние клавиатуры.
  WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);

  // Запоминаем, что состояние клавиатуры изменено.
  if (Message != NULL)
  {
    // Запоминаем, что состояние клавиатуры изменено.
    KbdState.Keyboard_state_is_changed = 1;

    // Если в очередь окна надо направить сообщение:
    if (Post_marker_message)
    {
      // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, состояние можно будет вернуть назад.
      HMQ Message_queue = WinQueryWindowULong (Message->hwnd, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_KBD_MODIFIERS, 0);
    }
  }
  // Или запоминаем, что состояние клавиатуры восстановлено.
  else
  {
    // Запоминаем, что состояние клавиатуры восстановлено.
    KbdState.Keyboard_state_is_changed = 0;
  }

  // Возврат.
  return;
}

// ─── Восстанавливает состояние клавиатуры ───

VOID KbdState_RestorePMKeyboardState (VOID)
{
  // Восстанавливаем состояние клавиатуры.
  if (KbdState.Keyboard_state_is_changed) KbdState_ChangePMKeyboardState (NULL, 0, 0);

  // Возврат.
  return;
}

// ─── Узнает, изменено ли состояние клавиатуры ───

BYTE KbdState_PMKeyboardStateIsChanged (VOID)
{
  // Проверяем, изменено ли состояние клавиатуры.
  if (KbdState.Keyboard_state_is_changed) return 1;

  // Возврат.
  return 0;
}