// ��⮤� ��� ࠡ��� � ᯨ᪮� ����.
#define QuerySwitchList                      WindowList_QuerySwitchList
#define FreeSwitchListMemory                 WindowList_FreeSwitchListMemory

#define CorrectWindowTitle                   WindowList_CorrectWindowTitle
#define QueryWindowTitle                     WindowList_QueryWindowTitle
#define GetDefaultShellTitle                 WindowList_GetDefaultShellTitle

#define ShowItemInSwitchList                 WindowList_ShowItemInSwitchList

// ��� ��⮤ ��� ������祭�� ����� ���

VOID WindowList_Start (VOID)
{
  #ifdef WindowList
  bzero (&WindowList, sizeof (WindowList));
  #endif

  // ������.
  return;
}

