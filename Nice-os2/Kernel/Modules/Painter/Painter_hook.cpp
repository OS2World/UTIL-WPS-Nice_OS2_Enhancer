// ─── Борется с ошибкой, вызывающей "мигание" рамки ───

// Message_queue - очередь, в которую направляется сообщение WM_MARK.
VOID Painter_DetectPermanentDrawing (HWND Frame_window, HMQ Message_queue)
{
  // Если нажата кнопка мыши - это может быть передвижением окна, возврат.
  if (MouseIsBusy ()) return;

  // Если это окно VIO или список окон - возврат.
  if (IsVIOWindow (Frame_window) || IsWinListWindow (Frame_window)) return;

  // Узнаем текущее время.
  LONG Current_time = WinGetCurrentTime (Enhancer.Application);

  // Находим очередь в списке.
  PMSGQUEUEINFO Target = NULL;

  for (INT Count = PAINTER_MONITORING_QUEUES - 1; Count >= 0; Count --)
   if (Painter.RTSettings.Drawing_windows[Count].Queue == Message_queue)
   {
     Target = &Painter.RTSettings.Drawing_windows[Count]; break;
   }

  // Если очереди сообщений нет в списке:
  if (Target == NULL)
  {
    // Сдвигаем список.
    for (INT Count = 0; Count < PAINTER_MONITORING_QUEUES - 1; Count ++)
     memcpy (&Painter.RTSettings.Drawing_windows[Count], &Painter.RTSettings.Drawing_windows[Count + 1], sizeof (MSGQUEUEINFO));

    // Запоминаем очередь сообщений.
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Queue = Message_queue;

    // Устанавливаем счетчик в значение "1" и запоминаем время его изменения.
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Quantity = 1;
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Time = Current_time;

    // Возврат.
    return;
  }

  // Если после увеличения счетчика прошло достаточно много времени:
  if (Current_time > Target->Time)
   if (Current_time - Target->Time > Painter.Constants.Drawing_check_timeout)
   {
     // Устанавливаем счетчик в значение 1 и запоминаем время его изменения.
     Target->Quantity = 1; Target->Time = Current_time;

     // Возврат.
     return;
   }

  // Если счетчик достиг большой величины:
  if (Target->Quantity > Painter.Constants.Permanent_drawing)
  {
    // Сбрасываем все счетчики.
    bzero (&Painter.RTSettings.Drawing_windows, sizeof (Painter.RTSettings.Drawing_windows));

    // Запоминаем PID приложения, создавшего окно.
    BYTE Success = 0;

    PID Process_ID = 0; TID Thread_ID = 0;
    WinQueryWindowProcess (Frame_window, &Process_ID, &Thread_ID);

    if (Process_ID)
    {
      for (INT Process_count = 0; Process_count < PAINTER_STUBBORN_PID_TABLE; Process_count ++)
      {
        if (Painter.RTSettings.Stubborn_processes[Process_count])
        {
          BYTE Process_is_exists = 1;
          if (DosVerifyPidTid (Painter.RTSettings.Stubborn_processes[Process_count], 1) != NO_ERROR) Process_is_exists = 0;

          if (!Process_is_exists) Painter.RTSettings.Stubborn_processes[Process_count] = 0;
        }
      }

      for (Process_count = 0; Process_count < PAINTER_STUBBORN_PID_TABLE; Process_count ++)
      {
        if (!Painter.RTSettings.Stubborn_processes[Process_count])
        {
          Painter.RTSettings.Stubborn_processes[Process_count] = Process_ID;
          Success = 1;
          break;
        }
      }
    }

    // Если это сделать не удалось:
    if (!Success)
    {
      // Отключаем рисование рамок.
      Painter.Settings.Draw_frames = 0;

      // Перерисовываем рамки всех окон. Никаких окон сообщений показывать нельзя - приложения падают при этом.
      WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_UPDATE_ALL_FRAMES, 0, 0);
    }
  }

  // Увеличиваем счетчик и запоминаем время его изменения.
  Target->Quantity ++; Target->Time = Current_time;

  // Возврат.
  return;
}

