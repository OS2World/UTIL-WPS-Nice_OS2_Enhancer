// ��⮤� ��� ��������� 梥⮢ � ����஥� �����窨 OS/2.
#define ChangeSystemColors    SysValues_ChangeSystemColors
#define RestoreSystemColors   SysValues_RestoreSystemColors

#define ChangeSystemValues    SysValues_ChangeSystemValues
#define RestoreSystemValues   SysValues_RestoreSystemValues

// ��� ��⮤ ��� ������祭�� ����� ���

VOID SysValues_Start (VOID)
{
  #ifdef SysValues
  bzero (&SysValues, sizeof (SysValues));
  #endif

  // ������.
  return;
}
