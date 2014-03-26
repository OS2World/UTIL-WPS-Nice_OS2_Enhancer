// ��⮤� ��� ������� �ਮ��⮢ �ਫ������.
#define SetDynamicPriorityLevels    PriorityManager_SetDynamicPriorityLevels

// ��� ��⮤ ��� ������祭�� ����� ���

VOID PriorityManager_Start( VOID )
{
 #ifdef PriorityManager
 bzero( &PriorityManager, sizeof( PriorityManager ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = PriorityManager_Tune;

 RememberModuleItem( Enhancer.Modules.PriorityManager, &Item );

 // ������.
 return;
}

