// Методы для управления клавиатурой.
#define SetCtrlAltDel     KbdLocks_SetCtrlAltDel

// ─── Метод для подключения класса ───

VOID KbdLocks_Start (VOID)
{
  #ifdef KbdLocks
  bzero (&KbdLocks, sizeof (KbdLocks));
  #endif

  // Возврат.
  return;
}

