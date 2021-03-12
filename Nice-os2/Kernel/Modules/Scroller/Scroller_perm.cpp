
// ─── Проверяет, можно ли передвигать изображение в окне с помощью мыши ───

// Window - окно. Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE Scroller_PermissionForScrolling (HWND Window)
{
  // Узнаем окно рамки.
  HWND Frame_window = QueryFrameWindow (Window);

  // Узнаем имя приложения, создавшего окно.
  CHAR Exe_name[SIZE_OF_NAME] = ""; GetDetectedExeName (Frame_window, Exe_name);

  // Если его удалось определить:
  if (Exe_name[0] != 0)
  {
    // Проверяем, есть ли приложение в списке исключений.
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_1)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_2)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_3)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_4)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_5)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_6)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_7)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.Scrolling_8)) return 0;
  }

  // Узнаем окно рабочей области для окна рамки.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  // Если оно есть:
  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно рабочей области.
    CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Window_name);

    // Проверяем, есть ли окно в списке исключений.
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_1)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_2)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_3)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_4)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_5)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_6)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_7)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.Scrolling_8)) return 0;
  }

  // Возврат.
  return 1;
}

// ─── Проверяет, можно ли передвигать изображение с помощью стрелок ───

// Window - окно. Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE Scroller_PermissionForKeyScrolling (HWND Window)
{
  // Узнаем окно рамки.
  HWND Frame_window = QueryFrameWindow (Window);

  // Узнаем имя приложения, создавшего окно.
  CHAR Exe_name[SIZE_OF_NAME] = ""; GetDetectedExeName (Frame_window, Exe_name);

  // Если его удалось определить:
  if (Exe_name[0] != 0)
  {
    // Проверяем, есть ли приложение в списке исключений.
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_1)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_2)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_3)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_4)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_5)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_6)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_7)) return 0;
    if (stric (Exe_name, Scroller.Settings.Exceptions.KeyScrolling_8)) return 0;
  }

  // Узнаем окно рабочей области для окна рамки.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  // Если оно есть:
  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно рабочей области.
    CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Window_name);

    // Проверяем, есть ли окно в списке исключений.
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_1)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_2)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_3)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_4)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_5)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_6)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_7)) return 0;
    if (strc (Window_name, Scroller.Settings.Exceptions.KeyScrolling_8)) return 0;
  }

  // Возврат.
  return 1;
}
