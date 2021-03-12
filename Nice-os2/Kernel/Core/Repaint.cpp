// Методы для обновления окон.
#define UpdateWindow           Repaint_UpdateWindow
#define UpdateAllWindows       Repaint_UpdateAllWindows
#define UpdateFrameBorder      Repaint_UpdateFrameBorder

// ─── Метод для подключения класса ───

VOID Repaint_Start (VOID)
{
  #ifdef Repaint
  bzero (&Repaint, sizeof (Repaint));
  #endif

  // Возврат.
  return;
}
