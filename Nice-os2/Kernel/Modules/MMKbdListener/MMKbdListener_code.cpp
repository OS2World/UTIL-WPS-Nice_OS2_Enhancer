
// ��� ����砥� ᮮ�饭�� � ����⨨ �� ������ ���

VOID MMKbdListener_WaitKeyboardEvents (VOID)
{
  // �஢��塞, ࠡ�⠥� �� "MMKbd.exe"
  CHAR MMKbd_semaphore_name[] = "\\SEM32\\MMKbd"; HMTX MMKbd_semaphore = NULLHANDLE;
  if (DosOpenMutexSem (MMKbd_semaphore_name, &MMKbd_semaphore) != NO_ERROR)
  {
    WinPostQueueMsg (Enhancer.Modules.MMKbdListener->Message_queue, WM_QUIT, 0, 0);
    return;
  }
  DosCloseMutexSem (MMKbd_semaphore);

  // ������� ᮡ�⨩�� ᥬ����.
  // ��� ⮫쪮 ������ �㤥� �����, ���� �� ��� �㤥� ����祭.
  #include "Modules\\MMKbdListener\\MMKbdListener_keys.cpp"

  // ������� ��騩 ᮡ�⨩�� ᥬ��� � ������塞 � ���� ࠭�� ᮧ����� ᥬ����.
  HMUX MainEventSem = NULLHANDLE;
  if (DosCreateMuxWaitSem (NULL, &MainEventSem, Quantity, Semaphores, DCMW_WAIT_ANY) != NO_ERROR) return;

  // ���� ����⨩ � ���뫠�� � ���� ᮮ�饭�� "WM_CHAR".
  while (1)
  {
    // �믮��塞 ��������.
    ULONG Record_number = 0;
    if (DosWaitMuxWaitSem (MainEventSem, SEM_INDEFINITE_WAIT, &Record_number) == NO_ERROR && Record_number > 0)
    {
      // ������ ����, � ���஥ ���ࠢ��� ���� �� ����������.
      HWND Input_window = WinQueryFocus (QueryDesktopWindow ());

      // �᫨ ⠪��� ���� ��� - ����� �� �㤥� ���� ࠡ�祣� �⮫�.
      if (Input_window == NULLHANDLE) Input_window = QueryDesktopWindow ();

      // ������ ��⠭�� ������.
      CHAR New_character_code = Char_codes[Record_number];
      BYTE New_scan_code = Scan_codes[Record_number];
      LONG New_modifiers = 0;

      // ���⠢�塞 ᮮ�饭�� � ����⨨ � �⦠⨨ ������.
      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers);

      // ���뫠�� ᮮ�饭�� � ����.
      // ��� ��� ������ �� �㤥� �믮������� �஢�ઠ, ������ �� ��� �� ᠬ�� ����.
      WinPostMsg (Input_window, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Input_window, WM_CHAR, First_parameter_2, Second_parameter_2);

      // ����뢠�� ᮡ�⨩�� ᥬ���� � ��砫쭮� ���ﭨ�.
      for (INT Count = 0; Count < Quantity; Count ++)
      {
        HEV Semaphore = (HEV) Semaphores[Count].hsemCur; ULONG Post_count = 0;
        DosResetEventSem (Semaphore, &Post_count);
      }
    }

    // �믮��塞 ������ ����প� �� ��砩 "�஦����" ������.
    Retard ();
  }

  // ����塞 ᥬ����.
  for (INT Count = 0; Count < Quantity; Count ++) DosDeleteMuxWaitSem (MainEventSem, Semaphores[Count].hsemCur);
  DosCloseMuxWaitSem (MainEventSem);

  for (Count = 0; Count < Quantity; Count ++)
  {
    HEV Semaphore = (HEV) Semaphores[Count].hsemCur;
    DosCloseEventSem (Semaphore);
  }

  // ������.
  return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID MMKbdListener_MMKbdListenerMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.MMKbdListener->Priority = MAKELONG (Class, Delta);
  }

  // ���� ������ �� �������.
  if (Message->msg == SM_WAIT_MMKBD_EVENTS) MMKbdListener_WaitKeyboardEvents ();

  // ������.
  return;
}

// ��� ��⮪ ��� ����祭�� ᮮ�饭�� � ����⨨ �� ������ ���

VOID MMKbdListener_MMKbdListenerThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.MMKbdListener->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.MMKbdListener->Message_queue == NULLHANDLE)
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
    MMKbdListener_MMKbdListenerMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
