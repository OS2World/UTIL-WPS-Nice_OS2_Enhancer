
// ��� �ਡ����� �ਫ������ �� ���� ࠡ�祣� �⮫� ���

// Message - ᮮ�饭��, ���஥ ��।����� ���� ࠡ�祣� �⮫�.
VOID TerminateProcessHook( PQMSG Message )
{
 // �ਡ����� �ਫ������.
 if( Message->msg == WM_MARK ) if( Message->hwnd == NULLHANDLE ) 
  if( Message->mp1 == (MPARAM) MRK_KILL_PROCESS )
   {
    // ������ �ਫ������.
    PID Process_ID = (PID) Message->mp2;

    // �ਡ����� ���.
    DosKillProcess( DKP_PROCESSTREE, Process_ID );
   }

 // ������.
 return;
}

