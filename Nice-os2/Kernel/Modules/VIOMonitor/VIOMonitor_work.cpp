
// ��� ������� ��⮪ ���

VOID VIOMonitor_StartThread (VOID)
{
  // ����뢠�� ��६����� ��� �⢥� �� ��⮪�.
  Thread_responds.Thread_is_created = 0;

  // �᫨ ��⮪ 㦥 ᮧ��� - ��室.
  CHAR Semaphore_name[] = "\\SEM32\\NICE-OS2!Krnl!VIOMonitor"; HMTX hmtxAlreadyRunning = NULLHANDLE;
  if (DosOpenMutexSem (Semaphore_name, &hmtxAlreadyRunning) == NO_ERROR) return;
  else DosCreateMutexSem (Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1);

  // ������� ��⮪.
  APIRET Thread_is_created = DosCreateThread (&Enhancer.Modules.VIOMonitor->Thread, (PFNTHREAD) VIOMonitor_VIOMonitorThread, 0, 0, THREAD_STACK_SIZE);
  // �᫨ �� ᮧ��� - ����, ���� � ��� �㤥� ᮧ���� ��।� ᮮ�饭��.
  if (Thread_is_created == NO_ERROR) while (Thread_responds.Thread_is_created == 0) { Retard (); }
  // �᫨ ��⮪ ᮧ���� �� 㤠���� - ������.
  if (Thread_is_created != NO_ERROR || Thread_responds.Thread_is_created == -1) { Enhancer.Modules.VIOMonitor->Thread = 0; return; }
  // ��⠭�������� �ਮ��� ��⮪�.
  WinPostQueueMsg (Enhancer.Modules.VIOMonitor->Message_queue, SM_PRIORITY, (MPARAM) PRTYC_REGULAR, 0);

  // ������.
  return;
}

// ��� ���뫠�� � ��⮪ ᮮ�饭�� WM_QUIT ���

VOID VIOMonitor_PostQuitMsg (VOID)
{
  // ���뫠�� ᮮ�饭�� � ��⮪.
  WinPostQueueMsg (Enhancer.Modules.VIOMonitor->Message_queue, WM_QUIT, 0, 0);

  // ������.
  return;
}
