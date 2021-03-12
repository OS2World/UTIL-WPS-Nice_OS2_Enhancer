
// ��� ��⠭�������� �ਫ������ ���

// Process_ID - �ਫ������.
VOID TerminateProcess_KillProcess (PID Process_ID)
{
  // �஢��塞, ���� �� �ਫ������.
  BYTE Process_is_exists = 1; if (DosVerifyPidTid (Process_ID, 1) != NO_ERROR) Process_is_exists = 0;

  // �᫨ ��� ����:
  if (Process_is_exists)
  {
    // ������ ������ �ਡ��� ���.
    APIRET Result = DosKillProcess (DKP_PROCESSTREE, Process_ID);

    // �᫨ �� ᤥ���� �� 㤠����:
    if (Result != NO_ERROR)
    {
      // ���뫠�� � ��।� ���� ࠡ�祣� �⮫� ᮮ�饭�� WM_MARK. 
      // �ਫ������ ����� �㤥� �ਡ��� �� �६� ��� ����祭��.
      HMQ Desktop_queue = WinQueryWindowULong (QueryDesktopWindow (), QWL_HMQ);
      WinPostQueueMsg (Desktop_queue, WM_MARK, (MPARAM) MRK_KILL_PROCESS, (MPARAM) Process_ID);
    }
  }

  // ������.
  return;
}
