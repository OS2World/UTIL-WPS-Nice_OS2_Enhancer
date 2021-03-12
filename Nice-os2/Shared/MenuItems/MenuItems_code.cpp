// ��� �஢���� ��ப� ���� ���

// Menu_window - ���� ����, Item - ��ப� ��� �஢�ન.
BYTE MenuItems_MenuItemIsPresent (HWND Menu_window, LONG Item)
{
  // ������, ���� �� � ���� ⠪�� ��ப�.
  BYTE Item_is_present = (LONG) WinSendMsg (Menu_window, MM_ISITEMVALID, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), 0);

  // ������.
  return Item_is_present;
}

// ��� ������ ᢮��⢠ ���� ���

// Menu_window - ���� ����, Item - ��ப� ��� �஢�ન.
BYTE MenuItems_MenuItemIsChecked (HWND Menu_window, LONG Item)
{
  // ����뢠�� ��६�����, ����� �ᯮ������ ��� ����祭�� ᢮��� ����.
  bzero (&MenuItems.RTSettings.Menu_item, sizeof (MENUITEM));

  // ������ ᢮��⢠ ��ப� ����.
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), &MenuItems.RTSettings.Menu_item);

  // ����ਬ, ��࠭� �� ��ப�.
  BYTE Item_is_checked = 0;
  if (MenuItems.RTSettings.Menu_item.afAttribute & MIA_CHECKED) Item_is_checked = 1;

  // ������.
  return Item_is_checked;
}

// ��� ������ ᢮��⢠ ���� ���

// Menu_window - ���� ����, Item - ��ப� ��� �஢�ન.
BYTE MenuItems_MenuItemIsEnabled (HWND Menu_window, LONG Item)
{
  // ����뢠�� ��६�����, ����� �ᯮ������ ��� ����祭�� ᢮��� ����.
  bzero (&MenuItems.RTSettings.Menu_item, sizeof (MENUITEM));

  // ������ ᢮��⢠ ��ப� ����.
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (Item, INCLUDE_SUBMENUS), &MenuItems.RTSettings.Menu_item);

  // ����ਬ, ����㯭� �� ��ப�.
  BYTE Item_is_enabled = 1;
  if (MenuItems.RTSettings.Menu_item.afAttribute & MIA_DISABLED) Item_is_enabled = 0;

  // ������.
  return Item_is_enabled;
}

// ��� ����砥� �������� MENUITEM �� ���� ���⨭�� ���

// SysMenu_window - ���� ���⨭��, Menu_item - 㪠��⥫� �� ��������.
VOID MenuItems_QuerySysMenuItemStruct (HWND SysMenu_window, PMENUITEM Menu_item)
{
  // ������ ���� ����, ���஥ ������ �� ����⨨ �� ���⨭��.
  ULONG First_position = 0;
  ULONG Menu_ID = (ULONG) WinSendMsg (SysMenu_window, MM_ITEMIDFROMPOSITION, (MPARAM) First_position, 0);

  // ������塞 �������� MENUITEM ��� �⮣� ����.
  WinSendMsg (SysMenu_window, MM_QUERYITEM, (MPARAM) Menu_ID, Menu_item);

  // ������.
  return;
}
