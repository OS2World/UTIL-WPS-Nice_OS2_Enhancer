// Методы для распознавания окружения.
#define Rnd            StdLib_Rnd

#define Unsigned       StdLib_Unsigned
#define Min            StdLib_Min
#define Max            StdLib_Max
#define DivideMultiply StdLib_DivideMultiply
#define DivideDivideLR StdLib_DivideDivideLR
#define DivideDivideRL StdLib_DivideDivideRL

#define Retard         StdLib_Retard

// ─── Метод для подключения класса ───

// Application - приложение.
VOID StdLib_Start (HAB Application = NULLHANDLE)
{
  #ifdef StdLib
  bzero (&StdLib, sizeof (StdLib));
  #endif

  // Запускаем датчик случайных чисел.
  srand (WinGetCurrentTime (Application));

  // Возврат.
  return;
}
