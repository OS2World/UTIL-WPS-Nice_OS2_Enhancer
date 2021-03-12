// ��� ��室�� ��������� ����, ������� ����⥫� ���

VOID Applier_FindDialogWindows (VOID)
{
  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
    if (!IsFrameWindow (Window)) continue;

    // �᫨ ���� ����㯭�:
    if (FrameWindowIsAccessible (Window))
    {
      // �᫨ ��� �⮣� ���� ������ ����⢨� - �믮��塞 ���.
      PLOGONDLGBOX Logon_dialog = NULL; Applier_FindWindowInLogonDialogList (Window, 1, &Logon_dialog);
      if (Logon_dialog != NULL) if (Logon_dialog->Enabled)
       WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_LOGON_WINDOW, (MPARAM) Window, 0);

      PDLGBOX Incomplete_dialog = NULL; Applier_FindWindowInIncompleteDialogList (Window, 1, &Incomplete_dialog);
      if (Incomplete_dialog != NULL) if (Incomplete_dialog->Enabled)
       WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_COMPLETE_DIALOG, (MPARAM) Window, 0);

      PMSGDLGBOX Message_dialog = NULL; Applier_FindWindowInMessageDialogList (Window, 1, &Message_dialog);
      if (Message_dialog != NULL) if (Message_dialog->Enabled)
       WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_SEND_YES, (MPARAM) Window, 0);
    }
  }
  WinEndEnumWindows (Enumeration);

  // ������.
  return;
}

// ��� ����뢠�� ���� ᮮ�饭�� ���

// Frame_window - ���� ᮮ�饭��.
VOID Applier_SendYes (HWND Frame_window)
{
  // ������, ������ �� ����⢨� ��� �⮣� ����.
  PMSGDLGBOX Dialog = NULL; Applier_FindWindowInMessageDialogList (Frame_window, 1, &Dialog);

  // �᫨ ����⢨� ������:
  if (Dialog != NULL)
  {
    // �᫨ ����⢨� �몫�祭� - ������.
    if (!Dialog->Enabled) return;

    // ����砥� ᢥ����� �� ����.
    ScanDialogWindow (Frame_window, &Applier.RTDlgMemory.Dialog_data);

    // ������ ������, ����� ������ ���� �����.
    HWND Button = NULLHANDLE; INT Button_count = -1;
    for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
     if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_PUSH_BUTTON)
     {
       Button_count ++;
       if (Button_count == Dialog->Close_button)
       {
         Button = Applier.RTDlgMemory.Dialog_data.Fields[Count].Window;
         break;
       }
     }

    // �᫨ ������ ������� - ���뫠�� �� ᮮ�饭�� � ����� ������ �����.
    if (Button != NULLHANDLE)
    {
      // ������ ������ ��࠭��� � ����㯭��.
      WinEnableWindow (Button, 1); WinSetFocus (QueryDesktopWindow (), Button);

      // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ Enter.
      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0);

      // ���뫠�� ���.
      WinPostMsg (Button, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Button, WM_CHAR, First_parameter_2, Second_parameter_2);
    }
  }

  // ������.
  return;
}

// ��� ����⠭�������� ���祭�� � ���� ������� ���

// Frame_window - ���� �������.
VOID Applier_CompleteDialog (HWND Frame_window)
{
  // ������, ������ �� ����⢨� ��� �⮣� ����.
  PDLGBOX Dialog = NULL; Applier_FindWindowInIncompleteDialogList (Frame_window, 1, &Dialog);

  // �᫨ ����⢨� ������:
  if (Dialog != NULL)
  {
    // �᫨ ����⢨� �몫�祭� - ������.
    if (!Dialog->Enabled) return;

    // �᫨ ����⢨� ��� �⮣� ���� 㦥 �믮��﫮�� - ������.
    for (INT Count = 0; Count < APPLIER_MONITORING_DIALOG_WINDOWS; Count ++)
     if (Applier.RTSettings.Last_dialog_windows[Count] == Frame_window)
      return;

    // ����⠭�������� ᮤ�ন��� ����� �����.
    RestoreDialogFields (Frame_window, Dialog);

    // �������� ᯨ᮪ ����, ��� ������ ����⠭���������� ���� �����.
    for (Count = 0; Count < APPLIER_MONITORING_DIALOG_WINDOWS - 1; Count ++)
     Applier.RTSettings.Last_dialog_windows[Count] = Applier.RTSettings.Last_dialog_windows[Count + 1];

    // ���������� ����.
    Applier.RTSettings.Last_dialog_windows[APPLIER_MONITORING_DIALOG_WINDOWS - 1] = Frame_window;
  }

  // ������.
  return;
}

