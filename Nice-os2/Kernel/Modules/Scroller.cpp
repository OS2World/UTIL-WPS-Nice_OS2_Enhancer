// Методы для передвижения изображения в окнах.

// ─── Метод для подключения класса ───

VOID Scroller_Start (VOID)
{
  #ifdef Scroller
  bzero (&Scroller, sizeof (Scroller));
  #endif

  // Задаем настройки по умолчанию.
  Scroller.RTSettings.Step_of_scrolling = 1;

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Scroller_StartThread;
  Item.PostQuitMsg = Scroller_PostQuitMsg;
  Item.TuneModule  = Scroller_Tune;

  RememberModuleItem (Enhancer.Modules.Scroller, &Item);

  // Возврат.
  return;
}

