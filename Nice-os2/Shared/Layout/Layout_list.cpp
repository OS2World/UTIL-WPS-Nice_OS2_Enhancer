
// ─── Создает список окон и полей ввода ───

// Layout - список полей ввода, Window - окно с полями ввода,
// и Length - наибольшее возможное число полей ввода в списке.
VOID Layout_LitCreateLayout (PLTWALL Layout, HWND Window, INT Length = 100)
{
  // Если список не задан или число полей ввода меньше единицы - возврат.
  if (Layout == NULL || Length < 1) return;

  // Если окно не указано - возврат.
  if (Window == NULLHANDLE) return;

  // Если такого окна нет - возврат.
  if (!WinIsWindow (WinQueryAnchorBlock (Window), Window)) return;

  // Отводим память для списка и запоминаем его свойства.
  if (DosAllocMem ((PPVOID) &Layout->pList, sizeof (LTBRICK) * Length, PAG_ALLOCATE) == NO_ERROR)
  {
    Layout->ulLength = Length;
  }
  // Или сбрасываем переменную для него в случае неудачи.
  else
  {
    bzero (Layout, sizeof (LTWALL));
  }

  // Запоминаем окно.
  Layout->hwnd = Window;

  // Возврат.
  return;
}

// ─── Возвращает указатель на поле ввода в списке ───

// Layout - список полей ввода, Position - расположение, для которого надо получить указатель.
PLTBRICK Layout_GetBrickPointer (PLTWALL Layout, INT Position)
{
  // Проверяем значение переменной для вычисления расположения.
  // Она считается от нуля и не может быть равна длине списка.
  if (Position < 0 || Position >= Layout->ulLength) return NULL;

  // Рассчитываем расположение.
  PBYTE Exact_pointer = (PBYTE) Layout->pList + Position * sizeof (LTBRICK);

  return (PLTBRICK) Exact_pointer;
}

// ─── Проверяет переменную для списка ───

// Layout - список полей ввода. Возвращаемое значение - 1 или 0.
BYTE Layout_ListIsCorrect (PLTWALL Layout)
{
  // Проверяем список.
  if (Layout == NULL || Layout->pList == NULL ||
      Layout->ulLength < 1 || Layout->ulQuantity < 0) return 0;

  // Пробуем получить указатель для последней строки списка.
  if (Layout->ulQuantity != 0)
   if (!Layout_GetBrickPointer (Layout, Layout->ulQuantity - 1))
    return 0;

  // Возврат.
  return 1;
}

// ─── Удаляет список окон и полей ввода, созданный ранее ───

// Layout - список полей ввода.
VOID Layout_LitDeleteLayout (PLTWALL Layout)
{
  // Если список задан неверно - возврат.
  if (!Layout_ListIsCorrect (Layout)) return;

  // Освобождаем память.
  DosFreeMem (Layout->pList);

  // Сбрасываем переменную для списка.
  bzero (Layout, sizeof (LTWALL));

  // Возврат.
  return;
}

// ─── Проверяет переменную для списка ───

// Layout - список полей ввода. Возвращаемое значение - 1 или 0.
BYTE Layout_ListIsFull (PLTWALL Layout)
{
  // Проверяем, заполнен ли список.
  if (Layout->ulQuantity == Layout->ulLength) return 1;

  // Возврат.
  return 0;
}

// ─── Проверяет переменную для поля ввода ───

// Brick - поле ввода. Возвращаемое значение - 1 или 0.
BYTE Layout_BrickIsCorrect (PLTBRICK Brick)
{
  // Проверяем переменную для поля ввода.
  if (Brick->cb != sizeof (LTBRICK)) return 0;
  if (Brick->hwnd == NULLHANDLE) return 0;

  // Возврат.
  return 1;
}

// ─── Подготавливает переменную для поля ввода ───

