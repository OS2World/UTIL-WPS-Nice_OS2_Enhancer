
// ��� �롨ࠥ� ���� ��� ��।������� ����ࠦ���� ���

// Window - ����, � ���஬ �ॡ���� ��।������ ����ࠦ����.
// �����頥��� ���祭�� - � �� ᠬ�� ���� ��� ���� �� ��� த�⥫�᪨� ���� (��������, �� ���� �����).
HWND Scroller_ChooseWindowFromScrollingList (HWND Window)
{
  // �᫨ � ���� ����� ��।������ ����ࠦ���� - �㤥� ���뫠�� ᮮ�饭�� ���.
  // ���� ���������� � ᯨ᮪ � ⮬ ��砥, �᫨ ��� ��� ࠧ ����稫� ᮮ�饭�� �� ����᮪ ��ᬮ��.
  if (Scroller_FindWindowInList (Window))
  {
    // �㤥� ���뫠�� ᮮ�饭�� �⮬� ����.
    return Window;
  }
  // ���� - �஢��塞 த�⥫�᪨� ����.
  else
  {
    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = QueryDesktopWindow ();

    // ��室�� த�⥫�᪮� ����, � ���஬ ����� ��।������ ����ࠦ����.
    HWND Parent_window = WinQueryWindow (Window, QW_PARENT);
    while (Parent_window != Desktop && Parent_window != NULLHANDLE)
    {
      // �᫨ � த�⥫�᪮� ���� ����� ��।������ ����ࠦ����:
      if (Scroller_FindWindowInList (Parent_window))
      {
        // �㤥� ���뫠�� ᮮ�饭�� த�⥫�᪮�� ����.
        return Parent_window;
      }

      // ������ ᫥���饥 த�⥫�᪮� ����.
      Parent_window = WinQueryWindow (Parent_window, QW_PARENT);
    }
  }

  // ������.
  return NULLHANDLE;
}

// ��� ��।������ ����ࠦ���� �� ����⮬ Scroll Lock ���

