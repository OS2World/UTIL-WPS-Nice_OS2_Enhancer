
// ─── Метод для подключения класса ───

VOID Controller_Start( VOID )
{
 #ifdef Controller
 bzero( &Controller, sizeof( Controller ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread  = Controller_StartThread;
 Item.PostQuitMsg  = Controller_PostQuitMsg;
 Item.ShutdownAll  = Controller_ShutdownAll;
 Item.TuneModule   = Controller_Tune;
 Item.JumpBeforeGo = Controller_Jump;

 RememberModuleItem( Enhancer.Modules.Controller, &Item );

 // Возврат.
 return;
}

