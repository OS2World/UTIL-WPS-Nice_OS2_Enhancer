
// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Detector_DlgProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �஢��塞 ᮮ�饭��.
  switch (Message)
  {
    // �믮��塞 ����⢨� �� ᮧ����� ����.
    case WM_INITDLG:
    {
      WinPostMsg (Window, SM_INITDLG, 0, 0);
    }
    return DLG_NOFOCUS;

    case SM_INITDLG:
    {
      // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
      LONG Code_page = Enhancer.Code_page;

      // ������ ⥪�� ����� �����.
      if (Code_page == RUSSIAN)
      {
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),      StrConst_RU_Pages_Detector_form_Window_title);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),     StrConst_RU_Pages_Detector_form_Name_for_list);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT),   StrConst_RU_Pages_Detector_form_Press_Insrt);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),   StrConst_RU_Pages_Detector_form_Press_Shift);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), StrConst_RU_Pages_Detector_form_Escape);
      }
      else
      {
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),      StrConst_EN_Pages_Detector_form_Window_title);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),     StrConst_EN_Pages_Detector_form_Name_for_list);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT),   StrConst_EN_Pages_Detector_form_Press_Insrt);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),   StrConst_EN_Pages_Detector_form_Press_Shift);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), StrConst_EN_Pages_Detector_form_Escape);
      }

      if (Enhancer.Detector_dialog.Key_code != NULL)
      {
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),         0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE_STRING),  0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),        0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST_STRING), 0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),      0);

        if (Code_page == RUSSIAN)
        {
          WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), StrConst_RU_Pages_Detector_form_Press_Key);
        }
        else
        {
          WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), StrConst_EN_Pages_Detector_form_Press_Key);
        }
      }
    }
    return 0;

    // �믮��塞 ����⢨� �१ ������� �஬���⪨ �६���.
    // ���稪 �६��� ᮧ������ � 㤠����� ��। ��砫�� � ��᫥ �����襭�� �������.
    case WM_TIMER:
    {
      // �᫨ ����� ������ ��� - ��������, ���� ��।������� ����, ������.
      if (MouseIsBusy ()) return 0;

      // �᫨ ���� �ਫ������ 㬥��襭� ��� ���� - �����蠥� ������.
      {
        SWP Window_placement = {0}; WinQueryWindowPos (Enhancer.Frame_window, &Window_placement);

        if (Window_placement.fl & SWP_MINIMIZE || Window_placement.fl & SWP_HIDE)
        {
          WinDismissDlg (Window, 0);
          return 0;
        }
      }

      // ������ ���� ��࠭��.
      if (Enhancer.Detector_dialog.Detector_is_running)
      {
        // ������ ��࠭��� ����.
        HWND Active_window = WinQueryActiveWindow (HWND_DESKTOP);

        // �᫨ �� ᯨ᮪ ���� - ������.
        if (IsWinListWindow (Active_window)) return 0;

        // ������ ��࠭�� ���� �ਫ������.
        if (Active_window != Enhancer.Frame_window)
        {
          WinSetActiveWindow (HWND_DESKTOP, Enhancer.Frame_window);
        }

        // �����뢠�� ���� ��।���⥫� ������ ��㣨� ����.
        WinSetWindowPos (Window, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST);
        WinSetFocus (HWND_DESKTOP, Window);

        // ��।������ ���� � �।��� ���� ࠬ��.
        Detector_MoveToCenter (Window);

        // ����ᮢ뢠�� ����.
        WinInvalidateRect (Window, NULL, 1);
      }

      // �᫨ ���� 㧭��� ��� ��� ᯨ᪠ �᪫�祭��:
      if (Enhancer.Detector_dialog.Window_name_1 != NULL || Enhancer.Detector_dialog.Scan_dialog)
      {
        // ������ ��� ��� ᯨ᪠ �᪫�祭��.
        POINT Point = {0};
        HWND Frame_window = NULLHANDLE; HWND Client_window = NULLHANDLE;
        CHAR Title[SIZE_OF_TITLE] = ""; CHAR Name[SIZE_OF_NAME] = "";
        CHAR Exe_name[SIZE_OF_NAME] = "";

        // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
        WinQueryPointerPos (HWND_DESKTOP, &Point);
        Detector_Form.Settings.Detected_window = WinWindowFromPoint (HWND_DESKTOP, &Point, 1);

        // ������ ���, ��� ����� ��।����� ���� ��� 㪠��⥫�� ���.
        WinQueryClassName (Detector_Form.Settings.Detected_window, SIZE_OF_NAME, Name);

        // �᫨ �� ����祭� Caps Lock � Scroll Lock �����६����:
        if (!((WinGetKeyState (HWND_DESKTOP, VK_CAPSLOCK) & KEY_IS_TOGGLED) &&
               (WinGetKeyState (HWND_DESKTOP, VK_SCRLLOCK) & KEY_IS_TOGGLED)))
        {
          // ������ ���� ࠬ�� ��� ��࠭���� ����.
          Frame_window = QueryFrameWindow (Detector_Form.Settings.Detected_window);

          // ������ ��������� ����.
          WinQueryWindowText (Frame_window, SIZE_OF_TITLE, Title);

          // ������ �������� �ਫ������, ᮧ���襣� ����.
          QueryExeName (Frame_window, Exe_name);

          // ������ ���� ࠡ�祩 ������.
          Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

          // �᫨ ��� ���� - 㧭��� ���, ��� ����� ��।����� ����.
          if (Client_window != NULLHANDLE) WinQueryClassName (Client_window, SIZE_OF_NAME, Name);

          // �᫨ ���� ࠡ�祩 ������ ��� ��� ������ Shift �� ����� - ���������� �������� �ਫ������.
          if (Client_window == NULLHANDLE ||
              !(WinGetKeyState (HWND_DESKTOP, VK_SHIFT) & KEY_IS_PRESSED))
          {
            strcpy (Name, Exe_name);
          }

          // �᫨ ���� ���� ����� �����窨 ��� �� ���� ODIN - ���������� �������� �ਫ������.
          if (Name[0] == '#' || IsVIOWindow (Frame_window) ||
              IsWindowsWindow (Frame_window)) strcpy (Name, Exe_name);

          // ������� ���� �� ���� ������� � ᯨ᮪ �����.
          if (WindowIsCreatedBy (APP_NICE_ENHANCER, Frame_window) ||
              WindowIsCreatedBy (APP_NICE_ENHANCER_SHELL, Frame_window)) Name[0] = 0;

          if (!Enhancer.Detector_dialog.Include_shell_windows)
           if (IsPMShellAuxiliaryWindow (Frame_window) ||
               IsWorkplaceShellWindow (Frame_window)) Name[0] = 0;

          if (Enhancer.Detector_dialog.Include_VIO_windows_only)
           if (!IsVIOWindow (Frame_window)) Name[0] = 0;
        }

        // �����塞 � ��������� �㪢� 0x0D � 0x0A �� �஡���.
        {
          INT Length = strlen (Title); INT Count;
          for (Count = 0; Count < Length; Count ++)
           if (Title[Count] == 0x0D || Title[Count] == 0x0A)
            if (Title[Count - 1] != ' ') Title[Count] = ' ';
            else
            {
              strncpy (&Title[Count], &Title[Count + 1], Length - Count);
              Count --;
            }
        }

        // ������ ���祭�� �����.
        WinSetDlgItemText (Window, ID_DETECTORFORM_WINTITLE_STRING, Title);
        WinSetDlgItemText (Window, ID_DETECTORFORM_NAME4LIST_STRING, Name);
      }
    }
    return 0;

    // ��ࠡ��뢠�� ������ �� ������.
    case WM_CHAR:
    {
      // ����ਬ, ����� ������ �����.
      BYTE Scan_code = CHAR4FROMMP (First_parameter);
      SHORT State = SHORT1FROMMP (First_parameter);

      // �᫨ ���� 㧭��� ��� ��� ᯨ᪠ �᪫�祭��:
      if (Enhancer.Detector_dialog.Window_name_1 != NULL || Enhancer.Detector_dialog.Scan_dialog)
      {
        // �᫨ ����� ������ Insert:
        if (Scan_code == SC_INSERT || Scan_code == SC_NUM_0)
        {
          // �� ����⨨ ������:
          if (!(State & KC_KEYUP))
          {
            // ����ਬ, �����⭮ �� ��� ��� ᯨ᪠ �᪫�祭��.
            CHAR Name[SIZE_OF_NAME] = "";
            WinQueryDlgItemText (Window, ID_DETECTORFORM_NAME4LIST_STRING, SIZE_OF_NAME, Name);

            // �᫨ ��� �������⭮ - ������.
            if (Name[0] == 0) return 0;

            // �᫨ ���� �������⭮ - ������.
            if (Detector_Form.Settings.Detected_window == NULLHANDLE) return 0;

            // �᫨ � ᯨ᮪ ���� ������ ��� ���� ��� �ਫ������, ᮧ���襣� ����:
            if (Enhancer.Detector_dialog.Window_name_1 != NULL &&
                Enhancer.Detector_dialog.Window_name_2 != NULL &&
                Enhancer.Detector_dialog.Window_name_3 != NULL &&
                Enhancer.Detector_dialog.Window_name_4 != NULL &&
                Enhancer.Detector_dialog.Window_name_5 != NULL &&
                Enhancer.Detector_dialog.Window_name_6 != NULL &&
                Enhancer.Detector_dialog.Window_name_7 != NULL &&
                Enhancer.Detector_dialog.Window_name_8 != NULL)
            {
              // ������ 㪠��⥫� ��� ����ᥭ�� � ᯨ᮪ ����� ����.
              PCHAR Window_names[8] = {0};

              // �஢��塞, ���� �� ���� � ᯨ᪥.
              if (strc (Name, Enhancer.Detector_dialog.Window_name_1)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_2)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_3)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_4)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_5)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_6)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_7)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_8)) return 0;

              // ������塞 ���� � ᯨ᮪.
             {
               PCHAR Item = NULL;

               if (Enhancer.Detector_dialog.Window_name_8[0] == 0) Item = Enhancer.Detector_dialog.Window_name_8;
               if (Enhancer.Detector_dialog.Window_name_7[0] == 0) Item = Enhancer.Detector_dialog.Window_name_7;
               if (Enhancer.Detector_dialog.Window_name_6[0] == 0) Item = Enhancer.Detector_dialog.Window_name_6;
               if (Enhancer.Detector_dialog.Window_name_5[0] == 0) Item = Enhancer.Detector_dialog.Window_name_5;
               if (Enhancer.Detector_dialog.Window_name_4[0] == 0) Item = Enhancer.Detector_dialog.Window_name_4;
               if (Enhancer.Detector_dialog.Window_name_3[0] == 0) Item = Enhancer.Detector_dialog.Window_name_3;
               if (Enhancer.Detector_dialog.Window_name_2[0] == 0) Item = Enhancer.Detector_dialog.Window_name_2;
               if (Enhancer.Detector_dialog.Window_name_1[0] == 0) Item = Enhancer.Detector_dialog.Window_name_1;

               if (Item == NULL) return 0;

               strncpy (Item, Name, SIZE_OF_NAME);
             }

              // ������塞 ����, ᮤ�ঠ饥 ᯨ᮪.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_UPDATE_LIST, 0, 0);

              // ��뢠�� ��࠭���� ����஥�.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, WM_COMMAND, MPFROMLONG (OK_BUTTON_ID), 0);
            }

            // �᫨ ���� ��������� ᢥ����� �� ����:
            if (Enhancer.Detector_dialog.Scan_dialog != NULL)
            {
              // ������ ���� ࠬ�� ��� ��࠭���� ����.
              HWND Frame_window = QueryFrameWindow (Detector_Form.Settings.Detected_window);

              // ��뢠�� ����⥫�, �⮡� �� �믮���� �ॡ㥬�� ����⢨� � �������� ����ன��.
              if (Enhancer.Detector_dialog.Scan_logon_dialog)
              {
                NiceScanLogonDialog (Frame_window);
              }

              if (Enhancer.Detector_dialog.Scan_fields_in_dialog)
              {
                NiceScanIncompleteDialog (Frame_window);
              }

              if (Enhancer.Detector_dialog.Scan_message_box_dialog)
              {
                NiceScanMessageDialog (Frame_window);
              }

              // ���� �����஥ �६�.
              DosSleep (250);

              // ����頥� ����, �� ��� ���� ������ �����⮢����� ����ன��.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_READ_LIST, 0, 0);
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_UPDATE_LIST, 0, 0);
            }

            // ����뢠�� ����.
            WinDismissDlg (Window, 0);
          }
          // �� �⦠⨨ ������:
          else
          {
            // ������ "Insert" �ᯮ������ ��� ��४���⥫�.
            WinSetSysValue (HWND_DESKTOP, SV_INSERTMODE, 1);
          }
        }
      }

      // �᫨ ���� 㧭��� �������:
      if (Enhancer.Detector_dialog.Key_code != NULL)
      {
        // �� ������� ������ ������ �������� �� ����.
        if (Scan_code != SC_ESC)
        if (Scan_code != SC_LEFT_CTRL) if (Scan_code != SC_RIGHT_CTRL)
        if (Scan_code != SC_LEFT_ALT) if (Scan_code != SC_RIGHT_ALT)
        if (Scan_code != SC_LEFT_SHIFT) if (Scan_code != SC_RIGHT_SHIFT)
        if (Scan_code != SC_LEFT_WINKEY) if (Scan_code != SC_RIGHT_WINKEY)
        if (Scan_code != SC_NEWLINE) if (Scan_code != SC_NUM_ENTER)
        {
          // ���������� �������.
          *Enhancer.Detector_dialog.Key_code = Scan_code;

          {
            CHAR String[SIZE_OF_ITEM_TEXT] = "";
            CHAR Value[SIZE_OF_ITEM_TEXT] = "";

            itoa (Scan_code, Value, 16); UpperCase (Value);
            strcpy (String, "0x"); if (strlen (Value) == 1) strcat (String, "0");
            strcat (String, Value); strcat (String, " (");
            itoa (Scan_code, Value, 10);
            strcat (String, Value); strcat (String, ")");

            WinSetDlgItemText (Window, ID_DETECTORFORM_PRESSINSERT, String);
          }

          // ���뢠�� ������.
          WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), 0);

          {
            // ���塞 梥� ���� �����.
            INT Count;

            for (Count = 0; Count < 3; Count ++)
            {
              ULONG White_color = MAKERGB (255, 255, 255);
              ULONG DarkRed_color = MAKERGB (80, 0, 0);

              WinSetPresParam (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), PP_FOREGROUNDCOLOR, sizeof (ULONG), &White_color);
              DosSleep (250);
              WinSetPresParam (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), PP_FOREGROUNDCOLOR, sizeof (ULONG), &DarkRed_color);
              DosSleep (250);
            }
          }

          // ���� ������ ���� ������.
          Scan_code = SC_ESC;
        }
      }

      // �᫨ �� ������ Esc - ����뢠�� ����.
      if (Scan_code == SC_ESC)
      {
        WinDismissDlg (Window, 0);
      }
    }
    return 0;

    // ��ࠡ��뢠�� ������ �� ������.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      // �����⢥���� ������ - �����⨥ ����.
      if (WM_Control_Button_ID == ID_DETECTORFORM_ESCAPE_BUTTON)
      {
        // �����蠥� ������.
        WinDismissDlg (Window, 0);
      }
    }
    return 0;
  }

  // ������.
  return WinDefDlgProc (Window, Message, First_parameter, Second_parameter);
}
