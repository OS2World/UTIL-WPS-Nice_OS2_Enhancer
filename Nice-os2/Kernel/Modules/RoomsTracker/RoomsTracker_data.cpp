// Внутренние переменные.
typedef struct _ROOMS_TRACKER
{
  // Постоянные величины.
  typedef struct _CONSTANTS
  {
    // Время, необходимое для смены комнат.
    INT Time_for_room_change;
  }
  CONSTANTS; CONSTANTS Constants;

  typedef struct _RTSTS
  {
    // Текущая и следующая комната.
    INT Current_room; INT Current_room_reserved_value; INT Next_room;
    // Время, когда произошла смена комнат.
    LONG Time_of_room_change;
  }
  RTSTS; RTSTS RTSettings;
}
ROOMS_TRACKER;

ROOMS_TRACKER RoomsTracker;
