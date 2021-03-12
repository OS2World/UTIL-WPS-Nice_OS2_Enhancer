// Методы для поиска окон.
#define SystemWindowIsPresent       Searcher_SystemWindowIsPresent
#define AppWindowIsPresent          Searcher_AppWindowIsPresent
#define FindSystemWindow            Searcher_FindSystemWindow
#define FindAppWindow               Searcher_FindAppWindow

// ─── Метод для подключения класса ───

VOID Searcher_Start (VOID)
{
  #ifdef Searcher
  bzero (&Searcher, sizeof (Searcher));
  #endif

  // Возврат.
  return;
}
