
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Rooms_Allocations_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Rooms_allocations;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Rooms.Settings.Allocate_windows_to_Rooms) Value = 1;
      WinSendDlgItemMsg (Window, Rooms_Allocations.Settings.Allocate_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      WinEnableControl (Window, Rooms_Allocations.Settings.KnownApps_button_ID, Value);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Selected_room_cmbox_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Application_list_ID), Value);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.AddRemove_ID), Rooms_Allocations.Settings.Application_Add_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.AddRemove_ID), Rooms_Allocations.Settings.Application_Remove_ID), Value);

      Value = 0; if (Rooms.Settings.Allocate_known_applications) Value = 1;
      WinSendDlgItemMsg (Window, Rooms_Allocations.Settings.KnownApps_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);
    }
    return 0;

    // Отображаем список окон.
    case SM_UPDATE_LIST:
    {
      HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Application_list_ID);

      Rooms_Allocations.Settings.Allocation_list_is_locked = 1;
      WinShowWindow (List_window, 0);

      WinSendMsg (List_window, LM_DELETEALL, 0, 0);

      if (Rooms.Settings.Allocations.Unit_1_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_1_name));
      if (Rooms.Settings.Allocations.Unit_2_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_2_name));
      if (Rooms.Settings.Allocations.Unit_3_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_3_name));
      if (Rooms.Settings.Allocations.Unit_4_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_4_name));
      if (Rooms.Settings.Allocations.Unit_5_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_5_name));
      if (Rooms.Settings.Allocations.Unit_6_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_6_name));
      if (Rooms.Settings.Allocations.Unit_7_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_7_name));
      if (Rooms.Settings.Allocations.Unit_8_name[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Rooms.Settings.Allocations.Unit_8_name));

      WinShowWindow (List_window, 1);
      Rooms_Allocations.Settings.Allocation_list_is_locked = 0;

      HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Selected_room_cmbox_ID);

      WinSendMsg (ComboBox_window, LM_SELECTITEM, MPFROMLONG (LIT_NONE), MPFROMLONG (1));
      WinSetWindowText (ComboBox_window, "");

      WinSendMsg (List_window, LM_SELECTITEM, MPFROMLONG (LIT_NONE), MPFROMLONG (1));
      WinSendMsg (List_window, LM_SELECTITEM, MPFROMLONG (0), MPFROMLONG (1));

      Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_1;
    }
    return 0;

    // Следим за полями ввода.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Rooms_Allocations.Settings.Allocate_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Rooms.Settings.Allocate_windows_to_Rooms = 0;
            else Rooms.Settings.Allocate_windows_to_Rooms = 1;

            BroadcastMessage (SM_SHOW_SETTINGS);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Rooms_Allocations.Settings.KnownApps_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Rooms.Settings.Allocate_known_applications = 0;
            else Rooms.Settings.Allocate_known_applications = 1;

            BroadcastMessage (SM_SHOW_SETTINGS);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Rooms_Allocations.Settings.Application_list_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case LN_SELECT:
          {
            if (!Rooms_Allocations.Settings.Allocation_list_is_locked)
            {
              HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Application_list_ID);

              INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
              if (Selected_string == LIT_NONE) return 0;

              {
                INT Preferable_room = NO_ROOM; Rooms_Allocations.Settings.Preferable_room_variable = NULL;

                switch (Selected_string)
                {
                  case 0: Preferable_room = Rooms.Settings.Allocations.Preferable_room_1; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_1; break;
                  case 1: Preferable_room = Rooms.Settings.Allocations.Preferable_room_2; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_2; break;
                  case 2: Preferable_room = Rooms.Settings.Allocations.Preferable_room_3; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_3; break;
                  case 3: Preferable_room = Rooms.Settings.Allocations.Preferable_room_4; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_4; break;
                  case 4: Preferable_room = Rooms.Settings.Allocations.Preferable_room_5; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_5; break;
                  case 5: Preferable_room = Rooms.Settings.Allocations.Preferable_room_6; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_6; break;
                  case 6: Preferable_room = Rooms.Settings.Allocations.Preferable_room_7; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_7; break;
                  case 7: Preferable_room = Rooms.Settings.Allocations.Preferable_room_8; Rooms_Allocations.Settings.Preferable_room_variable = &Rooms.Settings.Allocations.Preferable_room_8; break;
                }

                Selected_string = 0;

                switch (Preferable_room)
                {
                  case NORTHERN_ROOM: Selected_string = 1; break;
                  case WESTERN_ROOM:  Selected_string = 2; break;
                  case EASTERN_ROOM:  Selected_string = 3; break;
                  case SOUTHERN_ROOM: Selected_string = 4; break;
                }

                HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Selected_room_cmbox_ID);

                WinSendMsg (ComboBox_window, LM_SELECTITEM, MPFROMLONG (Selected_string), MPFROMLONG (1));
              }
            }
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Rooms_Allocations.Settings.Selected_room_cmbox_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case CBN_ENTER:
          {
            HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Selected_room_cmbox_ID);
            LONG Selected_string = (LONG) WinSendMsg (ComboBox_window, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0);

            if (Selected_string != LIT_NONE)
            {
              if (Rooms_Allocations.Settings.Preferable_room_variable != NULL)
              {
                *Rooms_Allocations.Settings.Preferable_room_variable = NO_ROOM;

                switch (Selected_string)
                {
                  case 1: *Rooms_Allocations.Settings.Preferable_room_variable = NORTHERN_ROOM; break;
                  case 2: *Rooms_Allocations.Settings.Preferable_room_variable = WESTERN_ROOM;  break;
                  case 3: *Rooms_Allocations.Settings.Preferable_room_variable = EASTERN_ROOM;  break;
                  case 4: *Rooms_Allocations.Settings.Preferable_room_variable = SOUTHERN_ROOM; break;
                }
              }
            }
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

      if (WM_Control_Button_ID == Rooms_Allocations.Settings.Application_Add_ID)
      {
        if (Rooms.Settings.Allocations.Unit_1_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_2_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_3_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_4_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_5_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_6_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_7_name[0] != 0)
        if (Rooms.Settings.Allocations.Unit_8_name[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Rooms.Settings.Allocations.Unit_1_name;
          Enhancer.Detector_dialog.Window_name_2 = Rooms.Settings.Allocations.Unit_2_name;
          Enhancer.Detector_dialog.Window_name_3 = Rooms.Settings.Allocations.Unit_3_name;
          Enhancer.Detector_dialog.Window_name_4 = Rooms.Settings.Allocations.Unit_4_name;
          Enhancer.Detector_dialog.Window_name_5 = Rooms.Settings.Allocations.Unit_5_name;
          Enhancer.Detector_dialog.Window_name_6 = Rooms.Settings.Allocations.Unit_6_name;
          Enhancer.Detector_dialog.Window_name_7 = Rooms.Settings.Allocations.Unit_7_name;
          Enhancer.Detector_dialog.Window_name_8 = Rooms.Settings.Allocations.Unit_8_name;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Rooms_Allocations.Settings.Application_Remove_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Application_list_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Rooms.Settings.Allocations.Unit_1_name, Rooms.Settings.Allocations.Unit_2_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_2_name, Rooms.Settings.Allocations.Unit_3_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_3_name, Rooms.Settings.Allocations.Unit_4_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_4_name, Rooms.Settings.Allocations.Unit_5_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_5_name, Rooms.Settings.Allocations.Unit_6_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Rooms.Settings.Allocations.Unit_2_name, Rooms.Settings.Allocations.Unit_3_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_3_name, Rooms.Settings.Allocations.Unit_4_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_4_name, Rooms.Settings.Allocations.Unit_5_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_5_name, Rooms.Settings.Allocations.Unit_6_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Rooms.Settings.Allocations.Unit_3_name, Rooms.Settings.Allocations.Unit_4_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_4_name, Rooms.Settings.Allocations.Unit_5_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_5_name, Rooms.Settings.Allocations.Unit_6_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Rooms.Settings.Allocations.Unit_4_name, Rooms.Settings.Allocations.Unit_5_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_5_name, Rooms.Settings.Allocations.Unit_6_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Rooms.Settings.Allocations.Unit_5_name, Rooms.Settings.Allocations.Unit_6_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Rooms.Settings.Allocations.Unit_6_name, Rooms.Settings.Allocations.Unit_7_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Rooms.Settings.Allocations.Unit_7_name, Rooms.Settings.Allocations.Unit_8_name, SIZE_OF_NAME);
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);
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
          PrfWriteProfileData (Ini_file, "Settings", "Attach windows to Rooms", &Rooms.Settings.Allocate_windows_to_Rooms, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Attach known applications", &Rooms.Settings.Allocate_known_applications, sizeof (BYTE));

          PrfWriteProfileData (Ini_file, "Allocations", NULL, NULL, 0);

          if (Rooms.Settings.Allocations.Unit_1_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 1 name", Rooms.Settings.Allocations.Unit_1_name, strlen (Rooms.Settings.Allocations.Unit_1_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 1", &Rooms.Settings.Allocations.Preferable_room_1, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_2_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 2 name", Rooms.Settings.Allocations.Unit_2_name, strlen (Rooms.Settings.Allocations.Unit_2_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 2", &Rooms.Settings.Allocations.Preferable_room_2, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_3_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 3 name", Rooms.Settings.Allocations.Unit_3_name, strlen (Rooms.Settings.Allocations.Unit_3_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 3", &Rooms.Settings.Allocations.Preferable_room_3, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_4_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 4 name", Rooms.Settings.Allocations.Unit_4_name, strlen (Rooms.Settings.Allocations.Unit_4_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 4", &Rooms.Settings.Allocations.Preferable_room_4, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_5_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 5 name", Rooms.Settings.Allocations.Unit_5_name, strlen (Rooms.Settings.Allocations.Unit_5_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 5", &Rooms.Settings.Allocations.Preferable_room_5, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_6_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 6 name", Rooms.Settings.Allocations.Unit_6_name, strlen (Rooms.Settings.Allocations.Unit_6_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 6", &Rooms.Settings.Allocations.Preferable_room_6, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_7_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 7 name", Rooms.Settings.Allocations.Unit_7_name, strlen (Rooms.Settings.Allocations.Unit_7_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 7", &Rooms.Settings.Allocations.Preferable_room_7, sizeof (INT));
          }
          if (Rooms.Settings.Allocations.Unit_8_name[0] != 0)
          {
            PrfWriteProfileData (Ini_file, "Allocations", "Unit 8 name", Rooms.Settings.Allocations.Unit_8_name, strlen (Rooms.Settings.Allocations.Unit_8_name) + 1);
            PrfWriteProfileData (Ini_file, "Allocations", "Preferable room 8", &Rooms.Settings.Allocations.Preferable_room_8, sizeof (INT));
          }

          PrfCloseProfile (Ini_file);

          BroadcastRSMessages ();
          NiceReadSettings (RS_UPDATE_FRAMES);
        }
      }

      if (WM_Control_Button_ID == PD_BUTTON_ID)
      {
        if (Rooms.Settings.Allocations.Unit_1_name[0] != 0 || Rooms.Settings.Allocations.Unit_2_name[0] != 0 ||
            Rooms.Settings.Allocations.Unit_3_name[0] != 0 || Rooms.Settings.Allocations.Unit_4_name[0] != 0 ||
            Rooms.Settings.Allocations.Unit_5_name[0] != 0 || Rooms.Settings.Allocations.Unit_6_name[0] != 0 ||
            Rooms.Settings.Allocations.Unit_7_name[0] != 0 || Rooms.Settings.Allocations.Unit_8_name[0] != 0)
        {
          CHAR String[256] = ""; LONG Reply = 0;
          BYTE Clear_list = 0; BYTE Clear_second_list = 0;

          LONG Code_page = Enhancer.Code_page;

          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Rooms_allocations_Question);
          else strcpy (String, StrConst_EN_Pages_Rooms_allocations_Question);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_list = 1;

          if (Clear_list)
          {
            CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);

            memcpy (Rooms.Settings.Allocations.Unit_1_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_2_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_3_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_4_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_5_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_6_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_7_name, Empty_name, SIZE_OF_NAME);
            memcpy (Rooms.Settings.Allocations.Unit_8_name, Empty_name, SIZE_OF_NAME);

            Rooms.Settings.Allocations.Preferable_room_1 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_2 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_3 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_4 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_5 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_6 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_7 = NO_ROOM;
            Rooms.Settings.Allocations.Preferable_room_8 = NO_ROOM;

            WinPostMsg (Window, SM_UPDATE_LIST, 0, 0);
          }
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