// ��� ������� ��������� ���� �ਫ������, ��뢠����� ��᫥ ����� ��஫� ���

// Title - ��६����� ��� ���������, Time - �६� ����᪠ �ਫ������.
VOID Applier_MakeLogonWindowTitle (PCHAR Title, LONG Time)
{
  // ���⠢�塞 ���������.
  strcpy (Title, "Logon - ");
  CHAR Number[25] = ""; itoa (Time, Number, 16); UpperCase (Number);
  strcat (Title, Number);

  // ������.
  return;
}

// ��� �����⠢������ ������� ��� �ᯮ������ ���

// Command - ��ப� ���� "Script.cmd %1 %2", Values � Quantity - ���祭��.
VOID Applier_PrepareLogonCommand (PCHAR Command, PDLGFIELD Values, INT Quantity)
{
  // ��室�� � ��ப� ���� ��� ����⠭���� ���祭��.
  PCHAR Str_pointers[DLG_MAX_FIELDS];
  PDLGFIELD Dlg_pointers[DLG_MAX_FIELDS];
  INT Pointers = 0;

  for (INT Count = 0; Count < Quantity; Count ++)
  {
    Str_pointers[Count] = NULL;
    Dlg_pointers[Count] = NULL;
  }

  INT Length = strlen (Command);

  for (Count = 0; Count < Length; Count ++)
   if (Command[Count] == '%')
   {
     CHAR Signature[3] = {0};
     if (Count < Length - 1)
     {
       CHAR Character = Command[Count + 1];
       if (Character >= '0' && Character <= '9') Signature[0] = Character;
     }
     if (Count < Length - 2)
     {
       CHAR Character = Command[Count + 2];
       if (Character >= '0' && Character <= '9') Signature[1] = Character;
     }

     INT Value_number = atoi (Signature) - 1;

     if (Value_number >= 0) if (Value_number < Quantity)
     {
       Str_pointers[Pointers] = &Command[Count];
       Dlg_pointers[Pointers] = &Values[Value_number];
       Pointers ++;
     }
   }

  // �᫨ ���祭�� ������ ���� ��।���:
  if (Pointers > 0)
  {
    // �஢��塞, �� �� ⥪�⮢� ���祭�� �� �����.
    BYTE First_text_value_is_found = 0;
    BYTE First_text_value_is_present = 0;
    BYTE Another_text_value_is_found = 0;
    BYTE Another_text_value_is_present = 0;

    for (INT Ptr_count = 0; Ptr_count < Pointers; Ptr_count ++)
     if (Str_pointers[Ptr_count] != NULL)
      if (Dlg_pointers[Ptr_count]->Type == DLG_INPUT_FIELD || Dlg_pointers[Ptr_count]->Type == DLG_ENTRY_FIELD)
      {
        if (!First_text_value_is_found)
        {
          First_text_value_is_found = 1;
          if (Dlg_pointers[Ptr_count]->Value[0] != 0) First_text_value_is_present = 1;
        }
        else
        {
          Another_text_value_is_found = 1;
          if (Dlg_pointers[Ptr_count]->Value[0] != 0) { Another_text_value_is_present = 1; break; }
        }
      }

    // �᫨ ��� ��ࢮ�� ���祭�� ��� �� ������ ���� ��᪮�쪮, �� ������ ⮫쪮 ��ࢮ� - ������.
    BYTE Cancel = 0;

    if ((!First_text_value_is_present) ||
        (Another_text_value_is_found && !Another_text_value_is_present)) Cancel = 1;

    if (Cancel) { Command[0] = 0; return; }
  }

  // ���⠢�塞 ����� ��ப�.
  CHAR New_command[SIZE_OF_PATH] = "";

  for (Count = 0; Count < Length; Count ++)
  {
    PCHAR Pointer = &Command[Count];

    for (INT Ptr_count = 0; Ptr_count < Pointers; Ptr_count ++)
     if (Pointer == Str_pointers[Ptr_count])
     {
       PCHAR Value = Dlg_pointers[Ptr_count]->Value;
       BYTE Space_is_present = 0; if (strstr (" ", Value)) Space_is_present = 1;

       if (Space_is_present) strcat (New_command, "\"");
       strcat (New_command, Value);
       if (Space_is_present) strcat (New_command, "\"");

       CHAR Signature[25] = "%"; itoa (Ptr_count, &Signature[1], 10);
       Count += strlen (Signature);

       break;
     }

    CHAR Character[2] = { Command[Count], 0 }; strcat (New_command, Character);
  }

  // �����뢠�� �� ����� ��ன.
  strcpy (Command, New_command);

  // ������.
  return;
}

