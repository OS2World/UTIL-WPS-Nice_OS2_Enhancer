
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Keyboard_Various_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Keyboard_various;

  // Проверяем сообщение.
  switch (Message)
  {
    // Отображаем настройки.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Controller.Settings.Turn_Num_Lock) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.Keep_NumLock, BM_SETCHECK, MPFROMLONG (Value), 0);

      WinEnableControl (Window, Keyboard_Various.Settings.NumLock_cbox, Value);
      WinEnableControl (Window, Keyboard_Various.Settings.NumKeys, Value);

      if (Controller.Settings.Turn_Num_Lock)
      {
        INT Selected_string = Controller.Settings.Turn_Num_Lock - 1;
        WinSendDlgItemMsg (Window, Keyboard_Various.Settings.NumLock_cbox, LM_SELECTITEM, MPFROMLONG (Selected_string), MPFROMLONG (1));
      }

      Value = 0; if (Controller.Settings.Define_Num_keys) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.NumKeys, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (KeyMapper.Settings.Define_Ctrl_CV) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.Ctrl_CV, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (KeyMapper.Settings.Define_Enter) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.WPS_Enter, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (KeyMapper.Settings.Define_Alt_F9) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.Alt_F9, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (KeyMapper.Settings.Discard_F3) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Various.Settings.F3, BM_SETCHECK, MPFROMLONG (Value), 0);
    }
    return 0;

    // Следим за полями ввода.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Keyboard_Various.Settings.Keep_NumLock)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Controller.Settings.Turn_Num_Lock = 0;
            else Controller.Settings.Turn_Num_Lock = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.NumLock_cbox)
      {
        switch (WM_Control_Action_ID)
        {
          case CBN_ENTER:
          {
            LONG Selected_string = (LONG) WinSendDlgItemMsg (Window, Keyboard_Various.Settings.NumLock_cbox, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0);
            if (Selected_string != LIT_NONE) Controller.Settings.Turn_Num_Lock = Selected_string + 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.NumKeys)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Controller.Settings.Define_Num_keys = 0;
            else Controller.Settings.Define_Num_keys = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.Ctrl_CV)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) KeyMapper.Settings.Define_Ctrl_CV = 0;
            else KeyMapper.Settings.Define_Ctrl_CV = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.WPS_Enter)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) KeyMapper.Settings.Define_Enter = 0;
            else KeyMapper.Settings.Define_Enter = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.Alt_F9)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) KeyMapper.Settings.Define_Alt_F9 = 0;
            else KeyMapper.Settings.Define_Alt_F9 = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Various.Settings.F3)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) KeyMapper.Settings.Discard_F3 = 0;
            else KeyMapper.Settings.Discard_F3 = 1;

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

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          PrfWriteProfileData (Ini_file, "Settings", "Turn Num Lock", &Controller.Settings.Turn_Num_Lock, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define Num keys", &Controller.Settings.Define_Num_keys, sizeof (BYTE));

          PrfWriteProfileData (Ini_file, "Settings", "Define Ctrl + C/V", &KeyMapper.Settings.Define_Ctrl_CV, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define Enter", &KeyMapper.Settings.Define_Enter, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Define Alt + F9", &KeyMapper.Settings.Define_Alt_F9, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Discard F3", &KeyMapper.Settings.Discard_F3, sizeof (BYTE));

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
