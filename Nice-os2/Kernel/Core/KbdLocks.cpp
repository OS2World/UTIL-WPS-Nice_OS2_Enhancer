// ��⮤� ��� �ࠢ����� ��������ன.
#define SetCtrlAltDel     KbdLocks_SetCtrlAltDel

// ��� ��⮤ ��� ������祭�� ����� ���

VOID KbdLocks_Start (VOID)
{
  #ifdef KbdLocks
  bzero (&KbdLocks, sizeof (KbdLocks));
  #endif

  // ������.
  return;
}

