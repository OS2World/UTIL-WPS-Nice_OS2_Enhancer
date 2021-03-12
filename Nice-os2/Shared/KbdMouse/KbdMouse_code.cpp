
// ─── Узнает, свободна ли мышь ───

// Возвращаемое значение: 1 или 0.
BYTE KbdMouse_MouseIsBusy (VOID)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если мышь отключена - возврат.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS))
  {
    // Возврат.
    return 0;
  }

  // Если хотя бы одна кнопка мыши нажата - считаем, что мышь занята.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
      WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED)
  {
    // Возврат.
    return 1;
  }

  // Возврат.
  return 0;
}

// ─── Узнает, нажаты ли несколько кнопок мыши ───

// Возвращаемое значение: 1 или 0.
BYTE KbdMouse_MouseIsUnderPressure (VOID)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если мышь отключена - возврат.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS)) return 0;

  // Узнаем, сколько кнопок нажато.
  if (WinGetKeyState (Desktop, VK_BUTTON1) & KEY_IS_PRESSED)
  {
    if (WinGetKeyState (Desktop, VK_BUTTON2) & KEY_IS_PRESSED ||
        WinGetKeyState (Desktop, VK_BUTTON3) & KEY_IS_PRESSED) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Узнает, нажата ли кнопка мыши{1} ───

// Button_number - номер кнопки: 1, 2 или 3.
BYTE KbdMouse_MouseButtonIsPressed (INT Button_number)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если мышь отключена - возврат.
  if (!WinQuerySysValue (Desktop, SV_CMOUSEBUTTONS)) return 0;

  {
    // Узнаем, нажата ли кнопка.
    INT Button_VK_Code = VK_BUTTON1;

    switch (Button_number)
    {
      case 1: Button_VK_Code = VK_BUTTON1; break;
      case 2: Button_VK_Code = VK_BUTTON2; break;
      case 3: Button_VK_Code = VK_BUTTON3; break;
    }

    if (WinGetKeyState (Desktop, Button_VK_Code) & KEY_IS_PRESSED) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Узнает, нажата ли кнопка мыши{2} ───

BYTE KbdMouse_MouseButtonIsPressed (VOID)
{
  // Проверяем все кнопки.
  if (KbdMouse_MouseButtonIsPressed (1) ||
      KbdMouse_MouseButtonIsPressed (2) ||
      KbdMouse_MouseButtonIsPressed (3)) return 1;

  return 0; 
}

// ─── Устанавливает указатель мыши таким, каким он должен быть для окна под ним ───

// Desktop - окно рабочего стола.
VOID KbdMouse_ShakePointer (HWND Desktop)
{
  // В окно, над которым расположен указатель, должно быть послано сообщение
  // WM_MOUSEMOVE. При этом будет установлен указатель для этого окна.
  WinSetCapture (Desktop, WinQueryActiveWindow (Desktop));
  WinSetCapture (Desktop, NULLHANDLE);

  // Возврат.
  return;
}

// ─── Устанавливает указатель мыши по умолчанию ───

VOID KbdMouse_ResetPointer (VOID)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Указатель может быть не виден. Показываем его.
  LONG Pointer_is_hidden = WinQuerySysValue (Desktop, SV_POINTERLEVEL);
  if (Pointer_is_hidden) WinShowPointer (Desktop, 1);

  // Устанавливаем указатель "стрелка".
  WinSetPointer (Desktop, WinQuerySysPointer (Desktop, SPTR_ARROW, 0));

  // Показываем указатель мыши, заданный для окна, над которым он расположен.
  KbdMouse_ShakePointer (Desktop);

  // Возврат.
  return;
}
