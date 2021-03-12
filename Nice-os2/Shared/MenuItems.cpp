// Методы для работы с окнами.
#define MenuItemIsPresent                  MenuItems_MenuItemIsPresent
#define MenuItemIsChecked                  MenuItems_MenuItemIsChecked
#define MenuItemIsEnabled                  MenuItems_MenuItemIsEnabled

#define QuerySysMenuItemStruct             MenuItems_QuerySysMenuItemStruct

// ─── Метод для подключения класса ───

VOID MenuItems_Start (VOID)
{
  #ifdef MenuItems
  bzero (&MenuItems, sizeof (MenuItems));
  #endif

  // Возврат.
  return;
}

