// ��� ������ � �訡���, ��뢠�饩 "�������" ࠬ�� ���

// Message_queue - ��।�, � ������ ���ࠢ����� ᮮ�饭�� WM_MARK.
VOID Painter_DetectPermanentDrawing (HWND Frame_window, HMQ Message_queue)
{
  // �᫨ ����� ������ ��� - �� ����� ���� ��।�������� ����, ������.
  if (MouseIsBusy ()) return;

  // �᫨ �� ���� VIO ��� ᯨ᮪ ���� - ������.
  if (IsVIOWindow (Frame_window) || IsWinListWindow (Frame_window)) return;

  // ������ ⥪�饥 �६�.
  LONG Current_time = WinGetCurrentTime (Enhancer.Application);

  // ��室�� ��।� � ᯨ᪥.
  PMSGQUEUEINFO Target = NULL;

  for (INT Count = PAINTER_MONITORING_QUEUES - 1; Count >= 0; Count --)
   if (Painter.RTSettings.Drawing_windows[Count].Queue == Message_queue)
   {
     Target = &Painter.RTSettings.Drawing_windows[Count]; break;
   }

  // �᫨ ��।� ᮮ�饭�� ��� � ᯨ᪥:
  if (Target == NULL)
  {
    // �������� ᯨ᮪.
    for (INT Count = 0; Count < PAINTER_MONITORING_QUEUES - 1; Count ++)
     memcpy (&Painter.RTSettings.Drawing_windows[Count], &Painter.RTSettings.Drawing_windows[Count + 1], sizeof (MSGQUEUEINFO));

    // ���������� ��।� ᮮ�饭��.
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Queue = Message_queue;

    // ��⠭�������� ���稪 � ���祭�� "1" � ���������� �६� ��� ���������.
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Quantity = 1;
    Painter.RTSettings.Drawing_windows[PAINTER_MONITORING_QUEUES - 1].Time = Current_time;

    // ������.
    return;
  }

  // �᫨ ��᫥ 㢥��祭�� ���稪� ��諮 �����筮 ����� �६���:
  if (Current_time > Target->Time)
   if (Current_time - Target->Time > Painter.Constants.Drawing_check_timeout)
   {
     // ��⠭�������� ���稪 � ���祭�� 1 � ���������� �६� ��� ���������.
     Target->Quantity = 1; Target->Time = Current_time;

     // ������.
     return;
   }

  // �᫨ ���稪 ���⨣ ����让 ����稭�:
  if (Target->Quantity > Painter.Constants.Permanent_drawing)
  {
    // ����뢠�� �� ���稪�.
    bzero (&Painter.RTSettings.Drawing_windows, sizeof (Painter.RTSettings.Drawing_windows));

    // ���������� PID �ਫ������, ᮧ���襣� ����.
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

    // �᫨ �� ᤥ���� �� 㤠����:
    if (!Success)
    {
      // �⪫�砥� �ᮢ���� ࠬ��.
      Painter.Settings.Draw_frames = 0;

      // ����ᮢ뢠�� ࠬ�� ��� ����. ������� ���� ᮮ�饭�� �����뢠�� ����� - �ਫ������ ������ �� �⮬.
      WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_UPDATE_ALL_FRAMES, 0, 0);
    }
  }

  // �����稢��� ���稪 � ���������� �६� ��� ���������.
  Target->Quantity ++; Target->Time = Current_time;

  // ������.
  return;
}

// ��� ��ࠡ��뢠�� ᮮ�饭�� � �ᮢ���� ���

