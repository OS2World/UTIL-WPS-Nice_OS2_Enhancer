
// ─── Включает выделение строк в текстовом окне ───

// Frame_window - текстовое окно.
VOID Clipper_BeginVIOMarking (HWND Frame_window)
{
  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Если окна нет - возврат.
  if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

  // Если в меню есть строки для включения выделения и действий с мышью:
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK) &&
      MenuItemIsPresent (SysMenu_window, SM_VIO_MOUSE))
  {
    // Если строка меню для включения выделения не выбрана:
    if (!MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
    {
      // Включаем выделение с помощью мыши.
      WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MOUSE, MPFROM2SHORT (CMDSRC_MENU, 0));

      // Если мышь не нажата:
      if (!MouseIsBusy ())
      {
        // Включаем выделение с помощью клавиатуры.
        WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MARK, MPFROM2SHORT (CMDSRC_MENU, 0));

        // Сбрасываем указатель мыши в состояние по умолчанию, чтобы пользователь заметил, что выделение началось.
        ShakePointer (QueryDesktopWindow ());
      }
    }
  }

  // Возврат.
  return;
}

// ─── Посылает в окно клавиши "Ctrl + V" ───

VOID Clipper_PostCtrlV (HWND Input_window)
{
  // Если окно не задано или его нет - возврат.
  if (!Input_window) return;
  if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

  // Задаем сочетание клавиш.
  CHAR New_character_code = 'V';
  BYTE New_scan_code = SC_V;
  LONG New_modifiers = KC_CTRL;

  // Составляем сообщение о нажатии клавиши.
  MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
  MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

  ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers);

  // Меняем состояние клавиатуры на время действия сообщения.
  QMSG Message; bzero (&Message, sizeof (Message));
  Message.msg = WM_CHAR; Message.hwnd = Input_window;
  ChangePMKeyboardState (&Message, New_scan_code, New_modifiers);

  // Посылаем в окно сообщение о нажатии клавиши.
  WinPostMsg (Input_window, WM_CHAR, First_parameter_1, Second_parameter_1);

  // Посылаем в окно сообщение об отжатии клавиши.
  WinPostMsg (Input_window, WM_CHAR, First_parameter_2, Second_parameter_2);

  // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, Clipboard можно будет восстановить.
  HMQ Message_queue = WinQueryWindowULong (Input_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_RESTORE_CLIPBOARD, 0);

  // Возврат.
  return;
}
