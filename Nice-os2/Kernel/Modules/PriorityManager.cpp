// Методы для задания приоритетов приложений.
#define SetDynamicPriorityLevels    PriorityManager_SetDynamicPriorityLevels

// ─── Метод для подключения класса ───

VOID PriorityManager_Start( VOID )
{
 #ifdef PriorityManager
 bzero( &PriorityManager, sizeof( PriorityManager ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = PriorityManager_Tune;

 RememberModuleItem( Enhancer.Modules.PriorityManager, &Item );

 // Возврат.
 return;
}

