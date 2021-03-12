
// ─── Возвращает "длину списка - 1" для его прохождения к началу ───

// Descendant - сведения о списке.
INT PrpList_GetTopItemPosition (PPRPLISTDESC Descendant)
{
  // Длина списка может быть равна нулю или быть предельной.
  if (Descendant->Top_position == 0 || Descendant->Top_position == Descendant->Length - 1)
   return Descendant->Top_position;
  else
   return Descendant->Top_position - 1;
}

// ─── Перебирает список ───

// Descendant - сведения о списке, Key - значение для поиска.
// Возвращаемое значение - расположение данных в списке или -1.
INT PrpList_LookupList (PPRPLISTDESC Descendant, LISTKEY Key)
{
  // Ищем значение в списке.
  PRPLISTISITEMEQUALSPROCEDURE IsEqualsTo = Descendant->IsItemEqualsTo;

  for (INT Count = PrpList_GetTopItemPosition (Descendant); Count >= 0; Count --)
   if (IsEqualsTo (Count, Key)) return Count;

  // Возврат.
  return -1;
}

// ─── Находит значение в списке ───

// Descendant - сведения о списке, Key - значение для поиска, Property - свойство, Data - данные.
VOID PrpList_FindProperty (PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data)
{
  // Ищем значение в списке.
  INT Position = PrpList_LookupList (Descendant, Key);

  // Если значение найдено - выбираем свойство.
  if (Position != -1)
  {
    PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
    PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

    memcpy (Data, SelectPointer (Position, Property), GetItemSize (Property));
  }

  // Возврат.
  return;
}

// ─── Добавляет свойства в список или изменяет их ───

// Descendant - сведения о списке, Key - значение для поиска, Property - свойство, Data - данные.
VOID PrpList_SetProperty (PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data)
{
  // Ищем значение в списке.
  INT Position = PrpList_LookupList (Descendant, Key);

  // Если его нет в списке - надо его добавить.
  if (Position == -1)
  {
    // Значения добавляются одно за другим.
    Position = Descendant->Input_position;

    // Если список уже используется - в нем можно найти свободное место для добавления.
    BYTE Hole_is_found = 0;

    if (Descendant->Top_position != 0)
    {
      PRPLISTISEMPTYPROCEDURE PlaceIsEmpty = Descendant->IsItemEmpty;

      for (INT Count = PrpList_GetTopItemPosition (Descendant); Count >= 0; Count --)
       if (PlaceIsEmpty (Count))
       {
         Hole_is_found = 1; Position = Count;
         break;
       }
    }

    // Если значение добавляется не на свободное место:
    if (!Hole_is_found)
    {
      // Задаем расположение для следующего значения.
      // Когда список заполняется, переходим к его началу - тогда наиболее старые значения выталкиваются из него.
      if (Descendant->Input_position != Descendant->Length - 1)
       Descendant->Input_position ++;
      else
       Descendant->Input_position = 0;

      // Увеличиваем длину списка, если это возможно.
      if (Descendant->Top_position != Descendant->Length - 1)
       Descendant->Top_position ++;

      // Освобождаем место для нового значения.
      PRPLISTDISCARDPROCEDURE DiscardProperties = Descendant->DiscardItem;
      DiscardProperties (Position);
    }

    // Добавляем значение в список.
    PRPLISTCREATENEWPROCEDURE CreateItem = Descendant->CreateNewItem;
    CreateItem (Position, Key);
  }

  // Устанавливаем свойство.
  PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
  PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

  memcpy (SelectPointer (Position, Property), Data, GetItemSize (Property));

  // Возврат.
  return;
}

// ─── Ничего не делает ───

ULONG PrpList_Void (VOID) 
{
  // Ничего не делает и ничего не возвращает.
  // Что бы ни случилось, с вершины стека будет снято нулевое значение.
  return 0;
}

// ─── Подготавливает список ───

// Descendant - сведения о списке.
VOID PrpList_PrepareList (PPRPLISTDESC Descendant)
{
  // Сбрасываем все переменные. Вызывать bzero () здесь необязательно - это увеличит расход памяти.
  Descendant->Top_position = Descendant->Input_position = 0;

  // Сбрасываем все указатели на методы.
  // Это полезно, например, при построении удлиняемого списка, а затем, на его основе - 
  // постоянного, в котором "метод для удлинения списка" просто ничего не будет делать.
  Descendant->IsItemEqualsTo    = (PRPLISTISITEMEQUALSPROCEDURE) PrpList_Void;
  Descendant->IsItemEmpty       = (PRPLISTISEMPTYPROCEDURE)      PrpList_Void;
  Descendant->CreateNewItem     = (PRPLISTCREATENEWPROCEDURE)    PrpList_Void;
  Descendant->DiscardItem       = (PRPLISTDISCARDPROCEDURE)      PrpList_Void;
  Descendant->GetPointerForData = (PRPLISTGETPOINTERPROCEDURE)   PrpList_Void;
  Descendant->GetSizeOfData     = (PRPLISTGETSIZERPROCEDURE)     PrpList_Void;

  // Возврат.
  return;
}
