
// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Inspector_InspectorMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Inspector->Priority = MAKELONG (Class, Delta);
  }

  // ������ ����� �ਫ������ ��� ⥪�⮢�� ����.
  if (Message->msg == SM_CHECK_VIO_EXENAME)
  {
    // ������ ���� ࠬ��.
    HWND Frame_window = (HWND) Message->mp1;

    // ������ ��� �ਫ������ � ���������� ��� � ᯨ᪥.
    RememberExeNameAndPath (Frame_window);
  }

  // ������.
  return;
}

// ��� ��⮪ ��� ��᫥������� ���� ���

VOID Inspector_InspectorThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Inspector->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Inspector->Message_queue == NULLHANDLE)
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
    Inspector_InspectorMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