// ─── Обрабатывает сообщения о рисовании ───

// Все переменные - внешние.
VOID Painter_NiceWindowsPaintMsgNode (ULONG Message, MPARAM First_parameter, HWND Frame_window, LONG Frame_type, HWND Window, LONG Window_type)
{
  // Можно рисовать рамки вместо существующих. Для этого надо задать свои обработчики
  // сообщений для окон картинки, заголовка, кнопок и меню и не выполнять рисование.
  // В некоторых случаях заменять обработчики не следует.
  BYTE SubClassing = 1;
  if (Window_type == WT_BORDER || Window_type == WT_SYSMENU) SubClassing = 0;

  // Если это можно сделать:
  if (SubClassing)
  {
    // Выбираем обработчик сообщений.
    PFNWP New_performer = NULL;

    if (Window_type == WT_TITLEBAR) New_performer = (PFNWP) Painter_TitleBarWindowHook;
    if (Window_type == WT_MINMAX)   New_performer = (PFNWP) Painter_MinMaxWindowHook;
    if (Window_type == WT_MENU)     New_performer = (PFNWP) Painter_MenuWindowHook;

    // Если он выбран:
    if (New_performer != NULL)
    {
      // Если это не обработчик расширителя - заменяем его.
      PFNWP Current_performer = (PFNWP) WinQueryWindowPtr (Window, QWP_PFNWP);
      if (Current_performer != New_performer) Painter_SubClassWindow (Frame_window, Window, Window_type);

      // Возврат.
      return;
    }
  }

  // Если требовалось обработать сообщение для окна обычных кнопок - возврат.
  if (Window_type == WT_MINMAX) return;

  // Если требовалось перерисовать рамку, но их украшать не надо - возврат.
  if (Window_type == WT_BORDER) if (!Painter_FrameDrawingIsRequired ()) return;

  // Посылаем в очередь сообщение WM_MARK. К тому времени, когда оно придет, окно
  // уже будет перерисовано, и тогда поверх него можно рисовать что-то новое. Из-за
  // добавления сообщений могут возникать ошибки.
  {
    // Узнаем очередь сообщений.
    HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);

    // Боремся с ошибкой, вызывающей "мигание" рамки.
    if (Message == WM_PAINT)
     if (Window_type == WT_BORDER)
      Painter_DetectPermanentDrawing (Frame_window, Message_queue);

    // Посылаем сообщение в очередь.
    WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Window);
  }

  // Возврат.
  return;
}

// ─── Обрабатывает сообщение WM_MARK ───

// *_parameter - данные, которые передаются вместе с сообщением.
VOID Painter_NiceWindowsMarkMsgNode (MPARAM Second_parameter)
{
  // Узнаем окно, которое должно быть перерисовано.
  HWND Target_window = (HWND) Second_parameter;

  // Узнаем, какое это окно.
  ULONG Target = WindowType (Target_window);

  // Узнаем окно рамки.
  HWND Frame_window = QueryFrameWindow (Target_window);

  // Посылаем сообщение в поток рисования.
  WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Target);

  // Возврат.
  return;
}

// ─── Перерисовывает рамки окон ───

