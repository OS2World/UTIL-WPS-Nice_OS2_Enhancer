
// ─── Возвращает комнату, выбранную пользователем ───

INT RoomsTracker_GetCurrentOrNextRoom( VOID )
{
 INT Room = SHELL_ROOM;

 if( RoomsTracker.RTSettings.Current_room )
  {
   Room = RoomsTracker.RTSettings.Current_room;
  }
 else
  {
   if( RoomsTracker.RTSettings.Next_room ) Room = RoomsTracker.RTSettings.Next_room;
  }

 // Возврат.
 return Room;
}

// ─── Устанавливает текущую и следующую комнату ───

VOID RoomsTracker_SetCurrentAndNextRoom( INT Current_room, INT Next_room )
{
 // Запоминаем значения.
 RoomsTracker.RTSettings.Current_room = Current_room;
 RoomsTracker.RTSettings.Next_room = Next_room;

 if( Current_room != NO_ROOM ) RoomsTracker.RTSettings.Current_room_reserved_value = Current_room;

 // Возврат.
 return;
}

// ─── Узнает, идет ли смена комнат в настоящее время ───

BYTE RoomsTracker_RoomsChangeIsInProcess( VOID )
{
 // Если выбранная комната неизвестна - она меняется.
 if( !RoomsTracker.RTSettings.Current_room ) return 1;

 // Возврат.
 return 0;
}

// ─── Запоминает время, когда произошла смена комнат ───

VOID RoomsTracker_RememberRoomsSwitchingTime( VOID )
{
 // Запоминаем время.
 RoomsTracker.RTSettings.Time_of_room_change = WinGetCurrentTime( Enhancer.Application );

 // Возврат.
 return;
}

// ─── Сравнивает текущее время и время, когда произошла смена комнат ───

BYTE RoomsTracker_TimeForRoomsSwitchingIsGone( VOID )
{
 // Узнаем текущее время.
 LONG Current_time = WinGetCurrentTime( Enhancer.Application );

 // Проверяем его.
 if( Current_time > RoomsTracker.RTSettings.Time_of_room_change )
  if( Current_time - RoomsTracker.RTSettings.Time_of_room_change > RoomsTracker.Constants.Time_for_room_change )
   return 1;

 // Возврат.
 return 0;
}
