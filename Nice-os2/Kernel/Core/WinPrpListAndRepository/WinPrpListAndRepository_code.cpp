
// ─── Узнает название приложения, создавшего окно, и запоминает его в списке свойств ───

// Frame_window - окно рамки, Name - строка для названия.
VOID WinPrpListAndRepository_GetDetectedExeName (HWND Frame_window, PCHAR Name)
{
  // Узнаем, есть ли имя приложения в списке.
  Name[0] = 0; FindProperty (Frame_window, PRP_EXENAME, Name);

  // Если его нет:
  if (Name[0] == 0)
  {
    // Узнаем его и запоминаем в списке.
    WinPrpListAndRepository_RememberExeNameAndPath (Frame_window);

    // Выбираем его из списка еще раз. Имя все равно может быть пустым.
    FindProperty (Frame_window, PRP_EXENAME, Name);
  }

  // Возврат.
  return;
}

// ─── Узнает путь к приложению, создавшему окно, и запоминает его в списке свойств ───

// Frame_window - окно рамки, Path - строка для пути к приложению.
VOID WinPrpListAndRepository_GetDetectedExePath (HWND Frame_window, PCHAR Path)
{
  // Узнаем, есть ли путь к приложению в списке.
  Path[0] = 0; FindProperty (Frame_window, PRP_EXEPATH, Path);

  // Если его нет:
  if (Path[0] == 0)
  {
    // Узнаем его и запоминаем в списке.
    WinPrpListAndRepository_RememberExeNameAndPath (Frame_window);

    // Выбираем его из списка еще раз. Путь все равно может быть пустым.
    FindProperty (Frame_window, PRP_EXEPATH, Path);
  }

  // Возврат.
  return;
}

// ─── Выбирает заголовок окна из списка свойств или узнает его ───

// Frame_window - окно рамки, Title - строка для заголовка.
VOID WinPrpListAndRepository_GetDetectedWindowTitle (HWND Frame_window, PCHAR Title)
{
  // Пробуем найти окно в списке свойств и узнать его заголовок.
  Title[0] = 0; FindProperty (Frame_window, PRP_TITLE, Title);

  // Если это сделать не удалось - узнаем заголовок окна.
  if (Title[0] == 0) QueryWindowTitle (Frame_window, WinWindowFromID (Frame_window, FID_TITLEBAR), Title, 0);

  // Возврат.
  return;
}