// Selected_window - ����, � ���஥ ���ࠢ��� ���� �� ���짮��⥫�, Scan_code �����뢠��, ����� ������ �����.
VOID Scroller_ScrollImage (HWND Selected_window, INT Scan_code)
{
  // �롨ࠥ� ���� ��� ��।������� ����ࠦ����.
  HWND Target_window = Scroller_ChooseWindowFromScrollingList (Selected_window);

  // �᫨ �� ���� ���� �� ��࠭� - ������.
  if (Target_window == NULLHANDLE) return;

  // � �������� ����� ��।������ ����ࠦ���� �� ����.
  if (!Scroller_PermissionForKeyScrolling (Target_window)) return;

  // �᫨ ����� ��५�� ����� ��� ���� - �஢��塞 ���ﭨ� ����᪨ ᢥ��� ����,
  // � �᫨ ����� ��५�� ����� ��� ��ࠢ� - �஢��塞 ���ﭨ� ����᪨ ᫥�� ���ࠢ�.
  BYTE SB_Type = SBS_HORZ; if (Scan_code == SC_UP || Scan_code == SC_DOWN) SB_Type = SBS_VERT;

  // �஡㥬 ���� ������ ��ᬮ�� ����� ��࠭���� ����.
  HWND SB_Control = Scroller_FindScrollBar (Target_window, SB_Type);

  // �᫨ ����᪠ ���� - 㧭���, � ����� ��� ���ﭨ�.
  if (SB_Control != NULLHANDLE)
  {
    // ������, � ����� ���ﭨ� ����᪠.
    Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
  }
  // �᫨ ����᪨ ��� - ��� ����� ���� �ᯮ������ �冷� � �����.
  else
  {
    // ������ த�⥫�᪮� ����.
    HWND Parent_window = WinQueryWindow (Target_window, QW_PARENT);

    // �஢��塞, ����� �� ��।������ ����ࠦ���� � த�⥫�᪮� ����.
    if (Scroller_PermissionForKeyScrolling (Parent_window))
    {
      // �饬 ������ � த�⥫�᪮� ����.
      SB_Control = Scroller_FindScrollBar (Parent_window, SB_Type);

      // �᫨ ����᪠ ���� - 㧭���, � ����� ��� ���ﭨ�.
      if (SB_Control != NULLHANDLE) Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
    }
  }

  // �᫨ ����᪠ �뫠 �������:
  if (SB_Control != NULLHANDLE)
  {
    // �᫨ ��� �⪫�祭� - ������.
    if (!Scroller.RTSettings.SB_State.sHilite) return;
    if (Scroller.RTSettings.SB_State.posFirst == 0 && Scroller.RTSettings.SB_State.posLast == 0) return;

    // �᫨ ������ ���⨣ ��� ����᪨ - ������.
    if (Scan_code == SC_UP || Scan_code == SC_LEFT)
     if (Scroller.RTSettings.SB_State.posThumb == Scroller.RTSettings.SB_State.posFirst) return;

    if (Scan_code == SC_DOWN || Scan_code == SC_RIGHT)
     if (Scroller.RTSettings.SB_State.posThumb == Scroller.RTSettings.SB_State.posLast) return;

    // ������ ᯮᮡ ��।������� ����ࠦ���� � ����.
    INT Scrolling_method = Scroller_QueryScrollingMethod (Target_window);

    // ���뫠�� ����᪥ ��ᬮ�� ᮮ�饭�� �� ���������� ��� ���.
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
  // � �᫨ ����᪨ ��ᬮ�� ���:
  else
  {
    // ���⠢�塞 ᮮ�饭�� � ⮬, �� ����ࠦ���� ���� ��������� �� ���� ��ப�.
    ULONG Message = 0; USHORT SB_Code = 0;
    if (Scan_code == SC_UP)   { Message = WM_VSCROLL; SB_Code = SB_LINEUP;   }
    if (Scan_code == SC_DOWN) { Message = WM_VSCROLL; SB_Code = SB_LINEDOWN; }
    if (Scan_code == SC_LEFT) { Message = WM_HSCROLL; SB_Code = SB_LINELEFT; }
    if (Scan_code == SC_RIGHT) { Message = WM_HSCROLL; SB_Code = SB_LINERIGHT; }

    // ���뫠�� ��� � ����.
    // ��� ��� ��� �ਭ����� ᮮ�饭�� �� ����᮪ ��ᬮ��, � ᪮॥ �ᥣ�, ��� ᬮ��� ��ࠡ���� � �� ᮮ�饭��.
    WinPostMsg (Target_window, Message, 0, MPFROM2SHORT (0, SB_Code));
  }

  // ������.
  return;
}

// ��� ��稭��� ��।������� ����ࠦ���� � ������� ��� ���

// Selected_window - ���� ��� 㪠��⥫�� ���, X � Y - �ᯮ������� 㪠��⥫� ��� �� �࠭�.
VOID Scroller_BeginDragging (HWND Selected_window, INT X, INT Y)
{
  // �롨ࠥ� ���� ��� ��।������� ����ࠦ����.
  HWND Target_window = Scroller_ChooseWindowFromScrollingList (Selected_window);

  // �᫨ �� ���� ���� �� ��࠭� - ������.
  if (Target_window == NULL) return;

  // � �������� ����� ��।������ ����ࠦ���� �� ����.
  if (!Scroller_PermissionForScrolling (Target_window)) return;

  // ������ ᯮᮡ ��।������� ����ࠦ���� � ����.
  INT Dragging_method = Scroller_QueryScrollingMethod (Target_window);

  // �᫨ � ���� ���� ��ࠢ���� ᮮ�饭�� �� ����᮪ ��ᬮ�� - ��室�� ��.
  if (Dragging_method == SCROLLING_COMMON ||
      Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
  {
    // ��室�� ����᪨ � ����.
    Scroller.RTSettings.VSB_Control = NULLHANDLE;
    Scroller.RTSettings.HSB_Control = NULLHANDLE;

    for (INT VH_Count = 0; VH_Count < 2; VH_Count ++)
    {
      // �����塞 ����⢨� ��� ࠧ�, ��� ���⨪��쭮� � ��ਧ��⠫쭮� ����᪨.
      BYTE SB_Type = SBS_VERT; if (VH_Count == 1) SB_Type = SBS_HORZ;
      HWND SB_Control = NULLHANDLE;

      // �஡㥬 ���� ������ ��ᬮ�� ����� ��࠭���� ����, � ��⮬ �ᯮ������� ⮣� ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
      if (Selected_window == Target_window)
      {
        SB_Control = Scroller_FindScrollBar (Target_window, SB_Type);
      }
      else
      {
        SWP Selected_window_placement = {0}; WinQueryWindowPos (Selected_window, &Selected_window_placement);
        SB_Control = Scroller_FindScrollBar (Target_window, SB_Type, &Selected_window_placement);
      }

      // �᫨ ����᪠ ���� - 㧭���, � ����� ��� ���ﭨ�.
      if (SB_Control != NULLHANDLE)
      {
        // ������, � ����� ���ﭨ� ����᪠.
        Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
      }
      // �᫨ ����᪨ ��� - ��� ����� ���� �ᯮ������ �冷� � �����.
      else
      {
        // ������ த�⥫�᪮� ����.
        HWND Parent_window = WinQueryWindow (Target_window, QW_PARENT);

        // �᫨ � த�⥫�᪮� ���� ����� ��।������ ����ࠦ���� - ��室�� � ��� ������.
        if (Scroller_PermissionForScrolling (Parent_window))
        {
          // �饬 ������ � த�⥫�᪮� ����, �஢���� �� �ᯮ�������.
          SWP Target_window_placement = {0}; WinQueryWindowPos (Target_window, &Target_window_placement);
          SB_Control = Scroller_FindScrollBar (Parent_window, SB_Type, &Target_window_placement);

          // �᫨ ����᪠ ���� - 㧭���, � ����� ��� ���ﭨ�.
          if (SB_Control != NULLHANDLE) Scroller_QueryScrollBarState (SB_Control, &Scroller.RTSettings.SB_State);
        }
      }

      // ���������� ������, �᫨ ��� �뫠 �������.
      if (SB_Control != NULLHANDLE)
      {
        if (SB_Type == SBS_VERT) Scroller.RTSettings.VSB_Control = SB_Control;
        if (SB_Type == SBS_HORZ) Scroller.RTSettings.HSB_Control = SB_Control;
      }
    }

    // �᫨ ������� ��� �� ���� ����᪠:
    if (Scroller.RTSettings.VSB_Control != NULLHANDLE || Scroller.RTSettings.HSB_Control != NULLHANDLE)
    {
      // �᫨ ��� ����᪨ �⪫�祭� - ������.
      Scroller_QueryScrollBarState (Scroller.RTSettings.VSB_Control, &Scroller.RTSettings.VSB_State);
      Scroller_QueryScrollBarState (Scroller.RTSettings.HSB_Control, &Scroller.RTSettings.HSB_State);

      if (!Scroller.RTSettings.VSB_State.sHilite && !Scroller.RTSettings.HSB_State.sHilite) return;
      if (Scroller.RTSettings.VSB_State.posFirst == 0 && Scroller.RTSettings.VSB_State.posLast == 0 &&
          Scroller.RTSettings.HSB_State.posFirst == 0 && Scroller.RTSettings.HSB_State.posLast == 0) return;

      // ���������� �ᯮ������� ������� ����᮪ ��ᬮ��.
      Scroller.RTSettings.Start_VSB_position = Scroller.RTSettings.VSB_State.posThumb;
      Scroller.RTSettings.Start_HSB_position = Scroller.RTSettings.HSB_State.posThumb;

      // ���������� ����.
      Scroller.RTSettings.Target_window = Target_window;

      // ���������� ᯮᮡ ��।������� ����ࠦ���� � ����.
      Scroller.RTSettings.Dragging_method = Dragging_method;

      // ���������� ᪮���� ��।������� ����ࠦ���� � ����.
      SCRLIST Record_from_list = {0}; Scroller_QueryScrollingVelocity (Target_window, &Record_from_list);
      Scroller.RTSettings.X_Velocity_DD = Record_from_list.X_Velocity_DD; Scroller.RTSettings.X_Velocity_D = Record_from_list.X_Velocity_D;
      Scroller.RTSettings.Y_Velocity_DD = Record_from_list.Y_Velocity_DD; Scroller.RTSettings.Y_Velocity_D = Record_from_list.Y_Velocity_D;
    }
    // � �᫨ �� ����� ����᪨ �� �������:
    else
    {
      // ���������� ����.
      Scroller.RTSettings.Target_window = Target_window;

      // ����砥� � ���� ०�� ��।������� � ������� ᮮ�饭�� "WM_xSCROLL".
      // ��� ��� ��� �ਭ����� ᮮ�饭�� �� ����᮪ ��ᬮ��, � ᪮॥ �ᥣ�, ��� ᬮ��� ��ࠡ���� � �� ᮮ�饭��.
      Scroller.RTSettings.Dragging_method = SCROLLING_DISCRETE_SCROLLMSG;

      // ������ ᪮���� ��।������� ����ࠦ���� � ����.
      Scroller.RTSettings.X_Velocity_DD = SCROLLER_DEF_SPEED_X; Scroller.RTSettings.X_Velocity_D = 1;
      Scroller.RTSettings.Y_Velocity_DD = SCROLLER_DEF_SPEED_Y; Scroller.RTSettings.Y_Velocity_D = 1;
    }
  }

  // �᫨ � ���� ���� ��ࠢ���� ᮮ�饭�� �������:
  if (Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
  {
    // ���������� ����.
    Scroller.RTSettings.Target_window = Target_window;
    if (Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW) Scroller.RTSettings.Target_window = WinQueryFocus (QueryDesktopWindow ());

    // ���������� ᯮᮡ ��।������� ����ࠦ���� � ����.
    Scroller.RTSettings.Dragging_method = SCROLLING_DISCRETE_SCROLLMSG;

    // ���������� ᪮���� ��।������� ����ࠦ���� � ����.
    SCRLIST Record_from_list = {0}; Scroller_QueryScrollingVelocity (Target_window, &Record_from_list);
    Scroller.RTSettings.X_Velocity_DD = Record_from_list.X_Velocity_DD; Scroller.RTSettings.X_Velocity_D = Record_from_list.X_Velocity_D;
    Scroller.RTSettings.Y_Velocity_DD = Record_from_list.Y_Velocity_DD; Scroller.RTSettings.Y_Velocity_D = Record_from_list.Y_Velocity_D;
  }

  // ���������� ��������� 㪠��⥫� ���.
  Scroller.RTSettings.Start_point.x = X;
  Scroller.RTSettings.Start_point.y = Y;
  Scroller.RTSettings.Previous_step_point.x = X;
  Scroller.RTSettings.Previous_step_point.y = Y;

  // ��⠭�������� ���� 㪠��⥫� ���.
  if (Resources.Pointer_for_dragging != NULLHANDLE)
   WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

  // ����������, �� ��।������� ��砫���.
  Scroller.RTSettings.Dragging = 1;

  // ������.
  return;
}

// ��� ��।������ ����ࠦ���� � ��࠭��� ��� ���

// X � Y - �ᯮ������� 㪠��⥫� ��� �� �࠭�.
VOID Scroller_DragImage (INT X, INT Y)
{
  // ����뢠��, �� ᮮ�饭�� �뫮 ��᫠��.
  BYTE Sent = 0; HWND Owner_window = NULLHANDLE;

  // ��।������ ����ࠦ���� ᢥ��� ����.
  if (Y != Scroller.RTSettings.Previous_step_point.y)
  {
    // ������뢠�� ����� ��������� ������ ����᪨ ��ᬮ�� ��� ���ࠢ����� ��।������� ����ࠦ����.
    INT New_position = -1; INT Lines_to_repeat = 1;

    // �᫨ ���� �ᯮ�짮���� ����᪨ ��ᬮ��:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON ||
        Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
    {
      // ������ ���ﭨ� ����᪨ ��ᬮ��.
      if (WinIsWindow (WinQueryAnchorBlock (Scroller.RTSettings.VSB_Control), Scroller.RTSettings.VSB_Control))
       Scroller_QueryScrollBarState (Scroller.RTSettings.VSB_Control, &Scroller.RTSettings.VSB_State);

      // �᫨ �����⭠ ᪮���� � ��।������� ����ࠦ���� ��������:
      if (Scroller.RTSettings.Y_Velocity_DD != 0) if (Scroller.RTSettings.Y_Velocity_D != 0)
       if (Scroller.RTSettings.VSB_State.posThumb >= Scroller.RTSettings.VSB_State.posFirst)
        if (Scroller.RTSettings.VSB_State.posThumb <= Scroller.RTSettings.VSB_State.posLast)
         if (!(Scroller.RTSettings.VSB_State.posFirst == 0 && Scroller.RTSettings.VSB_State.posLast == 0))
          if (Scroller.RTSettings.VSB_State.sHilite)
          {
            // �᫨ ����� ��몭������ ᯮᮡ ��।�������:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON)
            {
              // ������ ����ﭨ� � �窠� �� �窨 ��砫� ��।�������.
              INT Distance = abs (Scroller.RTSettings.Start_point.y - Y);

              // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ�:
              if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
              {
                // ������뢠�� ����� �ᯮ������� ������ ����᪨ ��ᬮ��.
                INT Lines = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance);

                New_position = Scroller.RTSettings.Start_VSB_position;
                if (Y > Scroller.RTSettings.Start_point.y) New_position += Lines;
                if (Y < Scroller.RTSettings.Start_point.y) New_position -= Lines;

                if (New_position < Scroller.RTSettings.VSB_State.posFirst) New_position = Scroller.RTSettings.VSB_State.posFirst;
                if (New_position > Scroller.RTSettings.VSB_State.posLast) New_position = Scroller.RTSettings.VSB_State.posLast;
                if (New_position == Scroller.RTSettings.VSB_State.posThumb) New_position = -1;
              }
            }

            // �᫨ ����� ᯮᮡ ��।������� �१ ��ࠢ�� ����᪠� ��ᬮ�� ᮮ�饭�� �� ���������� ��� ���:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
            {
              // ������ ����ﭨ� � �窠� �� �।��饩 �窨.
              INT Distance = abs (Scroller.RTSettings.Previous_step_point.y - Y);

              // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ� - ����ࠦ���� ���� ��।������ �� ���� ��� ��᪮�쪮 蠣�� ����� ��� ����.
              if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
              {
                Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
                if (Scroller.RTSettings.Previous_step_point.y > Y) New_position = 1;
                else New_position = 0;
              }
            }
          }
    }

    // �᫨ ���� ��ࠢ���� ᮮ�饭�� � ���� �������:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
    {
      // �᫨ �����⭠ ᪮���� � ��।������� ����ࠦ���� ��������:
      if (Scroller.RTSettings.Y_Velocity_DD != 0) if (Scroller.RTSettings.Y_Velocity_D != 0)
      {
        // ������ ����ﭨ� � �窠� �� �।��饩 �窨.
        INT Distance = abs (Scroller.RTSettings.Previous_step_point.y - Y);

        // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ� - ����ࠦ���� ���� ��।������ �� ���� ��� ��᪮�쪮 蠣�� ����� ��� ����.
        if (Distance >= Scroller.RTSettings.Y_Velocity_DD / Scroller.RTSettings.Y_Velocity_D)
        {
          Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
          if (Scroller.RTSettings.Previous_step_point.y > Y) New_position = 1;
          else New_position = 0;
        }
      }
    }

    // �᫨ �뫮 ������ ����� ��������� ������ ����᪨ ��ᬮ�� � ������ ��� �� �� �����:
    if (New_position != -1) if (MouseButtonIsPressed ())
    {
      // ���뫠�� ᮮ�饭��.
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

      // ����������, �� ᮮ�饭�� �뫨 ��᫠��.
      Sent = 1;
    }
  }

  // ��।������ ����ࠦ���� ᫥�� ���ࠢ�.
  if (X != Scroller.RTSettings.Previous_step_point.x)
  {
    // ������뢠�� ����� ��������� ������ ����᪨ ��ᬮ�� ��� ���ࠢ����� ��।������� ����ࠦ����.
    INT New_position = -1; INT Lines_to_repeat = 1;

    // �᫨ ���� �ᯮ�짮���� ����᪨ ��ᬮ��:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON ||
        Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
    {
      // ������ ���ﭨ� ����᪨ ��ᬮ��.
      if (WinIsWindow (WinQueryAnchorBlock (Scroller.RTSettings.HSB_Control), Scroller.RTSettings.HSB_Control))
       Scroller_QueryScrollBarState (Scroller.RTSettings.HSB_Control, &Scroller.RTSettings.HSB_State);

      // �᫨ �����⭠ ᪮���� � ��।������� ����ࠦ���� ��������:
      if (Scroller.RTSettings.X_Velocity_DD != 0) if (Scroller.RTSettings.X_Velocity_D != 0)
       if (Scroller.RTSettings.HSB_State.posThumb >= Scroller.RTSettings.HSB_State.posFirst)
        if (Scroller.RTSettings.HSB_State.posThumb <= Scroller.RTSettings.HSB_State.posLast)
         if (!(Scroller.RTSettings.HSB_State.posFirst == 0 && Scroller.RTSettings.HSB_State.posLast == 0))
          if (Scroller.RTSettings.HSB_State.sHilite)
          {
            // �᫨ ����� ��몭������ ᯮᮡ ��।�������:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_COMMON)
            {
              // ������ ����ﭨ� � �窠� �� �窨 ��砫� ��।�������.
              INT Distance = abs (Scroller.RTSettings.Start_point.x - X);

              // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ�:
              if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
              {
                // ������뢠�� ����� �ᯮ������� ������ ����᪨ ��ᬮ��.
                INT Lines = DivideDivideRL (Scroller.RTSettings.X_Velocity_DD, Scroller.RTSettings.X_Velocity_D, Distance);

                New_position = Scroller.RTSettings.Start_HSB_position;
                if (X > Scroller.RTSettings.Start_point.x) New_position -= Lines;
                if (X < Scroller.RTSettings.Start_point.x) New_position += Lines;

                if (New_position < Scroller.RTSettings.HSB_State.posFirst) New_position = Scroller.RTSettings.HSB_State.posFirst;
                if (New_position > Scroller.RTSettings.HSB_State.posLast) New_position = Scroller.RTSettings.HSB_State.posLast;
                if (New_position == Scroller.RTSettings.HSB_State.posThumb) New_position = -1;
              }
            }

            // �᫨ ����� ᯮᮡ ��।������� �१ ��ࠢ�� ����᪠� ��ᬮ�� ᮮ�饭�� �� ����������:
            if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_MB || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SBCTL_KBD)
            {
              // ������ ����ﭨ� � �窠� �� �।��饩 �窨.
              INT Distance = abs (Scroller.RTSettings.Previous_step_point.x - X);

              // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ� - ����ࠦ���� ���� ��।������ �� ���� ��� ��᪮�쪮 蠣�� ����� ��� ����.
              if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
              {
                Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
                if (Scroller.RTSettings.Previous_step_point.x > X) New_position = 1;
                else New_position = 0;
              }
            }
          }
    }

    // �᫨ ���� ��ࠢ���� ᮮ�饭�� � ���� �������:
    if (Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG || Scroller.RTSettings.Dragging_method == SCROLLING_DISCRETE_SCROLLMSG_IFW)
    {
      // �᫨ �����⭠ ᪮���� � ��।������� ����ࠦ���� ��������:
      if (Scroller.RTSettings.X_Velocity_DD != 0) if (Scroller.RTSettings.X_Velocity_D != 0)
      {
        // ������ ����ﭨ� � �窠� �� �।��饩 �窨.
        INT Distance = abs (Scroller.RTSettings.Previous_step_point.x - X);

        // �᫨ ��� �����, 祬 �������襥 ��������� ����ﭨ� - ����ࠦ���� ���� ��।������ �� ���� ��� ��᪮�쪮 蠣�� ����� ��� ����.
        if (Distance >= Scroller.RTSettings.X_Velocity_DD / Scroller.RTSettings.X_Velocity_D)
        {
          Lines_to_repeat = DivideDivideRL (Scroller.RTSettings.Y_Velocity_DD, Scroller.RTSettings.Y_Velocity_D, Distance); if (!Lines_to_repeat) Lines_to_repeat = 1;
          if (Scroller.RTSettings.Previous_step_point.x > X) New_position = 1;
          else New_position = 0;
        }
      }
    }

    // �᫨ �뫮 ������ ����� ��������� ������ ����᪨ ��ᬮ�� � ������ ��� �� �� �����:
    if (New_position != -1) if (MouseButtonIsPressed ())
    {
      // ���뫠�� ᮮ�饭��.
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

      // ����������, �� ᮮ�饭�� �뫨 ��᫠��.
      Sent = 1;
    }
  }

  // �᫨ ᮮ�饭�� �뫨 ��᫠��, �:
  if (Sent)
  {
    // ���������� ����� ��������� 㪠��⥫� ���.
    Scroller.RTSettings.Previous_step_point.x = X;
    Scroller.RTSettings.Previous_step_point.y = Y;

    // ��⠭�������� ���� 㪠��⥫� ���.
    if (Resources.Pointer_for_dragging != NULLHANDLE)
     WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_dragging);

    // �� ��ࠡ�⪥ ᮮ�饭�� ���� ����� ��⠭����� ᢮� 㪠��⥫�. ���뫠�� � ��।�
    // ���� ᮮ�饭�� WM_MARK - ����� ��� �㤥� ����祭�, 㪠��⥫� ����� �㤥� ��������.
    if (Resources.Pointer_for_dragging != NULLHANDLE)
    {
      HMQ Message_queue = WinQueryWindowULong (Owner_window, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_SET_POINTER, (MPARAM) NULLHANDLE);
    }
  }

  // ������.
  return;
}

