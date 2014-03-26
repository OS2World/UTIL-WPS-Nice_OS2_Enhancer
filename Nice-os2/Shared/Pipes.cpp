// Методы для работы с PIPE-соединениями.
#define TransactNamedPipe         Pipes_TransactNamedPipe

// ─── Метод для подключения класса ───

VOID Pipes_Start( VOID )
{
 #ifdef Pipes
 bzero( &Pipes, sizeof( Pipes ) );
 #endif

 // Возврат.
 return;
}
