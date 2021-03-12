
// ��� �������� ���� � ᯨ᮪ ��� ��।������� ����ࠦ���� ���

// Window - ����, Message � *_parameter - ᮮ�饭��, ���஥ ��।����� ����.
VOID Scroller_CollectWindows (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �᫨ �� ��।������� �� ���� ��ப� ��� ��࠭��� - ���������� ����.
  INT Command = SHORT2FROMMP (Second_parameter);
  if (Command == SB_LINEDOWN || Command == SB_PAGEDOWN ||
      Command == SB_LINEUP   || Command == SB_PAGEUP  )
   if (Scroller_PermissionForScrolling (Window)) Scroller_AddWindowToList (Window);

  // ������.
  return;
}

// ��� ������ ��।������� ����ࠦ���� � ���� ������ ���

// Message - ᮮ�饭��, ���஥ ��।����� ����.
VOID Scroller_SmoothScrolling (PQMSG Message)
{
  // �०�� �ᥣ� ���� ������ ������� �� ᮮ�饭��.
  Scroller.RTSettings.Detection_is_disabled = 1;
  WinSendMsg (Message->hwnd, Message->msg, Message->mp1, Message->mp2);
  Scroller.RTSettings.Detection_is_disabled = 0;

  // ��⥬ - ᮮ�饭�� � ⮬, �� ���� ��।������ ����ࠦ���� �� 㪠������� ����.
  SHORT Slider_position = SHORT1FROMMP (Message->mp2);
  Message->mp2 = MPFROM2SHORT (Slider_position, SB_SLIDERPOSITION);

  // ������.
  return;
}

// ��� �����蠥� ��।������� ����ࠦ���� � ������� ��� ���

VOID Scroller_TerminateDragging (VOID)
{
  // �����蠥� ��।�������.
  Scroller.RTSettings.Dragging = 0;

  Scroller.RTSettings.Target_window = NULLHANDLE;
  Scroller.RTSettings.VSB_Control = NULLHANDLE;
  Scroller.RTSettings.HSB_Control = NULLHANDLE;

  // �᢮������� 㪠��⥫� ���.
  ResetPointer ();

  // ������.
  return;
}

// ��� ���������� �窨 � ���� ���

// Window - ����, � ���஬ ���� ��������� �窨.
VOID Scroller_GetPointsFromWindow (HWND Window)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // ��窨 �㤥� ���������� � ������ ࠧ��஬ SCROLLER_SCRLIST_LINE * SCROLLER_SCRLIST_LINE * 2 ��� �����.
  INT Max_count = 0;
  if (Min (Rectangle.xRight, Rectangle.yTop) / 4 > SCROLLER_SCRLIST_LINE) Max_count = SCROLLER_SCRLIST_LINE;
  else Max_count = Min (Rectangle.xRight, Rectangle.yTop) / 4;

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return;

  // ���������� �窨 - ��� '>', �ᯮ�������� � �⮬ ������.
  // �᫨ �窠 ������㯭�, � GpiQueryPel () �����頥� (-1).
  POINT Point = {0};
  for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
  {
    Point.x = Rectangle.xRight / 2 - Count;
    Point.y = Rectangle.yTop / 2 - Count;
    Scroller.RTSettings.Line_1[Count] = GpiQueryPel (Presentation_space, &Point);
    Point.y = Rectangle.yTop / 2 + Count;
    Scroller.RTSettings.Line_2[Count] = GpiQueryPel (Presentation_space, &Point);
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return;
}

// ��� ��室�� �窨 � ���� � �����頥� ����ﭨ�, �� ���஥ ��� �뫨 ᤢ����� ���

