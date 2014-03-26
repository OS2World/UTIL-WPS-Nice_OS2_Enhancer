// Методы для запуска расширителя.

// ─── Метод для подключения класса ───

VOID Launcher_Start( VOID )
{
 #ifdef Launcher
 bzero( &Launcher, sizeof( Launcher ) );
 #endif

 // Возврат.
 return;
}
