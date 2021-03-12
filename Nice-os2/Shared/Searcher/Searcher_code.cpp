
// ─── Находит системное окно ───

// Topic_of_search - что надо найти, Find_visible - искать только видимые окна.
HWND Searcher_FindSystemWindow (LONG Topic_of_search, BYTE Find_visible = 0)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // Считаем, что окно не найдено.
    HWND System_window = NULLHANDLE;

    // Если надо найти видимое окно и это окно скрыто - продолжаем перебор окон.
    if (Find_visible) if (!WinIsWindowVisible (Window)) continue;

    // Проверяем окно.
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

    // Если окно найдено:
    if (System_window != NULLHANDLE)
    {
      // Завершаем перебор окон.
      WinEndEnumWindows (Enumeration);

      // Возврат.
      return System_window;
    }
  }
  WinEndEnumWindows (Enumeration);

  // Возврат.
  return NULLHANDLE;
}

// ─── Находит окно приложения ───

// App_code - что надо найти, Find_visible - искать только видимые окна.
HWND Searcher_FindAppWindow (LONG App_code, BYTE Find_visible = 0)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // Считаем, что окно не найдено.
    HWND App_window = NULLHANDLE;

    // Если надо найти видимое окно и это окно скрыто - продолжаем перебор окон.
    if (Find_visible) if (!WinIsWindowVisible (Window)) continue;

    // Проверяем окно.
    if (WindowIsCreatedBy (App_code, Window)) App_window = Window;

    // Если окно найдено:
    if (App_window != NULLHANDLE)
    {
      // Завершаем перебор окон.
      WinEndEnumWindows (Enumeration);

      // Возврат.
      return App_window;
    }
  }
  WinEndEnumWindows (Enumeration);

  // Возврат.
  return NULLHANDLE;
}

// ─── Узнает, показано ли системное окно ───

// Topic_of_search - что надо найти, Find_visible - искать только видимые окна.
BYTE Searcher_SystemWindowIsPresent (LONG Topic_of_search, BYTE Find_visible = 0)
{
  // Пробуем найти окно.
  if (Searcher_FindSystemWindow (Topic_of_search, Find_visible)) return 1;
  else return 0;
}

// ─── Узнает, показано ли окно приложения ───

// App_code - что надо найти, Find_visible - искать только видимые окна.
BYTE Searcher_AppWindowIsPresent (LONG App_code, BYTE Find_visible = 0)
{
  // Пробуем найти окно.
  if (Searcher_FindAppWindow (App_code, Find_visible)) return 1;
  else return 0;
}
