// ��� ��ࠢ��� ᮮ�饭�� �� �६� ��।������� ����ࠦ���� � ������� ��� ���

// SB_Control - ����᪠ ��ᬮ��, Message - ᮮ�饭��, New_position - ����� �ᯮ������� ������ ����᪨ ��ᬮ��.
VOID Scroller_PostScrollMessage (HWND SB_Control, ULONG Message, INT New_position)
{
  // ��।������ ������ ����᪨ � �������� ���.
  WinPostMsg (SB_Control, SBM_SETPOS, (MPARAM) New_position, 0);

  // ��ࠢ�塞 ᮮ�饭�� �� ����᪨ ��ᬮ�� ����, � ���஬ ��� �ᯮ������.
  HWND Owner_window = WinQueryWindow (SB_Control, QW_OWNER);
  SHORT SB_Id = WinQueryWindowUShort (SB_Control, QWS_ID);

  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_SLIDERTRACK));
  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_SLIDERPOSITION));
  WinPostMsg (Owner_window, Message, (MPARAM) SB_Id, MPFROM2SHORT (New_position, SB_ENDSCROLL));

  // ������.
  return;
}

// ��� ��ࠢ��� ᮮ�饭�� �� �६� ��।������� ����ࠦ���� � ������� ��� ���

// SB_Control - ����᪠ ��ᬮ��, Message - ᮮ�饭�� "WM_xSCROLL", Direction - ���ࠢ�����, Lines - ���稪 ����७��.
VOID Scroller_PostDiscreteMBScrollMessage (HWND SB_Control, ULONG Message, INT Direction, INT Lines)
{
  // ������ ࠧ��� ���� ����᪨ ��ᬮ��.
  RECT Rectangle = {0}; WinQueryWindowRect (SB_Control, &Rectangle);

  // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ ���.
  SHORT X_Point = 2; SHORT Y_Point = 2;
  if (Message == WM_VSCROLL) if (Direction == 1) Y_Point = Rectangle.yTop - 2;
  if (Message == WM_HSCROLL) if (Direction == 1) X_Point = Rectangle.xRight - 2;

  // ���뫠�� ��� ����᪥ ��ᬮ��.
  // ����饭�� ���� ���ࠢ���� ��⮤�� "Send", �⮡� ��� ����� �뫮 ���墠���.
  for (INT Count = 0; Count < Lines; Count ++)
  {
    WinSendMsg (SB_Control, WM_BUTTON1DOWN, MRFROM2SHORT (X_Point, Y_Point), MRFROM2SHORT (HT_NORMAL, KC_NONE));
    WinSendMsg (SB_Control, WM_BUTTON1UP, MRFROM2SHORT (X_Point, Y_Point), MRFROM2SHORT (HT_NORMAL, KC_NONE));
  }

  // ������.
  return;
}

// ��� ��ࠢ��� ᮮ�饭�� �� �६� ��।������� ����ࠦ���� � ������� ��� ���

// SB_Control - ����᪠ ��ᬮ��, Message - ᮮ�饭�� "WM_xSCROLL", Direction - ���ࠢ�����, Lines - ���稪 ����७��.
VOID Scroller_PostDiscreteKbdScrollMessage (HWND SB_Control, ULONG Message, INT Direction, INT Lines)
{
  // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ � ��५���.
  BYTE Scan_code = 0;
  if (Message == WM_VSCROLL) if (Direction == 0) Scan_code = SC_DOWN;
  if (Message == WM_VSCROLL) if (Direction == 1) Scan_code = SC_UP;
  if (Message == WM_HSCROLL) if (Direction == 0) Scan_code = SC_LEFT;
  if (Message == WM_HSCROLL) if (Direction == 1) Scan_code = SC_RIGHT;

  MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
  MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
  ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, Scan_code, 0, 0);

  // ���뫠�� ��� ����᪥ ��ᬮ��.
  for (INT Count = 0; Count < Lines; Count ++)
  {
    WinPostMsg (SB_Control, WM_CHAR, First_parameter_1, Second_parameter_1);
    WinPostMsg (SB_Control, WM_CHAR, First_parameter_2, Second_parameter_2);
  }

  // ������.
  return;
}

// ��� ��ࠢ��� ᮮ�饭�� �� �६� ��।������� ����ࠦ���� � ������� ��� ���

// Window - ����, Message - ᮮ�饭�� "WM_xSCROLL", Direction - ���ࠢ�����, Lines - ���稪 ����७��.
VOID Scroller_PostDirectScrollMessage (HWND Window, ULONG Message, INT Direction, INT Lines)
{
  // ���⠢�塞 ᮮ�饭�� �� ����᪨ ��ᬮ��.
  USHORT SB_Code = 0;
  if (Message == WM_VSCROLL) if (Direction == 0) SB_Code = SB_LINEDOWN;
  if (Message == WM_VSCROLL) if (Direction == 1) SB_Code = SB_LINEUP;
  if (Message == WM_HSCROLL) if (Direction == 0) SB_Code = SB_LINELEFT;
  if (Message == WM_HSCROLL) if (Direction == 1) SB_Code = SB_LINERIGHT;

  // ���뫠�� ��� � ����.
  for (INT Count = 0; Count < Lines; Count ++)
   WinPostMsg (Window, Message, 0, MPFROM2SHORT (0, SB_Code));

  // ������.
  return;
}
