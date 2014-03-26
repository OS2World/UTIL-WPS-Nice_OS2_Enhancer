// ��⮤� ��� ������ ����⢨� � ����� � ������� �ਫ�������.
#define ClipboardMouseAction    MouseMapper_ClipboardMouseAction

#define WMMBDownTime            MouseMapper_WMMBDownTime
#define DiscardWMMBDownTime     MouseMapper_DiscardWMMBDownTime

// ��� ��⮤ ��� ������祭�� ����� ���

VOID MouseMapper_Start( VOID )
{
 #ifdef MouseMapper
 bzero( &MouseMapper, sizeof( MouseMapper ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = MouseMapper_Tune;

 RememberModuleItem( Enhancer.Modules.MouseMapper, &Item );

 // ������.
 return;
}

