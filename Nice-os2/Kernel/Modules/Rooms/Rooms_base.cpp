
// ��� ������ ������� ��� ���� � ���������� �।����� ���

// Frame_window - ���� ࠬ��, Room - ������.
VOID Rooms_SetRoomProperty( HWND Frame_window, INT Room )
{
 // �᫨ ���� ����� ���祭�� ��� �������:
 if( Room == NO_ROOM )
  {
   // ���������� ���祭��.
   SetProperty( Frame_window, PRP_ROOM, &Room );
  }
 // � �᫨ ���� ������ ���祭�� ��� �������:
 else
  {
   // ������ �������, � ���ன �ᯮ������ ����.
   INT Current_room = NO_ROOM; FindProperty( Frame_window, PRP_ROOM, &Current_room );

   // �᫨ ������ � �� ᠬ�� - ������.
   if( Room == Current_room ) return;

   // ���������� ����� �������.
   SetProperty( Frame_window, PRP_ROOM, &Room );
  }

 // ������.
 return;
}
