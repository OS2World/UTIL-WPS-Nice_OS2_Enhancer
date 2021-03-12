// Методы для создания окон и полей ввода.
#define CreateNotebookWindow     TabWindow_CreateNotebookWindow

// ─── Метод для подключения класса ───

VOID TabWindow_Start (VOID)
{
  #ifdef TabWindow
  bzero (&TabWindow, sizeof (TabWindow));
  #endif

  // Возврат.
  return;
}
