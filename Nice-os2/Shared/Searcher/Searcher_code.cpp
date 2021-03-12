
// ��� ��室�� ��⥬��� ���� ���

// Topic_of_search - �� ���� ����, Find_visible - �᪠�� ⮫쪮 ������ ����.
HWND Searcher_FindSystemWindow (LONG Topic_of_search, BYTE Find_visible = 0)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // ��⠥�, �� ���� �� �������.
    HWND System_window = NULLHANDLE;

    // �᫨ ���� ���� ������� ���� � �� ���� ���� - �த������ ��ॡ�� ����.
    if (Find_visible) if (!WinIsWindowVisible (Window)) continue;

    // �஢��塞 ����.
    if (Topic_of_search & FIND_WARPCENTER)       if (IsWarpCenterWindow (Window))     System_window = Window;
    if (Topic_of_search & FIND_WARPCENTER_MENU)  if (IsWarpCenterMenuWindow (Window)) System_window = Window;
    if (Topic_of_search & FIND_SYSTRAY)          if (IsSysTrayWindow (Window))        System_window = Window;
    if (Topic_of_search & FIND_SYSTRAY_MENU)     if (IsSysTrayMenuWindow (Window))    System_window = Window;
    if (Topic_of_search & FIND_XWP_TASKBAR)      if (IsXWPTaskBarWindow (Window))     System_window = Window;
    if (Topic_of_search & FIND_XWP_TASKBAR_MENU) if (IsXWPTaskBarMenuWindow (Window)) System_window = Window;
    if (Topic_of_search & FIND_XWP_PAGER)        if (IsXWPPagerWindow (Window))       System_window = Window;
    if (Topic_of_search & FIND_WINDOW_LIST)      if (IsWinListWindow (Window))        System_window = Window;

    if (Topic_of_search & FIND_LSWITCHER_PANEL) if (IslSwitcherWindow (Window))
    {
      INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
      INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

      SWP Window_placement = {0}; WinQueryWindowPos (Window, &Window_placement);

      if (Window_placement.x < X_Screen / 2)
      if (Window_placement.y < Y_Screen / 2)
      if (Window_placement.x + Window_placement.cx > X_Screen / 2)
      if (Window_placement.y + Window_placement.cy > Y_Screen / 2)
      {
        System_window = Window;
      }
    }

    if (Topic_of_search & FIND_SYSMSG_WINDOW) if (IsSysMsgWindow (Window))
    {
      INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
      INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

      SWP Window_placement = {0}; WinQueryWindowPos (Window, &Window_placement);

      if (Window_placement.x < X_Screen / 2)
      if (Window_placement.y < Y_Screen / 2)
      if (Window_placement.x + Window_placement.cx > X_Screen / 2)
      if (Window_placement.y + Window_placement.cy > Y_Screen / 2)
      {
        System_window = Window;
      }
    }

    #ifndef INCLUDED_BY_SHELL
    if (Topic_of_search & FIND_VIO_FONT_DIALOG) if (IsVIOFontMetricsDialog (Window)) System_window = Window;
    #endif

    // �᫨ ���� �������:
    if (System_window != NULLHANDLE)
    {
      // �����蠥� ��ॡ�� ����.
      WinEndEnumWindows (Enumeration);

      // ������.
      return System_window;
    }
  }
  WinEndEnumWindows (Enumeration);

  // ������.
  return NULLHANDLE;
}

// ��� ��室�� ���� �ਫ������ ���

// App_code - �� ���� ����, Find_visible - �᪠�� ⮫쪮 ������ ����.
HWND Searcher_FindAppWindow (LONG App_code, BYTE Find_visible = 0)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // ��⠥�, �� ���� �� �������.
    HWND App_window = NULLHANDLE;

    // �᫨ ���� ���� ������� ���� � �� ���� ���� - �த������ ��ॡ�� ����.
    if (Find_visible) if (!WinIsWindowVisible (Window)) continue;

    // �஢��塞 ����.
    if (WindowIsCreatedBy (App_code, Window)) App_window = Window;

    // �᫨ ���� �������:
    if (App_window != NULLHANDLE)
    {
      // �����蠥� ��ॡ�� ����.
      WinEndEnumWindows (Enumeration);

      // ������.
      return App_window;
    }
  }
  WinEndEnumWindows (Enumeration);

  // ������.
  return NULLHANDLE;
}

// ��� ������, �������� �� ��⥬��� ���� ���

// Topic_of_search - �� ���� ����, Find_visible - �᪠�� ⮫쪮 ������ ����.
BYTE Searcher_SystemWindowIsPresent (LONG Topic_of_search, BYTE Find_visible = 0)
{
  // �஡㥬 ���� ����.
  if (Searcher_FindSystemWindow (Topic_of_search, Find_visible)) return 1;
  else return 0;
}

// ��� ������, �������� �� ���� �ਫ������ ���

// App_code - �� ���� ����, Find_visible - �᪠�� ⮫쪮 ������ ����.
BYTE Searcher_AppWindowIsPresent (LONG App_code, BYTE Find_visible = 0)
{
  // �஡㥬 ���� ����.
  if (Searcher_FindAppWindow (App_code, Find_visible)) return 1;
  else return 0;
}
