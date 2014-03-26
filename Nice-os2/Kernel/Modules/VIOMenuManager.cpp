// ��⮤� ��� ���������� ����� ��ப ���� � ⥪�⮢�� �����.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID VIOMenuManager_Start( VOID )
{
 #ifdef VIOMenuManager
 bzero( &VIOMenuManager, sizeof( VIOMenuManager ) );
 #endif

 // ������ ����ன�� �� 㬮�砭��.
 VIOMenuManager.RTSettings.Commands_menu_ID = 7000;

 // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
 MODULE Item; PresetModuleItem( &Item );

 Item.StartThread = VIOMenuManager_StartThread;
 Item.PostQuitMsg = VIOMenuManager_PostQuitMsg;
 Item.TuneModule  = VIOMenuManager_Tune;

 RememberModuleItem( Enhancer.Modules.VIOMenuManager, &Item );

 // ������.
 return;
}

