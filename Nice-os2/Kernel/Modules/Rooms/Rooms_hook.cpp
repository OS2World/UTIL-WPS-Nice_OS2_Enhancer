
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID RoomsInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // �᫨ ���� �������� ������� � ࠡ�祬� �⮫�:
  if (Rooms.Settings.Create_Rooms)
  {
    // ���室�� � ����� ������� �� ����祭�� ᮮ�饭�� WM_MARK.
    if (Rooms.Settings.Switch_by_WarpCenter)
     if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_GO_TO_ROOM)
     {
       // ������, � ����� ������� ���� ��३�.
       LONG Scan_code = (LONG) Message->mp2; INT Room = 0;

       if (Scan_code == SC_NUM_5) Room = SHELL_ROOM;
       if (Scan_code == SC_NUM_8) Room = NORTHERN_ROOM;
       if (Scan_code == SC_NUM_4) Room = WESTERN_ROOM;
       if (Scan_code == SC_NUM_6) Room = EASTERN_ROOM;
       if (Scan_code == SC_NUM_2) Room = SOUTHERN_ROOM;

       if (Scan_code == SC_NUM_7 || Scan_code == SC_NUM_9 ||
           Scan_code == SC_NUM_1 || Scan_code == SC_NUM_3) Room = CURRENT_ROOM;

       // �᫨ �맢��� ���⠢�� - ����⢨� �믮����� �� ����.
       if (Room)
        if (SystemIsLocked ()) { Room = 0; *Discarding = 1; }

       // �᫨ ���� ��४������� � ����� �������:
       if (Room)
       {
         // ���뫠�� ᮮ�饭�� � ��⮪.
         if (Room != CURRENT_ROOM) WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_GO_TO_ROOM, (MPARAM) Room, 0);

         // ����饭�� ������ ���� ��襭�.
         *Discarding = 1;
       }
     }

    // ����訢��� ���� ࠡ�祣� �⮫�.
    if (Rooms.Settings.Draw_wallpaper)
    {
      // �᫨ ���� ������ ���� ����ᮢ��� � �� ࠡ�稩 �⮫:
      if (Message->msg == WM_PAINT) if (Message->hwnd == QueryDesktopWindow ())
      {
        // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� �������.
        HMQ Message_queue = WinQueryWindowULong (Message->hwnd, QWL_HMQ);
        WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_FILL_DESKTOP, (MPARAM) Message->hwnd);
      }

      // ��ࠡ��뢠�� ᮮ�饭�� WM_MARK.
      if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_FILL_DESKTOP)
      {
        HWND Window = (HWND) Message->mp2;
        if (Window == QueryDesktopWindow ())
        {
          // ���뫠�� ᮮ�饭�� � ��⮪.
          WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_FILL_DESKTOP, (MPARAM) Window, 0);
        }
      }
    }

    // ��뢠�� LaunchPad ��� ᯨ᮪ ���� �� ����⨨ ������ ��� � ���� ࠡ�祣� �⮫�.
    BYTE Show_LaunchPad = 0; BYTE Show_Window_list = 0; BYTE Hide_Window_list = 0;

    // �᫨ ����� ������ ��� ����� ������ - ��뢠�� LaunchPad.
    if (Message->msg == WM_BUTTON1DBLCLK)
     if (Message->hwnd == QueryDesktopWindow ()) Show_LaunchPad = 1;

    // �᫨ ��� ����� ���� ࠧ:
    if (Message->msg == WM_BUTTON1DOWN)
    {
      // ������ ���� ࠡ�祣� �⮫�.
      HWND Desktop = QueryDesktopWindow ();

      // �᫨ ���� ����� � ���� ࠡ�祣� �⮫� - �஢��塞 ���ﭨ� ��㣨� ������ ���.
      if (Message->hwnd == Desktop)
      {
        if (MouseButtonIsPressed (2) || MouseButtonIsPressed (3))
         Show_Window_list = 1;
        else
         Hide_Window_list= 1;
      }
    }

    // �᫨ ����� �ࠢ�� ��� �।��� ������:
    if (Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
    {
      // ������ ���� ࠡ�祣� �⮫�.
      HWND Desktop = QueryDesktopWindow ();

      // �᫨ ���� ����� � ���� ࠡ�祣� �⮫� - �஢��塞 ���ﭨ� ����� ������ ���.
      if (Message->hwnd == Desktop)
      {
        if (MouseButtonIsPressed (1))
         Show_Window_list = 1;
        else
         Hide_Window_list = 1;
      }
    }

    // �᫨ ���� �맢��� LaunchPad ��� ᯨ᮪ ���� - ���뫠�� ᮮ�饭�� � ��⮪.
    if (Show_LaunchPad) WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_SHOW_LAUNCHPAD, 0, 0);
    if (Show_Window_list) WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_SHOW_WINDOW_LIST, (MPARAM) 1, 0);
    if (Hide_Window_list)
    {
      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_HIDE_WINDOW_LIST, 0, 0);
      WinPostQueueMsg (Enhancer.Modules.Launcher->Message_queue, SM_HIDE_WARPCENTER, 0, 0);
    }

    // �᫨ �ᯮ������ �����窠 WPS:
    if (ShellIsWPS ())
    {
      // �஢��塞 ���� WPS, ���஥ �⠭������ ��࠭��, �⮡� ����� ���� �����窨.
      // �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook () �� ��ࠡ�⪥ ᮮ�饭�� WM_ACTIVATE.
      if (GetCurrentOrNextRoom () != SHELL_ROOM)
       if (Message->hwnd == NULLHANDLE) if (Message->msg == WM_MARK) if (Message->mp1 == (MPARAM) MRK_CHECK_WINDOW)
       {
         // ���뫠�� ᮮ�饭�� � ��⮪.
         HWND Window = (HWND) Message->mp2;
         WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_CHECK_WINDOW, (MPARAM) Window, 0);
       }
    }

    // ���������� �ࠢ��쭮� ࠡ��� ��⮪�� ��᫥ ���室� ����� �����⠬�.
    if (Rooms.Settings.Synchronize_arranger_and_rooms)
    {
      // �᫨ �뫠 ����� ������ ��� - ��⠥�, �� ᬥ�� ������ �����襭�.
      if (Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN)
       if (Message->hwnd != CurtainWindow ())
        if (MouseIsBusy ())
         Rooms.Settings.Synchronize_arranger_and_rooms = 0;
    }
  }

  // ������.
  return;
}


// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID RoomsKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // �᫨ ���� �������� ������� � ࠡ�祬� �⮫�:
  if (Rooms.Settings.Create_Rooms)
  {
    // ���室�� � ����� ������� �� ����⨨ �� ��஢� ������. ���뫠�� ᮮ�饭�� � ��⮪ � ���뢠�� ��襤襥 ᮮ�饭��.
    if (Rooms.Settings.Switch_by_keyboard)
     if (Message->msg == WM_CHAR)
     {
       // ����ਬ, ����� ������ �����.
       BYTE Scan_code = CHAR4FROMMP (Message->mp1);
       SHORT State = SHORT1FROMMP (Message->mp1);

       // �᫨ ���� ����⨥ ������:
       if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
       {
         // ������, � ����� ������� ���� ��३�.
         INT Room = 0;

         // ������ ���� ����� ������ Shift � ��஢�� ������.
         if (State & KC_SHIFT) if (ShiftIsPressed ())
         {
           if (Scan_code == SC_NUM_5) Room = SHELL_ROOM;
           if (Scan_code == SC_NUM_8) Room = NORTHERN_ROOM;
           if (Scan_code == SC_NUM_4) Room = WESTERN_ROOM;
           if (Scan_code == SC_NUM_6) Room = EASTERN_ROOM;
           if (Scan_code == SC_NUM_2) Room = SOUTHERN_ROOM;

           if (Scan_code == SC_NUM_7 || Scan_code == SC_NUM_9 ||
               Scan_code == SC_NUM_1 || Scan_code == SC_NUM_3) Room = CURRENT_ROOM;
         }

         // �᫨ �맢��� ���⠢�� - ����⢨� �믮����� �� ����.
         if (Room) if (SystemIsLocked ()) { Room = 0; *Discarding = 1; }

         // �᫨ ���� ��४������� � ����� �������:
         if (Room)
         {
           // ���뫠�� ᮮ�饭�� � ��⮪.
           if (Room != CURRENT_ROOM) WinPostQueueMsg (Enhancer.Modules.Rooms->Message_queue, SM_GO_TO_ROOM, (MPARAM) Room, 0);

           // ����饭�� ������ ���� ��襭�.
           *Discarding = 1;
         }
       }
     }

    // ���������� �ࠢ��쭮� ࠡ��� ��⮪�� ��᫥ ���室� ����� �����⠬�.
    if (Rooms.Settings.Synchronize_arranger_and_rooms)
    {
      // �᫨ �뫠 ����� �� ������ - ��⠥�, �� ᬥ�� ������ �����襭�.
      if (Message->msg == WM_CHAR)
      {
        // ����ਬ, ����� ������ �����.
        BYTE Scan_code = CHAR4FROMMP (Message->mp1);
        SHORT State = SHORT1FROMMP (Message->mp1);

        // �᫨ ���� ����⨥ ������:
        if (!(State & KC_KEYUP)) if (!(State & KC_PREVDOWN))
        {
          // �᫨ �� ������ �� �ᯮ������ �� ��४��祭�� ����� �����⠬� - ᬥ�� ������ �����襭�.
          if (Scan_code < SC_NUM_FIRST || Scan_code > SC_NUM_LAST)
           Rooms.Settings.Synchronize_arranger_and_rooms = 0;
        }
      }
    }
  }

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID RoomsSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // �᫨ ���� �������� ������� � ࠡ�祬� �⮫�:
  if (Rooms.Settings.Create_Rooms) if (!RoomsChangeIsInProcess ())
  {
    // �᫨ ���� ࠬ�� �⠭������ ��࠭��:
    if (TopFrameWindowIsActivating (Message))
    {
      // ������ ���� ࠬ��.
      HWND Frame_window = QueryFrameWindow (Message->hwnd);

      // ���������� �������, � ���ன �ᯮ�������� ����.
      Rooms_SetRoomProperty (Frame_window, GetCurrentOrNextRoom ());

      // ������ ���� ����㯭� ��� ��४��祭��.
      WinPostQueueMsg (Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Frame_window, (MPARAM) SWL_JUMPABLE);
    }

    // �᫨ �ᯮ������ �����窠 WPS:
    if (ShellIsWPS ())
    {
      // �᫨ ���� �����窨 ����:
      if (GetCurrentOrNextRoom () != SHELL_ROOM)
      {
        // �᫨ ��� �����頥��� � ���筮� ���ﭨ� ��� �⠭������ ��࠭�� - ���� ������ ���.
        if (TopFrameWindowIsMoving (Message) || TopFrameWindowIsActivating (Message))
        {
          // ������ ���� ࠬ��.
          HWND Frame_window = QueryFrameWindow (Message->hwnd);

          // �᫨ �� ���� WPS - ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� �஢����.
          if (IsFolderWindow (Frame_window))
          {
            HMQ Message_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);
            WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_CHECK_WINDOW, (MPARAM) Frame_window);
          }
        }
      }
    }
  }

  // ������.
  return;
}

