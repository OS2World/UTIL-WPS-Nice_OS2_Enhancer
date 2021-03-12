// Методы для работы со списком окон.
#define QuerySwitchList                      WindowList_QuerySwitchList
#define FreeSwitchListMemory                 WindowList_FreeSwitchListMemory

#define CorrectWindowTitle                   WindowList_CorrectWindowTitle
#define QueryWindowTitle                     WindowList_QueryWindowTitle
#define GetDefaultShellTitle                 WindowList_GetDefaultShellTitle

#define ShowItemInSwitchList                 WindowList_ShowItemInSwitchList

// ─── Метод для подключения класса ───

VOID WindowList_Start (VOID)
{
  #ifdef WindowList
  bzero (&WindowList, sizeof (WindowList));
  #endif

  // Возврат.
  return;
}

