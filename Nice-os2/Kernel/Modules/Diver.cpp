// Методы для определения свойств окон.

// ─── Метод для подключения класса ───

VOID Diver_Start( VOID )
{
 #ifdef Diver
 bzero( &Diver, sizeof( Diver ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Diver_StartThread;
 Item.PostQuitMsg = Diver_PostQuitMsg;

 RememberModuleItem( Enhancer.Modules.Diver, &Item );

 // Возврат.
 return;
}

