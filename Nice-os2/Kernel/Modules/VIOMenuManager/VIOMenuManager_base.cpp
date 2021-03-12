//
// �� �㭪樨 ����� ࠡ���� ��� �訡�� ⮫쪮 ����� ��ࠡ��稪� ᮡ�⨩, ⠪ ���:
// 1. ���� 2-�� �஢�� ������ ���� ᮧ���� � ⮬ �� �ਫ������, �� � ���� 1-�� �஢��.
// 2. ����饭�� "MM_*" ������ 㪠�뢠�� �� ��ப� � �������� MENUITEM, �ᯮ������� �
// ����� �ਫ������, ᮧ���襣� ����. �⥪ ��⮪� �ᯮ�짮���� ����� - ��࠭�祭�� PM.
//

// ��� ������ ���� ���� ���

// SysMenu_window - ���� ���⨭��.
HWND VIOMenuManager_GetMenuWindow (HWND SysMenu_window)
{
  // ������ ���� ����, ���஥ ������ �� ����⨨ �� ���⨭��.
  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  QuerySysMenuItemStruct (SysMenu_window, &Menu_item);

  // �����頥� ����祭��� ���祭��.
  return Menu_item.hwndSubMenu;
}

// ��� �롨ࠥ� �� ᯨ᪠ ��ப�, ᮮ⢥�����騥 ���� ���

// Frame_window - ���� ࠬ��.
INT VIOMenuManager_GetCommandSubset (HWND Frame_window)
{
  // ������ ��������� ���� ��� �롨ࠥ� ��� �� ᯨ᪠ ᢮���.
  CHAR Window_title[SIZE_OF_TITLE] = ""; GetDetectedWindowTitle (Frame_window, Window_title);

  // �᫨ ��������� �������⥭ - ������.
  if (Window_title[0] == 0) return -1;

  // ��ᬠ�ਢ��� ᯨ᮪ 䠩���.
  for (INT File_number = 0; File_number < MAX_VIO_MENU_FILES; File_number ++)
  {
    // �᫨ ������ �� "����祭�" - �த������ ��ॡ��.
    if (!VIOMenuManager.RTSettings.Files[File_number].Active) continue;

    // ��ᬠ�ਢ��� ���������.
    for (INT Title_number = 0; Title_number < MAX_VIO_MENU_TITLES; Title_number ++)
    {
      // �᫨ ��������� ���� � �� ᮢ������ � ���������� ���� - �����頥� ����� 䠩��.
      PCHAR Title = VIOMenuManager.RTSettings.Files[File_number].Titles[Title_number];
      if (Title[0] != 0) if (stristr (Title, Window_title)) return File_number;
    }
  }

  // ������.
  return -1;
}

// ��� ��ࠢ��� ��ப� ��। �ࠢ������ ���

// String - ��ப�.
VOID VIOMenuManager_RemoveEmphasisMarks (PCHAR String)
{
  // ���ࠥ� "~" �� ��ப�.
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

  // ������.
  return;
}

// ��� ��室�� ��ப� � ᯨ᪥ ���

// File_number - ����� 䠩��, String - ��ப� � ��������, ������ ���� ����.
INT VIOMenuManager_FindCommandInList (INT File_number, PCHAR String)
{
  // �� �६� ���᪠ ���� 㤠���� �� ��ப �ࠢ���騥 ��᫥����⥫쭮��.
  VIOMenuManager_RemoveEmphasisMarks (String);

  // �믮��塞 ����.
  INT Position = -1;

  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    if (VIOMenuManager.RTSettings.Files[File_number].Commands[Count][0] == 0) break;

    CHAR Command[SIZE_OF_ITEM_TEXT] = "";
    strcpy (Command, VIOMenuManager.RTSettings.Files[File_number].Commands[Count]);
    VIOMenuManager_RemoveEmphasisMarks (Command);

    if (strc (Command, String)) { Position = Count; break; }
  }

  // ������.
  return Position;
}

// ��� ������� ���� � ᯨ᪮� ����⢨� ���

