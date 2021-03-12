
// ─── Метод для подключения класса ───

VOID VIOWindows_Start (LONG Settings_to_show = SET_ALL_SETTINGS)
{
  #ifdef VIOWindows_Fonts
  bzero (&VIOWindows_Fonts, sizeof (VIOWindows_Fonts));
  #endif

  #ifdef VIOWindows_SSH_Prompts
  bzero (&VIOWindows_SSH_Prompts, sizeof (VIOWindows_SSH_Prompts));
  #endif

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_VIOWindows_fonts_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_VIOWindows_fonts_Name);

      Item.Settings_to_show = SET_VIO_WINDOWS;
      strcpy (Item.Icon_name, "Vio_page.ico");

      Item.CreatePage     = VIOWindows_Fonts_CreatePage;
      Item.SetDefSettings = VIOFontManager_SetPreDefinedSettings;
      Item.ReadSettings   = VIOFontManager_ReadSettings;

      RememberPageItem (Enhancer.Pages.VIOWindows_fonts, &Item);
    }

    // Задаем ID полей ввода.
    VIOWindows_Fonts.Settings.AppList_Container_ID   = 1001;
    VIOWindows_Fonts.Settings.SelectBox_ID           = 1002;
    VIOWindows_Fonts.Settings.Selected_font_cmbox_ID = 1003;
    VIOWindows_Fonts.Settings.Application_list_ID    = 1004;
    VIOWindows_Fonts.Settings.AddRemove_ID           = 1005;
    VIOWindows_Fonts.Settings.Application_Add_ID     = 1006;
    VIOWindows_Fonts.Settings.Application_Remove_ID  = 1007;

    VIOWindows_Fonts.Settings.KnownApps_button_ID    = 1008;
    VIOWindows_Fonts.Settings.SetFont_button_ID      = 1009;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_VIOWindows_SSH_prompts_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_VIOWindows_SSH_prompts_Name);

      Item.Settings_to_show = SET_VIO_WINDOWS;
      strcpy (Item.Icon_name, "Vio_page.ico");

      Item.CreatePage     = VIOWindows_SSH_Prompts_CreatePage;
      Item.SetDefSettings = VIOMenuManager_SetPreDefinedSettings;
      Item.ReadSettings   = VIOMenuManager_ReadSettings;

      RememberPageItem (Enhancer.Pages.VIOWindows_SSH_prompts, &Item);
    }

    // Задаем ID полей ввода.
    VIOWindows_SSH_Prompts.Settings.SSH_Commands_button_ID = 1001;
    VIOWindows_SSH_Prompts.Settings.Use_AltTilde_button_ID = 1002;

    VIOWindows_SSH_Prompts.Settings.FileList_Container_ID  = 1003;
    VIOWindows_SSH_Prompts.Settings.SelectBox_ID           = 1004;
    VIOWindows_SSH_Prompts.Settings.File_list_ID           = 1005;
    VIOWindows_SSH_Prompts.Settings.AddRemove_ID           = 1006;
    VIOWindows_SSH_Prompts.Settings.File_Add_ID            = 1007;
    VIOWindows_SSH_Prompts.Settings.File_Remove_ID         = 1008;
  }

  // Возврат.
  return;
}
