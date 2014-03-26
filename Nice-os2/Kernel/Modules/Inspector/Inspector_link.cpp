
// ─── Сообщает, надо ли проверять список приложений ───

BYTE Inspector_RepositoryCheckIsRequired( VOID )
{
 // Проверяем настройки.
 if( Inspector.Settings.Check_Repository ) return 1;

 // Возврат.
 return 0;
}

