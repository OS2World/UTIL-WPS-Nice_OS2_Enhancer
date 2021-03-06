
// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Controller_ControllerMessageProcessing (PQMSG Message)
{
  // ��⠭�������� �ਮ��� ��⮪�.
  if (Message->msg == SM_PRIORITY)
  {
    // ��⠭�������� �ਮ���.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // ���������� �ਮ���.
    Enhancer.Modules.Controller->Priority = MAKELONG (Class, Delta);
  }

  // ��⠭�������� ��४���⥫� �� ���������.
  if (Message->msg == SM_SET_NUM_LOCK)
  {
    // �᫨ ����ன�� �몫�祭� - ������.
    if (!Controller.Settings.Turn_Num_Lock) return;

    // ��⠭�������� ��४���⥫�.
    Controller_SetNumLock ();
  }

  // ����뢠�� ���ﭨ� ������ "Shift".
  if (Message->msg == SM_RESET_SHIFT_KEYS)
  {
    // �᫨ ����ன�� �몫�祭� - ������.
    if (!Controller.Settings.Reset_Shift_keys) return;

    // ����뢠�� ���ﭨ� ������.
    Controller_ResetShiftKeys ();
  }

  // �믮��塞 "ࠧ���" ����������.
  if (Message->msg == SM_SPEEDUP_KEYBOARD)
  {
    // �᫨ ����ன�� �몫�祭� - ������.
    if (!Controller.Settings.SpeedUp_keyboard) return;

    // ����ࠨ���� ����������.
    Controller_SpeedUpKeyboard ();
  }

  // ��४��砥� ���ﭨ� ������ ��१���㧪�.
  if (Message->msg == SM_SET_CTRL_ALT_DEL)
  {
    // ������, �� ���� ᤥ����.
    LONG State = (LONG) Message->mp1;

    // ��४��砥� ���ﭨ� Ctrl + Alt + Del.
    if (State) SetCtrlAltDel (1); else SetCtrlAltDel (0);
  }

  // ������.
  return;
}

// ��� ��⮪ ��� �ࠢ����� ��������ன ���

VOID Controller_ControllerThread (VOID)
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
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Controller->Message_queue = Message_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Enhancer.Modules.Controller->Message_queue == NULLHANDLE)
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
    Controller_ControllerMessageProcessing (&Message);
  }

  // �����蠥� ࠡ��� ��⮪�.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
