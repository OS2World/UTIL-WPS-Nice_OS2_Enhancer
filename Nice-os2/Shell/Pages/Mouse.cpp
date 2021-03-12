
// ─── Метод для подключения класса ───

VOID Mouse_Start (LONG Settings_to_show = SET_ALL_SETTINGS)
{
  #ifdef Mouse_Buttons
  bzero (&Mouse_Buttons, sizeof (Mouse_Buttons));
  #endif

  #ifdef Mouse_VIO
  bzero (&Mouse_VIO, sizeof (Mouse_VIO));
  #endif

  #ifdef Mouse_Clipboard
  bzero (&Mouse_Clipboard, sizeof (Mouse_Clipboard));
  #endif

  #ifdef Mouse_Focus
  bzero (&Mouse_Focus, sizeof (Mouse_Focus));
  #endif

  #ifdef Mouse_Menus
  bzero (&Mouse_Menus, sizeof (Mouse_Menus));
  #endif

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Mouse_buttons_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Mouse_buttons_Name);

      Item.Settings_to_show = SET_MOUSE;
      strcpy (Item.Icon_name, "Mse_page.ico");

      Item.CreatePage     = Mouse_Buttons_CreatePage;
      Item.SetDefSettings = MouseMapper_SetPreDefinedSettings;
      Item.ReadSettings   = MouseMapper_ReadSettings;

      RememberPageItem (Enhancer.Pages.Mouse_buttons, &Item);
    }

    // Задаем ID полей ввода.
    Mouse_Buttons.Settings.ScrollBars_ID = 1001;
    Mouse_Buttons.Settings.CapsLock_ID   = 1002;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Mouse_VIO_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Mouse_VIO_Name);

      Item.Settings_to_show = SET_MOUSE;
      strcpy (Item.Icon_name, "Mse_page.ico");

      Item.CreatePage     = Mouse_VIO_CreatePage;
      Item.SetDefSettings = Clipper_SetPreDefinedSettings;
      Item.ReadSettings   = Clipper_ReadSettings;

      RememberPageItem (Enhancer.Pages.Mouse_VIO, &Item);
    }

    // Задаем ID полей ввода.
    Mouse_VIO.Settings.Mouse_button_ID          = 1001;
    Mouse_VIO.Settings.Mouse_Shift_button_ID    = 1002;
    Mouse_VIO.Settings.Mouse_Remember_button_ID = 1003;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Mouse_clipboard_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Mouse_clipboard_Name);

      Item.Settings_to_show = SET_MOUSE;
      strcpy (Item.Icon_name, "Mse_page.ico");

      Item.CreatePage     = Mouse_Clipboard_CreatePage;
      Item.SetDefSettings = MouseMapper_SetPreDefinedSettings;
      Item.ReadSettings   = MouseMapper_ReadSettings;

      RememberPageItem (Enhancer.Pages.Mouse_clipboard, &Item);
    }

    // Задаем ID полей ввода.
    Mouse_Clipboard.Settings.Mouse_cmbox_ID = 1001;
    Mouse_Clipboard.Settings.Use_MB_ID      = 1002;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Mouse_focus_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Mouse_focus_Name);

      Item.Settings_to_show = SET_MOUSE;
      strcpy (Item.Icon_name, "Mse_page.ico");

      Item.CreatePage     = Mouse_Focus_CreatePage;
      Item.SetDefSettings = MouseMapper_SetPreDefinedSettings;
      Item.ReadSettings   = MouseMapper_ReadSettings;

      RememberPageItem (Enhancer.Pages.Mouse_focus, &Item);
    }

    // Задаем ID полей ввода.
    Mouse_Focus.Settings.Scrolling_ID = 1001;
  }

  {
    // Задаем указатели в списке составляющих расширителя.
    {
      PAGE Item; PresetPageItem (&Item);

      if (Code_page == RUSSIAN) strcpy (Item.Name, StrConst_RU_Pages_Mouse_menus_Name);
      else strcpy (Item.Name, StrConst_EN_Pages_Mouse_menus_Name);

      Item.Settings_to_show = SET_MOUSE;
      strcpy (Item.Icon_name, "Mse_page.ico");

      Item.CreatePage     = Mouse_Menus_CreatePage;
      Item.SetDefSettings = MouseMapper_SetPreDefinedSettings;
      Item.ReadSettings   = MouseMapper_ReadSettings;

      RememberPageItem (Enhancer.Pages.Mouse_menus, &Item);
    }

    // Задаем ID полей ввода.
    Mouse_Menus.Settings.Sysmenu_ID = 1001;
  }

  // Возврат.
  return;
}