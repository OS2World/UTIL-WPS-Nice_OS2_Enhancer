// Методы для воспроизведения звука при нажатии на клавишу.

// ─── Метод для подключения класса ───

VOID Clicker_Start( VOID )
{
 #ifdef Clicker
 bzero( &Clicker, sizeof( Clicker ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Clicker_StartThread;
 Item.PostQuitMsg = Clicker_PostQuitMsg;
 Item.TuneModule  = Clicker_Tune;

 RememberModuleItem( Enhancer.Modules.Clicker, &Item );

 // Возврат.
 return;
}

