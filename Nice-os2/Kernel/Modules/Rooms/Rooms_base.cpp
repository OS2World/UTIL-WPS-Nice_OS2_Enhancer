
// ─── Задает комнату для окна и запоминает предыдущую ───

// Frame_window - окно рамки, Room - комната.
VOID Rooms_SetRoomProperty( HWND Frame_window, INT Room )
{
 // Если надо сбросить значение для комнаты:
 if( Room == NO_ROOM )
  {
   // Запоминаем значение.
   SetProperty( Frame_window, PRP_ROOM, &Room );
  }
 // А если надо задать значение для комнаты:
 else
  {
   // Узнаем комнату, в которой расположено окно.
   INT Current_room = NO_ROOM; FindProperty( Frame_window, PRP_ROOM, &Current_room );

   // Если комната та же самая - возврат.
   if( Room == Current_room ) return;

   // Запоминаем новую комнату.
   SetProperty( Frame_window, PRP_ROOM, &Room );
  }

 // Возврат.
 return;
}
