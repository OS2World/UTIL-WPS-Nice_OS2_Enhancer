//
// Эти функции могут работать без ошибок только внутри обработчика событий, так как:
// 1. Меню 2-го уровня должно быть создано в том же приложении, что и меню 1-го уровня.
// 2. Сообщения "MM_*" должны указывать на строки и структуры MENUITEM, расположенные в
// памяти приложения, создавшего окно. Стек потока использовать нельзя - ограничение PM.
//

// ─── Узнает окно меню ───

// SysMenu_window - окно картинки.
HWND VIOMenuManager_GetMenuWindow (HWND SysMenu_window)
{
  // Узнаем окно меню, которое появляется при нажатии на картинку.
  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  QuerySysMenuItemStruct (SysMenu_window, &Menu_item);

  // Возвращаем полученное значение.
  return Menu_item.hwndSubMenu;
}

// ─── Выбирает из списка строки, соответствующие окну ───

// Frame_window - окно рамки.
INT VIOMenuManager_GetCommandSubset (HWND Frame_window)
{
  // Узнаем заголовок окна или выбираем его из списка свойств.
  CHAR Window_title[SIZE_OF_TITLE] = ""; GetDetectedWindowTitle (Frame_window, Window_title);

  // Если заголовок неизвестен - возврат.
  if (Window_title[0] == 0) return -1;

  // Просматриваем список файлов.
  for (INT File_number = 0; File_number < MAX_VIO_MENU_FILES; File_number ++)
  {
    // Если запись не "включена" - продолжаем перебор.
    if (!VIOMenuManager.RTSettings.Files[File_number].Active) continue;

    // Просматриваем заголовки.
    for (INT Title_number = 0; Title_number < MAX_VIO_MENU_TITLES; Title_number ++)
    {
      // Если заголовок есть и он совпадает с заголовком окна - возвращаем номер файла.
      PCHAR Title = VIOMenuManager.RTSettings.Files[File_number].Titles[Title_number];
      if (Title[0] != 0) if (stristr (Title, Window_title)) return File_number;
    }
  }

  // Возврат.
  return -1;
}

// ─── Исправляет строку перед сравнением ───

// String - строка.
VOID VIOMenuManager_RemoveEmphasisMarks (PCHAR String)
{
  // Убираем "~" из строки.
  CHAR Temporary_string[SIZE_OF_ITEM_TEXT] = "";
  INT Length = strlen (String);

  for (INT Count = 0; Count < Length; Count ++)
  {
    if (String[Count] == '~')
    {
      if (String[Count + 1] != 0)
      {
        strcpy (Temporary_string, &String[Count + 1]);
        strcpy (&String[Count], Temporary_string);

        if (Count > 0) Count --;
      }
    }
  }

  // Возврат.
  return;
}

// ─── Находит строку в списке ───

// File_number - номер файла, String - строка с командой, которую надо найти.
INT VIOMenuManager_FindCommandInList (INT File_number, PCHAR String)
{
  // Во время поиска надо удалять из строк управляющие последовательности.
  VIOMenuManager_RemoveEmphasisMarks (String);

  // Выполняем поиск.
  INT Position = -1;

  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    if (VIOMenuManager.RTSettings.Files[File_number].Commands[Count][0] == 0) break;

    CHAR Command[SIZE_OF_ITEM_TEXT] = "";
    strcpy (Command, VIOMenuManager.RTSettings.Files[File_number].Commands[Count]);
    VIOMenuManager_RemoveEmphasisMarks (Command);

    if (strc (Command, String)) { Position = Count; break; }
  }

  // Возврат.
  return Position;
}

// ─── Создает меню со списком действий ───

// Frame_window - окно рамки, SysMenu_window - окно картинки.
HWND VIOMenuManager_CreateCommandsMenu (HWND Frame_window, HWND SysMenu_window)
{
  // Узнаем, какие строки надо добавить.
  INT File_number = VIOMenuManager_GetCommandSubset (Frame_window);

  // Если таких строк нет - возврат.
  if (File_number == -1) return NULLHANDLE;

  // Создаем окно меню.
  HWND CmdMenu_window = WinCreateWindow (HWND_DESKTOP, WC_MENU, NULL, 0x00, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Значения ID строк меню будут следовать за значением ID строки, вызывающей это меню.
  // Поскольку каждая строка содержит команду, запоминать постоянные значения ID не надо.
  ULONG Item_ID = VIOMenuManager.RTSettings.Commands_menu_ID + 1;

  // Выбираем строки из списка и добавляем их в меню.
  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    // Если строка не задана - продолжаем перебор.
    PCHAR Command = VIOMenuManager.RTSettings.Files[File_number].Commands[Count];
    if (Command[0] == 0) continue;

    // Увеличиваем значение ID строки.
    Item_ID ++;

    // Заполняем структуру MENUITEM.
    MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
    Menu_item.iPosition = MIT_END;
    Menu_item.afStyle = MIS_TEXT | MIS_SYSCOMMAND;
    Menu_item.id = Item_ID;

    // Добавляем строку в меню.
    WinSendMsg (CmdMenu_window, MM_INSERTITEM, (MPARAM) &Menu_item, (MPARAM) Command);
  }

  // Возврат.
  return CmdMenu_window;
}

