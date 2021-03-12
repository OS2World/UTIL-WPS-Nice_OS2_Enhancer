
// ��� ����� ࠬ�� ��� ���� ���

// Frame_window - ���� ࠬ��, Target - ����� �� ���� ���� ����ᮢ���.
VOID Painter_DrawWindowFrame (HWND Frame_window, ULONG Target)
{
  // ������ ࠧ��� � �ᯮ������� ����.
  RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
  Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

  // �᫨ ���� �� �������� - ������.
  if (Frame_rectangle.yTop <= 1 || Frame_rectangle.xRight <= 1) return;

  // ������, ��� �룫廊� ࠬ�� ����.
  LONG Frame_type = FrameType (Frame_window);

  // ������, ��࠭� �� ����.
  BYTE Window_is_active = WindowIsActive (Frame_window);

  // ��⠭�������� ᢮��⢮.
  SetProperty (Frame_window, PRP_ACTIVATED, &Window_is_active);

  // ������ ���� ���������.
  HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

  // ��� �������� ���� ����� �ᮢ��� ⮫쪮 ���������.
  BYTE Draw_TitleBar_only = 0;

  if (!Painter_PermissionForCompleteDrawing (Frame_window))
  {
    Draw_TitleBar_only = 1; Target = WT_TITLEBAR;
  }

  // ���㥬 ࠬ�� ��� ����.
  if (!Draw_TitleBar_only)
  {
    for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
    {
      if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
      Painter_DrawFrameRectangle (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, Window_is_active);
      if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
    }
  }

  // ����ન���� ��ꥬ ���� ����.
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

  // ������ ���� ������ ������.
  HWND MinMax_window = WinWindowFromID (Frame_window, FID_MINMAX);

  // �᫨ ���� ���᪮�:
  if (Frame_type == FT_FLAT)
  {
    // �᫨ � ��� ���� ���� ������ ������ - ��뢠�� ���.
    if (Painter.Settings.Draw_buttons) if (MinMax_window != NULLHANDLE) WinShowWindow (MinMax_window, 0);

    // ������.
    return;
  }
  // � �᫨ �� �� ���᪮� ����:
  else
  {
    // �᫨ ᢮��⢠ ���� ��������� � ����� ���� ��।����� � ���饬 - ������.
    if (!PropertiesForDrawingAreDetected (Frame_window))
     if (WinWindowFromID (Frame_window, FID_SYSMENU) != NULLHANDLE) return;
  }

  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // ������ ����� ��������� � ���⨭��.
  INT TitleBar_height = 0;

  if (TitleBar_window != NULLHANDLE)
  {
    RECT Rectangle = {0}; WinQueryWindowRect (TitleBar_window, &Rectangle); TitleBar_height = Rectangle.yTop - 1;
  }
  else
  {
    TitleBar_height = WinQuerySysValue (QueryDesktopWindow (), SV_CYMINMAXBUTTON) - 1;
  }

  // ���� ��������� � ���⨭�� ������ ���� �ᯮ������ �� ����� �����.
  // �᫨ �� �� ⠪ - ���� ���� �������� � ��祣� �� �ᮢ��� � ���.
  if (SysMenu_window != NULLHANDLE) if (TitleBar_window != NULLHANDLE)
   if (WinIsWindowVisible (SysMenu_window))
   {
     // ������ �ਭ� ࠬ�� ����.
     INT Frame_width = 0; FindProperty (Frame_window, PRP_BORDER, &Frame_width);
     if (!Frame_width) Frame_width = FrameWidth (Frame_window);

     // ������ �ᯮ������� ���� ���⨭��.
     SWP SysMenu_placement = {0}; WinQueryWindowPos (SysMenu_window, &SysMenu_placement);

     // �᫨ ��� �ᯮ������ �� ᢮�� ����:
     INT Y_middle_line = Frame_rectangle.yTop - Frame_width - TitleBar_height / 2;

     if (SysMenu_placement.y < Y_middle_line) if (SysMenu_placement.y + SysMenu_placement.cy > Y_middle_line)
     {
       // ������ �ᯮ������� ���� ���������.
       SWP TitleBar_placement = {0}; WinQueryWindowPos (TitleBar_window, &TitleBar_placement);

       // �᫨ ��������� �ᯮ����� �� �� ᢮�� ����:
       if (TitleBar_placement.y > Y_middle_line || TitleBar_placement.y + TitleBar_placement.cy < Y_middle_line)
       {
         // ������塞 ����.
         UpdateWindow (Frame_window);

         // ������.
         return;
       }
     }
   }

  // ������, ����� �� �ᮢ��� ��� ���� ���� ������.
  BYTE Draw_new_buttons = 0;

  if (Painter.Settings.Draw_buttons)
  {
    // ������, �뫮 �� ��।����� ���ﭨ� ������.
    BYTE Actions_are_detected = 0; FindProperty (Frame_window, PRP_ACTIONS, &Actions_are_detected);

    // �᫨ ��� �����⭮ - ������ ����� �ᮢ���.
    if (Actions_are_detected) Draw_new_buttons = Painter_PermissionForButtonsDrawing (Frame_window);
  }

  // ������ 㬥��襭�� � 㢥��祭�� ���� ���� ����� � ᦠ�� � "|". �஬� ⮣�, ࠬ��
  // ����� ᮤ�ঠ�� ��᪮�쪮 ������ ᫥�� � �ࠢ� �� ���������, �� ���� ��।������.
  BYTE Advanced_controls = 0;

  // �᫨ ���� �ᮢ��� ࠬ�� ��� ���������:
  if (Target & WT_UNKNOWN || Target & WT_BORDER || Target & WT_TITLEBAR)
  {
    // ��।������ ���� � ��������� � ������ ���室�騥 梥�.
    if (TitleBar_window != NULLHANDLE || MinMax_window != NULLHANDLE)
     if (Painter_PermissionForCompleteDrawing (Frame_window))
      Advanced_controls = Painter_PrepareWindowControls (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, TitleBar_window, SysMenu_window, MinMax_window);

    // �᫨ �ࠢ� �� ��������� �뫨 ������� �������⥫�� ���� - ���������� ��.
    if (Advanced_controls) SetProperty (Frame_window, PRP_CONTROLS, &Advanced_controls);
  }

  // ���㥬 ���� ������ � �ࠢ�� ���孥� 㣫� ����.
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

  // ���㥬 ���⨭�� � ����� ���孥� 㣫� ����.
  if (Painter.Settings.Draw_system_menus)
   if (Target & WT_UNKNOWN || Target & WT_SYSMENU)
    if (SysMenu_window != NULLHANDLE)
    {
      // ���㥬 ���⨭��.
      HPOINTER Icon = NULLHANDLE; FindProperty (Frame_window, PRP_ICON, &Icon);

      for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
      {
        if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
        Painter_DrawSystemMenu (SysMenu_window, Frame_window, &Frame_rectangle, &Frame_placement, Icon, Frame_type, 0);
        if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
      }

      // �᫨ ���� ���⨭�� ����뢠�� ࠬ�� - ����ᮢ뢠�� ��.
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

  // ���㥬 ��������� ����.
  if (Painter.Settings.Draw_titles)
   if (Target & WT_UNKNOWN || Target & WT_TITLEBAR)
    if (TitleBar_window != NULLHANDLE)
    {
      // ���㥬 ���������. ���쪮 ����ન���� ��� ��ꥬ ����� - ����� ��������� ���� � ������襭�� ���������� � ����ﬨ �� ���.
      CHAR Title[SIZE_OF_TITLE] = ""; FindProperty (Frame_window, PRP_TITLE, Title);

      for (INT Step = 0; Step < MAX_FCHECKS; Step ++)
      {
        if (Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);
        Painter_DrawTitleBar (TitleBar_window, Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, Title, Window_is_active, Advanced_controls);
        if (Step != MAX_FCHECKS - 1) if (!Painter_FrameRectangleIsChanged (Frame_window, &Frame_rectangle, &Frame_placement)) break;
      }
    }

  // ������.
  return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��. Thread - ��⮪.
VOID Painter_PainterMessageProcessing (PQMSG Message, HAB Thread)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Painter->Priority = MAKELONG (Class, Delta);
  }

  // ����ᮢ뢠�� ࠬ�� ����.
  if (Message->msg == SM_DRAW_FRAME)
  {
    // �᫨ �ᮢ���� �⪫�祭� - ������.
    if (!Painter.Settings.Draw_frames) return;

    // ��� ��ண� �஢��: ��ꥤ��塞 ��᪮�쪮 ������� � ����.
   {
     // �⠢�� ������� � ᯨ᮪.
     Painter.RTSettings.Demand[0].Frame_window = (HWND) Message->mp1;
     Painter.RTSettings.Demand[0].Target = (ULONG) Message->mp2;

     // ����ࠥ� ᫥���騥 ������� �� ��।� � �⠢�� �� � ᯨ᮪.
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

     // ��ᬠ�ਢ��� ��⠢����� ᯨ᮪ � �믮��塞 �ᮢ����.
     for (Count = 0; Count < Demand_total; Count ++)
     {
       // ������ ���� ࠬ��.
       HWND Frame_window = Painter.RTSettings.Demand[Count].Frame_window;
       // �᫨ � ᯨ᪥ ��� ���祭�� - �த������ ��ॡ��.
       if (Frame_window == NULLHANDLE) continue;

       // ������, ����� ���� ���� ����ᮢ���.
       ULONG Target = Painter.RTSettings.Demand[Count].Target;

       // �஡����� ᯨ᮪ �� ���� � ����ࠥ� ������� ��� ⮣� �� ����.
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

       // �᫨ ���� ��� - �த������ ��ॡ��.
       if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) continue;

       // ����ᮢ뢠�� ࠬ��, �ਬ���� "��饥 �������".
       Painter_DrawWindowFrame (Frame_window, Target);
     }
   }
  }

  // ����ᮢ뢠�� ���⨭�� � ����� ���孥� 㣫� ����.
  if (Message->msg == SM_DRAW_SYSMENU)
  {
    // �᫨ �ᮢ���� �⪫�祭� - ������.
    if (!Painter.Settings.Draw_frames) return;

    // ������ ���� ���⨭��.
    HWND SysMenu_window = (HWND) Message->mp1;

    // �᫨ ���� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

    // ������, ����� �� ���⨭��.
    LONG SysMenu_is_pressed = (LONG) Message->mp2;

    // ��室�� � ᯨ᪥ ���箪 ����.
    HPOINTER Icon = NULLHANDLE;
    HWND Frame_window = WinQueryWindow (SysMenu_window, QW_PARENT);

    FindProperty (Frame_window, PRP_ICON, &Icon);

    // ������ ࠧ��� � �ᯮ������� ���� ࠬ��.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // �᫨ ���箪 �� ������ - ����訢��� ���� ���⨭��.
    if (Icon == NULLHANDLE) Painter_PreDrawControl (SysMenu_window, SYSCLR_BUTTONMIDDLE, 0, Frame_window, &Frame_rectangle, &Frame_placement);
    // ���� - ��㥬 ���⨭��.
    else Painter_DrawSystemMenu (SysMenu_window, Frame_window, &Frame_rectangle, &Frame_placement, Icon, FT_UNKNOWN, SysMenu_is_pressed);
  }

  // ����ᮢ뢠�� ������.
  if (Message->msg == SM_DRAW_BUTTONS)
  {
    // �᫨ �ᮢ���� �⪫�祭� - ������.
    if (!Painter.Settings.Draw_frames) return;

    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ࠬ�� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ������, ��� �룫廊� ࠬ�� ����.
    LONG Frame_type = FrameType (Frame_window);

    // ������ ���� ���������.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // ������ ࠧ��� � �ᯮ������� ���� ࠬ��.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // ���㥬 ������.
    Painter_DrawButtons (Frame_window, Frame_type, &Frame_rectangle, &Frame_placement, TitleBar_window);
  }

  // ������ ���室�饥 �ᯮ������� ��� ���� ���⨭�� � ������.
  if (Message->msg == SM_PREPARE_CONTROLS)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // �᫨ ���� ࠬ�� ��� - ������.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // ������ ࠧ��� � �ᯮ������� ����.
    RECT Frame_rectangle = {0}; SWP Frame_placement = {0};
    Painter_QueryFrameRectangeAndPlacement (Frame_window, &Frame_rectangle, &Frame_placement);

    // ������ �ࠢ��쭮� �ᯮ������� ���� ���⨭��, ��������� � ��㣨� ����.
    // �� �⮬ ���� ࠬ�� ������ ���� ᮮ�饭�� WM_PAINT ����� ��᪮�쪨�.
    Painter_PrepareWindowControls (Frame_window, FT_UNKNOWN, &Frame_rectangle, &Frame_placement, NULLHANDLE, NULLHANDLE, NULLHANDLE);
  }

  // ������塞 ����.
  if (Message->msg == SM_UPDATE_FRAME) UpdateWindow ((HWND) Message->mp1);

  // ������塞 �� ����.
  if (Message->msg == SM_UPDATE_ALL_FRAMES)
  {
    // ����ᮢ뢠�� ࠬ�� ��� ����.
    UpdateAllWindows (QueryDesktopWindow ());
  }

  // ������.
  return;
}

// ��� ��⮪ ��� �ᮢ���� ࠬ�� ���

VOID Painter_PainterThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Painter->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Painter->Message_queue == NULLHANDLE)
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
    Painter_PainterMessageProcessing (&Message, Thread);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
