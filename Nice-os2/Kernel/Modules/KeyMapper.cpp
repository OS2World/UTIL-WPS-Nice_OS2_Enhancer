// ��⮤� ��� ������ ������ � ������� �ਫ�������.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID KeyMapper_Start( VOID )
{
 #ifdef KeyMapper
 bzero( &KeyMapper, sizeof( KeyMapper ) );
 #endif

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = KeyMapper_Tune;

 RememberModuleItem( Enhancer.Modules.KeyMapper, &Item );

 // ������.
 return;
}

