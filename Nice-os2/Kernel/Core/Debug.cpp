#ifdef DEBUG_VERSION

// Методы для отладки.
#define Bzz      Krnl_Debug_Bzz
#define Log      Krnl_Debug_Log

// ─── Метод для подключения класса ───

VOID Krnl_Debug_Start (VOID)
{
  #ifdef Krnl_Debug
  bzero (&Krnl_Debug, sizeof (Krnl_Debug));
  #endif

  // Удаляем файлы тестовой версии.
  DosForceDelete ("_log.txt"); DosForceDelete ("XTest.exe");

  // Возврат.
  return;
}

#endif