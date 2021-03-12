
// ─── Проверяет, можно ли прятать окно при смене комнат ───

// Frame_window - окно рамки.
BYTE Rooms_PermissionForRoomActions (HWND Frame_window)
{
  // Если окно недоступно - возврат.
  if (!FrameWindowIsAccessible (Frame_window)) return 0;

  // Узнаем имя приложения, создавшего окно.
  CHAR Exe_name[SIZE_OF_NAME] = ""; GetDetectedExeName (Frame_window, Exe_name);

  // Если его удалось определить:
  if (Exe_name[0] != 0)
  {
    // Проверяем, есть ли приложение в списке исключений.
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_1)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_2)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_3)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_4)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_5)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_6)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_7)) return 0;
    if (stric (Exe_name, Rooms.Settings.Exceptions.Rooms_8)) return 0;
  }

  // Узнаем окно рабочей области.
  HWND Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

  // Если оно есть:
  if (Client_window != NULLHANDLE)
  {
    // Узнаем имя, под которым определено окно рабочей области.
    CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Client_window, SIZE_OF_NAME, Window_name);

    // Проверяем, есть ли окно в списке исключений.
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_1)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_2)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_3)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_4)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_5)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_6)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_7)) return 0;
    if (strc (Window_name, Rooms.Settings.Exceptions.Rooms_8)) return 0;
  }

  // Возврат.
  return 1;
}
