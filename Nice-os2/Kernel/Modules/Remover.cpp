// ��⮤� ��� 㤠����� ��ப �� ᯨ᪠ ����.
#define WindowWillBeHidden Remover_WindowWillBeHidden

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Remover_Start( VOID )
{
 #ifdef Remover
 bzero( &Remover, sizeof( Remover ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread  = Remover_StartThread;
 Item.PostQuitMsg  = Remover_PostQuitMsg;
 Item.ShutdownAll  = Remover_ShutdownAll;
 Item.TuneModule   = Remover_Tune;
 Item.JumpBeforeGo = Remover_Jump;

 RememberModuleItem( Enhancer.Modules.Remover, &Item );

 // ������.
 return;
}

