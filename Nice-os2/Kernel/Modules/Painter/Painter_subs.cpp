
// ─── Устанавливает обычный обработчик сообщений для окна ───

// Frame_window - окно рамки, Window - окно, обработчик для которого был заменен, Window_type - какое это окно.
VOID Painter_DetachWindow (HWND Frame_window, HWND Window, LONG Window_type)
{
  // Находим в списке свойств окон предыдущий обработчик.
  LONG Property = PRP_TITLEBAR_PERF;
  if (Window_type == WT_MINMAX)   Property = PRP_MINMAX_PERF;
  if (Window_type == WT_MENU)     Property = PRP_MENU_PERF;

  PFNWP Previous_performer = NULL; FindProperty (Frame_window, Property, &Previous_performer);

  // Если он был заменен:
  if (Previous_performer != NULL )
  {
    // Возвращаем его обратно.
    WinSubclassWindow (Window, Previous_performer);

    // Заносим в список пустое значение.
    PFNWP Empty_value = NULL; SetProperty (Frame_window, Property, &Empty_value);
  }

  // Возврат.
  return;
}

// ─── Вызывает обычный обработчик сообщений ───

// Все переменные - внешние.
MRESULT EXPENTRY Painter_CallMessageProcessor (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, PFNWP Hook)
{
  // Вызываем обработчик сообщений.
  PFNWP Performer = (PFNWP) WinQueryWindowPtr (Window, QWP_PFNWP);

  if (Performer != Hook) return Performer (Window, Message, First_parameter, Second_parameter);

  // Если это сделать не удалось - вызываем обработчик по умолчанию.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);
  CLASSINFO Properties = {0}; WinQueryClassInfo (ActiveApplication (), Window_name, &Properties);

  return Properties.pfnWindowProc (Window, Message, First_parameter, Second_parameter);
}

// ─── Обработчик сообщений для окон внутри окна рамки ───

// Все переменные - внешние.
MRESULT EXPENTRY Painter_WindowHookMessageProcessing (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, LONG Window_type, PFNWP Hook)
{
  // Узнаем окно рамки.
  HWND Frame_window = QueryFrameWindow (Window);

  // Устанавливаем для окна предыдущий обработчик сообщений.
  Painter_DetachWindow (Frame_window, Window, Window_type);

  // Если окно должно быть перерисовано:
  if (Message == WM_PAINT)
  {
    // Задаем возвращаемое значение.
    MRESULT Report = 0;

    // Если это окно меню:
    if (Window_type == WT_MENU)
    {
      // Вызываем обычный обработчик сообщений.
      Report = Painter_CallMessageProcessor (Window, Message, First_parameter, Second_parameter, Hook);
    }
    // А если это окно заголовка или кнопок:
    else
    {
      // Окно ничего не рисует.
      RECT Rectangle = {0};
      HPS Presentation_space = WinBeginPaint (Window, NULLHANDLE, &Rectangle);
      WinEndPaint (Presentation_space);
    }

    // Посылаем сообщение в поток рисования.
    if (Window_type != WT_MINMAX) WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Window_type);

    // Возврат.
    return Report;
  }

  // Если окно заголовка становится выбранным:
  if (Window_type == WT_TITLEBAR && Message == TBM_SETHILITE)
  {
    // Посылаем сообщение в поток рисования.
    WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_TITLEBAR);

    // Возврат.
    return (MRESULT) 1;
  }

  // Вызываем обычный обработчик сообщений.
  return Painter_CallMessageProcessor (Window, Message, First_parameter, Second_parameter, Hook);
}

// ─── Обработчик сообщений для окна заголовка ───

// Поток приложения вызывает TitleBar_performer всякий раз, когда для окна есть сообщение.

// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Painter_TitleBarWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Обрабатываем сообщение.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_TITLEBAR, (PFNWP) Painter_TitleBarWindowHook);
}

// ─── Обработчик сообщений для окна обычных кнопок ───

// Поток приложения вызывает MinMax_performer всякий раз, когда для окна есть сообщение.

// Window окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Painter_MinMaxWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Обрабатываем сообщение.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_MINMAX, (PFNWP) Painter_MinMaxWindowHook);
}

// ─── Обработчик сообщений для окна меню ───

// Поток приложения вызывает Menu_performer всякий раз, когда для окна есть сообщение.

// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Painter_MenuWindowHook (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Обрабатываем сообщение.
  return Painter_WindowHookMessageProcessing (Window, Message, First_parameter, Second_parameter, WT_MENU, (PFNWP) Painter_MenuWindowHook);
}

// ─── Задает для окна новый обработчик сообщений ───

// Frame_window - окно рамки, Window - окно, для которого надо заменить обработчик сообщений, Target - какое это окно.
VOID Painter_SubClassWindow (HWND Frame_window, HWND Window, ULONG Target)
{
  // Выбираем обработчик сообщений.
  PFNWP New_performer = NULL; LONG Property = 0;

  if (Target == WT_TITLEBAR) { New_performer = (PFNWP) Painter_TitleBarWindowHook; Property = PRP_TITLEBAR_PERF; }
  if (Target == WT_MINMAX)   { New_performer = (PFNWP) Painter_MinMaxWindowHook;   Property = PRP_MINMAX_PERF;   }
  if (Target == WT_MENU)     { New_performer = (PFNWP) Painter_MenuWindowHook;     Property = PRP_MENU_PERF;     }

  // Задаем новый обработчик. Теперь он будет получать сообщения, приходящие окну.
  PFNWP Current_performer = WinSubclassWindow (Window, New_performer);

  // Запоминаем предыдущий обработчик в списке свойств окон.
  if (Current_performer != NULL) SetProperty (Frame_window, Property, &Current_performer);

  // Возврат.
  return;
}

