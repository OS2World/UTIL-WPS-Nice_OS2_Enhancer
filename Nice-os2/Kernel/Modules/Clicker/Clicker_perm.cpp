// ��� �஢����, ����� �� ���ந����� ��� �� ����⨨ �� ������� ���

// Message - ᮮ�饭��.
// �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE Clicker_PermissionForClicking( PQMSG Message )
{
 // ����ਬ, ����� ������ �����.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // ����ਬ, ��� ��⠭������ ���� � State.
 if( !( State & KC_KEYUP ) ) return 0;
 if( !( State & KC_LONEKEY ) ) return 0;

 // �஢��塞 �ਫ������.
 BYTE Permission = 0;

 // ������ ���� ࠬ��.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �᫨ �� ���� IRC - ���� ���ந����� ���.
   if( Clicker.Settings.Keyboard_echo_for_IRC )
    if( WindowIsUsedTo( DO_INTERNET_CHAT, Frame_window ) )
     Permission = 1;

   // �᫨ �� ���� ICQ - ���� ���ந����� ���.
   if( Clicker.Settings.Keyboard_echo_for_ICQ )
    if( WindowIsUsedTo( DO_CONTACT_PEOPLE, Frame_window ) )
     Permission = 1;
  }

 // ������.
 return Permission;
}
