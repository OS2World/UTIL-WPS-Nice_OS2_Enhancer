
// ��� �஢����, ����� �� ��।������ ����ࠦ���� � ���� � ������� ��� ���

// Window - ����. �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE Scroller_PermissionForScrolling( HWND Window )
{
 // ������ ���� ࠬ��.
 HWND Frame_window = QueryFrameWindow( Window );

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.Scrolling_8 ) == EQUALLY ) return 0;
  }

 // ������ ���� ࠡ�祩 ������ ��� ���� ࠬ��.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.Scrolling_8 ) == EQUALLY ) return 0;
  }

 // ������.
 return 1;
}

// ��� �஢����, ����� �� ��।������ ����ࠦ���� � ������� ��५�� ���

// Window - ����. �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE Scroller_PermissionForKeyScrolling( HWND Window )
{
 // ������ ���� ࠬ��.
 HWND Frame_window = QueryFrameWindow( Window );

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Scroller.Settings.Exceptions.KeyScrolling_8 ) == EQUALLY ) return 0;
  }

 // ������ ���� ࠡ�祩 ������ ��� ���� ࠬ��.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Scroller.Settings.Exceptions.KeyScrolling_8 ) == EQUALLY ) return 0;
  }

 // ������.
 return 1;
}
