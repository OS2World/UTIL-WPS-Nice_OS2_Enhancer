// ����७��� ��६����.
typedef struct _ROOMS_TRACKER
{
  // ����ﭭ� ����稭�.
  typedef struct _CONSTANTS
  {
    // �६�, ����室���� ��� ᬥ�� ������.
    INT Time_for_room_change;
  }
  CONSTANTS; CONSTANTS Constants;

  typedef struct _RTSTS
  {
    // ������ � ᫥����� ������.
    INT Current_room; INT Current_room_reserved_value; INT Next_room;
    // �६�, ����� �ந��諠 ᬥ�� ������.
    LONG Time_of_room_change;
  }
  RTSTS; RTSTS RTSettings;
}
ROOMS_TRACKER;

ROOMS_TRACKER RoomsTracker;