// Window - ����, � ���஬ ���� ���� �窨, Direction - ���ࠢ�����,
// � ���஬ �ந�室�� ��।�������, Supposition - �।���������� ����ﭨ�.
INT Scroller_FindPoints (HWND Window, LONG Direction, INT Supposition)
{
  // ������ ࠧ��� ����.
  RECT Rectangle = {0}; WinQueryWindowRect (Window, &Rectangle);

  // ��窨 ������������ � ������ ࠧ��஬ SCROLLER_SCRLIST_LINE * SCROLLER_SCRLIST_LINE * 2 ��� �����.
  INT Max_count = 0;
  if (Min (Rectangle.xRight, Rectangle.yTop) / 4 > SCROLLER_SCRLIST_LINE) Max_count = SCROLLER_SCRLIST_LINE;
  else Max_count = Min (Rectangle.xRight, Rectangle.yTop) / 4;

  // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
  HPS Presentation_space = WinGetPS (Window);

  // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
  if (Presentation_space == NULLHANDLE) return 0;

  // �����ﭨ� � �᫮ ᮢ������� ���������.
  INT Distance = 0; INT Coincidences = 0;

  // ���� ᪮����, �饬 �窨 � ���� �ࠧ� �� �� �।���������� ���� - �
  // �᫨ ��� ⠬, �����頥� ����ﭨ�. �஢��塞 ������� [A-2 .. A+2].
  BYTE Success = 0;
  if (Supposition != 0)
   for (INT Count_for_lines = 0; Count_for_lines < 4; Count_for_lines += 1)
   {
     // ������ ᬥ饭��.
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

     // ����ਬ, ����� �窨 ⠬ ᥩ��. �᫨ �窠 ������㯭�, � GpiQueryPel () �����頥� (-1).
     POINT Point = {0}; BYTE Points_is_found = 1;
     for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
     {
       Point.x = Rectangle.xRight / 2 - Count - X_Offset;
       Point.y = Rectangle.yTop / 2 - Count + Y_Offset;
       if (Scroller.RTSettings.Line_1[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
       Point.y = Rectangle.yTop / 2 + Count + Y_Offset;
       if (Scroller.RTSettings.Line_2[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
     }

     // �᫨ �窨 ������� - �����蠥� ����.
     if (Points_is_found) { Success = 1; break; }
   }

  // �᫨ �窨 ������� - ��୥� �� ����ﭨ�.
  if (Success) Distance = Supposition;
  // ���� - �஢���� ���� �� �ᥩ ������. ������� ���᪠ - Max_count.
  else
  {
    // �饬 �窨 � ���� � �� ���� ��稭�� � ⮣�, ��� ��� �뫨 - � �᫨ �������,
    // �����頥� ����ﭨ�. �᫨ ������� ��᪮�쪮 ᮢ�������, �����頥� 0.
    for (INT Count_for_lines = 0; Count_for_lines < Max_count; Count_for_lines += 1)
    {
      // ������ ᬥ饭��.
      INT X_Offset = 0; INT Y_Offset = 0;
      if (Direction == WM_VSCROLL) Y_Offset = Count_for_lines;
      else X_Offset = Count_for_lines;

      // ����ਬ, ����� �窨 ⠬ ᥩ��. �᫨ �窠 ������㯭�, � GpiQueryPel () �����頥� (-1).
      POINT Point = {0}; BYTE Points_is_found = 1;
      for (INT Count = Max_count - 1; Count >= 0; Count -= 1)
      {
        Point.x = Rectangle.xRight / 2 - Count - X_Offset;
        Point.y = Rectangle.yTop / 2 - Count + Y_Offset;
        if (Scroller.RTSettings.Line_1[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
        Point.y = Rectangle.yTop / 2 + Count + Y_Offset;
        if (Scroller.RTSettings.Line_2[Count] != GpiQueryPel (Presentation_space, &Point)) { Points_is_found = 0; break; }
      }

      // �᫨ �窨 �������:
      if (Points_is_found)
      {
        // �����稢��� ���稪 ᮢ������� � ���������� ����ﭨ�.
        Coincidences += 1; Distance = Count_for_lines;
        // �᫨ ᮢ������� ����� 1, �४�頥� ���� �� �ᥩ ������.
        if (Coincidences > 1) Distance = 0;
        // �᫨ ᮢ������� �뫮 �ࠧ� �� ��� �� �뫮 ����� 1, �����頥� 0.
        if (Distance == 0) break;
      }
    }
  }

  // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
  WinReleasePS (Presentation_space);

  // ������.
  return Distance;
}

// ��� ���������� ���� � ᪮���� �� ������� ��।������� ���

// Window - ����, Message � *_parameter - ᮮ�饭��, ���஥ ��।����� ����.
VOID Scroller_DetectSpeed (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // ����� ��।������� ��稭����� - ���������� ����.
  if (Scroller.RTSettings.Step_of_scrolling == 1)
  {
    // �᫨ ��।������� ����ࠦ���� ��������:
    if (Scroller_PermissionForScrolling (Window))
     if (!Scroller_WindowHasPreDefinedSpeed (Window))
     {
       // ���������� ����.
       Scroller.RTSettings.Scrolling_window = Window;
       Scroller.RTSettings.ScrList_position = 0;
       Scroller.RTSettings.Messages_is_redirected = 0;

       // �����稢��� ���稪.
       Scroller.RTSettings.Step_of_scrolling ++;
     }

    // ������.
    return;
  }

  // ����, ���஥ ����砥� ᮮ�饭�� �� ����᮪ ��ᬮ��, ����� ���뫠�� ��
  // � ��㣮� ����. ����� � ��� � ���� �������� ᪮����.
  if (Scroller.RTSettings.Step_of_scrolling == 2)
   if (Window != Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position == 0)
     if (!Scroller.RTSettings.Messages_is_redirected)
      if (Scroller_PermissionForScrolling (Window))
       if (!Scroller_WindowHasPreDefinedSpeed (Window))
       {
         // ��४��砥��� �� ��㣮� ����.
         Scroller.RTSettings.Scrolling_window = Window;
         Scroller.RTSettings.ScrList_position = 0;
         Scroller.RTSettings.Messages_is_redirected = 1;
       }

  // �� ��஬ 蠣� - ���������� �窨 � ����.
  if (Scroller.RTSettings.Step_of_scrolling == 2)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position == 0)
    {
      // ����ᨬ ���� � ᯨ᮪ � ���������� ����� ����� � ���.
      Scroller.RTSettings.ScrList_position = Scroller_AddWindowToList (Scroller.RTSettings.Scrolling_window);

      // ���������� ��������� ������ ����᪨.
      Scroller.RTSettings.Slider_position = SHORT1FROMMP (Second_parameter);
      // ���������� �窨 � ����.
      Scroller_GetPointsFromWindow (Window);

      // �����稢��� ���稪.
      Scroller.RTSettings.Step_of_scrolling ++;

      // ������.
      return;
    }

  // �� ᫥���饬 蠣� ��祣� �� ������ - ��������, ����ࠦ���� �� �� ��।�����.
  if (Scroller.RTSettings.Step_of_scrolling == 3)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position != 0)
    {
      // �����稢��� ���稪.
      Scroller.RTSettings.Step_of_scrolling ++;

      // ������.
      return;
    }

  // �� ��᫥���� 蠣� 㧭��� ᪮���� � ���뢠�� ��६����� ᭮�� � 0.
  if (Scroller.RTSettings.Step_of_scrolling == 4)
   if (Window == Scroller.RTSettings.Scrolling_window)
    if (Scroller.RTSettings.ScrList_position != 0)
    {
      // ������, �� ᪮�쪮 ������� ��।����� ������ ����᪨.
      SHORT Current_position = SHORT1FROMMP (Second_parameter);
      INT I = Scroller.RTSettings.ScrList_position;

      // �᫨ ������ ����᪨ ��।����� ���� ��� ��ࠢ� - ���������� ᪮����.
      if (Current_position > Scroller.RTSettings.Slider_position)
      {
        // ���������� ᪮���� �� ��ਧ��⠫�:
        if (Message == WM_HSCROLL)
        {
          // �।���������� ����ﭨ�:
          INT Lines = Current_position - Scroller.RTSettings.Slider_position;
          INT Supposition = DivideMultiply (Scroller.Scrolling_list[I].X_Velocity_DD, Scroller.Scrolling_list[I].X_Velocity_D, Lines);
          // �� ᠬ�� ���� �ன����:
          INT Distance = Scroller_FindPoints (Window, Message, Supposition);

          // ���������� �ன������ ����ﭨ� - ��� � �窠�, ⠪ � � �������� ����᪨ ��ᬮ��.
          if (Distance > 0)
          {
            // �᫨ ᪮���� �������� - ���������� ��.
            INT Previous_V_DD = Scroller.Scrolling_list[I].X_Velocity_DD;
            INT Previous_V_D  = Scroller.Scrolling_list[I].X_Velocity_D;

            if (Previous_V_DD == 0 || Previous_V_D == 0) { Previous_V_DD = 0; Previous_V_D = 1; }

            if (Distance >= Lines)
             if (Distance / Lines != Previous_V_DD / Previous_V_D)
              if (Distance / Lines < SCROLLER_MAX_VELOCITY_DD_D)
              {
                // ���������� ᪮����.
                Scroller.Scrolling_list[I].X_Velocity_DD = Distance;
                Scroller.Scrolling_list[I].X_Velocity_D  = Lines;

                // ���᮪ ���� �㤥� ��࠭���.
                WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);
              }
          }
        }

        // ���������� ᪮���� �� ���⨪���:
        if (Message == WM_VSCROLL)
        {
          // �।���������� ����ﭨ�:
          INT Lines = Current_position - Scroller.RTSettings.Slider_position;
          INT Supposition = DivideMultiply (Scroller.Scrolling_list[I].Y_Velocity_DD, Scroller.Scrolling_list[I].Y_Velocity_D, Lines);
          // �� ᠬ�� ���� �ன����:
          INT Distance = Scroller_FindPoints (Window, Message, Supposition);

          // ���������� �ன������ ����ﭨ� - ��� � �窠�, ⠪ � � �������� ����᪨ ��ᬮ��.
          if (Distance > 0)
          {
            // �᫨ ᪮���� �������� - ���������� ��.
            INT Previous_V_DD = Scroller.Scrolling_list[I].Y_Velocity_DD;
            INT Previous_V_D  = Scroller.Scrolling_list[I].Y_Velocity_D;

            if (Previous_V_DD == 0 || Previous_V_D == 0) { Previous_V_DD = 0; Previous_V_D = 1; }

            if (Distance >= Lines)
             if (Distance / Lines != Previous_V_DD / Previous_V_D)
              if (Distance / Lines < SCROLLER_MAX_VELOCITY_DD_D)
              {
                // ���������� ᪮����.
                Scroller.Scrolling_list[I].Y_Velocity_DD = Distance;
                Scroller.Scrolling_list[I].Y_Velocity_D  = Lines;

                // ���᮪ ���� �㤥� ��࠭���.
                WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);
              }
          }
        }
      }

      // ����� �� ���������� ᪮����.
      Scroller.RTSettings.Step_of_scrolling = 0;
    }

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ScrollerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // ���������� ����, � ������ �ந�室�� ��।������� ����ࠦ����.
  if (Scroller.Settings.Key_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     Scroller_CollectWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

  // ��।������� ����ࠦ���� �㤥� ������. �᫨ � ����᪥ ��ᬮ�� ��६�頥���
  // ������, � ����� ���� �ࠧ� ��।������ ����ࠦ����. ����饭�� �㤥� ��������.
  if (Scroller.Settings.Smooth_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     if (SHORT2FROMMP (Message->mp2) == SB_SLIDERTRACK)
      Scroller_SmoothScrolling (Message);

  // ���������� ���� � ᪮���� �� ������� ��।�������.
  if (Scroller.Settings.Image_dragging)
  {
    // ��᫥ ������ ��� ��� ����᪮� ��ᬮ�� ᪮���� ����� ��������.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
     Scroller.RTSettings.Step_of_scrolling = 1;

    // ����� ���� ��।������� - �����塞 ᪮����.
    if (Scroller.RTSettings.Step_of_scrolling != 0)
     if (!Scroller.RTSettings.Dragging)
      if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
      {
        SHORT Command = SHORT2FROMMP (Message->mp2);
        if (Command == SB_SLIDERTRACK || Command == SB_SLIDERPOSITION)
         Scroller_DetectSpeed (Message->hwnd, Message->msg, Message->mp1, Message->mp2);
      }
  }

  // ��।������ ����ࠦ���� � ������� ���.
  if (Scroller.Settings.Image_dragging)
  {
    // ����ਬ �� ᮮ�饭��.
    BYTE Beginning = 0;

    // �᫨ ����� �ࠢ�� ������ � ����祭 ��� ����� Caps Lock - ��稭��� ��।�������.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_CAPS_LOCK)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsToggled (SC_CAPSLOCK) || KeyIsPressed (SC_CAPSLOCK))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // �᫨ ����� �ࠢ�� ������ � ����祭 Scroll Lock - ��稭��� ��।�������.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_SCROLL_LOCK)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsToggled (SC_SCRLLOCK))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // �᫨ ����� �ࠢ�� ������ � ������ Shift - ��稭��� ��।�������.
    if (Scroller.Settings.Image_dragging == SCROLLER_USE_SHIFT)
     if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
      if (KeyIsPressed (SC_LEFT_SHIFT) || KeyIsPressed (SC_RIGHT_SHIFT))
       if (!MouseButtonIsPressed (1))
        Beginning = 1;

    // ��稭��� ��।�������.
    if (Beginning == 1)
    {
      // ��� ����᮪ ��ᬮ��, ࠬ�� � ���� Win-OS/2 �� �� ������ ����⢮����.
      if (!IsFrameWindow (Message->hwnd))   if (!IsTitleBarWindow (Message->hwnd))
      if (!IsMenuWindow (Message->hwnd))    if (!IsScrollBarWindow (Message->hwnd))
      if (!IsWindowsWindow (Message->hwnd)) if (!IsDesktopWindow (Message->hwnd))
      if (WinQueryWindow (Message->hwnd, QW_PARENT) != QueryDesktopWindow ())
      {
        // ��稭��� ��।�������.
        HWND Desktop = QueryDesktopWindow ();
        POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
        HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);
        WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_BEGIN, (MPARAM) Window, 0);

        // ����饭�� ������ ���� ��襭�.
        *Discarding = 1;
      }
    }

    // ��।������ ����ࠦ���� � ��࠭��� ���.
    if (Scroller.RTSettings.Dragging == 1) 
     if (Message->msg == WM_MOUSEMOVE)
      if (MouseButtonIsPressed ())
      {
        // ��।������ ����ࠦ���� � ��࠭��� ���.
        WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_DRAG, 0, 0);

        // ����饭�� ������ ���� ��襭�.
        // �� �⮬ 㪠��⥫� ��� �� �㤥� �������.
        *Discarding = 1;
      }

    // �᫨ �⦠� ������ ��� ��� ��� ����� �� ��ன ࠧ - �����蠥� ��।�������.
    if (Scroller.RTSettings.Dragging == 1)
     if (Message->msg == WM_BUTTON1UP   || Message->msg == WM_BUTTON2UP   || Message->msg == WM_BUTTON3UP   ||
         Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
         (Message->msg == WM_MOUSEMOVE && !MouseButtonIsPressed ()))
     {
       // �����蠥� ��।�������.
       Scroller_TerminateDragging ();
       WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

       // �᫨ ���� �ᯮ�짮���� Caps Lock - ���뢠�� ��४���⥫� �� ���������.
       if (Scroller.Settings.Image_dragging == SCROLLER_USE_CAPS_LOCK)
        if (KeyIsToggled (SC_CAPSLOCK) || KeyIsPressed (SC_CAPSLOCK))
         WinPostQueueMsg (Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0);

       // ����饭�� ������ ���� ��襭�.
       *Discarding = 1;
     }

    // �᫨ ���� �ᯮ�짮���� Scroll Lock � �� �⪫�祭 - �����蠥� ��।�������.
    if (Scroller.RTSettings.Dragging == 1)
     if (Scroller.Settings.Image_dragging == SCROLLER_USE_SCROLL_LOCK)
      if (Message->msg == WM_MOUSEMOVE)
       if (!KeyIsToggled (SC_SCRLLOCK))
       {
         // �����蠥� ��।�������.
         Scroller_TerminateDragging ();
         WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

         // ����饭�� ������ ���� ��襭�.
         *Discarding = 1;
       }

    // �᫨ ���� �ᯮ�짮���� Shift � �� �� ����� - �����蠥� ��।�������.
    if (Scroller.RTSettings.Dragging == 1)
     if (Scroller.Settings.Image_dragging == SCROLLER_USE_SHIFT)
      if (Message->msg == WM_MOUSEMOVE)
       if (!KeyIsPressed (SC_LEFT_SHIFT)) if (!KeyIsPressed (SC_RIGHT_SHIFT))
       {
         // �����蠥� ��।�������.
         Scroller_TerminateDragging ();
         WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

         // ����饭�� ������ ���� ��襭�.
         *Discarding = 1;
       }
  }

  // ��⠭�������� 㪠��⥫� ��� �� ��।������� ����ࠦ����.
  if (Scroller.Settings.Image_dragging) if (Scroller.RTSettings.Dragging == 1)
   if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK)
    if (Message->mp1 == (MPARAM) MRK_SET_POINTER) if (Message->mp2 == (MPARAM) NULLHANDLE)
     if (Resources.Pointer_for_dragging != NULLHANDLE)
      WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

  // ������.
  return;
}

