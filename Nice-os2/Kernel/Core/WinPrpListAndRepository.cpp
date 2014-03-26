// Методы для работы со списком свойств окон.
#define RememberExeNameAndPath          WinPrpListAndRepository_RememberExeNameAndPath

// ─── Метод для подключения класса ───

VOID WinPrpListAndRepository_Start( VOID )
{
 #ifdef WinPrpListAndRepository
 bzero( &WinPrpListAndRepository, sizeof( WinPrpListAndRepository ) );
 #endif

 // Возврат.
 return;
}
