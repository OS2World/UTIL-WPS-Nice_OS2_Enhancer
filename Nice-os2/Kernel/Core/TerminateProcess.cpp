// Методы для прерывания других приложений и потоков.
#define KillProcess          TerminateProcess_TerminateProcess

// ─── Метод для подключения класса ───

VOID TerminateProcess_Start (VOID)
{
  #ifdef TerminateProcess
  bzero (&TerminateProcess, sizeof (TerminateProcess));
  #endif

  // Возврат.
  return;
}

