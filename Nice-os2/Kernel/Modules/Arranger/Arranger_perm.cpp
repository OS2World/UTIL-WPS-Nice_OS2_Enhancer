
// ─── Проверяет, можно ли выравнивать окно браузера ───

// Frame_window - окно рамки.
BYTE Arranger_PermissionForBrowsers (HWND Frame_window, BYTE Recursive_calling = 0)
{
  // Если окно не задано - возврат.
  if (Frame_window == NULLHANDLE) return 0;

  // Узнаем, как выглядит рамка окна.
  ULONG Frame_style = WinQueryWindowULong (Frame_window, QWL_STYLE);

  // Окно можно выравнивать, только если оно имеет обычную рамку.
  // Если у него другая рамка - возврат.
  if (!(Frame_style & FS_SIZEBORDER)) return 0;

  // Узнаем, есть ли окно в списке окон. 
  // Если его там нет или в него нельзя переключиться - возврат.
  if (!FrameWindowIsAccessible (Frame_window)) return 0;

  // Узнаем состояние кнопок в окне.
  LONG Buttons_state = QueryButtonsState (Frame_window, MINIMIZE_ACTION | HIDE_ACTION, 1);

  // Если у окна нет кнопки сокрытия и нет кнопки уменьшения в значок - возврат.
  if (!(Buttons_state & MINIMIZE_ACTION) && !(Buttons_state & HIDE_ACTION)) return 0;

  // Если у окна нет кнопки увеличения во весь экран - возврат.
  if (!(Buttons_state & MAXIMIZE_ACTION)) return 0;

  // Если это не рекурсивный вызов:
  if (!Recursive_calling)
  {
    // Узнаем имя приложения, создавшего окно.
    CHAR Exe_name[SIZE_OF_NAME] = ""; GetDetectedExeName (Frame_window, Exe_name);

    // Если его удалось определить:
    if (Exe_name[0] != 0)
    {
      // Считаем, что окно выравнивать можно.
      BYTE Permission = 1;

      // Перебираем окна в окне рабочего стола.
      HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
      while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
      {
        // Если это то же самое окно - продолжаем перебор окон.
        if (Window == Frame_window) continue;

        // Если это не окно рамки - продолжаем перебор окон.
        if (!IsFrameWindow (Window)) continue;

        // Узнаем имя приложения, создавшего окно.
        CHAR Exe_name_2[SIZE_OF_NAME] = ""; GetDetectedExeName (Window, Exe_name_2);
  
        // Если имена совпадают:
        if (strc (Exe_name, Exe_name_2))
        {
          // Если и другое окно можно выравнивать по тем же правилам - значит, 
          // такое же окно уже присутствует на экране и больше ничего делать не надо.
          if (Arranger_PermissionForBrowsers (Window, RECURSIVE_CALLING))
          {
            Permission = 0; break;
          }
        }
      }
      WinEndEnumWindows (Enumeration);

      // Если окно выравнивать нельзя - возврат.
      if (!Permission) return 0;
    }
  }

  // Если все проверки пройдены - действие возможно.
  return 1;
}