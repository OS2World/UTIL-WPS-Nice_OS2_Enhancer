// ─── Находит диалоговые окна, известные расширителю ───

VOID Applier_FindDialogWindows (VOID)
{
  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // Если это не окно рамки - продолжаем перебор окон.
    if (!IsFrameWindow (Window)) continue;

    // Если окно доступно:
    if (FrameWindowIsAccessible (Window))
    {
      // Если для этого окна задано действие - выполняем его.
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

  // Возврат.
  return;
}

// ─── Закрывает окно сообщения ───

// Frame_window - окно сообщения.
VOID Applier_SendYes (HWND Frame_window)
{
  // Узнаем, задано ли действие для этого окна.
  PMSGDLGBOX Dialog = NULL; Applier_FindWindowInMessageDialogList (Frame_window, 1, &Dialog);

  // Если действие задано:
  if (Dialog != NULL)
  {
    // Если действие выключено - возврат.
    if (!Dialog->Enabled) return;

    // Получаем сведения об окне.
    ScanDialogWindow (Frame_window, &Applier.RTDlgMemory.Dialog_data);

    // Узнаем кнопку, которая должна быть нажата.
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

    // Если кнопка существует - посылаем ей сообщение о нажати клавиши ввода.
    if (Button != NULLHANDLE)
    {
      // Делаем кнопку выбранной и доступной.
      WinEnableWindow (Button, 1); WinSetFocus (QueryDesktopWindow (), Button);

      // Составляем сообщение о нажатии клавиши Enter.
      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0);

      // Посылаем его.
      WinPostMsg (Button, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Button, WM_CHAR, First_parameter_2, Second_parameter_2);
    }
  }

  // Возврат.
  return;
}

// ─── Восстанавливает значения в окне диалога ───

// Frame_window - окно диалога.
VOID Applier_CompleteDialog (HWND Frame_window)
{
  // Узнаем, задано ли действие для этого окна.
  PDLGBOX Dialog = NULL; Applier_FindWindowInIncompleteDialogList (Frame_window, 1, &Dialog);

  // Если действие задано:
  if (Dialog != NULL)
  {
    // Если действие выключено - возврат.
    if (!Dialog->Enabled) return;

    // Если действие для этого окна уже выполнялось - возврат.
    for (INT Count = 0; Count < APPLIER_MONITORING_DIALOG_WINDOWS; Count ++)
     if (Applier.RTSettings.Last_dialog_windows[Count] == Frame_window)
      return;

    // Восстанавливаем содержимое полей ввода.
    RestoreDialogFields (Frame_window, Dialog);

    // Сдвигаем список окон, для которых восстанавливались поля ввода.
    for (Count = 0; Count < APPLIER_MONITORING_DIALOG_WINDOWS - 1; Count ++)
     Applier.RTSettings.Last_dialog_windows[Count] = Applier.RTSettings.Last_dialog_windows[Count + 1];

    // Запоминаем окно.
    Applier.RTSettings.Last_dialog_windows[APPLIER_MONITORING_DIALOG_WINDOWS - 1] = Frame_window;
  }

  // Возврат.
  return;
}

// ─── Создает заголовок окна приложения, вызываемого после ввода пароля ───

// Title - переменная для заголовка, Time - время запуска приложения.
VOID Applier_MakeLogonWindowTitle (PCHAR Title, LONG Time)
{
  // Составляем заголовок.
  strcpy (Title, "Logon - ");
  CHAR Number[25] = ""; itoa (Time, Number, 16); UpperCase (Number);
  strcat (Title, Number);

  // Возврат.
  return;
}

// ─── Подготавливает команду для исполнения ───

