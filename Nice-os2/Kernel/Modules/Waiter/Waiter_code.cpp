// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��, Thread_queue - ��।� ᮮ�饭�� ��⮪�.
VOID Waiter_WaiterMessageProcessing (PQMSG Message, HMQ Thread_queue)
{
  // ���� �����஥ �६� � ��ࠢ�塞 ᮮ�饭�� � ��㣮� ��⮪.
  // ���筮 �� �ॡ���� ��� ⮣�, �⮡� ����� ����ன�� � INI-䠩�, �� ����� ���� � �� ��㣮� ����⢨�.
  if (Message->msg == SM_WAIT_SOME_TIME)
  {
    // ������� �ਮ��� ��⮪�.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // ������ ��।� ᮮ�饭�� �������� ��⮪�.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // ���믠�� �� �����஥ �६�.
    DosSleep (Waiter.Constants.Sleep_to_wait_some_time);

    // ����頥� ��������� � ⮬, �� �������� �����襭�.
    // ��ࠬ���� ᮮ�饭�� ������ ���� ࠢ�� ���, ⮣�� ��᪮�쪮 ᮮ�饭�� ���� ��ࠡ�⠭� ��� ����.
    WinPostQueueMsg (Owner_queue, SM_WAITING_COMPLETE, 0, 0);

    // ���뫠�� ᢮��� ��⮪� ᮮ�饭�� � ⮬, �� ��� ࠡ�� �����祭�.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // ���� ������ �ਫ������ � �����頥� �� �⮬ ��㣮� ��⮪.
  if (Message->msg == SM_WAIT_STARTING_PROCESS)
  {
    // ������� �ਮ��� ��⮪�.
    DosSetPriority (PRTYS_THREAD, PRTYC_REGULAR, 0, 0);

    // ������ �ਫ������, ������ ���ண� ���� �����.
    INT App_code = (INT) Message->mp1;
    // ������ ��।� ᮮ�饭�� �������� ��⮪�.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // ���� �����஥ �६�.
    INT Point_to_reduce_priority_1 = (INT) (Waiter.Constants.Retards_to_wait_process / 3);
    INT Point_to_reduce_priority_2 = (INT) (Point_to_reduce_priority_1 * 2);

    for (INT Count = 0; Count < Waiter.Constants.Retards_to_wait_process; Count ++)
    {
      // �믮��塞 ��������. ���� � �⮣� �����, ⠪ ��� �� ��ࢮ� 蠣� ��� �� ��-� �㤥� �������.
      Retard ();

      // �஢��塞, ���� �� �ਫ������.
      HWND App_window = FindAppWindow (App_code, FIND_VISIBLE_WINDOW);

      // �᫨ ��� ����:
      if (App_window != NULLHANDLE)
      {
        // ����頥� �� �⮬ ���������.
        WinPostQueueMsg (Owner_queue, SM_STARTING_PROCESS_APPEARED, (MPARAM) App_code, (MPARAM) App_window);

        // �४�頥� ��������.
        break;
      }

      // �᫨ �������� ��������� - ᭨���� �ਮ��� �� � ��.
      if (Count == Point_to_reduce_priority_1) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_QUICK, 0);
      if (Count == Point_to_reduce_priority_2) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_NORMAL, 0);
    }

    // ���뫠�� ᢮��� ��⮪� ᮮ�饭�� � ⮬, �� ��� ࠡ�� �����祭�.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // ���� �����襭�� �ਫ������ � �����頥� �� �⮬ ��㣮� ��⮪.
  if (Message->msg == SM_WAIT_EXISTING_PROCESS)
  {
    // ������� �ਮ��� ��⮪�.
    DosSetPriority (PRTYS_THREAD, PRTYC_REGULAR, 0, 0);

    // ������ �ਫ������, �� ����� ���� ᫥����.
    PID Process_ID = (PID) Message->mp1;
    // ������ ��।� ᮮ�饭�� �������� ��⮪�.
    HMQ Owner_queue = (HMQ) Message->mp2;

    // ���� �����஥ �६�.
    INT Point_to_reduce_priority_1 = (INT) (Waiter.Constants.Retards_to_wait_process / 3);
    INT Point_to_reduce_priority_2 = (INT) (Point_to_reduce_priority_1 * 2);

    for (INT Count = 0; Count < Waiter.Constants.Retards_to_wait_process; Count ++)
    {
      // �஢��塞, ���� �� �ਫ������.
      BYTE Process_is_exists = 1; if (DosVerifyPidTid (Process_ID, 1) != NO_ERROR) Process_is_exists = 0;

      // �᫨ ��� ����:
      if (Process_is_exists)
      {
        // ���� �����஥ �६�.
        Retard ();
      }
      // � �᫨ ��� ���:
      else
      {
        // ����頥� �� �⮬ ���������.
        WinPostQueueMsg (Owner_queue, SM_LOGON_PROCESS_STOPPED, (MPARAM) Process_ID, 0);

        // �४�頥� ��������.
        break;
      }

      // �᫨ �������� ��������� - ᭨���� �ਮ��� �� � ��.
      if (Count == Point_to_reduce_priority_1) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_QUICK, 0);
      if (Count == Point_to_reduce_priority_2) DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_NORMAL, 0);
    }

    // ���뫠�� ᢮��� ��⮪� ᮮ�饭�� � ⮬, �� ��� ࠡ�� �����祭�.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // ���� �����襭�� �ਫ������ ��� �ਡ����� ��� �१ �����஥ �६�.
  if (Message->msg == SM_ESCORT_LOGON)
  {
    // ������� �ਮ��� ��⮪�.
    DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, 0, 0);

    // ������ �६� ����᪠ �ਫ������ � ��⠢�塞 ��������� ����.
    LONG Time = (LONG) Message->mp1;
    CHAR Title[SIZE_OF_TITLE] = ""; MakeLogonWindowTitle (Title, Time);

    // ������ ���� �ਫ������ ������㯭묨 ��� ��४��祭��.
    HWND Frame_window = NULLHANDLE;

    for (INT Count = 0; Count < Waiter.Constants.Retards_at_escorting_process; Count ++)
    {
      // ���� �����஥ �६�.
      Retard ();

      // ������, ���� �� �� �ਫ������, ᮧ���襥 ���� � ⠪�� ����������.
      Frame_window = FindFrameWindowInWindowList (Title);

      // �᫨ ��� ��� - �४�頥� ��������:
      if (Frame_window == NULLHANDLE) break;

      // ���祬 ����.
      SetProcessJumpableFlag (Title, SWL_NOTJUMPABLE);
    }

    // �᫨ �ਫ������ �� �� ����:
    if (Frame_window != NULLHANDLE)
    {
      // ���믠�� �� �६�, �����筮� ��� ⮣�, �⮡� �ਫ������ �����訫���.
      DosSleep (Waiter.Constants.Sleep_when_escorting_process);

      // ������, ���� �� �� �ਫ������, ᮧ���襥 ���� � ⠪�� ����������.
      HWND Frame_window = FindFrameWindowInWindowList (Title);

      // ����뢠�� ���� �ਫ������.
      while (Frame_window != NULLHANDLE)
      {
        PerformAction (Frame_window, CLOSE_ACTION);
        Retard ();
        Frame_window = FindFrameWindowInWindowList (Title);
      }
    }

    // ���뫠�� ᢮��� ��⮪� ᮮ�饭�� � ⮬, �� ��� ࠡ�� �����祭�.
    WinPostQueueMsg (Thread_queue, WM_QUIT, 0, 0);
  }

  // ������.
  return;
}

// ��� ��⮪ ��� �������� ������ ��� �����襭�� �ਫ������ ���

VOID WaiterThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Waiter->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Message_queue == NULLHANDLE)
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
    Waiter_WaiterMessageProcessing (&Message, Message_queue);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}

