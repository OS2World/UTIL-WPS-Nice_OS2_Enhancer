
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Scrolling_Settings_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Scrolling_settings;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Scroller.Settings.Smooth_scrolling) Value = 1;
      WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Smooth_scrolling_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (Scroller.Settings.Key_scrolling) Value = 1;
      WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Keyboard_scrolling_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (Scroller.Settings.Image_dragging) Value = 1;
      WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_scrolling_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);
      WinEnableControl (Window, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID, Value);
      WinEnableControl (Window, Scrolling_Settings.Settings.Mouse_pointer_button_ID, Value);

      if (Scroller.Settings.Image_dragging)
      {
        INT Selected_string = Scroller.Settings.Image_dragging - 1;
        WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID, LM_SELECTITEM, MPFROMLONG (Selected_string), MPFROMLONG (1));
      }
      else
      {
        WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID, LM_SELECTITEM, 0, MPFROMLONG (1));
      }

      Value = 0; if (Scroller.Settings.Number_of_pointer >= 2) Value = 1;
      WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_pointer_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);
      WinEnableControl (Window, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID, Value);

      if (Scroller.Settings.Number_of_pointer)
      {
        INT Selected_string = Scroller.Settings.Number_of_pointer - 1 - 1;
        WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID, LM_SELECTITEM, MPFROMLONG (Selected_string), MPFROMLONG (1));
      }
      else
      {
        WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID, LM_SELECTITEM, 0, MPFROMLONG (1));
      }
    }
    return 0;

    // Распознаем настройки.
    case SM_RECOGNIZE_SELECTION:
    {
      LONG Selected_string = (LONG) WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0);
      if (Selected_string != LIT_NONE) Scroller.Settings.Image_dragging = Selected_string + 1;

      Selected_string = (LONG) WinSendDlgItemMsg (Window, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0);
      if (Selected_string != LIT_NONE) Scroller.Settings.Number_of_pointer = Selected_string + 1 + 1;
    }
    return 0;

    // Следим за полями ввода.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Smooth_scrolling_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Scroller.Settings.Smooth_scrolling = 0;
            else Scroller.Settings.Smooth_scrolling = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Keyboard_scrolling_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Scroller.Settings.Key_scrolling = 0;
            else Scroller.Settings.Key_scrolling = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Mouse_scrolling_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked)
            {
              Scroller.Settings.Image_dragging = 0;
              Scroller.Settings.Number_of_pointer = 0;
            }
            else
            {
              Scroller.Settings.Image_dragging = 1;
              Scroller.Settings.Number_of_pointer = 1;

              WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
            }

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case CBN_ENTER:
          {
            WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Mouse_pointer_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked)
            {
              Scroller.Settings.Number_of_pointer = 0;
            }
            else
            {
              Scroller.Settings.Number_of_pointer = 2;

              WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
            }

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case CBN_ENTER:
          {
            WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
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

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          PrfWriteProfileData (Ini_file, "Settings", "Key scrolling", &Scroller.Settings.Key_scrolling, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Smooth scrolling", &Scroller.Settings.Smooth_scrolling, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Image dragging", &Scroller.Settings.Image_dragging, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Number of pointer", &Scroller.Settings.Number_of_pointer, sizeof (INT));

          PrfCloseProfile (Ini_file);

          BroadcastRSMessages ();
          NiceReadSettings ();
        }
      }

      if (WM_Control_Button_ID == PD_BUTTON_ID)
      {
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
