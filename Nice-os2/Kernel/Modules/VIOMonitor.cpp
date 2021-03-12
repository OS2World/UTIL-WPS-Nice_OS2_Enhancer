// Методы для слежения за текстовыми окнами.

// ─── Метод для подключения класса ───

VOID VIOMonitor_Start (VOID)
{
  #ifdef VIOMonitor
  bzero (&VIOMonitor, sizeof (VIOMonitor));
  #endif

  // Задаем постоянные величины.
  VIOMonitor.Constants.Retards_when_VIO_monitoring = 100;

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = VIOMonitor_StartThread;
  Item.PostQuitMsg = VIOMonitor_PostQuitMsg;
  Item.TuneModule  = VIOMonitor_Tune;

  RememberModuleItem (Enhancer.Modules.VIOMonitor, &Item);

  // Возврат.
  return;
}