// ��� �믮���� ������� ��᫥ �����襭�� �ਫ������, �맢��襣� ���� ����� ��஫� ���

// Process_ID - �ਫ������, �����襭�� ���ண� �������� ��⮪ Waiter.
VOID Applier_ExecuteLogonScript (PID Process_ID)
{
  // ���⠢�塞 ᯨ᮪ �������� ����⥫� ���������� ����.
  PLOGONDLGBOX DlgList[8] = {
                              &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                              &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                              &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                              &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8
                            };

  // ��室�� �ਫ������ � ᯨ᪥.
  for (INT Count = 0; Count < 8; Count ++)
  {
    PLOGONSCRIPTDATA Parameters = &DlgList[Count]->Parameters;

    if (Parameters->Process_ID == Process_ID)
    {
      // �믮��塞 �������� ���짮��⥫�� �������.
      CHAR Command[SIZE_OF_PATH] = ""; strcpy (Command, DlgList[Count]->Logon_command);
      Applier_PrepareLogonCommand (Command, Parameters->Values, Parameters->Quantity);

      if (Command[0] != 0)
      {
        // ������ ⥪�饥 �६�.
        LONG Current_time = WinGetCurrentTime (Enhancer.Application);

        // �����⠢������ ��������� ��� ����.
        CHAR Title[SIZE_OF_TITLE] = ""; Applier_MakeLogonWindowTitle (Title, Current_time);

        // �믮��塞 �������.
        CHAR Parameters[SIZE_OF_PATH] = "";
        PCHAR Space = strstr (" ", Command);
        if (Space) { strcpy (Parameters, Space + 1); *Space = 0; }

        HAPP PM_Handle = Execute (Command, Parameters, Title, SWP_MINIMIZE);

        // �᫨ �ਫ������ �뫮 �맢��� - ᮯ஢������ ���.
        if (PM_Handle != NULLHANDLE)
        {
          // ����뢠�� ��६����� ��� �⢥� �� ��⮪�.
          Thread_responds.Thread_is_created = 0;

          // ������� ��⮪.
          TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread (&Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE);
          // �᫨ �� ᮧ��� - ����, ���� � ��� �㤥� ᮧ���� ��।� ᮮ�饭��.
          if (Thread_is_created == NO_ERROR) while (Thread_responds.Thread_is_created == 0) { Retard (); }

          // �᫨ ��⮪ 㤠���� ᮧ����:
          if (Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1)
          {
            // ���뫠�� ᮮ�饭�� � ��⮪.
            WinPostQueueMsg (Enhancer.Modules.Waiter->Message_queue, SM_ESCORT_LOGON, (MPARAM) Current_time, 0);

            // ���뢠�� �� ����.
            Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
          }
        }
      }

      // ����뢠�� ����ன��.
      bzero (Parameters, sizeof (LOGONSCRIPTDATA));

      // ����������, �� ����⢨� �믮�����.
      DlgList[Count]->Action_performed = 1;
    }
  }

  // ������.
  return;
}

// ��� �஢����, ��⠫��� �� �� ���� ����� ��஫� ���

VOID Applier_CheckLogonWindows (VOID)
{
  // ����ਬ, ���� �� �� ���� ����� ��஫�.
  BYTE Logon_in_process = 0;

  for (INT Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS; Count ++)
  {
    HWND Logon_window = Applier.RTDlgMemory.Logon_windows[Count].Window;
    if (!WinIsWindow (WinQueryAnchorBlock (Logon_window), Logon_window))
     Applier.RTDlgMemory.Logon_windows[Count].Window = NULLHANDLE;

    if (Applier.RTDlgMemory.Logon_windows[Count].Window != NULLHANDLE) Logon_in_process = 1;
  }

  Applier.RTSettings.Logon_in_process = Logon_in_process;

  // ������.
  return;
}

