
// ��� �஢����, ���� �� ����� ࠬ�� ���

BYTE Painter_FrameDrawingIsRequired (VOID)
{
  // �஢��塞 ����ன��.
  if (!Painter.Settings.Draw_normal_frames)
   if (!Painter.Settings.Draw_const_frames)
    if (!Painter.Settings.Draw_point_frames)
     if (!Painter.Settings.Draw_flat_frames) return 0;

  // ������.
  return 1;
}

// ��� ��ᯮ����� ��� ��������� ���

BYTE Painter_DifferentTitleBarImagesAreRequired (VOID)
{
  // ������.
  return 0;
}

// ��� ��ᯮ����� ��� ��������� ���

// Window_is_active - ��࠭� �� ����.
BYTE Painter_NeonTitleBarIsRequired (BYTE Window_is_active = 1)
{
  // �஢��塞 ⥬� ��� ࠬ�� � ᬮ�ਬ, ��࠭� �� ����.
  if (Window_is_active)
  {
    if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX) return 1;
    if (Painter.Settings.Theme == PAINTER_THEME_BLUE_LION) return 1;
    if (Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION) return 1;
  }

  // ������.
  return 0;
}

// ��� ��ᯮ����� ��� ��������� ���

// Window_is_active - ��࠭� �� ����.
BYTE Painter_GlassTitleBarIsRequired (BYTE Window_is_active = 1)
{
  // �஢��塞 ⥬� ��� ࠬ�� � ᬮ�ਬ, ��࠭� �� ����.
  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB) return 1;

  if (Window_is_active)
  {
    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) return 1;
  }

  // ������.
  return 0;
}

// ��� ��ᯮ����� ��� ��������� ���

// Window_is_active - ��࠭� �� ����.
BYTE Painter_TitleBarIsGrayed (BYTE Window_is_active = 1)
{
  // �஢��塞 ⥬� ��� ࠬ��.
  if (!Painter_NeonTitleBarIsRequired (Window_is_active))
   if (!Painter_GlassTitleBarIsRequired (Window_is_active))
    return 1;

  // ������.
  return 0;
}

// ��� �����頥� ����� ��� ����ࠦ���� �� ��� ������ ���

INT Painter_GetButtonPixelMargin (VOID)
{
  // �롨ࠥ� ����� �� ��� ���������.
  INT Pixel_margin = 0;

  if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Pixel_margin = 1;

  // ������.
  return Pixel_margin;
}

// ��� �����頥� ����� ��� ����ࠦ���� �� ��� ��������� ���

// Theme - ⥬� ��� �ᮢ����, Frame_window - ���� ࠬ��, Window_is_active - ��࠭� �� ����.
INT Painter_GetTitleBarPixelMargin (INT Theme, HWND Frame_window, BYTE Window_is_active)
{
  // �롨ࠥ� ����� �� ��� ���������.
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

  // ������.
  return Pixel_margin;
}

// ��� ����뢠�� 㧮� ��� ���������� ��������� ���

VOID Painter_DeleteTitleBarPattern (VOID)
{
  // ����뢠�� ��᫥���� �ᯮ�짮����� 㧮�.
  if (Painter.RTSettings.Pattern != NULLHANDLE)
  {
    GpiDeleteBitmap (Painter.RTSettings.Pattern);
    Painter.RTSettings.Pattern = NULLHANDLE ;
  }

  // ����뢠�� ��� ���.
  Painter.RTSettings.Pattern_name[0] = 0;

  // ������.
  return;
}

// ��� ����� ����ࠦ���� ��� ���������� ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_PrepareTitleBarImage (HPS Memory_space, RECT Rectangle, BYTE Window_is_active)
{
  // ������ ��� 㧮�.
  PCHAR File_name = Painter.Settings.TitleBar_pattern;
  CHAR Name[SIZE_OF_NAME] = ""; strcpy (Name, FindNameInPath (File_name));

  // ������, ���� �� ����㦠�� 㧮� � ��᪠, ��� ����� ����� ��⮢�.
  BYTE Use_last_loaded_pattern = 0;

  if (Painter.RTSettings.Pattern != NULLHANDLE)
   if (strc (Painter.RTSettings.Pattern_name, Name))
    Use_last_loaded_pattern = 1;

  // �᫨ ���� ����㦠�� ���� 㧮�
  if (!Use_last_loaded_pattern)
  {
    // ����塞 �।��騩 㧮�.
    Painter_DeleteTitleBarPattern ();

    // ����㦠�� 㧮� � ��᪠.
    LoadBitmap (Enhancer.Application, File_name, &Painter.RTSettings.Pattern, &Painter.RTSettings.Pattern_width, &Painter.RTSettings.Pattern_height);

    // �᫨ 㧮� ��� - ������.
    if (Painter.RTSettings.Pattern == NULLHANDLE) return;

    // ���������� ��� ���.
    strcpy (Painter.RTSettings.Pattern_name, Name);
  }

  // ������塞 ����ࠦ���� � �����.
  for (INT X_Count = 0; X_Count < Rectangle.xRight; X_Count += Painter.RTSettings.Pattern_width)
  {
    POINT Point = { X_Count, 0 };
    WinDrawBitmap (Memory_space, Painter.RTSettings.Pattern, NULL, &Point, 0, 0, DBM_NORMAL);
  }

  // ������.
  return;
}

// ��� ����뢠�� ����ࠦ���� ��� ���������� ��������� ���

VOID Painter_DeleteTitleBarImages (VOID)
{
  // ����塞 ����ࠦ����.
  if (Painter.RTSettings.AT_Bitmap != NULLHANDLE) { GpiDeleteBitmap (Painter.RTSettings.AT_Bitmap); Painter.RTSettings.AT_Bitmap = NULLHANDLE; }
  if (Painter.RTSettings.IT_Bitmap != NULLHANDLE) { GpiDeleteBitmap (Painter.RTSettings.IT_Bitmap); Painter.RTSettings.IT_Bitmap = NULLHANDLE; }

  Painter.RTSettings.AT_Bitmap_width = Painter.RTSettings.AT_Bitmap_height = -1;

  // ������.
  return;
}

// ��� ������� ����ࠦ���� ��� ���������� ��������� ���

VOID Painter_CreateTitleBarImages (INT Required_width = 0)
{
  // ����塞 �।��騥 ����ࠦ����.
  Painter_DeleteTitleBarImages ();

  // �᫨ ������� ��������� �ᮢ��� �� ���� - ������.
  if (!Painter_NeonTitleBarIsRequired ()) return;

  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // ������ ����� ��������� ����.
  INT TitleBar_height = WinQuerySysValue (Desktop, SV_CYMINMAXBUTTON);

  // ������ ࠧ���� ����ࠦ����.
  INT Width = Required_width;
  if (!Width) Width = WinQuerySysValue (QueryDesktopWindow (), SV_CXSCREEN);

  INT AT_Height = TitleBar_height - Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, NULLHANDLE, 1);
  INT IT_Height = TitleBar_height - Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, NULLHANDLE, 0);

  // ������� ����࠭�⢮ �⮡ࠦ���� � �����.
  HPS Drawing_memory_space = CreatePresentationSpace (Enhancer.Application);

  // ������� ����ࠦ���� ��� ���������� ���������.
  Painter.RTSettings.AT_Bitmap = CreateBitmap (Drawing_memory_space, Width, AT_Height);
  Painter.RTSettings.IT_Bitmap = CreateBitmap (Drawing_memory_space, Width, IT_Height);

  // ������塞 ����ࠦ���� ��� ���������� ����.
  for (INT Images_count = 0; Images_count < 2; Images_count ++)
  {
    // ������ ��אַ㣮�쭨� ��� �ᮢ����.
    INT Height = AT_Height; if (Images_count == 1) INT Height = IT_Height;
    RECT Rectangle = { 0, 0, Width - 1, Height - 1 };

    // �롨ࠥ� ����ࠦ����.
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

  // ����塞 ����࠭�⢮ �⮡ࠦ����.
  GpiDestroyPS (Drawing_memory_space); Drawing_memory_space = NULLHANDLE;

  // ���������� ࠧ���� ����ࠦ����.
  Painter.RTSettings.AT_Bitmap_width = Width; Painter.RTSettings.AT_Bitmap_height = AT_Height;

  // ������.
  return;
}

