
// ─── Проверяет, надо ли украшать рамки ───

BYTE Painter_FrameDrawingIsRequired (VOID)
{
  // Проверяем настройки.
  if (!Painter.Settings.Draw_normal_frames)
   if (!Painter.Settings.Draw_const_frames)
    if (!Painter.Settings.Draw_point_frames)
     if (!Painter.Settings.Draw_flat_frames) return 0;

  // Возврат.
  return 1;
}

// ─── Распознает вид заголовка ───

BYTE Painter_DifferentTitleBarImagesAreRequired (VOID)
{
  // Возврат.
  return 0;
}

// ─── Распознает вид заголовка ───

// Window_is_active - выбрано ли окно.
BYTE Painter_NeonTitleBarIsRequired (BYTE Window_is_active = 1)
{
  // Проверяем тему для рамок и смотрим, выбрано ли окно.
  if (Window_is_active)
  {
    if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX) return 1;
    if (Painter.Settings.Theme == PAINTER_THEME_BLUE_LION) return 1;
    if (Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Распознает вид заголовка ───

// Window_is_active - выбрано ли окно.
BYTE Painter_GlassTitleBarIsRequired (BYTE Window_is_active = 1)
{
  // Проверяем тему для рамок и смотрим, выбрано ли окно.
  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB) return 1;

  if (Window_is_active)
  {
    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Распознает вид заголовка ───

// Window_is_active - выбрано ли окно.
BYTE Painter_TitleBarIsGrayed (BYTE Window_is_active = 1)
{
  // Проверяем тему для рамок.
  if (!Painter_NeonTitleBarIsRequired (Window_is_active))
   if (!Painter_GlassTitleBarIsRequired (Window_is_active))
    return 1;

  // Возврат.
  return 0;
}

// ─── Возвращает отступ для изображения от края кнопок ───

INT Painter_GetButtonPixelMargin (VOID)
{
  // Выбираем отступ от края заголовка.
  INT Pixel_margin = 0;

  if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Pixel_margin = 1;

  // Возврат.
  return Pixel_margin;
}

// ─── Возвращает отступ для изображения от края заголовка ───

// Theme - тема для рисования, Frame_window - окно рамки, Window_is_active - выбрано ли окно.
INT Painter_GetTitleBarPixelMargin (INT Theme, HWND Frame_window, BYTE Window_is_active)
{
  // Выбираем отступ от края заголовка.
  INT Pixel_margin = 0;

  switch (Painter.Settings.Theme)
  {
    case PAINTER_THEME_CLASSIC_GRAY:
    case PAINTER_THEME_CLASSIC_RGB:
    {
      if (!Window_is_active)
      {
        if (Painter_PermissionForCompleteDrawing (Frame_window)) Pixel_margin = 1;
        else Pixel_margin = 2;
      }
    }
    break;

    case PAINTER_THEME_PHOENIX:
    case PAINTER_THEME_WHITE_SNOW:
    {
      if (Window_is_active) Pixel_margin = 1;
      else Pixel_margin = 2;
    }
    break;
  }

  // Возврат.
  return Pixel_margin;
}

// ─── Сбрасывает узор для заполнения заголовка ───

VOID Painter_DeleteTitleBarPattern (VOID)
{
  // Сбрасываем последний использованный узор.
  if (Painter.RTSettings.Pattern != NULLHANDLE)
  {
    GpiDeleteBitmap (Painter.RTSettings.Pattern);
    Painter.RTSettings.Pattern = NULLHANDLE ;
  }

  // Сбрасываем его имя.
  Painter.RTSettings.Pattern_name[0] = 0;

  // Возврат.
  return;
}

// ─── Рисует изображения для заполнения заголовка ───

// Все переменные - внешние.
VOID Painter_PrepareTitleBarImage (HPS Memory_space, RECT Rectangle, BYTE Window_is_active)
{
  // Узнаем имя узора.
  PCHAR File_name = Painter.Settings.TitleBar_pattern;
  CHAR Name[SIZE_OF_NAME] = ""; strcpy (Name, FindNameInPath (File_name));

  // Узнаем, надо ли загружать узор с диска, или можно взять готовый.
  BYTE Use_last_loaded_pattern = 0;

  if (Painter.RTSettings.Pattern != NULLHANDLE)
   if (strc (Painter.RTSettings.Pattern_name, Name))
    Use_last_loaded_pattern = 1;

  // Если надо загружать новый узор
  if (!Use_last_loaded_pattern)
  {
    // Удаляем предыдущий узор.
    Painter_DeleteTitleBarPattern ();

    // Загружаем узор с диска.
    LoadBitmap (Enhancer.Application, File_name, &Painter.RTSettings.Pattern, &Painter.RTSettings.Pattern_width, &Painter.RTSettings.Pattern_height);

    // Если узора нет - возврат.
    if (Painter.RTSettings.Pattern == NULLHANDLE) return;

    // Запоминаем его имя.
    strcpy (Painter.RTSettings.Pattern_name, Name);
  }

  // Заполняем изображение в памяти.
  for (INT X_Count = 0; X_Count < Rectangle.xRight; X_Count += Painter.RTSettings.Pattern_width)
  {
    POINT Point = { X_Count, 0 };
    WinDrawBitmap (Memory_space, Painter.RTSettings.Pattern, NULL, &Point, 0, 0, DBM_NORMAL);
  }

  // Возврат.
  return;
}

// ─── Сбрасывает изображения для заполнения заголовка ───

VOID Painter_DeleteTitleBarImages (VOID)
{
  // Удаляем изображения.
  if (Painter.RTSettings.AT_Bitmap != NULLHANDLE) { GpiDeleteBitmap (Painter.RTSettings.AT_Bitmap); Painter.RTSettings.AT_Bitmap = NULLHANDLE; }
  if (Painter.RTSettings.IT_Bitmap != NULLHANDLE) { GpiDeleteBitmap (Painter.RTSettings.IT_Bitmap); Painter.RTSettings.IT_Bitmap = NULLHANDLE; }

  Painter.RTSettings.AT_Bitmap_width = Painter.RTSettings.AT_Bitmap_height = -1;

  // Возврат.
  return;
}

// ─── Создает изображения для заполнения заголовка ───

VOID Painter_CreateTitleBarImages (INT Required_width = 0)
{
  // Удаляем предыдущие изображения.
  Painter_DeleteTitleBarImages ();

  // Если неоновые заголовки рисовать не надо - возврат.
  if (!Painter_NeonTitleBarIsRequired ()) return;

  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Узнаем высоту заголовка окна.
  INT TitleBar_height = WinQuerySysValue (Desktop, SV_CYMINMAXBUTTON);

  // Задаем размеры изображений.
  INT Width = Required_width;
  if (!Width) Width = WinQuerySysValue (QueryDesktopWindow (), SV_CXSCREEN);

  INT AT_Height = TitleBar_height - Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, NULLHANDLE, 1);
  INT IT_Height = TitleBar_height - Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, NULLHANDLE, 0);

  // Создаем пространство отображения в памяти.
  HPS Drawing_memory_space = CreatePresentationSpace (Enhancer.Application);

  // Создаем изображения для заполнения заголовка.
  Painter.RTSettings.AT_Bitmap = CreateBitmap (Drawing_memory_space, Width, AT_Height);
  Painter.RTSettings.IT_Bitmap = CreateBitmap (Drawing_memory_space, Width, IT_Height);

  // Заполняем изображения для заголовков окон.
  for (INT Images_count = 0; Images_count < 2; Images_count ++)
  {
    // Задаем прямоугольник для рисования.
    INT Height = AT_Height; if (Images_count == 1) INT Height = IT_Height;
    RECT Rectangle = { 0, 0, Width - 1, Height - 1 };

    // Выбираем изображение.
    if (Images_count == 0)
    {
      GpiSetBitmap (Drawing_memory_space, Painter.RTSettings.AT_Bitmap);
      Painter_PrepareTitleBarImage (Drawing_memory_space, Rectangle, 1);
      GpiSetBitmap (Drawing_memory_space, NULLHANDLE);
    }
    else
    {
      GpiSetBitmap (Drawing_memory_space, Painter.RTSettings.IT_Bitmap);
      Painter_PrepareTitleBarImage (Drawing_memory_space, Rectangle, 0);
      GpiSetBitmap (Drawing_memory_space, NULLHANDLE);
    }
  }

  // Удаляем пространство отображения.
  GpiDestroyPS (Drawing_memory_space); Drawing_memory_space = NULLHANDLE;

  // Запоминаем размеры изображений.
  Painter.RTSettings.AT_Bitmap_width = Width; Painter.RTSettings.AT_Bitmap_height = AT_Height;

  // Возврат.
  return;
}

// ─── Узнает размер и расположение окна рамки ───

// Все переменные - внешние.
VOID Painter_QueryFrameRectangeAndPlacement (HWND Frame_window, PRECT Rectangle, PSWP Placement)
{
  // Узнаем размер окна.
  WinQueryWindowRect (Frame_window, Rectangle);

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle->yTop --; Rectangle->xRight --;

  // Узнаем расположение окна.
  WinQueryWindowPos (Frame_window, Placement);

  // Возврат.
  return;
}

// ─── Проверяет, не изменился ли размер окна рамки ───

// Frame_window - окно рамки, Frame_rectangle - размер окна, Frame_placement - расположение окна.
// Возвращаемое значение: 1 если размер рамки изменен, иначе 0.
BYTE Painter_FrameRectangleIsChanged (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Проверяем, существует ли окно.
  if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return 1;

  // Проверяем, видимо ли окно.
  if (!WinIsWindowVisible (Frame_window)) return 1;

  // Проверяем, не изменился ли размер окна.
  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  if (Frame_rectangle != NULL)
  {
    RECT Current_rectangle = {0};
    if (!WinQueryWindowRect (Frame_window, &Current_rectangle)) return 1;
    Current_rectangle.yTop --; Current_rectangle.xRight --;

    if (Current_rectangle.xRight != Frame_rectangle->xRight ||
        Current_rectangle.yTop != Frame_rectangle->yTop) return 1;
  }

  // Проверяем, не изменилось ли расположение окна.
  if (Frame_placement != NULL)
  {
    SWP Current_placement = {0};
    if (!WinQueryWindowPos (Frame_window, &Current_placement)) return 1;

    if (Current_placement.x != Frame_placement->x ||
        Current_placement.y != Frame_placement->y) return 1;
  }

  // Возврат.
  return 0;
}

// ─── Проверяет, нет ли ошибок, связанных с SMP ───

// Все переменные - внешние
BYTE Painter_SMPError (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Внутренняя проверка параметров.
  if (!Frame_window || !Frame_rectangle) { Painter.Settings.Draw_frames = 0; return 1; }

  // Проверяем размер окна рамки.
  if (Painter_FrameRectangleIsChanged (Frame_window, Frame_rectangle, Frame_placement)) return 1;

  // Возврат.
  return 0;
}

// ─── Закрашивает свободное пространство рамки ───

// Presentation_space - пространство отображения, Frame_* - окно рамки, его размер и расположение.
// Wall - граница закрашивания, Window_is_active - выбрано ли окно.
VOID Painter_FillFrameSpace (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, LONG Color, INT Wall, BYTE Window_is_active)
{
  // Закрашиваем рамку от 2 до определенной границы.
  GpiSetColor (Presentation_space, Color);

  for (INT Offset = 2; Offset < Wall; Offset ++)
  {
    // Рисуем линии.
    POINT Point = { Offset, Offset };           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Frame_rectangle->yTop - Offset;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Offset;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Возврат.
  return;
}

// ─── Рисует внешнюю часть рамки ───

// Presentation_space - пространство отображения, Frame_* - окно рамки, его размер и расположение..
VOID Painter_DrawExternalFrame (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Рисуем светлую часть внешней рамки.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = { 1, 1 };                if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем темную часть внешней рамки.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки внешней рамки.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Frame_rectangle->yTop - 1;
  Point.x = Frame_rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = 1; Point.x = 1;              if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Возврат.
  return;
}

// ─── Рисует тень для рамки ───

// Presentation_space - пространство отображения, Frame_* - окно рамки, его размер и расположение.
VOID Painter_DrawFrameShadow (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Рисуем темную часть тени.
  GpiSetColor (Presentation_space, CLR_BLACK);

  POINT Point = {0};                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть тени.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Возврат.
  return;
}

// ─── Рисует рамку для плоского окна ───

// Все переменные - внешние.
VOID Painter_DrawFlatFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // Узнаем ширину рамки окна.
  INT Const_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Const_frame);
  if (!Const_frame) Const_frame = FrameWidth (Frame_window);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Frame_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем тень для рамки.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Рисуем внешнюю часть рамки.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Рисуем темную часть внутренней рамки.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  INT Offset = Const_frame - 1;
  POINT Point = { Offset - 1, Offset - 1 };         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - Offset + 1;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - Offset + 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  Point.x = Frame_rectangle->xRight - Offset;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Offset;                                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Offset;                                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть внутренней рамки.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = Offset; Point.x = Offset;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - Offset;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - Offset;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  Point.x = Frame_rectangle->xRight - Offset + 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Offset - 1;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Offset - 1;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Закрашиваем свободное пространство.
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, SYSCLR_DIALOGBACKGROUND, Offset - 1, Window_is_active);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Frame_rectangle->yTop - Offset;
  Point.x = Frame_rectangle->xRight - Offset;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Offset; Point.x = Offset;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Frame_rectangle->yTop - Offset + 1;
  Point.x = Frame_rectangle->xRight - Offset + 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Offset - 1; Point.x = Offset - 1;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Рисует рамку для окна постоянного размера ───

