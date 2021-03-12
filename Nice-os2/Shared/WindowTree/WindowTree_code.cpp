
// ─── Перебирает окна на одном уровне дерева и заполняет внешний массив ───

// Parent_window - окно, где надо просмотреть окна, Array - массив для заполнения,
// Length - длина массива, Quantity - число найденных окон и значений в массиве.
VOID WindowTree_EnumerateWindows (HWND Parent_window, PHWND Array, INT Length, PINT Quantity)
{
  // Если массив заполнен до отказа - возврат.
  if (*Quantity >= Length) return;

   // Перебираем окна в указанном окне.
   HENUM Enumeration = WinBeginEnumWindows (Parent_window); HWND Window = NULLHANDLE;
   while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
   {
     // Запоминаем окно.
     INT Current_position = (*Quantity - 1);
     INT Next_position = Current_position + 1; Array[Next_position] = Window;

     // Увеличиваем переменную, содержащую число окон в массиве.
     // Запись с использованием "двух плюсов" почему-то не сработала - странно...
     *Quantity = *Quantity + 1;

     // Если массив заполнен до отказа - прекращаем поиск.
     if (*Quantity >= Length) break;

     // Пробуем найти окна внутри этого окна.
     // Если их там нет - значения переменных не изменятся.
     WindowTree_EnumerateWindows (Window, Array, Length, Quantity);
   }
   WinEndEnumWindows (Enumeration);

  // Возврат.
  return;
}

// ─── Просматривает дерево окон и заполняет массив значений для них ───

// Window - окно, с которого надо начать просмотр, Array - массив для заполнения, Length - длина массива.
VOID WindowTree_ExploreWindowTree (HWND Window, PHWND Array, PINT Length)
{
  // Проверяем значения.
  if (Array == NULL || Length == NULL || *Length <= 0) return;

  // Просматриваем дерево окон.
  Array[0] = Window; INT Quantity = 1;
  WindowTree_EnumerateWindows (Window, Array, *Length, &Quantity);

  // Запоминаем число найденных окон.
  *Length = Quantity;

  // Возврат.
  return;
}

// ─── Удаляет дерево окон ───

// Window - окно, начиная с которого надо удалить все окна, а переменная
// Include_root_window указывает, надо ли вместе с ними удалять это окно.
VOID WindowTree_DestroyWindowTree (HWND Window, BYTE Include_root_window = 1)
{
  // Просматриваем дерево окон.
  HWND Tree[WNDTREE_SIZE]; INT Length = WNDTREE_SIZE; WindowTree_ExploreWindowTree (Window, Tree, &Length);

  // Отключаем рисование во всех окнах.
  for (INT Count = 0; Count < Length; Count ++) WinEnableWindowUpdate (Tree[Count], 0);

  // Удаляем все окна, начиная с последнего найденного.
  INT Limit = 0; if (!Include_root_window) Limit = 1;

  for (Count = Length - 1; Count >= Limit; Count --) WinDestroyWindow (Tree[Count]);

  // Включаем рисование в окне, если его удалять не надо.
  if (!Include_root_window) WinEnableWindowUpdate (Window, 1);

  // Возврат.
  return;
}

// ─── Включает или отключает рисование в окнах ───

// Window - окно, New_state - новое состояние, Include_root_window - надо ли изменять и это окно.
// В переменную Changed_windows записываются окна, состояние которых действительно было изменено.
VOID WindowTree_EnableWindowTreeUpdate (HWND Window, BYTE New_state, PHWND Changed_windows = NULL, INT Changed_windows_length = WNDTREE_SIZE, BYTE Include_root_window = 1)
{
  // Просматриваем дерево окон.
  HWND Tree[WNDTREE_SIZE]; INT Length = WNDTREE_SIZE; WindowTree_ExploreWindowTree (Window, Tree, &Length);

  // Включаем или отключаем рисование во всех окнах.
  // Невидимые окна - не трогаем, потому что при включении рисования они станут видимыми.
  INT Limit = 0; if (!Include_root_window) Limit = 1;

  if (!New_state)
  {
    for (INT Count = Limit; Count < Length; Count ++) 
    {
      if (Changed_windows != NULL && Count < Changed_windows_length) Changed_windows[Count] = NULLHANDLE;

      if (WinIsWindowVisible (Tree[Count])) 
      {
        WinEnableWindowUpdate (Tree[Count], 0);

        if (Changed_windows != NULL && Count < Changed_windows_length) Changed_windows[Count] = Tree[Count];
      }
    }
  }
  else
  {
    for (INT Count = Length - 1; Count >= Limit; Count --) 
    {
      if (Changed_windows != NULL && Count < Changed_windows_length) 
       if (Changed_windows[Count] == NULLHANDLE || Changed_windows[Count] != Tree[Count]) continue;

      WinEnableWindowUpdate (Tree[Count], 1);
    }
  }

  // Возврат.
  return;
}

