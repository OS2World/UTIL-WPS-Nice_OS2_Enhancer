// ─── Отправляет сообщения во время передвижения изображений с помощью мыши ───

// SB_Control - полоска просмотра, Message - сообщение, New_position - новое расположение движка полоски просмотра.
VOID Scroller_PostScrollMessage (HWND SB_Control, ULONG Message, INT New_position)
{
  // Передвигаем движок полоски в заданную точку.
  WinPostMsg (SB_Control, SBM_SETPOS, (MPARAM) New_position, 0);

  // Отправляем сообщения от полоски просмотра окну, в котором она расположена.
  HWND Owner_window = WinQueryWindow (SB_Control, QW_OWNER);
  SHORT SB_Id = WinQueryWindowUShort (SB_Control, QWS_ID);

  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_SLIDERTRACK));
  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_SLIDERPOSITION));
  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_ENDSCROLL));

  // Возврат.
  return;
}

// ─── Отправляет сообщения во время передвижения изображений с помощью мыши ───

// SB_Control - полоска просмотра, Message - сообщение "WM_xSCROLL", Direction - направление, Lines - счетчик повторений.
VOID Scroller_PostDiscreteMBScrollMessage (HWND SB_Control, ULONG Message, INT Direction, INT Lines)
{
  // Узнаем размер окна полоски просмотра.
  RECT Rectangle = {0}; WinQueryWindowRect (SB_Control, &Rectangle);

  // Составляем сообщение о нажатии кнопки мыши.
  SHORT X_Point = 2; SHORT Y_Point = 2;
  if (Message == WM_VSCROLL) if (Direction == 1) Y_Point = Rectangle.yTop - 2;
  if (Message == WM_HSCROLL) if (Direction == 1) X_Point = Rectangle.xRight - 2;

  // Посылаем его полоске просмотра.
  // Сообщение надо направлять методом "Send", чтобы его нельзя было перехватить.
  for (INT Count = 0; Count < Lines; Count ++)
  {
    WinSendMsg (SB_Control, WM_BUTTON1DOWN, MRFROM2SHORT (X_Point, Y_Point), MRFROM2SHORT (HT_NORMAL, KC_NONE));
    WinSendMsg (SB_Control, WM_BUTTON1UP, MRFROM2SHORT (X_Point, Y_Point), MRFROM2SHORT (HT_NORMAL, KC_NONE));
  }

  // Возврат.
  return;
}

// ─── Отправляет сообщения во время передвижения изображений с помощью мыши ───

// SB_Control - полоска просмотра, Message - сообщение "WM_xSCROLL", Direction - направление, Lines - счетчик повторений.
VOID Scroller_PostDiscreteKbdScrollMessage (HWND SB_Control, ULONG Message, INT Direction, INT Lines)
{
  // Составляем сообщение о нажатии клавиши со стрелкой.
  BYTE Scan_code = 0;
  if (Message == WM_VSCROLL) if (Direction == 0) Scan_code = SC_DOWN;
  if (Message == WM_VSCROLL) if (Direction == 1) Scan_code = SC_UP;
  if (Message == WM_HSCROLL) if (Direction == 0) Scan_code = SC_LEFT;
  if (Message == WM_HSCROLL) if (Direction == 1) Scan_code = SC_RIGHT;

  MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
  MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
  ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, Scan_code, 0, 0);

  // Посылаем его полоске просмотра.
  for (INT Count = 0; Count < Lines; Count ++)
  {
    WinPostMsg (SB_Control, WM_CHAR, First_parameter_1, Second_parameter_1);
    WinPostMsg (SB_Control, WM_CHAR, First_parameter_2, Second_parameter_2);
  }

  // Возврат.
  return;
}

// ─── Отправляет сообщения во время передвижения изображений с помощью мыши ───

// Window - окно, Message - сообщение "WM_xSCROLL", Direction - направление, Lines - счетчик повторений.
VOID Scroller_PostDirectScrollMessage (HWND Window, ULONG Message, INT Direction, INT Lines)
{
  // Составляем сообщение от полоски просмотра.
  USHORT SB_Code = 0;
  if (Message == WM_VSCROLL) if (Direction == 0) SB_Code = SB_LINEDOWN;
  if (Message == WM_VSCROLL) if (Direction == 1) SB_Code = SB_LINEUP;
  if (Message == WM_HSCROLL) if (Direction == 0) SB_Code = SB_LINELEFT;
  if (Message == WM_HSCROLL) if (Direction == 1) SB_Code = SB_LINERIGHT;

  // Посылаем его в окно.
  for (INT Count = 0; Count < Lines; Count ++)
   WinPostMsg (Window, Message, 0, MPFROM2SHORT (0, SB_Code));

  // Возврат.
  return;
}
