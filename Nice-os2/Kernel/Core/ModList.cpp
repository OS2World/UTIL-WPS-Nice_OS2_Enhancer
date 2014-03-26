// Методы для перебора составляющих приложения.
#define GetModListEntry      ModList_GetModListEntry

#define PresetModuleItem     ModList_PresetModuleItem
#define RememberModuleItem   ModList_RememberModuleItem

// ─── Метод для подключения класса ───

VOID ModList_Start( VOID )
{
 #ifdef ModList
 bzero( &ModList, sizeof( ModList ) );
 #endif

 // Возврат.
 return;
}
