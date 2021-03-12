// Методы для получения сообщений при нажатии на клавиши.

// ─── Метод для подключения класса ───

VOID MMKbdListener_Start (VOID)
{
  #ifdef MMKbdListener
  bzero (&MMKbdListener, sizeof (MMKbdListener));
  #endif

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = MMKbdListener_StartThread;
  Item.PostQuitMsg = MMKbdListener_PostQuitMsg;
  Item.TuneModule  = MMKbdListener_Tune;

  RememberModuleItem (Enhancer.Modules.MMKbdListener, &Item);

  // Возврат.
  return;
}

