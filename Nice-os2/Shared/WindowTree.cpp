// ��⮤� ��� ��室� ��ॢ� ����.
#define ExploreWindowTree       WindowTree_ExploreWindowTree

#define EnableWindowTreeUpdate  WindowTree_EnableWindowTreeUpdate
#define DestroyWindowTree       WindowTree_DestroyWindowTree

// ��� ��⮤ ��� ������祭�� ����� ���

VOID WindowTree_Start (VOID)
{
  #ifdef WindowTree
  bzero (&WindowTree, sizeof (WindowTree));
  #endif

  // ������.
  return;
}

