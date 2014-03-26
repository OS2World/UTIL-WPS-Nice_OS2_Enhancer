// Методы для задания приоритетов приложений.
#define SetPriorityLevel            Priority_SetPriorityLevel

// ─── Метод для подключения класса ───

VOID Priority_Start( VOID )
{
 #ifdef Priority
 bzero( &Priority, sizeof( Priority ) );
 #endif

 // Возврат.
 return;
}

