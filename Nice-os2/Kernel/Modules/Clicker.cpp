// ��⮤� ��� ���ந�������� ��㪠 �� ����⨨ �� �������.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Clicker_Start( VOID )
{
 #ifdef Clicker
 bzero( &Clicker, sizeof( Clicker ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Clicker_StartThread;
 Item.PostQuitMsg = Clicker_PostQuitMsg;
 Item.TuneModule  = Clicker_Tune;

 RememberModuleItem( Enhancer.Modules.Clicker, &Item );

 // ������.
 return;
}

