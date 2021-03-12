
// ��� ������, ��࠭� �� ���� ���

// Frame_window - ���� ࠬ��.
BYTE WindowManagement_WindowIsActive (HWND Frame_window)
{
  // �᫨ ���� ��� - ������.
  if (Frame_window == NULLHANDLE) return 0;

  // �᫨ ���� ���� - ������.
  if (!WinIsWindowVisible (Frame_window)) return 0;

  // ������ த�⥫�᪮� ����.
  HWND Parent_window = WinQueryWindow (Frame_window, QW_PARENT);

  // �஢��塞 ����.
  if (Frame_window == WinQueryActiveWindow (Parent_window)) return 1;

  // ������.
  return 0;
}

// ��� �஢����, �ᯮ������ �� ���� �� �।����� �࠭� ���

// Window - ���� ��� �஢�ન.
BYTE WindowManagement_WindowIsOutOfTheScreen (HWND Window, PSWP Window_state)
{
  // ������ ࠧ��� �࠭�.
  HWND Desktop = QueryDesktopWindow ();

  INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
  INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

  // �஢��塞 �ᯮ������� ����. � ��砥, �᫨ ���� �ᯮ������ � �窥 (0, 0) ��⠥�, �� ��� �� �� ����㯭�.
  if (Window_state->x + Window_state->cx < 0) return 1;
  if (Window_state->y + Window_state->cy < 0) return 1;
  if (Window_state->x > X_Screen) return 1;
  if (Window_state->y > Y_Screen) return 1;

  // ������.
  return 0;
}

// ��� �஢����, ����� �� ��४������� � ���� ���

// Window - ����. �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE WindowManagement_PermissionForSwitching (HWND Window, BYTE Exclude_WPS_Shell = 1)
{
  // �᫨ ���� ��� - ������.
  if (Window == NULLHANDLE) return 0;

  // �᫨ ���� ���� - ������.
  if (!WinIsWindowVisible (Window)) return 0;

  // ������ �ᯮ������� ���� � ��� ���ﭨ�.
  SWP Window_state = {0}; WinQueryWindowPos (Window, &Window_state);

  // �᫨ ���� ���� ��� 㬥��襭� � ���箪 - ��४������� �����, ������.
  if (Window_state.fl & SWP_HIDE || Window_state.fl & SWP_MINIMIZE) return 0;

  // �᫨ ���� �ᯮ������ �� �।����� �࠭� - ��४������� �����, ������.
  if (WindowManagement_WindowIsOutOfTheScreen (Window, &Window_state)) return 0;

  #ifndef INCLUDED_BY_SHELL

  // �᫨ �� ���� �����窨 - ��४������� �����, ������.
  if (Exclude_WPS_Shell) if (HasShellPlacement (Window, &Window_state)) return 0;

  #endif

  // ������.
  return 1;
}

// ��� �஢����, ����㯭� �� ���� ࠬ�� ���

// Frame_window - ���� ࠬ��.
BYTE WindowManagement_FrameWindowIsAccessible (HWND Frame_window)
{
  // �᫨ � ���� ����� ��४������� �� ᯨ᪠ ���� - ��� ������㯭�.
  if (!WindowIsTouchable (Frame_window)) return 0;

  // �᫨ �� �����饥 ���� OS/2:
  if (!IsWindowsWindow (Frame_window))
  {
    // ������ ���� ���������.
    HWND TitleBar_window = WinWindowFromID (Frame_window, FID_TITLEBAR);

    // �᫨ ��� ��� - ���� ࠬ�� ������㯭�.
    if (TitleBar_window == NULLHANDLE) return 0;

    // �᫨ ���� ࠬ�� ������:
    if (WinIsWindowVisible (Frame_window))
    {
      // ������ �ᯮ������� ���� � ��� ���ﭨ�.
      SWP Window_state = {0}; WinQueryWindowPos (Frame_window, &Window_state);

      // �᫨ ���� �� ���� � �� 㬥��襭� � ���箪:
      if (!(Window_state.fl & SWP_HIDE)) if (!(Window_state.fl & SWP_MINIMIZE))
      {
        // �᫨ ���� �ᯮ������ �� �।����� �࠭� - ��� ������㯭�.
        if (WindowManagement_WindowIsOutOfTheScreen (Frame_window, &Window_state)) return 0;

        // �᫨ ���� ��������� �� �������� - ���� ࠬ�� ������㯭�.
        if (Window_state.x + Window_state.cx > 0)
         if (!WindowIsPresent (TitleBar_window)) return 0;
      }
    }
  }

  // ������.
  return 1;
}

