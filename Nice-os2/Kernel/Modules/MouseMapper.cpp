// Методы для замены действий с мышью в оконных приложениях.
#define ClipboardMouseAction    MouseMapper_ClipboardMouseAction

#define WMMBDownTime            MouseMapper_WMMBDownTime
#define DiscardWMMBDownTime     MouseMapper_DiscardWMMBDownTime

// ─── Метод для подключения класса ───

VOID MouseMapper_Start( VOID )
{
 #ifdef MouseMapper
 bzero( &MouseMapper, sizeof( MouseMapper ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = MouseMapper_Tune;

 RememberModuleItem( Enhancer.Modules.MouseMapper, &Item );

 // Возврат.
 return;
}

