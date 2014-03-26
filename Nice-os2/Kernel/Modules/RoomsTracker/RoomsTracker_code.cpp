
// ��� �����頥� �������, ��࠭��� ���짮��⥫�� ���

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

 // ������.
 return Room;
}

// ��� ��⠭�������� ⥪���� � ᫥������ ������� ���

VOID RoomsTracker_SetCurrentAndNextRoom( INT Current_room, INT Next_room )
{
 // ���������� ���祭��.
 RoomsTracker.RTSettings.Current_room = Current_room;
 RoomsTracker.RTSettings.Next_room = Next_room;

 if( Current_room != NO_ROOM ) RoomsTracker.RTSettings.Current_room_reserved_value = Current_room;

 // ������.
 return;
}

// ��� ������, ���� �� ᬥ�� ������ � �����饥 �६� ���

BYTE RoomsTracker_RoomsChangeIsInProcess( VOID )
{
 // �᫨ ��࠭��� ������ �������⭠ - ��� �������.
 if( !RoomsTracker.RTSettings.Current_room ) return 1;

 // ������.
 return 0;
}

// ��� ���������� �६�, ����� �ந��諠 ᬥ�� ������ ���

VOID RoomsTracker_RememberRoomsSwitchingTime( VOID )
{
 // ���������� �६�.
 RoomsTracker.RTSettings.Time_of_room_change = WinGetCurrentTime( Enhancer.Application );

 // ������.
 return;
}

// ��� �ࠢ������ ⥪�饥 �६� � �६�, ����� �ந��諠 ᬥ�� ������ ���

BYTE RoomsTracker_TimeForRoomsSwitchingIsGone( VOID )
{
 // ������ ⥪�饥 �६�.
 LONG Current_time = WinGetCurrentTime( Enhancer.Application );

 // �஢��塞 ���.
 if( Current_time > RoomsTracker.RTSettings.Time_of_room_change )
  if( Current_time - RoomsTracker.RTSettings.Time_of_room_change > RoomsTracker.Constants.Time_for_room_change )
   return 1;

 // ������.
 return 0;
}