// Brick - поле ввода.
VOID Layout_LitPrepareBrick (PLTBRICK Brick)
{
  // Заполняем переменную нулями.
  bzero (Brick, sizeof (LTBRICK));

  // Запоминаем длину структуры.
  Brick->cb = sizeof (LTBRICK);

  // Возврат.
  return;
}

// ─── Добавляет поле ввода в список ───

// Layout - список полей ввода, Brick - поле ввода для добавления в список.
VOID Layout_LitJoinBrick (PLTWALL Layout, PLTBRICK Brick)
{
  // Если список задан неверно - возврат.
  if (!Layout_ListIsCorrect (Layout)) return;

  // Если поле ввода не задано - возврат.
  if (!Layout_BrickIsCorrect (Brick)) return;

  // Если список заполнен до отказа - возврат.
  if (Layout_ListIsFull (Layout)) return;

  // Размер для поля ввода может быть задан в точках (число > 1.00) или в %% от
  // размера родительского окна (число <= 1.00), или по умолчанию (число = 0.00),
  // а если размер поля ввода меньше нуля - считаем, что он был не задан.
  if (Brick->prpWidthInParent < 0) Brick->prpWidthInParent = 0;
  if (Brick->prpHeightInParent < 0) Brick->prpHeightInParent = 0;

  // Задаем ширину и высоту по умолчанию.
  if (!Brick->prpWidthInParent || !Brick->prpHeightInParent)
  {
    Brick->prpWidthInParent = Brick->prpHeightInParent = 0;

    CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Brick->hwnd, SIZE_OF_NAME, Window_name);

    if (WinFindAtom (WinQuerySystemAtomTable (), Window_name) == SHORT1FROMLONG ((ULONG) WC_FRAME) ||
        WinFindAtom (WinQuerySystemAtomTable (), Window_name) == SHORT1FROMLONG ((ULONG) WC_NOTEBOOK))
    {
      Brick->prpWidthInParent = Brick->prpHeightInParent = 1.00;
    }
  }

  // Так как в прошлый раз длина списка была увеличена на единицу, значение
  // переменной для нее соответствует следующему расположению для поля ввода.
  INT Next_position = Layout->ulQuantity; PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Next_position);

  if (Pointer != NULL)
  {
    // Добавляем поле ввода в список.
    memcpy (Pointer, Brick, sizeof (LTBRICK));

    // Увеличиваем длину списка.
    Layout->ulQuantity ++;
  }

  // Делаем окно видимым.
  WinShowWindow (Brick->hwnd, 1);

  // Перерисовывать окно не надо.
  WinValidateRect (Brick->hwnd, NULL, 1);

  // Сбрасываем значение для поля ввода, чтобы случайно не использовать его дважды.
  HWND Window_for_future_use = Brick->hwnd;
  bzero (Brick, sizeof (LTBRICK)); Brick->hwnd = Window_for_future_use;

  // Возврат.
  return;
}

// ─── Добавляет в список признак нового ряда ───

// Layout - список полей ввода.
VOID Layout_LitCompleteRow (PLTWALL Layout)
{
  // Если список задан неверно - возврат.
  if (!Layout_ListIsCorrect (Layout)) return;

  // Если список пустой - первый ряд и так будет новым, возврат.
  if (!Layout->ulQuantity) return;

  // Если признак нового ряда только что был добавлен - возврат.
  INT Current_position = Layout->ulQuantity - 1; PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Current_position);

  if (Pointer != NULL) if (Pointer->hwnd == (HWND) LTM_NEXT_ROW_MARK) return;

  // Узнаем расположение для признака нового ряда.
  INT Next_position = Layout->ulQuantity; Pointer = Layout_GetBrickPointer (Layout, Next_position);

  if (Pointer != NULL)
  {
    // Добавляем в список признак нового ряда.
    LTBRICK Mark_brick; Layout_LitPrepareBrick (&Mark_brick);

    Mark_brick.hwnd = (HWND) LTM_NEXT_ROW_MARK;

    memcpy (Pointer, &Mark_brick, sizeof (LTBRICK));

    // Увеличиваем длину списка.
    Layout->ulQuantity ++;
  }

  // Возврат.
  return;
}

