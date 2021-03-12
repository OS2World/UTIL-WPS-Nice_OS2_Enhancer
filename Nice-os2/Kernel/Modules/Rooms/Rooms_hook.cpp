
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID RoomsInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Если надо добавить комнаты к рабочему столу:
  if (Rooms.Settings.Create_Rooms)
  {
    // Переходим в другую комнату при получении сообщения WM_MARK.
    if (Rooms.Settings.Switch_by_WarpCenter)
     if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_GO_TO_ROOM)
     {
       // Узнаем, в какую комнату надо перейти.
       LONG Scan_code = (LONG) Message->mp2; INT Room = 0;

       if (Scan_code == SC_NUM_5) Room = SHELL_ROOM;
       if (Scan_code == SC_NUM_8) Room = NORTHERN_ROOM;
       if (Scan_code == SC_NUM_4) Room = WESTERN_ROOM;
       if (Scan_code == SC_NUM_6) Room = EASTERN_ROOM;
       if (Scan_code == SC_NUM_2) Room = SOUTHERN_ROOM;

       if (Scan_code == SC_NUM_7 || Scan_code == SC_NUM_9 ||
           Scan_code == SC_NUM_1 || Scan_code == SC_NUM_3) Room = CURRENT_ROOM;

       // Если вызвана заставка - действие выполнять не надо.
       if (Room)
        if (SystemIsLocked ()) { Room = 0; *Discarding = 1; }

       // Если надо переключиться в другую комнату:
       if (Room)
       {
         // Посылаем сообщение в поток.
         if (Room != CURRENT_ROOM) WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_GO_TO_ROOM, (MPARAM) Room, 0);

         // Сообщение должно быть сброшено.
         *Discarding = 1;
       }
     }

    // Закрашиваем окно рабочего стола.
    if (Rooms.Settings.Draw_wallpaper)
    {
      // Если окно должно быть перерисовано и это рабочий стол:
      if (Message->msg == WM_PAINT) if (Message->hwnd == QueryDesktopWindow ())
      {
        // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, окно можно будет закрасить.
        HMQ Message_queue = WinQueryWindowULong (Message->hwnd, QWL_HMQ);
        WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_FILL_DESKTOP, (MPARAM) Message->hwnd);
      }

      // Обрабатываем сообщение WM_MARK.
      if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_FILL_DESKTOP)
      {
        HWND Window = (HWND) Message->mp2;
        if (Window == QueryDesktopWindow ())
        {
          // Посылаем сообщение в поток.
          WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_FILL_DESKTOP, (MPARAM) Window, 0);
        }
      }
    }

    // Вызываем LaunchPad или список окон при нажатии кнопок мыши в окне рабочего стола.
    BYTE Show_LaunchPad = 0; BYTE Show_Window_list = 0; BYTE Hide_Window_list = 0;

    // Если левая кнопка мыши нажата дважды - вызываем LaunchPad.
    if (Message->msg == WM_BUTTON1DBLCLK)
     if (Message->hwnd == QueryDesktopWindow ()) Show_LaunchPad = 1;

    // Если она нажата один раз:
    if (Message->msg == WM_BUTTON1DOWN)
    {
      // Узнаем окно рабочего стола.
      HWND Desktop = QueryDesktopWindow ();

      // Если мышь нажата в окне рабочего стола - проверяем состояние других кнопок мыши.
      if (Message->hwnd == Desktop)
      {
        if (MouseButtonIsPressed (2) || MouseButtonIsPressed (3))
         Show_Window_list = 1;
        else
         Hide_Window_list= 1;
      }
    }

    // Если нажата правая или средняя кнопка:
    if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
    {
      // Узнаем окно рабочего стола.
      HWND Desktop = QueryDesktopWindow ();

      // Если мышь нажата в окне рабочего стола - проверяем состояние левой кнопки мыши.
      if (Message->hwnd == Desktop)
      {
        if (MouseButtonIsPressed (1))
         Show_Window_list = 1;
        else
         Hide_Window_list = 1;
      }
    }

    // Если надо вызвать LaunchPad или список окон - посылаем сообщение в поток.
    if (Show_LaunchPad) WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_SHOW_LAUNCHPAD, 0, 0);
    if (Show_Window_list) WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_SHOW_WINDOW_LIST, (MPARAM) 1, 0);
    if (Hide_Window_list)
    {
      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_HIDE_WINDOW_LIST, 0, 0);
      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_HIDE_WARPCENTER, 0, 0);
    }

    // Если используется оболочка WPS:
    if (ShellIsWPS ())
    {
      // Проверяем окно WPS, которое становится выбранным, чтобы скрыть окно оболочки.
      // Это сообщение посылается в окно в SendMsgHook () при обработке сообщения WM_ACTIVATE.
      if (GetCurrentOrNextRoom () != SHELL_ROOM)
       if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_CHECK_WINDOW)
       {
         // Посылаем сообщение в поток.
         HWND Window = (HWND) Message->mp2;
         WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_CHECK_WINDOW, (MPARAM) Window, 0);
       }
    }

    // Добиваемся правильной работы потоков после перехода между комнатами.
    if (Rooms.Settings.Synchronize_arranger_and_rooms)
    {
      // Если была нажата кнопка мыши - считаем, что смена комнат завершена.
      if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
       if (Message->hwnd != CurtainWindow ())
        if (MouseIsBusy ())
         Rooms.Settings.Synchronize_arranger_and_rooms = 0;
    }
  }

  // Возврат.
  return;
}


// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID RoomsKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Если надо добавить комнаты к рабочему столу:
  if (Rooms.Settings.Create_Rooms)
  {
    // Переходим в другую комнату при нажатии на цифровые клавиши. Посылаем сообщение в поток и сбрасываем пришедшее сообщение.
    if (Rooms.Settings.Switch_by_keyboard)
     if (Message->msg == WM_CHAR)
     {
       // Смотрим, какая клавиша нажата.
       BYTE Scan_code = CHAR4FROMMP (Message->mp1);
       SHORT State = SHORT1FROMMP (Message->mp1);

       // Если идет нажатие клавиши:
       if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
       {
         // Узнаем, в какую комнату надо перейти.
         INT Room = 0;

         // Должна быть нажата клавиша Shift и цифровая клавиша.
         if (State & KC_SHIFT) if (ShiftIsPressed ())
         {
           if (Scan_code == SC_NUM_5) Room = SHELL_ROOM;
           if (Scan_code == SC_NUM_8) Room = NORTHERN_ROOM;
           if (Scan_code == SC_NUM_4) Room = WESTERN_ROOM;
           if (Scan_code == SC_NUM_6) Room = EASTERN_ROOM;
           if (Scan_code == SC_NUM_2) Room = SOUTHERN_ROOM;

           if (Scan_code == SC_NUM_7 || Scan_code == SC_NUM_9 ||
               Scan_code == SC_NUM_1 || Scan_code == SC_NUM_3) Room = CURRENT_ROOM;
         }

         // Если вызвана заставка - действие выполнять не надо.
         if (Room) if (SystemIsLocked ()) { Room = 0; *Discarding = 1; }

         // Если надо переключиться в другую комнату:
         if (Room)
         {
           // Посылаем сообщение в поток.
           if (Room != CURRENT_ROOM) WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_GO_TO_ROOM, (MPARAM) Room, 0);

           // Сообщение должно быть сброшено.
           *Discarding = 1;
         }
       }
     }

    // Добиваемся правильной работы потоков после перехода между комнатами.
    if (Rooms.Settings.Synchronize_arranger_and_rooms)
    {
      // Если была нажата любая клавиша - считаем, что смена комнат завершена.
      if (Message->msg == WM_CHAR)
      {
        // Смотрим, какая клавиша нажата.
        BYTE Scan_code = CHAR4FROMMP (Message->mp1);
        SHORT State = SHORT1FROMMP (Message->mp1);

        // Если идет нажатие клавиши:
        if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
        {
          // Если эта клавиша не используется дл переключения между комнатами - смена комнат завершена.
          if (Scan_code < SC_NUM_FIRST || Scan_code > SC_NUM_LAST)
           Rooms.Settings.Synchronize_arranger_and_rooms = 0;
        }
      }
    }
  }

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID RoomsSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // Если надо добавить комнаты к рабочему столу:
  if (Rooms.Settings.Create_Rooms) if (!RoomsChangeIsInProcess ())
  {
    // Если окно рамки становится выбранным:
    if (TopFrameWindowIsActivating (Message))
    {
      // Узнаем окно рамки.
      HWND Frame_window = QueryFrameWindow (Message->hwnd);

      // Запоминаем комнату, в которой располагается окно.
      Rooms_SetRoomProperty (Frame_window, GetCurrentOrNextRoom ());

      // Делаем окно доступным для переключения.
      WinPostQueueMsg (Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Frame_window, (MPARAM) SWL_JUMPABLE);
    }

    // Если используется оболочка WPS:
    if (ShellIsWPS ())
    {
      // Если окно оболочки скрыто:
      if (GetCurrentOrNextRoom () != SHELL_ROOM)
      {
        // Если оно возвращается в обычное состояние или становится выбранным - надо спрятать его.
        if (TopFrameWindowIsMoving (Message) || TopFrameWindowIsActivating (Message))
        {
          // Узнаем окно рамки.
          HWND Frame_window = QueryFrameWindow (Message->hwnd);

          // Если это окно WPS - посылаем в очередь сообщение WM_MARK. Когда оно будет получено, окно можно будет проверить.
          if (IsFolderWindow (Frame_window))
          {
            HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);
            WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_CHECK_WINDOW, (MPARAM) Frame_window);
          }
        }
      }
    }
  }

  // Возврат.
  return;
}