// ��� �஢���� ���ﭨ� ���� � ��稭��� �믮������ ����⢨� ���

// Dismissed_frame - ���� ࠬ��, ����砢襥 ᮮ�饭�� � �����⨨.
VOID Applier_CheckLogonWindowsAndStartWaiting (HWND Dismissed_frame)
{
  // ����ਬ, ����� ���� ��� ����� ��஫� �뫨 �������.
  PLOGONDLGBOX Task_list[8] = {0}; INT Tasks = 0;

  for (INT Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS; Count ++)
   if (Applier.RTDlgMemory.Logon_windows[Count].Window == Dismissed_frame )
   {
     // �஢��塞, ����� �� ���� ����� ������ "�⬥��". �஡㥬 ������� ������� ��� �ᯮ������.
     PLOGONDLGBOX Related_dialog = Applier.RTDlgMemory.Logon_windows[Count].Related_dialog;
     CHAR Command[SIZE_OF_PATH] = ""; strcpy (Command, Related_dialog->Logon_command);

     PDLGBOX Dialog = &Applier.RTDlgMemory.Logon_windows[Count].Dialog;
     Applier_PrepareLogonCommand (Command, Dialog->Fields, Dialog->Quantity);

     BYTE Cancel = 0; if (Command[0] == 0) Cancel = 1;

     if (!Cancel)
     {
       // ����ਬ, ���� �� 㦥 � ᯨ᪥ ������� ����⢨� ��� �⮣� ����.
       BYTE Task_is_exists = 0;

       for (INT Pointer = 0; Pointer < 8; Pointer ++)
       {
         if (Task_list[Pointer] == NULL) break;
         if (Task_list[Pointer] == Related_dialog) { Task_is_exists = 1; break; }
       }

       // ������塞 �������, �᫨ ��� �� �� �뫮 ���������:
       if (!Task_is_exists)
       {
         // ���������� ���祭��.
         for (INT Number = 0; Number < Dialog->Quantity; Number ++)
          memcpy (&Related_dialog->Parameters.Values[Number], &Dialog->Fields[Number], sizeof (DLGFIELD));

         Related_dialog->Parameters.Quantity = Dialog->Quantity;

         // ���������� �ਫ������.
         Related_dialog->Parameters.Process_ID = Applier.RTDlgMemory.Logon_windows[Count].Process_ID;

         // ���������� �������.
         Task_list[Tasks] = Related_dialog;
         Tasks ++;
       }
     }

     // ����뢠�� ���祭�� ��� ����.
     bzero (&Applier.RTDlgMemory.Logon_windows[Count], sizeof (LOGONWNDINFO));
   }

  // �믮��塞 �������, ᮧ����� ��⮪� ��� �������� �����襭�� �ਫ������.
  for (Count = 0; Count < Tasks; Count ++)
  {
    // �᫨ ���� �������:
    PLOGONDLGBOX Task = Task_list[Count];
    PID Process_ID = Task->Parameters.Process_ID;

    if (Process_ID != NULLHANDLE)
    {
      // ����뢠�� ��६����� ��� �⢥� �� ��⮪�.
      Thread_responds.Thread_is_created = 0;

      // ������� ��⮪.
      TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread (&Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE);
      // �᫨ �� ᮧ��� - ����, ���� � ��� �㤥� ᮧ���� ��।� ᮮ�饭��.
      if (Thread_is_created == NO_ERROR) while (Thread_responds.Thread_is_created == 0) { Retard (); }

      // �᫨ ��⮪ 㤠���� ᮧ����:
      if (Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1)
      {
        // ���뫠�� ᮮ�饭�� � ��⮪.
        HMQ Owner_queue = Enhancer.Modules.Applier->Message_queue;
        WinPostQueueMsg (Enhancer.Modules.Waiter->Message_queue, SM_WAIT_EXISTING_PROCESS, (MPARAM) Process_ID, (MPARAM) Owner_queue);

        // ���뢠�� �� ����.
        Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
      }
    }
  }

  // �஢��塞, ���� �� �� ���� ����� ��஫�.
  Applier_CheckLogonWindows ();

  // ������.
  return;
}

// ��� �롨ࠥ� ���祭�� �� ���� ����� ��஫� ���

