
// ─── Выбирает окно для передвижения изображения ───

// Window - окно, в котором требуется передвигать изображение.
// Возвращаемое значение - то же самое окно или одно из его родительских окон (возможно, это поле ввода).
HWND Scroller_ChooseWindowFromScrollingList (HWND Window)
{
  // Если в окне можно передвигать изображение - будем посылать сообщение ему.
  // Окно добавляется в список в том случае, если оно хоть раз получило сообщение от полосок просмотра.
  if (Scroller_FindWindowInList (Window))
  {
    // Будем посылать сообщения этому окну.
    return Window;
  }
  // Иначе - проверяем родительские окна.
  else
  {
    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Находим родительское окно, в котором можно передвигать изображение.
    HWND Parent_window = WinQueryWindow (Window, QW_PARENT);
    while (Parent_window != Desktop && Parent_window != NULLHANDLE)
    {
      // Если в родительском окне можно передвигать изображение:
      if (Scroller_FindWindowInList (Parent_window))
      {
        // Будем посылать сообщения родительскому окну.
        return Parent_window;
      }

      // Узнаем следующее родительское окно.
      Parent_window = WinQueryWindow (Parent_window, QW_PARENT);
    }
  }

  // Возврат.
  return NULLHANDLE;
}

// ─── Передвигает изображение при нажатом Scroll Lock ───

// Selected_window - окно, в которое направлен ввод от пользователя, Scan_code показывает, какая клавиша нажата.
VOID Scroller_ScrollImage (HWND Selected_window, INT Scan_code)
{
  // Выбираем окно для передвижения изображения.
  HWND Target_window = Scroller_ChooseWindowFromScrollingList (Selected_window);

  // Если ни одно окно не выбрано - возврат.
  if (Target_window == NULLHANDLE) return;

  // В некоторых окнах передвигать изображение не надо.
  if (!Scroller_PermissionForKeyScrolling (Target_window)) return;

  // Если нажата стрелка вверх или вниз - проверяем состояние полоски сверху вниз,
  // а если нажата стрелка влево или вправо - проверяем состояние полоски слева направо.
  BYTE SB_Type = SBS_HORZ; if (Scan_code == SC_UP || Scan_code == SC_DOWN) SB_Type = SBS_VERT;

  // Пробуем найти полоску просмотра внутри выбранного окна.
  HWND SB_Control = Scroller_FindScrollBar (Target_window, SB_Type);

  // Если полоска есть - узнаем, в каком она состоянии.
  if (SB_Control != NULLHANDLE)
  {
    // Узнаем, в каком состоянии полоска.
    Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
  }
  // Если полоски нет - она может быть расположена рядом с окном.
  else
  {
    // Узнаем родительское окно.
    HWND Parent_window = WinQueryWindow (Target_window, QW_PARENT);

    // Проверяем, можно ли передвигать изображение в родительском окне.
    if (Scroller_PermissionForKeyScrolling (Parent_window))
    {
      // Ищем полоску в родительском окне.
      SB_Control = Scroller_FindScrollBar (Parent_window, SB_Type);

      // Если полоска есть - узнаем, в каком она состоянии.
      if (SB_Control != NULLHANDLE) Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
    }
  }

  // Если полоска была найдена:
  if (SB_Control != NULLHANDLE)
  {
    // Если она отключена - возврат.
    if (!Scroller.RTSettings.SB_State.sHilite) return;
    if (Scroller.RTSettings.SB_State.posFirst == 0 && Scroller.RTSettings.SB_State.posLast == 0) return;

    // Если движок достиг края полоски - возврат.
    if (Scan_code == SC_UP || Scan_code == SC_LEFT)
     if (Scroller.RTSettings.SB_State.posThumb == Scroller.RTSettings.SB_State.posFirst) return;

    if (Scan_code == SC_DOWN || Scan_code == SC_RIGHT)
     if (Scroller.RTSettings.SB_State.posThumb == Scroller.RTSettings.SB_State.posLast) return;

    // Узнаем способ передвижения изображения в окне.
    INT Scrolling_method = Scroller_QueryScrollingMethod (Target_window);

    // Посылаем полоске просмотра сообщение от клавиатуры или мыши.
    ULONG Message = 0; INT Direction = 0;
    if (Scan_code == SC_UP)   { Message = WM_VSCROLL; Direction = 1; }
    if (Scan_code == SC_DOWN) { Message = WM_VSCROLL; Direction = 0; }
    if (Scan_code == SC_LEFT) { Message = WM_HSCROLL; Direction = 0; }
    if (Scan_code == SC_RIGHT) { Message = WM_HSCROLL; Direction = 1; }

    if (Scrolling_method == SCROLLING_COMMON || Scrolling_method == SCROLLING_DISCRETE_SBCTL_KBD)
     Scroller_PostDiscreteKbdScrollMessage (SB_Control, Message, Direction, 1);

    if (Scrolling_method == SCROLLING_DISCRETE_SBCTL_MB)
     Scroller_PostDiscreteMBScrollMessage (SB_Control, Message, Direction, 1);
  }
  // А если полоски просмотра нет:
  else
  {
    // Составляем сообщение о том, что изображение надо подвинуть на одну строку.
    ULONG Message = 0; USHORT SB_Code = 0;
    if (Scan_code == SC_UP)   { Message = WM_VSCROLL; SB_Code = SB_LINEUP;   }
    if (Scan_code == SC_DOWN) { Message = WM_VSCROLL; SB_Code = SB_LINEDOWN; }
    if (Scan_code == SC_LEFT) { Message = WM_HSCROLL; SB_Code = SB_LINELEFT; }
    if (Scan_code == SC_RIGHT) { Message = WM_HSCROLL; SB_Code = SB_LINERIGHT; }

    // Посылаем его в окно.
    // Так как оно принимало сообщения от полосок просмотра, то скорее всего, оно сможет обработать и это сообщение.
    WinPostMsg (Target_window, Message, 0, MPFROM2SHORT (0, SB_Code));
  }

  // Возврат.
  return;
}

