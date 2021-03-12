
// ��� �஢����, ����㯭� �� ���� ���

// Window - ����, ���஥ ���� �஢����.
BYTE WindowTypes_WindowIsPresent (HWND Window)
{
  // �஢��塞, ���� �� ����� ⠪�� ����.
  if (Window == NULLHANDLE) return 0;
  if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return 0;

  // �஢��塞, ������ �� ���.
  if (!WinIsWindowVisible (Window)) return 0;

  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // �஢��塞 ���.
  if (Rectangle.yTop <= 1 || Rectangle.xRight <= 1) return 0;

  // ������.
  return 1;
}

// ��� ������ ��� ���� ���

// Window - ����.
LONG WindowTypes_WindowType (HWND Window)
{
  // �᫨ ���� �� ������ - ������.
  if (Window == NULLHANDLE) return WT_UNKNOWN;

  // �᫨ �� ���� ࠡ�祣� �⮫� - ������.
  if (IsDesktopWindow (Window)) return WT_UNKNOWN;

  // �� ����� ���� ���� ࠬ��.
  if (IsFrameWindow (Window)) return WT_BORDER;

  // ���� ���������, ���⨭�� � ���� ����� ����� ࠧ���� �����.
  // � ��� ���� த�⥫�᪮� ���� - ࠡ�稩 �⮫ ��� ���� ࠬ��.
  HWND Parent_window = WinQueryWindow (Window, QW_PARENT);

  if (IsFrameWindow (Parent_window))
  {
    if (WinWindowFromID (Parent_window, FID_SYSMENU) == Window) return WT_SYSMENU;
    if (WinWindowFromID (Parent_window, FID_TITLEBAR) == Window) return WT_TITLEBAR;
    if (WinWindowFromID (Parent_window, FID_MINMAX) == Window) return WT_MINMAX;
    if (WinWindowFromID (Parent_window, FID_MENU) == Window) return WT_MENU;
    if (WinWindowFromID (Parent_window, FID_CLIENT) == Window) return WT_CLIENT;
  }

  // ������.
  return WT_UNKNOWN;
}

// ��� ������, ��� �룫廊� ࠬ�� ���� ���

// Frame_window - ���� ࠬ��. �����頥��� ���祭�� - ��� ࠬ��.
LONG WindowTypes_FrameType (HWND Frame_window)
{
  // ������, ��� �룫廊� ࠬ�� ����.
  ULONG Frame_style = WinQueryWindowULong (Frame_window, QWL_STYLE);

  // �᫨ ���� ����� ������ ࠬ�� - �����頥� ���祭��.
  if (Frame_style & FS_SIZEBORDER) return FT_NORMAL;

  // �᫨ �� ���� ����ﭭ��� ࠧ��� ��� ���᪮� ���� - ᬮ�ਬ, ���� �� � ���� ���������.
  if (Frame_style & FS_DLGBORDER)
  {
    // ������ ���� ���������.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // �᫨ ���� ��������� ��� - �� ���᪮� ����.
    if (TitleBar_window == NULLHANDLE) return FT_FLAT;

    // �᫨ ���� ��������� �� ��������:
    if (!WindowTypes_WindowIsPresent (TitleBar_window))
    {
      // ������ �ᯮ������� ���� ࠬ�� � ��� ���ﭨ�.
      SWP Window_state = {0}; WinQueryWindowPos (Frame_window, &Window_state);

      // �᫨ ���� �� ���� � �� 㬥��襭� � ���箪 - �� ���᪮� ����.
      if (!(Window_state.fl & SWP_HIDE))
       if (!(Window_state.fl & SWP_MINIMIZE))
        return FT_FLAT;
    }

    // ���� - �� ���� ����ﭭ��� ࠧ���.
    return FT_CONST;
  }

  // ���� ����� ����� ࠬ�� � 1 ���.
  if (Frame_style & FS_BORDER) return FT_POINT;

  // � ���� ����� ���� ⮫쪮 ���������.
  if (WinWindowFromID (Frame_window, FID_TITLEBAR) != NULLHANDLE) return FT_NOFRAME;

  // � ��㣮� ��砥 ��⠥�, �� ࠬ�� �� ���ᮢ���.
  return FT_RECT;
}


