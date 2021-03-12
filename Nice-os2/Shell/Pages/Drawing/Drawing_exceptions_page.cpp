
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Drawing_Exceptions_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Drawing_exceptions;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем список исключений.
    case SM_UPDATE_LIST:
    {
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Drawing_Exceptions.Settings.Container_Disable_ID), Drawing_Exceptions.Settings.List_Disable_ID);

        WinSendMsg (List_window, LM_DELETEALL, 0, 0);

        if (Painter.Settings.Exceptions.Drawing_1[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_1));
        if (Painter.Settings.Exceptions.Drawing_2[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_2));
        if (Painter.Settings.Exceptions.Drawing_3[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_3));
        if (Painter.Settings.Exceptions.Drawing_4[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_4));
        if (Painter.Settings.Exceptions.Drawing_5[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_5));
        if (Painter.Settings.Exceptions.Drawing_6[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_6));
        if (Painter.Settings.Exceptions.Drawing_7[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_7));
        if (Painter.Settings.Exceptions.Drawing_8[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.Drawing_8));
      }

      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Drawing_Exceptions.Settings.Container_BorderDraw_ID), Drawing_Exceptions.Settings.List_BorderDraw_ID);

        WinSendMsg (List_window, LM_DELETEALL, 0, 0);

        if (Painter.Settings.Exceptions.BorderDrawing_1[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_1));
        if (Painter.Settings.Exceptions.BorderDrawing_2[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_2));
        if (Painter.Settings.Exceptions.BorderDrawing_3[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_3));
        if (Painter.Settings.Exceptions.BorderDrawing_4[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_4));
        if (Painter.Settings.Exceptions.BorderDrawing_5[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_5));
        if (Painter.Settings.Exceptions.BorderDrawing_6[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_6));
        if (Painter.Settings.Exceptions.BorderDrawing_7[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_7));
        if (Painter.Settings.Exceptions.BorderDrawing_8[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Painter.Settings.Exceptions.BorderDrawing_8));
      }
    }
    return 0;

    // Обрабатываем нажатия на кнопки.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      if (WM_Control_Button_ID == Drawing_Exceptions.Settings.Add_button_BorderDraw_ID)
      {
        if (Painter.Settings.Exceptions.BorderDrawing_1[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_2[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_3[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_4[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_5[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_6[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_7[0] != 0)
        if (Painter.Settings.Exceptions.BorderDrawing_8[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Painter.Settings.Exceptions.BorderDrawing_1;
          Enhancer.Detector_dialog.Window_name_2 = Painter.Settings.Exceptions.BorderDrawing_2;
          Enhancer.Detector_dialog.Window_name_3 = Painter.Settings.Exceptions.BorderDrawing_3;
          Enhancer.Detector_dialog.Window_name_4 = Painter.Settings.Exceptions.BorderDrawing_4;
          Enhancer.Detector_dialog.Window_name_5 = Painter.Settings.Exceptions.BorderDrawing_5;
          Enhancer.Detector_dialog.Window_name_6 = Painter.Settings.Exceptions.BorderDrawing_6;
          Enhancer.Detector_dialog.Window_name_7 = Painter.Settings.Exceptions.BorderDrawing_7;
          Enhancer.Detector_dialog.Window_name_8 = Painter.Settings.Exceptions.BorderDrawing_8;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Drawing_Exceptions.Settings.Remove_button_BorderDraw_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Drawing_Exceptions.Settings.Container_BorderDraw_ID), Drawing_Exceptions.Settings.List_BorderDraw_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_1, Painter.Settings.Exceptions.BorderDrawing_2, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_2, Painter.Settings.Exceptions.BorderDrawing_3, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_3, Painter.Settings.Exceptions.BorderDrawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_4, Painter.Settings.Exceptions.BorderDrawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Painter.Settings.Exceptions.BorderDrawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_2, Painter.Settings.Exceptions.BorderDrawing_3, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_3, Painter.Settings.Exceptions.BorderDrawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_4, Painter.Settings.Exceptions.BorderDrawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Painter.Settings.Exceptions.BorderDrawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_3, Painter.Settings.Exceptions.BorderDrawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_4, Painter.Settings.Exceptions.BorderDrawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Painter.Settings.Exceptions.BorderDrawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_4, Painter.Settings.Exceptions.BorderDrawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Painter.Settings.Exceptions.BorderDrawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Painter.Settings.Exceptions.BorderDrawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Painter.Settings.Exceptions.BorderDrawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Painter.Settings.Exceptions.BorderDrawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);
            break;
          }
        }

        WinPostMsg (Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0);
      }

      if (WM_Control_Button_ID == Drawing_Exceptions.Settings.Add_button_Disable_ID)
      {
        if (Painter.Settings.Exceptions.Drawing_1[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_2[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_3[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_4[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_5[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_6[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_7[0] != 0)
        if (Painter.Settings.Exceptions.Drawing_8[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Painter.Settings.Exceptions.Drawing_1;
          Enhancer.Detector_dialog.Window_name_2 = Painter.Settings.Exceptions.Drawing_2;
          Enhancer.Detector_dialog.Window_name_3 = Painter.Settings.Exceptions.Drawing_3;
          Enhancer.Detector_dialog.Window_name_4 = Painter.Settings.Exceptions.Drawing_4;
          Enhancer.Detector_dialog.Window_name_5 = Painter.Settings.Exceptions.Drawing_5;
          Enhancer.Detector_dialog.Window_name_6 = Painter.Settings.Exceptions.Drawing_6;
          Enhancer.Detector_dialog.Window_name_7 = Painter.Settings.Exceptions.Drawing_7;
          Enhancer.Detector_dialog.Window_name_8 = Painter.Settings.Exceptions.Drawing_8;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Drawing_Exceptions.Settings.Remove_button_Disable_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Drawing_Exceptions.Settings.Container_Disable_ID), Drawing_Exceptions.Settings.List_Disable_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Painter.Settings.Exceptions.Drawing_1, Painter.Settings.Exceptions.Drawing_2, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_2, Painter.Settings.Exceptions.Drawing_3, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_3, Painter.Settings.Exceptions.Drawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_4, Painter.Settings.Exceptions.Drawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_5, Painter.Settings.Exceptions.Drawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Painter.Settings.Exceptions.Drawing_2, Painter.Settings.Exceptions.Drawing_3, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_3, Painter.Settings.Exceptions.Drawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_4, Painter.Settings.Exceptions.Drawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_5, Painter.Settings.Exceptions.Drawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Painter.Settings.Exceptions.Drawing_3, Painter.Settings.Exceptions.Drawing_4, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_4, Painter.Settings.Exceptions.Drawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_5, Painter.Settings.Exceptions.Drawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Painter.Settings.Exceptions.Drawing_4, Painter.Settings.Exceptions.Drawing_5, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_5, Painter.Settings.Exceptions.Drawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Painter.Settings.Exceptions.Drawing_5, Painter.Settings.Exceptions.Drawing_6, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Painter.Settings.Exceptions.Drawing_6, Painter.Settings.Exceptions.Drawing_7, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Painter.Settings.Exceptions.Drawing_7, Painter.Settings.Exceptions.Drawing_8, SIZE_OF_NAME);
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);
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
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 1", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 2", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 3", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 4", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 5", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 6", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 7", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 8", NULL, 0);

          if (Painter.Settings.Exceptions.Drawing_1[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 1", Painter.Settings.Exceptions.Drawing_1, strlen (Painter.Settings.Exceptions.Drawing_1) + 1);
          if (Painter.Settings.Exceptions.Drawing_2[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 2", Painter.Settings.Exceptions.Drawing_2, strlen (Painter.Settings.Exceptions.Drawing_2) + 1);
          if (Painter.Settings.Exceptions.Drawing_3[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 3", Painter.Settings.Exceptions.Drawing_3, strlen (Painter.Settings.Exceptions.Drawing_3) + 1);
          if (Painter.Settings.Exceptions.Drawing_4[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 4", Painter.Settings.Exceptions.Drawing_4, strlen (Painter.Settings.Exceptions.Drawing_4) + 1);
          if (Painter.Settings.Exceptions.Drawing_5[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 5", Painter.Settings.Exceptions.Drawing_5, strlen (Painter.Settings.Exceptions.Drawing_5) + 1);
          if (Painter.Settings.Exceptions.Drawing_6[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 6", Painter.Settings.Exceptions.Drawing_6, strlen (Painter.Settings.Exceptions.Drawing_6) + 1);
          if (Painter.Settings.Exceptions.Drawing_7[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 7", Painter.Settings.Exceptions.Drawing_7, strlen (Painter.Settings.Exceptions.Drawing_7) + 1);
          if (Painter.Settings.Exceptions.Drawing_8[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Drawing 8", Painter.Settings.Exceptions.Drawing_8, strlen (Painter.Settings.Exceptions.Drawing_8) + 1);

          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 1", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 2", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 3", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 4", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 5", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 6", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 7", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 8", NULL, 0);

          if (Painter.Settings.Exceptions.BorderDrawing_1[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 1", Painter.Settings.Exceptions.BorderDrawing_1, strlen (Painter.Settings.Exceptions.BorderDrawing_1) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_2[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 2", Painter.Settings.Exceptions.BorderDrawing_2, strlen (Painter.Settings.Exceptions.BorderDrawing_2) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_3[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 3", Painter.Settings.Exceptions.BorderDrawing_3, strlen (Painter.Settings.Exceptions.BorderDrawing_3) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_4[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 4", Painter.Settings.Exceptions.BorderDrawing_4, strlen (Painter.Settings.Exceptions.BorderDrawing_4) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_5[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 5", Painter.Settings.Exceptions.BorderDrawing_5, strlen (Painter.Settings.Exceptions.BorderDrawing_5) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_6[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 6", Painter.Settings.Exceptions.BorderDrawing_6, strlen (Painter.Settings.Exceptions.BorderDrawing_6) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_7[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 7", Painter.Settings.Exceptions.BorderDrawing_7, strlen (Painter.Settings.Exceptions.BorderDrawing_7) + 1);
          if (Painter.Settings.Exceptions.BorderDrawing_8[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "BorderDrawing 8", Painter.Settings.Exceptions.BorderDrawing_8, strlen (Painter.Settings.Exceptions.BorderDrawing_8) + 1);

          PrfCloseProfile (Ini_file);

          BroadcastRSMessages ();
          NiceReadSettings ();
        }
      }

      if (WM_Control_Button_ID == PD_BUTTON_ID)
      {
        CHAR String[256] = ""; LONG Reply = 0;
        BYTE Clear_first_list = 0; BYTE Clear_second_list = 0;
        LONG Code_page = Enhancer.Code_page;

        if (Painter.Settings.Exceptions.Drawing_1[0] != 0 || Painter.Settings.Exceptions.Drawing_2[0] != 0 ||
            Painter.Settings.Exceptions.Drawing_3[0] != 0 || Painter.Settings.Exceptions.Drawing_4[0] != 0 ||
            Painter.Settings.Exceptions.Drawing_5[0] != 0 || Painter.Settings.Exceptions.Drawing_6[0] != 0 ||
            Painter.Settings.Exceptions.Drawing_7[0] != 0 || Painter.Settings.Exceptions.Drawing_8[0] != 0)
        {
          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Drawing_exceptions_Question_Disable);
          else strcpy (String, StrConst_EN_Pages_Drawing_exceptions_Question_Disable);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_first_list = 1;
        }

        if (Painter.Settings.Exceptions.BorderDrawing_1[0] != 0 || Painter.Settings.Exceptions.BorderDrawing_2[0] != 0 ||
            Painter.Settings.Exceptions.BorderDrawing_3[0] != 0 || Painter.Settings.Exceptions.BorderDrawing_4[0] != 0 ||
            Painter.Settings.Exceptions.BorderDrawing_5[0] != 0 || Painter.Settings.Exceptions.BorderDrawing_6[0] != 0 ||
            Painter.Settings.Exceptions.BorderDrawing_7[0] != 0 || Painter.Settings.Exceptions.BorderDrawing_8[0] != 0)
        {
          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Drawing_exceptions_Question_BorderDraw);
          else strcpy (String, StrConst_EN_Pages_Drawing_exceptions_Question_BorderDraw);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_second_list = 1;
        }

        if (Clear_first_list)
        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_1, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_2, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_3, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_4, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_5, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_6, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_7, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.Drawing_8, Empty_name, SIZE_OF_NAME);

          WinPostMsg (Window, SM_UPDATE_LIST, 0, 0);
        }

        if (Clear_second_list)
        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_1, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_2, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_3, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_4, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_5, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_6, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_7, Empty_name, SIZE_OF_NAME);
          memcpy (Painter.Settings.Exceptions.BorderDrawing_8, Empty_name, SIZE_OF_NAME);

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
