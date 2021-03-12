
// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Controller_ControllerMessageProcessing (PQMSG Message)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.Controller->Priority = MAKELONG (Class, Delta);
  }

  // Устанавливаем переключатели на клавиатуре.
  if (Message->msg == SM_SET_NUM_LOCK)
  {
    // Если настройка выключена - возврат.
    if (!Controller.Settings.Turn_Num_Lock) return;

    // Устанавливаем переключатели.
    Controller_SetNumLock ();
  }

  // Сбрасываем состояние клавиш "Shift".
  if (Message->msg == SM_RESET_SHIFT_KEYS)
  {
    // Если настройка выключена - возврат.
    if (!Controller.Settings.Reset_Shift_keys) return;

    // Сбрасываем состояние клавиш.
    Controller_ResetShiftKeys ();
  }

  // Выполняем "разгон" клавиатуры.
  if (Message->msg == SM_SPEEDUP_KEYBOARD)
  {
    // Если настройка выключена - возврат.
    if (!Controller.Settings.SpeedUp_keyboard) return;

    // Настраиваем клавиатуру.
    Controller_SpeedUpKeyboard ();
  }

  // Переключаем состояние клавиш перезагрузки.
  if (Message->msg == SM_SET_CTRL_ALT_DEL)
  {
    // Узнаем, что надо сделать.
    LONG State = (LONG) Message->mp1;

    // Переключаем состояние Ctrl + Alt + Del.
    if (State) SetCtrlAltDel (1); else SetCtrlAltDel (0);
  }

  // Возврат.
  return;
}

// ─── Поток для управления клавиатурой ───

VOID Controller_ControllerThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Controller->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.Controller->Message_queue == NULLHANDLE)
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
    Controller_ControllerMessageProcessing (&Message);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
