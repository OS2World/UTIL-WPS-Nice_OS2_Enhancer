
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Remover_SetPreDefinedSettings (LONG Division)
{
  // Задаем настройки.
  if (Division == SET_ALL_SETTINGS)
  {
    bzero (&Remover.Settings.WinListNames, sizeof (WINLISTNAMES));
  }

  if (Division == SET_ALL_SETTINGS || Division == SET_WINLIST)
  {
    Remover.Settings.Remove_items_from_Window_list = 0;
    Remover.Settings.Hide_known_applications = 1;

    strcpy (Remover.Settings.DDNS, "DDNS Server Administrator");
    strcpy (Remover.Settings.DHCP, "DHCP Server Administrator");
    strcpy (Remover.Settings.BINL, "BINL Server Administrator");
  }

  // Возврат.
  return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Remover_ReadSettings (HINI Ini_file)
{
  // Читаем настройки.
  ULONG Byte = 0; ULONG Name = 0; ULONG Byte_data = 0;

  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Remove items from Window list", &Byte_data, &Byte)) Remover.Settings.Remove_items_from_Window_list = Byte_data;
  Byte = sizeof (BYTE); if (PrfQueryProfileData (Ini_file, "Settings", "Hide known applications", &Byte_data, &Byte)) Remover.Settings.Hide_known_applications = Byte_data;

  {
    CHAR Item[SIZE_OF_PATH] = "";

    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 1 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_1_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 2 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_2_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 3 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_3_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 4 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_4_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 5 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_5_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 6 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_6_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 7 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_7_name, Item); Item[0] = 0; }
    Name = SIZE_OF_TITLE; PrfQueryProfileData (Ini_file, "WinList", "Remove from list 8 name", Item, &Name);
    if (Item[0] != 0) { strcpy (Remover.Settings.WinListNames.Remove_from_list_8_name, Item); Item[0] = 0; }
  }

  // Возврат.
  return;
}