// Command - строка вида "Script.cmd %1 %2", Values и Quantity - значения.
VOID Applier_PrepareLogonCommand (PCHAR Command, PDLGFIELD Values, INT Quantity)
{
  // Находим в строке места для подстановки значений.
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

  // Если значения должны быть переданы:
  if (Pointers > 0)
  {
    // Проверяем, все ли текстовые значения на местах.
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

    // Если нет первого значения или их должно быть несколько, но задано только первое - возврат.
    BYTE Cancel = 0;

    if ((!First_text_value_is_present) ||
        (Another_text_value_is_found && !Another_text_value_is_present)) Cancel = 1;

    if (Cancel) { Command[0] = 0; return; }
  }

  // Составляем новую строку.
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

  // Записываем ее вместо старой.
  strcpy (Command, New_command);

  // Возврат.
  return;
}

// ─── Выполняет команду после завершения приложения, вызвавшего окно ввода пароля ───

// Process_ID - приложение, завершения которого дождался поток Waiter.
VOID Applier_ExecuteLogonScript (PID Process_ID)
{
  // Составляем список известных расширителю диалоговых окон.
  PLOGONDLGBOX DlgList[8] = {
                              &Applier.Settings.Dialogs.Logon_dialog_1, &Applier.Settings.Dialogs.Logon_dialog_2,
                              &Applier.Settings.Dialogs.Logon_dialog_3, &Applier.Settings.Dialogs.Logon_dialog_4,
                              &Applier.Settings.Dialogs.Logon_dialog_5, &Applier.Settings.Dialogs.Logon_dialog_6,
                              &Applier.Settings.Dialogs.Logon_dialog_7, &Applier.Settings.Dialogs.Logon_dialog_8
                            };

  // Находим приложение в списке.
  for (INT Count = 0; Count < 8; Count ++)
  {
    PLOGONSCRIPTDATA Parameters = &DlgList[Count]->Parameters;

    if (Parameters->Process_ID == Process_ID)
    {
      // Выполняем заданную пользователем команду.
      CHAR Command[SIZE_OF_PATH] = ""; strcpy (Command, DlgList[Count]->Logon_command);
      Applier_PrepareLogonCommand (Command, Parameters->Values, Parameters->Quantity);

      if (Command[0] != 0)
      {
        // Узнаем текущее время.
        LONG Current_time = WinGetCurrentTime (Enhancer.Application);

        // Подготавливаем заголовок для окна.
        CHAR Title[SIZE_OF_TITLE] = ""; Applier_MakeLogonWindowTitle (Title, Current_time);

        // Выполняем команду.
        CHAR Parameters[SIZE_OF_PATH] = "";
        PCHAR Space = strstr (" ", Command);
        if (Space) { strcpy (Parameters, Space + 1); *Space = 0; }

        HAPP PM_Handle = Execute (Command, Parameters, Title, SWP_MINIMIZE);

        // Если приложение было вызвано - сопровождаем его.
        if (PM_Handle != NULLHANDLE)
        {
          // Сбрасываем переменную для ответа от потока.
          Thread_responds.Thread_is_created = 0;

          // Создаем поток.
          TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread (&Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE);
          // Если он создан - ждем, пока в нем будет создана очередь сообщений.
          if (Thread_is_created == NO_ERROR) while (Thread_responds.Thread_is_created == 0) { Retard (); }

          // Если поток удалось создать:
          if (Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1)
          {
            // Посылаем сообщение в поток.
            WinPostQueueMsg (Enhancer.Modules.Waiter->Message_queue, SM_ESCORT_LOGON, (MPARAM) Current_time, 0);

            // Забываем про него.
            Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
          }
        }
      }

      // Сбрасываем настройки.
      bzero (Parameters, sizeof (LOGONSCRIPTDATA));

      // Запоминаем, что действие выполнено.
      DlgList[Count]->Action_performed = 1;
    }
  }

  // Возврат.
  return;
}

// ─── Проверяет, остались ли еще окна ввода пароля ───

VOID Applier_CheckLogonWindows (VOID)
{
  // Смотрим, есть ли еще окна ввода пароля.
  BYTE Logon_in_process = 0;

  for (INT Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS; Count ++)
  {
    HWND Logon_window = Applier.RTDlgMemory.Logon_windows[Count].Window;
    if (!WinIsWindow (WinQueryAnchorBlock (Logon_window), Logon_window))
     Applier.RTDlgMemory.Logon_windows[Count].Window = NULLHANDLE;

    if (Applier.RTDlgMemory.Logon_windows[Count].Window != NULLHANDLE) Logon_in_process = 1;
  }

  Applier.RTSettings.Logon_in_process = Logon_in_process;

  // Возврат.
  return;
}

