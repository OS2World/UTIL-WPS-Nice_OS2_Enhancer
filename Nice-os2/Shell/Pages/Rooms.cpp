
// ─── Метод для подключения класса ───

VOID Rooms_Start (LONG Settings_to_show = SET_ALL_SETTINGS)
{
  #ifdef Rooms_Colors
  bzero (&Rooms_Colors, sizeof (Rooms_Colors));
  #endif

  #ifdef Rooms_Allocations
  bzero (&Rooms_Allocations, sizeof (Rooms_Allocations));
  #endif

  #ifdef Rooms_Exceptions
  bzero (&Rooms_Exceptions, sizeof (Rooms_Exceptions));
  #endif

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Rooms_colors_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Rooms_colors_Name);

      Item.Settings_to_show = SET_ROOMS;
      strcpy (Item.Icon_name, "Rms_page.ico");

      Item.CreatePage          = Rooms_Colors_CreatePage;
      Item.SetDefSettings      = Rooms_SetPreDefinedSettings;
      Item.SetDefSettings_Ext1 = Painter_SetPreDefinedSettings;
      Item.ReadSettings        = Rooms_ReadSettings;
      Item.ReadSettings_Ext1   = Painter_ReadSettings;

      RememberPageItem (Enhancer.Pages.Rooms_colors, &Item);
    }

    // Задаем ID полей ввода.
    Rooms_Colors.Settings.Container_ID              = 1001;
    Rooms_Colors.Settings.Wallpaper_filebox_ID      = 1002;
    Rooms_Colors.Settings.Wallpaper_label_ID        = 1003;
    Rooms_Colors.Settings.Wallpaper_name_ID         = 1004;
    Rooms_Colors.Settings.Wallpaper_button_ID       = 1005;

    Rooms_Colors.Settings.Selected_room_cmbox_ID    = 1006;
    Rooms_Colors.Settings.Create_rooms_button_ID    = 1007;

    Rooms_Colors.Settings.NeonPalette_Container_ID  = 2001;
    Rooms_Colors.Settings.NeonPalette_Palette_ID    = 2002;
    Rooms_Colors.Settings.NeonPalette_Inactive_1_ID = 2003;
    Rooms_Colors.Settings.NeonPalette_Inactive_2_ID = 2004;
    Rooms_Colors.Settings.NeonPalette_Inactive_3_ID = 2005;
    Rooms_Colors.Settings.NeonPalette_Active_1_ID   = 2006;
    Rooms_Colors.Settings.NeonPalette_Active_2_ID   = 2007;
    Rooms_Colors.Settings.NeonPalette_Active_3_ID   = 2008;
    Rooms_Colors.Settings.NeonPalette_FillTB_ID     = 2009;

    Rooms_Colors.Settings.WinTitles_Container_ID    = 3001;
    Rooms_Colors.Settings.WinTitles_Palette_ID      = 3002;
    Rooms_Colors.Settings.WinTitles_Inactive_ID     = 3003;
    Rooms_Colors.Settings.WinTitles_Active_ID       = 3004;
    Rooms_Colors.Settings.WinTitles_Button_ID       = 3005;
    Rooms_Colors.Settings.WinTitles_DrawText_ID     = 3006;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Rooms_Allocations_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Rooms_Allocations_Name);

      Item.Settings_to_show = SET_ROOMS;
      strcpy (Item.Icon_name, "Rms_page.ico");

      Item.CreatePage     = Rooms_Allocations_CreatePage;
      Item.SetDefSettings = Rooms_SetPreDefinedSettings;
      Item.ReadSettings   = Rooms_ReadSettings;

      RememberPageItem (Enhancer.Pages.Rooms_allocations, &Item);
    }

    // Задаем ID полей ввода.
    Rooms_Allocations.Settings.AppList_Container_ID   = 1001;
    Rooms_Allocations.Settings.SelectBox_ID           = 1002;
    Rooms_Allocations.Settings.Selected_room_cmbox_ID = 1003;
    Rooms_Allocations.Settings.Application_list_ID    = 1004;
    Rooms_Allocations.Settings.AddRemove_ID           = 1005;
    Rooms_Allocations.Settings.Application_Add_ID     = 1006;
    Rooms_Allocations.Settings.Application_Remove_ID  = 1007;

    Rooms_Allocations.Settings.KnownApps_button_ID    = 1008;
    Rooms_Allocations.Settings.Allocate_button_ID     = 1009;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Rooms_Exceptions_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Rooms_Exceptions_Name);

      Item.Settings_to_show = SET_ROOMS;
      strcpy (Item.Icon_name, "Rms_page.ico");

      Item.CreatePage     = Rooms_Exceptions_CreatePage;
      Item.SetDefSettings = Rooms_SetPreDefinedSettings;
      Item.ReadSettings   = Rooms_ReadSettings;

      RememberPageItem (Enhancer.Pages.Rooms_exceptions, &Item);
    }

    // Задаем ID полей ввода.
    Rooms_Exceptions.Settings.Container_ID          = 1001;
    Rooms_Exceptions.Settings.List_ID               = 1002;
    Rooms_Exceptions.Settings.Add_button_ID         = 1003;
    Rooms_Exceptions.Settings.Remove_button_ID      = 1004;

    Rooms_Exceptions.Settings.NoKeys_button_ID      = 1005;
    Rooms_Exceptions.Settings.NoIcons_button_ID     = 1006;
    Rooms_Exceptions.Settings.NoWallpaper_button_ID = 1007;
  }

  // Возврат.
  return;
}
