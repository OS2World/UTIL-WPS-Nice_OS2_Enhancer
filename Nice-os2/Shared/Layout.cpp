// ��⮤� ��� �ᯮ������� ����� ����� � �����.
#define LitCreateLayout      Layout_LitCreateLayout
#define LitDeleteLayout      Layout_LitDeleteLayout

#define LitPrepareBrick      Layout_LitPrepareBrick
#define LitJoinBrick         Layout_LitJoinBrick
#define LitCompleteRow       Layout_LitCompleteRow

#define LitApplyLayout       Layout_LitApplyLayout
#define LitShowFrameWindow   Layout_LitShowFrameWindow

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Layout_Start( VOID )
{
 #ifdef Layout
 bzero( &Layout, sizeof( Layout ) );
 #endif

 // ������.
 return;
}
