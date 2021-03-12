
// ─── Проверяет, доступно ли окно ───

// Window - окно, которое надо проверить.
BYTE WindowTypes_WindowIsPresent (HWND Window)
{
  // Проверяем, есть ли вообще такое окно.
  if (Window == NULLHANDLE) return 0;
  if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return 0;

  // Проверяем, видимо ли оно.
  if (!WinIsWindowVisible (Window)) return 0;

  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // Проверяем его.
  if (Rectangle.yTop <= 1 || Rectangle.xRight <= 1) return 0;

  // Возврат.
  return 1;
}

// ─── Узнает вид окна ───

// Window - окно.
LONG WindowTypes_WindowType (HWND Window)
{
  // Если окно не задано - возврат.
  if (Window == NULLHANDLE) return WT_UNKNOWN;

  // Если это окно рабочего стола - возврат.
  if (IsDesktopWindow (Window)) return WT_UNKNOWN;

  // Это может быть окно рамки.
  if (IsFrameWindow (Window)) return WT_BORDER;

  // Окна заголовка, картинки и меню могут иметь различные имена.
  // У них есть родительское окно - рабочий стол или окно рамки.
  HWND Parent_window = WinQueryWindow (Window, QW_PARENT);

  if (IsFrameWindow (Parent_window))
  {
    if (WinWindowFromID (Parent_window, FID_SYSMENU) == Window) return WT_SYSMENU;
    if (WinWindowFromID (Parent_window, FID_TITLEBAR) == Window) return WT_TITLEBAR;
    if (WinWindowFromID (Parent_window, FID_MINMAX) == Window) return WT_MINMAX;
    if (WinWindowFromID (Parent_window, FID_MENU) == Window) return WT_MENU;
    if (WinWindowFromID (Parent_window, FID_CLIENT) == Window) return WT_CLIENT;
  }

  // Возврат.
  return WT_UNKNOWN;
}

// ─── Узнает, как выглядит рамка окна ───

// Frame_window - окно рамки. Возвращаемое значение - вид рамки.
LONG WindowTypes_FrameType (HWND Frame_window)
{
  // Узнаем, как выглядит рамка окна.
  ULONG Frame_style = WinQueryWindowULong (Frame_window, QWL_STYLE);

  // Если окно имеет обычную рамку - возвращаем значение.
  if (Frame_style & FS_SIZEBORDER) return FT_NORMAL;

  // Если это окно постоянного размера или плоское окно - смотрим, есть ли у него заголовок.
  if (Frame_style & FS_DLGBORDER)
  {
    // Узнаем окно заголовка.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // Если окна заголовка нет - это плоское окно.
    if (TitleBar_window == NULLHANDLE) return FT_FLAT;

    // Если окно заголовка не показано:
    if (!WindowTypes_WindowIsPresent (TitleBar_window))
    {
      // Узнаем расположение окна рамки и его состояние.
      SWP Window_state = {0}; WinQueryWindowPos (Frame_window, &Window_state);

      // Если окно не скрыто и не уменьшено в значок - это плоское окно.
      if (!(Window_state.fl & SWP_HIDE))
       if (!(Window_state.fl & SWP_MINIMIZE))
        return FT_FLAT;
    }

    // Иначе - это окно постоянного размера.
    return FT_CONST;
  }

  // Окно может иметь рамку в 1 точку.
  if (Frame_style & FS_BORDER) return FT_POINT;

  // У него может быть только заголовок.
  if (WinWindowFromID (Frame_window, FID_TITLEBAR) != NULLHANDLE) return FT_NOFRAME;

  // В другом случае считаем, что рамка не нарисована.
  return FT_RECT;
}