// Все переменные - внешние.
VOID Painter_DrawConstFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // Узнаем ширину рамки окна.
  INT Const_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Const_frame);
  if (!Const_frame) Const_frame = FrameWidth (Frame_window);

  // Узнаем окно заголовка и его размер.
  HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Frame_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем тень для рамки.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Рисуем внешнюю часть рамки.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Закрашиваем свободное пространство.
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, SYSCLR_DIALOGBACKGROUND, Const_frame, Window_is_active);

  // Узнаем, надо ли рисовать внутреннюю рамку.
  BYTE Draw_inner_frame = Painter.Settings.Draw_volume_lines;

  if (Draw_inner_frame)
  {
    // Если в окне есть меню - рисовать рамку не надо.
    if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_inner_frame = 0;

    // Если окно заголовка не показано - рисовать рамку не надо.
    if (!WindowIsPresent (TitleBar_window)) Draw_inner_frame = 0;
  }

  // Рисуем рамку внутри окна.
  if (Draw_inner_frame)
  {
    // Вычисляем расположение точек.
    INT Width = Frame_rectangle->xRight;
    INT Height = Frame_rectangle->yTop;
    INT Title = TitleBar_rectangle.yTop;
    INT Offset = Const_frame - 1;

    // Рисуем темную часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = { Offset, Height - Offset - Title }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Height - Offset;                         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Width - Offset;                          if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем светлую часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = Height - Offset - Title - 1;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки внешней рамки.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Height - Offset; Point.x = Width - Offset;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

    // Закрашиваем свободное пространство цветом окна.
    GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

    Point.y = Height - Offset - Title - 2;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Height - Offset - Title - 2;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Рисует рамку в 1 точку ───

// Все переменные - внешние.
VOID Painter_DrawPointFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Узнаем размер экрана.
  INT Y_Screen = WinQuerySysValue (QueryDesktopWindow (), SV_CYSCREEN);

  // Если окно занимает весь экран, то это заставка - возврат.
  if (Frame_rectangle->yTop >= Y_Screen - 1) return;

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Frame_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = {0};                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop; Point.x = Frame_rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Рисует рамку для обычного окна ───

// Все переменные - внешние.
VOID Painter_DrawNormalFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // Узнаем ширину рамки окна.
  INT Normal_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Normal_frame);
  if (!Normal_frame) Normal_frame = FrameWidth (Frame_window);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Frame_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем тень для рамки.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Рисуем внешнюю часть рамки.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // Рисуем внутреннюю часть рамки.
  INT Offset = Normal_frame;

  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_GRAY || Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB)
  {
    // Уменьшаем отступ.
    Offset --;

    // Рисуем темную часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = { Offset, Offset };           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Frame_rectangle->yTop - Offset;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем светлую часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки внутренней рамки.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    Point.y = Frame_rectangle->yTop - Offset;
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Offset; Point.x = Offset;         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // Закрашиваем свободное пространство.
  LONG Color = SYSCLR_ACTIVEBORDER; if (!Window_is_active) Color = SYSCLR_INACTIVEBORDER;
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, Color, Offset, Window_is_active);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Рисует рамку для окна ───

// *_window - окна рамки и заголовка, *_rectangle и *_placement - их размеры. Frame_type - вид рамки, Window_is_active - выбрано ли окно.
VOID Painter_DrawFrameRectangle (HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // Если рамки украшать не надо - возврат.
  if (!Painter_FrameDrawingIsRequired ()) return;

  // Рисуем рамку.
  switch (Frame_type)
  {
    case FT_NORMAL:
     if (Painter.Settings.Draw_normal_frames) Painter_DrawNormalFrame (Frame_window, Frame_rectangle, Frame_placement, Window_is_active);
    break;

    case FT_POINT:
     if (Painter.Settings.Draw_point_frames) Painter_DrawPointFrame (Frame_window, Frame_rectangle, Frame_placement);
    break;

    case FT_CONST:
     if (Painter.Settings.Draw_const_frames) Painter_DrawConstFrame (Frame_window, Frame_rectangle, Frame_placement, Window_is_active);
    break;

    case FT_FLAT:
     if (Painter.Settings.Draw_flat_frames) Painter_DrawFlatFrame (Frame_window, Frame_rectangle, Frame_placement, Window_is_active);
    break;
  }

  // Возврат.
  return;
}

// ─── Подчеркивает объем меню окна ───