// ─── Проверяет строку меню ───

// Item_ID - значение ID строки меню.
BYTE VIOMenuManager_IsSSHCommandMenuItem (ULONG Item_ID)
{
  // Проверяем значение.
  INT Min = VIOMenuManager.RTSettings.Commands_menu_ID + 1;
  INT Max = Min + MAX_VIO_MENU_COMMANDS;

  if (Item_ID >= Min &&
      Item_ID <= Max) return 1;

  // Возврат.
  return 0;
}

// ─── Добавляет в меню строку "показать список действий" ───

// SysMenu_window - окно картинки, Menu_window - окно меню, Name - строка меню, CmdMenu_window - меню второго уровня.
VOID VIOMenuManager_AddCommandsMenuItem (HWND SysMenu_window, HWND Menu_window, PCHAR Name, HWND CmdMenu_window)
{
  // Составляем строку.
  CHAR String[SIZE_OF_NAME] = "SSH/2";

  if (Name)
  {
    strcat (String, ": "); strcat (String, Name);
    strchg (String, '^', ' ');
  }

  // Заполняем структуру MENUITEM. Строка будет добавлена в меню после "действий с мышью".
  ULONG Position = (ULONG) WinSendMsg (Menu_window, MM_ITEMPOSITIONFROMID, (MPARAM) SM_VIO_MOUSE, 0);

  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  Menu_item.iPosition = Position + 1;
  Menu_item.afStyle = MIS_TEXT | MIS_SUBMENU;
  Menu_item.id = VIOMenuManager.RTSettings.Commands_menu_ID;
  Menu_item.hwndSubMenu = CmdMenu_window;

  // Добавляем строку в меню.
  WinSendMsg (Menu_window, MM_INSERTITEM, (MPARAM) &Menu_item, (MPARAM) String);

  // Возврат.
  return;
}

// ─── Добавляет строки в меню ───

// Frame_window - окно рамки.
VOID VIOMenuManager_AddItems (HWND Frame_window)
{
  // Узнаем окно меню первого уровня, которое появляется при нажатии на картинку.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);

  // Смотрим, есть ли уже такие строки в меню первого или второго уровня.
  // Важно, что эта проверка стоит только в одном месте и действует для всех строк.
  // Кроме всего прочего, она предотвращает повторное создание меню второго уровня.
  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    // Если любая из этих строк уже есть - возврат.
    ULONG Item_ID = VIOMenuManager.RTSettings.Commands_menu_ID + Count;
    ULONG Item_is_present = (ULONG) WinSendMsg (SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT (Item_ID, INCLUDE_SUBMENUS), 0);

    if (Item_is_present) return;
  }

  // Создаем меню второго уровня со списком команд.
  HWND CmdMenu_window = VIOMenuManager_CreateCommandsMenu (Frame_window, SysMenu_window);

  // Добавляем его в меню первого уровня.
  if (CmdMenu_window)
  {
    // Узнаем путь к значку "Командная среда".
    // Имя каталога можно использовать как строку.
    CHAR Path[SIZE_OF_PATH] = "";
    HOBJECT CmdPrompts_object = QueryWPSObject ("<WP_PROMPTS>");
    if (CmdPrompts_object != NULLHANDLE) WinQueryObjectPath (CmdPrompts_object, Path, SIZE_OF_PATH);

    // Если он был получен:
    if (Path[0] != 0)
    {
      // Добавляем строку в меню первого уровня.
      // При выборе этой строки будет появляться меню второго уровня со списком команд.
      PCHAR Name = FindNameInPath (Path);
      if (Name) VIOMenuManager_AddCommandsMenuItem (SysMenu_window, Menu_window, Name, CmdMenu_window);
    }
  }

  // Возврат.
  return;
}

// ─── Показывает меню ───

// Frame_window - окно рамки.
VOID VIOMenuManager_ShowItems (HWND Frame_window)
{
  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Отправляем ему сообщение о том, что его меню должно появиться на экране.
  WinSendMsg (SysMenu_window, MM_STARTMENUMODE, (MPARAM) 1, 0);

  // Делаем выбранной строку списка команд.
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);
  WinSendMsg (Menu_window, MM_SELECTITEM, MPFROM2SHORT (VIOMenuManager.RTSettings.Commands_menu_ID, 0), 0);

  // Возврат.
  return;
}

// ─── Получаем текст строки меню по значению ID строки ───

// Frame_window - окно рамки, Item_ID - значение ID строки, String_* - внешние переменные.
VOID VIOMenuManager_QueryCommandItemText (HWND Frame_window, ULONG Item_ID, PCHAR String, ULONG String_length)
{
  // Узнаем окно меню первого уровня, которое появляется при нажатии на картинку.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);

  // Узнаем свойства строки меню.
  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (VIOMenuManager.RTSettings.Commands_menu_ID, 0), &Menu_item);

  // Если такая строка есть и она вызывает окно меню второго уровня:
  if (Menu_item.hwndSubMenu)
  {
    // Получаем текст строки.
    WinSendMsg (Menu_item.hwndSubMenu, MM_QUERYITEMTEXT, MPFROM2SHORT (Item_ID, String_length), String);
  }

  // Возврат.
  return;
}

