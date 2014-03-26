
// ��� �஢����, ����� �� ������ ���� �� ᬥ�� ������ ���

// Frame_window - ���� ࠬ��.
BYTE Rooms_PermissionForRoomActions( HWND Frame_window )
{
 // �᫨ ���� ������㯭� - ������.
 if( !FrameWindowIsAccessible( Frame_window ) ) return 0;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_8 ) == EQUALLY ) return 0;
  }

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_8 ) == EQUALLY ) return 0;
  }

 // ������.
 return 1;
}
