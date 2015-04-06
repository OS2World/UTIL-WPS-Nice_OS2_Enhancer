
// ��� �஢����, ����� �� ������ �ਮ��� �ਫ������ ���

// Frame_window - ���� ࠬ��.
// �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE PriorityManager_PermissionForPriorityActions( HWND Frame_window )
{
 // �᫨ ���� ᮧ���� �����窮� ��� ����⥫�� - ������ �ਮ��� �����.
 if( IsPMShellAuxiliaryWindow( Frame_window ) ||
     IsWorkplaceShellWindow( Frame_window ) ||
     WindowIsCreatedBy( APP_NICE, Frame_window ) ) return 0;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ 㤠���� ��।����� ��� �ਫ������:
 if( Exe_name[ 0 ] != 0 )
  {
   // �᫨ �� ��㣮� ����⥫� - ������ �ਮ��� �����.
   if( WindowIsCreatedBy( APP_NPSWPS, Frame_window ) ) return 0;

   // �᫨ �� �ਡ���⥫� ������� ����� - ������ �ਮ��� �����.
   if( WindowIsCreatedBy( APP_WATCHCAT, Frame_window ) ) return 0;

   // �᫨ �ਫ������ �ॡ�� �६��� ��� ࠡ��� - ������ �ਮ��� �����.
   if( WindowIsCreatedBy( APP_ZMP3, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_TIMIDITY, Frame_window ) ) return 0;

   if( WindowIsCreatedBy( APP_CDRECORD, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_DVDRECORD, Frame_window ) ) return 0;

   // ���� �᫨ VirtualPC ����ࠥ� �� �६�, ������ �ਮ��� �����.
   if( WindowIsCreatedBy( APP_VIRTUALPC, Frame_window ) ) return 0;
  }

 // �᫨ �� ⥪�⮢�� ���� � ��� �ண��� �� ���� - ������ �ਮ��� �����.
 if( !PriorityManager.Settings.Dynamic_priority_for_VIO ) if( IsVIOWindow( Frame_window ) ) return 0;

 // �᫨ �� ���� ᯨ᪠ ���� - ������ �ਮ��� ����� (�� ��砩, �᫨ �� �ࠡ���� �᫮��� ���砫�).
 if( IsWinListWindow( Frame_window ) ) return 0;

 // ������.
 return 1;
}

// ��� �஢����, ����� �� ������ �ਮ��� �ਫ������ ���

// Frame_window - ���� ࠬ��, WinList_title - �������� � ᯨ᪥ ����.
// �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE PriorityManager_PermissionForDynamicPriorityActions( HWND Frame_window, PCHAR WinList_title = NULL )
{
 // �᫨ ���� ������ ���� 㤠���� �� ᯨ᪠ ���� - ������ �ਮ��� �����.
 if( WinList_title != NULL ) if( WindowWillBeHidden( WinList_title ) ) return 0;

 // �᫨ ���� ������㯭� - ������ �ਮ��� �����.
 if( !FrameWindowIsAccessible( Frame_window ) ) return 0;

 // ������.
 return 1;
}
