
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Keyboard_Keys_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Keyboard_keys;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Definer.Settings.Define_keys) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Keys.Settings.Define_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Kbd_list_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Use_button_ID), Value);
    }
    return 0;

    // Распознаем настройки.
    case SM_RECOGNIZE_SELECTION:
    {
      if (!Keyboard_Keys.Settings.Key_list_is_locked)
      {
        Keyboard_Keys.Settings.Key_permission = NULL;

        HWND List_window = WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Kbd_list_ID);
        LONG Selected_string = (LONG) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));

        if (Selected_string != LIT_NONE)
        {
          if (Selected_string ==  0) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_common_keys;
          if (Selected_string ==  1) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_win_keys;
          if (Selected_string ==  2) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_function_keys;
          if (Selected_string ==  3) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_quick_keys;
          if (Selected_string ==  4) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_numeric_keys;
          if (Selected_string ==  5) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_pointer_keys;
          if (Selected_string ==  6) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_power_keys;
          if (Selected_string ==  7) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_multimedia_keys;
          if (Selected_string ==  8) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_toolkit_keys;
          if (Selected_string ==  9) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_internet_keys;
          if (Selected_string == 10) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_scrolling_keys;
          if (Selected_string == 11) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_user_keys;
          if (Selected_string == 12) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_Cherry_keys;
          if (Selected_string == 13) Keyboard_Keys.Settings.Key_permission = &Definer.Settings.Define_Compaq_keys;
        }

        if (Keyboard_Keys.Settings.Key_permission != NULL)
        {
          BYTE Value = *Keyboard_Keys.Settings.Key_permission;
          WinSendMsg (WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Use_button_ID), BM_SETCHECK, MPFROMLONG (Value), 0);
        }
      }
    }
    return 0;

    // Следим за полями ввода.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Keyboard_Keys.Settings.Define_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Definer.Settings.Define_keys = 0;
            else Definer.Settings.Define_keys = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Keys.Settings.Kbd_list_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case LN_SELECT:
          {
            WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Keys.Settings.Use_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            if (Keyboard_Keys.Settings.Key_permission != NULL)
            {
              ULONG Box_is_checked = (ULONG) WinSendMsg (WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Use_button_ID), BM_QUERYCHECK, 0, 0);

              if (Box_is_checked) *(Keyboard_Keys.Settings.Key_permission) = 0;
              else *(Keyboard_Keys.Settings.Key_permission) = 1;

              WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
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

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          PrfWriteProfileData (Ini_file, "Settings", "Define keys", &Definer.Settings.Define_keys, sizeof (BYTE));

          PrfWriteProfileData (Ini_file, "Settings", "Define common keys", &Definer.Settings.Define_common_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define win keys", &Definer.Settings.Define_win_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define function keys", &Definer.Settings.Define_function_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define quick keys", &Definer.Settings.Define_quick_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define numeric keys", &Definer.Settings.Define_numeric_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define pointer keys", &Definer.Settings.Define_pointer_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define power keys", &Definer.Settings.Define_power_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define multimedia keys", &Definer.Settings.Define_multimedia_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define toolkit keys", &Definer.Settings.Define_toolkit_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define internet keys", &Definer.Settings.Define_internet_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define scrolling keys", &Definer.Settings.Define_scrolling_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define user keys", &Definer.Settings.Define_user_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define Cherry keys", &Definer.Settings.Define_Cherry_keys, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define Compaq keys", &Definer.Settings.Define_Compaq_keys, sizeof (BYTE));

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