// ��� ��뢠�� ���� � ������ ��� ��࠭�� ���

// Frame_window - ���� ࠬ��, ���஥ ���� �맢���.
BYTE WindowManagement_MoveWindowAbove (HWND Frame_window)
{
  // �᫨ ���� �� ��࠭�:
  if (!WindowManagement_WindowIsActive (Frame_window))
  {
    // �� ����� ���� ���� Win-OS/2 ��� Odin.
    BYTE Is_Windows_window = IsWindowsWindow (Frame_window);

    // ������ ���� ࠡ�祣� �⮫�.
    HWND Desktop = QueryDesktopWindow ();

    // ������ ������� ���� �ਫ������.
    HWND Main_window = QueryMainWindow (Frame_window);

    // �᫨ ��� �� ������� - ��뢠�� � ����, �� ������.
    if (Main_window == NULLHANDLE) Main_window = Frame_window;

    // �᫨ ���� ���� - ������ ��� ������.
    if (!WinIsWindowVisible (Main_window)) WinShowWindow (Main_window, 1);

    // ������� ���� �ਫ������ �⠭������ ��࠭��.
    if (Main_window != Frame_window)
    {
      if (!Is_Windows_window) WinSetActiveWindow (Desktop, Main_window);
      else WinSetWindowPos (Main_window, NULLHANDLE, 0, 0, 0, 0, SWP_ACTIVATE);
    }

    // ���� �⠭������ ��࠭��.
    if (!Is_Windows_window) WinSetActiveWindow (Desktop, Frame_window);
    else WinSetWindowPos (Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_ACTIVATE);

    // ������.
    return 1;
  }

  // ������.
  return 0;
}

// ��� ������ ����, �ᯮ�������� � �।��� �࠭� ���

HWND WindowManagement_WindowInCenter (BYTE Exclude_WPS_Shell = 1)
{
  // ������ ࠧ��� �࠭�.
  HWND Desktop = QueryDesktopWindow ();

  INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
  INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

  // ������ ���� ࠬ��, ���஥ �ᯮ������ � �।��� �࠭�.
  POINT Center_of_screen = { X_Screen / 2, Y_Screen / 2 };
  HWND Center_window = WinWindowFromPoint (Desktop, &Center_of_screen, 0);

  // ������ ����, ����� �ᯮ������ �冷� � ���, � ��⥬ �롨ࠥ� ���� �� ����.
  // � ⮬ �᫥ ������ ���� �������, ���ਬ��, ���� VIO ࠧ��஬ 80 x 25 ���⮪
  // � ���⮬ 10 x 6 �祪, �ᯮ�������� � 㣫� �࠭� ࠧ��஬ 1024 x 768 �祪.
  // �� �� ��ࢮ� ����⪥ ���᪠ ����� �� �।��� �࠭� ������ ���� ������訬,
  // ���� �㤥� �����㦥�� ��४��⨥ ����, ����� ���� VIO ࠧ��஬ 80 x 25 ���⮪
  // � ���⮬ 14 x 8 �ᯮ������ ��� ����� �ࠢ�筨�� ��� ⥪�⮢��� ।����.
  // ����� ����� ���� �襭� ���⥯���� 㢥��祭��� ������ ���᪠ �� 1/8 �� 1/4.
  HWND Target_window = NULLHANDLE; INT Max_steps = 5; INT Divisor = 8;

  for (INT Step = 0; Step < Max_steps; Step ++)
  {
    INT X_Step = X_Screen / Divisor;
    INT Y_Step = Y_Screen / Divisor;

    Divisor --;

    POINT Other_point_1 = { Center_of_screen.x + X_Step, Center_of_screen.y - Y_Step };
    HWND Other_window_1 = WinWindowFromPoint (Desktop, &Other_point_1, 0);

    POINT Other_point_2 = { Center_of_screen.x - X_Step, Center_of_screen.y + Y_Step };
    HWND Other_window_2 = WinWindowFromPoint (Desktop, &Other_point_2, 0);

    POINT Other_point_3 = { Center_of_screen.x + X_Step, Center_of_screen.y + Y_Step };
    HWND Other_window_3 = WinWindowFromPoint (Desktop, &Other_point_3, 0);

    POINT Other_point_4 = { Center_of_screen.x - X_Step, Center_of_screen.y - Y_Step };
    HWND Other_window_4 = WinWindowFromPoint (Desktop, &Other_point_4, 0);

    // �᫨ � ���� �� ���� ����� ��४������� - ��ࠥ� ��६�����.
    for (INT Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window == NULLHANDLE) continue;

      if (!IsFrameWindow (*Window) ||
          !WindowManagement_PermissionForSwitching (*Window, Exclude_WPS_Shell)) *Window = NULLHANDLE;
    }

    // �롨ࠥ� ���� ��� ��४��祭��.
    for (Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window != NULLHANDLE) { Target_window = *Window; break; }
    }

    // �᫨ �� ������ ���� ��� ��� �� ��� ������㯭� - �த������ ����⪨.
    if (Target_window == NULLHANDLE) continue;

    // � ��砥, �᫨ ���� ��४�뢠����, �㤥� ������� ��᪮�쪮 ����.
    BYTE Overflow = 0;

    for (Count = 0; Count < 5; Count ++)
    {
      PHWND Window = NULL;
      if (Count == 0) Window = &Center_window;
      if (Count == 1) Window = &Other_window_1;
      if (Count == 2) Window = &Other_window_2;
      if (Count == 3) Window = &Other_window_3;
      if (Count == 4) Window = &Other_window_4;

      if (*Window != NULLHANDLE && *Window != Target_window) { Overflow = 1; break; }
    }

    // �᫨ �����㦥�� ��४��⨥ - �����頥� ���� �� ����.
    // ��㣨� ����⮪ �� ������ - 㢥��稢��� ������� ���᪠ ��ᯮ�����.
    if (Overflow)
    {
      if (Center_window) return Center_window;
      if (Other_window_1) return Other_window_1;
      if (Other_window_2) return Other_window_2;
      if (Other_window_3) return Other_window_3;
      if (Other_window_4) return Other_window_4;
    }

    // �����頥� ��������� ����, �᫨ ��� ����.
    if (Target_window) return Target_window;
  }

  // �����頥� NULLHANDLE.
  return NULLHANDLE;
}

