
// ��� ����頥�, ��� ������ ࠡ���� ��⮪ ��� ��ࠢ������� ���� ���

BYTE Rooms_SynchronizeArrangerAndRooms (VOID)
{
  // �஢��塞 ����ன��.
  if (Rooms.Settings.Synchronize_arranger_and_rooms) return 1;

  // ������.
  return 0;
}