// ─── Проверяет значение для расположения поля ввода, заданное пользователем ───

// Layout - список полей ввода, Position - расположение поля ввода в нем.
BYTE Layout_PositionIsCorrect (PLTWALL Layout, INT Position)
{
  // Проверяем значение переменной для вычисления расположения.
  // Она считается от нуля и не превышает число значений в списке.
  if (Position < 0 || Position >= Layout->ulQuantity) return 0;

  // Возврат.
  return 1;
}

// ─── Удаляет поле ввода из списка ───

// Layout - список полей ввода, Position - расположение поля ввода в нем.
VOID Layout_DeleteInputField (PLTWALL Layout, INT Position)
{
  // Если список задан неверно - возврат.
  if (!Layout_ListIsCorrect (Layout)) return;

  // Если расположение задано неверно - возврат.
  if (!Layout_PositionIsCorrect (Layout, Position)) return;

  // Получаем указатель на поле ввода в списке.
  PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Position);

  if (Pointer != NULL)
  {
    // Затираем значение для поля ввода.
    bzero (Pointer, sizeof (LTBRICK));

    // Если это последнее поле ввода - уменьшаем длину списка.
    if (Position == Layout->ulQuantity - 1) Layout->ulQuantity --;
  }

  // Возврат.
  return;
}

// ─── Находит поле ввода в списке ───

// Layout - список полей ввода, Field - поле ввода.
// Возвращаемое значение - указатель на поле ввода в списке.
PLTBRICK Layout_FindInputField (PLTWALL Layout, HWND Field)
{
  // Если список задан неверно - возврат.
  if (!Layout_ListIsCorrect (Layout)) return NULL;

  // Если поле ввода не задано - возврат.
  if (Field == NULLHANDLE) return NULL;

  // Просматриваем список.
  for (INT Count = 0; Count < Layout->ulQuantity; Count ++)
  {
    // Получаем указатель на поле ввода в списке.
    PLTBRICK Pointer = Layout_GetBrickPointer (Layout, Count);

    if (Pointer != NULL)
    {
      // Проверяем поле ввода.
      if (Pointer->hwnd == Field) return Pointer;
    }
  }

  // Возврат.
  return NULL;
}

// ─── Узнает свойства поля ввода ───

// Layout - список полей ввода, Field - поле ввода.
// Brick - внешняя переменная, которая будет заполнена, если поле ввода будет найдено.
VOID Layout_GetInputField (PLTWALL Layout, HWND Field, PLTBRICK Brick)
{
  // Если внешняя переменная не задана - возврат.
  if (Brick == NULL) return;

  // Находим поле ввода. При этом выполняются проверки для всех остальных значений.
  PLTBRICK Pointer = Layout_FindInputField (Layout, Field);

  // Изменяем внешнюю переменную или затираем ее.
  if (Pointer != NULL) memcpy (Brick, Pointer, sizeof (LTBRICK));
  else bzero (Brick, sizeof (LTBRICK));

  // Возврат.
  return;
}

// ─── Изменяет свойства поля ввода ───

// Layout - список полей ввода, Field - поле ввода.
// Brick - внешняя переменная, которая будет использована, если поле ввода будет найдено.
VOID Layout_SetInputField (PLTWALL Layout, HWND Field, PLTBRICK Brick)
{
  // Если внешняя переменная не задана - возврат.
  if (Brick == NULL) return;

  // Находим поле ввода. При этом выполняются проверки для всех остальных значений.
  PLTBRICK Pointer = Layout_FindInputField (Layout, Field);

  // Переносим значения из внешней переменной.
  if (Pointer != NULL) memcpy (Pointer, Brick, sizeof (LTBRICK));

  // Возврат.
  return;
}

