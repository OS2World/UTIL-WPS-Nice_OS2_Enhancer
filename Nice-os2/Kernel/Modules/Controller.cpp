
// ��� ��⮤ ��� ������祭�� ����� ���

VOID Controller_Start( VOID )
{
 #ifdef Controller
 bzero( &Controller, sizeof( Controller ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread  = Controller_StartThread;
 Item.PostQuitMsg  = Controller_PostQuitMsg;
 Item.ShutdownAll  = Controller_ShutdownAll;
 Item.TuneModule   = Controller_Tune;
 Item.JumpBeforeGo = Controller_Jump;

 RememberModuleItem( Enhancer.Modules.Controller, &Item );

 // ������.
 return;
}

