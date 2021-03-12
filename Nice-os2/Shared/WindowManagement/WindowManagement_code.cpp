
// ─── Узнает, выбрано ли окно ───

// Frame_window - окно рамки.
BYTE WindowManagement_WindowIsActive (HWND Frame_window)
{
  // Если окна нет - возврат.
  if (Frame_window == NULLHANDLE) return 0;

  // Если окно скрыто - возврат.
  if (!WinIsWindowVisible (Frame_window)) return 0;

  // Узнаем родительское окно.
  HWND Parent_window = WinQueryWindow (Frame_window, QW_PARENT);

  // Проверяем окно.
  if (Frame_window == WinQueryActiveWindow (Parent_window)) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, расположено ли окно за пределами экрана ───

// Window - окно для проверки.
BYTE WindowManagement_WindowIsOutOfTheScreen (HWND Window, PSWP Window_state)
{
  // Узнаем размер экрана.
  HWND Desktop = QueryDesktopWindow ();

  INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
  INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

  // Проверяем расположение окна. В случае, если окно расположено в точке (0, 0) считаем, что оно все еще доступно.
  if (Window_state->x + Window_state->cx < 0) return 1;
  if (Window_state->y + Window_state->cy < 0) return 1;
  if (Window_state->x > X_Screen) return 1;
  if (Window_state->y > Y_Screen) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет, можно ли переключиться в окно ───

// Window - окно. Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE WindowManagement_PermissionForSwitching (HWND Window, BYTE Exclude_WPS_Shell = 1)
{
  // Если окна нет - возврат.
  if (Window == NULLHANDLE) return 0;

  // Если окно скрыто - возврат.
  if (!WinIsWindowVisible (Window)) return 0;

  // Узнаем расположение окна и его состояние.
  SWP Window_state = {0}; WinQueryWindowPos (Window, &Window_state);

  // Если окно скрыто или уменьшено в значок - переключиться нельзя, возврат.
  if (Window_state.fl & SWP_HIDE || Window_state.fl & SWP_MINIMIZE) return 0;

  // Если окно расположено за пределами экрана - переключиться нельзя, возврат.
  if (WindowManagement_WindowIsOutOfTheScreen (Window, &Window_state)) return 0;

  #ifndef INCLUDED_BY_SHELL

  // Если это окно оболочки - переключиться нельзя, возврат.
  if (Exclude_WPS_Shell) if (HasShellPlacement (Window, &Window_state)) return 0;

  #endif

  // Возврат.
  return 1;
}

// ─── Проверяет, доступно ли окно рамки ───

// Frame_window - окно рамки.
BYTE WindowManagement_FrameWindowIsAccessible (HWND Frame_window)
{
  // Если в окно нельзя переключиться из списка окон - оно недоступно.
  if (!WindowIsTouchable (Frame_window)) return 0;

  // Если это настоящее окно OS/2:
  if (!IsWindowsWindow (Frame_window))
  {
    // Узнаем окно заголовка.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // Если его нет - окно рамки недоступно.
    if (TitleBar_window == NULLHANDLE) return 0;

    // Если окно рамки видимо:
    if (WinIsWindowVisible (Frame_window))
    {
      // Узнаем расположение окна и его состояние.
      SWP Window_state = {0}; WinQueryWindowPos (Frame_window, &Window_state);

      // Если окно не скрыто и не уменьшено в значок:
      if (!(Window_state.fl & SWP_HIDE)) if (!(Window_state.fl & SWP_MINIMIZE))
      {
        // Если окно расположено за пределами экрана - оно недоступно.
        if (WindowManagement_WindowIsOutOfTheScreen (Frame_window, &Window_state)) return 0;

        // Если окно заголовка не показано - окно рамки недоступно.
        if (Window_state.x + Window_state.cx > 0)
         if (!WindowIsPresent (TitleBar_window)) return 0;
      }
    }
  }

  // Возврат.
  return 1;
}

// ─── Вызывает окно и делает его выбранным ───

// Frame_window - окно рамки, которое надо вызвать.
BYTE WindowManagement_MoveWindowAbove (HWND Frame_window)
{
  // Если окно не выбрано:
  if (!WindowManagement_WindowIsActive (Frame_window))
  {
    // Это может быть окно Win-OS/2 или Odin.
    BYTE Is_Windows_window = IsWindowsWindow (Frame_window);

    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Узнаем главное окно приложения.
    HWND Main_window = QueryMainWindow (Frame_window);

    // Если оно не найдено - вызываем то окно, что задано.
    if (Main_window == NULLHANDLE) Main_window = Frame_window;

    // Если окно скрыто - делаем его видимым.
    if (!WinIsWindowVisible (Main_window)) WinShowWindow (Main_window, 1);

    // Главное окно приложения становится выбранным.
    if (Main_window != Frame_window)
    {
      if (!Is_Windows_window) WinSetActiveWindow (Desktop, Main_window);
      else WinSetWindowPos (Main_window, NULLHANDLE, 0, 0, 0, 0, SWP_ACTIVATE);
    }

    // Окно становится выбранным.
    if (!Is_Windows_window) WinSetActiveWindow (Desktop, Frame_window);
    else WinSetWindowPos (Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_ACTIVATE);

    // Возврат.
    return 1;
  }

  // Возврат.
  return 0;
}

// ─── Узнает окно, расположенное в середине экрана ───

HWND WindowManagement_WindowInCenter (BYTE Exclude_WPS_Shell = 1)
{
  // Узнаем размер экрана.
  HWND Desktop = QueryDesktopWindow ();

  INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
  INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

  // Узнаем окно рамки, которое расположено в середине экрана.
  POINT Center_of_screen = { X_Screen / 2, Y_Screen / 2 };
  HWND Center_window = WinWindowFromPoint (Desktop, &Center_of_screen, 0);

  // Узнаем окна, которые расположены рядом с ним, а затем выбираем одно из окон.
  // В том числе должно быть найдено, например, окно VIO размером 80 x 25 клеток
  // со шрифтом 10 x 6 точек, расположенное в углу экрана размером 1024 x 768 точек.
  // Но при первой попытке поиска отступ от середины экрана должен быть небольшим,
  // иначе будет обнаружено перекрытие окон, когда окно VIO размером 80 x 25 клеток
  // со шрифтом 14 x 8 расположено над окном справочника или текстового редактора.
  // Задача может быть решена постепенным увеличением области поиска от 1/8 до 1/4.
  HWND Target_window = NULLHANDLE; INT Max_steps = 5; INT Divisor = 8;

  for (INT Step = 0; Step < Max_steps; Step ++)
  {
    INT X_Step = X_Screen / Divisor;
    INT Y_Step = Y_Screen / Divisor;

    Divisor --;

    POINT Other_point_1 = { Center_of_screen.x + X_Step, Center_of_screen.y - Y_Step };
    HWND Other_window_1 = WinWindowFromPoint (Desktop, &Other_point_1, 0);

    POINT Other_point_2 = { Center_of_screen.x - X_Step, Center_of_screen.y + Y_Step };
    HWND Other_window_2 = WinWindowFromPoint (Desktop, &Other_point_2, 0);

    POINT Other_point_3 = { Center_of_screen.x + X_Step, Center_of_screen.y + Y_Step };
    HWND Other_window_3 = WinWindowFromPoint (Desktop, &Other_point_3, 0);

    POINT Other_point_4 = { Center_of_screen.x - X_Step, Center_of_screen.y - Y_Step };
    HWND Other_window_4 = WinWindowFromPoint (Desktop, &Other_point_4, 0);

    // Если в одно из окон нельзя переключиться - стираем переменную.
    for (INT Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window == NULLHANDLE) continue;

      if (!IsFrameWindow (*Window) ||
          !WindowManagement_PermissionForSwitching (*Window, Exclude_WPS_Shell)) *Window = NULLHANDLE;
    }

    // Выбираем окно для переключения.
    for (Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window != NULLHANDLE) { Target_window = *Window; break; }
    }

    // Если ни одного окна нет или все они недоступны - продолжаем попытки.
    if (Target_window == NULLHANDLE) continue;

    // В случае, если окна перекрываются, будет найдено несколько окон.
    BYTE Overflow = 0;

    for (Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window != NULLHANDLE && *Window != Target_window) { Overflow = 1; break; }
    }

    // Если обнаружено перекрытие - возвращаем одно из окон.
    // Других попыток не делаем - увеличивать область поиска бесполезно.
    if (Overflow)
    {
      if (Center_window) return Center_window;
      if (Other_window_1) return Other_window_1;
      if (Other_window_2) return Other_window_2;
      if (Other_window_3) return Other_window_3;
      if (Other_window_4) return Other_window_4;
    }

    // Возвращаем найденное окно, если оно есть.
    if (Target_window) return Target_window;
  }

  // Возвращаем NULLHANDLE.
  return NULLHANDLE;
}

