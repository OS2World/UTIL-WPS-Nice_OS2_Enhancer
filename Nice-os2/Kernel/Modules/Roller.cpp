// ��⮤� ��� 㡨࠭�� ���� ������.
#define RememberRolledWindow     Roller_RememberRolledWindow 
#define RolledWindow             Roller_RolledWindow
#define GetRolledWindowPlacement Roller_GetRolledWindowPlacement

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Roller_Start (VOID)
{
  #ifdef Roller
  bzero (&Roller, sizeof (Roller));
  #endif

  // ������.
  return;
}