// Все переменные - внешние.
VOID Painter_DrawWindowMenu (HWND Menu_window, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Если окно не показано - возврат.
  if (!WindowIsPresent (Menu_window)) return;

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Menu_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Menu_window, &Rectangle);

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle.yTop --; Rectangle.xRight --;

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = { 0, 1 };     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle.yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки. Так как есть разделяющая линия, то рисуем только уголок справа вверху.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Rectangle.yTop; Point.x = Rectangle.xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Рисуем разделяющую линию.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = 0; Point.x = 0;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Задает прямоугольники для кнопок ───

// Переменные - окно рамки и прямоугольники. Возвращаемое значение - размер кнопки.
INT Painter_CalculateButtonRectangles (HWND Frame_window, PRECT Rectangle, HWND TitleBar_window, PRECT TitleBar_rectangle, PRECT Max_button, PRECT Min_button, PRECT Rollup_button, PRECT Close_button, PRECT All_buttons)
{
  // Узнаем состояние кнопок в окне.
  LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

  // Задаем отступ от края окна, размер, а также верхние и нижние точки прямоугольников.
  INT Size = 0; INT Top = 0; INT Bottom = 0;
  INT Offset = 0; FindProperty (Frame_window, PRP_BORDER, &Offset);
  if (!Offset) Offset = FrameWidth (Frame_window);

  // Узнаем окно заголовка, если оно не было известно заранее.
  if (TitleBar_window == NULLHANDLE) TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

  // Если оно есть - смотрим на его размер. Иначе - используем настройки оконной оболочки.
  if (!Size && TitleBar_window != NULLHANDLE && TitleBar_rectangle != NULL)
  {
    Size = TitleBar_rectangle->yTop - 1;
  }
  if (!Size && TitleBar_window != NULLHANDLE && TitleBar_rectangle == NULL)
  {
    RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle); Size = Rectangle.yTop - 1;
  }
  if (!Size)
  {
    Size = WinQuerySysValue (QueryDesktopWindow (), SV_CYMINMAXBUTTON) - 1;
  }

  // Задаем расположение точек.
  Top = Rectangle->yTop - Offset; Bottom = Top - Size;

  // Подготавливаем четыре прямоугольника.
  RECT Rect[4];
  RECT Rect_0 = { Rectangle->xRight - Offset - Size, Bottom, Rectangle->xRight - Offset, Top };
  RECT Rect_1 = { Rect_0.xLeft - Size - 1,           Bottom, Rect_0.xRight - Size - 1,   Top };
  RECT Rect_2 = { Rect_1.xLeft - Size - 1,           Bottom, Rect_1.xRight - Size - 1,   Top };
  RECT Rect_3 = { Rect_2.xLeft - Size - 1,           Bottom, Rect_2.xRight - Size - 1,   Top };
  memcpy (&Rect[0], &Rect_0, sizeof (RECT));
  memcpy (&Rect[1], &Rect_1, sizeof (RECT));
  memcpy (&Rect[2], &Rect_2, sizeof (RECT));
  memcpy (&Rect[3], &Rect_3, sizeof (RECT));

  // Подготавливаем общий прямоугольник.
  RECT Border = { 0, Bottom, Rect[0].xRight, Top };

  // Если кнопок нет - надо задать только общий прямоугольник.
  if (Buttons == NO_ACTION)
  {
    // Прямоугольник ничего не содержит.
    Border.xLeft = Border.xRight + 1; Border.xRight ++;
    if (FrameType (Frame_window) == FT_NOFRAME) Border.xLeft ++;

    if (All_buttons != NULL) memcpy (All_buttons, &Border, sizeof (RECT));

    // Возврат.
    return Size;
  }

  // Некоторые прямоугольники будут использованы для кнопок.
  INT Quantity = 0;

  // Смотрим, где надо рисовать кнопку закрытия окна.
  BYTE Close_button_rightward = 0; if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Close_button_rightward = 1;

  // Если кнопку закрытия надо рисовать слева, то:
  if (!Close_button_rightward)
  {
    if (Buttons & MAXIMIZE_ACTION || Buttons & RESTORE_ACTION)
    {
      if (Max_button != NULL) memcpy (Max_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & MINIMIZE_ACTION || Buttons & HIDE_ACTION)
    {
      if (Min_button != NULL) memcpy (Min_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & ROLLUP_ACTION)
    {
      if (Rollup_button != NULL) memcpy (Rollup_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & CLOSE_ACTION)
    {
      if (Close_button != NULL) memcpy (Close_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }
  }
  // А если ее надо рисовать справа, то:
  else
  {
    if (Buttons & CLOSE_ACTION)
    {
      if (Close_button != NULL) memcpy (Close_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & MAXIMIZE_ACTION || Buttons & RESTORE_ACTION)
    {
      if (Max_button != NULL) memcpy (Max_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & MINIMIZE_ACTION || Buttons & HIDE_ACTION)
    {
      if (Min_button != NULL) memcpy (Min_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }

    if (Buttons & ROLLUP_ACTION)
    {
      if (Rollup_button != NULL) memcpy (Rollup_button, &Rect[Quantity], sizeof (RECT));
      Quantity ++;
    }
  }

  // Задаем прямоугольник для всех кнопок.
  switch (Quantity)
  {
    case 1: Border.xLeft = Rect[0].xLeft; break;
    case 2: Border.xLeft = Rect[1].xLeft; break;
    case 3: Border.xLeft = Rect[2].xLeft; break;
    case 4: Border.xLeft = Rect[3].xLeft; break;
  }

  if (All_buttons != NULL) memcpy (All_buttons, &Border, sizeof (RECT));

  // Возврат.
  return Size;
}

// ─── Рисует кнопки в правом верхнем углу окна ───

// Все переменные - внешние.
VOID Painter_DrawButtons (HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, HWND TitleBar_window)
{
  // Если окно заголовка не показано - возврат.
  if (!WindowIsPresent (TitleBar_window)) return;

  // Узнаем размер окна заголовка
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // Узнаем прямоугольники для кнопок.
  RECT Max_button = {0}; RECT Min_button = {0}; RECT Rollup_button = {0};
  RECT Close_button = {0}; RECT All_buttons = {0};
  INT Size = Painter_CalculateButtonRectangles (Frame_window, Frame_rectangle, TitleBar_window, &TitleBar_rectangle, &Max_button, &Min_button, &Rollup_button, &Close_button, &All_buttons);

  // Если кнопок нет - возврат.
  if (All_buttons.xRight - All_buttons.xLeft < 3) return;
  if (All_buttons.yTop - All_buttons.yBottom < 3) return;

  // Узнаем, как выглядит рамка окна, если это требуется.
  if (Frame_type == FT_UNKNOWN) Frame_type = FrameType (Frame_window);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Frame_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Узнаем отступ от края кнопки.
  INT Pixel_margin = Painter_GetButtonPixelMargin ();

  // Узнаем, надо ли рисовать тень, если кнопка нажата.
  BYTE Draw_lines = 1;

  if (Pixel_margin == 0)
  {
    // Если у окна рамка в одну точку - не рисуем тень.
    if (Painter.RTSettings.Selected_button)
     if (Frame_type == FT_POINT) Draw_lines = 0;

    // Если у окна рамка постоянного размера:
    if (Painter.RTSettings.Selected_button)
     if (Frame_type == FT_CONST)
     {
       // Если у окна нет внутренней рамки - не рисуем тень.
       if (!Painter.Settings.Draw_volume_lines) Draw_lines = 0;
       // Если в окне есть меню - не рисуем тень.
       else if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_lines = 0;
     }
  }

  // Подготавливаем прямоугольники для кнопок. Подчеркиваем их объем, рисуем тени.
  for (INT Count = 0; Count < 4; Count ++)
  {
    // Выбираем прямоугольник.
    PRECT Current_button = NULL; LONG Button_is_pressed = 0;
    switch (Count)
    {
      case 0:
       if (!Max_button.yTop) break;
       Current_button = &Max_button;
       if (Frame_window == Painter.RTSettings.Selected_window)
        if (Painter.RTSettings.Selected_button == MAXIMIZE_ACTION || Painter.RTSettings.Selected_button == RESTORE_ACTION) Button_is_pressed = 1;
      break;

      case 1:
       if (!Min_button.yTop) break;
       Current_button = &Min_button;
       if (Frame_window == Painter.RTSettings.Selected_window)
        if (Painter.RTSettings.Selected_button == MINIMIZE_ACTION || Painter.RTSettings.Selected_button == HIDE_ACTION) Button_is_pressed = 1;
      break;

      case 2:
       if (!Rollup_button.yTop) break;
       Current_button = &Rollup_button;
       if (Frame_window == Painter.RTSettings.Selected_window)
        if (Painter.RTSettings.Selected_button == ROLLUP_ACTION) Button_is_pressed = 1;
      break;

      case 3:
       if (!Close_button.yTop) break;
       Current_button = &Close_button;
       if (Frame_window == Painter.RTSettings.Selected_window)
        if (Painter.RTSettings.Selected_button == CLOSE_ACTION) Button_is_pressed = 1;
      break;
    }

    // Если кнопку рисовать не надо - продолжаем перебор.
    if (Current_button == NULL) continue;

    // Рисуем светлую часть рамки, или тень, если кнопка нажата.
    POINT Point = { Current_button->xLeft + Pixel_margin, Current_button->yBottom + Pixel_margin };

    LONG Color = CLR_WHITE;
    if (Button_is_pressed)
    {
      if (Draw_lines) Color = CLR_DARKGRAY;
      else Color = SYSCLR_BUTTONMIDDLE;
    }
    GpiSetColor (Presentation_space, Color);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Current_button->yTop - Pixel_margin;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Current_button->xRight - Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем темную часть рамки или закрашиваем свободное пространство.
    if (!Button_is_pressed) GpiSetColor (Presentation_space, CLR_DARKGRAY);
    else GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE);

    Point.y = Current_button->yBottom + Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Current_button->xLeft + Pixel_margin;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки.
    Color = SYSCLR_BUTTONMIDDLE;
    if (Button_is_pressed) if (Draw_lines) Color = CLR_DARKGRAY;
    GpiSetColor (Presentation_space, Color);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Current_button->yTop - Pixel_margin;
    Point.x = Current_button->xRight - Pixel_margin;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

    // Рисуем внешнюю рамку.
    if (Pixel_margin != 0)
    {
      // Рисуем светлую часть внешней рамки.
      GpiSetColor (Presentation_space, CLR_WHITE);

      Point.y = Current_button->yBottom;
      Point.x = Current_button->xLeft;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Current_button->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.y = Current_button->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

      // Рисуем темную часть внешней рамки.
      GpiSetColor (Presentation_space, CLR_DARKGRAY);

      Point.x = Current_button->xLeft;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.y = Current_button->yBottom; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

      // Рисуем уголки.
      GpiSetColor (Presentation_space, CLR_PALEGRAY);

      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
      Point.y = Current_button->yTop; Point.x = Current_button->xRight;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    }

    // Если кнопка нажата - сдвигаем изображение вниз и вправо.
    if (Button_is_pressed)
    {
      // Сдвигаем изображение.
      Current_button->xLeft ++; Current_button->xRight ++;
      Current_button->yBottom --; Current_button->yTop --;

      // Закрашиваем свободное пространство.
      LONG Color = SYSCLR_BUTTONMIDDLE;
      GpiSetColor (Presentation_space, Color);

      Point.x = Current_button->xLeft + Pixel_margin;
      Point.y = Current_button->yBottom + Pixel_margin + 1;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);

      Point.y = Current_button->yTop - Pixel_margin;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.x = Current_button->xRight - Pixel_margin - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }
  }

  // Задаем размеры изображения.
  BYTE Icon_size = 'L';
  if ((All_buttons.yTop - All_buttons.yBottom) + 1 <= 22) Icon_size = 'L';
  if ((All_buttons.yTop - All_buttons.yBottom) + 1 <= 20) Icon_size = 'M';
  if ((All_buttons.yTop - All_buttons.yBottom) + 1 <= 18) Icon_size = 'S';

  INT Step = 4;    if (Icon_size == 'S') Step --;
  INT Jump = 6;    if (Icon_size == 'S') Jump --;

  INT CB_Step = 7; if (Icon_size == 'S') CB_Step --;
  INT CB_Jump = 1; if (Icon_size == 'M') CB_Jump = 2;
                   if (Icon_size == 'L') CB_Jump = 3;
  INT CB_Hole = 2;

  // Рисуем кнопку увеличения окна.
  if (Max_button.yTop)
  {
    // Закрашиваем свободное пространство.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // Задаем прямоугольник.
    Rectangle.xLeft = Max_button.xLeft + 1;     Rectangle.xRight = Max_button.xRight - 1;
    Rectangle.yBottom = Max_button.yBottom + 1; Rectangle.yTop = Max_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // Закрашиваем его.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // Рисуем линии.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // Если окно увеличено - уменьшаем прямоугольник.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    if (Buttons & RESTORE_ACTION)
    {
      Max_button.xLeft ++; Max_button.xRight --; Max_button.yBottom ++; Max_button.yTop --;
    }

    // Рисуем изображение.
    GpiSetColor (Presentation_space, CLR_DARKBLUE);

    POINT Point = { Max_button.xLeft + Step + 2, Max_button.yBottom + Step + 2 };
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Max_button.yTop - Step - 2;    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Max_button.xRight - Step - 2;  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Max_button.yBottom + Step + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Max_button.xLeft + Step + 2;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.x ++; Point.y ++;                     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Max_button.yTop - Step - 2 - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Max_button.xRight - Step - 2 - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = Max_button.xLeft + Step + 2;
    Point.y = Max_button.yBottom + Step + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Max_button.yTop - Step - 2;    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.x = Max_button.xRight - Step - 2;  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Max_button.yBottom + Step + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // Рисуем кнопку уменьшения или сокрытия окна.
  if (Min_button.yTop)
  {
    // Закрашиваем свободное пространство.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // Задаем прямоугольник.
    Rectangle.xLeft = Min_button.xLeft + 1;     Rectangle.xRight = Min_button.xRight - 1;
    Rectangle.yBottom = Min_button.yBottom + 1; Rectangle.yTop = Min_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // Закрашиваем его.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // Рисуем линии.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // Рисуем изображение.
    GpiSetColor (Presentation_space, CLR_DARKGREEN);

    POINT Point = { Min_button.xLeft + Jump + 2, Min_button.yBottom + Jump + 2 };
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Min_button.yTop - Jump - 2;    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Min_button.xRight - Jump - 2;  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Min_button.yBottom + Jump + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Min_button.xLeft + Jump + 2;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.x ++; Point.y ++;                     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Min_button.yTop - Jump - 2 - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Min_button.xRight - Jump - 2 - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = Min_button.xLeft + Jump + 2;
    Point.y = Min_button.yBottom + Jump + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Min_button.yTop - Jump - 2;    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.x = Min_button.xRight - Jump - 2;  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Min_button.yBottom + Jump + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // Рисуем кнопку "Убрать наверх".
  if (Rollup_button.yTop)
  {
    // Закрашиваем свободное пространство.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // Задаем прямоугольник.
    Rectangle.xLeft = Rollup_button.xLeft + 1;     Rectangle.xRight = Rollup_button.xRight - 1;
    Rectangle.yBottom = Rollup_button.yBottom + 1; Rectangle.yTop = Rollup_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // Закрашиваем его.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // Рисуем линии.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // Если окно увеличено - уменьшаем прямоугольник.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    if (Icon_size == 'L') if (Buttons & RESTORE_ACTION)
    {
      Rollup_button.yBottom ++; Rollup_button.yTop --;
    }

    // Рисуем изображение.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = { Rollup_button.xLeft + Step + 1, Rollup_button.yBottom + Jump + 3 };
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rollup_button.yTop - Jump - 2;    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rollup_button.xRight - Step - 1;  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Rollup_button.yBottom + Jump + 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rollup_button.xLeft + Step + 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.x ++; Point.y ++;                        if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rollup_button.yTop - Jump - 2 - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rollup_button.xRight - Step - 1 - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Рисуем кнопку закрытия.
  if (Close_button.yTop)
  {
    // Закрашиваем свободное пространство.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // Задаем прямоугольник.
    Rectangle.xLeft = Close_button.xLeft + 1;     Rectangle.xRight = Close_button.xRight - 1;
    Rectangle.yBottom = Close_button.yBottom + 1; Rectangle.yTop = Close_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // Закрашиваем его.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // Рисуем линии.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // Рисуем изображение.
    GpiSetColor (Presentation_space, CLR_DARKRED);

    POINT Point = { Close_button.xLeft + CB_Step, Close_button.yBottom + CB_Step };
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y += CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Close_button.yTop - CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y -= CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.x = Close_button.xLeft + CB_Step; Point.y = Close_button.yTop - CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x += CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Close_button.xRight - CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x -= CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.x = Close_button.xRight - CB_Step; Point.y = Close_button.yTop - CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y -= CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Close_button.yBottom + CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y += CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.x = Close_button.xRight - CB_Step; Point.y = Close_button.yBottom + CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x -= CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Close_button.xLeft + CB_Step;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x += CB_Jump;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE);

    Point.y = Point.y = Close_button.yBottom + CB_Step;
    Point.x = Close_button.xLeft + CB_Step + CB_Jump; if (Icon_size == 'S') Point.x += 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x += CB_Hole - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.y = Close_button.yTop - CB_Step;
    Point.x = Close_button.xLeft + CB_Step + CB_Jump; if (Icon_size == 'S') Point.x += 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x += CB_Hole - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.x = Close_button.xLeft + CB_Step;
    Point.y = Close_button.yTop - CB_Step - CB_Jump - 1; if (Icon_size == 'S') Point.y -= 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y += CB_Hole - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    Point.x = Close_button.xRight - CB_Step;
    Point.y = Close_button.yTop - CB_Step - CB_Jump - 1; if (Icon_size == 'S') Point.y -= 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y += CB_Hole - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Задает прямоугольник для строки заголовка ───

// Все переменные - внешние.
VOID Painter_CalculateTitleRectangle (HPS Presentation_space, HWND TitleBar_window, PRECT TitleBar_rectangle, HWND Frame_window, PRECT Frame_rectangle, BYTE Window_is_active, BYTE Advanced_controls, PCHAR Window_title, PRECT Title_rectangle, PLONG Text_attributes)
{
  // Узнаем расположение окна заголовка в окне рамки.
  SWP TitleBar_placement = {0}; WinQueryWindowPos (TitleBar_window, &TitleBar_placement);

  // Узнаем размер прямоугольника, который потребуется для рисования строки.
  INT Length = strlen (Window_title); POINT Text_box_points[TXTBOX_COUNT];
  GpiQueryTextBox (Presentation_space, Length, Window_title, TXTBOX_COUNT, Text_box_points);

  // Ширина строки.
  INT String_width = Text_box_points[TXTBOX_TOPRIGHT].x - Text_box_points[TXTBOX_BOTTOMLEFT].x;

  // Отступ слева и справа внутри заголовка.
  INT Margin = TitleBar_rectangle->yTop / 2;

  // Расстояние в окне рамки до начала строки.
  INT Space = (Frame_rectangle->xRight - String_width) / 2;
  INT Min_space = TitleBar_placement.x + Margin;
  if (Space < Min_space) Space = Min_space;

  // Задаем выравнивание для текста.
  LONG Defined_alignment = DT_CENTER;

  if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX ||
      Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION ||
      Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Defined_alignment = DT_LEFT;

  // Название надо выравнивать по середине окна заголовка, но если справа от него
  // есть еще какое-то окно, то название надо выравнивать по середине окна рамки.
  BYTE Binding_to_TitleBar = 1; LONG Alignment_in_rectangle = 0;

  // Если строка больше, чем окно заголовка, то ее придется выровнять по левому краю.
  if (String_width > TitleBar_rectangle->xRight - Margin * 2)
  {
    Alignment_in_rectangle = DT_LEFT;
  }
  // Иначе:
  else
  {
    // Иногда текст может быть привязан не к заголовку, а к рамке окна.
    BYTE Text_can_be_unbinded = 0;

    // Если рядом с заголовком нет дополнительных окон:
    if (!Advanced_controls)
    {
      // Текст будет выровнен так, как задано по умолчанию.
      Alignment_in_rectangle = Defined_alignment;

      // Если окно не имеет кнопок в правом верхнем углу и они не будут нарисованы - текст можно не привязывать к заголовку.
      if (Defined_alignment == DT_CENTER)
       if (!Painter.Settings.Draw_buttons)
        if (WinWindowFromID (Frame_window, FID_MINMAX) == NULLHANDLE)
         Text_can_be_unbinded = 1;
    }
    // А если такие окна есть:
    else
    {
      // Если текст надо выравнивать по середине:
      if (Defined_alignment == DT_CENTER)
      {
        // Текст будет выровнен по правому краю прямоугольника.
        Alignment_in_rectangle = DT_RIGHT;

        // Текст можно не привязывать к заголовку.
        Text_can_be_unbinded = 1;
      }
    }

    // Если строка не выйдет за пределы заголовка, ее можно привязать к окну рамки.
    if (Text_can_be_unbinded)
     if (Space + String_width < TitleBar_placement.x + TitleBar_placement.cx - Margin)
      Binding_to_TitleBar = 0;
  }

  // Если надо привязаться к окну заголовка:
  if (Binding_to_TitleBar)
  {
    // Прямоугольник для строки - это окно заголовка с учетом отступа.
    Title_rectangle->xLeft = TitleBar_rectangle->xLeft + Margin;
    Title_rectangle->xRight = TitleBar_rectangle->xRight - Margin;

    // Выравнивание текста было определено заранее.
    *Text_attributes |= Alignment_in_rectangle;
  }
  // А если привязываться к окну заголовка не надо:
  else
  {
    // Прямоугольник будет расположен внутри окна рамки.
    // Выравнивание текста в этом случае уже не имеет значения.
    Title_rectangle->xLeft = Space - TitleBar_placement.x;
    Title_rectangle->xRight = Title_rectangle->xLeft + String_width;
  }

  // Возврат.
  return;
}

// ─── Восстанавливает в окне заголовка цвета по умолчанию ───

// TitleBar_window - окно заголовка.
VOID Painter_ResetTitleBarColors (HWND TitleBar_window)
{
  // Узнаем, были ли заданы для окна заголовка другие цвета.
  ULONG Color = 0;

  ULONG FG_Attribute_is_exists = 0; WinQueryPresParam (TitleBar_window, PP_ACTIVETEXTFGNDCOLORINDEX, 0, &FG_Attribute_is_exists, sizeof (ULONG), &Color, QPF_ID1COLORINDEX | QPF_NOINHERIT);
  ULONG BG_Attribute_is_exists = 0; WinQueryPresParam (TitleBar_window, PP_ACTIVECOLORINDEX, 0, &BG_Attribute_is_exists, sizeof (ULONG), &Color, QPF_ID1COLORINDEX | QPF_NOINHERIT);

  // Если они были заданы - сбрасываем их.
  if (FG_Attribute_is_exists || BG_Attribute_is_exists)
  {
    // Запрещаем обновление окна.
    WinEnableWindowUpdate (TitleBar_window, 0);

    // Удаляем заданные расширителем цвета.
    WinRemovePresParam (TitleBar_window, PP_ACTIVECOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_ACTIVETEXTBGNDCOLORINDEX);

    WinRemovePresParam (TitleBar_window, PP_INACTIVECOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_INACTIVETEXTBGNDCOLORINDEX);

    WinRemovePresParam (TitleBar_window, PP_ACTIVETEXTFGNDCOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_INACTIVETEXTFGNDCOLORINDEX);

    // Разрешаем обновление окна.
    WinEnableWindowUpdate (TitleBar_window, 1);
  }

  // Возврат.
  return;
}

// ─── Рисует картинку в левом верхнем углу окна ───

// Все переменные - внешние, SysMenu_is_pressed, SysMenu_is_used - пользователь нажал на картинку с помощью мыши.
VOID Painter_DrawSystemMenu (HWND SysMenu_window, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, HPOINTER Icon, LONG Frame_type, BYTE SysMenu_is_pressed)
{
  // Если картинка неизвестна - возврат.
  if (Icon == NULLHANDLE) return;

  // Если окно не показано - возврат.
  if (!WindowIsPresent (SysMenu_window)) return;

  // Узнаем, как выглядит рамка окна, если это требуется.
  if (Frame_type == FT_UNKNOWN) Frame_type = FrameType (Frame_window);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (SysMenu_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (SysMenu_window, &Rectangle);

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle.yTop --; Rectangle.xRight --;

  // Закрашиваем картинку.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE);

  for (INT Count = 0; Count <= Rectangle.yTop; Count ++)
  {
    // Рисуем линии.
    POINT Point = { 0, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Рисуем значок. Если картинка нажата - сдвигаем ее.
  INT X = 1; INT Y = 1; if (SysMenu_is_pressed) { X = 2; Y = 0; }
  WinDrawPointer (Presentation_space, X, Y, Icon, DP_MINIICON);

  // Узнаем отступ от края картинки.
  INT Pixel_margin = Painter_GetButtonPixelMargin ();

  // Узнаем, надо ли рисовать тень, если картинка нажата.
  BYTE Draw_lines = 1;

  if (Pixel_margin == 0)
  {
    // Если у окна рамка в одну точку - не рисуем тень.
    if (SysMenu_is_pressed)
     if (Frame_type == FT_POINT) Draw_lines = 0;

    // Если у окна рамка постоянного размера:
    if (SysMenu_is_pressed)
     if (Frame_type == FT_CONST)
     {
       // Если у окна нет внутренней рамки - не рисуем тень.
       if (!Painter.Settings.Draw_volume_lines) Draw_lines = 0;
       // Если в окне есть меню - не рисуем тень.
       else if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_lines = 0;
     }
  }

  // Рисуем светлую часть рамки, или тень, если картинка нажата.
  POINT Point = { Pixel_margin, Pixel_margin };

  if (!(SysMenu_is_pressed && !Draw_lines))
  {
    if (!SysMenu_is_pressed) GpiSetColor (Presentation_space, CLR_WHITE);
    else GpiSetColor (Presentation_space, CLR_DARKGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle.yTop - Pixel_margin;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle.xRight - Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Рисуем темную часть рамки и уголки, если картинка не нажата.
  if (!SysMenu_is_pressed)
  {
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.y = Rectangle.yTop - Pixel_margin; Point.x = Rectangle.xRight - Pixel_margin;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle.yTop - Pixel_margin; Point.x = Rectangle.xRight - Pixel_margin;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // Рисуем внешнюю рамку.
  if (Pixel_margin != 0)
  {
    // Рисуем светлую часть внешней рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = 0; Point.x = 0;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Rectangle.yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем темную часть внешней рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle.yTop; Point.x = Rectangle.xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка, делая его трехмерным ───

// Все переменные - внешние.
VOID Painter_DrawVTVControlVolumeLines (HWND TitleBar_window, PRECT Rectangle, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Если окно рамки не выбрано - подчеркиваем объем.
  if (!Window_is_active)
  {
    // Рисуем темную часть рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем светлую часть рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем темную часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = 1; Point.y = 1;        if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем светлую часть внутренней рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.x = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки рамки.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop - 1; Point.x = Rectangle->xRight - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = 0; Point.x = 0;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }
  // А если окно выбрано - рисуем прямоугольник.
  else
  {
    GpiSetColor (Presentation_space, Color);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка ───

// Все переменные - внешние.
VOID Painter_DrawOS4TitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.x = 1; Point.y = 1;        if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.x = Rectangle->xRight; Point.y = Rectangle->yTop - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = 0; Point.x = Rectangle->xRight;                   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0;                                                if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  Point.x = Rectangle->xRight - 1; Point.y = Rectangle->yTop - 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = 1;                                                    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 1;                                                    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

  Point.y = 0; Point.x = 0;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = 1; Point.x = 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop - 1; Point.x = Rectangle->xRight - 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка ───

// Все переменные - внешние.
VOID Painter_DrawLionTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

  Point.y = 0; Point.x = 0;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка ───

// Все переменные - внешние.
VOID Painter_DrawECSTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y ++;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.x ++;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y --;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y --;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.x --;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y ++;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = 0; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.x --;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.x ++; Point.y ++;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Rectangle->yTop; Point.x = 0;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y --;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y ++; Point.x ++;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  Point.y = Rectangle->yTop - 1; Point.x = 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.y = 1; Point.x = Rectangle->xRight - 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка ───

// Все переменные - внешние.
VOID Painter_DrawSnowTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Рисуем темную часть рамки.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем светлую часть рамки.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // Рисуем уголки рамки.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем заголовка ───

// Все переменные - внешние.
VOID Painter_DrawClassicTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Если окно рамки не выбрано - подчеркиваем объем.
  if (!Window_is_active)
  {
    // Рисуем светлую часть рамки.
    GpiSetColor (Presentation_space, CLR_WHITE);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем темную часть рамки.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // Рисуем уголки рамки.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }
  // А если окно выбрано - рисуем прямоугольник.
  else
  {
    GpiSetColor (Presentation_space, Color);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Подчеркивает объем окна заголовка ───

// Все переменные - внешние.
VOID Painter_DrawTitleBarVolumeLines (HWND TitleBar_window, LONG Frame_type, PRECT Rectangle, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Задаем правила рисования в зависимости от выбранной темы для рамок.
  BYTE Draw_OS4_lines     = 0; 
  BYTE Draw_Lion_lines    = 0; 
  BYTE Draw_eCS_lines     = 0; 
  BYTE Draw_classic_lines = 0; 
  BYTE Draw_Snow_lines    = 0; 
  BYTE Draw_VTV_lines     = 0;
  BYTE Draw_nothing       = 0;

  switch (Painter.Settings.Theme)
  {
    case PAINTER_THEME_PHOENIX:
    {
      if (Window_is_active) Draw_OS4_lines = 1;
      else Draw_VTV_lines = 1;
    }
    break;

    case PAINTER_THEME_BLUE_LION:
    {
      if (Window_is_active) Draw_Lion_lines = 1;
      else Draw_nothing = 1;
    }
    break;

    case PAINTER_THEME_ECOMSTATION:
    {
      if (Window_is_active) Draw_eCS_lines = 1;
      else Draw_nothing = 1;
    }
    break;

    case PAINTER_THEME_CLASSIC_GRAY:
    case PAINTER_THEME_CLASSIC_RGB:
    {
      if (!Window_is_active)
      {
        if (Painter_PermissionForCompleteDrawing (Frame_window)) Draw_classic_lines = 1;
        else Draw_VTV_lines = 1;
      }
      else
      {
        if (!Painter_PermissionForCompleteDrawing (Frame_window)) Draw_OS4_lines = 1;
        else Draw_nothing = 1;
      }
    }
    break;

    case PAINTER_THEME_WHITE_SNOW:
    {
      if (Window_is_active) Draw_Snow_lines = 1;
      else Draw_VTV_lines = 1;
    }
    break;
  }

  // Подчеркиваем объем окна.
  if (Draw_OS4_lines) Painter_DrawOS4TitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_Lion_lines) Painter_DrawLionTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_eCS_lines) Painter_DrawECSTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_classic_lines) Painter_DrawClassicTitleBarVolumeLines (TitleBar_window,  Rectangle, -1, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_Snow_lines) Painter_DrawSnowTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_VTV_lines) Painter_DrawVTVControlVolumeLines (TitleBar_window, Rectangle, -1, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);

  // Возврат.
  return;
}

// ─── Заполняет окно заголовка, используя прямоугольники ───

// Все переменные - внешние.
VOID Painter_FillGlassTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Заполняем изображение прямоугольниками.
  switch (Painter.Settings.Theme)
  {
    case PAINTER_THEME_CLASSIC_RGB:
    {
      // Выбираем цвета.
      LONG Color_1 = Painter.Settings.AT_Color_1; LONG Color_2 = Painter.Settings.AT_Color_2; LONG Color_3 = Painter.Settings.AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.IT_Color_1; Color_2 = Painter.Settings.IT_Color_2; Color_3 = Painter.Settings.IT_Color_3; }

      switch (GetCurrentOrNextRoom ())
      {
        case NORTHERN_ROOM:{ Color_1 = Painter.Settings.Northern_AT_Color_1; Color_2 = Painter.Settings.Northern_AT_Color_2; Color_3 = Painter.Settings.Northern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Northern_IT_Color_1; Color_2 = Painter.Settings.Northern_IT_Color_2; Color_3 = Painter.Settings.Northern_IT_Color_3; }} break;
        case WESTERN_ROOM: { Color_1 = Painter.Settings.Western_AT_Color_1; Color_2 = Painter.Settings.Western_AT_Color_2; Color_3 = Painter.Settings.Western_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Western_IT_Color_1; Color_2 = Painter.Settings.Western_IT_Color_2; Color_3 = Painter.Settings.Western_IT_Color_3; }} break;
        case EASTERN_ROOM: { Color_1 = Painter.Settings.Eastern_AT_Color_1; Color_2 = Painter.Settings.Eastern_AT_Color_2; Color_3 = Painter.Settings.Eastern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Eastern_IT_Color_1; Color_2 = Painter.Settings.Eastern_IT_Color_2; Color_3 = Painter.Settings.Eastern_IT_Color_3; }} break;
        case SOUTHERN_ROOM:{ Color_1 = Painter.Settings.Southern_AT_Color_1; Color_2 = Painter.Settings.Southern_AT_Color_2; Color_3 = Painter.Settings.Southern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Southern_IT_Color_1; Color_2 = Painter.Settings.Southern_IT_Color_2; Color_3 = Painter.Settings.Southern_IT_Color_3; }} break;
      }

      // Рассчитываем цветовые переходы.
      INT Red_delta = REDFROMRGB (Color_2) - REDFROMRGB (Color_1);
      INT Green_delta = GREENFROMRGB (Color_2) - GREENFROMRGB (Color_1);
      INT Blue_delta = BLUEFROMRGB (Color_2) - BLUEFROMRGB (Color_1);

      // Рассчитываем расстояния.
      INT Width = Rectangle->xRight - Rectangle->xLeft;
      INT Height = Rectangle->yTop - Rectangle->yBottom;

      INT Limit = Max (Unsigned (Red_delta), Unsigned (Green_delta), Unsigned (Blue_delta));
      if (Limit > Width / 2) Limit = Width / 2;

      INT Colors = Limit + 1;

      FLOAT Step_for_red =   (FLOAT) (Red_delta) / Colors;
      FLOAT Step_for_green = (FLOAT) (Green_delta) / Colors;
      FLOAT Step_for_blue =  (FLOAT) (Blue_delta) / Colors;

      RECT Brick = { 0, Pixel_margin, 0, Rectangle->yTop - Pixel_margin + 1 };

      FLOAT Brick_width = (FLOAT) Width / 2 / Limit;

      // Рисуем прямоугольники.
      for (INT Count = 0; Count <= Limit; Count ++)
      {
        INT Red_intencity =   REDFROMRGB (Color_1) + Step_for_red * Count;
        INT Green_intencity = GREENFROMRGB (Color_1) + Step_for_green * Count;
        INT Blue_intencity =  BLUEFROMRGB (Color_1) + Step_for_blue * Count;

        LONG Color = MAKERGB (Red_intencity, Green_intencity, Blue_intencity);

        INT Left = Brick_width * Count + Pixel_margin;
        INT Right = Left + Brick_width + Pixel_margin;

        Brick.xLeft = Left; Brick.xRight = Right + 1;
        if (!Painter_SMPError (Frame_window, Frame_rectangle, NULL)) WinFillRect (Presentation_space, &Brick, Color);

        Brick.xLeft = Rectangle->xRight - Right; Brick.xRight = Rectangle->xRight - Left + 1;
        if (!Painter_SMPError (Frame_window, Frame_rectangle, NULL)) WinFillRect (Presentation_space, &Brick, Color);
      }
    }
    break;

    case PAINTER_THEME_WHITE_SNOW:
    {
      // Выбираем цвета.
      LONG Color_1 = Painter.Settings.AT_Color_2; LONG Color_2 = Painter.Settings.IT_Color_2;

      switch (GetCurrentOrNextRoom ())
      {
        case NORTHERN_ROOM:{ Color_1 = Painter.Settings.Northern_AT_Color_2; Color_2 = Painter.Settings.Northern_IT_Color_2; } break;
        case WESTERN_ROOM: { Color_1 = Painter.Settings.Western_AT_Color_2;  Color_2 = Painter.Settings.Western_IT_Color_2; } break;
        case EASTERN_ROOM: { Color_1 = Painter.Settings.Eastern_AT_Color_2;  Color_2 = Painter.Settings.Eastern_IT_Color_2; } break;
        case SOUTHERN_ROOM:{ Color_1 = Painter.Settings.Southern_AT_Color_2; Color_2 = Painter.Settings.Southern_IT_Color_2; } break;
      }

      // Рассчитываем цветовые переходы.
      INT Red_delta = REDFROMRGB (Color_2) - REDFROMRGB (Color_1);
      INT Green_delta = GREENFROMRGB (Color_2) - GREENFROMRGB (Color_1);
      INT Blue_delta = BLUEFROMRGB (Color_2) - BLUEFROMRGB (Color_1);

      // Рассчитываем расстояния.
      INT Width = Rectangle->xRight - Rectangle->xLeft;
      INT Height = Rectangle->yTop - Rectangle->yBottom;

      INT Limit = Max (Unsigned (Red_delta), Unsigned (Green_delta), Unsigned (Blue_delta));
      if (Limit > Width) Limit = Width;

      INT Colors = Limit + 1;

      FLOAT Step_for_red =   (FLOAT) (Red_delta) / Colors;
      FLOAT Step_for_green = (FLOAT) (Green_delta) / Colors;
      FLOAT Step_for_blue =  (FLOAT) (Blue_delta) / Colors;

      RECT Brick = { 0, Pixel_margin, 0, Rectangle->yTop - Pixel_margin + 1 };

      FLOAT Brick_width = (FLOAT) Width / Limit;

      // Рисуем прямоугольники.
      for (INT Count = 0; Count <= Limit; Count ++)
      {
        INT Red_intencity =   REDFROMRGB (Color_1) + Step_for_red * Count;
        INT Green_intencity = GREENFROMRGB (Color_1) + Step_for_green * Count;
        INT Blue_intencity =  BLUEFROMRGB (Color_1) + Step_for_blue * Count;

        LONG Color = MAKERGB (Red_intencity, Green_intencity, Blue_intencity);

        INT Left = Brick_width * Count + Pixel_margin;
        INT Right = Left + Brick_width + Pixel_margin;

        if (Right > Rectangle->xRight - Pixel_margin) Right = Rectangle->xRight - Pixel_margin;

        Brick.xLeft = Left; Brick.xRight = Right + 1;
        if (!Painter_SMPError (Frame_window, Frame_rectangle, NULL)) WinFillRect (Presentation_space, &Brick, Color);
      }
    }
    break;
  }

  // Возврат.
  return;
}

// ─── Заполняет окно, используя изображение ───

// Все переменные - внешние.
VOID Painter_FillNeonTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Создаем пространство отображения в памяти.
  HPS Drawing_memory_space = CreatePresentationSpace (Enhancer.Application);

  // Переносим изображение в окно.
  if (Window_is_active) GpiSetBitmap (Drawing_memory_space, Painter.RTSettings.AT_Bitmap);
  else GpiSetBitmap (Drawing_memory_space, Painter.RTSettings.IT_Bitmap);

  if (Rectangle->xRight <= Painter.RTSettings.AT_Bitmap_width)
  {
    POINT Image_points[4] = { 0, 0, Rectangle->xRight + 1, Rectangle->yTop + 1, 0, 0, Painter.RTSettings.AT_Bitmap_width - 1, Painter.RTSettings.AT_Bitmap_height - 1 };
    if (Pixel_margin) { Image_points[0].x += Pixel_margin; Image_points[0].y += Pixel_margin; Image_points[1].x -= Pixel_margin; Image_points[1].y -= Pixel_margin; }

    GpiBitBlt (Presentation_space, Drawing_memory_space, 3, Image_points, ROP_SRCCOPY, BBO_IGNORE);
  }
  else
  {
    for (INT X_Point = 0; X_Point < Rectangle->xRight; X_Point += Painter.RTSettings.AT_Bitmap_width)
     for (INT Y_Point = 0; Y_Point < Rectangle->yTop; Y_Point += Painter.RTSettings.AT_Bitmap_height)
     {
       POINT Image_points[4] = { X_Point, Y_Point, Rectangle->xRight, Rectangle->yTop, 0, 0, Painter.RTSettings.AT_Bitmap_width - 1, Painter.RTSettings.AT_Bitmap_height - 1 };
       if (Pixel_margin) { Image_points[0].x += Pixel_margin; Image_points[0].y += Pixel_margin; Image_points[1].x -= Pixel_margin; Image_points[1].y -= Pixel_margin; }

       GpiBitBlt (Presentation_space, Drawing_memory_space, 3, Image_points, ROP_SRCCOPY, BBO_IGNORE);
     }
  }

  GpiSetBitmap (Drawing_memory_space, NULLHANDLE);

  // Удаляем пространство отображения.
  GpiDestroyPS (Drawing_memory_space); Drawing_memory_space = NULLHANDLE;

  // Возврат.
  return;
}

// ─── Заполняет окно заголовка разными цветами ───

// Все переменные - внешние.
VOID Painter_FillNeonOrGlassTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Заполняем окно заголовка.
  if (!Painter_GlassTitleBarIsRequired ())
   Painter_FillNeonTitleBar (TitleBar_window, Presentation_space, Rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  else
   Painter_FillGlassTitleBar (TitleBar_window, Presentation_space, Rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);

  // Возврат.
  return;
}

// ─── Закрашивает окно в заголовке ───

// Все переменные - внешние.
VOID Painter_FillControl (HPS Presentation_space, PRECT Rectangle, LONG Color, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Закрашиваем окно. Значения Rectangle были уменьшены на единицу.
  GpiSetColor (Presentation_space, Color);

  // Рисуем линии.
  if (Pixel_margin)
  {
    for (INT Count = Pixel_margin; Count <= Rectangle->yTop - Pixel_margin; Count ++)
    {
      POINT Point = { Pixel_margin, Count };      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle->xRight - Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }
  }
  else
  {
    for (INT Count = 0; Count <= Rectangle->yTop; Count ++)
    {
      POINT Point = { 0, Count };  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }
  }

  // Возврат.
  return;
}

// ─── Заполняет окно заголовка одним цветом ───

// Все переменные - внешние.
VOID Painter_FillTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Выбираем цвет.
  LONG Background_color = Painter.Settings.AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.IT_Background_color;

  INT Room = GetCurrentOrNextRoom ();

  if (Room == NORTHERN_ROOM) { Background_color = Painter.Settings.Northern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Northern_IT_Background_color; }
  if (Room == WESTERN_ROOM) { Background_color = Painter.Settings.Western_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Western_IT_Background_color; }
  if (Room == EASTERN_ROOM) { Background_color = Painter.Settings.Eastern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Eastern_IT_Background_color; }
  if (Room == SOUTHERN_ROOM) { Background_color = Painter.Settings.Southern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Southern_IT_Background_color; }

  // Закрашиваем заголовок.
  Painter_FillControl (Presentation_space, Rectangle, Background_color, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);

  // Возврат.
  return;
}

// ─── Рисует заголовок ───

// Все переменные - внешние.
VOID Painter_DrawTitleBar (HWND TitleBar_window, HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, PCHAR Window_title, BYTE Window_is_active, BYTE Advanced_controls)
{
  // Если окно не показано - возврат.
  if (!WindowIsPresent (TitleBar_window)) return;

  // Узнаем размер окна заголовка
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  TitleBar_rectangle.yTop --; TitleBar_rectangle.xRight --;

  // Подчеркиваем объем окна заголовка.
  BYTE Volume_lines_are_drawn = 0;
  if (!Painter_NeonTitleBarIsRequired (Window_is_active))
  {
    Painter_DrawTitleBarVolumeLines (TitleBar_window, Frame_type, &TitleBar_rectangle, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
    Volume_lines_are_drawn = 1;
  }

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Задаем вид текста.
  LONG Text_attributes = DT_TEXTATTRS;

  BYTE Allow_mnemonic_characters = 1; INT Count = 0;
  while (Window_title[Count] != 0)
  {
    if (Window_title[Count] == '~') Allow_mnemonic_characters = 0;
    Count ++;
  }

  if (Allow_mnemonic_characters) Text_attributes |= DT_MNEMONIC;

  // Задаем прямоугольник для строки заголовка.
  INT Pixel_margin = Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, Frame_window, Window_is_active);

  RECT Title_rectangle = { 0, 0, 0, TitleBar_rectangle.yTop };
  Painter_CalculateTitleRectangle (Presentation_space, TitleBar_window, &TitleBar_rectangle, Frame_window, Frame_rectangle, Window_is_active, Advanced_controls, Window_title, &Title_rectangle, &Text_attributes);

  // Сбрасываем палитру цветов для окна заголовка.
  ForceColorPaletteToRGB (Presentation_space);

  // Закрашиваем заголовок.
  if (Painter_TitleBarIsGrayed (Window_is_active))
  {
    Painter_FillTitleBar (TitleBar_window, Presentation_space, &TitleBar_rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  }
  else
  {
    Painter_FillNeonOrGlassTitleBar (TitleBar_window, Presentation_space, &TitleBar_rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  }

  // Если надо подчеркивать объем заголовка и окно выбрано - передвигаем строку вниз и вправо.
  // Примечательно, что пользователю может показаться то же самое, если будет нарисована тень.
  BYTE Move_title = 0;

  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_GRAY || Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB)
   if (Window_is_active || !Painter_PermissionForCompleteDrawing (Frame_window))
    Move_title = 1;

  if (Move_title)
  {
    Title_rectangle.xLeft ++; Title_rectangle.xRight ++;
    Title_rectangle.yBottom --; Title_rectangle.yTop --;
  }

  // Строку надо подвинуть если заголовок больше некоторого размера.
  if (Title_rectangle.yTop - Title_rectangle.yBottom > 20)
  {
    Title_rectangle.yBottom --; Title_rectangle.yTop --;
  }

  // Если окно заголовка все еще есть:
  if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
  {
    // Выбираем цвет.
    LONG Text_color = MAKERGB (0xFF, 0xFF, 0xFF); if (!Window_is_active) Text_color = MAKERGB (0, 0, 0);
    if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_GRAY)
    {
      Text_color = Painter.Settings.AT_Text_color; if (!Window_is_active) Text_color = Painter.Settings.IT_Text_color;
    }

    INT Room = GetCurrentOrNextRoom ();

    if (Room == NORTHERN_ROOM) { Text_color = Painter.Settings.Northern_AT_Text_color; if (!Window_is_active) Text_color = Painter.Settings.Northern_IT_Text_color; }
    if (Room == WESTERN_ROOM) { Text_color = Painter.Settings.Western_AT_Text_color; if (!Window_is_active) Text_color = Painter.Settings.Western_IT_Text_color; }
    if (Room == EASTERN_ROOM) { Text_color = Painter.Settings.Eastern_AT_Text_color; if (!Window_is_active) Text_color = Painter.Settings.Eastern_IT_Text_color; }
    if (Room == SOUTHERN_ROOM) { Text_color = Painter.Settings.Southern_AT_Text_color; if (!Window_is_active) Text_color = Painter.Settings.Southern_IT_Text_color; }

    // Если надо рисовать 3D текст:
    BYTE Draw_A3D_text = 0; BYTE Draw_V3D_text = 0;

    if (!Window_is_active)
    {
      if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX ||
          Painter.Settings.Theme == PAINTER_THEME_BLUE_LION ||
          Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION) Draw_A3D_text = 1;

      if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB ||
          Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Draw_V3D_text = 1;
    }

    if (Draw_A3D_text)
    {
      // Задаем прямоугольник для текста.
      RECT A3D_rectangle = {0}; memcpy (&A3D_rectangle, &Title_rectangle, sizeof (RECT));
      A3D_rectangle.xLeft --; A3D_rectangle.xRight --; A3D_rectangle.yBottom ++; A3D_rectangle.yTop ++;

      // Рисуем темный текст для строки заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_WHITE);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &A3D_rectangle, 0, 0, Text_attributes);

      // Задаем прямоугольник для текста.
      A3D_rectangle.xLeft ++; A3D_rectangle.xRight ++; A3D_rectangle.yBottom --; A3D_rectangle.yTop --;

      // Рисуем светлый текст для строки заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_DARKGRAY);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &A3D_rectangle, 0, 0, Text_attributes);
    }

    if (Draw_V3D_text)
    {
      // Задаем прямоугольник для текста.
      RECT V3D_rectangle = {0}; memcpy (&V3D_rectangle, &Title_rectangle, sizeof (RECT));
      V3D_rectangle.xLeft ++; V3D_rectangle.xRight ++; V3D_rectangle.yBottom --; V3D_rectangle.yTop --;

      // Рисуем темный текст для строки заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_WHITE);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &V3D_rectangle, 0, 0, Text_attributes);

      // Задаем прямоугольник для текста.
      V3D_rectangle.xLeft --; V3D_rectangle.xRight --; V3D_rectangle.yBottom ++; V3D_rectangle.yTop ++;

      // Рисуем светлый текст для строки заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_DARKGRAY);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &V3D_rectangle, 0, 0, Text_attributes);
    }

    // Если надо рисовать тень:
    BYTE Draw_shadow = 0;

    if (Window_is_active)
    {
      if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX ||
          Painter.Settings.Theme == PAINTER_THEME_BLUE_LION ||
          Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION ||
          Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB ||
          Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Draw_shadow = 1;
    }

    if (Draw_shadow)
    {
      // Задаем прямоугольник для тени.
      RECT Shadow_rectangle = {0}; memcpy (&Shadow_rectangle, &Title_rectangle, sizeof (RECT));
      Shadow_rectangle.xLeft ++; Shadow_rectangle.xRight ++; Shadow_rectangle.yBottom --; Shadow_rectangle.yTop --;

      // Рисуем тень для строки заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_BLACK);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &Shadow_rectangle, 0, 0, Text_attributes);
    }

    // Если рисовать 3D текст не надо:
    if (!Draw_A3D_text) if (!Draw_V3D_text)
    {
      // Рисуем строку заголовка.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, Text_color);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &Title_rectangle, 0, 0, Text_attributes);
    }
  }

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Подчеркиваем объем окна заголовка, если это не было сделано раньше.
  if (!Volume_lines_are_drawn)
  {
    if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
    {
      Painter_DrawTitleBarVolumeLines (TitleBar_window, Frame_type, &TitleBar_rectangle, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
    }
  }

  // Возврат.
  return;
}

// ─── Предварительно закрашивает окно, используя изображение или прямоугольники ───

// Все переменные - внешние.
VOID Painter_PreDrawNeonOrGlassTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle.yTop --; Rectangle.xRight --;

  // Отступать от края окна не требуется.
  INT No_margin = 0;

  // Сбрасываем палитру цветов для окна заголовка.
  ForceColorPaletteToRGB (Presentation_space);

  // Закрашиваем заголовок окна.
  Painter_FillNeonOrGlassTitleBar (TitleBar_window, Presentation_space, &Rectangle, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Предварительно закрашивает окно заголовка, используя один цвет ───

// Все переменные - внешние.
VOID Painter_PreDrawGrayedTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle.yTop --; Rectangle.xRight --;

  // Отступать от края окна не требуется.
  INT No_margin = 0;

  // Сбрасываем палитру цветов для окна заголовка.
  ForceColorPaletteToRGB (Presentation_space);

  // Закрашиваем заголовок окна.
  Painter_FillTitleBar (TitleBar_window, Presentation_space, &Rectangle, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Предварительно закрашивает окно заголовка ───

// Control_window - одно из окон в заголовке, Color - цвет, Window_is_active - выбрано ли окно рамки, Frame_* - окно рамки и его размер/расположение.
VOID Painter_PreDrawControl (HWND Control_window, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Узнаем размер окна.
  RECT Rectangle = {0}; WinQueryWindowRect (Control_window, &Rectangle);

  // Работаем в пространстве отображения окна.
  HPS Presentation_space = WinGetPS (Control_window);

  // Если пространство отображения не получено - возврат.
  if (Presentation_space == NULLHANDLE) return;

  // Отсчет ведется от 0, поэтому размеры надо уменьшить на единицу.
  Rectangle.yTop --; Rectangle.xRight --;

  // Отступать от края окна не требуется.
  INT No_margin = 0;

  // Закрашиваем заголовок окна.
  Painter_FillControl (Presentation_space, &Rectangle, Color, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // Завершаем работу в пространстве отображения окна.
  WinReleasePS (Presentation_space);

  // Возврат.
  return;
}

// ─── Предварительно закрашивает окно заголовка ───

// Все переменные - внешние.
VOID Painter_PreDrawTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // Закрашиваем окно.
  if (Painter_TitleBarIsGrayed ())
  {
    Painter_PreDrawGrayedTitleBar (TitleBar_window, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  }
  else
  {
    Painter_PreDrawNeonOrGlassTitleBar (TitleBar_window, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  }

  // Возврат.
  return;
}

