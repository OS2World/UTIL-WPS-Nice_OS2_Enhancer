#ifndef INCLUDED_BY_SHELL

// ─── Возвращает второй код клавиши ───

// Scan_code - код клавиши.
INT Krnl_KbdMouse_i386_GetVKFromSC (INT Scan_code)
{
  // Возвращаем код VK_* зная код SC_*.
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

  // Возврат.
  return 0;
}

// ─── Составляет сообщение WM_CHAR ───

// Переменные указывают на поля сообщения WM_CHAR, код клавиши и букву.
VOID Krnl_KbdMouse_i386_ComposeWMCharMessage (PMPARAM mp1_down, PMPARAM mp2_down, PMPARAM mp1_up, PMPARAM mp2_up, INT Scan_code, BYTE Character, LONG Modifiers)
{
  // Составляем сообщение о нажатии клавиши.
  SHORT State = KC_SCANCODE; if (Character != 0) State |= KC_CHAR;
  Modifiers &= (KC_CTRL | KC_ALT | KC_SHIFT); State |= Modifiers;

  SHORT Count_and_scan_code = MAKESHORT (1, Scan_code);
  SHORT Key = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code); if (Key != 0) State |= KC_VKEY;

  if (mp1_down != NULL) *mp1_down = MRFROM2SHORT (State, Count_and_scan_code);
  if (mp2_down != NULL) *mp2_down = MRFROM2SHORT (Character, Key);

  // Составляем сообщение об отжатии клавиши.
  State |= KC_KEYUP; if (!Modifiers) State |= KC_LONEKEY;

  if (mp1_up != NULL) *mp1_up = MRFROM2SHORT (State, Count_and_scan_code);
  if (mp2_up != NULL) *mp2_up = MRFROM2SHORT (Character, Key);

  // Возврат.
  return;
}

// ─── Составляет сообщение WM_CHAR для текстового окна ───

// Переменные указывают на поля сообщения WM_CHAR, код клавиши и букву.
VOID Krnl_KbdMouse_i386_ComposeWMCharMessageForVIOWindow (PMPARAM mp1_down, PMPARAM mp2_down, INT Scan_code, BYTE Character)
{
  // Составляем сообщение о нажатии клавиши.
  // Cообщение об отжатии клавиши посылать нельзя.
  SHORT Fixed_state_for_VIO = KC_SCANCODE;

  SHORT Count_and_scan_code = MAKESHORT (1, Scan_code);
  SHORT Key = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code);

  if (mp1_down != NULL) *mp1_down = MRFROM2SHORT (Fixed_state_for_VIO, Count_and_scan_code);
  if (mp2_down != NULL) *mp2_down = MRFROM2SHORT (Character, Key);

  // Возврат.
  return;
}

// ─── Подбирает подходящий ускоритель для сообщения WM_CHAR, если его можно преобразовать в WM_COMMAND ───

// Main_window - главное окно приложения, Scan_code - код клавиши, Modifiers - дополнительные клавиши.
LONG Krnl_KbdMouse_i386_FindRelatedWMCommandAccelerator (HWND Main_window, INT Scan_code, LONG Modifiers)
{
  // Если окно не указано - возврат.
  if (Main_window == NULLHANDLE) return 0;

  // Узнаем приложение, создавшее окно.
  HAB Application = WinQueryAnchorBlock (Main_window);

  // Узнаем, заданы ли ускорители для этого окна.
  HACCEL Accelerators = WinQueryAccelTable (Application, Main_window);

  // Если они есть:
  if (Accelerators != NULLHANDLE)
  {
    // Составляем сообщение о нажатии клавиши.
    MPARAM First_parameter = 0; MPARAM Second_parameter = 0;
    Krnl_KbdMouse_i386_ComposeWMCharMessage (&First_parameter, &Second_parameter, NULL, NULL, Scan_code, 0, Modifiers);

    // Пробуем преобразовать его.
    QMSG WMCommand = { Main_window, WM_CHAR, First_parameter, Second_parameter, 0, 0, 0 };
    WinTranslateAccel (Application, Main_window, Accelerators, &WMCommand);

    // Если это удалось сделать - возвращаем ускоритель.
    if (WMCommand.msg == WM_COMMAND) return (LONG) WMCommand.mp1;
  }

  // Возврат.
  return 0;
}