// Window - окно, Message и *_parameter - сообщение, которое передается окну.
VOID Painter_NiceWindows (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Если окно получает сообщение о том, что оно должно быть перерисовано:
  if (Message == WM_PAINT || Message == TBM_SETHILITE || Message == WM_ACTIVATE)
  {
    // Узнаем, можно ли перерисовать окно, а также рамку окна.
    LONG Window_type = WT_UNKNOWN;
    HWND Frame_window = Painter_PermissionForDrawing (Window, &Window_type);

    // Если рамку рисовать можно:
    if (Frame_window != NULLHANDLE)
    {
      // Узнаем, как выглядит рамка окна.
      LONG Frame_type = FrameType (Frame_window);

      // Обрабатываем сообщение.
      Painter_NiceWindowsPaintMsgNode (Message, First_parameter, Frame_window, Frame_type, Window, Window_type);

      // Если у окна есть заголовок и кнопки:
      if (Frame_type != FT_FLAT)
      {
        // Если окно должно быть перерисовано - узнаем картинку, заголовок и состояние кнопок.
        if (Message == WM_PAINT)
        {
          BYTE Query_properties = 0;

          if (Painter.Settings.Draw_system_menus) if (Window_type == WT_SYSMENU)  Query_properties = 1;
          if (Painter.Settings.Draw_titles)       if (Window_type == WT_TITLEBAR) Query_properties = 1;
          if (Painter.Settings.Draw_buttons)      if (Window_type == WT_BORDER)   Query_properties = 1;

          if (Query_properties) WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_QUERY_PROPERTIES, (MPARAM) Frame_window, (MPARAM) Window_type);
        }

        // Если главное окно приложения становится выбранным - проверяем состояние других окон.
        if (Message == TBM_SETHILITE) if (First_parameter == (MPARAM) 1)
         if (Frame_window == QueryMainWindow (Frame_window))
          WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_CHECK_CONTROLS, (MPARAM) Frame_window, 0);
      }
    }

    // Рамку для окон постоянного размера могут закрывать дочерние окна, например,
    // окно рабочей области. Когда они перерисовываются, ее надо проверять.
    if (Painter.Settings.Draw_const_frames) if (Painter.Settings.Draw_volume_lines)
     if (Message == WM_PAINT)
     {
       // Если окна рамки неизвестно - узнаем его.
       if (Frame_window == NULLHANDLE) Frame_window = QueryFrameWindow (Window);

       // Если окно имеет рамку постоянного размера:
       if (Frame_window != NULLHANDLE && Frame_window != Window)
        if (FrameType (Frame_window) == FT_CONST)
        {
          // Если окно, которое надо перерисовать, не заголовок и не кнопки:
          LONG Window_type = WindowType (Window);

          if (Window_type != WT_SYSMENU && Window_type != WT_TITLEBAR &&
              Window_type != WT_MINMAX  && Window_type != WT_MENU )
          {
            // Если окно рамки может быть перерисовано:
            if (Painter_PermissionForDrawing (Frame_window))
            {
              // Посылаем сообщение в поток.
              WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_CHECK_FRAME, (MPARAM) Frame_window, (MPARAM) Window);
            }
          }
        }
     }
  }

  // Обрабатываем сообщение WM_MARK, которое приходит в очередь окна.
  if (Window == NULLHANDLE) if (Message == WM_MARK)
   if (First_parameter == (MPARAM) MRK_DRAW_FRAME)
    Painter_NiceWindowsMarkMsgNode (Second_parameter);

  // При закрытии окна - удаляем его из списка.
  if (Message == WM_DESTROY)
   if (IsFrameWindow (Window))
    DiscardUnusedProperties (Window);

  // Возврат.
  return;
}

// ─── Посылает сообщение в поток рисования или в очередь окна ───

// Frame_window - окно рамки.
VOID Painter_NiceControlsDrawingNode (HWND Frame_window)
{
  // Перерисовываем рамку выбранного окна.
  HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Frame_window);

  // Перерисовываем картинку в левом верхнем углу окна.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  if (SysMenu_window != NULLHANDLE) WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) SysMenu_window);

  // Возврат.
  return;
}

// ─── Обрабатывает сообщение WM_MARK ───

// *_parameter - данные, которые передаются вместе с сообщением.
VOID Painter_NiceControlsMarkMsgNode (MPARAM First_parameter, MPARAM Second_parameter)
{
  // Узнаем окно, которое должно быть перерисовано.
  HWND Control_window = (HWND) Second_parameter;

  // Если это действительно окно картинки:
  if (WindowType (Control_window) == WT_SYSMENU)
  {
    // Посылаем сообщение в поток рисования.
    LONG Control_is_pressed = 0;
    if (First_parameter == (MPARAM) MRK_PRESS_SYSMENU) Control_is_pressed = 1;

    WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_SYSMENU, (MPARAM) Control_window, (MPARAM) Control_is_pressed);
  }

  // Возврат.
  return;
}

// ─── Обрабатывает сообщение WM_MENUSELECT ───

