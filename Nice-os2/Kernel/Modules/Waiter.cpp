// Методы для ожидания появления или завершения приложения.

// ─── Метод для подключения класса ───

VOID Waiter_Start (VOID)
{
  #ifdef Waiter
  bzero (&Waiter, sizeof (Waiter));
  #endif

  // Задаем постоянные величины.
  Waiter.Constants.Sleep_to_wait_some_time = 7000;

  Waiter.Constants.Retards_to_wait_process = 2500;
  Waiter.Constants.Sleep_when_escorting_process = 125000;
  Waiter.Constants.Retards_at_escorting_process = 300;

  // Возврат.
  return;
}

