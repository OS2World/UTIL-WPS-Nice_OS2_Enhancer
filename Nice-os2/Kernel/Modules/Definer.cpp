// Методы для выполнения действий при нажатии на клавиши.

// ─── Метод для подключения класса ───

VOID Definer_Start (VOID)
{
  #ifdef Definer
  bzero (&Definer, sizeof (Definer));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.TuneModule = Definer_Tune;
  Item.SysValuesChangeReporter = Definer_SysValuesChangeReporter;

  RememberModuleItem (Enhancer.Modules.Definer, &Item);

  // Возврат.
  return;
}

