
// ��� ����ࠥ� ᢥ����� �� ���� ����� ��஫� ���

// Logon_window - ���� ����� ��஫�.
VOID EXPENTRY Applier_ScanLogonDialog (HWND Logon_window)
{
  // �᫨ த�⥫�᪮� ���� �� ࠡ�稩 �⮫ - ������.
  if (WinQueryWindow (Logon_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // ����砥� ᢥ����� �� ����.
  ScanDialogWindow (Logon_window, &Applier.RTDlgMemory.Dialog_data);

  // �᫨ ��� ࠬ�� ���� �������⥭ - ������.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // �᫨ � ���� ��� �� ������ ���� ����� - ������.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // �᫨ � ���� ��� �� ������ ���� ��� ����� ⥪�� - ������.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_INPUT_FIELD) break;
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_ENTRY_FIELD) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  // �᫨ ⠪�� ���� 㦥 ���� � ᯨ᪥ - ������.
  if (Applier_WindowIsPresentInLogonDialogList (Logon_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Logon_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Logon_window, 1)) return;

  // ���������� ᢥ����� �� ����.
  bzero (&Applier.RTDlgMemory.Logon_data, sizeof (LOGONDLGBOX));

  Applier.RTDlgMemory.Logon_data.Frame_type = Applier.RTDlgMemory.Dialog_data.Frame_type;
  strcpy (Applier.RTDlgMemory.Logon_data.Exe_name, Applier.RTDlgMemory.Dialog_data.Exe_name);
  strcpy (Applier.RTDlgMemory.Logon_data.Window_title, Applier.RTDlgMemory.Dialog_data.Window_title);

  // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
  PLOGONDLGBOX DlgList[8] = {
                              &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                              &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                              &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                              &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8
                            };

  // ������塞 ᢥ����� �� ���� �� ��ࢮ� ᢮������ ���� � ᯨ᪥.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // ������塞 ����ன�� � ᯨ᮪.
     PLOGONDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Logon_data, sizeof (LOGONDLGBOX));
     strcpy (DlgList_entry->Logon_command, "Script.cmd %1 %2");

     DlgList_entry->Enabled = 1;

     // �����뢠�� ����ன��.
     Applier_WriteDialogList (DlgList_entry);

     // �� � ���浪�.
     break;
   }

  // ������.
  return;
}

// ��� ����ࠥ� ᢥ����� �� ���� ������� ���

// Dialog_window - ���� �������.
VOID EXPENTRY Applier_ScanIncompleteDialog (HWND Dialog_window)
{
  // �᫨ த�⥫�᪮� ���� �� ࠡ�稩 �⮫ - ������.
  if (WinQueryWindow (Dialog_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // ����砥� ᢥ����� �� ����.
  ScanDialogWindow (Dialog_window, &Applier.RTDlgMemory.Dialog_data);

  // �᫨ ��� ࠬ�� ���� �������⥭ - ������.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // �᫨ � ���� ��� �� ������ ���� ����� - ������.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // �᫨ � ���� ⮫쪮 ������ - ������.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type != DLG_PUSH_BUTTON) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  if (Applier_WindowIsPresentInLogonDialogList (Dialog_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Dialog_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Dialog_window, 1)) return;

  // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
  PDLGBOX DlgList[8] = {
                         &Applier.Settings.Dialogs.Incomplete_dialog_1, &Applier.Settings.Dialogs.Incomplete_dialog_2,
                         &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4,
                         &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6,
                         &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8
                       };

  // ������塞 ᢥ����� �� ���� �� ��ࢮ� ᢮������ ���� � ᯨ᪥.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // ������塞 ����ன�� � ᯨ᮪.
     PDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Dialog_data, sizeof (DLGBOX));
     DlgList_entry->Enabled = 1;

     // �����뢠�� ����ன��.
     Applier_WriteDialogList (DlgList_entry);

     // �� � ���浪�.
     break;
   }

  // ������.
  return;
}

// ��� ����ࠥ� ᢥ����� �� ���� ᮮ�饭�� ���

// Message_window - ���� ᮮ�饭��.
VOID EXPENTRY Applier_ScanMessageDialog (HWND Message_window)
{
  // �᫨ த�⥫�᪮� ���� �� ࠡ�稩 �⮫ - ������.
  if (WinQueryWindow (Message_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // ����砥� ᢥ����� �� ����.
  ScanDialogWindow (Message_window, &Applier.RTDlgMemory.Dialog_data);

  // �᫨ ��� ࠬ�� ���� �������⥭ - ������.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // �᫨ � ���� ��� �� ������ ���� ����� - ������.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // �᫨ � ���� ��� �� ����� ������ - ������.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_PUSH_BUTTON) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  if (Applier_WindowIsPresentInLogonDialogList (Message_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Message_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Message_window, 1)) return;

  // ���������� ᢥ����� �� ����.
  bzero (&Applier.RTDlgMemory.Message_data, sizeof (MSGDLGBOX));

  Applier.RTDlgMemory.Message_data.Frame_type = Applier.RTDlgMemory.Dialog_data.Frame_type;
  strcpy (Applier.RTDlgMemory.Message_data.Exe_name, Applier.RTDlgMemory.Dialog_data.Exe_name);
  strcpy (Applier.RTDlgMemory.Message_data.Window_title, Applier.RTDlgMemory.Dialog_data.Window_title);

  INT Button_number = 0;
  for (Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_PUSH_BUTTON)
    {
      Applier.RTDlgMemory.Message_data.Buttons[Button_number].Type = DLG_PUSH_BUTTON;
      strcpy (Applier.RTDlgMemory.Message_data.Buttons[Button_number].Value, Applier.RTDlgMemory.Dialog_data.Fields[Count].Value);
      Button_number ++; if (Button_number == DLG_MAX_BUTTONS) break;
    }
  }
  Applier.RTDlgMemory.Message_data.Quantity = Button_number;

  for (Count = 0; Count < Applier.RTDlgMemory.Message_data.Quantity; Count ++)
  {
    if (strc (Applier.RTDlgMemory.Message_data.Buttons[Count].Value, "Discard") ||
        strc (Applier.RTDlgMemory.Message_data.Buttons[Count].Value, "Dismiss") ||
        strc (Applier.RTDlgMemory.Message_data.Buttons[Count].Value, "Cancel")  ||
        strc (Applier.RTDlgMemory.Message_data.Buttons[Count].Value, "Close"))
    {
      Applier.RTDlgMemory.Message_data.Close_button = Count;
      break;
    }
  }

  // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
  PMSGDLGBOX DlgList[8] = {
                            &Applier.Settings.Dialogs.Message_dialog_1, &Applier.Settings.Dialogs.Message_dialog_2,
                            &Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4,
                            &Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6,
                            &Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8
                          };

  // ������塞 ᢥ����� �� ���� �� ��ࢮ� ᢮������ ���� � ᯨ᪥.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // ������塞 ����ன�� � ᯨ᮪.
     PMSGDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Message_data, sizeof (MSGDLGBOX));
     DlgList_entry->Enabled = 1;

     // �����뢠�� ����ன��.
     Applier_WriteDialogList (DlgList_entry);

     // �� � ���浪�.
     break;
   }

  // ������.
  return;
}
