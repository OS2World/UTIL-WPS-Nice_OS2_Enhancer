// Методы для работы со списком окон.
#define ShowSwitchListItems WindowList_ShowSwitchListItems

// ─── Метод для подключения класса ───

VOID Shell_WindowList_Start( VOID )
{
 #ifdef Shell_WindowList
 bzero( &Shell_WindowList, sizeof( Shell_WindowList ) );
 #endif

 // Возврат.
 return;
}
