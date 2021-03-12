// ─── Проверяет строку меню ───

// Menu_window - окно меню, Item - строка для проверки.
BYTE MenuItems_MenuItemIsPresent (HWND Menu_window, LONG Item)
{
  // Узнаем, есть ли в меню такая строка.
  BYTE Item_is_present = (LONG) WinSendMsg (Menu_window, MM_ISITEMVALID, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), 0);

  // Возврат.
  return Item_is_present;
}

// ─── Узнает свойства меню ───

// Menu_window - окно меню, Item - строка для проверки.
BYTE MenuItems_MenuItemIsChecked (HWND Menu_window, LONG Item)
{
  // Сбрасываем переменную, которая используется для получения свойств меню.
  bzero (&MenuItems.RTSettings.Menu_item, sizeof (MENUITEM));

  // Узнаем свойства строки меню.
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), &MenuItems.RTSettings.Menu_item);

  // Смотрим, выбрана ли строка.
  BYTE Item_is_checked = 0;
  if (MenuItems.RTSettings.Menu_item.afAttribute & MIA_CHECKED) Item_is_checked = 1;

  // Возврат.
  return Item_is_checked;
}

// ─── Узнает свойства меню ───

// Menu_window - окно меню, Item - строка для проверки.
BYTE MenuItems_MenuItemIsEnabled (HWND Menu_window, LONG Item)
{
  // Сбрасываем переменную, которая используется для получения свойств меню.
  bzero (&MenuItems.RTSettings.Menu_item, sizeof (MENUITEM));

  // Узнаем свойства строки меню.
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), &MenuItems.RTSettings.Menu_item);

  // Смотрим, доступна ли строка.
  BYTE Item_is_enabled = 1;
  if (MenuItems.RTSettings.Menu_item.afAttribute & MIA_DISABLED) Item_is_enabled = 0;

  // Возврат.
  return Item_is_enabled;
}

// ─── Получает структуру MENUITEM от окна картинки ───

// SysMenu_window - окно картинки, Menu_item - указатель на структуру.
VOID MenuItems_QuerySysMenuItemStruct (HWND SysMenu_window, PMENUITEM Menu_item)
{
  // Узнаем окно меню, которое появляется при нажатии на картинку.
  ULONG First_position = 0;
  ULONG Menu_ID = (ULONG) WinSendMsg (SysMenu_window, MM_ITEMIDFROMPOSITION, (MPARAM) First_position, 0);

  // Заполняем структуру MENUITEM для этого меню.
  WinSendMsg (SysMenu_window, MM_QUERYITEM, (MPARAM) Menu_ID, Menu_item);

  // Возврат.
  return;
}
