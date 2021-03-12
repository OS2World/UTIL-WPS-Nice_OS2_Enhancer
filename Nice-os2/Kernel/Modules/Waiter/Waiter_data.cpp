// Ожидание появления или завершения приложений.
typedef struct _WAITER
{
  // Постоянные величины.
  typedef struct _CONSTANTS
  {
    // Число задержек для простого ожидания.
    INT Sleep_to_wait_some_time;

    // Число задержек для ожидания приложения (две минуты или более).
    INT Retards_to_wait_process;

    // Время глубокого сна при сопровождении приложения (две минуты или более).
    INT Sleep_when_escorting_process;

    // Число задержек для сокрытия приложения в начале его сопровождения.
    INT Retards_at_escorting_process;
  }
  CONSTANTS; CONSTANTS Constants;
}
WAITER;

WAITER Waiter;