// *_parameter - данные, которые передаются вместе с сообщением.
VOID Painter_NiceControlsMenuSelectMsgNode (MPARAM Second_parameter)
{
  // Если была нажата картинка в левом верхнем углу окна, а затем нажата
  // клавиша Esc или кнопка мыши, чтобы убрать меню - рисуем рамку для окна.

  // Узнаем окно меню.
  HWND Menu_window = (HWND) Second_parameter;

  // Узнаем, можно ли перерисовать окно, а также рамку окна.
  LONG Window_type = WT_UNKNOWN;
  HWND Frame_window = Painter_PermissionForDrawing (Menu_window, &Window_type);

  // Если рамку рисовать нельзя - возврат.
  if (Frame_window == NULLHANDLE) return;

  // Если это сообщение от окна картинки:
  if (Window_type == WT_SYSMENU)
  {
    // Узнаем, нажата ли картинка.
    LONG SysMenu_is_pressed = 0;
    if (MouseIsBusy ()) if (WindowIsActive (Frame_window))
    {
      // Узнаем окно, над которым расположен указатель мыши.
      HWND Desktop = QueryDesktopWindow ();

      POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
      HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);

      // Если это окно картинки - она нажата.
      if (Window == Menu_window) SysMenu_is_pressed = 1;
    }

    // Посылаем в очередь сообщение WM_MARK. Когда оно придет, картинку можно будет перерисовать.
    MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;
    if (SysMenu_is_pressed) First_parameter = (MPARAM) MRK_PRESS_SYSMENU;

    HMQ Message_queue = WinQueryWindowULong (Menu_window, QWL_HMQ);
    WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Menu_window);

    // Перерисовываем окно картинки, которое было выбрано раньше.
    if (Painter.RTSettings.Prev_selected_menu != NULLHANDLE)
     if (Painter.RTSettings.Prev_selected_menu != Menu_window)
     {
       // Посылаем в очередь сообщение WM_MARK. Когда оно придет, картинку можно будет перерисовать.
       MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;

       HMQ Message_queue = WinQueryWindowULong (Painter.RTSettings.Prev_selected_menu, QWL_HMQ);
       WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Painter.RTSettings.Prev_selected_menu);
     }

    // Запоминаем окно картинки.
    Painter.RTSettings.Prev_selected_menu = Menu_window;
  }
  // А если выбрано меню:
  else
  {
    // Перерисовываем окно картинки, которое было выбрано раньше.
    if (Painter.RTSettings.Prev_selected_menu != Menu_window)
    {
      // Посылаем в очередь сообщение WM_MARK. Когда оно придет, картинку можно будет перерисовать.
      MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;

      HMQ Message_queue = WinQueryWindowULong (Painter.RTSettings.Prev_selected_menu, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Painter.RTSettings.Prev_selected_menu);
    }

    // Выбранное окно картинки - неизвестно.
    Painter.RTSettings.Prev_selected_menu = NULLHANDLE;
  }

  // Возврат.
  return;
}

// ─── Посылает сообщение в поток рисования или в очередь окна ───

// Frame_window - окно рамки, SysMenu_is_pressed - ее состояние.
VOID Painter_AnimateButtonsDrawingNode (HWND Frame_window, BYTE SysMenu_is_pressed)
{
  // Перерисовываем картинку в левом верхнем углу окна.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;
  if (SysMenu_is_pressed) First_parameter = (MPARAM) MRK_PRESS_SYSMENU;

  HMQ Message_queue = WinQueryWindowULong (SysMenu_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) SysMenu_window);

  // Возврат.
  return;
}

// ─── Обрабатывает нажатия на кнопки в заголовке окна ───

