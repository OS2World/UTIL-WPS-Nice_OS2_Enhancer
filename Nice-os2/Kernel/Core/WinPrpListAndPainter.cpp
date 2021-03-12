// Методы для работы со списком свойств окон.
#define CheckActivityProperties         WinPrpListAndPainter_CheckActivityProperties

// ─── Метод для подключения класса ───

VOID WinPrpListAndPainter_Start (VOID)
{
  #ifdef WinPrpListAndPainter
  bzero (&WinPrpListAndPainter, sizeof (WinPrpListAndPainter));
  #endif

  // Возврат.
  return;
}
