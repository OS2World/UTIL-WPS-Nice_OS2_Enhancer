
// ─── Добавляет окна в список для передвижения изображения ───

// Window - окно, Message и *_parameter - сообщение, которое передается окну.
VOID Scroller_CollectWindows (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Если это передвижение на одну строку или страницу - запоминаем окно.
  INT Command = SHORT2FROMMP (Second_parameter);
  if (Command == SB_LINEDOWN || Command == SB_PAGEDOWN ||
      Command == SB_LINEUP   || Command == SB_PAGEUP  )
   if (Scroller_PermissionForScrolling (Window)) Scroller_AddWindowToList (Window);

  // Возврат.
  return;
}

// ─── Делает передвижение изображения в окне плавным ───

// Message - сообщение, которое передается окну.
VOID Scroller_SmoothScrolling (PQMSG Message)
{
  // Прежде всего окно должно получить это сообщение.
  Scroller.RTSettings.Detection_is_disabled = 1;
  WinSendMsg (Message->hwnd, Message->msg, Message->mp1, Message->mp2);
  Scroller.RTSettings.Detection_is_disabled = 0;

  // Затем - сообщение о том, что надо передвинуть изображение до указанного места.
  SHORT Slider_position = SHORT1FROMMP (Message->mp2);
  Message->mp2 = MPFROM2SHORT (Slider_position, SB_SLIDERPOSITION);

  // Возврат.
  return;
}

// ─── Завершает передвижение изображения с помощью мыши ───

VOID Scroller_TerminateDragging (VOID)
{
  // Завершаем передвижение.
  Scroller.RTSettings.Dragging = 0;

  Scroller.RTSettings.Target_window = NULLHANDLE;
  Scroller.RTSettings.VSB_Control = NULLHANDLE;
  Scroller.RTSettings.HSB_Control = NULLHANDLE;

  // Освобождаем указатель мыши.
  ResetPointer ();

  // Возврат.
  return;
}

// ─── Запоминает точки в окне ───