// ─── Проверяет состояние окон и начинает выполнение действий ───

// Dismissed_frame - окно рамки, получавшее сообщение о закрытии.
VOID Applier_CheckLogonWindowsAndStartWaiting (HWND Dismissed_frame)
{
  // Смотрим, какие окна для ввода пароля были закрыты.
  PLOGONDLGBOX Task_list[8] = {0}; INT Tasks = 0;

  for (INT Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS; Count ++)
   if (Applier.RTDlgMemory.Logon_windows[Count].Window == Dismissed_frame )
   {
     // Проверяем, могла ли быть нажата кнопка "Отмена". Пробуем получить команду для исполнения.
     PLOGONDLGBOX Related_dialog = Applier.RTDlgMemory.Logon_windows[Count].Related_dialog;
     CHAR Command[SIZE_OF_PATH] = ""; strcpy (Command, Related_dialog->Logon_command);

     PDLGBOX Dialog = &Applier.RTDlgMemory.Logon_windows[Count].Dialog;
     Applier_PrepareLogonCommand (Command, Dialog->Fields, Dialog->Quantity);

     BYTE Cancel = 0; if (Command[0] == 0) Cancel = 1;

     if (!Cancel)
     {
       // Смотрим, есть ли уже в списке заданий действие для этого окна.
       BYTE Task_is_exists = 0;

       for (INT Pointer = 0; Pointer < 8; Pointer ++)
       {
         if (Task_list[Pointer] == NULL) break;
         if (Task_list[Pointer] == Related_dialog) { Task_is_exists = 1; break; }
       }

       // Добавляем задание, если оно еще не было добавлено:
       if (!Task_is_exists)
       {
         // Запоминаем значения.
         for (INT Number = 0; Number < Dialog->Quantity; Number ++)
          memcpy (&Related_dialog->Parameters.Values[Number], &Dialog->Fields[Number], sizeof (DLGFIELD));

         Related_dialog->Parameters.Quantity = Dialog->Quantity;

         // Запоминаем приложение.
         Related_dialog->Parameters.Process_ID = Applier.RTDlgMemory.Logon_windows[Count].Process_ID;

         // Запоминаем задание.
         Task_list[Tasks] = Related_dialog;
         Tasks ++;
       }
     }

     // Сбрасываем значения для окна.
     bzero (&Applier.RTDlgMemory.Logon_windows[Count], sizeof (LOGONWNDINFO));
   }

  // Выполняем задания, создавая потоки для ожидания завершения приложений.
  for (Count = 0; Count < Tasks; Count ++)
  {
    // Если есть задание:
    PLOGONDLGBOX Task = Task_list[Count];
    PID Process_ID = Task->Parameters.Process_ID;

    if (Process_ID != NULLHANDLE)
    {
      // Сбрасываем переменную для ответа от потока.
      Thread_responds.Thread_is_created = 0;

      // Создаем поток.
      TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread (&Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE);
      // Если он создан - ждем, пока в нем будет создана очередь сообщений.
      if (Thread_is_created == NO_ERROR) while (Thread_responds.Thread_is_created == 0) { Retard (); }

      // Если поток удалось создать:
      if (Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1)
      {
        // Посылаем сообщение в поток.
        HMQ Owner_queue = Enhancer.Modules.Applier->Message_queue;
        WinPostQueueMsg (Enhancer.Modules.Waiter->Message_queue, SM_WAIT_EXISTING_PROCESS, (MPARAM) Process_ID, (MPARAM) Owner_queue);

        // Забываем про него.
        Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
      }
    }
  }

  // Проверяем, есть ли еще окна ввода пароля.
  Applier_CheckLogonWindows ();

  // Возврат.
  return;
}

// ─── Выбирает значения из окна ввода пароля ───

