
// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Keyboard_Echo_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �����⥫� �� ��࠭���.
  PPAGE Page = Enhancer.Pages.Keyboard_echo;

  // �஢��塞 ᮮ�饭��.
  switch (Message)
  {
    // �⮡ࠦ��� ����ன��.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Clicker.Settings.Keyboard_echo) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Echo.Settings.Play_sound, BM_SETCHECK, MPFROMLONG (Value), 0);
      WinEnableControl (Window, Keyboard_Echo.Settings.For_IRC, Value);
      WinEnableControl (Window, Keyboard_Echo.Settings.For_ICQ, Value);
      WinEnableControl (Window, Keyboard_Echo.Settings.Use_RAMFS, Value);

      Value = 0; if (Clicker.Settings.Keyboard_echo_for_IRC) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Echo.Settings.For_IRC, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (Clicker.Settings.Keyboard_echo_for_ICQ) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Echo.Settings.For_ICQ, BM_SETCHECK, MPFROMLONG (Value), 0);

      Value = 0; if (Clicker.Settings.Cache_echo_file) Value = 1;
      WinSendDlgItemMsg (Window, Keyboard_Echo.Settings.Use_RAMFS, BM_SETCHECK, MPFROMLONG (Value), 0);
    }
    return 0;

    // ������ �� ���ﬨ �����.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Keyboard_Echo.Settings.Play_sound)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Clicker.Settings.Keyboard_echo = 0;
            else Clicker.Settings.Keyboard_echo = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Echo.Settings.For_IRC)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Clicker.Settings.Keyboard_echo_for_IRC = 0;
            else Clicker.Settings.Keyboard_echo_for_IRC = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Echo.Settings.For_ICQ)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Clicker.Settings.Keyboard_echo_for_ICQ = 0;
            else Clicker.Settings.Keyboard_echo_for_ICQ = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Keyboard_Echo.Settings.Use_RAMFS)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Clicker.Settings.Cache_echo_file = 0;
            else Clicker.Settings.Cache_echo_file = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }
    }
    return 0;

    // ��ࠡ��뢠�� ������ �� ������.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      if (WM_Control_Button_ID == OK_BUTTON_ID)
      {
        CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
        HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

        if (Ini_file)
        {
          PrfWriteProfileData (Ini_file, "Settings", "Keyboard echo", &Clicker.Settings.Keyboard_echo, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Keyboard echo for IRC", &Clicker.Settings.Keyboard_echo_for_IRC, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Keyboard echo for ICQ", &Clicker.Settings.Keyboard_echo_for_ICQ, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Settings", "Cache echo file", &Clicker.Settings.Cache_echo_file, sizeof (BYTE));

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

  // ������.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
