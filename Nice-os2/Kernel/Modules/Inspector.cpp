
// ─── Метод для подключения класса ───

VOID Inspector_Start (VOID)
{
  #ifdef Inspector
  bzero (&Inspector, sizeof (Inspector));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread  = Inspector_StartThread;
  Item.PostQuitMsg  = Inspector_PostQuitMsg;
  Item.TuneModule   = Inspector_Tune;

  RememberModuleItem (Enhancer.Modules.Inspector, &Item);

  // Возврат.
  return;
}