// ��� ������ ࠧ��� � �ᯮ������� ���� ࠬ�� ���

// �� ��६���� - ���譨�.
VOID Painter_QueryFrameRectangeAndPlacement (HWND Frame_window, PRECT Rectangle, PSWP Placement)
{
  // ������ ࠧ��� ����.
  WinQueryWindowRect (Frame_window, Rectangle);

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle->yTop --; Rectangle->xRight --;

  // ������ �ᯮ������� ����.
  WinQueryWindowPos (Frame_window, Placement);

  // ������.
  return;
}

// ��� �஢����, �� ��������� �� ࠧ��� ���� ࠬ�� ���

// Frame_window - ���� ࠬ��, Frame_rectangle - ࠧ��� ����, Frame_placement - �ᯮ������� ����.
// �����頥��� ���祭��: 1 �᫨ ࠧ��� ࠬ�� �������, ���� 0.
BYTE Painter_FrameRectangleIsChanged (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // �஢��塞, ������� �� ����.
  if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return 1;

  // �஢��塞, ������ �� ����.
  if (!WinIsWindowVisible (Frame_window)) return 1;

  // �஢��塞, �� ��������� �� ࠧ��� ����.
  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  if (Frame_rectangle != NULL)
  {
    RECT Current_rectangle = {0};
    if (!WinQueryWindowRect (Frame_window, &Current_rectangle)) return 1;
    Current_rectangle.yTop --; Current_rectangle.xRight --;

    if (Current_rectangle.xRight != Frame_rectangle->xRight ||
        Current_rectangle.yTop != Frame_rectangle->yTop) return 1;
  }

  // �஢��塞, �� ���������� �� �ᯮ������� ����.
  if (Frame_placement != NULL)
  {
    SWP Current_placement = {0};
    if (!WinQueryWindowPos (Frame_window, &Current_placement)) return 1;

    if (Current_placement.x != Frame_placement->x ||
        Current_placement.y != Frame_placement->y) return 1;
  }

  // ������.
  return 0;
}

// ��� �஢����, ��� �� �訡��, �易���� � SMP ���

// �� ��६���� - ���譨�
BYTE Painter_SMPError (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����७��� �஢�ઠ ��ࠬ��஢.
  if (!Frame_window || !Frame_rectangle) { Painter.Settings.Draw_frames = 0; return 1; }

  // �஢��塞 ࠧ��� ���� ࠬ��.
  if (Painter_FrameRectangleIsChanged (Frame_window, Frame_rectangle, Frame_placement)) return 1;

  // ������.
  return 0;
}

// ��� ����訢��� ᢮������ ����࠭�⢮ ࠬ�� ���

