// Методы для удаления строк из списка окон.
#define WindowWillBeHidden Remover_WindowWillBeHidden

// ─── Метод для подключения класса ───

VOID Remover_Start( VOID )
{
 #ifdef Remover
 bzero( &Remover, sizeof( Remover ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread  = Remover_StartThread;
 Item.PostQuitMsg  = Remover_PostQuitMsg;
 Item.ShutdownAll  = Remover_ShutdownAll;
 Item.TuneModule   = Remover_Tune;
 Item.JumpBeforeGo = Remover_Jump;

 RememberModuleItem( Enhancer.Modules.Remover, &Item );

 // Возврат.
 return;
}

