// ��⮤� ��� ᮧ����� ���� � ����� �����.
#define CreateNotebookWindow     TabWindow_CreateNotebookWindow

// ��� ��⮤ ��� ������祭�� ����� ���

VOID TabWindow_Start (VOID)
{
  #ifdef TabWindow
  bzero (&TabWindow, sizeof (TabWindow));
  #endif

  // ������.
  return;
}
