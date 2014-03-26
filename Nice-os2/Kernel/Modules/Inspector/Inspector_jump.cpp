
// ─── Выполняет действия после чтения настроек и создания потока ───

VOID Inspector_Jump( VOID )
{
 // Выполняем дополнительные проверки.
 if( Inspector.Settings.Check_Repository ) 
  WinPostQueueMsg( Enhancer.Modules.Inspector->Message_queue, SM_CHECK_REPOSITORY, (MPARAM) 0, 0 );

 // Возврат.
 return;
}