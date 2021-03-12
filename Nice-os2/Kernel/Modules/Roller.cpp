// Методы для убирания окна наверх.
#define RememberRolledWindow     Roller_RememberRolledWindow 
#define RolledWindow             Roller_RolledWindow
#define GetRolledWindowPlacement Roller_GetRolledWindowPlacement

// ─── Метод для подключения класса ───

VOID Roller_Start (VOID)
{
  #ifdef Roller
  bzero (&Roller, sizeof (Roller));
  #endif

  // Возврат.
  return;
}

