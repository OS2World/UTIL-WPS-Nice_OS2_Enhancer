// ��⮤� ��� ��।������ ᢮��� ����.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Diver_Start( VOID )
{
 #ifdef Diver
 bzero( &Diver, sizeof( Diver ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Diver_StartThread;
 Item.PostQuitMsg = Diver_PostQuitMsg;

 RememberModuleItem( Enhancer.Modules.Diver, &Item );

 // ������.
 return;
}