// Frame_window - окно диалога.
VOID Applier_WatchLogonValues (HWND Frame_window)
{
  // Находим окно в списке отслеживаемых окон и запоминаем значения.
  PLOGONWNDINFO Target = NULL;

  for (INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count --)
   if (Applier.RTDlgMemory.Logon_windows[Count].Window == Frame_window)
   {
     Target = &Applier.RTDlgMemory.Logon_windows[Count];
     break;
   }

  // Если оно найдено:
  if (Target != NULL)
  {
    // Получаем сведения об окне. Для увеличения скорости выбираются только поля, полезные при наборе пароля.
    ScanDialogWindow (Frame_window, &Applier.RTDlgMemory.Dialog_data, SCAN_INPUT_FIELDS);

    // Если значения еще не были перенесены:
    if (Target->Dialog.Quantity == 0)
    {
      // Переносим данные как есть.
      memcpy (&Target->Dialog, &Applier.RTDlgMemory.Dialog_data, sizeof (DLGBOX));
    }
    // А если они уже были получены раньше:
    else
    {
      // Запоминаем значения.
      INT Fields = 0;

      for (Count = 0; Count < Applier.RTDlgMemory.Dialog_data.Quantity; Count ++)
      {
        // Число полей в окне может меняться, если оно включает их во время набора. Обходим это.
        LONG Source_type = Applier.RTDlgMemory.Dialog_data.Fields[Count].Type;
        LONG Target_type = Target->Dialog.Fields[Count].Type;

        if (Source_type == Target_type)
        {
          // Окно может стереть пароль. Проверяем, так ли это.
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

  // Возврат.
  return;
}

// ─── Распознает и запоминает окно ввода пароля ───

// Frame_window - окно диалога.
VOID Applier_CheckLogonWindow (HWND Frame_window)
{
  // Узнаем, задано ли действие для этого окна.
  PLOGONDLGBOX Dialog = NULL; Applier_FindWindowInLogonDialogList (Frame_window, 1, &Dialog);

  // Если действие задано:
  if (Dialog != NULL)
  {
    // Если действие выключено - возврат.
    if (!Dialog->Enabled) return;

    // Если действие уже выполнялось и второй раз выполнять его не надо - возврат.
    if (Dialog->Only_once) if (Dialog->Action_performed) return;

    // Запоминаем, что такое окно есть.
    Applier.RTSettings.Logon_in_process = 1;

    // Если оно есть в списке отслеживаемых окон - возврат.
    for (INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count --)
     if (Applier.RTDlgMemory.Logon_windows[Count].Window == Frame_window)
      return;

    // Сдвигаем список.
    for (Count = 0; Count < APPLIER_MONITORING_LOGON_WINDOWS - 1; Count ++)
     memcpy (&Applier.RTDlgMemory.Logon_windows[Count], &Applier.RTDlgMemory.Logon_windows[Count + 1], sizeof (LOGONWNDINFO));

    // Запоминаем окно, создавшее его приложение и настройки, связанные с окном. Значения полей в нем самом пока неизвестны.
    bzero (&Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1], sizeof (LOGONWNDINFO));

    PID Process_ID = QueryWindowRealProcessID (Frame_window);

    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Window = Frame_window;
    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Process_ID = Process_ID;
    Applier.RTDlgMemory.Logon_windows[APPLIER_MONITORING_LOGON_WINDOWS - 1].Related_dialog = Dialog;


    // Чтобы значения полей стали известны - посылаем сообщение в поток.
    WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_LOGON_VALUES, (MPARAM) Frame_window, 0);
  }

  // Возврат.
  return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Applier_ApplierMessageProcessing (PQMSG Message)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.Applier->Priority = MAKELONG (Class, Delta);
  }

  // Распознаем и запоминаем окна ввода пароля.
  if (Message->msg == SM_LOGON_WINDOW)
  {
    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Распознаем и запоминаем его.
    Applier_CheckLogonWindow (Frame_window);
  }

  // Запоминаем значения в окнах ввода пароля.
  if (Message->msg == SM_LOGON_VALUES)
  {
    // Если ни одного окна для ввода пароля нет - возврат.
    if (!Applier.RTSettings.Logon_in_process) return;

    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Выбираем значения, набранные в окне.
    Applier_WatchLogonValues (Frame_window);
  }

  // Проверяем состояние окон для ввода пароля.
  if (Message->msg == SM_LOGON_ACTION)
  {
    // Если ни одного окна для ввода пароля нет - возврат.
    if (!Applier.RTSettings.Logon_in_process) return;

    // Узнаем закрывшееся окно.
    HWND Dismissed_frame = (HWND) Message->mp1;

    // Если оно не задано - возврат.
    if (Dismissed_frame == NULLHANDLE) return;

    // Проверяем состояние окон и начинаем выполнение действий, если это требуется.
    Applier_CheckLogonWindowsAndStartWaiting (Dismissed_frame);
  }

  // Проверяем существование окон ввода пароля.
  if (Message->msg == SM_LOGON_CHECK) Applier_CheckLogonWindows ();

  // Выполняем команду пользователя после завершения приложения, вызвавшего окно ввода пароля.
  if (Message->msg == SM_LOGON_PROCESS_STOPPED)
  {
    // Узнаем приложение.
    PID Process_ID = (PID) Message->mp1;

    // Если оно неизвестно - возврат.
    if (Process_ID == NULLHANDLE) return;

    // Уменьшаем приоритет.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // Выполняем команду.
    Applier_ExecuteLogonScript (Process_ID);

    // Восстанавливаем приоритет.
    LONG Class = SHORT1FROMLONG (Enhancer.Modules.Applier->Priority);
    LONG Delta = SHORT2FROMLONG (Enhancer.Modules.Applier->Priority);
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);
  }

  // Восстанавливаем поля ввода в окнах диалогов.
  if (Message->msg == SM_COMPLETE_DIALOG)
  {
    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Закрываем его.
    Applier_CompleteDialog (Frame_window);
  }

  // Закрываем окна сообщений.
  if (Message->msg == SM_SEND_YES)
  {
    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Закрываем его.
    Applier_SendYes (Frame_window);
  }

  // Находим диалоговые окна, известные расширителю.
  if (Message->msg == SM_FIND_DIALOG_WINDOWS)
  {
    // Проверяем существующие окна ввода пароля.
    if (Applier.Settings.Script_after_Logon) Applier_CheckLogonWindows ();

    // Выполняем поиск новых окон.
    Applier_FindDialogWindows ();
  }

  // Возврат.
  return;
}

