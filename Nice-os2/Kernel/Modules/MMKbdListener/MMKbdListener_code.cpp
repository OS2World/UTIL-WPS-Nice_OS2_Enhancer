
// ─── Получает сообщения о нажатии на клавиши ───

VOID MMKbdListener_WaitKeyboardEvents (VOID)
{
  // Проверяем, работает ли "MMKbd.exe"
  CHAR MMKbd_semaphore_name[] = "\\SEM32\\MMKbd"; HMTX MMKbd_semaphore = NULLHANDLE;
  if (DosOpenMutexSem (MMKbd_semaphore_name, &MMKbd_semaphore) != NO_ERROR)
  {
    WinPostQueueMsg (Enhancer.Modules.MMKbdListener->Message_queue, WM_QUIT, 0, 0);
    return;
  }
  DosCloseMutexSem (MMKbd_semaphore);

  // Создаем событийные семафоры.
  // Как только клавиша будет нажата, один из них будет включен.
  #include "Modules\\MMKbdListener\\MMKbdListener_keys.cpp"

  // Создаем общий событийный семафор и добавляем к нему ранее созданные семафоры.
  HMUX MainEventSem = NULLHANDLE;
  if (DosCreateMuxWaitSem (NULL, &MainEventSem, Quantity, Semaphores, DCMW_WAIT_ANY) != NO_ERROR) return;

  // Ждем нажатий и посылаем в окна сообщения "WM_CHAR".
  while (1)
  {
    // Выполняем ожидание.
    ULONG Record_number = 0;
    if (DosWaitMuxWaitSem (MainEventSem, SEM_INDEFINITE_WAIT, &Record_number) == NO_ERROR && Record_number > 0)
    {
      // Узнаем окно, в которое направлен ввод от клавиатуры.
      HWND Input_window = WinQueryFocus (QueryDesktopWindow ());

      // Если такого окна нет - пусть это будет окно рабочего стола.
      if (Input_window == NULLHANDLE) Input_window = QueryDesktopWindow ();

      // Задаем сочетание клавиш.
      CHAR New_character_code = Char_codes[Record_number];
      BYTE New_scan_code = Scan_codes[Record_number];
      LONG New_modifiers = 0;

      // Составляем сообщения о нажатии и отжатии клавиши.
      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers);

      // Посылаем сообщения в окно.
      // Для этих клавиш не будет выполняться проверка, нажаты ли они на самом деле.
      WinPostMsg (Input_window, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Input_window, WM_CHAR, First_parameter_2, Second_parameter_2);

      // Сбрасываем событийные семафоры в начальное состояние.
      for (INT Count = 0; Count < Quantity; Count ++)
      {
        HEV Semaphore = (HEV) Semaphores[Count].hsemCur; ULONG Post_count = 0;
        DosResetEventSem (Semaphore, &Post_count);
      }
    }

    // Выполняем короткую задержку на случай "дрожания" клавиш.
    Retard ();
  }

  // Удаляем семафоры.
  for (INT Count = 0; Count < Quantity; Count ++) DosDeleteMuxWaitSem (MainEventSem, Semaphores[Count].hsemCur);
  DosCloseMuxWaitSem (MainEventSem);

  for (Count = 0; Count < Quantity; Count ++)
  {
    HEV Semaphore = (HEV) Semaphores[Count].hsemCur;
    DosCloseEventSem (Semaphore);
  }

  // Возврат.
  return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID MMKbdListener_MMKbdListenerMessageProcessing (PQMSG Message)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.MMKbdListener->Priority = MAKELONG (Class, Delta);
  }

  // Ждем нажатия на клавишу.
  if (Message->msg == SM_WAIT_MMKBD_EVENTS) MMKbdListener_WaitKeyboardEvents ();

  // Возврат.
  return;
}

// ─── Поток для получения сообщений о нажатии на клавиши ───

VOID MMKbdListener_MMKbdListenerThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.MMKbdListener->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.MMKbdListener->Message_queue == NULLHANDLE)
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
    MMKbdListener_MMKbdListenerMessageProcessing (&Message);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
