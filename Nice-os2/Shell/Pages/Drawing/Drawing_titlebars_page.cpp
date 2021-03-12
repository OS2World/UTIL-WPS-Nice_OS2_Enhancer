
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Drawing_Titlebars_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Drawing_titlebars;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      WinSendMsg (Window, SM_SET_PRESENTATION_PARAMETERS, 0, 0);
    }
    return 0;

    case SM_SET_PRESENTATION_PARAMETERS:
    {
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Active_ID), PP_FOREGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.AT_Text_color);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Active_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.AT_Background_color);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Inactive_ID), PP_FOREGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.IT_Text_color);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Inactive_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.IT_Background_color);

      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_1_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.AT_Color_1);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_2_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.AT_Color_2);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_3_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.AT_Color_3);

      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_1_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.IT_Color_1);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_2_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.IT_Color_2);
      WinSetPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_3_ID), PP_BACKGROUNDCOLOR, sizeof (ULONG), &Painter.Settings.IT_Color_3);
    }
    return 0;

    // Применяем выбранную тему.
    case SM_RECOGNIZE_THEME:
    {
      THEMEPAGEDEF Input_fields; bzero (&Input_fields, sizeof (Input_fields));

      Input_fields.NeonPalette_FillTB_window = WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_FillTB_ID);
      Input_fields.NeonPalette_Container_window = WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID);

      Input_fields.NeonPalette_Active_1_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_1_ID);
      Input_fields.NeonPalette_Active_2_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_2_ID);
      Input_fields.NeonPalette_Active_3_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_3_ID);

      Input_fields.NeonPalette_Inactive_1_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_1_ID);
      Input_fields.NeonPalette_Inactive_2_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_2_ID);
      Input_fields.NeonPalette_Inactive_3_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_3_ID);

      RecognizeSelectedTheme (&Input_fields);
    }
    return 0;

    // Обрабатываем нажатия на кнопки.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      if (WM_Control_Button_ID == Drawing_Titlebars.Settings.WinTitles_Button_ID)
      {
        ShowWPSColorPalette ();
      }

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          {
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Active_ID), PP_FOREGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.AT_Text_color, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Active_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.AT_Background_color, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Inactive_ID), PP_FOREGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.IT_Text_color, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.WinTitles_Container_ID), Drawing_Titlebars.Settings.WinTitles_Palette_ID), Drawing_Titlebars.Settings.WinTitles_Inactive_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.IT_Background_color, QPF_NOINHERIT);

            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_1_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.AT_Color_1, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_2_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.AT_Color_2, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Active_3_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.AT_Color_3, QPF_NOINHERIT);

            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_1_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.IT_Color_1, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_2_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.IT_Color_2, QPF_NOINHERIT);
            WinQueryPresParam (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Drawing_Titlebars.Settings.NeonPalette_Container_ID), Drawing_Titlebars.Settings.NeonPalette_Palette_ID), Drawing_Titlebars.Settings.NeonPalette_Inactive_3_ID), PP_BACKGROUNDCOLOR, 0, NULL, sizeof (ULONG), &Painter.Settings.IT_Color_3, QPF_NOINHERIT);
          }

          PrfWriteProfileData (Ini_file, "Drawing", "AT Color", &Painter.Settings.AT_Text_color, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "AT BG Color", &Painter.Settings.AT_Background_color, sizeof (LONG));

          PrfWriteProfileData (Ini_file, "Drawing", "IT Color", &Painter.Settings.IT_Text_color, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "IT BG Color", &Painter.Settings.IT_Background_color, sizeof (LONG));

          PrfWriteProfileData (Ini_file, "Drawing", "AT Color 1", &Painter.Settings.AT_Color_1, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "AT Color 2", &Painter.Settings.AT_Color_2, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "AT Color 3", &Painter.Settings.AT_Color_3, sizeof (LONG));

          PrfWriteProfileData (Ini_file, "Drawing", "IT Color 1", &Painter.Settings.IT_Color_1, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "IT Color 2", &Painter.Settings.IT_Color_2, sizeof (LONG));
          PrfWriteProfileData (Ini_file, "Drawing", "IT Color 3", &Painter.Settings.IT_Color_3, sizeof (LONG));

          PrfWriteProfileData (Ini_file, "Colors", NULL, NULL, 0);

          PrfCloseProfile (Ini_file);

          BroadcastRSMessages ();
          NiceReadSettings (RS_UPDATE_FRAMES);
        }
      }

      if (WM_Control_Button_ID == PD_BUTTON_ID)
      {
        if (Page->SetDefSettings) Page->SetDefSettings (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext1) Page->SetDefSettings_Ext1 (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext2) Page->SetDefSettings_Ext2 (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext3) Page->SetDefSettings_Ext3 (Page->Settings_to_show);

        WinSendMsg (Window, SM_SET_PRESENTATION_PARAMETERS, 0, 0);
        WinPostMsg (Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0);
      }

      if (WM_Control_Button_ID == HP_BUTTON_ID)
      {
        Help (Page->Settings_to_show, Enhancer.Code_page);
      }
    }
    return 0;
  }

  // Возврат.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
