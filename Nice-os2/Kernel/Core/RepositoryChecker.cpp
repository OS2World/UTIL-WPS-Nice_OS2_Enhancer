// Методы для проверки списка известных приложений и значков для них.
#define CheckRepositoryEntries  RepositoryChecker_CheckRepositoryEntries

// ─── Метод для подключения класса ───

VOID RepositoryChecker_Start( VOID )
{
 #ifdef RepositoryChecker
 bzero( &RepositoryChecker, sizeof( RepositoryChecker ) );
 #endif

 // Возврат.
 return;
}