// Frame_window - окно рамки, Message - сообщение, Control_window - получатель сообщения, Window_type - какое это окно.
// Возвращаемое значение: если сообщение обработано и его надо убрать из очереди, то 1, иначе 0.
BYTE Painter_AnimateButtons (HWND Frame_window, LONG Message, HWND Control_window, LONG Window_type, PPOINT Point)
{
  // Если надо рисовать картинку в левом верхнем углу окна:
  if (Painter.Settings.Draw_system_menus)
  {
    // Если указатель мыши расположен над картинкой:
    if (Window_type == WT_SYSMENU)
    {
      // Делаем картинку нажатой.
      Painter.RTSettings.Selected_button = SYSMENU_ACTION;

      // Перерисовываем ее.
      BYTE Control_is_pressed = 0;
      if (Painter.RTSettings.Selected_button == SYSMENU_ACTION) Control_is_pressed = 1;

      Painter_AnimateButtonsDrawingNode (Frame_window, Control_is_pressed);

      // Возврат.
      return 0;
    }
    // А если указатель расположен не над картинкой, и она была нажата:
    else
    {
      if (Painter.RTSettings.Selected_button == SYSMENU_ACTION)
      {
        // Кнопки не нажаты.
        Painter.RTSettings.Selected_button = NO_ACTION;

        // Перерисовываем ее.
        Painter_AnimateButtonsDrawingNode (Frame_window, 0);
      }
    }
  }

  // Если надо рисовать кнопки:
  if (Painter.Settings.Draw_buttons)
  {
    // Узнаем размер окна рамки.
    RECT Rectangle = {0}; WinQueryWindowRect (Frame_window, &Rectangle);

    // Узнаем окно заголовка.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // Узнаем размер окна заголовка.
    RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

    // Узнаем прямоугольники для кнопок.
    RECT Max_button = {0}; RECT Min_button = {0}; RECT Rollup_button = {0}; RECT Close_button = {0}; RECT All_buttons = {0};
    Painter_CalculateButtonRectangles (Frame_window, &Rectangle, TitleBar_window, &TitleBar_rectangle, &Max_button, &Min_button, &Rollup_button, &Close_button, &All_buttons);

    // Узнаем состояние кнопок в окне.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    // Проверяем, над какой кнопкой расположен указатель мыши.
    for (INT Count = 0; Count < 4; Count ++)
    {
      // Выбираем прямоугольник и действие.
      PRECT Current_button = NULL; LONG Action = NO_ACTION;

      switch (Count)
      {
        case 0:
        {
          if (!Max_button.yTop) break;
          Current_button = &Max_button;
          if (Buttons & MAXIMIZE_ACTION) Action = MAXIMIZE_ACTION;
          else Action = RESTORE_ACTION;
        }
        break;

        case 1:
        {
          if (!Min_button.yTop) break;
          Current_button = &Min_button;
          if (Buttons & MINIMIZE_ACTION) Action = MINIMIZE_ACTION;
          else Action = HIDE_ACTION;
        }
        break;

        case 2:
        {
          if (!Rollup_button.yTop) break;
          Current_button = &Rollup_button;
          Action = ROLLUP_ACTION;
        }
        break;

        case 3:
        {
          if (!Close_button.yTop) break;
          Current_button = &Close_button;
          Action = CLOSE_ACTION;
        }
        break;
      }

      // Если кнопки нет - продолжаем перебор.
      if (Current_button == NULL) continue;

      // Узнаем отступ от края кнопки.
      INT Pixel_margin = Painter_GetButtonPixelMargin ();

      // Если указатель мыши расположен над прямоугольником для кнопки:
      if (Point->x >= Current_button->xLeft + Pixel_margin && Point->x <= Current_button->xRight - Pixel_margin &&
          Point->y >= Current_button->yBottom + Pixel_margin && Point->y <= Current_button->yTop - Pixel_margin)
      {
        // Если кнопка была нажата - возврат.
        if (Painter.RTSettings.Selected_button == Action) return 1;

        // Делаем кнопку в заголовке нажатой.
        Painter.RTSettings.Selected_button = Action;

        // Вызываем окно наверх и делаем его выбранным. Можно посылать сообщение
        // в поток, но при этом некоторые окна не отвечают на сообщение WM_SYSCOMMAND.
        if (Message != WM_MOUSEMOVE) MoveWindowAbove (Frame_window);

        // Перерисовываем кнопки. Посылаем сообщение в поток.
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_BUTTONS, (MPARAM) Frame_window, 0);

        // Возврат.
        return 1;
      }
      // А если указатель расположен над другой кнопкой и раньше эта кнопка была нажата:
      else if (Painter.RTSettings.Selected_button == Action)
      {
        // Кнопки не нажаты.
        Painter.RTSettings.Selected_button = NO_ACTION;

        // Перерисовываем кнопки. Посылаем сообщение в поток.
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_BUTTONS, (MPARAM) Frame_window, 0);
      }
    }
  }

  // Возврат.
  return 0;
}

