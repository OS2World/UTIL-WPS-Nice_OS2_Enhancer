
// ─── Прибивает приложение из окна рабочего стола ───

// Message - сообщение, которое передается окну рабочего стола.
VOID TerminateProcessHook( PQMSG Message )
{
 // Прибиваем приложение.
 if( Message->msg == WM_MARK ) if( Message->hwnd == NULLHANDLE ) 
  if( Message->mp1 == (MPARAM) MRK_KILL_PROCESS )
   {
    // Узнаем приложение.
    PID Process_ID = (PID) Message->mp2;

    // Прибиваем его.
    DosKillProcess( DKP_PROCESSTREE, Process_ID );
   }

 // Возврат.
 return;
}

