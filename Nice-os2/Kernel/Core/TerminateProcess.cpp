// ��⮤� ��� ���뢠��� ��㣨� �ਫ������ � ��⮪��.
#define KillProcess          TerminateProcess_TerminateProcess

// ��� ��⮤ ��� ������祭�� ����� ���

VOID TerminateProcess_Start (VOID)
{
  #ifdef TerminateProcess
  bzero (&TerminateProcess, sizeof (TerminateProcess));
  #endif

  // ������.
  return;
}

