// Методы для выполнения действий при нажатии на кнопки в заголовке окна.

// ─── Метод для подключения класса ───

VOID WindowManager_Start (VOID)
{
  #ifdef WindowManager
  bzero (&WindowManager, sizeof (WindowManager));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = WindowManager_StartThread;
  Item.PostQuitMsg = WindowManager_PostQuitMsg;
  Item.TuneModule  = WindowManager_Tune;

  RememberModuleItem (Enhancer.Modules.WindowManager, &Item);

  // Возврат.
  return;
}