// Frame_window - ���� ࠬ��, SysMenu_window - ���� ���⨭��.
HWND VIOMenuManager_CreateCommandsMenu (HWND Frame_window, HWND SysMenu_window)
{
  // ������, ����� ��ப� ���� ��������.
  INT File_number = VIOMenuManager_GetCommandSubset (Frame_window);

  // �᫨ ⠪�� ��ப ��� - ������.
  if (File_number == -1) return NULLHANDLE;

  // ������� ���� ����.
  HWND CmdMenu_window = WinCreateWindow (HWND_DESKTOP, WC_MENU, NULL, 0x00, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // ���祭�� ID ��ப ���� ���� ᫥������ �� ���祭��� ID ��ப�, ��뢠�饩 �� ����.
  // ��᪮��� ������ ��ப� ᮤ�ন� �������, ���������� ����ﭭ� ���祭�� ID �� ����.
  ULONG Item_ID = VIOMenuManager.RTSettings.Commands_menu_ID + 1;

  // �롨ࠥ� ��ப� �� ᯨ᪠ � ������塞 �� � ����.
  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    // �᫨ ��ப� �� ������ - �த������ ��ॡ��.
    PCHAR Command = VIOMenuManager.RTSettings.Files[File_number].Commands[Count];
    if (Command[0] == 0) continue;

    // �����稢��� ���祭�� ID ��ப�.
    Item_ID ++;

    // ������塞 �������� MENUITEM.
    MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
    Menu_item.iPosition = MIT_END;
    Menu_item.afStyle = MIS_TEXT | MIS_SYSCOMMAND;
    Menu_item.id = Item_ID;

    // ������塞 ��ப� � ����.
    WinSendMsg (CmdMenu_window, MM_INSERTITEM, (MPARAM) &Menu_item, (MPARAM) Command);
  }

  // ������.
  return CmdMenu_window;
}

// ��� �஢���� ��ப� ���� ���

// Item_ID - ���祭�� ID ��ப� ����.
BYTE VIOMenuManager_IsSSHCommandMenuItem (ULONG Item_ID)
{
  // �஢��塞 ���祭��.
  INT Min = VIOMenuManager.RTSettings.Commands_menu_ID + 1;
  INT Max = Min + MAX_VIO_MENU_COMMANDS;

  if (Item_ID >= Min &&
      Item_ID <= Max) return 1;

  // ������.
  return 0;
}

// ��� �������� � ���� ��ப� "�������� ᯨ᮪ ����⢨�" ���

// SysMenu_window - ���� ���⨭��, Menu_window - ���� ����, Name - ��ப� ����, CmdMenu_window - ���� ��ண� �஢��.
VOID VIOMenuManager_AddCommandsMenuItem (HWND SysMenu_window, HWND Menu_window, PCHAR Name, HWND CmdMenu_window)
{
  // ���⠢�塞 ��ப�.
  CHAR String[SIZE_OF_NAME] = "SSH/2";

  if (Name)
  {
    strcat (String, ": "); strcat (String, Name);
    strchg (String, '^', ' ');
  }

  // ������塞 �������� MENUITEM. ��ப� �㤥� ��������� � ���� ��᫥ "����⢨� � �����".
  ULONG Position = (ULONG) WinSendMsg (Menu_window, MM_ITEMPOSITIONFROMID, (MPARAM) SM_VIO_MOUSE, 0);

  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  Menu_item.iPosition = Position + 1;
  Menu_item.afStyle = MIS_TEXT | MIS_SUBMENU;
  Menu_item.id = VIOMenuManager.RTSettings.Commands_menu_ID;
  Menu_item.hwndSubMenu = CmdMenu_window;

  // ������塞 ��ப� � ����.
  WinSendMsg (Menu_window, MM_INSERTITEM, (MPARAM) &Menu_item, (MPARAM) String);

  // ������.
  return;
}

// ��� �������� ��ப� � ���� ���

// Frame_window - ���� ࠬ��.
VOID VIOMenuManager_AddItems (HWND Frame_window)
{
  // ������ ���� ���� ��ࢮ�� �஢��, ���஥ ������ �� ����⨨ �� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);

  // ����ਬ, ���� �� 㦥 ⠪�� ��ப� � ���� ��ࢮ�� ��� ��ண� �஢��.
  // �����, �� �� �஢�ઠ �⮨� ⮫쪮 � ����� ���� � ������� ��� ��� ��ப.
  // �஬� �ᥣ� ��祣�, ��� �।���頥� ����୮� ᮧ����� ���� ��ண� �஢��.
  for (INT Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++)
  {
    // �᫨ �� �� ��� ��ப 㦥 ���� - ������.
    ULONG Item_ID = VIOMenuManager.RTSettings.Commands_menu_ID + Count;
    ULONG Item_is_present = (ULONG) WinSendMsg (SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT (Item_ID, INCLUDE_SUBMENUS), 0);

    if (Item_is_present) return;
  }

  // ������� ���� ��ண� �஢�� � ᯨ᪮� ������.
  HWND CmdMenu_window = VIOMenuManager_CreateCommandsMenu (Frame_window, SysMenu_window);

  // ������塞 ��� � ���� ��ࢮ�� �஢��.
  if (CmdMenu_window)
  {
    // ������ ���� � ����� "��������� �।�".
    // ��� ��⠫��� ����� �ᯮ�짮���� ��� ��ப�.
    CHAR Path[SIZE_OF_PATH] = "";
    HOBJECT CmdPrompts_object = QueryWPSObject ("<WP_PROMPTS>");
    if (CmdPrompts_object != NULLHANDLE) WinQueryObjectPath (CmdPrompts_object, Path, SIZE_OF_PATH);

    // �᫨ �� �� ����祭:
    if (Path[0] != 0)
    {
      // ������塞 ��ப� � ���� ��ࢮ�� �஢��.
      // �� �롮� �⮩ ��ப� �㤥� ������� ���� ��ண� �஢�� � ᯨ᪮� ������.
      PCHAR Name = FindNameInPath (Path);
      if (Name) VIOMenuManager_AddCommandsMenuItem (SysMenu_window, Menu_window, Name, CmdMenu_window);
    }
  }

  // ������.
  return;
}

// ��� �����뢠�� ���� ���

// Frame_window - ���� ࠬ��.
VOID VIOMenuManager_ShowItems (HWND Frame_window)
{
  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // ��ࠢ�塞 ��� ᮮ�饭�� � ⮬, �� ��� ���� ������ ������ �� �࠭�.
  WinSendMsg (SysMenu_window, MM_STARTMENUMODE, (MPARAM) 1, 0);

  // ������ ��࠭��� ��ப� ᯨ᪠ ������.
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);
  WinSendMsg (Menu_window, MM_SELECTITEM, MPFROM2SHORT (VIOMenuManager.RTSettings.Commands_menu_ID, 0), 0);

  // ������.
  return;
}

// ��� ����砥� ⥪�� ��ப� ���� �� ���祭�� ID ��ப� ���

// Frame_window - ���� ࠬ��, Item_ID - ���祭�� ID ��ப�, String_* - ���譨� ��६����.
VOID VIOMenuManager_QueryCommandItemText (HWND Frame_window, ULONG Item_ID, PCHAR String, ULONG String_length)
{
  // ������ ���� ���� ��ࢮ�� �஢��, ���஥ ������ �� ����⨨ �� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  HWND Menu_window = VIOMenuManager_GetMenuWindow (SysMenu_window);

  // ������ ᢮��⢠ ��ப� ����.
  MENUITEM Menu_item; bzero (&Menu_item, sizeof (MENUITEM));
  WinSendMsg (Menu_window, MM_QUERYITEM, MPFROM2SHORT (VIOMenuManager.RTSettings.Commands_menu_ID, 0), &Menu_item);

  // �᫨ ⠪�� ��ப� ���� � ��� ��뢠�� ���� ���� ��ண� �஢��:
  if (Menu_item.hwndSubMenu)
  {
    // ����砥� ⥪�� ��ப�.
    WinSendMsg (Menu_item.hwndSubMenu, MM_QUERYITEMTEXT, MPFROM2SHORT (Item_ID, String_length), String);
  }

  // ������.
  return;
}

