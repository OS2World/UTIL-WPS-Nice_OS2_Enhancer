
// ─── Возвращает "длину списка - 1" для его прохождения к началу ───

// Descendant - сведения о списке.
INT AbstractPrpList_GetTopItemPosition( PPRPLISTDESC Descendant )
{
 // Длина списка может быть равна нулю или быть предельной.
 if( Descendant->Top_position == 0 || Descendant->Top_position == Descendant->Length - 1 )
  return Descendant->Top_position;
 else
  return Descendant->Top_position - 1;
}

// ─── Перебирает список ───

// Descendant - сведения о списке, Key - значение для поиска.
// Возвращаемое значение - расположение данных в списке или -1.
INT AbstractPrpList_LookupList( PPRPLISTDESC Descendant, LISTKEY Key )
{
 // Ищем значение в списке.
 PRPLISTISITEMEQUALSPROCEDURE ItemsAreEqually = Descendant->IsItemEqualsTo;

 for( INT Count = AbstractPrpList_GetTopItemPosition( Descendant ); Count >= 0; Count -- )
  if( ItemsAreEqually( Count, Key ) ) return Count;

 // Возврат.
 return -1;
}

// ─── Находит значение в списке ───

// Descendant - сведения о списке, Key - значение для поиска, Property - свойство, Data - данные.
VOID AbstractPrpList_FindProperty( PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data )
{
 // Ищем значение в списке.
 INT Position = AbstractPrpList_LookupList( Descendant, Key );

 // Если значение найдено - выбираем свойство.
 if( Position != -1 )
  {
   PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
   PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

   memcpy( Data, SelectPointer( Position, Property ), GetItemSize( Property ) );
  }

 // Возврат.
 return;
}

// ─── Добавляет свойства в список или изменяет их ───

// Descendant - сведения о списке, Key - значение для поиска, Property - свойство, Data - данные.
VOID AbstractPrpList_SetProperty( PPRPLISTDESC Descendant, LISTKEY Key, LISTPRP Property, PVOID Data )
{
 // Ищем значение в списке.
 INT Position = AbstractPrpList_LookupList( Descendant, Key );

 // Если его нет в списке - надо его добавить.
 if( Position == -1 )
  {
   // Значения добавляются одно за другим.
   Position = Descendant->Input_position;

   // Если список уже используется - в нем можно найти свободное место для добавления.
   BYTE Hole_is_found = 0;

   if( Descendant->Top_position != 0 )
    {
     PRPLISTISEMPTYPROCEDURE PlaceIsEmpty = Descendant->IsItemEmpty;

     for( INT Count = AbstractPrpList_GetTopItemPosition( Descendant ); Count >= 0; Count -- )
      if( PlaceIsEmpty( Count ) )
       {
        Hole_is_found = 1; Position = Count;
        break;
       }
    }

   // Если значение добавляется не на свободное место:
   if( !Hole_is_found )
    {
     // Задаем расположение для следующего значения.
     // Когда список заполняется, переходим к его началу - тогда наиболее старые значения выталкиваются из него.
     if( Descendant->Input_position != Descendant->Length - 1 )
      Descendant->Input_position ++;
     else
      Descendant->Input_position = 0;

     // Увеличиваем длину списка, если это возможно.
     if( Descendant->Top_position != Descendant->Length - 1 )
      Descendant->Top_position ++;

     // Освобождаем место для нового значения.
     PRPLISTDISCARDPROCEDURE DiscardProperties = Descendant->DiscardItem;
     DiscardProperties( Position );
    }

   // Добавляем значение в список.
   PRPLISTCREATENEWPROCEDURE CreateItem = Descendant->CreateNewItem;
   CreateItem( Position, Key );
  }

 // Устанавливаем свойство.
 PRPLISTGETPOINTERPROCEDURE SelectPointer = Descendant->GetPointerForData;
 PRPLISTGETSIZERPROCEDURE GetItemSize = Descendant->GetSizeOfData;

 memcpy( SelectPointer( Position, Property ), Data, GetItemSize( Property ) );

 // Возврат.
 return;
}

// ─── Подготавливает список ───

// Descendant - сведения о списке.
VOID AbstractPrpList_PrepareList( PPRPLISTDESC Descendant )
{
 // Сбрасываем все переменные. Вызывать bzero() здесь необязательно - это увеличит расход памяти.
 Descendant->Top_position = Descendant->Input_position = 0;

 // Сбрасываем все указатели на методы.
 // Это полезно, например, при построении удлиняемого списка, а затем, на его основе - 
 // постоянного, в котором "метод для удлинения списка" просто ничего не будет делать.
 Descendant->IsItemEqualsTo    = (PRPLISTISITEMEQUALSPROCEDURE) AbstractClass_Void;
 Descendant->IsItemEmpty       = (PRPLISTISEMPTYPROCEDURE)      AbstractClass_Void;
 Descendant->CreateNewItem     = (PRPLISTCREATENEWPROCEDURE)    AbstractClass_Void;
 Descendant->DiscardItem       = (PRPLISTDISCARDPROCEDURE)      AbstractClass_Void;
 Descendant->GetPointerForData = (PRPLISTGETPOINTERPROCEDURE)   AbstractClass_Void;
 Descendant->GetSizeOfData     = (PRPLISTGETSIZERPROCEDURE)     AbstractClass_Void;

 // Возврат.
 return;
}
