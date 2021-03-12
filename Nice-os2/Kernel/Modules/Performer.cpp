// Методы для выполнения действий с окнами.
#define SetNextButtons           Performer_SetNextButtons

#define PerformAction            Performer_PerformAction

#define WindowIsRolled           Performer_WindowIsRolled
#define UnrollWindow             Performer_UnrollWindow

#define ArrangerMustBeDisabled   Performer_ArrangerMustBeDisabled

// ─── Метод для подключения класса ───

VOID Performer_Start (VOID)
{
  #ifdef Performer
  bzero (&Performer, sizeof (Performer));
  #endif

  // Возврат.
  return;
}

