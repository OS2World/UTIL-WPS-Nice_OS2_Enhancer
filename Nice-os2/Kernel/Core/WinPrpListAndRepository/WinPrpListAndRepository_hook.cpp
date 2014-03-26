
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID WinPrpListAndRepositorySendMsgHook( PSMHSTRUCT Message )
{
 // Добиваемся того, чтобы в свойствах окон всегда были имена создавших их приложений.
 // Проверку можно выполнять, когда окно становится выбранным. При этом может быть вызвано
 // приложение, заполняющее список и находящее новые значки на рабочем столе.
 if( FrameWindowIsActivating( Message ) )
  {
   // Узнаем окно рамки.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // Узнаем, есть ли имя приложения в списке.
   CHAR Name[ SIZE_OF_NAME ] = ""; FindProperty( Frame_window, PRP_EXENAME, Name );

   // Если его нет - узнаем его и запоминаем в списке.
   if( Name[ 0 ] == 0 ) WinPrpListAndRepository_RememberExeNameAndPath( Frame_window );

   // Если это окно VIO - в нем могут быть запущены разные приложения. Требуется дополнительная проверка.
   if( IsVIOWindow( Frame_window ) ) WinPostQueueMsg( Enhancer.Modules.Inspector->Message_queue, SM_CHECK_VIO_EXENAME, (MPARAM) Frame_window, 0 );
  }

 // Возврат.
 return;
}