// �� ��६���� - ���譨�.
VOID Painter_NiceWindowsPaintMsgNode (ULONG Message, MPARAM First_parameter, HWND Frame_window, LONG Frame_type, HWND Window, LONG Window_type)
{
  // ����� �ᮢ��� ࠬ�� ����� ���������. ��� �⮣� ���� ������ ᢮� ��ࠡ��稪�
  // ᮮ�饭�� ��� ���� ���⨭��, ���������, ������ � ���� � �� �믮����� �ᮢ����.
  // � �������� ����� �������� ��ࠡ��稪� �� ᫥���.
  BYTE SubClassing = 1;
  if (Window_type == WT_BORDER || Window_type == WT_SYSMENU) SubClassing = 0;

  // �᫨ �� ����� ᤥ����:
  if (SubClassing)
  {
    // �롨ࠥ� ��ࠡ��稪 ᮮ�饭��.
    PFNWP New_performer = NULL;

    if (Window_type == WT_TITLEBAR) New_performer = (PFNWP) Painter_TitleBarWindowHook;
    if (Window_type == WT_MINMAX)   New_performer = (PFNWP) Painter_MinMaxWindowHook;
    if (Window_type == WT_MENU)     New_performer = (PFNWP) Painter_MenuWindowHook;

    // �᫨ �� ��࠭:
    if (New_performer != NULL)
    {
      // �᫨ �� �� ��ࠡ��稪 ����⥫� - �����塞 ���.
      PFNWP Current_performer = (PFNWP) WinQueryWindowPtr (Window, QWP_PFNWP);
      if (Current_performer != New_performer) Painter_SubClassWindow (Frame_window, Window, Window_type);

      // ������.
      return;
    }
  }

  // �᫨ �ॡ������� ��ࠡ���� ᮮ�饭�� ��� ���� ������ ������ - ������.
  if (Window_type == WT_MINMAX) return;

  // �᫨ �ॡ������� ����ᮢ��� ࠬ��, �� �� ����� �� ���� - ������.
  if (Window_type == WT_BORDER) if (!Painter_FrameDrawingIsRequired ()) return;

  // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. � ⮬� �६���, ����� ��� �ਤ��, ����
  // 㦥 �㤥� ����ᮢ���, � ⮣�� ������ ���� ����� �ᮢ��� ��-� �����. ��-��
  // ���������� ᮮ�饭�� ����� ��������� �訡��.
  {
    // ������ ��।� ᮮ�饭��.
    HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);

    // ��६�� � �訡���, ��뢠�饩 "�������" ࠬ��.
    if (Message == WM_PAINT)
     if (Window_type == WT_BORDER)
      Painter_DetectPermanentDrawing (Frame_window, Message_queue);

    // ���뫠�� ᮮ�饭�� � ��।�.
    WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Window);
  }

  // ������.
  return;
}

// ��� ��ࠡ��뢠�� ᮮ�饭�� WM_MARK ���

// *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
VOID Painter_NiceWindowsMarkMsgNode (MPARAM Second_parameter)
{
  // ������ ����, ���஥ ������ ���� ����ᮢ���.
  HWND Target_window = (HWND) Second_parameter;

  // ������, ����� �� ����.
  ULONG Target = WindowType (Target_window);

  // ������ ���� ࠬ��.
  HWND Frame_window = QueryFrameWindow (Target_window);

  // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
  WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Target);

  // ������.
  return;
}

// ��� ����ᮢ뢠�� ࠬ�� ���� ���

