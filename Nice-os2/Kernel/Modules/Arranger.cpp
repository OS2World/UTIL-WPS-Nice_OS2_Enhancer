// Методы для выравнивания окон.
#define ArrangeVIOWindows Arranger_ArrangeVIOWindows

// ─── Метод для подключения класса ───

VOID Arranger_Start( VOID )
{
 #ifdef Arranger
 bzero( &Arranger, sizeof( Arranger ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Arranger_StartThread;
 Item.PostQuitMsg = Arranger_PostQuitMsg;
 Item.TuneModule  = Arranger_Tune;

 RememberModuleItem( Enhancer.Modules.Arranger, &Item );

 // Возврат.
 return;
}