// Frame_window - ���� �������.
VOID Applier_WatchLogonValues (HWND Frame_window)
{
  // ��室�� ���� � ᯨ᪥ ��᫥�������� ���� � ���������� ���祭��.
  PLOGONWNDINFO Target = NULL;

  for (INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count --)
   if (Applier.RTDlgMemory.Logon_windows[Count].Window == Frame_window)
   {
     Target = &Applier.RTDlgMemory.Logon_windows[Count];
     break;
   }

  // �᫨ ��� �������:
  if (Target != NULL)
  {
    // ����砥� ᢥ����� �� ����. ��� 㢥��祭�� ᪮��� �롨����� ⮫쪮 ����, ������� �� ����� ��஫�.
    ScanDialogWindow (Frame_window, &Applier.RTDlgMemory.Dialog_data, SCAN_INPUT_FIELDS);

    // �᫨ ���祭�� �� �� �뫨 ��७�ᥭ�:
    if (Target->Dialog.Quantity == 0)
    {
      // ��७�ᨬ ����� ��� ����.
      memcpy (&Target->Dialog, &Applier.RTDlgMemory.Dialog_data, sizeof (DLGBOX));
    }
    // � �᫨ ��� 㦥 �뫨 ����祭� ࠭��:
    else
    {
      // ���������� ���祭��.
      INT Fields = 0;

      for (Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
      {
        // ��᫮ ����� � ���� ����� ��������, �᫨ ��� ����砥� �� �� �६� �����. ��室�� ��.
        LONG Source_type = Applier.RTDlgMemory.Dialog_data.Fields[Count].Type;
        LONG Target_type = Target->Dialog.Fields[Count].Type;

        if (Source_type == Target_type)
        {
          // ���� ����� ����� ��஫�. �஢��塞, ⠪ �� ��.
          BYTE Source_is_empty = 0; if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Value[0] == 0) Source_is_empty = 1;
          BYTE Target_is_empty = 0; if (Target->Dialog.Fields[Count].Value[0] == 0) Target_is_empty = 1;

          BYTE All_OK = 1; if (Source_is_empty && !Target_is_empty) All_OK = 0;
          if (All_OK) strcpy (Target->Dialog.Fields[Count].Value, Applier.RTDlgMemory.Dialog_data.Fields[Count].Value);

          Fields ++;
        }
      }

      Target->Dialog.Quantity = Fields;
    }
  }

  // ������.
  return;
}

// ��� ��ᯮ����� � ���������� ���� ����� ��஫� ���

