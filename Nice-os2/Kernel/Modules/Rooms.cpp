// Методы для смены комнат.
#define SynchronizeArrangerAndRooms Rooms_SynchronizeArrangerAndRooms

// ─── Метод для подключения класса ───

VOID Rooms_Start (VOID)
{
  #ifdef Rooms
  bzero (&Rooms, sizeof (Rooms));
  #endif

  // Задаем постоянные величины.
  Rooms.Constants.Retards_after_room_change = 7;

  // Задаем указатели в списке составляющих расширителя.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Rooms_StartThread;
  Item.PostQuitMsg = Rooms_PostQuitMsg;
  Item.ShutdownAll = Rooms_ShutdownAll;
  Item.TuneModule  = Rooms_Tune;
  Item.SysColorsChangeReporter = Rooms_SysColorsChangeReporter;

  RememberModuleItem (Enhancer.Modules.Rooms, &Item);

  // Возврат.
  return;
}

