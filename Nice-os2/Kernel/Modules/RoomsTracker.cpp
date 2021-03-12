// ��⮤� ��� ᬥ�� ������.
#define GetCurrentOrNextRoom           RoomsTracker_GetCurrentOrNextRoom
#define SetCurrentAndNextRoom          RoomsTracker_SetCurrentAndNextRoom

#define RoomsChangeIsInProcess         RoomsTracker_RoomsChangeIsInProcess
#define RememberRoomsSwitchingTime     RoomsTracker_RememberRoomsSwitchingTime
#define TimeForRoomsSwitchingIsGone    RoomsTracker_TimeForRoomsSwitchingIsGone

// ��� ��⮤ ��� ������祭�� ����� ���

VOID RoomsTracker_Start (VOID)
{
  #ifdef RoomsTracker
  bzero (&RoomsTracker, sizeof (RoomsTracker));
  #endif

  // ������ ����ﭭ� ����稭�.
  RoomsTracker.Constants.Time_for_room_change = 7500;

  // ������ ����ன�� �� 㬮�砭��.
  RoomsTracker.RTSettings.Current_room = RoomsTracker.RTSettings.Current_room_reserved_value = SHELL_ROOM;

  // ������.
  return;
}

