// Методы для смены комнат.
#define GetCurrentOrNextRoom           RoomsTracker_GetCurrentOrNextRoom
#define SetCurrentAndNextRoom          RoomsTracker_SetCurrentAndNextRoom

#define RoomsChangeIsInProcess         RoomsTracker_RoomsChangeIsInProcess
#define RememberRoomsSwitchingTime     RoomsTracker_RememberRoomsSwitchingTime
#define TimeForRoomsSwitchingIsGone    RoomsTracker_TimeForRoomsSwitchingIsGone

// ─── Метод для подключения класса ───

VOID RoomsTracker_Start (VOID)
{
  #ifdef RoomsTracker
  bzero (&RoomsTracker, sizeof (RoomsTracker));
  #endif

  // Задаем постоянные величины.
  RoomsTracker.Constants.Time_for_room_change = 7500;

  // Задаем настройки по умолчанию.
  RoomsTracker.RTSettings.Current_room = RoomsTracker.RTSettings.Current_room_reserved_value = SHELL_ROOM;

  // Возврат.
  return;
}