// ─── Делает выбранным окно, которое расположено в середине экрана ───

// Возвращаемое значение: 1 - окно найдено, 0 - окно не найдено.
BYTE WindowManagement_ActivateWindowInCenter (VOID)
{
  // Делаем выбранным окно в середине экрана.
  HWND Window_in_center_without_WPS = WindowManagement_WindowInCenter ();

  if (Window_in_center_without_WPS != NULLHANDLE)
  {
    WindowManagement_MoveWindowAbove (Window_in_center_without_WPS); return 1;
  }
  else
  {
    HWND Window_in_center_with_WPS = WindowManagement_WindowInCenter (0);

    if (Window_in_center_with_WPS != NULLHANDLE)
    {
      WindowManagement_MoveWindowAbove (Window_in_center_with_WPS); return 1;
    }
    else
    {
      #ifndef INCLUDED_BY_SHELL

      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_PREV_WINDOW, 0);

      #endif
    }
  }

  // Возврат.
  return 0;
}

// ─── Скрывает окно рамки, присутствующее на экране ───

// Frame_window - окно рамки, которое надо скрыть.
BYTE WindowManagement_HideWindowAway (HWND Frame_window)
{
  // Если окно и так уже недоступно - возврат.
  if (!WindowManagement_PermissionForSwitching (Frame_window)) return 0;

  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Выбираем наиболее подходящее действие.
  ULONG Suitable_action = SWP_HIDE;

  if (SysMenu_window != NULLHANDLE)
   if (MenuItemIsPresent (SysMenu_window, SC_MINIMIZE))
    if (MenuItemIsEnabled (SysMenu_window, SC_MINIMIZE))
     Suitable_action = SWP_MINIMIZE;

  if (SysMenu_window != NULLHANDLE)
   if (MenuItemIsPresent (SysMenu_window, SC_HIDE))
    if (MenuItemIsEnabled (SysMenu_window, SC_HIDE))
     Suitable_action = SWP_HIDE;

  // Прячем окно рамки.
  if (Suitable_action == SWP_MINIMIZE)
  {
    WinShowWindow (Frame_window, 0);
    WinSetWindowPos (Frame_window, NULLHANDLE, 0, 0, 0, 0, Suitable_action);
    WinShowWindow (Frame_window, 1);
  }

  if (Suitable_action == SWP_HIDE)
  {
    WinShowWindow (Frame_window, 0);
  }

  // Выбираем окно в середине экрана.
  WindowManagement_ActivateWindowInCenter ();

  // Возврат.
  return 1;
}