// Window - окно, в котором надо запомнить точки.
VOID Scroller_GetPointsFromWindow (HWND Window)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // Точки будем запоминаем в квадрате размером SCROLLER_SCRLIST_LINE * SCROLLER_SCRLIST_LINE * 2 или меньше.
  INT Max_count = 0;
  if (Min (Rectangle.xRight, Rectangle.yTop) / 4 > SCROLLER_SCRLIST_LINE) Max_count = SCROLLER_SCRLIST_LINE;
  else Max_count = Min (Rectangle.xRight, Rectangle.yTop) / 4;

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Запоминаем точки - как '>', расположенную в этом квадрате.
  // Если точка недоступна, то GpiQueryPel () возвращает (-1).
  POINT Point = {0};
  for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
  {
    Point.x = Rectangle.xRight / 2 - Count;
    Point.y = Rectangle.yTop / 2 - Count;
    Scroller.RTSettings.Line_1[Count] = GpiQueryPel (Presentation_space, &Point);
    Point.y = Rectangle.yTop / 2 + Count;
    Scroller.RTSettings.Line_2[Count] = GpiQueryPel (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Находит точки в окне и возвращает расстояние, на которое они были сдвинуты ───

// Window - окно, в котором надо найти точки, Direction - направление,
// в котором происходит передвижение, Supposition - предполагаемое расстояние.
INT Scroller_FindPoints (HWND Window, LONG Direction, INT Supposition)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // Точки запоминались в квадрате размером SCROLLER_SCRLIST_LINE * SCROLLER_SCRLIST_LINE * 2 или меньше.
  INT Max_count = 0;
  if (Min (Rectangle.xRight, Rectangle.yTop) / 4 > SCROLLER_SCRLIST_LINE) Max_count = SCROLLER_SCRLIST_LINE;
  else Max_count = Min (Rectangle.xRight, Rectangle.yTop) / 4;

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return 0;

  // Расстояние и число совпадений неизвестны.
  INT Distance = 0; INT Coincidences = 0;

  // Зная скорость, ищем точки в окне сразу на их предполагаемом месте - и
  // если они там, возвращаем расстояние. Проверяем область [A-2 .. A+2].
  BYTE Success = 0;
  if (Supposition != 0)
   for (INT Count_for_lines = 0; Count_for_lines < 4; Count_for_lines += 1)
   {
     // Задаем смещение.
     INT X_Offset = 0; INT Y_Offset = 0;
     if (Direction == WM_VSCROLL)
     {
       if (Count_for_lines == 0) Y_Offset = Supposition;
       if (Count_for_lines == 1) Y_Offset = Supposition + 1;
       if (Count_for_lines == 2) Y_Offset = Supposition - 1;
       if (Count_for_lines == 3) Y_Offset = Supposition + 2;
       if (Count_for_lines == 4) Y_Offset = Supposition - 2;
     }
     else
     {
       if (Count_for_lines == 0) X_Offset = Supposition;
       if (Count_for_lines == 1) X_Offset = Supposition - 1;
       if (Count_for_lines == 2) X_Offset = Supposition + 1;
       if (Count_for_lines == 3) X_Offset = Supposition - 2;
       if (Count_for_lines == 4) X_Offset = Supposition + 2;
     }

     // Смотрим, какие точки там сейчас. Если точка недоступна, то GpiQueryPel () возвращает (-1).
     POINT Point = {0}; BYTE Points_is_found = 1;
     for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
     {
       Point.x = Rectangle.xRight / 2 - Count - X_Offset;
       Point.y = Rectangle.yTop / 2 - Count + Y_Offset;
       if (Scroller.RTSettings.Line_1[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
       Point.y = Rectangle.yTop / 2 + Count + Y_Offset;
       if (Scroller.RTSettings.Line_2[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
     }

     // Если точки найдены - завершаем поиск.
     if (Points_is_found) { Success = 1; break; }
   }

  // Если точки найдены - вернем это расстояние.
  if (Success) Distance = Supposition;
  // Иначе - проводим поиск по всей области. Область поиска - Max_count.
  else
  {
    // Ищем точки в окне в любом месте начиная с того, где они были - и если найдены,
    // возвращаем расстояние. Если найдено несколько совпадений, возвращаем 0.
    for (INT Count_for_lines = 0; Count_for_lines < Max_count; Count_for_lines += 1)
    {
      // Задаем смещение.
      INT X_Offset = 0; INT Y_Offset = 0;
      if (Direction == WM_VSCROLL) Y_Offset = Count_for_lines;
      else X_Offset = Count_for_lines;

      // Смотрим, какие точки там сейчас. Если точка недоступна, то GpiQueryPel () возвращает (-1).
      POINT Point = {0}; BYTE Points_is_found = 1;
      for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
      {
        Point.x = Rectangle.xRight / 2 - Count - X_Offset;
        Point.y = Rectangle.yTop / 2 - Count + Y_Offset;
        if (Scroller.RTSettings.Line_1[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
        Point.y = Rectangle.yTop / 2 + Count + Y_Offset;
        if (Scroller.RTSettings.Line_2[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
      }

      // Если точки найдены:
      if (Points_is_found)
      {
        // Увеличиваем счетчик совпадений и запоминаем расстояние.
        Coincidences += 1; Distance = Count_for_lines;
        // Если совпадений больше 1, прекращаем поиск по всей области.
        if (Coincidences > 1) Distance = 0;
        // Если совпадение было сразу же или их было больше 1, возвращаем 0.
        if (Distance == 0) break;
      }
    }
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return Distance;
}

// ─── Запоминает окна и скорость при плавном передвижении ───

// Window - окно, Message и *_parameter - сообщение, которое передается окну.
VOID Scroller_DetectSpeed (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Когда передвижение начинается - запоминаем окно.
  if (Scroller.RTSettings.Step_of_scrolling == 1)
  {
    // Если передвижение изображения возможно:
    if (Scroller_PermissionForScrolling (Window))
     if (!Scroller_WindowHasPreDefinedSpeed (Window))
     {
       // Запоминаем окно.
       Scroller.RTSettings.Scrolling_window = Window;
       Scroller.RTSettings.ScrList_position = 0;
       Scroller.RTSettings.Messages_is_redirected = 0;

       // Увеличиваем счетчик.
       Scroller.RTSettings.Step_of_scrolling ++;
     }

    // Возврат.
    return;
  }

  // Окно, которое получает сообщения от полосок просмотра, может посылать их
  // в другое окно. Тогда в нем и надо измерять скорость.
  if (Scroller.RTSettings.Step_of_scrolling == 2)
   if (Window != Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position == 0)
     if (!Scroller.RTSettings.Messages_is_redirected)
      if (Scroller_PermissionForScrolling (Window))
       if (!Scroller_WindowHasPreDefinedSpeed (Window))
       {
         // Переключаемся на другое окно.
         Scroller.RTSettings.Scrolling_window = Window;
         Scroller.RTSettings.ScrList_position = 0;
         Scroller.RTSettings.Messages_is_redirected = 1;
       }

  // На втором шаге - запоминаем точки в окне.
  if (Scroller.RTSettings.Step_of_scrolling == 2)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position == 0)
    {
      // Заносим окно в список и запоминаем номер записи в нем.
      Scroller.RTSettings.ScrList_position = Scroller_AddWindowToList (Scroller.RTSettings.Scrolling_window);

      // Запоминаем положение движка полоски.
      Scroller.RTSettings.Slider_position = SHORT1FROMMP (Second_parameter);
      // Запоминаем точки в окне.
      Scroller_GetPointsFromWindow (Window);

      // Увеличиваем счетчик.
      Scroller.RTSettings.Step_of_scrolling ++;

      // Возврат.
      return;
    }

  // На следующем шаге ничего не делаем - возможно, изображение еще не передвинуто.
  if (Scroller.RTSettings.Step_of_scrolling == 3)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position != 0)
    {
      // Увеличиваем счетчик.
      Scroller.RTSettings.Step_of_scrolling ++;

      // Возврат.
      return;
    }

  // На последнем шаге узнаем скорость и сбрасываем переменную снова в 0.
  if (Scroller.RTSettings.Step_of_scrolling == 4)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position != 0)
    {
      // Узнаем, на сколько делений передвинут движок полоски.
      SHORT Current_position = SHORT1FROMMP (Second_parameter);
      INT I = Scroller.RTSettings.ScrList_position;

      // Если движок полоски передвинут вниз или вправо - запоминаем скорость.
      if (Current_position > Scroller.RTSettings.Slider_position)
      {
        // Запоминаем скорость по горизонтали:
        if (Message == WM_HSCROLL)
        {
          // Предполагаемое расстояние:
          INT Lines = Current_position - Scroller.RTSettings.Slider_position;
          INT Supposition = DivideMultiply (Scroller.Scrolling_list[I].X_Velocity_DD, Scroller.Scrolling_list[I].X_Velocity_D, Lines);
          // На самом деле пройдено:
          INT Distance = Scroller_FindPoints (Window, Message, Supposition);

          // Запоминаем пройденное расстояние - как в точках, так и в делениях полоски просмотра.
          if (Distance > 0)
          {
            // Если скорость изменена - запоминаем ее.
            INT Previous_V_DD = Scroller.Scrolling_list[I].X_Velocity_DD;
            INT Previous_V_D  = Scroller.Scrolling_list[I].X_Velocity_D;

            if (Previous_V_DD == 0 || Previous_V_D == 0) { Previous_V_DD = 0; Previous_V_D = 1; }

            if (Distance >= Lines)
             if (Distance / Lines != Previous_V_DD / Previous_V_D)
              if (Distance / Lines < SCROLLER_MAX_VELOCITY_DD_D)
              {
                // Запоминаем скорость.
                Scroller.Scrolling_list[I].X_Velocity_DD = Distance;
                Scroller.Scrolling_list[I].X_Velocity_D  = Lines;

                // Список надо будет сохранить.
                WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);
              }
          }
        }

        // Запоминаем скорость по вертикали:
        if (Message == WM_VSCROLL)
        {
          // Предполагаемое расстояние:
          INT Lines = Current_position - Scroller.RTSettings.Slider_position;
          INT Supposition = DivideMultiply (Scroller.Scrolling_list[I].Y_Velocity_DD, Scroller.Scrolling_list[I].Y_Velocity_D, Lines);
          // На самом деле пройдено:
          INT Distance = Scroller_FindPoints (Window, Message, Supposition);

          // Запоминаем пройденное расстояние - как в точках, так и в делениях полоски просмотра.
          if (Distance > 0)
          {
            // Если скорость изменена - запоминаем ее.
            INT Previous_V_DD = Scroller.Scrolling_list[I].Y_Velocity_DD;
            INT Previous_V_D  = Scroller.Scrolling_list[I].Y_Velocity_D;

            if (Previous_V_DD == 0 || Previous_V_D == 0) { Previous_V_DD = 0; Previous_V_D = 1; }

            if (Distance >= Lines)
             if (Distance / Lines != Previous_V_DD / Previous_V_D)
              if (Distance / Lines < SCROLLER_MAX_VELOCITY_DD_D)
              {
                // Запоминаем скорость.
                Scroller.Scrolling_list[I].Y_Velocity_DD = Distance;
                Scroller.Scrolling_list[I].Y_Velocity_D  = Lines;

                // Список надо будет сохранить.
                WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);
              }
          }
        }
      }

      // Больше не запоминаем скорость.
      Scroller.RTSettings.Step_of_scrolling = 0;
    }

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ScrollerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Запоминаем окна, в которых происходит передвижение изображения.
  if (Scroller.Settings.Key_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     Scroller_CollectWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

  // Передвижение изображения будет плавным. Если в полоске просмотра перемещается
  // движок, то пусть окно сразу передвигает изображение. Сообщение будет изменено.
  if (Scroller.Settings.Smooth_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     if (SHORT2FROMMP (Message->mp2) == SB_SLIDERTRACK)
      Scroller_SmoothScrolling (Message);

  // Запоминаем окна и скорость при плавном передвижении.
  if (Scroller.Settings.Image_dragging)
  {
    // После нажатия мыши над полоской просмотра скорость можно измерять.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
     Scroller.RTSettings.Step_of_scrolling = 1;

    // Когда идет передвижение - измеряем скорость.
    if (Scroller.RTSettings.Step_of_scrolling != 0)
     if (!Scroller.RTSettings.Dragging)
      if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
      {
        SHORT Command = SHORT2FROMMP (Message->mp2);
        if (Command == SB_SLIDERTRACK || Command == SB_SLIDERPOSITION)
         Scroller_DetectSpeed (Message->hwnd, Message->msg, Message->mp1, Message->mp2);
      }
  }

  // Передвигаем изображение с помощью мыши.
  if (Scroller.Settings.Image_dragging)
  {
    // Смотрим на сообщение.
    BYTE Beginning = 0;

    // Если нажата правая кнопка и включен или нажат Caps Lock - начинаем передвижение.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_CAPS_LOCK)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsToggled (SC_CAPSLOCK) || KeyIsPressed (SC_CAPSLOCK))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // Если нажата правая кнопка и включен Scroll Lock - начинаем передвижение.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_SCROLL_LOCK)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsToggled (SC_SCRLLOCK))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // Если нажата правая кнопка и клавиша Shift - начинаем передвижение.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_SHIFT)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsPressed (SC_LEFT_SHIFT) || KeyIsPressed (SC_RIGHT_SHIFT))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // Начинаем передвижение.
    if (Beginning == 1)
    {
      // Для полосок просмотра, рамок и окон Win-OS/2 это не должно действовать.
      if (!IsFrameWindow (Message->hwnd))   if (!IsTitleBarWindow (Message->hwnd))
      if (!IsMenuWindow (Message->hwnd))    if (!IsScrollBarWindow (Message->hwnd))
      if (!IsWindowsWindow (Message->hwnd)) if (!IsDesktopWindow (Message->hwnd))
      if (WinQueryWindow (Message->hwnd, QW_PARENT) != QueryDesktopWindow ())
      {
        // Начинаем передвижение.
        HWND Desktop = QueryDesktopWindow ();
        POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
        HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);
        WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_BEGIN, (MPARAM) Window, 0);

        // Сообщение должно быть сброшено.
        *Discarding = 1;
      }
    }

    // Передвигаем изображение в выбранную точку.
    if (Scroller.RTSettings.Dragging == 1) 
     if (Message->msg == WM_MOUSEMOVE)
      if (MouseButtonIsPressed ())
      {
        // Передвигаем изображение в выбранную точку.
        WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_DRAG, 0, 0);

        // Сообщение должно быть сброшено.
        // При этом указатель мыши не будет изменен.
        *Discarding = 1;
      }

    // Если отжата кнопка мыши или она нажата во второй раз - завершаем передвижение.
    if (Scroller.RTSettings.Dragging == 1)
     if (Message->msg == WM_BUTTON1UP   || Message->msg == WM_BUTTON2UP   || Message->msg == WM_BUTTON3UP   ||
         Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
         (Message->msg == WM_MOUSEMOVE && !MouseButtonIsPressed ()))
     {
       // Завершаем передвижение.
       Scroller_TerminateDragging ();
       WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

       // Если надо использовать Caps Lock - сбрасываем переключатели на клавиатуре.
       if (Scroller.Settings.Image_dragging == SCROLLER_USE_CAPS_LOCK)
        if (KeyIsToggled (SC_CAPSLOCK) || KeyIsPressed (SC_CAPSLOCK))
         WinPostQueueMsg (Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0);

       // Сообщение должно быть сброшено.
       *Discarding = 1;
     }

    // Если надо использовать Scroll Lock и он отключен - завершаем передвижение.
    if (Scroller.RTSettings.Dragging == 1)
     if (Scroller.Settings.Image_dragging == SCROLLER_USE_SCROLL_LOCK)
      if (Message->msg == WM_MOUSEMOVE)
       if (!KeyIsToggled (SC_SCRLLOCK))
       {
         // Завершаем передвижение.
         Scroller_TerminateDragging ();
         WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

         // Сообщение должно быть сброшено.
         *Discarding = 1;
       }

    // Если надо использовать Shift и он не нажат - завершаем передвижение.
    if (Scroller.RTSettings.Dragging == 1)
     if (Scroller.Settings.Image_dragging == SCROLLER_USE_SHIFT)
      if (Message->msg == WM_MOUSEMOVE)
       if (!KeyIsPressed (SC_LEFT_SHIFT)) if (!KeyIsPressed (SC_RIGHT_SHIFT))
       {
         // Завершаем передвижение.
         Scroller_TerminateDragging ();
         WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

         // Сообщение должно быть сброшено.
         *Discarding = 1;
       }
  }

  // Устанавливаем указатели мыши при передвижении изображения.
  if (Scroller.Settings.Image_dragging) if (Scroller.RTSettings.Dragging == 1)
   if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK)
    if (Message->mp1 == (MPARAM) MRK_SET_POINTER) if (Message->mp2 == (MPARAM) NULLHANDLE)
     if (Resources.Pointer_for_dragging != NULLHANDLE)
      WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

  // Возврат.
  return;
}

// ─── Слежение за клавиатурой ───

// Все переменные - внешние.
VOID ScrollerKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Сдвигаем изображение на одну строку, если нажата стрелка и включен Scroll Lock.
  if (Scroller.Settings.Key_scrolling) if (!Scroller.RTSettings.Dragging)
   if (Message->msg == WM_CHAR)
   {
     // Смотрим, какая клавиша нажата.
     BYTE Scan_code = CHAR4FROMMP (Message->mp1);
     SHORT State = SHORT1FROMMP (Message->mp1);

     // Если идет нажатие клавиши:
     if (!(State & KC_KEYUP))
     {
       // Проверяем клавишу.
       BYTE Perform_action = 0;

       // Если это стрелка и Scroll Lock включен - изображение можно двигать.
       // Проверять, действительно ли клавиша нажата, здесь не надо - это может быть сообщение и от мыши.
       if (Scan_code == SC_UP || Scan_code == SC_DOWN || Scan_code == SC_LEFT || Scan_code == SC_RIGHT)
        if (!IsScrollBarWindow (Message->hwnd))
         if (KeyIsToggled (SC_SCRLLOCK))
          Perform_action = 1;

       // Цифровые клавиши могут быть переопределены.
       if (Perform_action)
        if (Scan_code >= SC_NUM_FIRST) if (Scan_code <= SC_NUM_LAST)
         Perform_action = 0;

       // Если изображение можно двигать - посылаем сообщение в поток.
       if (Perform_action) WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_LINE, (MPARAM) Message->hwnd, (MPARAM) Scan_code);
     }
   }

  // Передвигаем изображение с помощью мыши.
  if (Scroller.Settings.Image_dragging)
  {
    // Если нажата клавиша Esc - завершаем передвижение.
    if (Scroller.RTSettings.Dragging == 1) if (Message->msg == WM_CHAR)
    {
      // Смотрим, какая клавиша нажата.
      BYTE Scan_code = CHAR4FROMMP (Message->mp1);
      SHORT State = SHORT1FROMMP (Message->mp1);

      // Если идет нажатие клавиши:
      if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
      {
        // Если это Esc - завершаем передвижение.
        if (Scan_code == SC_ESC)
        {
          // Затем - завершаем передвижение.
          WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

          // Сообщение должно быть сброшено.
          *Discarding = 1;
        }
      }
    }
  }

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ScrollerSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // Запоминаем окна, в которых происходит передвижение изображения.
  if (Scroller.Settings.Key_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     Scroller_CollectWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

  // Запоминаем окна и скорость при плавном передвижении.
  if (Scroller.Settings.Image_dragging)
   if (!Scroller.RTSettings.Detection_is_disabled)
    if (!Scroller.RTSettings.Dragging)
     if (Scroller.RTSettings.Step_of_scrolling != 0)
      if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
      {
        SHORT Command = SHORT2FROMMP (Message->mp2);

        if (Command == SB_SLIDERTRACK || Command == SB_SLIDERPOSITION)
         Scroller_DetectSpeed (Message->hwnd, Message->msg, Message->mp1, Message->mp2);
      }

  // Возврат.
  return;
}