// ─── Начинает передвижение изображения с помощью мыши ───

// Selected_window - окно под указателем мыши, X и Y - расположение указателя мыши на экране.
VOID Scroller_BeginDragging (HWND Selected_window, INT X, INT Y)
{
  // Выбираем окно для передвижения изображения.
  HWND Target_window = Scroller_ChooseWindowFromScrollingList (Selected_window);

  // Если ни одно окно не выбрано - возврат.
  if (Target_window == NULL) return;

  // В некоторых окнах передвигать изображение не надо.
  if (!Scroller_PermissionForScrolling (Target_window)) return;

  // Узнаем способ передвижения изображения в окне.
  INT Dragging_method = Scroller_QueryScrollingMethod (Target_window);

  // Если в окно надо отправлять сообщения от полосок просмотра - находим их.
  if (Dragging_method == SCROLLING_COMMON ||
      Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
  {
    // Находим полоски в окне.
    Scroller.RTSettings.VSB_Control = NULLHANDLE;
    Scroller.RTSettings.HSB_Control = NULLHANDLE;

    for (INT VH_Count = 0; VH_Count < 2; VH_Count ++)
    {
      // Повторяем действие два раза, для вертикальной и горизонтальной полоски.
      BYTE SB_Type = SBS_VERT; if (VH_Count == 1) SB_Type = SBS_HORZ;
      HWND SB_Control = NULLHANDLE;

      // Пробуем найти полоску просмотра внутри выбранного окна, с учетом расположения того окна, над которым расположен указатель мыши.
      if (Selected_window == Target_window)
      {
        SB_Control = Scroller_FindScrollBar (Target_window, SB_Type);
      }
      else
      {
        SWP Selected_window_placement = {0}; WinQueryWindowPos (Selected_window, &Selected_window_placement);
        SB_Control = Scroller_FindScrollBar (Target_window, SB_Type, &Selected_window_placement);
      }

      // Если полоска есть - узнаем, в каком она состоянии.
      if (SB_Control != NULLHANDLE)
      {
        // Узнаем, в каком состоянии полоска.
        Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
      }
      // Если полоски нет - она может быть расположена рядом с окном.
      else
      {
        // Узнаем родительское окно.
        HWND Parent_window = WinQueryWindow (Target_window, QW_PARENT);

        // Если в родительском окне можно передвигать изображение - находим в нем полоску.
        if (Scroller_PermissionForScrolling (Parent_window))
        {
          // Ищем полоску в родительском окне, проверяя ее расположение.
          SWP Target_window_placement = {0}; WinQueryWindowPos (Target_window, &Target_window_placement);
          SB_Control = Scroller_FindScrollBar (Parent_window, SB_Type, &Target_window_placement);

          // Если полоска есть - узнаем, в каком она состоянии.
          if (SB_Control != NULLHANDLE) Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
        }
      }

      // Запоминаем полоску, если она была найдена.
      if (SB_Control != NULLHANDLE)
      {
        if (SB_Type == SBS_VERT) Scroller.RTSettings.VSB_Control = SB_Control;
        if (SB_Type == SBS_HORZ) Scroller.RTSettings.HSB_Control = SB_Control;
      }
    }

    // Если найдена хотя бы одна полоска:
    if (Scroller.RTSettings.VSB_Control != NULLHANDLE || Scroller.RTSettings.HSB_Control != NULLHANDLE)
    {
      // Если обе полоски отключены - возврат.
      Scroller_QueryScrollBarState (Scroller.RTSettings.VSB_Control, &Scroller.RTSettings.VSB_State);
      Scroller_QueryScrollBarState (Scroller.RTSettings.HSB_Control, &Scroller.RTSettings.HSB_State);

      if (!Scroller.RTSettings.VSB_State.sHilite && !Scroller.RTSettings.HSB_State.sHilite) return;
      if (Scroller.RTSettings.VSB_State.posFirst == 0 && Scroller.RTSettings.VSB_State.posLast == 0 &&
          Scroller.RTSettings.HSB_State.posFirst == 0 && Scroller.RTSettings.HSB_State.posLast == 0) return;

      // Запоминаем расположение движков полосок просмотра.
      Scroller.RTSettings.Start_VSB_position = Scroller.RTSettings.VSB_State.posThumb;
      Scroller.RTSettings.Start_HSB_position = Scroller.RTSettings.HSB_State.posThumb;

      // Запоминаем окно.
      Scroller.RTSettings.Target_window = Target_window;

      // Запоминаем способ передвижения изображения в окне.
      Scroller.RTSettings.Dragging_method = Dragging_method;

      // Запоминаем скорость передвижения изображения в окне.
      SCRLIST Record_from_list = {0}; Scroller_QueryScrollingVelocity (Target_window, &Record_from_list);
      Scroller.RTSettings.X_Velocity_DD = Record_from_list.X_Velocity_DD; Scroller.RTSettings.X_Velocity_D = Record_from_list.X_Velocity_D;
      Scroller.RTSettings.Y_Velocity_DD = Record_from_list.Y_Velocity_DD; Scroller.RTSettings.Y_Velocity_D = Record_from_list.Y_Velocity_D;
    }
    // А если ни одной полоски не найдено:
    else
    {
      // Запоминаем окно.
      Scroller.RTSettings.Target_window = Target_window;

      // Включаем в окне режим передвижения с помощью сообщений "WM_xSCROLL".
      // Так как оно принимало сообщения от полосок просмотра, то скорее всего, оно сможет обработать и это сообщение.
      Scroller.RTSettings.Dragging_method = SCROLLING_DISCRETE_SCROLLMSG;

      // Задаем скорость передвижения изображения в окне.
      Scroller.RTSettings.X_Velocity_DD = SCROLLER_DEF_SPEED_X; Scroller.RTSettings.X_Velocity_D = 1;
      Scroller.RTSettings.Y_Velocity_DD = SCROLLER_DEF_SPEED_Y; Scroller.RTSettings.Y_Velocity_D = 1;
    }
  }

  // Если в окно надо отправлять сообщения напрямую:
  if (Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
  {
    // Запоминаем окно.
    Scroller.RTSettings.Target_window = Target_window;
    if (Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW) Scroller.RTSettings.Target_window = WinQueryFocus (QueryDesktopWindow ());

    // Запоминаем способ передвижения изображения в окне.
    Scroller.RTSettings.Dragging_method = SCROLLING_DISCRETE_SCROLLMSG;

    // Запоминаем скорость передвижения изображения в окне.
    SCRLIST Record_from_list = {0}; Scroller_QueryScrollingVelocity (Target_window, &Record_from_list);
    Scroller.RTSettings.X_Velocity_DD = Record_from_list.X_Velocity_DD; Scroller.RTSettings.X_Velocity_D = Record_from_list.X_Velocity_D;
    Scroller.RTSettings.Y_Velocity_DD = Record_from_list.Y_Velocity_DD; Scroller.RTSettings.Y_Velocity_D = Record_from_list.Y_Velocity_D;
  }

  // Запоминаем положение указателя мыши.
  Scroller.RTSettings.Start_point.x = X;
  Scroller.RTSettings.Start_point.y = Y;
  Scroller.RTSettings.Previous_step_point.x = X;
  Scroller.RTSettings.Previous_step_point.y = Y;

  // Устанавливаем новый указатель мыши.
  if (Resources.Pointer_for_dragging != NULLHANDLE)
   WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

  // Запоминаем, что передвижение началось.
  Scroller.RTSettings.Dragging = 1;

  // Возврат.
  return;
}

// ─── Передвигает изображение в выбранную точку ───

// X и Y - расположение указателя мыши на экране.
VOID Scroller_DragImage (INT X, INT Y)
{
  // Указывает, что сообщение было послано.
  BYTE Sent = 0; HWND Owner_window = NULLHANDLE;

  // Передвигаем изображение сверху вниз.
  if (Y != Scroller.RTSettings.Previous_step_point.y)
  {
    // Рассчитываем новое положение движка полоски просмотра или направление передвижения изображения.
    INT New_position = -1; INT Lines_to_repeat = 1;

    // Если надо использовать полоски просмотра:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON ||
        Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
    {
      // Узнаем состояние полоски просмотра.
      if (WinIsWindow (WinQueryAnchorBlock (Scroller.RTSettings.VSB_Control), Scroller.RTSettings.VSB_Control))
       Scroller_QueryScrollBarState (Scroller.RTSettings.VSB_Control, &Scroller.RTSettings.VSB_State);

      // Если известна скорость и передвижение изображения возможно:
      if (Scroller.RTSettings.Y_Velocity_DD != 0) if (Scroller.RTSettings.Y_Velocity_D != 0)
       if (Scroller.RTSettings.VSB_State.posThumb >= Scroller.RTSettings.VSB_State.posFirst)
        if (Scroller.RTSettings.VSB_State.posThumb <= Scroller.RTSettings.VSB_State.posLast)
         if (!(Scroller.RTSettings.VSB_State.posFirst == 0 && Scroller.RTSettings.VSB_State.posLast == 0))
          if (Scroller.RTSettings.VSB_State.sHilite)
          {
            // Если задан обыкновенный способ передвижения:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON)
            {
              // Узнаем расстояние в точках от точки начала передвижения.
              INT Distance = abs (Scroller.RTSettings.Start_point.y - Y);

              // Если оно больше, чем наименьшее возможное расстояние:
              if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
              {
                // Рассчитываем новое расположение движка полоски просмотра.
                INT Lines = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance);

                New_position = Scroller.RTSettings.Start_VSB_position;
                if (Y > Scroller.RTSettings.Start_point.y) New_position += Lines;
                if (Y < Scroller.RTSettings.Start_point.y) New_position -= Lines;

                if (New_position < Scroller.RTSettings.VSB_State.posFirst) New_position = Scroller.RTSettings.VSB_State.posFirst;
                if (New_position > Scroller.RTSettings.VSB_State.posLast) New_position = Scroller.RTSettings.VSB_State.posLast;
                if (New_position == Scroller.RTSettings.VSB_State.posThumb) New_position = -1;
              }
            }

            // Если задан способ передвижения через отправку полоскам просмотра сообщений от клавиатуры или мыши:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
            {
              // Узнаем расстояние в точках от предыдущей точки.
              INT Distance = abs (Scroller.RTSettings.Previous_step_point.y - Y);

              // Если оно больше, чем наименьшее возможное расстояние - изображение надо передвинуть на один или несколько шагов вверх или вниз.
              if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
              {
                Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
                if (Scroller.RTSettings.Previous_step_point.y > Y) New_position = 1;
                else New_position = 0;
              }
            }
          }
    }

    // Если надо отправлять сообщения в окно напрямую:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
    {
      // Если известна скорость и передвижение изображения возможно:
      if (Scroller.RTSettings.Y_Velocity_DD != 0) if (Scroller.RTSettings.Y_Velocity_D != 0)
      {
        // Узнаем расстояние в точках от предыдущей точки.
        INT Distance = abs (Scroller.RTSettings.Previous_step_point.y - Y);

        // Если оно больше, чем наименьшее возможное расстояние - изображение надо передвинуть на один или несколько шагов вверх или вниз.
        if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
        {
          Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
          if (Scroller.RTSettings.Previous_step_point.y > Y) New_position = 1;
          else New_position = 0;
        }
      }
    }

    // Если было задано новое положение движка полоски просмотра и кнопка мыши все еще нажата:
    if (New_position != -1) if (MouseButtonIsPressed ())
    {
      // Посылаем сообщения.
      ULONG Message = WM_VSCROLL;
      switch (Scroller.RTSettings.Dragging_method)
      {
        case SCROLLING_COMMON:
         Scroller_PostScrollMessage (Scroller.RTSettings.VSB_Control, Message, New_position);
        break;

        case SCROLLING_DISCRETE_SBCTL_MB:
         Scroller_PostDiscreteMBScrollMessage (Scroller.RTSettings.VSB_Control, Message, New_position, Lines_to_repeat);
        break;

        case SCROLLING_DISCRETE_SBCTL_KBD:
         Scroller_PostDiscreteKbdScrollMessage (Scroller.RTSettings.VSB_Control, Message, New_position, Lines_to_repeat);
        break;

        case SCROLLING_DISCRETE_SCROLLMSG:
        case SCROLLING_DISCRETE_SCROLLMSG_IFW:
         Scroller_PostDirectScrollMessage (Scroller.RTSettings.Target_window, Message, New_position, Lines_to_repeat);
        break;
      }

      // Запоминаем, что сообщения были посланы.
      Sent = 1;
    }
  }

  // Передвигаем изображение слева направо.
  if (X != Scroller.RTSettings.Previous_step_point.x)
  {
    // Рассчитываем новое положение движка полоски просмотра или направление передвижения изображения.
    INT New_position = -1; INT Lines_to_repeat = 1;

    // Если надо использовать полоски просмотра:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON ||
        Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
    {
      // Узнаем состояние полоски просмотра.
      if (WinIsWindow (WinQueryAnchorBlock (Scroller.RTSettings.HSB_Control), Scroller.RTSettings.HSB_Control))
       Scroller_QueryScrollBarState (Scroller.RTSettings.HSB_Control, &Scroller.RTSettings.HSB_State);

      // Если известна скорость и передвижение изображения возможно:
      if (Scroller.RTSettings.X_Velocity_DD != 0) if (Scroller.RTSettings.X_Velocity_D != 0)
       if (Scroller.RTSettings.HSB_State.posThumb >= Scroller.RTSettings.HSB_State.posFirst)
        if (Scroller.RTSettings.HSB_State.posThumb <= Scroller.RTSettings.HSB_State.posLast)
         if (!(Scroller.RTSettings.HSB_State.posFirst == 0 && Scroller.RTSettings.HSB_State.posLast == 0))
          if (Scroller.RTSettings.HSB_State.sHilite)
          {
            // Если задан обыкновенный способ передвижения:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON)
            {
              // Узнаем расстояние в точках от точки начала передвижения.
              INT Distance = abs (Scroller.RTSettings.Start_point.x - X);

              // Если оно больше, чем наименьшее возможное расстояние:
              if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
              {
                // Рассчитываем новое расположение движка полоски просмотра.
                INT Lines = DivideDivideRL (Scroller.RTSettings.X_Velocity_DD, Scroller.RTSettings.X_Velocity_D, Distance);

                New_position = Scroller.RTSettings.Start_HSB_position;
                if (X > Scroller.RTSettings.Start_point.x) New_position -= Lines;
                if (X < Scroller.RTSettings.Start_point.x) New_position += Lines;

                if (New_position < Scroller.RTSettings.HSB_State.posFirst) New_position = Scroller.RTSettings.HSB_State.posFirst;
                if (New_position > Scroller.RTSettings.HSB_State.posLast) New_position = Scroller.RTSettings.HSB_State.posLast;
                if (New_position == Scroller.RTSettings.HSB_State.posThumb) New_position = -1;
              }
            }

            // Если задан способ передвижения через отправку полоскам просмотра сообщений от клавиатуры:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
            {
              // Узнаем расстояние в точках от предыдущей точки.
              INT Distance = abs (Scroller.RTSettings.Previous_step_point.x - X);

              // Если оно больше, чем наименьшее возможное расстояние - изображение надо передвинуть на один или несколько шагов вверх или вниз.
              if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
              {
                Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
                if (Scroller.RTSettings.Previous_step_point.x > X) New_position = 1;
                else New_position = 0;
              }
            }
          }
    }

    // Если надо отправлять сообщения в окно напрямую:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
    {
      // Если известна скорость и передвижение изображения возможно:
      if (Scroller.RTSettings.X_Velocity_DD != 0) if (Scroller.RTSettings.X_Velocity_D != 0)
      {
        // Узнаем расстояние в точках от предыдущей точки.
        INT Distance = abs (Scroller.RTSettings.Previous_step_point.x - X);

        // Если оно больше, чем наименьшее возможное расстояние - изображение надо передвинуть на один или несколько шагов вверх или вниз.
        if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
        {
          Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
          if (Scroller.RTSettings.Previous_step_point.x > X) New_position = 1;
          else New_position = 0;
        }
      }
    }

    // Если было задано новое положение движка полоски просмотра и кнопка мыши все еще нажата:
    if (New_position != -1) if (MouseButtonIsPressed ())
    {
      // Посылаем сообщения.
      ULONG Message = WM_HSCROLL;
      switch (Scroller.RTSettings.Dragging_method)
      {
        case SCROLLING_COMMON:
         Scroller_PostScrollMessage (Scroller.RTSettings.HSB_Control, Message, New_position);
        break;

        case SCROLLING_DISCRETE_SBCTL_MB:
         Scroller_PostDiscreteMBScrollMessage (Scroller.RTSettings.HSB_Control, Message, New_position, Lines_to_repeat);
        break;

        case SCROLLING_DISCRETE_SBCTL_KBD:
         Scroller_PostDiscreteKbdScrollMessage (Scroller.RTSettings.HSB_Control, Message, New_position, Lines_to_repeat);
        break;

        case SCROLLING_DISCRETE_SCROLLMSG:
        case SCROLLING_DISCRETE_SCROLLMSG_IFW:
         Scroller_PostDirectScrollMessage (Scroller.RTSettings.Target_window, Message, New_position, Lines_to_repeat);
        break;
      }

      // Запоминаем, что сообщения были посланы.
      Sent = 1;
    }
  }

  // Если сообщения были посланы, то:
  if (Sent)
  {
    // Запоминаем новое положение указателя мыши.
    Scroller.RTSettings.Previous_step_point.x = X;
    Scroller.RTSettings.Previous_step_point.y = Y;

    // Устанавливаем новый указатель мыши.
    if (Resources.Pointer_for_dragging != NULLHANDLE)
     WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

    // При обработке сообщения окно может установить свой указатель. Посылаем в очередь
    // окна сообщение WM_MARK - когда оно будет получено, указатель можно будет заменить.
    if (Resources.Pointer_for_dragging != NULLHANDLE)
    {
      HMQ Message_queue = WinQueryWindowULong (Owner_window, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_SET_POINTER, (MPARAM) NULLHANDLE);
    }
  }

  // Возврат.
  return;
}

// ─── Завершает передвижение изображения с помощью мыши ───

VOID Scroller_EndDragging (VOID)
{
  // Завершаем передвижение.
  Scroller_TerminateDragging ();
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Scroller_ScrollerMessageProcessing (PQMSG Message)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.Scroller->Priority = MAKELONG (Class, Delta);
  }

  // Передвигаем изображение при нажатии клавиш со стрелками.
  if (Message->msg == SM_SC_LINE)
  {
    // Узнаем окно и нажатую клавишу.
    HWND Window = (HWND) Message->mp1;
    INT Scan_code = (INT) Message->mp2;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

    // Передвигаем изображение.
    Scroller_ScrollImage (Window, Scan_code);
  }

  // Начинаем передвижение изображения с помощью мыши.
  if (Message->msg == SM_SC_BEGIN)
  {
    // Узнаем окно.
    HWND Window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

    // Если не нажата клавиша Ctrl - делаем окно выбранным.
    if (!CtrlIsPressed ()) MoveWindowAbove (QueryFrameWindow (Window));

    // Узнаем расположение указателя мыши.
    POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);

    // Начинаем передвижение.
    Scroller_BeginDragging (Window, Pointer.x, Pointer.y);
  }

  // Передвигаем изображение.
  if (Message->msg == SM_SC_DRAG)
   if (Scroller.RTSettings.Dragging)
    if (MouseButtonIsPressed ())
    {
      // Узнаем расположение указателя мыши.
      POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);

      // Если указатель на том же месте - возврат.
      if (Pointer.x == Scroller.RTSettings.Previous_step_point.x)
       if (Pointer.y == Scroller.RTSettings.Previous_step_point.y)
        return;

      // Передвигаем изображение.
      Scroller_DragImage (Pointer.x, Pointer.y);
    }

  // Завершаем передвижение.
  if (Message->msg == SM_SC_END) Scroller_EndDragging ();

  // Сохраняем настройки.
  if (Message->msg == SM_WRITE_SETTINGS) Scroller_StartWaiterToWriteSettings ();
  if (Message->msg == SM_WAITING_COMPLETE) Scroller_WriteSettingsAfterWaiting ();

  // Возврат.
  return;
}

// ─── Поток для передвижения изображения в окнах ───

VOID Scroller_ScrollerThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Scroller->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.Scroller->Message_queue == NULLHANDLE)
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
    Scroller_ScrollerMessageProcessing (&Message);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
