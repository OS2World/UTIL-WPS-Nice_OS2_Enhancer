// ��⮤� ��� ��ॡ�� ��⠢����� �ਫ������.
#define GetModListEntry      ModList_GetModListEntry

#define PresetModuleItem     ModList_PresetModuleItem
#define RememberModuleItem   ModList_RememberModuleItem

// ��� ��⮤ ��� ������祭�� ����� ���

VOID ModList_Start( VOID )
{
 #ifdef ModList
 bzero( &ModList, sizeof( ModList ) );
 #endif

 // ������.
 return;
}
