// ��⮤� ��� ��ॡ�� ��࠭�� �ਫ������.
#define GetPageListEntry   PageList_GetPageListEntry

#define PresetPageItem     PageList_PresetPageItem
#define RememberPageItem   PageList_RememberPageItem

#define BroadcastMessage   PageList_BroadcastMessage

// ��� ��⮤ ��� ������祭�� ����� ���

VOID PageList_Start( VOID )
{
 #ifdef PageList
 bzero( &PageList, sizeof( PageList ) );
 #endif

 // ������.
 return;
}
