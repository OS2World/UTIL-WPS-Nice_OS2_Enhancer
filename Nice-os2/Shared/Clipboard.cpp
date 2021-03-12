// Методы для работы с окнами.
#define PutStringIntoClipboard           Clipboard_PutStringIntoClipboard
#define GetStringFromClipboard           Clipboard_GetStringFromClipboard

// ─── Метод для подключения класса ───

VOID Clipboard_Start (VOID)
{
  #ifdef Clipboard
  bzero (&Clipboard, sizeof (Clipboard));
  #endif

  // Возврат.
  return;
}

