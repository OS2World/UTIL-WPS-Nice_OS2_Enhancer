
// ─── Рисует рамки для окон ───

// Frame_window - окно рамки, Target - какое из окон надо перерисовать.
VOID Painter_DrawWindowFrame (HWND Frame_window, ULONG Target)
{
  // Узнаем размер и расположение окна.
  RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
  Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

  // Если окно не показано - возврат.
  if (Frame_rectangle.yTop <= 1 || Frame_rectangle.xRight <= 1) return;

  // Узнаем, как выглядит рамка окна.
  LONG Frame_type = FrameType (Frame_window);

  // Узнаем, выбрано ли окно.
  BYTE Window_is_active = WindowIsActive (Frame_window);

  // Устанавливаем свойство.
  SetProperty (Frame_window, PRP_ACTIVATED, &Window_is_active);

  // Узнаем окно заголовка.
  HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

  // Для некоторых окон можно рисовать только заголовок.
  BYTE Draw_TitleBar_only = 0;

  if (!Painter_PermissionForCompleteDrawing (Frame_window))
  {
    Draw_TitleBar_only = 1; Target = WT_TITLEBAR;
  }

  // Рисуем рамку для окна.
  if (!Draw_TitleBar_only)
  {
    for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
    {
      if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
      Painter_DrawFrameRectangle (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, Window_is_active);
      if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
    }
  }

  // Подчеркиваем объем меню окна.
  if (Painter.Settings.Draw_menus) if (Frame_type != FT_FLAT)
   if (Target & WT_UNKNOWN || Target & WT_MENU)
   {
     HWND Menu_window = WinWindowFromID (Frame_window, FID_MENU);

     if (Menu_window != NULLHANDLE)
     {
       for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
       {
         if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
         Painter_DrawWindowMenu (Menu_window, Frame_window, &Frame_rectangle, &Frame_placement);
         if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
       }
     }
   }

  // Узнаем окно обычных кнопок.
  HWND MinMax_window = WinWindowFromID (Frame_window, FID_MINMAX);

  // Если окно плоское:
  if (Frame_type == FT_FLAT)
  {
    // Если в нем есть окно обычных кнопок - скрываем его.
    if (Painter.Settings.Draw_buttons) if (MinMax_window != NULLHANDLE) WinShowWindow (MinMax_window, 0);

    // Возврат.
    return;
  }
  // А если это не плоское окно:
  else
  {
    // Если свойства окна неизвестны и могут быть определены в будущем - возврат.
    if (!PropertiesForDrawingAreDetected (Frame_window))
     if (WinWindowFromID (Frame_window, FID_SYSMENU) != NULLHANDLE) return;
  }

  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Узнаем высоту заголовка и картинки.
  INT TitleBar_height = 0;

  if (TitleBar_window != NULLHANDLE)
  {
    RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle); TitleBar_height = Rectangle.yTop - 1;
  }
  else
  {
    TitleBar_height = WinQuerySysValue (QueryDesktopWindow (), SV_CYMINMAXBUTTON) - 1;
  }

  // Окна заголовка и картинки должны быть расположены на одной линии.
  // Если это не так - окно надо обновить и ничего не рисовать в нем.
  if (SysMenu_window != NULLHANDLE) if (TitleBar_window != NULLHANDLE)
   if (WinIsWindowVisible (SysMenu_window))
   {
     // Узнаем ширину рамки окна.
     INT Frame_width = 0; FindProperty (Frame_window, PRP_BORDER, &Frame_width);
     if (!Frame_width) Frame_width = FrameWidth (Frame_window);

     // Узнаем расположение окна картинки.
     SWP SysMenu_placement = {0}; WinQueryWindowPos (SysMenu_window, &SysMenu_placement);

     // Если оно расположено на своем месте:
     INT Y_middle_line = Frame_rectangle.yTop - Frame_width - TitleBar_height / 2;

     if (SysMenu_placement.y < Y_middle_line) if (SysMenu_placement.y + SysMenu_placement.cy > Y_middle_line)
     {
       // Узнаем расположение окна заголовка.
       SWP TitleBar_placement = {0}; WinQueryWindowPos (TitleBar_window, &TitleBar_placement);

       // Если заголовок расположен не на своем месте:
       if (TitleBar_placement.y > Y_middle_line || TitleBar_placement.y + TitleBar_placement.cy < Y_middle_line)
       {
         // Обновляем окно.
         UpdateWindow (Frame_window);

         // Возврат.
         return;
       }
     }
   }

  // Узнаем, можно ли рисовать для окна новые кнопки.
  BYTE Draw_new_buttons = 0;

  if (Painter.Settings.Draw_buttons)
  {
    // Узнаем, было ли определено состояние кнопок.
    BYTE Actions_are_detected = 0; FindProperty (Frame_window, PRP_ACTIONS, &Actions_are_detected);

    // Если оно известно - кнопки можно рисовать.
    if (Actions_are_detected) Draw_new_buttons = Painter_PermissionForButtonsDrawing (Frame_window);
  }

  // Кнопки уменьшения и увеличения окна надо скрыть и сжать в "|". Кроме того, рамка
  // может содержать несколько кнопок слева и справа от заголовка, их надо передвинуть.
  BYTE Advanced_controls = 0;

  // Если надо рисовать рамку или заголовок:
  if (Target & WT_UNKNOWN || Target & WT_BORDER || Target & WT_TITLEBAR)
  {
    // Передвигаем окна в заголовке и задаем подходящие цвета.
    if (TitleBar_window != NULLHANDLE || MinMax_window != NULLHANDLE)
     if (Painter_PermissionForCompleteDrawing (Frame_window))
      Advanced_controls = Painter_PrepareWindowControls (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, TitleBar_window, SysMenu_window, MinMax_window);

    // Если справа от заголовка были найдены дополнительные окна - запоминаем это.
    if (Advanced_controls) SetProperty (Frame_window, PRP_CONTROLS, &Advanced_controls);
  }

  // Рисуем новые кнопки в правом верхнем углу окна.
  if (Draw_new_buttons)
   if (Target & WT_UNKNOWN || Target & WT_BORDER)
    if (TitleBar_window != NULLHANDLE)
    {
      for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
      {
        if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
        Painter_DrawButtons (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, TitleBar_window);
        if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
      }
    }

  // Рисуем картинку в левом верхнем углу окна.
  if (Painter.Settings.Draw_system_menus)
   if (Target & WT_UNKNOWN || Target & WT_SYSMENU)
    if (SysMenu_window != NULLHANDLE)
    {
      // Рисуем картинку.
      HPOINTER Icon = NULLHANDLE; FindProperty (Frame_window, PRP_ICON, &Icon);

      for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
      {
        if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
        Painter_DrawSystemMenu (SysMenu_window, Frame_window, &Frame_rectangle, &Frame_placement, Icon, Frame_type, 0);
        if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
      }

      // Если окно картинки закрывает рамку - перерисовываем ее.
      if (Frame_rectangle.xRight + 1 < TitleBar_height * 2)
      {
        for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
        {
          if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
          Painter_DrawFrameRectangle (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, Window_is_active);
          if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
        }
      }
    }

  // Рисуем заголовок окна.
  if (Painter.Settings.Draw_titles)
   if (Target & WT_UNKNOWN || Target & WT_TITLEBAR)
    if (TitleBar_window != NULLHANDLE)
    {
      // Рисуем заголовок. Только подчеркивать его объем нельзя - может получиться окно с незакрашенным заголовком и линиями по краям.
      CHAR Title[SIZE_OF_TITLE] = ""; FindProperty (Frame_window, PRP_TITLE, Title);

      for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
      {
        if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
        Painter_DrawTitleBar (TitleBar_window, Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, Title, Window_is_active, Advanced_controls);
        if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
      }
    }

  // Возврат.
  return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение. Thread - поток.
