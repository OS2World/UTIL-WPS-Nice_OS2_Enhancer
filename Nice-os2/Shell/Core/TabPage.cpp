// Методы для заполнения страниц-"закладок".
#define CreateCtlButtons    TabPage_CreateCtlButtons
#define CreatePromptText    TabPage_CreatePromptText
#define CompleteCreation    TabPage_CompleteCreation

#define UpdatePageWindow    TabPage_UpdatePageWindow

#define BroadcastRSMessages TabPage_BroadcastRSMessages

// ─── Метод для подключения класса ───

VOID TabPage_Start( VOID )
{
 #ifdef TabPage
 bzero( &TabPage, sizeof( TabPage ) );
 #endif

 // Возврат.
 return;
}