// ─── Обрабатывает нажатия на кнопки в заголовке окна ───

// Message - сообщение, которое передается одному из окон.
VOID Painter_NiceControls (PQMSG Message)
{
  // Обрабатываем нажатия на кнопки в заголовке окна.
  // При нажатии на кнопку надо запомнить окно. При передвижении мыши, если кнопка
  // нажата, надо перерисовать рамку. При отжатии - выполнить определенное действие.

  // Если все кнопки в заголовке были в отжатом состоянии:
  if (Painter.RTSettings.Selected_window == NULLHANDLE)
  {
    // Если нажата кнопка мыши - запоминаем окно и рисуем кнопку в заголовке нажатой.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
        Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
    {
      // Узнаем, можно ли перерисовать окно, а также рамку окна.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Message->hwnd, &Window_type);

      // Если рамку рисовать нельзя - возврат.
      if (Frame_window == NULLHANDLE) return;

      // Если указатель расположен над рамкой, заголовком или картинкой в левом верхнем углу окна:
      if (Window_type == WT_BORDER || Window_type == WT_SYSMENU || Window_type == WT_TITLEBAR)
      {
        // Если кнопки рисовать нельзя - возврат.
        if (!Painter_PermissionForButtonsDrawing (Frame_window)) return;

        // Запоминаем выбранное окно.
        Painter.RTSettings.Selected_window = Frame_window;

        // Рисуем одну из кнопок в заголовке нажатой.
        POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
        BYTE Button_is_pressed = Painter_AnimateButtons (Frame_window, Message->msg, Message->hwnd, Window_type, &Mouse_point);

        // Если нажата кнопка в заголовке окна - сброс сообщения.
        if (Button_is_pressed)
        {
          Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
        }
        // А если кнопка не нажата:
        else
        {
          // При двойном нажатии правой кнопки мыши в заголовке окно должно быть убрано наверх.
          if (Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
           if (Window_type == WT_TITLEBAR)
           {
             // Окно должно быть убрано наверх если оно увеличено.
             BYTE Rollup_window = 0;

             // Узнаем состояние кнопок в окне.
             LONG Buttons = 0;

             if (Painter.Settings.Draw_buttons) FindProperty (Frame_window, PRP_BUTTONS, &Buttons);
             else Buttons = Painter_QueryButtonsState (Frame_window, MAXIMIZE_ACTION, 1);

             if (Buttons & ROLLUP_ACTION)
              if (Painter_PermissionForRolling (Frame_window))
               Rollup_window = 1;

             // Убираем окно наверх.
             if (Rollup_window)
             {
               // Посылаем сообщение в поток.
               WinPostQueueMsg (Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Frame_window, (MPARAM) ROLLUP_ACTION);

               // Сбрасываем сообщение.
               Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
             }
           }
        }
      }
    }
  }
  // Если одна из кнопок в заголовке была в нажатом состоянии:
  else
  {
    // Если мышь движется - рисуем кнопки в заголовке окна. Одна из них становится нажатой.
    if (Message->msg == WM_MOUSEMOVE)
    {
      // При нажатии на заголовок окна сообщение WM_BUTTONUP теряется - делаем остановку.
      BYTE Stop_animation = 0; if (!MouseIsBusy ()) Stop_animation = 1;

      // Так же при переключении в другое окно с помощью Ctrl + Esc.
      if (Painter.RTSettings.Selected_window != NULLHANDLE)
       if (!WindowIsActive (Painter.RTSettings.Selected_window))
        if (!MouseIsBusy ())
         Stop_animation = 1;

      // Прекращаем слежение за мышью, если это требуется.
      if (Stop_animation)
      {
        // Кнопки не нажаты, выбранное окно - неизвестно.
        HWND Window = Painter.RTSettings.Selected_window;
        Painter.RTSettings.Selected_window = NULLHANDLE;
        Painter.RTSettings.Selected_button = NO_ACTION;

        // Перерисовываем рамку выбранного окна.
        Painter_NiceControlsDrawingNode (Window);

        // Возврат.
        return;
      }

      // Узнаем окно, над которым расположен указатель мыши.
      HWND Desktop = QueryDesktopWindow ();

      POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
      HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);

      // Узнаем, что это за окно, а также окно рамки.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Window, &Window_type);

      // Указатель мыши может быть расположен не в выбранном окне.
      HWND Control_window = Message->hwnd;

      if (Frame_window != Painter.RTSettings.Selected_window)
      {
        // Рисовать картинку и кнопки надо в нажатом окне.
        Frame_window = Painter.RTSettings.Selected_window; Window_type = WT_UNKNOWN;

        if (Painter.RTSettings.Selected_button == SYSMENU_ACTION) Control_window = WinWindowFromID (Frame_window, FID_SYSMENU);
        else Control_window = Frame_window;
      }

      // Рисуем кнопки.
      POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
      Painter_AnimateButtons (Frame_window, Message->msg, Control_window, Window_type, &Mouse_point);
    }

    // Если нажата еще одна кнопка мыши - сброс сообщения.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
        Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
    {
      // Узнаем, окно, над которым расположен указатель мыши, а также окно рамки.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Message->hwnd, &Window_type);

      // Если окно может быть перерисовано:
      if (Frame_window != NULLHANDLE)
      {
        // Если указатель мыши расположен над кнопками - сброс сообщения.
        POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
        BYTE Button_is_pressed = Painter_AnimateButtons (Frame_window, Message->msg, Message->hwnd, Window_type, &Mouse_point);

        if (Button_is_pressed)
        {
          Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
        }
      }
    }

    // Если отжата кнопка мыши - выполняем действие и рисуем кнопки в обычном виде.
    if (Message->msg == WM_BUTTON1UP || Message->msg == WM_BUTTON2UP || Message->msg == WM_BUTTON3UP)
    {
      // Кнопки не нажаты, выбранное окно - неизвестно.
      HWND Window = Painter.RTSettings.Selected_window;
      LONG Command = Painter.RTSettings.Selected_button;
      Painter.RTSettings.Selected_window = NULLHANDLE;
      Painter.RTSettings.Selected_button = NO_ACTION;

      // Перерисовываем рамку выбранного окна.
      Painter_NiceControlsDrawingNode (Window);

      // Выполняем определенное действие. Посылаем сообщение в поток.
      WinPostQueueMsg (Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Window, (MPARAM) Command);
    }
  }

  // Обрабатываем сообщение WM_MARK, которое приходит в очередь для окна картинки.
  if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK)
   if (Message->mp1 == (MPARAM) MRK_DRAW_SYSMENU || Message->mp1 == (MPARAM) MRK_PRESS_SYSMENU)
    Painter_NiceControlsMarkMsgNode (Message->mp1, Message->mp2);

  // Боремся с мусором в окнах. Обрабатываем сообщение WM_MENUSELECT.
  if (Painter.Settings.Draw_system_menus) if (Message->msg == WM_MENUSELECT)
   Painter_NiceControlsMenuSelectMsgNode (Message->mp2);

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PainterInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Рисуем рамку для окна.
  if (Painter.Settings.Draw_frames)
  {
    // Рисуем рамку.
    Painter_NiceWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

    // Обрабатываем нажатия на картинку и кнопки в заголовке окна.
    Painter_NiceControls (Message);
  }

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PainterSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // Рисуем рамку для окна.
  if (Painter.Settings.Draw_frames)
  {
    // Рисуем рамку.
    Painter_NiceWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

    // Обрабатываем нажатия на картинку и кнопки в заголовке окна.
    if (Message->msg == WM_MENUSELECT)
    {
      QMSG Incoming_message = { Message->hwnd, Message->msg, Message->mp1, Message->mp2, NULL, NULL, NULL };
      Painter_NiceControls (&Incoming_message);
    }
  }

  // Возврат.
  return;
}