// Window - ����, Message � *_parameter - ᮮ�饭��, ���஥ ��।����� ����.
VOID Painter_NiceWindows (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �᫨ ���� ����砥� ᮮ�饭�� � ⮬, �� ��� ������ ���� ����ᮢ���:
  if (Message == WM_PAINT || Message == TBM_SETHILITE || Message == WM_ACTIVATE)
  {
    // ������, ����� �� ����ᮢ��� ����, � ⠪�� ࠬ�� ����.
    LONG Window_type = WT_UNKNOWN;
    HWND Frame_window = Painter_PermissionForDrawing (Window, &Window_type);

    // �᫨ ࠬ�� �ᮢ��� �����:
    if (Frame_window != NULLHANDLE)
    {
      // ������, ��� �룫廊� ࠬ�� ����.
      LONG Frame_type = FrameType (Frame_window);

      // ��ࠡ��뢠�� ᮮ�饭��.
      Painter_NiceWindowsPaintMsgNode (Message, First_parameter, Frame_window, Frame_type, Window, Window_type);

      // �᫨ � ���� ���� ��������� � ������:
      if (Frame_type != FT_FLAT)
      {
        // �᫨ ���� ������ ���� ����ᮢ��� - 㧭��� ���⨭��, ��������� � ���ﭨ� ������.
        if (Message == WM_PAINT)
        {
          BYTE Query_properties = 0;

          if (Painter.Settings.Draw_system_menus) if (Window_type == WT_SYSMENU)  Query_properties = 1;
          if (Painter.Settings.Draw_titles)       if (Window_type == WT_TITLEBAR) Query_properties = 1;
          if (Painter.Settings.Draw_buttons)      if (Window_type == WT_BORDER)   Query_properties = 1;

          if (Query_properties) WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_QUERY_PROPERTIES, (MPARAM) Frame_window, (MPARAM) Window_type);
        }

        // �᫨ ������� ���� �ਫ������ �⠭������ ��࠭�� - �஢��塞 ���ﭨ� ��㣨� ����.
        if (Message == TBM_SETHILITE) if (First_parameter == (MPARAM) 1)
         if (Frame_window == QueryMainWindow (Frame_window))
          WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_CHECK_CONTROLS, (MPARAM) Frame_window, 0);
      }
    }

    // ����� ��� ���� ����ﭭ��� ࠧ��� ����� ����뢠�� ���୨� ����, ���ਬ��,
    // ���� ࠡ�祩 ������. ����� ��� ����ᮢ뢠����, �� ���� �஢�����.
    if (Painter.Settings.Draw_const_frames) if (Painter.Settings.Draw_volume_lines)
     if (Message == WM_PAINT)
     {
       // �᫨ ���� ࠬ�� �������⭮ - 㧭��� ���.
       if (Frame_window == NULLHANDLE) Frame_window = QueryFrameWindow (Window);

       // �᫨ ���� ����� ࠬ�� ����ﭭ��� ࠧ���:
       if (Frame_window != NULLHANDLE && Frame_window != Window)
        if (FrameType (Frame_window) == FT_CONST)
        {
          // �᫨ ����, ���஥ ���� ����ᮢ���, �� ��������� � �� ������:
          LONG Window_type = WindowType (Window);

          if (Window_type != WT_SYSMENU && Window_type != WT_TITLEBAR &&
              Window_type != WT_MINMAX  && Window_type != WT_MENU )
          {
            // �᫨ ���� ࠬ�� ����� ���� ����ᮢ���:
            if (Painter_PermissionForDrawing (Frame_window))
            {
              // ���뫠�� ᮮ�饭�� � ��⮪.
              WinPostQueueMsg (Enhancer.Modules.Diver->Message_queue, SM_CHECK_FRAME, (MPARAM) Frame_window, (MPARAM) Window);
            }
          }
        }
     }
  }

  // ��ࠡ��뢠�� ᮮ�饭�� WM_MARK, ���஥ ��室�� � ��।� ����.
  if (Window == NULLHANDLE) if (Message == WM_MARK)
   if (First_parameter == (MPARAM) MRK_DRAW_FRAME)
    Painter_NiceWindowsMarkMsgNode (Second_parameter);

  // �� �����⨨ ���� - 㤠�塞 ��� �� ᯨ᪠.
  if (Message == WM_DESTROY)
   if (IsFrameWindow (Window))
    DiscardUnusedProperties (Window);

  // ������.
  return;
}

// ��� ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ���� ��� � ��।� ���� ���

// Frame_window - ���� ࠬ��.
VOID Painter_NiceControlsDrawingNode (HWND Frame_window)
{
  // ����ᮢ뢠�� ࠬ�� ��࠭���� ����.
  HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Frame_window);

  // ����ᮢ뢠�� ���⨭�� � ����� ���孥� 㣫� ����.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);
  if (SysMenu_window != NULLHANDLE) WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) SysMenu_window);

  // ������.
  return;
}

