// ��⮤� ��� ���������� ��࠭��-"��������".
#define CreateCtlButtons    TabPage_CreateCtlButtons
#define CreatePromptText    TabPage_CreatePromptText
#define CompleteCreation    TabPage_CompleteCreation

#define UpdatePageWindow    TabPage_UpdatePageWindow

#define BroadcastRSMessages TabPage_BroadcastRSMessages

// ��� ��⮤ ��� ������祭�� ����� ���

VOID TabPage_Start( VOID )
{
 #ifdef TabPage
 bzero( &TabPage, sizeof( TabPage ) );
 #endif

 // ������.
 return;
}
