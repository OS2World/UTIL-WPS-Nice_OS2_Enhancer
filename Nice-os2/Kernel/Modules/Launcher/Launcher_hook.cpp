
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID LauncherInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Выравниваем окна. Это сообщение посылается в очередь eCenter.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_SELECT_ANYTHING )
   WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_ACTIVATE_ANYTHING, 0, 0 );

 // Возврат.
 return;
}
