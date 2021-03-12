// Методы для окон сообщений.
#define MessageBox      Krnl_MessageBox_MessageBox

// ─── Метод для подключения класса ───

VOID Krnl_MessageBox_Start (VOID)
{
  #ifdef Krnl_MessageBox
  bzero (&Krnl_MessageBox, sizeof (Krnl_MessageBox));
  #endif

  // Возврат.
  return;
}