VOID Painter_PainterMessageProcessing (PQMSG Message, HAB Thread)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.Painter->Priority = MAKELONG (Class, Delta);
  }

  // Перерисовываем рамки окон.
  if (Message->msg == SM_DRAW_FRAME)
  {
    // Если рисование отключено - возврат.
    if (!Painter.Settings.Draw_frames) return;

    // Кеш второго уровня: объединяем несколько заданий в одно.
   {
     // Ставим задание в список.
     Painter.RTSettings.Demand[0].Frame_window = (HWND) Message->mp1;
     Painter.RTSettings.Demand[0].Target = (ULONG) Message->mp2;

     // Забираем следующие задания из очереди и ставим их в список.
     INT Demand_total = 1;

     for (INT Count = 1; Count < PAINTER_DEMAND_TABLE; Count ++)
     {
       QMSG Next_message = {0};
       WinPeekMsg (Thread, &Next_message, NULLHANDLE, SM_DRAW_FRAME, SM_DRAW_FRAME, PM_REMOVE);

       if (Next_message.msg)
       {
         Painter.RTSettings.Demand[Count].Frame_window = (HWND) Next_message.mp1;
         Painter.RTSettings.Demand[Count].Target = (ULONG) Next_message.mp2;

         Demand_total ++;
       }
       else
       {
         break;
       }
     }

     // Просматриваем составленный список и выполняем рисование.
     for (Count = 0; Count < Demand_total; Count ++)
     {
       // Узнаем окно рамки.
       HWND Frame_window = Painter.RTSettings.Demand[Count].Frame_window;
       // Если в списке нет значения - продолжаем перебор.
       if (Frame_window == NULLHANDLE) continue;

       // Узнаем, какое окно надо перерисовать.
       ULONG Target = Painter.RTSettings.Demand[Count].Target;

       // Пробегаем список до конца и забираем задания для того же окна.
       if (Demand_total > 1)
        if (Count != Demand_total - 1)
        {
          for (INT Position = Count + 1; Position < Demand_total; Position ++)
           if (Painter.RTSettings.Demand[Position].Frame_window == Frame_window)
           {
             Target = Target | Painter.RTSettings.Demand[Position].Target;
             Painter.RTSettings.Demand[Position].Frame_window = NULLHANDLE;
           }
        }

       // Если окна нет - продолжаем перебор.
       if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) continue;

       // Перерисовываем рамку, применяя "общее задание".
       Painter_DrawWindowFrame (Frame_window, Target);
     }
   }
  }

  // Перерисовываем картинку в левом верхнем углу окна.
  if (Message->msg == SM_DRAW_SYSMENU)
  {
    // Если рисование отключено - возврат.
    if (!Painter.Settings.Draw_frames) return;

    // Узнаем окно картинки.
    HWND SysMenu_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

    // Узнаем, нажата ли картинка.
    LONG SysMenu_is_pressed = (LONG) Message->mp2;

    // Находим в списке значок окна.
    HPOINTER Icon = NULLHANDLE;
    HWND Frame_window = WinQueryWindow (SysMenu_window, QW_PARENT);

    FindProperty (Frame_window, PRP_ICON, &Icon);

    // Узнаем размер и расположение окна рамки.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // Если значок не найден - закрашиваем окно картинки.
    if (Icon == NULLHANDLE) Painter_PreDrawControl (SysMenu_window, SYSCLR_BUTTONMIDDLE, 0, Frame_window, &Frame_rectangle, &Frame_placement);
    // Иначе - рисуем картинку.
    else Painter_DrawSystemMenu (SysMenu_window, Frame_window, &Frame_rectangle, &Frame_placement, Icon, FT_UNKNOWN, SysMenu_is_pressed);
  }

  // Перерисовываем кнопки.
  if (Message->msg == SM_DRAW_BUTTONS)
  {
    // Если рисование отключено - возврат.
    if (!Painter.Settings.Draw_frames) return;

    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна рамки нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Узнаем, как выглядит рамка окна.
    LONG Frame_type = FrameType (Frame_window);

    // Узнаем окно заголовка.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // Узнаем размер и расположение окна рамки.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // Рисуем кнопки.
    Painter_DrawButtons (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, TitleBar_window);
  }

  // Задаем подходящее расположение для окна картинки и кнопок.
  if (Message->msg == SM_PREPARE_CONTROLS)
  {
    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна рамки нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Узнаем размер и расположение окна.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // Задаем правильное расположение окна картинки, заголовка и других окон.
    // При этом окно рамки получит одно сообщение WM_PAINT вместо нескольких.
    Painter_PrepareWindowControls (Frame_window, FT_UNKNOWN, &Frame_rectangle, &Frame_placement, NULLHANDLE, NULLHANDLE, NULLHANDLE);
  }

  // Обновляем окно.
  if (Message->msg == SM_UPDATE_FRAME) UpdateWindow ((HWND) Message->mp1);

  // Обновляем все окна.
  if (Message->msg == SM_UPDATE_ALL_FRAMES)
  {
    // Перерисовываем рамки всех окон.
    UpdateAllWindows (QueryDesktopWindow ());
  }

  // Возврат.
  return;
}

// ─── Поток для рисования рамок ───

VOID Painter_PainterThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Painter->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.Painter->Message_queue == NULLHANDLE)
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
    Painter_PainterMessageProcessing (&Message, Thread);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
