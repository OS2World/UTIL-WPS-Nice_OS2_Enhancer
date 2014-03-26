
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID WinPrpListAndRepositorySendMsgHook( PSMHSTRUCT Message )
{
 // ���������� ⮣�, �⮡� � ᢮��⢠� ���� �ᥣ�� �뫨 ����� ᮧ����� �� �ਫ������.
 // �஢��� ����� �믮�����, ����� ���� �⠭������ ��࠭��. �� �⮬ ����� ���� �맢���
 // �ਫ������, ��������饥 ᯨ᮪ � ��室�饥 ���� ���窨 �� ࠡ�祬 �⮫�.
 if( FrameWindowIsActivating( Message ) )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // ������, ���� �� ��� �ਫ������ � ᯨ᪥.
   CHAR Name[ SIZE_OF_NAME ] = ""; FindProperty( Frame_window, PRP_EXENAME, Name );

   // �᫨ ��� ��� - 㧭��� ��� � ���������� � ᯨ᪥.
   if( Name[ 0 ] == 0 ) WinPrpListAndRepository_RememberExeNameAndPath( Frame_window );

   // �᫨ �� ���� VIO - � ��� ����� ���� ����饭� ࠧ�� �ਫ������. �ॡ���� �������⥫쭠� �஢�ઠ.
   if( IsVIOWindow( Frame_window ) ) WinPostQueueMsg( Enhancer.Modules.Inspector->Message_queue, SM_CHECK_VIO_EXENAME, (MPARAM) Frame_window, 0 );
  }

 // ������.
 return;
}