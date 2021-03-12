
// ─── Добавляет в список имя, под которым определено окно ───

// Window - окно, которое надо добавить в список.
// Возвращаемое значение - номер в списке (его можно будет использовать для изменения значений).
INT Scroller_AddWindowToList (HWND Window)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Устраняем пробел в конце слова.
  if (Window_name[SIZE_OF_NAME - 2] == ' ') Window_name[SIZE_OF_NAME - 2] = '_';

  // Если имя есть в списке - возврат.
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
    return Count;

  // Если оно не было найдено - его надо добавить.
  for (INT I = 0; I < SCROLLER_SCRLIST_SIZE; I ++)
   if (Scroller.Scrolling_list[I].Name[0] == 0)
   {
     // Заносим имя в список.
     // На этом шаге считаем, что скорость передвижения изображения равна "1 / 1", то есть что
     // расстояние в точках равно единице и движок полоски просмотра тоже изменяется на единицу.
     strncpy (Scroller.Scrolling_list[I].Name, Window_name, SIZE_OF_NAME);
     Scroller.Scrolling_list[I].X_Velocity_DD = 1;
     Scroller.Scrolling_list[I].X_Velocity_D  = 1;
     Scroller.Scrolling_list[I].Y_Velocity_DD = 1;
     Scroller.Scrolling_list[I].Y_Velocity_D  = 1;
     Scroller.Scrolling_list[I].PreDefined    = 0;
     Scroller.Scrolling_list[I].Method        = SCROLLING_COMMON;

     // Список надо будет сохранить.
     WinPostQueueMsg (Enhancer.Modules.Scroller->Message_queue, SM_WRITE_SETTINGS, 0, 0);

     // Возвращаем номер в списке.
     return I;
   }

  // Возвращаем нулевое значение.
  return 0;
}

// ─── Добавляет в список имя и скорость ───

// Window_name - имя, XY_V_* - скорость, Method - способ прокрутки (может отличаться от общепринятого).
VOID Scroller_AddPreDefinedWindowToList (PCHAR Window_name, INT X_V_DD, INT Y_V_DD, INT Method)
{
  // Скорость в "шагах" полоски просмотра будет равна единице.
  INT X_V_D = 1; INT Y_V_D = 1;

  // Если имя есть в списке:
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
   {
     // В любом случае задаем скорость и способ передвижения изображения.
     // Некоторым окнам надо направлять сообщения через полоски просмотра (посылая полоскам сообщения
     // "WM_CHAR"), а некоторые окна будут сдвигать изображение даже при отсутствии полосок просмотра.
     Scroller.Scrolling_list[Count].X_Velocity_DD = X_V_DD;
     Scroller.Scrolling_list[Count].X_Velocity_D  = X_V_D;
     Scroller.Scrolling_list[Count].Y_Velocity_DD = Y_V_DD;
     Scroller.Scrolling_list[Count].Y_Velocity_D  = Y_V_D;
     Scroller.Scrolling_list[Count].PreDefined    = 1;
     Scroller.Scrolling_list[Count].Method        = Method;

     // Возврат.
     return;
   }

  // Если оно не было найдено - его надо добавить.
  for (INT I = 0; I < SCROLLER_SCRLIST_SIZE; I ++)
   if (Scroller.Scrolling_list[I].Name[0] == 0)
   {
     // Заносим имя в список.
     strncpy (Scroller.Scrolling_list[I].Name, Window_name, SIZE_OF_NAME);
     Scroller.Scrolling_list[I].X_Velocity_DD = X_V_DD;
     Scroller.Scrolling_list[I].X_Velocity_D  = X_V_D;
     Scroller.Scrolling_list[I].Y_Velocity_DD = Y_V_DD;
     Scroller.Scrolling_list[I].Y_Velocity_D  = Y_V_D;
     Scroller.Scrolling_list[I].PreDefined    = 1;
     Scroller.Scrolling_list[I].Method        = Method;

     // Прекращаем поиск.
     break;
   }

  // Возврат.
  return;
}

// ─── Находит имя в списке ───

// Window - окно, которое надо найти.
// Возвращаемое значение - номер в списке (его можно будет использовать для изменения значений).
// Если поиск был успешным, заполняется переменная по указателю Record_from_list, иначе она не изменяется.
INT Scroller_FindWindowInList (HWND Window, PSCRLIST Record_from_list = NULL)
{
  // Узнаем имя, под которым определено окно.
  CHAR Window_name[SIZE_OF_NAME] = ""; WinQueryClassName (Window, SIZE_OF_NAME, Window_name);

  // Устраняем пробел в конце слова.
  if (Window_name[SIZE_OF_NAME - 2] == ' ') Window_name[SIZE_OF_NAME - 2] = '_';

  // Если имя есть в списке:
  for (INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++)
   if (strc (Window_name, Scroller.Scrolling_list[Count].Name))
   {
     // Заполняем переменную, указывающую на запись из списка. После ее можно будет использовать.
     if (Record_from_list != NULL)
     {
       Record_from_list->X_Velocity_DD = Scroller.Scrolling_list[Count].X_Velocity_DD;
       Record_from_list->X_Velocity_D  = Scroller.Scrolling_list[Count].X_Velocity_D;
       Record_from_list->Y_Velocity_DD = Scroller.Scrolling_list[Count].Y_Velocity_DD;
       Record_from_list->Y_Velocity_D  = Scroller.Scrolling_list[Count].Y_Velocity_D;
       Record_from_list->PreDefined    = Scroller.Scrolling_list[Count].PreDefined;
       Record_from_list->Method        = Scroller.Scrolling_list[Count].Method;
     }

     // Возвращаем номер в списке.
     return Count;
   }

  // Возвращаем нулевое значение.
  return 0;
}

// ─── Узнает скорость передвижения изображения в окне ───

// Window - окно, Record_from_list - переменная, которая будет содержать скорость.
VOID Scroller_QueryScrollingVelocity (HWND Window, PSCRLIST Record_from_list)
{
  // Узнаем скорость.
  Scroller_FindWindowInList (Window, Record_from_list);

  // Возврат.
  return;
}

// ─── Узнает способ передвижения изображения в окне ───

// Window - окно, в котором надо передвигать изображение.
INT Scroller_QueryScrollingMethod (HWND Window)
{
  // Находим окно в списке.
  SCRLIST Record_from_list = {0};
  Scroller_FindWindowInList (Window, &Record_from_list);

  // Возвращаем способ передвижения.
  return Record_from_list.Method;
}

// ─── Узнает, было ли окно добавлено в список со значениями по умолчанию ───

// Window - окно, в котором надо передвигать изображение.
BYTE Scroller_WindowHasPreDefinedSpeed (HWND Window)
{
  // Находим окно в списке.
  SCRLIST Record_from_list = {0};
  Scroller_FindWindowInList (Window, &Record_from_list);

  // Возврат.
  return Record_from_list.PreDefined;
}