// Presentation_space - ����࠭�⢮ �⮡ࠦ����, Frame_* - ���� ࠬ��, ��� ࠧ��� � �ᯮ�������.
// Wall - �࠭�� ����訢����, Window_is_active - ��࠭� �� ����.
VOID Painter_FillFrameSpace (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, LONG Color, INT Wall, BYTE Window_is_active)
{
  // ����訢��� ࠬ�� �� 2 �� ��।������� �࠭���.
  GpiSetColor (Presentation_space, Color);

  for (INT Offset = 2; Offset < Wall; Offset ++)
  {
    // ���㥬 �����.
    POINT Point = { Offset, Offset };           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Frame_rectangle->yTop - Offset;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Offset;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // ������.
  return;
}

// ��� ����� ������ ���� ࠬ�� ���

// Presentation_space - ����࠭�⢮ �⮡ࠦ����, Frame_* - ���� ࠬ��, ��� ࠧ��� � �ᯮ�������..
VOID Painter_DrawExternalFrame (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ���㥬 ᢥ��� ���� ���譥� ࠬ��.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = { 1, 1 };                if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ⥬��� ���� ���譥� ࠬ��.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ���譥� ࠬ��.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Frame_rectangle->yTop - 1;
  Point.x = Frame_rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = 1; Point.x = 1;              if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // ������.
  return;
}

// ��� ����� ⥭� ��� ࠬ�� ���

// Presentation_space - ����࠭�⢮ �⮡ࠦ����, Frame_* - ���� ࠬ��, ��� ࠧ��� � �ᯮ�������.
VOID Painter_DrawFrameShadow (HPS Presentation_space, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ���㥬 ⥬��� ���� ⥭�.
  GpiSetColor (Presentation_space, CLR_BLACK);

  POINT Point = {0};                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ⥭�.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ������.
  return;
}

// ��� ����� ࠬ�� ��� ���᪮�� ���� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawFlatFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // ������ �ਭ� ࠬ�� ����.
  INT Const_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Const_frame);
  if (!Const_frame) Const_frame = FrameWidth (Frame_window);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Frame_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥭� ��� ࠬ��.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ���㥬 ������ ���� ࠬ��.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ���㥬 ⥬��� ���� ����७��� ࠬ��.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  INT Offset = Const_frame - 1;
  POINT Point = { Offset - 1, Offset - 1 };         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - Offset + 1;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - Offset + 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  Point.x = Frame_rectangle->xRight - Offset;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Offset;                                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Offset;                                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ����७��� ࠬ��.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = Offset; Point.x = Offset;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop - Offset;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight - Offset;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  Point.x = Frame_rectangle->xRight - Offset + 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Offset - 1;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Offset - 1;                           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ����訢��� ᢮������ ����࠭�⢮.
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, SYSCLR_DIALOGBACKGROUND, Offset - 1, Window_is_active);

  // ���㥬 㣮��� ࠬ��.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Frame_rectangle->yTop - Offset;
  Point.x = Frame_rectangle->xRight - Offset;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Offset; Point.x = Offset;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Frame_rectangle->yTop - Offset + 1;
  Point.x = Frame_rectangle->xRight - Offset + 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Offset - 1; Point.x = Offset - 1;     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����� ࠬ�� ��� ���� ����ﭭ��� ࠧ��� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawConstFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // ������ �ਭ� ࠬ�� ����.
  INT Const_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Const_frame);
  if (!Const_frame) Const_frame = FrameWidth (Frame_window);

  // ������ ���� ��������� � ��� ࠧ���.
  HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Frame_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥭� ��� ࠬ��.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ���㥬 ������ ���� ࠬ��.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ����訢��� ᢮������ ����࠭�⢮.
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, SYSCLR_DIALOGBACKGROUND, Const_frame, Window_is_active);

  // ������, ���� �� �ᮢ��� ����७��� ࠬ��.
  BYTE Draw_inner_frame = Painter.Settings.Draw_volume_lines;

  if (Draw_inner_frame)
  {
    // �᫨ � ���� ���� ���� - �ᮢ��� ࠬ�� �� ����.
    if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_inner_frame = 0;

    // �᫨ ���� ��������� �� �������� - �ᮢ��� ࠬ�� �� ����.
    if (!WindowIsPresent (TitleBar_window)) Draw_inner_frame = 0;
  }

  // ���㥬 ࠬ�� ����� ����.
  if (Draw_inner_frame)
  {
    // ����塞 �ᯮ������� �祪.
    INT Width = Frame_rectangle->xRight;
    INT Height = Frame_rectangle->yTop;
    INT Title = TitleBar_rectangle.yTop;
    INT Offset = Const_frame - 1;

    // ���㥬 ⥬��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = { Offset, Height - Offset - Title }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Height - Offset;                         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Width - Offset;                          if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ᢥ��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = Height - Offset - Title - 1;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮��� ���譥� ࠬ��.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Height - Offset; Point.x = Width - Offset;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

    // ����訢��� ᢮������ ����࠭�⢮ 梥⮬ ����.
    GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

    Point.y = Height - Offset - Title - 2;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset;                                  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Height - Offset - Title - 2;             if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����� ࠬ�� � 1 ��� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawPointFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������ ࠧ��� �࠭�.
  INT Y_Screen = WinQuerySysValue (QueryDesktopWindow (), SV_CYSCREEN);

  // �᫨ ���� �������� ���� �࠭, � �� ���⠢�� - ������.
  if (Frame_rectangle->yTop >= Y_Screen - 1) return;

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Frame_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = {0};                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Frame_rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Frame_rectangle->yTop; Point.x = Frame_rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����� ࠬ�� ��� ���筮�� ���� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawNormalFrame (HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // ������ �ਭ� ࠬ�� ����.
  INT Normal_frame = 0; FindProperty (Frame_window, PRP_BORDER, &Normal_frame);
  if (!Normal_frame) Normal_frame = FrameWidth (Frame_window);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Frame_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥭� ��� ࠬ��.
  Painter_DrawFrameShadow (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ���㥬 ������ ���� ࠬ��.
  Painter_DrawExternalFrame (Presentation_space, Frame_window, Frame_rectangle, Frame_placement);

  // ���㥬 ����७��� ���� ࠬ��.
  INT Offset = Normal_frame;

  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_GRAY || Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB)
  {
    // �����蠥� �����.
    Offset --;

    // ���㥬 ⥬��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = { Offset, Offset };           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Frame_rectangle->yTop - Offset;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ᢥ��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮��� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    Point.y = Frame_rectangle->yTop - Offset;
    Point.x = Frame_rectangle->xRight - Offset; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Offset; Point.x = Offset;         if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // ����訢��� ᢮������ ����࠭�⢮.
  LONG Color = SYSCLR_ACTIVEBORDER; if (!Window_is_active) Color = SYSCLR_INACTIVEBORDER;
  Painter_FillFrameSpace (Presentation_space, Frame_window, Frame_rectangle, Frame_placement, Color, Offset, Window_is_active);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����� ࠬ�� ��� ���� ���

// *_window - ���� ࠬ�� � ���������, *_rectangle � *_placement - �� ࠧ����. Frame_type - ��� ࠬ��, Window_is_active - ��࠭� �� ����.
VOID Painter_DrawFrameRectangle (HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, BYTE Window_is_active)
{
  // �᫨ ࠬ�� ����� �� ���� - ������.
  if (!Painter_FrameDrawingIsRequired ()) return;

  // ���㥬 ࠬ��.
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

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ���� ���� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawWindowMenu (HWND Menu_window, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // �᫨ ���� �� �������� - ������.
  if (!WindowIsPresent (Menu_window)) return;

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Menu_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Menu_window, &Rectangle);

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle.yTop --; Rectangle.xRight --;

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_WHITE);

  POINT Point = { 0, 1 };     if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle.yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��. ��� ��� ���� ࠧ������� �����, � ��㥬 ⮫쪮 㣮��� �ࠢ� ������.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  Point.y = Rectangle.yTop; Point.x = Rectangle.xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // ���㥬 ࠧ�������� �����.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = 0; Point.x = 0;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ������ ��אַ㣮�쭨�� ��� ������ ���

// ��६���� - ���� ࠬ�� � ��אַ㣮�쭨��. �����頥��� ���祭�� - ࠧ��� ������.
INT Painter_CalculateButtonRectangles (HWND Frame_window, PRECT Rectangle, HWND TitleBar_window, PRECT TitleBar_rectangle, PRECT Max_button, PRECT Min_button, PRECT Rollup_button, PRECT Close_button, PRECT All_buttons)
{
  // ������ ���ﭨ� ������ � ����.
  LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

  // ������ ����� �� ��� ����, ࠧ���, � ⠪�� ���孨� � ������ �窨 ��אַ㣮�쭨���.
  INT Size = 0; INT Top = 0; INT Bottom = 0;
  INT Offset = 0; FindProperty (Frame_window, PRP_BORDER, &Offset);
  if (!Offset) Offset = FrameWidth (Frame_window);

  // ������ ���� ���������, �᫨ ��� �� �뫮 �����⭮ ��࠭��.
  if (TitleBar_window == NULLHANDLE) TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

  // �᫨ ��� ���� - ᬮ�ਬ �� ��� ࠧ���. ���� - �ᯮ��㥬 ����ன�� ������� �����窨.
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

  // ������ �ᯮ������� �祪.
  Top = Rectangle->yTop - Offset; Bottom = Top - Size;

  // �����⠢������ ���� ��אַ㣮�쭨��.
  RECT Rect[4];
  RECT Rect_0 = { Rectangle->xRight - Offset - Size, Bottom, Rectangle->xRight - Offset, Top };
  RECT Rect_1 = { Rect_0.xLeft - Size - 1,           Bottom, Rect_0.xRight - Size - 1,   Top };
  RECT Rect_2 = { Rect_1.xLeft - Size - 1,           Bottom, Rect_1.xRight - Size - 1,   Top };
  RECT Rect_3 = { Rect_2.xLeft - Size - 1,           Bottom, Rect_2.xRight - Size - 1,   Top };
  memcpy (&Rect[0], &Rect_0, sizeof (RECT));
  memcpy (&Rect[1], &Rect_1, sizeof (RECT));
  memcpy (&Rect[2], &Rect_2, sizeof (RECT));
  memcpy (&Rect[3], &Rect_3, sizeof (RECT));

  // �����⠢������ ��騩 ��אַ㣮�쭨�.
  RECT Border = { 0, Bottom, Rect[0].xRight, Top };

  // �᫨ ������ ��� - ���� ������ ⮫쪮 ��騩 ��אַ㣮�쭨�.
  if (Buttons == NO_ACTION)
  {
    // ��אַ㣮�쭨� ��祣� �� ᮤ�ন�.
    Border.xLeft = Border.xRight + 1; Border.xRight ++;
    if (FrameType (Frame_window) == FT_NOFRAME) Border.xLeft ++;

    if (All_buttons != NULL) memcpy (All_buttons, &Border, sizeof (RECT));

    // ������.
    return Size;
  }

  // ������� ��אַ㣮�쭨�� ���� �ᯮ�짮���� ��� ������.
  INT Quantity = 0;

  // ����ਬ, ��� ���� �ᮢ��� ������ ������� ����.
  BYTE Close_button_rightward = 0; if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Close_button_rightward = 1;

  // �᫨ ������ ������� ���� �ᮢ��� ᫥��, �:
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
  // � �᫨ �� ���� �ᮢ��� �ࠢ�, �:
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

  // ������ ��אַ㣮�쭨� ��� ��� ������.
  switch (Quantity)
  {
    case 1: Border.xLeft = Rect[0].xLeft; break;
    case 2: Border.xLeft = Rect[1].xLeft; break;
    case 3: Border.xLeft = Rect[2].xLeft; break;
    case 4: Border.xLeft = Rect[3].xLeft; break;
  }

  if (All_buttons != NULL) memcpy (All_buttons, &Border, sizeof (RECT));

  // ������.
  return Size;
}

// ��� ����� ������ � �ࠢ�� ���孥� 㣫� ���� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawButtons (HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, HWND TitleBar_window)
{
  // �᫨ ���� ��������� �� �������� - ������.
  if (!WindowIsPresent (TitleBar_window)) return;

  // ������ ࠧ��� ���� ���������
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // ������ ��אַ㣮�쭨�� ��� ������.
  RECT Max_button = {0}; RECT Min_button = {0}; RECT Rollup_button = {0};
  RECT Close_button = {0}; RECT All_buttons = {0};
  INT Size = Painter_CalculateButtonRectangles (Frame_window, Frame_rectangle, TitleBar_window, &TitleBar_rectangle, &Max_button, &Min_button, &Rollup_button, &Close_button, &All_buttons);

  // �᫨ ������ ��� - ������.
  if (All_buttons.xRight - All_buttons.xLeft < 3) return;
  if (All_buttons.yTop - All_buttons.yBottom < 3) return;

  // ������, ��� �룫廊� ࠬ�� ����, �᫨ �� �ॡ����.
  if (Frame_type == FT_UNKNOWN) Frame_type = FrameType (Frame_window);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Frame_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ������ ����� �� ��� ������.
  INT Pixel_margin = Painter_GetButtonPixelMargin ();

  // ������, ���� �� �ᮢ��� ⥭�, �᫨ ������ �����.
  BYTE Draw_lines = 1;

  if (Pixel_margin == 0)
  {
    // �᫨ � ���� ࠬ�� � ���� ��� - �� ��㥬 ⥭�.
    if (Painter.RTSettings.Selected_button)
     if (Frame_type == FT_POINT) Draw_lines = 0;

    // �᫨ � ���� ࠬ�� ����ﭭ��� ࠧ���:
    if (Painter.RTSettings.Selected_button)
     if (Frame_type == FT_CONST)
     {
       // �᫨ � ���� ��� ����७��� ࠬ�� - �� ��㥬 ⥭�.
       if (!Painter.Settings.Draw_volume_lines) Draw_lines = 0;
       // �᫨ � ���� ���� ���� - �� ��㥬 ⥭�.
       else if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_lines = 0;
     }
  }

  // �����⠢������ ��אַ㣮�쭨�� ��� ������. ����ન���� �� ��ꥬ, ��㥬 ⥭�.
  for (INT Count = 0; Count < 4; Count ++)
  {
    // �롨ࠥ� ��אַ㣮�쭨�.
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

    // �᫨ ������ �ᮢ��� �� ���� - �த������ ��ॡ��.
    if (Current_button == NULL) continue;

    // ���㥬 ᢥ��� ���� ࠬ��, ��� ⥭�, �᫨ ������ �����.
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

    // ���㥬 ⥬��� ���� ࠬ�� ��� ����訢��� ᢮������ ����࠭�⢮.
    if (!Button_is_pressed) GpiSetColor (Presentation_space, CLR_DARKGRAY);
    else GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE);

    Point.y = Current_button->yBottom + Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Current_button->xLeft + Pixel_margin;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮���.
    Color = SYSCLR_BUTTONMIDDLE;
    if (Button_is_pressed) if (Draw_lines) Color = CLR_DARKGRAY;
    GpiSetColor (Presentation_space, Color);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Current_button->yTop - Pixel_margin;
    Point.x = Current_button->xRight - Pixel_margin;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

    // ���㥬 ������ ࠬ��.
    if (Pixel_margin != 0)
    {
      // ���㥬 ᢥ��� ���� ���譥� ࠬ��.
      GpiSetColor (Presentation_space, CLR_WHITE);

      Point.y = Current_button->yBottom;
      Point.x = Current_button->xLeft;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Current_button->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.y = Current_button->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

      // ���㥬 ⥬��� ���� ���譥� ࠬ��.
      GpiSetColor (Presentation_space, CLR_DARKGRAY);

      Point.x = Current_button->xLeft;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.y = Current_button->yBottom; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

      // ���㥬 㣮���.
      GpiSetColor (Presentation_space, CLR_PALEGRAY);

      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
      Point.y = Current_button->yTop; Point.x = Current_button->xRight;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    }

    // �᫨ ������ ����� - ᤢ����� ����ࠦ���� ���� � ��ࠢ�.
    if (Button_is_pressed)
    {
      // �������� ����ࠦ����.
      Current_button->xLeft ++; Current_button->xRight ++;
      Current_button->yBottom --; Current_button->yTop --;

      // ����訢��� ᢮������ ����࠭�⢮.
      LONG Color = SYSCLR_BUTTONMIDDLE;
      GpiSetColor (Presentation_space, Color);

      Point.x = Current_button->xLeft + Pixel_margin;
      Point.y = Current_button->yBottom + Pixel_margin + 1;
      if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);

      Point.y = Current_button->yTop - Pixel_margin;       if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
      Point.x = Current_button->xRight - Pixel_margin - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }
  }

  // ������ ࠧ���� ����ࠦ����.
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

  // ���㥬 ������ 㢥��祭�� ����.
  if (Max_button.yTop)
  {
    // ����訢��� ᢮������ ����࠭�⢮.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // ������ ��אַ㣮�쭨�.
    Rectangle.xLeft = Max_button.xLeft + 1;     Rectangle.xRight = Max_button.xRight - 1;
    Rectangle.yBottom = Max_button.yBottom + 1; Rectangle.yTop = Max_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // ����訢��� ���.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // ���㥬 �����.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // �᫨ ���� 㢥��祭� - 㬥��蠥� ��אַ㣮�쭨�.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    if (Buttons & RESTORE_ACTION)
    {
      Max_button.xLeft ++; Max_button.xRight --; Max_button.yBottom ++; Max_button.yTop --;
    }

    // ���㥬 ����ࠦ����.
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

  // ���㥬 ������ 㬥��襭�� ��� ᮪���� ����.
  if (Min_button.yTop)
  {
    // ����訢��� ᢮������ ����࠭�⢮.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // ������ ��אַ㣮�쭨�.
    Rectangle.xLeft = Min_button.xLeft + 1;     Rectangle.xRight = Min_button.xRight - 1;
    Rectangle.yBottom = Min_button.yBottom + 1; Rectangle.yTop = Min_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // ����訢��� ���.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // ���㥬 �����.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // ���㥬 ����ࠦ����.
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

  // ���㥬 ������ "����� ������".
  if (Rollup_button.yTop)
  {
    // ����訢��� ᢮������ ����࠭�⢮.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // ������ ��אַ㣮�쭨�.
    Rectangle.xLeft = Rollup_button.xLeft + 1;     Rectangle.xRight = Rollup_button.xRight - 1;
    Rectangle.yBottom = Rollup_button.yBottom + 1; Rectangle.yTop = Rollup_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // ����訢��� ���.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // ���㥬 �����.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // �᫨ ���� 㢥��祭� - 㬥��蠥� ��אַ㣮�쭨�.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    if (Icon_size == 'L') if (Buttons & RESTORE_ACTION)
    {
      Rollup_button.yBottom ++; Rollup_button.yTop --;
    }

    // ���㥬 ����ࠦ����.
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

  // ���㥬 ������ �������.
  if (Close_button.yTop)
  {
    // ����訢��� ᢮������ ����࠭�⢮.
    GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE); RECT Rectangle = {0};

    // ������ ��אַ㣮�쭨�.
    Rectangle.xLeft = Close_button.xLeft + 1;     Rectangle.xRight = Close_button.xRight - 1;
    Rectangle.yBottom = Close_button.yBottom + 1; Rectangle.yTop = Close_button.yTop - 1;

    if (Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW)
    {
      Rectangle.xLeft ++;   Rectangle.xRight --; Rectangle.yBottom ++; Rectangle.yTop --;
    }

    // ����訢��� ���.
    for (INT Count = Rectangle.yBottom; Count <= Rectangle.yTop; Count ++)
    {
      // ���㥬 �����.
      POINT Point = { Rectangle.xLeft, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
      Point.x = Rectangle.xRight;               if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    }

    // ���㥬 ����ࠦ����.
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

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ������ ��אַ㣮�쭨� ��� ��ப� ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_CalculateTitleRectangle (HPS Presentation_space, HWND TitleBar_window, PRECT TitleBar_rectangle, HWND Frame_window, PRECT Frame_rectangle, BYTE Window_is_active, BYTE Advanced_controls, PCHAR Window_title, PRECT Title_rectangle, PLONG Text_attributes)
{
  // ������ �ᯮ������� ���� ��������� � ���� ࠬ��.
  SWP TitleBar_placement = {0}; WinQueryWindowPos (TitleBar_window, &TitleBar_placement);

  // ������ ࠧ��� ��אַ㣮�쭨��, ����� ���ॡ���� ��� �ᮢ���� ��ப�.
  INT Length = strlen (Window_title); POINT Text_box_points[TXTBOX_COUNT];
  GpiQueryTextBox (Presentation_space, Length, Window_title, TXTBOX_COUNT, Text_box_points);

  // ��ਭ� ��ப�.
  INT String_width = Text_box_points[TXTBOX_TOPRIGHT].x - Text_box_points[TXTBOX_BOTTOMLEFT].x;

  // ����� ᫥�� � �ࠢ� ����� ���������.
  INT Margin = TitleBar_rectangle->yTop / 2;

  // �����ﭨ� � ���� ࠬ�� �� ��砫� ��ப�.
  INT Space = (Frame_rectangle->xRight - String_width) / 2;
  INT Min_space = TitleBar_placement.x + Margin;
  if (Space < Min_space) Space = Min_space;

  // ������ ��ࠢ������� ��� ⥪��.
  LONG Defined_alignment = DT_CENTER;

  if (Painter.Settings.Theme == PAINTER_THEME_PHOENIX ||
      Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION ||
      Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW) Defined_alignment = DT_LEFT;

  // �������� ���� ��ࠢ������ �� �।��� ���� ���������, �� �᫨ �ࠢ� �� ����
  // ���� �� �����-� ����, � �������� ���� ��ࠢ������ �� �।��� ���� ࠬ��.
  BYTE Binding_to_TitleBar = 1; LONG Alignment_in_rectangle = 0;

  // �᫨ ��ப� �����, 祬 ���� ���������, � �� �ਤ���� ��஢���� �� ������ ���.
  if (String_width > TitleBar_rectangle->xRight - Margin * 2)
  {
    Alignment_in_rectangle = DT_LEFT;
  }
  // ����:
  else
  {
    // ������ ⥪�� ����� ���� �ਢ易� �� � ���������, � � ࠬ�� ����.
    BYTE Text_can_be_unbinded = 0;

    // �᫨ �冷� � ���������� ��� �������⥫��� ����:
    if (!Advanced_controls)
    {
      // ����� �㤥� ��஢��� ⠪, ��� ������ �� 㬮�砭��.
      Alignment_in_rectangle = Defined_alignment;

      // �᫨ ���� �� ����� ������ � �ࠢ�� ���孥� 㣫� � ��� �� ���� ���ᮢ��� - ⥪�� ����� �� �ਢ�뢠�� � ���������.
      if (Defined_alignment == DT_CENTER)
       if (!Painter.Settings.Draw_buttons)
        if (WinWindowFromID (Frame_window, FID_MINMAX) == NULLHANDLE)
         Text_can_be_unbinded = 1;
    }
    // � �᫨ ⠪�� ���� ����:
    else
    {
      // �᫨ ⥪�� ���� ��ࠢ������ �� �।���:
      if (Defined_alignment == DT_CENTER)
      {
        // ����� �㤥� ��஢��� �� �ࠢ��� ��� ��אַ㣮�쭨��.
        Alignment_in_rectangle = DT_RIGHT;

        // ����� ����� �� �ਢ�뢠�� � ���������.
        Text_can_be_unbinded = 1;
      }
    }

    // �᫨ ��ப� �� �멤�� �� �।��� ���������, �� ����� �ਢ易�� � ���� ࠬ��.
    if (Text_can_be_unbinded)
     if (Space + String_width < TitleBar_placement.x + TitleBar_placement.cx - Margin)
      Binding_to_TitleBar = 0;
  }

  // �᫨ ���� �ਢ易���� � ���� ���������:
  if (Binding_to_TitleBar)
  {
    // ��אַ㣮�쭨� ��� ��ப� - �� ���� ��������� � ��⮬ ����㯠.
    Title_rectangle->xLeft = TitleBar_rectangle->xLeft + Margin;
    Title_rectangle->xRight = TitleBar_rectangle->xRight - Margin;

    // ��ࠢ������� ⥪�� �뫮 ��।����� ��࠭��.
    *Text_attributes |= Alignment_in_rectangle;
  }
  // � �᫨ �ਢ�뢠���� � ���� ��������� �� ����:
  else
  {
    // ��אַ㣮�쭨� �㤥� �ᯮ����� ����� ���� ࠬ��.
    // ��ࠢ������� ⥪�� � �⮬ ��砥 㦥 �� ����� ���祭��.
    Title_rectangle->xLeft = Space - TitleBar_placement.x;
    Title_rectangle->xRight = Title_rectangle->xLeft + String_width;
  }

  // ������.
  return;
}

// ��� ����⠭�������� � ���� ��������� 梥� �� 㬮�砭�� ���

// TitleBar_window - ���� ���������.
VOID Painter_ResetTitleBarColors (HWND TitleBar_window)
{
  // ������, �뫨 �� ������ ��� ���� ��������� ��㣨� 梥�.
  ULONG Color = 0;

  ULONG FG_Attribute_is_exists = 0; WinQueryPresParam (TitleBar_window, PP_ACTIVETEXTFGNDCOLORINDEX, 0, &FG_Attribute_is_exists, sizeof (ULONG), &Color, QPF_ID1COLORINDEX | QPF_NOINHERIT);
  ULONG BG_Attribute_is_exists = 0; WinQueryPresParam (TitleBar_window, PP_ACTIVECOLORINDEX, 0, &BG_Attribute_is_exists, sizeof (ULONG), &Color, QPF_ID1COLORINDEX | QPF_NOINHERIT);

  // �᫨ ��� �뫨 ������ - ���뢠�� ��.
  if (FG_Attribute_is_exists || BG_Attribute_is_exists)
  {
    // ����頥� ���������� ����.
    WinEnableWindowUpdate (TitleBar_window, 0);

    // ����塞 ������� ����⥫�� 梥�.
    WinRemovePresParam (TitleBar_window, PP_ACTIVECOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_ACTIVETEXTBGNDCOLORINDEX);

    WinRemovePresParam (TitleBar_window, PP_INACTIVECOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_INACTIVETEXTBGNDCOLORINDEX);

    WinRemovePresParam (TitleBar_window, PP_ACTIVETEXTFGNDCOLORINDEX);
    WinRemovePresParam (TitleBar_window, PP_INACTIVETEXTFGNDCOLORINDEX);

    // ����蠥� ���������� ����.
    WinEnableWindowUpdate (TitleBar_window, 1);
  }

  // ������.
  return;
}

// ��� ����� ���⨭�� � ����� ���孥� 㣫� ���� ���

// �� ��६���� - ���譨�, SysMenu_is_pressed, SysMenu_is_used - ���짮��⥫� ����� �� ���⨭�� � ������� ���.
VOID Painter_DrawSystemMenu (HWND SysMenu_window, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement, HPOINTER Icon, LONG Frame_type, BYTE SysMenu_is_pressed)
{
  // �᫨ ���⨭�� �������⭠ - ������.
  if (Icon == NULLHANDLE) return;

  // �᫨ ���� �� �������� - ������.
  if (!WindowIsPresent (SysMenu_window)) return;

  // ������, ��� �룫廊� ࠬ�� ����, �᫨ �� �ॡ����.
  if (Frame_type == FT_UNKNOWN) Frame_type = FrameType (Frame_window);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (SysMenu_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (SysMenu_window, &Rectangle);

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle.yTop --; Rectangle.xRight --;

  // ����訢��� ���⨭��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONMIDDLE);

  for (INT Count = 0; Count <= Rectangle.yTop; Count ++)
  {
    // ���㥬 �����.
    POINT Point = { 0, Count }; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // ���㥬 ���箪. �᫨ ���⨭�� ����� - ᤢ����� ��.
  INT X = 1; INT Y = 1; if (SysMenu_is_pressed) { X = 2; Y = 0; }
  WinDrawPointer (Presentation_space, X, Y, Icon, DP_MINIICON);

  // ������ ����� �� ��� ���⨭��.
  INT Pixel_margin = Painter_GetButtonPixelMargin ();

  // ������, ���� �� �ᮢ��� ⥭�, �᫨ ���⨭�� �����.
  BYTE Draw_lines = 1;

  if (Pixel_margin == 0)
  {
    // �᫨ � ���� ࠬ�� � ���� ��� - �� ��㥬 ⥭�.
    if (SysMenu_is_pressed)
     if (Frame_type == FT_POINT) Draw_lines = 0;

    // �᫨ � ���� ࠬ�� ����ﭭ��� ࠧ���:
    if (SysMenu_is_pressed)
     if (Frame_type == FT_CONST)
     {
       // �᫨ � ���� ��� ����७��� ࠬ�� - �� ��㥬 ⥭�.
       if (!Painter.Settings.Draw_volume_lines) Draw_lines = 0;
       // �᫨ � ���� ���� ���� - �� ��㥬 ⥭�.
       else if (WinWindowFromID (Frame_window, FID_MENU) != NULLHANDLE) Draw_lines = 0;
     }
  }

  // ���㥬 ᢥ��� ���� ࠬ��, ��� ⥭�, �᫨ ���⨭�� �����.
  POINT Point = { Pixel_margin, Pixel_margin };

  if (!(SysMenu_is_pressed && !Draw_lines))
  {
    if (!SysMenu_is_pressed) GpiSetColor (Presentation_space, CLR_WHITE);
    else GpiSetColor (Presentation_space, CLR_DARKGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle.yTop - Pixel_margin;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle.xRight - Pixel_margin; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // ���㥬 ⥬��� ���� ࠬ�� � 㣮���, �᫨ ���⨭�� �� �����.
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

  // ���㥬 ������ ࠬ��.
  if (Pixel_margin != 0)
  {
    // ���㥬 ᢥ��� ���� ���譥� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = 0; Point.x = 0;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle.xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Rectangle.yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ⥬��� ���� ���譥� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮���.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle.yTop; Point.x = Rectangle.xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ���������, ����� ��� ��嬥�� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawVTVControlVolumeLines (HWND TitleBar_window, PRECT Rectangle, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // �᫨ ���� ࠬ�� �� ��࠭� - ����ન���� ��ꥬ.
  if (!Window_is_active)
  {
    // ���㥬 ⥬��� ���� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ᢥ��� ���� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ⥬��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.x = 1; Point.y = 1;        if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.x = Rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = Rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ᢥ��� ���� ����७��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    Point.x = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop - 1; Point.x = Rectangle->xRight - 1;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = 0; Point.x = 0;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }
  // � �᫨ ���� ��࠭� - ��㥬 ��אַ㣮�쭨�.
  else
  {
    GpiSetColor (Presentation_space, Color);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawOS4TitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.x = 1; Point.y = 1;        if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop - 1;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.x = Rectangle->xRight; Point.y = Rectangle->yTop - 1; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = 0; Point.x = Rectangle->xRight;                   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0;                                                if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  Point.x = Rectangle->xRight - 1; Point.y = Rectangle->yTop - 2; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = 1;                                                    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 1;                                                    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

  Point.y = 0; Point.x = 0;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = 1; Point.x = 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop - 1; Point.x = Rectangle->xRight - 1;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawLionTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_DIALOGBACKGROUND);

  Point.y = 0; Point.x = 0;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawECSTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONDARK);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, SYSCLR_BUTTONLIGHT);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��.
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

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawSnowTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���㥬 ⥬��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_DARKGRAY);

  POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
  Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 ᢥ��� ���� ࠬ��.
  GpiSetColor (Presentation_space, CLR_WHITE);

  Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

  // ���㥬 㣮��� ࠬ��.
  GpiSetColor (Presentation_space, CLR_PALEGRAY);

  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
  if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawClassicTitleBarVolumeLines (HWND TitleBar_window, PRECT Rectangle, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // �᫨ ���� ࠬ�� �� ��࠭� - ����ન���� ��ꥬ.
  if (!Window_is_active)
  {
    // ���㥬 ᢥ��� ���� ࠬ��.
    GpiSetColor (Presentation_space, CLR_WHITE);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 ⥬��� ���� ࠬ��.
    GpiSetColor (Presentation_space, CLR_DARKGRAY);

    Point.y = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);

    // ���㥬 㣮��� ࠬ��.
    GpiSetColor (Presentation_space, CLR_PALEGRAY);

    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
    Point.y = Rectangle->yTop; Point.x = Rectangle->xRight;
    if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiSetPel (Presentation_space, &Point);
  }
  // � �᫨ ���� ��࠭� - ��㥬 ��אַ㣮�쭨�.
  else
  {
    GpiSetColor (Presentation_space, Color);

    POINT Point = {0};           if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiMove (Presentation_space, &Point);
    Point.y = Rectangle->yTop;   if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = Rectangle->xRight; if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.y = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
    Point.x = 0;                 if (!Painter_SMPError (Frame_window, Frame_rectangle, Frame_placement)) GpiLine (Presentation_space, &Point);
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ����ન���� ��ꥬ ���� ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawTitleBarVolumeLines (HWND TitleBar_window, LONG Frame_type, PRECT Rectangle, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������ �ࠢ��� �ᮢ���� � ����ᨬ��� �� ��࠭��� ⥬� ��� ࠬ��.
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

  // ����ન���� ��ꥬ ����.
  if (Draw_OS4_lines) Painter_DrawOS4TitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_Lion_lines) Painter_DrawLionTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_eCS_lines) Painter_DrawECSTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_classic_lines) Painter_DrawClassicTitleBarVolumeLines (TitleBar_window,  Rectangle, -1, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_Snow_lines) Painter_DrawSnowTitleBarVolumeLines (TitleBar_window, Rectangle, Frame_window, Frame_rectangle, Frame_placement);
  if (Draw_VTV_lines) Painter_DrawVTVControlVolumeLines (TitleBar_window, Rectangle, -1, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);

  // ������.
  return;
}

// ��� �������� ���� ���������, �ᯮ���� ��אַ㣮�쭨�� ���

// �� ��६���� - ���譨�.
VOID Painter_FillGlassTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������塞 ����ࠦ���� ��אַ㣮�쭨����.
  switch (Painter.Settings.Theme)
  {
    case PAINTER_THEME_CLASSIC_RGB:
    {
      // �롨ࠥ� 梥�.
      LONG Color_1 = Painter.Settings.AT_Color_1; LONG Color_2 = Painter.Settings.AT_Color_2; LONG Color_3 = Painter.Settings.AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.IT_Color_1; Color_2 = Painter.Settings.IT_Color_2; Color_3 = Painter.Settings.IT_Color_3; }

      switch (GetCurrentOrNextRoom ())
      {
        case NORTHERN_ROOM:{ Color_1 = Painter.Settings.Northern_AT_Color_1; Color_2 = Painter.Settings.Northern_AT_Color_2; Color_3 = Painter.Settings.Northern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Northern_IT_Color_1; Color_2 = Painter.Settings.Northern_IT_Color_2; Color_3 = Painter.Settings.Northern_IT_Color_3; }} break;
        case WESTERN_ROOM: { Color_1 = Painter.Settings.Western_AT_Color_1; Color_2 = Painter.Settings.Western_AT_Color_2; Color_3 = Painter.Settings.Western_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Western_IT_Color_1; Color_2 = Painter.Settings.Western_IT_Color_2; Color_3 = Painter.Settings.Western_IT_Color_3; }} break;
        case EASTERN_ROOM: { Color_1 = Painter.Settings.Eastern_AT_Color_1; Color_2 = Painter.Settings.Eastern_AT_Color_2; Color_3 = Painter.Settings.Eastern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Eastern_IT_Color_1; Color_2 = Painter.Settings.Eastern_IT_Color_2; Color_3 = Painter.Settings.Eastern_IT_Color_3; }} break;
        case SOUTHERN_ROOM:{ Color_1 = Painter.Settings.Southern_AT_Color_1; Color_2 = Painter.Settings.Southern_AT_Color_2; Color_3 = Painter.Settings.Southern_AT_Color_3; if (!Window_is_active) { Color_1 = Painter.Settings.Southern_IT_Color_1; Color_2 = Painter.Settings.Southern_IT_Color_2; Color_3 = Painter.Settings.Southern_IT_Color_3; }} break;
      }

      // ������뢠�� 梥⮢� ���室�.
      INT Red_delta = REDFROMRGB (Color_2) - REDFROMRGB (Color_1);
      INT Green_delta = GREENFROMRGB (Color_2) - GREENFROMRGB (Color_1);
      INT Blue_delta = BLUEFROMRGB (Color_2) - BLUEFROMRGB (Color_1);

      // ������뢠�� ����ﭨ�.
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

      // ���㥬 ��אַ㣮�쭨��.
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
      // �롨ࠥ� 梥�.
      LONG Color_1 = Painter.Settings.AT_Color_2; LONG Color_2 = Painter.Settings.IT_Color_2;

      switch (GetCurrentOrNextRoom ())
      {
        case NORTHERN_ROOM:{ Color_1 = Painter.Settings.Northern_AT_Color_2; Color_2 = Painter.Settings.Northern_IT_Color_2; } break;
        case WESTERN_ROOM: { Color_1 = Painter.Settings.Western_AT_Color_2;  Color_2 = Painter.Settings.Western_IT_Color_2; } break;
        case EASTERN_ROOM: { Color_1 = Painter.Settings.Eastern_AT_Color_2;  Color_2 = Painter.Settings.Eastern_IT_Color_2; } break;
        case SOUTHERN_ROOM:{ Color_1 = Painter.Settings.Southern_AT_Color_2; Color_2 = Painter.Settings.Southern_IT_Color_2; } break;
      }

      // ������뢠�� 梥⮢� ���室�.
      INT Red_delta = REDFROMRGB (Color_2) - REDFROMRGB (Color_1);
      INT Green_delta = GREENFROMRGB (Color_2) - GREENFROMRGB (Color_1);
      INT Blue_delta = BLUEFROMRGB (Color_2) - BLUEFROMRGB (Color_1);

      // ������뢠�� ����ﭨ�.
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

      // ���㥬 ��אַ㣮�쭨��.
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

  // ������.
  return;
}

// ��� �������� ����, �ᯮ���� ����ࠦ���� ���

// �� ��६���� - ���譨�.
VOID Painter_FillNeonTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������� ����࠭�⢮ �⮡ࠦ���� � �����.
  HPS Drawing_memory_space = CreatePresentationSpace (Enhancer.Application);

  // ��७�ᨬ ����ࠦ���� � ����.
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

  // ����塞 ����࠭�⢮ �⮡ࠦ����.
  GpiDestroyPS (Drawing_memory_space); Drawing_memory_space = NULLHANDLE;

  // ������.
  return;
}

// ��� �������� ���� ��������� ࠧ�묨 梥⠬� ���

// �� ��६���� - ���譨�.
VOID Painter_FillNeonOrGlassTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������塞 ���� ���������.
  if (!Painter_GlassTitleBarIsRequired ())
   Painter_FillNeonTitleBar (TitleBar_window, Presentation_space, Rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  else
   Painter_FillGlassTitleBar (TitleBar_window, Presentation_space, Rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);

  // ������.
  return;
}

// ��� ����訢��� ���� � ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_FillControl (HPS Presentation_space, PRECT Rectangle, LONG Color, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����訢��� ����. ���祭�� Rectangle �뫨 㬥��襭� �� �������.
  GpiSetColor (Presentation_space, Color);

  // ���㥬 �����.
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

  // ������.
  return;
}

// ��� �������� ���� ��������� ����� 梥⮬ ���

// �� ��६���� - ���譨�.
VOID Painter_FillTitleBar (HWND TitleBar_window, HPS Presentation_space, PRECT Rectangle, BYTE Window_is_active, INT Pixel_margin, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // �롨ࠥ� 梥�.
  LONG Background_color = Painter.Settings.AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.IT_Background_color;

  INT Room = GetCurrentOrNextRoom ();

  if (Room == NORTHERN_ROOM) { Background_color = Painter.Settings.Northern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Northern_IT_Background_color; }
  if (Room == WESTERN_ROOM) { Background_color = Painter.Settings.Western_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Western_IT_Background_color; }
  if (Room == EASTERN_ROOM) { Background_color = Painter.Settings.Eastern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Eastern_IT_Background_color; }
  if (Room == SOUTHERN_ROOM) { Background_color = Painter.Settings.Southern_AT_Background_color; if (!Window_is_active) Background_color = Painter.Settings.Southern_IT_Background_color; }

  // ����訢��� ���������.
  Painter_FillControl (Presentation_space, Rectangle, Background_color, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);

  // ������.
  return;
}

// ��� ����� ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_DrawTitleBar (HWND TitleBar_window, HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, PCHAR Window_title, BYTE Window_is_active, BYTE Advanced_controls)
{
  // �᫨ ���� �� �������� - ������.
  if (!WindowIsPresent (TitleBar_window)) return;

  // ������ ࠧ��� ���� ���������
  RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  TitleBar_rectangle.yTop --; TitleBar_rectangle.xRight --;

  // ����ન���� ��ꥬ ���� ���������.
  BYTE Volume_lines_are_drawn = 0;
  if (!Painter_NeonTitleBarIsRequired (Window_is_active))
  {
    Painter_DrawTitleBarVolumeLines (TitleBar_window, Frame_type, &TitleBar_rectangle, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
    Volume_lines_are_drawn = 1;
  }

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ������ ��� ⥪��.
  LONG Text_attributes = DT_TEXTATTRS;

  BYTE Allow_mnemonic_characters = 1; INT Count = 0;
  while (Window_title[Count] != 0)
  {
    if (Window_title[Count] == '~') Allow_mnemonic_characters = 0;
    Count ++;
  }

  if (Allow_mnemonic_characters) Text_attributes |= DT_MNEMONIC;

  // ������ ��אַ㣮�쭨� ��� ��ப� ���������.
  INT Pixel_margin = Painter_GetTitleBarPixelMargin (Painter.Settings.Theme, Frame_window, Window_is_active);

  RECT Title_rectangle = { 0, 0, 0, TitleBar_rectangle.yTop };
  Painter_CalculateTitleRectangle (Presentation_space, TitleBar_window, &TitleBar_rectangle, Frame_window, Frame_rectangle, Window_is_active, Advanced_controls, Window_title, &Title_rectangle, &Text_attributes);

  // ����뢠�� ������� 梥⮢ ��� ���� ���������.
  ForceColorPaletteToRGB (Presentation_space);

  // ����訢��� ���������.
  if (Painter_TitleBarIsGrayed (Window_is_active))
  {
    Painter_FillTitleBar (TitleBar_window, Presentation_space, &TitleBar_rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  }
  else
  {
    Painter_FillNeonOrGlassTitleBar (TitleBar_window, Presentation_space, &TitleBar_rectangle, Window_is_active, Pixel_margin, Frame_window, Frame_rectangle, Frame_placement);
  }

  // �᫨ ���� ����ન���� ��ꥬ ��������� � ���� ��࠭� - ��।������ ��ப� ���� � ��ࠢ�.
  // �ਬ��⥫쭮, �� ���짮��⥫� ����� ���������� � �� ᠬ��, �᫨ �㤥� ���ᮢ��� ⥭�.
  BYTE Move_title = 0;

  if (Painter.Settings.Theme == PAINTER_THEME_CLASSIC_GRAY || Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB)
   if (Window_is_active || !Painter_PermissionForCompleteDrawing (Frame_window))
    Move_title = 1;

  if (Move_title)
  {
    Title_rectangle.xLeft ++; Title_rectangle.xRight ++;
    Title_rectangle.yBottom --; Title_rectangle.yTop --;
  }

  // ��ப� ���� ��������� �᫨ ��������� ����� �����ண� ࠧ���.
  if (Title_rectangle.yTop - Title_rectangle.yBottom > 20)
  {
    Title_rectangle.yBottom --; Title_rectangle.yTop --;
  }

  // �᫨ ���� ��������� �� �� ����:
  if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
  {
    // �롨ࠥ� 梥�.
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

    // �᫨ ���� �ᮢ��� 3D ⥪��:
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
      // ������ ��אַ㣮�쭨� ��� ⥪��.
      RECT A3D_rectangle = {0}; memcpy (&A3D_rectangle, &Title_rectangle, sizeof (RECT));
      A3D_rectangle.xLeft --; A3D_rectangle.xRight --; A3D_rectangle.yBottom ++; A3D_rectangle.yTop ++;

      // ���㥬 ⥬�� ⥪�� ��� ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_WHITE);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &A3D_rectangle, 0, 0, Text_attributes);

      // ������ ��אַ㣮�쭨� ��� ⥪��.
      A3D_rectangle.xLeft ++; A3D_rectangle.xRight ++; A3D_rectangle.yBottom --; A3D_rectangle.yTop --;

      // ���㥬 ᢥ�� ⥪�� ��� ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_DARKGRAY);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &A3D_rectangle, 0, 0, Text_attributes);
    }

    if (Draw_V3D_text)
    {
      // ������ ��אַ㣮�쭨� ��� ⥪��.
      RECT V3D_rectangle = {0}; memcpy (&V3D_rectangle, &Title_rectangle, sizeof (RECT));
      V3D_rectangle.xLeft ++; V3D_rectangle.xRight ++; V3D_rectangle.yBottom --; V3D_rectangle.yTop --;

      // ���㥬 ⥬�� ⥪�� ��� ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_WHITE);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &V3D_rectangle, 0, 0, Text_attributes);

      // ������ ��אַ㣮�쭨� ��� ⥪��.
      V3D_rectangle.xLeft --; V3D_rectangle.xRight --; V3D_rectangle.yBottom ++; V3D_rectangle.yTop ++;

      // ���㥬 ᢥ�� ⥪�� ��� ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_DARKGRAY);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &V3D_rectangle, 0, 0, Text_attributes);
    }

    // �᫨ ���� �ᮢ��� ⥭�:
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
      // ������ ��אַ㣮�쭨� ��� ⥭�.
      RECT Shadow_rectangle = {0}; memcpy (&Shadow_rectangle, &Title_rectangle, sizeof (RECT));
      Shadow_rectangle.xLeft ++; Shadow_rectangle.xRight ++; Shadow_rectangle.yBottom --; Shadow_rectangle.yTop --;

      // ���㥬 ⥭� ��� ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, RGB_BLACK);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &Shadow_rectangle, 0, 0, Text_attributes);
    }

    // �᫨ �ᮢ��� 3D ⥪�� �� ����:
    if (!Draw_A3D_text) if (!Draw_V3D_text)
    {
      // ���㥬 ��ப� ���������.
      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       GpiSetColor (Presentation_space, Text_color);

      if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
       WinDrawText (Presentation_space, -1, Window_title, &Title_rectangle, 0, 0, Text_attributes);
    }
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ����ન���� ��ꥬ ���� ���������, �᫨ �� �� �뫮 ᤥ���� ࠭��.
  if (!Volume_lines_are_drawn)
  {
    if (WinIsWindow (WinQueryAnchorBlock (TitleBar_window), TitleBar_window))
    {
      Painter_DrawTitleBarVolumeLines (TitleBar_window, Frame_type, &TitleBar_rectangle, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
    }
  }

  // ������.
  return;
}

// ��� �।���⥫쭮 ����訢��� ����, �ᯮ���� ����ࠦ���� ��� ��אַ㣮�쭨�� ���

// �� ��६���� - ���譨�.
VOID Painter_PreDrawNeonOrGlassTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle.yTop --; Rectangle.xRight --;

  // ����㯠�� �� ��� ���� �� �ॡ����.
  INT No_margin = 0;

  // ����뢠�� ������� 梥⮢ ��� ���� ���������.
  ForceColorPaletteToRGB (Presentation_space);

  // ����訢��� ��������� ����.
  Painter_FillNeonOrGlassTitleBar (TitleBar_window, Presentation_space, &Rectangle, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� �।���⥫쭮 ����訢��� ���� ���������, �ᯮ���� ���� 梥� ���

// �� ��६���� - ���譨�.
VOID Painter_PreDrawGrayedTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (TitleBar_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle.yTop --; Rectangle.xRight --;

  // ����㯠�� �� ��� ���� �� �ॡ����.
  INT No_margin = 0;

  // ����뢠�� ������� 梥⮢ ��� ���� ���������.
  ForceColorPaletteToRGB (Presentation_space);

  // ����訢��� ��������� ����.
  Painter_FillTitleBar (TitleBar_window, Presentation_space, &Rectangle, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� �।���⥫쭮 ����訢��� ���� ��������� ���

// Control_window - ���� �� ���� � ���������, Color - 梥�, Window_is_active - ��࠭� �� ���� ࠬ��, Frame_* - ���� ࠬ�� � ��� ࠧ���/�ᯮ�������.
VOID Painter_PreDrawControl (HWND Control_window, LONG Color, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Control_window, &Rectangle);

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Control_window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ����� ������� �� 0, ���⮬� ࠧ���� ���� 㬥����� �� �������.
  Rectangle.yTop --; Rectangle.xRight --;

  // ����㯠�� �� ��� ���� �� �ॡ����.
  INT No_margin = 0;

  // ����訢��� ��������� ����.
  Painter_FillControl (Presentation_space, &Rectangle, Color, Window_is_active, No_margin, Frame_window, Frame_rectangle, Frame_placement);

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� �।���⥫쭮 ����訢��� ���� ��������� ���

// �� ��६���� - ���譨�.
VOID Painter_PreDrawTitleBar (HWND TitleBar_window, BYTE Window_is_active, HWND Frame_window, PRECT Frame_rectangle, PSWP Frame_placement)
{
  // ����訢��� ����.
  if (Painter_TitleBarIsGrayed ())
  {
    Painter_PreDrawGrayedTitleBar (TitleBar_window, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  }
  else
  {
    Painter_PreDrawNeonOrGlassTitleBar (TitleBar_window, Window_is_active, Frame_window, Frame_rectangle, Frame_placement);
  }

  // ������.
  return;
}

