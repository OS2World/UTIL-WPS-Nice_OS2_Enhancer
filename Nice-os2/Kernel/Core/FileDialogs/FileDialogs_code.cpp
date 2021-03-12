
// ─── Находит в окне открытия файла подходящее поле ввода ───

// Frame_window - окно рамки.
HWND FileDialogs_FindFieldInFileDialog (HWND Frame_window)
{
  // Узнаем поле ввода для имени файла, используя значение, по которому оно может быть задано в обычном диалоге.
  HWND Field = WinWindowFromID (Frame_window, FDLG_ENTRY_FIELD);

  // Если это не поле ввода - надо найти его другим способом.
  if (Field == NULLHANDLE || !IsEntryFieldWindow (Field))
  {
    // Считаем, что поле ввода неизвестно.
    if (Field != NULLHANDLE) Field = NULLHANDLE;

    // Перебираем окна в окне рамки.
    HENUM Enumeration = WinBeginEnumWindows (Frame_window); HWND Window = NULLHANDLE;
    while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
    {
      // Если это поле ввода:
      if (IsEntryFieldWindow (Window))
      {
        // Если было найдено несколько полей ввода - прекращаем перебор окон.
        if (Field != NULLHANDLE) { Field = NULLHANDLE; break; }

        // Запоминаем поле ввода.
        Field = Window;
      }
    }
    WinEndEnumWindows (Enumeration);
  }

  // Возврат.
  return Field;
}