// ─── Поток для выполнения действия с окнами диалога ───

VOID Applier_ApplierThread (VOID)
{
  // Определяем поток в системе.
  HAB Thread = WinInitialize (0);

  // Если это сделать не удалось - выход.
  if (Thread == NULLHANDLE)
  {
    // При создании потока произошла ошибка.
    Thread_responds.Thread_is_created = -1;

    // Выход.
    return;
  }

  // Создаем очередь сообщений - она должна быть в каждом потоке.
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Applier->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.Applier->Message_queue == NULLHANDLE)
  {
    // Завершаем работу потока.
    WinTerminate (Thread);

    // При создании потока произошла ошибка.
    Thread_responds.Thread_is_created = -1;

    // Выход.
    return;
  }

  // Поток создан успешно.
  Thread_responds.Thread_is_created = 1;

  // Получение и обработка сообщений, приходящих в поток.
  QMSG Message = {0};
  while (WinGetMsg (Thread, &Message, 0, 0, 0))
  {
    // Проверяем, не идет ли следом такое же сообщение.
    QMSG Next_message = {0};
    WinPeekMsg (Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE);
    if (Next_message.msg == Message.msg)
     if (Next_message.mp1 == Message.mp1)
      if (Next_message.mp2 == Message.mp2)
       if (Next_message.hwnd == Message.hwnd) continue;

    // Обрабатываем сообщение.
    Applier_ApplierMessageProcessing (&Message);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
