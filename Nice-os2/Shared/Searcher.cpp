// ��⮤� ��� ���᪠ ����.
#define SystemWindowIsPresent       Searcher_SystemWindowIsPresent
#define AppWindowIsPresent          Searcher_AppWindowIsPresent
#define FindSystemWindow            Searcher_FindSystemWindow
#define FindAppWindow               Searcher_FindAppWindow

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Searcher_Start (VOID)
{
  #ifdef Searcher
  bzero (&Searcher, sizeof (Searcher));
  #endif

  // ������.
  return;
}
