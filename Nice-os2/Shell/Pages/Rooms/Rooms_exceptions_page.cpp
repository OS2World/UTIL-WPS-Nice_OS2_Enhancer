
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Rooms_Exceptions_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Rooms_exceptions;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (!Rooms.Settings.Draw_wallpaper) Value = 1;
      WinSendDlgItemMsg (Window, Rooms_Exceptions.Settings.NoWallpaper_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (!Rooms.Settings.Switch_by_WarpCenter) Value = 1;
      WinSendDlgItemMsg (Window, Rooms_Exceptions.Settings.NoIcons_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (!Rooms.Settings.Switch_by_keyboard) Value = 1;
      WinSendDlgItemMsg (Window, Rooms_Exceptions.Settings.NoKeys_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);
    }
    return 0;

    // Отображаем список исключений.
    case SM_UPDATE_LIST:
    {
      HWND List_window = WinWindowFromID (WinWindowFromID (Window, Rooms_Exceptions.Settings.Container_ID), Rooms_Exceptions.Settings.List_ID);

      WinSendMsg (List_window, LM_DELETEALL, 0, 0);

      if (Rooms.Settings.Exceptions.Rooms_1[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_1));
      if (Rooms.Settings.Exceptions.Rooms_2[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_2));
      if (Rooms.Settings.Exceptions.Rooms_3[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_3));
      if (Rooms.Settings.Exceptions.Rooms_4[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_4));
      if (Rooms.Settings.Exceptions.Rooms_5[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_5));
      if (Rooms.Settings.Exceptions.Rooms_6[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_6));
      if (Rooms.Settings.Exceptions.Rooms_7[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_7));
      if (Rooms.Settings.Exceptions.Rooms_8[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Exceptions.Rooms_8));
    }
    return 0;

    // Следим за полями ввода.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Rooms_Exceptions.Settings.NoKeys_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Rooms.Settings.Switch_by_keyboard = 1;
            else Rooms.Settings.Switch_by_keyboard = 0;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Rooms_Exceptions.Settings.NoIcons_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Rooms.Settings.Switch_by_WarpCenter = 1;
            else Rooms.Settings.Switch_by_WarpCenter = 0;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Rooms_Exceptions.Settings.NoWallpaper_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Rooms.Settings.Draw_wallpaper = 1;
            else Rooms.Settings.Draw_wallpaper = 0;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }
    }
    return 0;

    // Обрабатываем нажатия на кнопки.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      if (WM_Control_Button_ID == Rooms_Exceptions.Settings.Add_button_ID)
      {
        if (Rooms.Settings.Exceptions.Rooms_1[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_2[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_3[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_4[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_5[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_6[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_7[0] != 0)
        if (Rooms.Settings.Exceptions.Rooms_8[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Rooms.Settings.Exceptions.Rooms_1;
          Enhancer.Detector_dialog.Window_name_2 = Rooms.Settings.Exceptions.Rooms_2;
          Enhancer.Detector_dialog.Window_name_3 = Rooms.Settings.Exceptions.Rooms_3;
          Enhancer.Detector_dialog.Window_name_4 = Rooms.Settings.Exceptions.Rooms_4;
          Enhancer.Detector_dialog.Window_name_5 = Rooms.Settings.Exceptions.Rooms_5;
          Enhancer.Detector_dialog.Window_name_6 = Rooms.Settings.Exceptions.Rooms_6;
          Enhancer.Detector_dialog.Window_name_7 = Rooms.Settings.Exceptions.Rooms_7;
          Enhancer.Detector_dialog.Window_name_8 = Rooms.Settings.Exceptions.Rooms_8;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Rooms_Exceptions.Settings.Remove_button_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Rooms_Exceptions.Settings.Container_ID), Rooms_Exceptions.Settings.List_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Rooms.Settings.Exceptions.Rooms_1, Rooms.Settings.Exceptions.Rooms_2, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_2, Rooms.Settings.Exceptions.Rooms_3, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_3, Rooms.Settings.Exceptions.Rooms_4, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_4, Rooms.Settings.Exceptions.Rooms_5, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_5, Rooms.Settings.Exceptions.Rooms_6, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Rooms.Settings.Exceptions.Rooms_2, Rooms.Settings.Exceptions.Rooms_3, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_3, Rooms.Settings.Exceptions.Rooms_4, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_4, Rooms.Settings.Exceptions.Rooms_5, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_5, Rooms.Settings.Exceptions.Rooms_6, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Rooms.Settings.Exceptions.Rooms_3, Rooms.Settings.Exceptions.Rooms_4, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_4, Rooms.Settings.Exceptions.Rooms_5, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_5, Rooms.Settings.Exceptions.Rooms_6, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Rooms.Settings.Exceptions.Rooms_4, Rooms.Settings.Exceptions.Rooms_5, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_5, Rooms.Settings.Exceptions.Rooms_6, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Rooms.Settings.Exceptions.Rooms_5, Rooms.Settings.Exceptions.Rooms_6, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Rooms.Settings.Exceptions.Rooms_6, Rooms.Settings.Exceptions.Rooms_7, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Rooms.Settings.Exceptions.Rooms_7, Rooms.Settings.Exceptions.Rooms_8, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);
            break;
          }
        }

        WinPostMsg (Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0);
      }

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          if (!Rooms.Settings.Switch_by_WarpCenter && !Rooms.Settings.Switch_by_keyboard)
          {
            Rooms.Settings.Switch_by_WarpCenter = 1;
            BroadcastMessage (SM_SHOW_SETTINGS);
          }

          PrfWriteProfileData (Ini_file, "Settings", "Draw wallpaper", &Rooms.Settings.Draw_wallpaper, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Switch by WarpCenter", &Rooms.Settings.Switch_by_WarpCenter, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Switch by keyboard", &Rooms.Settings.Switch_by_keyboard, sizeof (BYTE));

          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 1", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 2", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 3", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 4", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 5", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 6", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 7", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 8", NULL, 0);

          if (Rooms.Settings.Exceptions.Rooms_1[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 1", Rooms.Settings.Exceptions.Rooms_1, strlen (Rooms.Settings.Exceptions.Rooms_1) + 1);
          if (Rooms.Settings.Exceptions.Rooms_2[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 2", Rooms.Settings.Exceptions.Rooms_2, strlen (Rooms.Settings.Exceptions.Rooms_2) + 1);
          if (Rooms.Settings.Exceptions.Rooms_3[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 3", Rooms.Settings.Exceptions.Rooms_3, strlen (Rooms.Settings.Exceptions.Rooms_3) + 1);
          if (Rooms.Settings.Exceptions.Rooms_4[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 4", Rooms.Settings.Exceptions.Rooms_4, strlen (Rooms.Settings.Exceptions.Rooms_4) + 1);
          if (Rooms.Settings.Exceptions.Rooms_5[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 5", Rooms.Settings.Exceptions.Rooms_5, strlen (Rooms.Settings.Exceptions.Rooms_5) + 1);
          if (Rooms.Settings.Exceptions.Rooms_6[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 6", Rooms.Settings.Exceptions.Rooms_6, strlen (Rooms.Settings.Exceptions.Rooms_6) + 1);
          if (Rooms.Settings.Exceptions.Rooms_7[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 7", Rooms.Settings.Exceptions.Rooms_7, strlen (Rooms.Settings.Exceptions.Rooms_7) + 1);
          if (Rooms.Settings.Exceptions.Rooms_8[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Rooms 8", Rooms.Settings.Exceptions.Rooms_8, strlen (Rooms.Settings.Exceptions.Rooms_8) + 1);

          PrfCloseProfile (Ini_file);

          BroadcastRSMessages ();
          NiceReadSettings (RS_UPDATE_FRAMES);
        }
      }

      if (WM_Control_Button_ID == PD_BUTTON_ID)
      {
        CHAR String[256] = ""; LONG Reply = 0;
        BYTE Clear_list = 0;
        LONG Code_page = Enhancer.Code_page;

        if (Rooms.Settings.Exceptions.Rooms_1[0] != 0 || Rooms.Settings.Exceptions.Rooms_2[0] != 0 ||
            Rooms.Settings.Exceptions.Rooms_3[0] != 0 || Rooms.Settings.Exceptions.Rooms_4[0] != 0 ||
            Rooms.Settings.Exceptions.Rooms_5[0] != 0 || Rooms.Settings.Exceptions.Rooms_6[0] != 0 ||
            Rooms.Settings.Exceptions.Rooms_7[0] != 0 || Rooms.Settings.Exceptions.Rooms_8[0] != 0)
        {
          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Rooms_exceptions_Question);
          else strcpy (String, StrConst_EN_Pages_Rooms_exceptions_Question);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_list = 1;
        }

        if (Clear_list)
        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_1, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_2, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_3, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_4, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_5, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_6, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_7, Empty_name, SIZE_OF_NAME);
          memcpy (Rooms.Settings.Exceptions.Rooms_8, Empty_name, SIZE_OF_NAME);

          WinPostMsg (Window, SM_UPDATE_LIST, 0, 0);
        }

        if (Page->SetDefSettings) Page->SetDefSettings (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext1) Page->SetDefSettings_Ext1 (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext2) Page->SetDefSettings_Ext2 (Page->Settings_to_show);
        if (Page->SetDefSettings_Ext3) Page->SetDefSettings_Ext3 (Page->Settings_to_show);

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