// ��� ��ࠡ��뢠�� ᮮ�饭�� WM_MARK ���

// *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
VOID Painter_NiceControlsMarkMsgNode (MPARAM First_parameter, MPARAM Second_parameter)
{
  // ������ ����, ���஥ ������ ���� ����ᮢ���.
  HWND Control_window = (HWND) Second_parameter;

  // �᫨ �� ����⢨⥫쭮 ���� ���⨭��:
  if (WindowType (Control_window) == WT_SYSMENU)
  {
    // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
    LONG Control_is_pressed = 0;
    if (First_parameter == (MPARAM) MRK_PRESS_SYSMENU) Control_is_pressed = 1;

    WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_SYSMENU, (MPARAM) Control_window, (MPARAM) Control_is_pressed);
  }

  // ������.
  return;
}

// ��� ��ࠡ��뢠�� ᮮ�饭�� WM_MENUSELECT ���

// *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
VOID Painter_NiceControlsMenuSelectMsgNode (MPARAM Second_parameter)
{
  // �᫨ �뫠 ����� ���⨭�� � ����� ���孥� 㣫� ����, � ��⥬ �����
  // ������ Esc ��� ������ ���, �⮡� ���� ���� - ��㥬 ࠬ�� ��� ����.

  // ������ ���� ����.
  HWND Menu_window = (HWND) Second_parameter;

  // ������, ����� �� ����ᮢ��� ����, � ⠪�� ࠬ�� ����.
  LONG Window_type = WT_UNKNOWN;
  HWND Frame_window = Painter_PermissionForDrawing (Menu_window, &Window_type);

  // �᫨ ࠬ�� �ᮢ��� ����� - ������.
  if (Frame_window == NULLHANDLE) return;

  // �᫨ �� ᮮ�饭�� �� ���� ���⨭��:
  if (Window_type == WT_SYSMENU)
  {
    // ������, ����� �� ���⨭��.
    LONG SysMenu_is_pressed = 0;
    if (MouseIsBusy ()) if (WindowIsActive (Frame_window))
    {
      // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
      HWND Desktop = QueryDesktopWindow ();

      POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
      HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);

      // �᫨ �� ���� ���⨭�� - ��� �����.
      if (Window == Menu_window) SysMenu_is_pressed = 1;
    }

    // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �ਤ��, ���⨭�� ����� �㤥� ����ᮢ���.
    MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;
    if (SysMenu_is_pressed) First_parameter = (MPARAM) MRK_PRESS_SYSMENU;

    HMQ Message_queue = WinQueryWindowULong (Menu_window, QWL_HMQ);
    WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Menu_window);

    // ����ᮢ뢠�� ���� ���⨭��, ���஥ �뫮 ��࠭� ࠭��.
    if (Painter.RTSettings.Prev_selected_menu != NULLHANDLE)
     if (Painter.RTSettings.Prev_selected_menu != Menu_window)
     {
       // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �ਤ��, ���⨭�� ����� �㤥� ����ᮢ���.
       MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;

       HMQ Message_queue = WinQueryWindowULong (Painter.RTSettings.Prev_selected_menu, QWL_HMQ);
       WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Painter.RTSettings.Prev_selected_menu);
     }

    // ���������� ���� ���⨭��.
    Painter.RTSettings.Prev_selected_menu = Menu_window;
  }
  // � �᫨ ��࠭� ����:
  else
  {
    // ����ᮢ뢠�� ���� ���⨭��, ���஥ �뫮 ��࠭� ࠭��.
    if (Painter.RTSettings.Prev_selected_menu != Menu_window)
    {
      // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �ਤ��, ���⨭�� ����� �㤥� ����ᮢ���.
      MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;

      HMQ Message_queue = WinQueryWindowULong (Painter.RTSettings.Prev_selected_menu, QWL_HMQ);
      WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) Painter.RTSettings.Prev_selected_menu);
    }

    // ��࠭��� ���� ���⨭�� - �������⭮.
    Painter.RTSettings.Prev_selected_menu = NULLHANDLE;
  }

  // ������.
  return;
}

// ��� ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ���� ��� � ��।� ���� ���

// Frame_window - ���� ࠬ��, SysMenu_is_pressed - �� ���ﭨ�.
VOID Painter_AnimateButtonsDrawingNode (HWND Frame_window, BYTE SysMenu_is_pressed)
{
  // ����ᮢ뢠�� ���⨭�� � ����� ���孥� 㣫� ����.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  MPARAM First_parameter = (MPARAM) MRK_DRAW_SYSMENU;
  if (SysMenu_is_pressed) First_parameter = (MPARAM) MRK_PRESS_SYSMENU;

  HMQ Message_queue = WinQueryWindowULong (SysMenu_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, First_parameter, (MPARAM) SysMenu_window);

  // ������.
  return;
}

// ��� ��ࠡ��뢠�� ������ �� ������ � ��������� ���� ���

// Frame_window - ���� ࠬ��, Message - ᮮ�饭��, Control_window - �����⥫� ᮮ�饭��, Window_type - ����� �� ����.
// �����頥��� ���祭��: �᫨ ᮮ�饭�� ��ࠡ�⠭� � ��� ���� ���� �� ��।�, � 1, ���� 0.
BYTE Painter_AnimateButtons (HWND Frame_window, LONG Message, HWND Control_window, LONG Window_type, PPOINT Point)
{
  // �᫨ ���� �ᮢ��� ���⨭�� � ����� ���孥� 㣫� ����:
  if (Painter.Settings.Draw_system_menus)
  {
    // �᫨ 㪠��⥫� ��� �ᯮ����� ��� ���⨭���:
    if (Window_type == WT_SYSMENU)
    {
      // ������ ���⨭�� ����⮩.
      Painter.RTSettings.Selected_button = SYSMENU_ACTION;

      // ����ᮢ뢠�� ��.
      BYTE Control_is_pressed = 0;
      if (Painter.RTSettings.Selected_button == SYSMENU_ACTION) Control_is_pressed = 1;

      Painter_AnimateButtonsDrawingNode (Frame_window, Control_is_pressed);

      // ������.
      return 0;
    }
    // � �᫨ 㪠��⥫� �ᯮ����� �� ��� ���⨭���, � ��� �뫠 �����:
    else
    {
      if (Painter.RTSettings.Selected_button == SYSMENU_ACTION)
      {
        // ������ �� ������.
        Painter.RTSettings.Selected_button = NO_ACTION;

        // ����ᮢ뢠�� ��.
        Painter_AnimateButtonsDrawingNode (Frame_window, 0);
      }
    }
  }

  // �᫨ ���� �ᮢ��� ������:
  if (Painter.Settings.Draw_buttons)
  {
    // ������ ࠧ��� ���� ࠬ��.
    RECT Rectangle = {0}; WinQueryWindowRect (Frame_window, &Rectangle);

    // ������ ���� ���������.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // ������ ࠧ��� ���� ���������.
    RECT TitleBar_rectangle = {0}; WinQueryWindowRect (TitleBar_window, &TitleBar_rectangle);

    // ������ ��אַ㣮�쭨�� ��� ������.
    RECT Max_button = {0}; RECT Min_button = {0}; RECT Rollup_button = {0}; RECT Close_button = {0}; RECT All_buttons = {0};
    Painter_CalculateButtonRectangles (Frame_window, &Rectangle, TitleBar_window, &TitleBar_rectangle, &Max_button, &Min_button, &Rollup_button, &Close_button, &All_buttons);

    // ������ ���ﭨ� ������ � ����.
    LONG Buttons = NO_ACTION; FindProperty (Frame_window, PRP_BUTTONS, &Buttons);

    // �஢��塞, ��� ����� ������� �ᯮ����� 㪠��⥫� ���.
    for (INT Count = 0; Count < 4; Count ++)
    {
      // �롨ࠥ� ��אַ㣮�쭨� � ����⢨�.
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

      // �᫨ ������ ��� - �த������ ��ॡ��.
      if (Current_button == NULL) continue;

      // ������ ����� �� ��� ������.
      INT Pixel_margin = Painter_GetButtonPixelMargin ();

      // �᫨ 㪠��⥫� ��� �ᯮ����� ��� ��אַ㣮�쭨��� ��� ������:
      if (Point->x >= Current_button->xLeft + Pixel_margin && Point->x <= Current_button->xRight - Pixel_margin &&
          Point->y >= Current_button->yBottom + Pixel_margin && Point->y <= Current_button->yTop - Pixel_margin)
      {
        // �᫨ ������ �뫠 ����� - ������.
        if (Painter.RTSettings.Selected_button == Action) return 1;

        // ������ ������ � ��������� ����⮩.
        Painter.RTSettings.Selected_button = Action;

        // ��뢠�� ���� ������ � ������ ��� ��࠭��. ����� ���뫠�� ᮮ�饭��
        // � ��⮪, �� �� �⮬ ������� ���� �� �⢥��� �� ᮮ�饭�� WM_SYSCOMMAND.
        if (Message != WM_MOUSEMOVE) MoveWindowAbove (Frame_window);

        // ����ᮢ뢠�� ������. ���뫠�� ᮮ�饭�� � ��⮪.
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_BUTTONS, (MPARAM) Frame_window, 0);

        // ������.
        return 1;
      }
      // � �᫨ 㪠��⥫� �ᯮ����� ��� ��㣮� ������� � ࠭�� �� ������ �뫠 �����:
      else if (Painter.RTSettings.Selected_button == Action)
      {
        // ������ �� ������.
        Painter.RTSettings.Selected_button = NO_ACTION;

        // ����ᮢ뢠�� ������. ���뫠�� ᮮ�饭�� � ��⮪.
        WinPostQueueMsg (Enhancer.Modules.Painter->Message_queue, SM_DRAW_BUTTONS, (MPARAM) Frame_window, 0);
      }
    }
  }

  // ������.
  return 0;
}

