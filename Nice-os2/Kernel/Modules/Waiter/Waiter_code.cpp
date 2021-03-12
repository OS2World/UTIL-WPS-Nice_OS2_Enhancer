// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение, Thread_queue - очередь сообщений потока.
VOID Waiter_WaiterMessageProcessing (PQMSG Message, HMQ Thread_queue)
{
  // Ждем некоторое время и отправляем сообщение в другой поток.
  // Обычно это требуется для того, чтобы сбросить настройки в INI-файл, но может быть и любое другое действие.
  if (Message->msg == SM_WAIT_SOME_TIME)
  {
    // Снижаем приоритет потока.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // Узнаем очередь сообщений владельца потока.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // Засыпаем на некоторое время.
    DosSleep (Waiter.Constants.Sleep_to_wait_some_time);

    // Сообщаем владельцу о том, что ожидание завершено.
    // Параметры сообщения должны быть равны нулю, тогда несколько сообщений будут обработаны как одно.
    WinPostQueueMsg (Owner_queue, SM_WAITING_COMPLETE, 0, 0);

    // Посылаем своему потоку сообщение о том, что его работа закончена.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // Ждем появления приложения и оповещаем об этом другой поток.
  if (Message->msg == SM_WAIT_STARTING_PROCESS)
  {
    // Снижаем приоритет потока.
    DosSetPriority (PRTYS_THREAD, PRTYC_REGULAR, 0, 0);

    // Узнаем приложение, появления которого надо ждать.
    INT App_code = (INT) Message->mp1;
    // Узнаем очередь сообщений владельца потока.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // Ждем некоторое время.
    INT Point_to_reduce_priority_1 = (INT) (Waiter.Constants.Retards_to_wait_process / 3);
    INT Point_to_reduce_priority_2 = (INT) (Point_to_reduce_priority_1 * 2);

    for (INT Count = 0; Count < Waiter.Constants.Retards_to_wait_process; Count ++)
    {
      // Выполняем ожидание. Лучше с этого начать, так как на первом шаге вряд ли что-то будет найдено.
      Retard ();

      // Проверяем, есть ли приложение.
      HWND App_window = FindAppWindow (App_code, FIND_VISIBLE_WINDOW);

      // Если оно есть:
      if (App_window != NULLHANDLE)
      {
        // Сообщаем об этом владельцу.
        WinPostQueueMsg (Owner_queue, SM_STARTING_PROCESS_APPEARED, (MPARAM) App_code, (MPARAM) App_window);

        // Прекращаем ожидание.
        break;
      }

      // Если ожидание затягивается - снижаем приоритет еще и еще.
      if (Count == Point_to_reduce_priority_1) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_QUICK, 0);
      if (Count == Point_to_reduce_priority_2) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_NORMAL, 0);
    }

    // Посылаем своему потоку сообщение о том, что его работа закончена.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // Ждем завершения приложения и оповещаем об этом другой поток.
  if (Message->msg == SM_WAIT_EXISTING_PROCESS)
  {
    // Снижаем приоритет потока.
    DosSetPriority (PRTYS_THREAD, PRTYC_REGULAR, 0, 0);

    // Узнаем приложение, за которым надо следить.
    PID Process_ID = (PID) Message->mp1;
    // Узнаем очередь сообщений владельца потока.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // Ждем некоторое время.
    INT Point_to_reduce_priority_1 = (INT) (Waiter.Constants.Retards_to_wait_process / 3);
    INT Point_to_reduce_priority_2 = (INT) (Point_to_reduce_priority_1 * 2);

    for (INT Count = 0; Count < Waiter.Constants.Retards_to_wait_process; Count ++)
    {
      // Проверяем, есть ли приложение.
      BYTE Process_is_exists = 1; if (DosVerifyPidTid (Process_ID, 1) != NO_ERROR) Process_is_exists = 0;

      // Если оно есть:
      if (Process_is_exists)
      {
        // Ждем некоторое время.
        Retard ();
      }
      // А если его нет:
      else
      {
        // Сообщаем об этом владельцу.
        WinPostQueueMsg (Owner_queue, SM_LOGON_PROCESS_STOPPED, (MPARAM) Process_ID, 0);

        // Прекращаем ожидание.
        break;
      }

      // Если ожидание затягивается - снижаем приоритет еще и еще.
      if (Count == Point_to_reduce_priority_1) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_QUICK, 0);
      if (Count == Point_to_reduce_priority_2) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_NORMAL, 0);
    }

    // Посылаем своему потоку сообщение о том, что его работа закончена.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // Ждем завершения приложения или прибиваем его через некоторое время.
  if (Message->msg == SM_ESCORT_LOGON)
  {
    // Снижаем приоритет потока.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // Узнаем время запуска приложения и составляем заголовок окна.
    LONG Time = (LONG) Message->mp1;
    CHAR Title[SIZE_OF_TITLE] = ""; MakeLogonWindowTitle (Title, Time);

    // Делаем окна приложения недоступными для переключения.
    HWND Frame_window = NULLHANDLE;

    for (INT Count = 0; Count < Waiter.Constants.Retards_at_escorting_process; Count ++)
    {
      // Ждем некоторое время.
      Retard ();

      // Узнаем, есть ли еще приложение, создавшее окно с таким заголовком.
      Frame_window = FindFrameWindowInWindowList (Title);

      // Если его нет - прекращаем ожидание:
      if (Frame_window == NULLHANDLE) break;

      // Прячем окна.
      SetProcessJumpableFlag (Title, SWL_NOTJUMPABLE);
    }

    // Если приложение все еще есть:
    if (Frame_window != NULLHANDLE)
    {
      // Засыпаем на время, достаточное для того, чтобы приложение завершилось.
      DosSleep (Waiter.Constants.Sleep_when_escorting_process);

      // Узнаем, есть ли еще приложение, создавшее окно с таким заголовком.
      HWND Frame_window = FindFrameWindowInWindowList (Title);

      // Закрываем окна приложения.
      while (Frame_window != NULLHANDLE)
      {
        PerformAction (Frame_window, CLOSE_ACTION);
        Retard ();
        Frame_window = FindFrameWindowInWindowList (Title);
      }
    }

    // Посылаем своему потоку сообщение о том, что его работа закончена.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // Возврат.
  return;
}

// ─── Поток для ожидания появления или завершения приложения ───

VOID WaiterThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Waiter->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Message_queue == NULLHANDLE)
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
    Waiter_WaiterMessageProcessing (&Message, Message_queue);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}

