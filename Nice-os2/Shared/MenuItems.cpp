// ��⮤� ��� ࠡ��� � ������.
#define MenuItemIsPresent                  MenuItems_MenuItemIsPresent
#define MenuItemIsChecked                  MenuItems_MenuItemIsChecked
#define MenuItemIsEnabled                  MenuItems_MenuItemIsEnabled

#define QuerySysMenuItemStruct             MenuItems_QuerySysMenuItemStruct

// ��� ��⮤ ��� ������祭�� ����� ���

VOID MenuItems_Start (VOID)
{
  #ifdef MenuItems
  bzero (&MenuItems, sizeof (MenuItems));
  #endif

  // ������.
  return;
}