// Frame_window - ���� �������.
VOID Applier_CheckLogonWindow (HWND Frame_window)
{
  // ������, ������ �� ����⢨� ��� �⮣� ����.
  PLOGONDLGBOX Dialog = NULL; Applier_FindWindowInLogonDialogList (Frame_window, 1, &Dialog);

  // �᫨ ����⢨� ������:
  if (Dialog != NULL)
  {
    // �᫨ ����⢨� �몫�祭� - ������.
    if (!Dialog->Enabled) return;

    // �᫨ ����⢨� 㦥 �믮��﫮�� � ��ன ࠧ �믮����� ��� �� ���� - ������.
    if (Dialog->Only_once) if (Dialog->Action_performed) return;

    // ����������, �� ⠪�� ���� ����.
    Applier.RTSettings.Logon_in_process = 1;

    // �᫨ ��� ���� � ᯨ᪥ ��᫥�������� ���� - ������.
    for (INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count --)
     if (Applier.RTDlgMemory.Logon_windows[Count].Window == Frame_window)
      return;

    // �������� ᯨ᮪.
    for (Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS - 1; Count ++)
     memcpy (&Applier.RTDlgMemory.Logon_windows[Count], &Applier.RTDlgMemory.Logon_windows[Count + 1], sizeof (LOGONWNDINFO));

    // ���������� ����, ᮧ���襥 ��� �ਫ������ � ����ன��, �易��� � �����. ���祭�� ����� � ��� ᠬ�� ���� ���������.
    bzero (&Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1], sizeof (LOGONWNDINFO));

    PID Process_ID = QueryWindowRealProcessID (Frame_window);

    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Window = Frame_window;
    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Process_ID = Process_ID;
    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Related_dialog = Dialog;


    // �⮡� ���祭�� ����� �⠫� ������� - ���뫠�� ᮮ�饭�� � ��⮪.
    WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_LOGON_VALUES, (MPARAM) Frame_window, 0);
  }

  // ������.
  return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Applier_ApplierMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Applier->Priority = MAKELONG (Class, Delta);
  }

  // ��ᯮ����� � ���������� ���� ����� ��஫�.
  if (Message->msg == SM_LOGON_WINDOW)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ��ᯮ����� � ���������� ���.
    Applier_CheckLogonWindow (Frame_window);
  }

  // ���������� ���祭�� � ����� ����� ��஫�.
  if (Message->msg == SM_LOGON_VALUES)
  {
    // �᫨ �� ������ ���� ��� ����� ��஫� ��� - ������.
    if (!Applier.RTSettings.Logon_in_process) return;

    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // �롨ࠥ� ���祭��, ���࠭�� � ����.
    Applier_WatchLogonValues (Frame_window);
  }

  // �஢��塞 ���ﭨ� ���� ��� ����� ��஫�.
  if (Message->msg == SM_LOGON_ACTION)
  {
    // �᫨ �� ������ ���� ��� ����� ��஫� ��� - ������.
    if (!Applier.RTSettings.Logon_in_process) return;

    // ������ �����襥�� ����.
    HWND Dismissed_frame = (HWND) Message->mp1;

    // �᫨ ��� �� ������ - ������.
    if (Dismissed_frame == NULLHANDLE) return;

    // �஢��塞 ���ﭨ� ���� � ��稭��� �믮������ ����⢨�, �᫨ �� �ॡ����.
    Applier_CheckLogonWindowsAndStartWaiting (Dismissed_frame);
  }

  // �஢��塞 ����⢮����� ���� ����� ��஫�.
  if (Message->msg == SM_LOGON_CHECK) Applier_CheckLogonWindows ();

  // �믮��塞 ������� ���짮��⥫� ��᫥ �����襭�� �ਫ������, �맢��襣� ���� ����� ��஫�.
  if (Message->msg == SM_LOGON_PROCESS_STOPPED)
  {
    // ������ �ਫ������.
    PID Process_ID = (PID) Message->mp1;

    // �᫨ ��� �������⭮ - ������.
    if (Process_ID == NULLHANDLE) return;

    // �����蠥� �ਮ���.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // �믮��塞 �������.
    Applier_ExecuteLogonScript (Process_ID);

    // ����⠭�������� �ਮ���.
    LONG Class = SHORT1FROMLONG (Enhancer.Modules.Applier->Priority);
    LONG Delta = SHORT2FROMLONG (Enhancer.Modules.Applier->Priority);
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);
  }

  // ����⠭�������� ���� ����� � ����� ��������.
  if (Message->msg == SM_COMPLETE_DIALOG)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ����뢠�� ���.
    Applier_CompleteDialog (Frame_window);
  }

  // ����뢠�� ���� ᮮ�饭��.
  if (Message->msg == SM_SEND_YES)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ����뢠�� ���.
    Applier_SendYes (Frame_window);
  }

  // ��室�� ��������� ����, ������� ����⥫�.
  if (Message->msg == SM_FIND_DIALOG_WINDOWS)
  {
    // �஢��塞 �������騥 ���� ����� ��஫�.
    if (Applier.Settings.Script_after_Logon) Applier_CheckLogonWindows ();

    // �믮��塞 ���� ����� ����.
    Applier_FindDialogWindows ();
  }

  // ������.
  return;
}

// ��� ��⮪ ��� �믮������ ����⢨� � ������ ������� ���

VOID Applier_ApplierThread (VOID)
{
  // ��।��塞 ��⮪ � ��⥬�.
  HAB Thread = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Thread == NULLHANDLE)
  {
    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Applier->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Applier->Message_queue == NULLHANDLE)
  {
    // �����蠥� ࠡ��� ��⮪�.
    WinTerminate (Thread);

    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ��⮪ ᮧ��� �ᯥ譮.
  Thread_responds.Thread_is_created = 1;

  // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
  QMSG Message = {0};
  while (WinGetMsg (Thread, &Message, 0, 0, 0))
  {
    // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
    QMSG Next_message = {0};
    WinPeekMsg (Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE);
    if (Next_message.msg == Message.msg)
     if (Next_message.mp1 == Message.mp1)
      if (Next_message.mp2 == Message.mp2)
       if (Next_message.hwnd == Message.hwnd) continue;

    // ��ࠡ��뢠�� ᮮ�饭��.
    Applier_ApplierMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
