// Методы для замены клавиш в оконных приложениях.

// ─── Метод для подключения класса ───

VOID KeyMapper_Start( VOID )
{
 #ifdef KeyMapper
 bzero( &KeyMapper, sizeof( KeyMapper ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = KeyMapper_Tune;

 RememberModuleItem( Enhancer.Modules.KeyMapper, &Item );

 // Возврат.
 return;
}