// ─── Узнает состояние клавиши ───

// Scan_code - код клавиши.
BYTE Krnl_KbdMouse_i386_KeyIsPressed (INT Scan_code)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если клавиша нажата - все в порядке.
  // Проверять V-код здесь нельзя, так как его состояние иногда меняет сам расширитель.
  // При удаленном выполнении приложений (remote access) этот метод всегда вернет "нет".
  if (WinGetPhysKeyState (Desktop, Scan_code) & KEY_IS_PRESSED) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает состояние переключателя ───

// Scan_code - код клавиши.
BYTE Krnl_KbdMouse_i386_KeyIsToggled (INT Scan_code)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Узнаем V-код клавиши.
  // Проверка настоящего кода работать не будет.
  INT VK_Code = Krnl_KbdMouse_i386_GetVKFromSC (Scan_code);

  // Если он известен - проверяем клавишу второй раз.
  if (VK_Code != 0) if (WinGetKeyState (Desktop, VK_Code) & KEY_IS_TOGGLED) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает состояние любой из клавиш Ctrl ───

BYTE Krnl_KbdMouse_i386_CtrlIsPressed (VOID)
{
  // Проверяем обе клавиши.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_CTRL) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_CTRL)) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает состояние любой из клавиш Alt ───

BYTE Krnl_KbdMouse_i386_AltIsPressed (VOID)
{
  // Проверяем обе клавиши.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_ALT) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_ALT)) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает состояние любой из клавиш Shift ───

BYTE Krnl_KbdMouse_i386_ShiftIsPressed (VOID)
{
  // Проверяем обе клавиши.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_SHIFT) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_SHIFT)) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает состояние любой из клавиш WinKey ───

BYTE Krnl_KbdMouse_i386_WinKeyIsPressed (VOID)
{
  // Проверяем обе клавиши.
  if (Krnl_KbdMouse_i386_KeyIsPressed (SC_LEFT_WINKEY) || Krnl_KbdMouse_i386_KeyIsPressed (SC_RIGHT_WINKEY)) return 1;

  // Возврат.
  return 0;
}

// ─── Узнает, занята ли мышь и была ли она занята в последнее время ───

// Возвращаемое значение: 1 или 0.
BYTE Krnl_KbdMouse_i386_MouseCanBeBusy (VOID)
{
  // Если известно время, когда мышь в последний раз была занята:
  if (Krnl_KbdMouse_i386.Last_mouse_busy_time)
  {
    // Узнаем текущее время.
    LONG Current_time = WinGetCurrentTime (Enhancer.Application);

    // Проверяем его.
    if (Current_time >= Krnl_KbdMouse_i386.Last_mouse_busy_time)
     if (Current_time - Krnl_KbdMouse_i386.Last_mouse_busy_time < 100)
      return 1;
  }

  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если мышь отключена - возврат.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS))
  {
    // Считаем, что время последнего нажатия на мышь неизвестно.
    Krnl_KbdMouse_i386.Last_mouse_busy_time = 0;

    // Возврат.
    return 0;
  }

  // Если хотя бы одна кнопка мыши нажата - считаем, что мышь занята.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED)
  {
    // Запоминаем текущее время.
    Krnl_KbdMouse_i386.Last_mouse_busy_time = WinGetCurrentTime (Enhancer.Application);

    // Возврат.
    return 1;
  }

  // Считаем, что время последнего нажатия на мышь неизвестно.
  Krnl_KbdMouse_i386.Last_mouse_busy_time = 0;

  // Возврат.
  return 0;
}

#endif

