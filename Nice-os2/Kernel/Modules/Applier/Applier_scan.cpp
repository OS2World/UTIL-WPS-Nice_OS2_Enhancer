
// ─── Собирает сведения об окне ввода пароля ───

// Logon_window - окно ввода пароля.
VOID EXPENTRY Applier_ScanLogonDialog (HWND Logon_window)
{
  // Если родительское окно не рабочий стол - возврат.
  if (WinQueryWindow (Logon_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // Получаем сведения об окне.
  ScanDialogWindow (Logon_window, &Applier.RTDlgMemory.Dialog_data);

  // Если вид рамки окна неизвестен - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // Если в окне нет ни одного поля ввода - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // Если в окне нет ни одного поля для набора текста - возврат.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_INPUT_FIELD) break;
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_ENTRY_FIELD) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  // Если такое окно уже есть в списке - возврат.
  if (Applier_WindowIsPresentInLogonDialogList (Logon_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Logon_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Logon_window, 1)) return;

  // Запоминаем сведения об окне.
  bzero (&Applier.RTDlgMemory.Logon_data, sizeof (LOGONDLGBOX));

  Applier.RTDlgMemory.Logon_data.Frame_type = Applier.RTDlgMemory.Dialog_data.Frame_type;
  strcpy (Applier.RTDlgMemory.Logon_data.Exe_name, Applier.RTDlgMemory.Dialog_data.Exe_name);
  strcpy (Applier.RTDlgMemory.Logon_data.Window_title, Applier.RTDlgMemory.Dialog_data.Window_title);

  // Составляем список известных расширителю диалоговых окон.
  PLOGONDLGBOX DlgList[8] = {
                              &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                              &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                              &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                              &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8
                            };

  // Добавляем сведения об окне на первое свободное место в списке.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // Добавляем настройки в список.
     PLOGONDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Logon_data, sizeof (LOGONDLGBOX));
     strcpy (DlgList_entry->Logon_command, "Script.cmd %1 %2");

     DlgList_entry->Enabled = 1;

     // Записываем настройки.
     Applier_WriteDialogList (DlgList_entry);

     // Все в порядке.
     break;
   }

  // Возврат.
  return;
}

// ─── Собирает сведения об окне диалога ───

// Dialog_window - окно диалога.
VOID EXPENTRY Applier_ScanIncompleteDialog (HWND Dialog_window)
{
  // Если родительское окно не рабочий стол - возврат.
  if (WinQueryWindow (Dialog_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // Получаем сведения об окне.
  ScanDialogWindow (Dialog_window, &Applier.RTDlgMemory.Dialog_data);

  // Если вид рамки окна неизвестен - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // Если в окне нет ни одного поля ввода - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // Если в окне только кнопки - возврат.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type != DLG_PUSH_BUTTON) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  if (Applier_WindowIsPresentInLogonDialogList (Dialog_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Dialog_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Dialog_window, 1)) return;

  // Составляем список известных расширителю диалоговых окон.
  PDLGBOX DlgList[8] = {
                         &Applier.Settings.Dialogs.Incomplete_dialog_1, &Applier.Settings.Dialogs.Incomplete_dialog_2,
                         &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4,
                         &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6,
                         &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8
                       };

  // Добавляем сведения об окне на первое свободное место в списке.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // Добавляем настройки в список.
     PDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Dialog_data, sizeof (DLGBOX));
     DlgList_entry->Enabled = 1;

     // Записываем настройки.
     Applier_WriteDialogList (DlgList_entry);

     // Все в порядке.
     break;
   }

  // Возврат.
  return;
}

// ─── Собирает сведения об окне сообщения ───

// Message_window - окно сообщения.
VOID EXPENTRY Applier_ScanMessageDialog (HWND Message_window)
{
  // Если родительское окно не рабочий стол - возврат.
  if (WinQueryWindow (Message_window, QW_PARENT) != QueryDesktopWindow ()) return;

  // Получаем сведения об окне.
  ScanDialogWindow (Message_window, &Applier.RTDlgMemory.Dialog_data);

  // Если вид рамки окна неизвестен - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Frame_type == FT_UNKNOWN) return;

  // Если в окне нет ни одного поля ввода - возврат.
  if (Applier.RTDlgMemory.Dialog_data.Quantity == 0) return;

  // Если в окне нет ни одной кнопки - возврат.
  for (INT Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
  {
    if (Applier.RTDlgMemory.Dialog_data.Fields[Count].Type == DLG_PUSH_BUTTON) break;
    if (Count == Applier.RTDlgMemory.Dialog_data.Quantity - 1) return;
  }

  if (Applier_WindowIsPresentInLogonDialogList (Message_window, 1) ||
      Applier_WindowIsPresentInIncompleteDialogList (Message_window, 1) ||
      Applier_WindowIsPresentInMessageDialogList (Message_window, 1)) return;

  // Запоминаем сведения об окне.
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

  // Составляем список известных расширителю диалоговых окон.
  PMSGDLGBOX DlgList[8] = {
                            &Applier.Settings.Dialogs.Message_dialog_1, &Applier.Settings.Dialogs.Message_dialog_2,
                            &Applier.Settings.Dialogs.Message_dialog_3, &Applier.Settings.Dialogs.Message_dialog_4,
                            &Applier.Settings.Dialogs.Message_dialog_5, &Applier.Settings.Dialogs.Message_dialog_6,
                            &Applier.Settings.Dialogs.Message_dialog_7, &Applier.Settings.Dialogs.Message_dialog_8
                          };

  // Добавляем сведения об окне на первое свободное место в списке.
  for (Count = 0; Count < 8; Count ++)
   if (DlgList[Count]->Frame_type == 0)
   {
     // Добавляем настройки в список.
     PMSGDLGBOX DlgList_entry = DlgList[Count];

     memcpy (DlgList_entry, &Applier.RTDlgMemory.Message_data, sizeof (MSGDLGBOX));
     DlgList_entry->Enabled = 1;

     // Записываем настройки.
     Applier_WriteDialogList (DlgList_entry);

     // Все в порядке.
     break;
   }

  // Возврат.
  return;
}
