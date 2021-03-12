// Методы для прохода дерева окон.
#define ExploreWindowTree       WindowTree_ExploreWindowTree

#define EnableWindowTreeUpdate  WindowTree_EnableWindowTreeUpdate
#define DestroyWindowTree       WindowTree_DestroyWindowTree

// ─── Метод для подключения класса ───

VOID WindowTree_Start (VOID)
{
  #ifdef WindowTree
  bzero (&WindowTree, sizeof (WindowTree));
  #endif

  // Возврат.
  return;
}

