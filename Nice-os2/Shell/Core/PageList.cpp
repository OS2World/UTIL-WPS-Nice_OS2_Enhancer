// Методы для перебора страниц приложения.
#define GetPageListEntry   PageList_GetPageListEntry

#define PresetPageItem     PageList_PresetPageItem
#define RememberPageItem   PageList_RememberPageItem

#define BroadcastMessage   PageList_BroadcastMessage

// ─── Метод для подключения класса ───

VOID PageList_Start( VOID )
{
 #ifdef PageList
 bzero( &PageList, sizeof( PageList ) );
 #endif

 // Возврат.
 return;
}
