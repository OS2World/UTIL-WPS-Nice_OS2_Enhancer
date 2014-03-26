// ��⮤� ��� ��ࠢ������� ����.
#define ArrangeVIOWindows Arranger_ArrangeVIOWindows

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Arranger_Start( VOID )
{
 #ifdef Arranger
 bzero( &Arranger, sizeof( Arranger ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = Arranger_StartThread;
 Item.PostQuitMsg = Arranger_PostQuitMsg;
 Item.TuneModule  = Arranger_Tune;

 RememberModuleItem( Enhancer.Modules.Arranger, &Item );

 // ������.
 return;
}