// ��� �������� �� ��������ன ���

// �� ��६���� - ���譨�.
VOID ScrollerKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // �������� ����ࠦ���� �� ���� ��ப�, �᫨ ����� ��५�� � ����祭 Scroll Lock.
  if (Scroller.Settings.Key_scrolling) if (!Scroller.RTSettings.Dragging)
   if (Message->msg == WM_CHAR)
   {
     // ����ਬ, ����� ������ �����.
     BYTE Scan_code = CHAR4FROMMP (Message->mp1);
     SHORT State = SHORT1FROMMP (Message->mp1);

     // �᫨ ���� ����⨥ ������:
     if (!(State & KC_KEYUP))
     {
       // �஢��塞 �������.
       BYTE Perform_action = 0;

       // �᫨ �� ��५�� � Scroll Lock ����祭 - ����ࠦ���� ����� �������.
       // �஢�����, ����⢨⥫쭮 �� ������ �����, ����� �� ���� - �� ����� ���� ᮮ�饭�� � �� ���.
       if (Scan_code == SC_UP || Scan_code == SC_DOWN || Scan_code == SC_LEFT || Scan_code == SC_RIGHT)
        if (!IsScrollBarWindow (Message->hwnd))
         if (KeyIsToggled (SC_SCRLLOCK))
          Perform_action = 1;

       // ���஢� ������ ����� ���� ��८�।�����.
       if (Perform_action)
        if (Scan_code >= SC_NUM_FIRST) if (Scan_code <= SC_NUM_LAST)
         Perform_action = 0;

       // �᫨ ����ࠦ���� ����� ������� - ���뫠�� ᮮ�饭�� � ��⮪.
       if (Perform_action) WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_LINE, (MPARAM) Message->hwnd, (MPARAM) Scan_code);
     }
   }

  // ��।������ ����ࠦ���� � ������� ���.
  if (Scroller.Settings.Image_dragging)
  {
    // �᫨ ����� ������ Esc - �����蠥� ��।�������.
    if (Scroller.RTSettings.Dragging == 1) if (Message->msg == WM_CHAR)
    {
      // ����ਬ, ����� ������ �����.
      BYTE Scan_code = CHAR4FROMMP (Message->mp1);
      SHORT State = SHORT1FROMMP (Message->mp1);

      // �᫨ ���� ����⨥ ������:
      if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
      {
        // �᫨ �� Esc - �����蠥� ��।�������.
        if (Scan_code == SC_ESC)
        {
          // ��⥬ - �����蠥� ��।�������.
          WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_SC_END, 0, 0);

          // ����饭�� ������ ���� ��襭�.
          *Discarding = 1;
        }
      }
    }
  }

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ScrollerSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // ���������� ����, � ������ �ந�室�� ��।������� ����ࠦ����.
  if (Scroller.Settings.Key_scrolling)
   if (!Scroller.RTSettings.Dragging)
    if (Message->msg == WM_VSCROLL || Message->msg == WM_HSCROLL)
     Scroller_CollectWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

  // ���������� ���� � ᪮���� �� ������� ��।�������.
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

  // ������.
  return;
}
