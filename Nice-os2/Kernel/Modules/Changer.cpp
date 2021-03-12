// Методы для изменения свойств окон.

// ─── Метод для подключения класса ───

VOID Changer_Start (VOID)
{
  #ifdef Changer
  bzero (&Changer, sizeof (Changer));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Changer_StartThread;
  Item.PostQuitMsg = Changer_PostQuitMsg;
  Item.TuneModule  = Changer_Tune;

  RememberModuleItem (Enhancer.Modules.Changer, &Item);

  // Возврат.
  return;
}

