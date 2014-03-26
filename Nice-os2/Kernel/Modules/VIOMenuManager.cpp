// Методы для добавления новых строк меню в текстовых окнах.

// ─── Метод для подключения класса ───

VOID VIOMenuManager_Start( VOID )
{
 #ifdef VIOMenuManager
 bzero( &VIOMenuManager, sizeof( VIOMenuManager ) );
 #endif

 // Задаем настройки по умолчанию.
 VIOMenuManager.RTSettings.Commands_menu_ID = 7000;

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = VIOMenuManager_StartThread;
 Item.PostQuitMsg = VIOMenuManager_PostQuitMsg;
 Item.TuneModule  = VIOMenuManager_Tune;

 RememberModuleItem( Enhancer.Modules.VIOMenuManager, &Item );

 // Возврат.
 return;
}

