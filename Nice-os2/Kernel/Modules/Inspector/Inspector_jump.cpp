
// ��� �믮���� ����⢨� ��᫥ �⥭�� ����஥� � ᮧ����� ��⮪� ���

VOID Inspector_Jump( VOID )
{
 // �믮��塞 �������⥫�� �஢�ન.
 if( Inspector.Settings.Check_Repository ) 
  WinPostQueueMsg( Enhancer.Modules.Inspector->Message_queue, SM_CHECK_REPOSITORY, (MPARAM) 0, 0 );

 // ������.
 return;
}