// ��� ��ࠡ��뢠�� ������ �� ������ � ��������� ���� ���

// Message - ᮮ�饭��, ���஥ ��।����� ������ �� ����.
VOID Painter_NiceControls (PQMSG Message)
{
  // ��ࠡ��뢠�� ������ �� ������ � ��������� ����.
  // �� ����⨨ �� ������ ���� ��������� ����. �� ��।������� ���, �᫨ ������
  // �����, ���� ����ᮢ��� ࠬ��. �� �⦠⨨ - �믮����� ��।������� ����⢨�.

  // �᫨ �� ������ � ��������� �뫨 � �⦠⮬ ���ﭨ�:
  if (Painter.RTSettings.Selected_window == NULLHANDLE)
  {
    // �᫨ ����� ������ ��� - ���������� ���� � ��㥬 ������ � ��������� ����⮩.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
        Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
    {
      // ������, ����� �� ����ᮢ��� ����, � ⠪�� ࠬ�� ����.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Message->hwnd, &Window_type);

      // �᫨ ࠬ�� �ᮢ��� ����� - ������.
      if (Frame_window == NULLHANDLE) return;

      // �᫨ 㪠��⥫� �ᯮ����� ��� ࠬ���, ���������� ��� ���⨭��� � ����� ���孥� 㣫� ����:
      if (Window_type == WT_BORDER || Window_type == WT_SYSMENU || Window_type == WT_TITLEBAR)
      {
        // �᫨ ������ �ᮢ��� ����� - ������.
        if (!Painter_PermissionForButtonsDrawing (Frame_window)) return;

        // ���������� ��࠭��� ����.
        Painter.RTSettings.Selected_window = Frame_window;

        // ���㥬 ���� �� ������ � ��������� ����⮩.
        POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
        BYTE Button_is_pressed = Painter_AnimateButtons (Frame_window, Message->msg, Message->hwnd, Window_type, &Mouse_point);

        // �᫨ ����� ������ � ��������� ���� - ��� ᮮ�饭��.
        if (Button_is_pressed)
        {
          Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
        }
        // � �᫨ ������ �� �����:
        else
        {
          // �� ������� ����⨨ �ࠢ�� ������ ��� � ��������� ���� ������ ���� �࠭� ������.
          if (Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
           if (Window_type == WT_TITLEBAR)
           {
             // ���� ������ ���� �࠭� ������ �᫨ ��� 㢥��祭�.
             BYTE Rollup_window = 0;

             // ������ ���ﭨ� ������ � ����.
             LONG Buttons = 0;

             if (Painter.Settings.Draw_buttons) FindProperty (Frame_window, PRP_BUTTONS, &Buttons);
             else Buttons = Painter_QueryButtonsState (Frame_window, MAXIMIZE_ACTION, 1);

             if (Buttons & ROLLUP_ACTION)
              if (Painter_PermissionForRolling (Frame_window))
               Rollup_window = 1;

             // ���ࠥ� ���� ������.
             if (Rollup_window)
             {
               // ���뫠�� ᮮ�饭�� � ��⮪.
               WinPostQueueMsg (Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Frame_window, (MPARAM) ROLLUP_ACTION);

               // ����뢠�� ᮮ�饭��.
               Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
             }
           }
        }
      }
    }
  }
  // �᫨ ���� �� ������ � ��������� �뫠 � ����⮬ ���ﭨ�:
  else
  {
    // �᫨ ���� �������� - ��㥬 ������ � ��������� ����. ���� �� ��� �⠭������ ����⮩.
    if (Message->msg == WM_MOUSEMOVE)
    {
      // �� ����⨨ �� ��������� ���� ᮮ�饭�� WM_BUTTONUP ������ - ������ ��⠭����.
      BYTE Stop_animation = 0; if (!MouseIsBusy ()) Stop_animation = 1;

      // ��� �� �� ��४��祭�� � ��㣮� ���� � ������� Ctrl + Esc.
      if (Painter.RTSettings.Selected_window != NULLHANDLE)
       if (!WindowIsActive (Painter.RTSettings.Selected_window))
        if (!MouseIsBusy ())
         Stop_animation = 1;

      // �४�頥� ᫥����� �� �����, �᫨ �� �ॡ����.
      if (Stop_animation)
      {
        // ������ �� ������, ��࠭��� ���� - �������⭮.
        HWND Window = Painter.RTSettings.Selected_window;
        Painter.RTSettings.Selected_window = NULLHANDLE;
        Painter.RTSettings.Selected_button = NO_ACTION;

        // ����ᮢ뢠�� ࠬ�� ��࠭���� ����.
        Painter_NiceControlsDrawingNode (Window);

        // ������.
        return;
      }

      // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
      HWND Desktop = QueryDesktopWindow ();

      POINT Pointer = {0}; WinQueryPointerPos (Desktop, &Pointer);
      HWND Window = WinWindowFromPoint (Desktop, &Pointer, 1);

      // ������, �� �� �� ����, � ⠪�� ���� ࠬ��.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Window, &Window_type);

      // �����⥫� ��� ����� ���� �ᯮ����� �� � ��࠭��� ����.
      HWND Control_window = Message->hwnd;

      if (Frame_window != Painter.RTSettings.Selected_window)
      {
        // ��ᮢ��� ���⨭�� � ������ ���� � ����⮬ ����.
        Frame_window = Painter.RTSettings.Selected_window; Window_type = WT_UNKNOWN;

        if (Painter.RTSettings.Selected_button == SYSMENU_ACTION) Control_window = WinWindowFromID (Frame_window, FID_SYSMENU);
        else Control_window = Frame_window;
      }

      // ���㥬 ������.
      POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
      Painter_AnimateButtons (Frame_window, Message->msg, Control_window, Window_type, &Mouse_point);
    }

    // �᫨ ����� �� ���� ������ ��� - ��� ᮮ�饭��.
    if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN ||
        Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK)
    {
      // ������, ����, ��� ����� �ᯮ����� 㪠��⥫� ���, � ⠪�� ���� ࠬ��.
      LONG Window_type = WT_UNKNOWN;
      HWND Frame_window = Painter_PermissionForDrawing (Message->hwnd, &Window_type);

      // �᫨ ���� ����� ���� ����ᮢ���:
      if (Frame_window != NULLHANDLE)
      {
        // �᫨ 㪠��⥫� ��� �ᯮ����� ��� �������� - ��� ᮮ�饭��.
        POINT Mouse_point = { SHORT1FROMMP (Message->mp1), SHORT2FROMMP (Message->mp1) };
        BYTE Button_is_pressed = Painter_AnimateButtons (Frame_window, Message->msg, Message->hwnd, Window_type, &Mouse_point);

        if (Button_is_pressed)
        {
          Message->msg = WM_NULL; Message->mp1 = NULL; Message->mp2 = NULL;
        }
      }
    }

    // �᫨ �⦠� ������ ��� - �믮��塞 ����⢨� � ��㥬 ������ � ���筮� ����.
    if (Message->msg == WM_BUTTON1UP || Message->msg == WM_BUTTON2UP || Message->msg == WM_BUTTON3UP)
    {
      // ������ �� ������, ��࠭��� ���� - �������⭮.
      HWND Window = Painter.RTSettings.Selected_window;
      LONG Command = Painter.RTSettings.Selected_button;
      Painter.RTSettings.Selected_window = NULLHANDLE;
      Painter.RTSettings.Selected_button = NO_ACTION;

      // ����ᮢ뢠�� ࠬ�� ��࠭���� ����.
      Painter_NiceControlsDrawingNode (Window);

      // �믮��塞 ��।������� ����⢨�. ���뫠�� ᮮ�饭�� � ��⮪.
      WinPostQueueMsg (Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Window, (MPARAM) Command);
    }
  }

  // ��ࠡ��뢠�� ᮮ�饭�� WM_MARK, ���஥ ��室�� � ��।� ��� ���� ���⨭��.
  if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK)
   if (Message->mp1 == (MPARAM) MRK_DRAW_SYSMENU || Message->mp1 == (MPARAM) MRK_PRESS_SYSMENU)
    Painter_NiceControlsMarkMsgNode (Message->mp1, Message->mp2);

  // ��६�� � ���஬ � �����. ��ࠡ��뢠�� ᮮ�饭�� WM_MENUSELECT.
  if (Painter.Settings.Draw_system_menus) if (Message->msg == WM_MENUSELECT)
   Painter_NiceControlsMenuSelectMsgNode (Message->mp2);

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PainterInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // ���㥬 ࠬ�� ��� ����.
  if (Painter.Settings.Draw_frames)
  {
    // ���㥬 ࠬ��.
    Painter_NiceWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

    // ��ࠡ��뢠�� ������ �� ���⨭�� � ������ � ��������� ����.
    Painter_NiceControls (Message);
  }

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PainterSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // ���㥬 ࠬ�� ��� ����.
  if (Painter.Settings.Draw_frames)
  {
    // ���㥬 ࠬ��.
    Painter_NiceWindows (Message->hwnd, Message->msg, Message->mp1, Message->mp2);

    // ��ࠡ��뢠�� ������ �� ���⨭�� � ������ � ��������� ����.
    if (Message->msg == WM_MENUSELECT)
    {
      QMSG Incoming_message = { Message->hwnd, Message->msg, Message->mp1, Message->mp2, NULL, NULL, NULL };
      Painter_NiceControls (&Incoming_message);
    }
  }

  // ������.
  return;
}