// ��� �����蠥� ��।������� ����ࠦ���� � ������� ��� ���

VOID Scroller_EndDragging (VOID)
{
  // �����蠥� ��।�������.
  Scroller_TerminateDragging ();
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Scroller_ScrollerMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Scroller->Priority = MAKELONG (Class, Delta);
  }

  // ��।������ ����ࠦ���� �� ����⨨ ������ � ��५����.
  if (Message->msg == SM_SC_LINE)
  {
    // ������ ���� � ������� �������.
    HWND Window = (HWND) Message->mp1;
    INT Scan_code = (INT) Message->mp2;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

    // ��।������ ����ࠦ����.
    Scroller_ScrollImage (Window, Scan_code);
  }

  // ��稭��� ��।������� ����ࠦ���� � ������� ���.
  if (Message->msg == SM_SC_BEGIN)
  {
    // ������ ����.
    HWND Window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

    // �᫨ �� ����� ������ Ctrl - ������ ���� ��࠭��.
    if (!CtrlIsPressed ()) MoveWindowAbove (QueryFrameWindow (Window));

    // ������ �ᯮ������� 㪠��⥫� ���.
    POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);

    // ��稭��� ��।�������.
    Scroller_BeginDragging (Window, Pointer.x, Pointer.y);
  }

  // ��।������ ����ࠦ����.
  if (Message->msg == SM_SC_DRAG)
   if (Scroller.RTSettings.Dragging)
    if (MouseButtonIsPressed ())
    {
      // ������ �ᯮ������� 㪠��⥫� ���.
      POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);

      // �᫨ 㪠��⥫� �� ⮬ �� ���� - ������.
      if (Pointer.x == Scroller.RTSettings.Previous_step_point.x)
       if (Pointer.y == Scroller.RTSettings.Previous_step_point.y)
        return;

      // ��।������ ����ࠦ����.
      Scroller_DragImage (Pointer.x, Pointer.y);
    }

  // �����蠥� ��।�������.
  if (Message->msg == SM_SC_END) Scroller_EndDragging ();

  // ���࠭塞 ����ன��.
  if (Message->msg == SM_WRITE_SETTINGS) Scroller_StartWaiterToWriteSettings ();
  if (Message->msg == SM_WAITING_COMPLETE) Scroller_WriteSettingsAfterWaiting ();

  // ������.
  return;
}

// ��� ��⮪ ��� ��।������� ����ࠦ���� � ����� ���

VOID Scroller_ScrollerThread (VOID)
{
  // ��।��塞 ��⮪ � ��⥬�.
  HAB Thread = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Thread == NULLHANDLE)
  {
    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Scroller->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Scroller->Message_queue == NULLHANDLE)
  {
    // �����蠥� ࠡ��� ��⮪�.
    WinTerminate (Thread);

    // �� ᮧ����� ��⮪� �ந��諠 �訡��.
    Thread_responds.Thread_is_created = -1;

    // ��室.
    return;
  }

  // ��⮪ ᮧ��� �ᯥ譮.
  Thread_responds.Thread_is_created = 1;

  // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
  QMSG Message = {0};
  while (WinGetMsg (Thread, &Message, 0, 0, 0))
  {
    // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
    QMSG Next_message = {0};
    WinPeekMsg (Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE);
    if (Next_message.msg == Message.msg)
     if (Next_message.mp1 == Message.mp1)
      if (Next_message.mp2 == Message.mp2)
       if (Next_message.hwnd == Message.hwnd) continue;

    // ��ࠡ��뢠�� ᮮ�饭��.
    Scroller_ScrollerMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