// ��� ������ ��࠭�� ����, ���஥ �ᯮ������ � �।��� �࠭� ���

// �����頥��� ���祭��: 1 - ���� �������, 0 - ���� �� �������.
BYTE WindowManagement_ActivateWindowInCenter (VOID)
{
  // ������ ��࠭�� ���� � �।��� �࠭�.
  HWND Window_in_center_without_WPS = WindowManagement_WindowInCenter ();

  if (Window_in_center_without_WPS != NULLHANDLE)
  {
    WindowManagement_MoveWindowAbove (Window_in_center_without_WPS); return 1;
  }
  else
  {
    HWND Window_in_center_with_WPS = WindowManagement_WindowInCenter (0);

    if (Window_in_center_with_WPS != NULLHANDLE)
    {
      WindowManagement_MoveWindowAbove (Window_in_center_with_WPS); return 1;
    }
    else
    {
      #ifndef INCLUDED_BY_SHELL

      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_PREV_WINDOW, 0);

      #endif
    }
  }

  // ������.
  return 0;
}

// ��� ���뢠�� ���� ࠬ��, ���������饥 �� �࠭� ���

// Frame_window - ���� ࠬ��, ���஥ ���� �����.
BYTE WindowManagement_HideWindowAway (HWND Frame_window)
{
  // �᫨ ���� � ⠪ 㦥 ������㯭� - ������.
  if (!WindowManagement_PermissionForSwitching (Frame_window)) return 0;

  // ������ ���� ���⨭��.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // �롨ࠥ� �������� ���室�饥 ����⢨�.
  ULONG Suitable_action = SWP_HIDE;

  if (SysMenu_window != NULLHANDLE)
   if (MenuItemIsPresent (SysMenu_window, SC_MINIMIZE))
    if (MenuItemIsEnabled (SysMenu_window, SC_MINIMIZE))
     Suitable_action = SWP_MINIMIZE;

  if (SysMenu_window != NULLHANDLE)
   if (MenuItemIsPresent (SysMenu_window, SC_HIDE))
    if (MenuItemIsEnabled (SysMenu_window, SC_HIDE))
     Suitable_action = SWP_HIDE;

  // ���祬 ���� ࠬ��.
  if (Suitable_action == SWP_MINIMIZE)
  {
    WinShowWindow (Frame_window, 0);
    WinSetWindowPos (Frame_window, NULLHANDLE, 0, 0, 0, 0, Suitable_action);
    WinShowWindow (Frame_window, 1);
  }

  if (Suitable_action == SWP_HIDE)
  {
    WinShowWindow (Frame_window, 0);
  }

  // �롨ࠥ� ���� � �।��� �࠭�.
  WindowManagement_ActivateWindowInCenter ();

  // ������.
  return 1;
}