
// ��� �ॡ�� �⪫�祭�� ��ࠢ������� ���� ���

// State - ࠧ�襭�� ��� ����饭�� ��ࠢ������� ����.
VOID Performer_DisableArranger( BYTE State )
{
 // ���������� ���祭��.
 Performer.RTSettings.Performer_disables_arranger = State;

 // ������.
 return;
}

// ��� �����頥� � ���筮� ���ﭨ� ����, ���஥ �࠭� ������ ���

// �� ��६���� - ���譨�.
VOID Performer_UnrollWindow( HWND Frame_window )
{
 // �᫨ ���� �� ᠬ�� ���� �� �࠭� ������ - ������.
 if( Frame_window != RolledWindow() ) return;

 // �⪫�砥� ��ࠢ������� ����.
 Performer_DisableArranger( 1 );

 // �����頥� ���� � ���筮� ���ﭨ�.
 INT X = 0; INT Y = 0; INT Width = 0; INT Height = 0;
 GetRolledWindowPlacement( &X, &Y, &Width, &Height );

 WinSetWindowPos( Frame_window, NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

 // ����砥� ��ࠢ������� ����.
 Performer_DisableArranger( 0 );

 // ����ᮢ뢠�� ࠬ�� ����. ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
 WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_UNKNOWN );

 // ���� - �������⭮.
 RememberRolledWindow( NULLHANDLE );

 // ������.
 return;
}

