// ��⮤� ��� ᬥ�� ������.
#define SynchronizeArrangerAndRooms Rooms_SynchronizeArrangerAndRooms

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Rooms_Start (VOID)
{
  #ifdef Rooms
  bzero (&Rooms, sizeof (Rooms));
  #endif

  // ������ ����ﭭ� ����稭�.
  Rooms.Constants.Retards_after_room_change = 7;

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Rooms_StartThread;
  Item.PostQuitMsg = Rooms_PostQuitMsg;
  Item.ShutdownAll = Rooms_ShutdownAll;
  Item.TuneModule  = Rooms_Tune;
  Item.SysColorsChangeReporter = Rooms_SysColorsChangeReporter;

  RememberModuleItem (Enhancer.Modules.Rooms, &Item);

  // ������.
  return;
}

