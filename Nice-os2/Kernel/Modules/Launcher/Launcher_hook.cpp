
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID LauncherInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ��ࠢ������ ����. �� ᮮ�饭�� ���뫠���� � ��।� eCenter.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_SELECT_ANYTHING )
   WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_ACTIVATE_ANYTHING, 0, 0 );

 // ������.
 return;
}
