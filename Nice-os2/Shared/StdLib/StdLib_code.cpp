// ─── Возвращает случайное число в заданных пределах ───

INT StdLib_Rnd (INT Max)
{
  // Если число больше допустимого значения - возврат.
  if (Max > RAND_MAX - 1) return -1;

  // Получаем случайное число от 0 до 1.
  INT Integer_value = rand ();

  // Число должно быть от 0 до Max.
  INT Divisor = RAND_MAX / (Max + 1);

  // Получаем число.
  INT Result = Integer_value / Divisor;
  if (Result > Max) Result = Max;

  // Возвращаем число.
  return Result;
}

// ─── Возвращает положительное целое число ───

INT StdLib_Unsigned (INT Number)
{
  // Умножаем число на -1 если оно меньше нуля.
  if (Number < 0) Number *= (-1);

  // Возвращаем число.
  return Number;
}

// ─── Возвращает наименьшее целое число из нескольких чисел ───

INT StdLib_Min (INT V1, INT V2, INT V3 = INT_MAX, INT V4 = INT_MAX)
{
  // Выполняем сравнение.
  INT Min_value = V1;
  if (V2 < Min_value) Min_value = V2;
  if (V3 < Min_value) Min_value = V3;
  if (V4 < Min_value) Min_value = V4;

  // Возвращаем число.
  return Min_value;
}

// ─── Возвращает наибольшее целое число из нескольких чисел ───

INT StdLib_Max (INT V1, INT V2, INT V3 = INT_MIN, INT V4 = INT_MIN)
{
  // Выполняем сравнение.
  INT Max_value = V1;
  if (V2 > Max_value) Max_value = V2;
  if (V3 > Max_value) Max_value = V3;
  if (V4 > Max_value) Max_value = V4;

  // Возвращаем число.
  return Max_value;
}

// ─── Выполняет деление с умножением и возвращает целое число ───

INT StdLib_DivideMultiply (INT DD, INT D, INT L)
{
  // На ноль не делим, но возвращаем ноль.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // Если числа делятся нацело без остатка - выполняем расчет без потери точности.
  // Иначе выполняем деление с точкой, затем выполняем умножение и теряем точность.
  if (DD % D == 0) return (DD / D) * L;
  else return ((FLOAT) DD / D) * L;
}

// ─── Выполняет двойное деление и возвращает целое число ───

INT StdLib_DivideDivideLR (INT DD, INT D, INT L)
{
  // На ноль не делим, но возвращаем ноль.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // Если числа делятся нацело без остатка - выполняем расчет без потери точности.
  // Иначе выполняем деление с точкой, затем выполняем ещё деление и теряем точность.
  if (DD % D == 0) return (DD / D) / L;
  else return ((FLOAT) DD / D) / L;
}

// ─── Выполняет двойное деление и возвращает целое число ───

INT StdLib_DivideDivideRL (INT DD, INT D, INT L)
{
  // На ноль не делим, но возвращаем ноль.
  if (DD == 0 || D == 0 || L == 0) return 0;

  // Если числа делятся нацело без остатка - выполняем расчет без потери точности.
  // Иначе выполняем деление с точкой, затем выполняем ещё деление и теряем точность.
  if (DD % D == 0) return L / (DD / D);
  else return L / ((FLOAT) DD / D);
}

// ─── Выполняет задержку внутри потока ───

VOID StdLib_Retard (VOID)
{
  // Ждем некоторое время.
  #ifdef I386_ARCHITECTURE
   DosSleep (50);
  #else
   DosSleep (10);
  #endif

  // Возврат.
  return;
}

