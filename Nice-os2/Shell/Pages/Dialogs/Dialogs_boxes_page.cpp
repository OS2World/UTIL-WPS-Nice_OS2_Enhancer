
// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Dialogs_Boxes_WndProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �����⥫� �� ��࠭���.
  PPAGE Page = Enhancer.Pages.Dialogs_boxes;

  // �஢��塞 ᮮ�饭��.
  switch (Message)
  {
    // �⮡ࠦ��� ����ன��.
    case SM_SHOW_SETTINGS:
    {
      BYTE Value = 0; if (Applier.Settings.Send_Yes) Value = 1;
      WinSendDlgItemMsg (Window, Dialogs_Boxes.Settings.SendYes_button_ID, BM_SETCHECK, MPFROMLONG (Value), 0);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Window_list_ID), Value);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.UseCmd_button_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Action_label_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Action_cmbox_ID), Value);

      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.AddRemove_ID), Dialogs_Boxes.Settings.Window_Add_ID), Value);
      WinEnableWindow (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.AddRemove_ID), Dialogs_Boxes.Settings.Window_Remove_ID), Value);
    }
    return 0;

    // ������塞 ᯨ᮪ ����.
    case SM_UPDATE_LIST:
    {
      INT Max_strings = 8; PCHAR Strings[8]; INT Count;
      for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], SIZE_OF_TITLE, PAG_ALLOCATE);

      strncpy (Strings[0], Applier.Settings.Dialogs.Message_dialog_1.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[1], Applier.Settings.Dialogs.Message_dialog_2.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[2], Applier.Settings.Dialogs.Message_dialog_3.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[3], Applier.Settings.Dialogs.Message_dialog_4.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[4], Applier.Settings.Dialogs.Message_dialog_5.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[5], Applier.Settings.Dialogs.Message_dialog_6.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[6], Applier.Settings.Dialogs.Message_dialog_7.Window_title, SIZE_OF_TITLE);
      strncpy (Strings[7], Applier.Settings.Dialogs.Message_dialog_8.Window_title, SIZE_OF_TITLE);

      for (Count = 0; Count < Max_strings; Count ++)
      {
        INT Space = 0; INT Length = strlen (Strings[Count]);

        for (Space = Length; Space > 7; Space --)
         if (Strings[Count][Space] == ' ')
         {
           strcpy (&Strings[Count][Space], "...");
           break;
         }
      }

      for (Count = 0; Count < Max_strings; Count ++)
       if (Strings[Count][0] != 0)
        strcat (Strings[Count], " (");

      strcat (Strings[0], Applier.Settings.Dialogs.Message_dialog_1.Exe_name);
      strcat (Strings[1], Applier.Settings.Dialogs.Message_dialog_2.Exe_name);
      strcat (Strings[2], Applier.Settings.Dialogs.Message_dialog_3.Exe_name);
      strcat (Strings[3], Applier.Settings.Dialogs.Message_dialog_4.Exe_name);
      strcat (Strings[4], Applier.Settings.Dialogs.Message_dialog_5.Exe_name);
      strcat (Strings[5], Applier.Settings.Dialogs.Message_dialog_6.Exe_name);
      strcat (Strings[6], Applier.Settings.Dialogs.Message_dialog_7.Exe_name);
      strcat (Strings[7], Applier.Settings.Dialogs.Message_dialog_8.Exe_name);

      for (Count = 0; Count < Max_strings; Count ++)
       if (Strings[Count][0] != 0)
        strcat (Strings[Count], ")");

      {
        HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Window_list_ID);

        Dialogs_Boxes.Settings.Dialog_list_is_locked = 1;
        WinShowWindow (List_window, 0);

        WinSendMsg (List_window, LM_DELETEALL, 0, 0);
        for (Count = 0; Count < Max_strings; Count ++)
        {
          if (Strings[Count][0] == 0) break;
          WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Strings[Count]));
        }

        WinShowWindow (List_window, 1);
        Dialogs_Boxes.Settings.Dialog_list_is_locked = 0;
      }

      for (Count = 0; Count < Max_strings; Count ++) { DosFreeMem (Strings[Count]); Strings[Count] = NULL; }
    }
    return 0;

    // ��⠥� ᯨ᮪ ��������.
    case SM_READ_LIST:
    {
      CHAR Settings_file_name[SIZE_OF_PATH] = ""; GetSettingsFileName (Settings_file_name);
      HINI Ini_file = OpenIniProfile (Enhancer.Application, Settings_file_name);

      if (Ini_file)
      {
        ReadDialogList (Ini_file);
        PrfCloseProfile (Ini_file);
      }
    }
    return 0;

    // ��ᯮ����� ����ன��.
    case SM_RECOGNIZE_SELECTION:
    {
      if (!Dialogs_Boxes.Settings.Dialog_list_is_locked)
      {
        PMSGDLGBOX Dialog = Dialogs_Boxes.Settings.Selected_dialog;

        {
          BYTE Enabled = 0; if (Dialog) Enabled = Dialog->Enabled;
          WinSendMsg (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.UseCmd_button_ID), BM_SETCHECK, MPFROMLONG (Enabled), 0);
        }

        {
          HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Action_cmbox_ID);

          WinSendMsg (ComboBox_window, LM_DELETEALL, 0, 0);
          WinSetWindowText (ComboBox_window, "");

          if (Dialog)
          {
            {
              INT Max_strings = 10; PCHAR Strings[10]; INT Count;
              for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

              for (Count = 0; Count < Dialog->Quantity; Count ++)
              {
                if (Dialog->Buttons[Count].Value[0] == 0) break;
                strcpy (Strings[Count], Dialog->Buttons[Count].Value);
              }
              Max_strings = Count;

              Dialogs_Boxes.Settings.Action_list_is_locked = 1;
              for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count])); }
              Dialogs_Boxes.Settings.Action_list_is_locked = 0;

              for (Count = 0; Count < Max_strings; Count ++) 
              { 
                DosFreeMem (Strings[Count]); Strings[Count] = NULL; 
              }
            }

            Dialogs_Boxes.Settings.Action_list_is_locked = 1;
            WinSendMsg (ComboBox_window, LM_SELECTITEM, MPFROMLONG (Dialog->Close_button), MPFROMLONG (1));
            Dialogs_Boxes.Settings.Action_list_is_locked = 0;
          }
        }
      }
    }
    return 0;

    // ������ �� ���ﬨ �����.
    case WM_CONTROL:
    {
      ULONG WM_Control_Window_ID = SHORT1FROMMP (First_parameter);
      ULONG WM_Control_Action_ID = SHORT2FROMMP (First_parameter);

      if (WM_Control_Window_ID == Dialogs_Boxes.Settings.SendYes_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

            if (Button_is_checked) Applier.Settings.Send_Yes = 0;
            else Applier.Settings.Send_Yes = 1;

            WinSendMsg (Window, SM_SHOW_SETTINGS, 0, 0);
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Dialogs_Boxes.Settings.Window_list_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case LN_SELECT:
          {
            if (!Dialogs_Boxes.Settings.Dialog_list_is_locked)
            {
              HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Window_list_ID);

              INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
              if (Selected_string == LIT_NONE) return 0;

              {
                Dialogs_Boxes.Settings.Selected_dialog = NULL;

                switch (Selected_string)
                {
                  case 0: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_1; break;
                  case 1: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_2; break;
                  case 2: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_3; break;
                  case 3: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_4; break;
                  case 4: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_5; break;
                  case 5: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_6; break;
                  case 6: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_7; break;
                  case 7: Dialogs_Boxes.Settings.Selected_dialog = &Applier.Settings.Dialogs.Message_dialog_8; break;
                }
              }

              WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
            }
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Dialogs_Boxes.Settings.UseCmd_button_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case BN_CLICKED:
          case BN_DBLCLICKED:
          {
            if (Dialogs_Boxes.Settings.Selected_dialog != NULL)
            {
              PMSGDLGBOX Dialog = Dialogs_Boxes.Settings.Selected_dialog;

              ULONG Button_is_checked = (ULONG) WinSendMsg (WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.UseCmd_button_ID), BM_QUERYCHECK, 0, 0);

              if (Button_is_checked) Dialog->Enabled = 0;
              else Dialog->Enabled = 1;

              WinSendMsg (Window, SM_RECOGNIZE_SELECTION, 0, 0);
            }
          }
          break;
        }
      }

      if (WM_Control_Window_ID == Dialogs_Boxes.Settings.Action_cmbox_ID)
      {
        switch (WM_Control_Action_ID)
        {
          case CBN_ENTER:
          {
            if (Dialogs_Boxes.Settings.Selected_dialog != NULL)
             if (!Dialogs_Boxes.Settings.Action_list_is_locked)
             {
               HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Action_cmbox_ID);
               LONG Selected_string = (LONG) WinSendMsg (ComboBox_window, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0);

               if (Selected_string != LIT_NONE)
               {
                 PMSGDLGBOX Dialog = Dialogs_Boxes.Settings.Selected_dialog;

                 Dialog->Close_button = Selected_string;
               }
             }
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

      if (WM_Control_Button_ID == Dialogs_Boxes.Settings.Window_Add_ID)
      {
        if (Applier.Settings.Dialogs.Message_dialog_1.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_2.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_3.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_4.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_5.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_6.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_7.Frame_type != 0)
        if (Applier.Settings.Dialogs.Message_dialog_8.Frame_type != 0) return 0;

        if (!Enhancer.Detector_dialog.Detector_is_running)
        {
          Enhancer.Detector_dialog.Customer_window = Window;

          Enhancer.Detector_dialog.Scan_dialog = 1;
          Enhancer.Detector_dialog.Scan_message_box_dialog = 1;
          Enhancer.Detector_dialog.Include_shell_windows = 1;

          OpenDETECTOR ();
        }
      }

      if (WM_Control_Button_ID == Dialogs_Boxes.Settings.Window_Remove_ID)
      {
        HWND List_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Window, Dialogs_Boxes.Settings.WinList_Container_ID), Dialogs_Boxes.Settings.ButtonBox_ID), Dialogs_Boxes.Settings.Window_list_ID);

        INT Selected_string = (INT) WinSendMsg (List_window, LM_QUERYSELECTION, MPFROMLONG (LIT_FIRST), MPFROMLONG (0));
        if (Selected_string == LIT_NONE) return 0;

        WinSendMsg (List_window, LM_DELETEITEM, MPFROMLONG (Selected_string), 0);

        {
          CHAR Empty_name[SIZE_OF_NAME] = ""; bzero (Empty_name, SIZE_OF_NAME);
          switch (Selected_string)
          {
            case 0:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_1, &Applier.Settings.Dialogs.Message_dialog_2, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_2, &Applier.Settings.Dialogs.Message_dialog_3, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_4, &Applier.Settings.Dialogs.Message_dialog_5, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 1:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_2, &Applier.Settings.Dialogs.Message_dialog_3, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_4, &Applier.Settings.Dialogs.Message_dialog_5, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 2:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_4, &Applier.Settings.Dialogs.Message_dialog_5, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 3:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_4, &Applier.Settings.Dialogs.Message_dialog_5, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 4:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 5:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_6, &Applier.Settings.Dialogs.Message_dialog_7, sizeof (MSGDLGBOX));
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 6:
             memcpy (&Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
            break;

            case 7:
             bzero (&Applier.Settings.Dialogs.Message_dialog_8, sizeof (MSGDLGBOX));
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
          PrfWriteProfileData (Ini_file, "Settings", "Send Yes", &Applier.Settings.Send_Yes, sizeof (BYTE));
          PrfWriteProfileData (Ini_file, "Dialogs", NULL, NULL, 0);

          PrfCloseProfile (Ini_file);

          WriteDialogList (NULL);

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
