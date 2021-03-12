
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Scrolling_Exceptions_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Scrolling_exceptions;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем список исключений.
    case SM_UPDATE_LIST:
    {
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Scrolling_Exceptions.Settings.Container_Mou_ID), Scrolling_Exceptions.Settings.List_Mou_ID);

        WinSendMsg (List_window, LM_DELETEALL, 0, 0);

        if (Scroller.Settings.Exceptions.Scrolling_1[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_1));
        if (Scroller.Settings.Exceptions.Scrolling_2[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_2));
        if (Scroller.Settings.Exceptions.Scrolling_3[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_3));
        if (Scroller.Settings.Exceptions.Scrolling_4[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_4));
        if (Scroller.Settings.Exceptions.Scrolling_5[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_5));
        if (Scroller.Settings.Exceptions.Scrolling_6[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_6));
        if (Scroller.Settings.Exceptions.Scrolling_7[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_7));
        if (Scroller.Settings.Exceptions.Scrolling_8[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.Scrolling_8));
      }

      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Scrolling_Exceptions.Settings.Container_Kbd_ID), Scrolling_Exceptions.Settings.List_Kbd_ID);

        WinSendMsg (List_window, LM_DELETEALL, 0, 0);

        if (Scroller.Settings.Exceptions.KeyScrolling_1[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_1));
        if (Scroller.Settings.Exceptions.KeyScrolling_2[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_2));
        if (Scroller.Settings.Exceptions.KeyScrolling_3[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_3));
        if (Scroller.Settings.Exceptions.KeyScrolling_4[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_4));
        if (Scroller.Settings.Exceptions.KeyScrolling_5[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_5));
        if (Scroller.Settings.Exceptions.KeyScrolling_6[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_6));
        if (Scroller.Settings.Exceptions.KeyScrolling_7[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_7));
        if (Scroller.Settings.Exceptions.KeyScrolling_8[0] != 0) WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Scroller.Settings.Exceptions.KeyScrolling_8));
      }
    }
    return 0;

    // Обрабатываем нажатия на кнопки.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      if (WM_Control_Button_ID == Scrolling_Exceptions.Settings.Add_button_Kbd_ID)
      {
        if (Scroller.Settings.Exceptions.KeyScrolling_1[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_2[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_3[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_4[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_5[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_6[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_7[0] != 0)
        if (Scroller.Settings.Exceptions.KeyScrolling_8[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Scroller.Settings.Exceptions.KeyScrolling_1;
          Enhancer.Detector_dialog.Window_name_2 = Scroller.Settings.Exceptions.KeyScrolling_2;
          Enhancer.Detector_dialog.Window_name_3 = Scroller.Settings.Exceptions.KeyScrolling_3;
          Enhancer.Detector_dialog.Window_name_4 = Scroller.Settings.Exceptions.KeyScrolling_4;
          Enhancer.Detector_dialog.Window_name_5 = Scroller.Settings.Exceptions.KeyScrolling_5;
          Enhancer.Detector_dialog.Window_name_6 = Scroller.Settings.Exceptions.KeyScrolling_6;
          Enhancer.Detector_dialog.Window_name_7 = Scroller.Settings.Exceptions.KeyScrolling_7;
          Enhancer.Detector_dialog.Window_name_8 = Scroller.Settings.Exceptions.KeyScrolling_8;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Scrolling_Exceptions.Settings.Remove_button_Kbd_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Scrolling_Exceptions.Settings.Container_Kbd_ID), Scrolling_Exceptions.Settings.List_Kbd_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_1, Scroller.Settings.Exceptions.KeyScrolling_2, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_2, Scroller.Settings.Exceptions.KeyScrolling_3, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_3, Scroller.Settings.Exceptions.KeyScrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Scroller.Settings.Exceptions.KeyScrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Scroller.Settings.Exceptions.KeyScrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_2, Scroller.Settings.Exceptions.KeyScrolling_3, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_3, Scroller.Settings.Exceptions.KeyScrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Scroller.Settings.Exceptions.KeyScrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Scroller.Settings.Exceptions.KeyScrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_3, Scroller.Settings.Exceptions.KeyScrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Scroller.Settings.Exceptions.KeyScrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Scroller.Settings.Exceptions.KeyScrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Scroller.Settings.Exceptions.KeyScrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Scroller.Settings.Exceptions.KeyScrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Scroller.Settings.Exceptions.KeyScrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Scroller.Settings.Exceptions.KeyScrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Scroller.Settings.Exceptions.KeyScrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);
            break;
          }
        }

        WinPostMsg (Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0);
      }

      if (WM_Control_Button_ID == Scrolling_Exceptions.Settings.Add_button_Mou_ID)
      {
        if (Scroller.Settings.Exceptions.Scrolling_1[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_2[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_3[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_4[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_5[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_6[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_7[0] != 0)
        if (Scroller.Settings.Exceptions.Scrolling_8[0] != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Window_name_1 = Scroller.Settings.Exceptions.Scrolling_1;
          Enhancer.Detector_dialog.Window_name_2 = Scroller.Settings.Exceptions.Scrolling_2;
          Enhancer.Detector_dialog.Window_name_3 = Scroller.Settings.Exceptions.Scrolling_3;
          Enhancer.Detector_dialog.Window_name_4 = Scroller.Settings.Exceptions.Scrolling_4;
          Enhancer.Detector_dialog.Window_name_5 = Scroller.Settings.Exceptions.Scrolling_5;
          Enhancer.Detector_dialog.Window_name_6 = Scroller.Settings.Exceptions.Scrolling_6;
          Enhancer.Detector_dialog.Window_name_7 = Scroller.Settings.Exceptions.Scrolling_7;
          Enhancer.Detector_dialog.Window_name_8 = Scroller.Settings.Exceptions.Scrolling_8;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Scrolling_Exceptions.Settings.Remove_button_Mou_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (Window, Scrolling_Exceptions.Settings.Container_Mou_ID), Scrolling_Exceptions.Settings.List_Mou_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (Scroller.Settings.Exceptions.Scrolling_1, Scroller.Settings.Exceptions.Scrolling_2, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_2, Scroller.Settings.Exceptions.Scrolling_3, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_3, Scroller.Settings.Exceptions.Scrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_4, Scroller.Settings.Exceptions.Scrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_5, Scroller.Settings.Exceptions.Scrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 1:
             memcpy (Scroller.Settings.Exceptions.Scrolling_2, Scroller.Settings.Exceptions.Scrolling_3, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_3, Scroller.Settings.Exceptions.Scrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_4, Scroller.Settings.Exceptions.Scrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_5, Scroller.Settings.Exceptions.Scrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 2:
             memcpy (Scroller.Settings.Exceptions.Scrolling_3, Scroller.Settings.Exceptions.Scrolling_4, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_4, Scroller.Settings.Exceptions.Scrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_5, Scroller.Settings.Exceptions.Scrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 3:
             memcpy (Scroller.Settings.Exceptions.Scrolling_4, Scroller.Settings.Exceptions.Scrolling_5, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_5, Scroller.Settings.Exceptions.Scrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 4:
             memcpy (Scroller.Settings.Exceptions.Scrolling_5, Scroller.Settings.Exceptions.Scrolling_6, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 5:
             memcpy (Scroller.Settings.Exceptions.Scrolling_6, Scroller.Settings.Exceptions.Scrolling_7, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 6:
             memcpy (Scroller.Settings.Exceptions.Scrolling_7, Scroller.Settings.Exceptions.Scrolling_8, SIZE_OF_NAME);
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
            break;

            case 7:
             memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);
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
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 1", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 2", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 3", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 4", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 5", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 6", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 7", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 8", NULL, 0);

          if (Scroller.Settings.Exceptions.Scrolling_1[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 1", Scroller.Settings.Exceptions.Scrolling_1, strlen (Scroller.Settings.Exceptions.Scrolling_1) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_2[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 2", Scroller.Settings.Exceptions.Scrolling_2, strlen (Scroller.Settings.Exceptions.Scrolling_2) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_3[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 3", Scroller.Settings.Exceptions.Scrolling_3, strlen (Scroller.Settings.Exceptions.Scrolling_3) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_4[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 4", Scroller.Settings.Exceptions.Scrolling_4, strlen (Scroller.Settings.Exceptions.Scrolling_4) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_5[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 5", Scroller.Settings.Exceptions.Scrolling_5, strlen (Scroller.Settings.Exceptions.Scrolling_5) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_6[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 6", Scroller.Settings.Exceptions.Scrolling_6, strlen (Scroller.Settings.Exceptions.Scrolling_6) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_7[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 7", Scroller.Settings.Exceptions.Scrolling_7, strlen (Scroller.Settings.Exceptions.Scrolling_7) + 1);
          if (Scroller.Settings.Exceptions.Scrolling_8[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "Scrolling 8", Scroller.Settings.Exceptions.Scrolling_8, strlen (Scroller.Settings.Exceptions.Scrolling_8) + 1);

          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 1", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 2", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 3", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 4", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 5", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 6", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 7", NULL, 0);
          PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 8", NULL, 0);

          if (Scroller.Settings.Exceptions.KeyScrolling_1[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 1", Scroller.Settings.Exceptions.KeyScrolling_1, strlen (Scroller.Settings.Exceptions.KeyScrolling_1) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_2[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 2", Scroller.Settings.Exceptions.KeyScrolling_2, strlen (Scroller.Settings.Exceptions.KeyScrolling_2) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_3[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 3", Scroller.Settings.Exceptions.KeyScrolling_3, strlen (Scroller.Settings.Exceptions.KeyScrolling_3) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_4[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 4", Scroller.Settings.Exceptions.KeyScrolling_4, strlen (Scroller.Settings.Exceptions.KeyScrolling_4) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_5[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 5", Scroller.Settings.Exceptions.KeyScrolling_5, strlen (Scroller.Settings.Exceptions.KeyScrolling_5) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_6[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 6", Scroller.Settings.Exceptions.KeyScrolling_6, strlen (Scroller.Settings.Exceptions.KeyScrolling_6) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_7[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 7", Scroller.Settings.Exceptions.KeyScrolling_7, strlen (Scroller.Settings.Exceptions.KeyScrolling_7) + 1);
          if (Scroller.Settings.Exceptions.KeyScrolling_8[0] != 0) PrfWriteProfileData (Ini_file, "ExceptionList", "KeyScrolling 8", Scroller.Settings.Exceptions.KeyScrolling_8, strlen (Scroller.Settings.Exceptions.KeyScrolling_8) + 1);

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

        if (Scroller.Settings.Exceptions.Scrolling_1[0] != 0 || Scroller.Settings.Exceptions.Scrolling_2[0] != 0 ||
            Scroller.Settings.Exceptions.Scrolling_3[0] != 0 || Scroller.Settings.Exceptions.Scrolling_4[0] != 0 ||
            Scroller.Settings.Exceptions.Scrolling_5[0] != 0 || Scroller.Settings.Exceptions.Scrolling_6[0] != 0 ||
            Scroller.Settings.Exceptions.Scrolling_7[0] != 0 || Scroller.Settings.Exceptions.Scrolling_8[0] != 0)
        {
          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Scrolling_exceptions_Question_Mou);
          else strcpy (String, StrConst_EN_Pages_Scrolling_exceptions_Question_Mou);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_first_list = 1;
        }

        if (Scroller.Settings.Exceptions.KeyScrolling_1[0] != 0 || Scroller.Settings.Exceptions.KeyScrolling_2[0] != 0 ||
            Scroller.Settings.Exceptions.KeyScrolling_3[0] != 0 || Scroller.Settings.Exceptions.KeyScrolling_4[0] != 0 ||
            Scroller.Settings.Exceptions.KeyScrolling_5[0] != 0 || Scroller.Settings.Exceptions.KeyScrolling_6[0] != 0 ||
            Scroller.Settings.Exceptions.KeyScrolling_7[0] != 0 || Scroller.Settings.Exceptions.KeyScrolling_8[0] != 0)
        {
          if (Code_page == RUSSIAN) strcpy (String, StrConst_RU_Pages_Scrolling_exceptions_Question_Kbd);
          else strcpy (String, StrConst_EN_Pages_Scrolling_exceptions_Question_Kbd);

          {
            CHAR Title[SIZE_OF_TITLE] = ""; GetEnhancerWindowTitle (Title);
            Reply = WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO);
          }

          if (Reply == MBID_YES) Clear_second_list = 1;
        }

        if (Clear_first_list)
        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_1, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_2, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_3, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_4, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_5, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_6, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_7, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.Scrolling_8, Empty_name, SIZE_OF_NAME);

          WinPostMsg (Window, SM_UPDATE_LIST, 0, 0);
        }

        if (Clear_second_list)
        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_1, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_2, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_3, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_4, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_5, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_6, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_7, Empty_name, SIZE_OF_NAME);
          memcpy (Scroller.Settings.Exceptions.KeyScrolling_8, Empty_name, SIZE_OF_NAME);

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
