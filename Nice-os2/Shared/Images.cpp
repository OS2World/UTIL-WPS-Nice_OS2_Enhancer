// ��⮤� ��� ࠡ��� � ����ࠦ���ﬨ.
#define CreatePresentationSpace Images_CreatePresentationSpace
#define CreateBitmap            Images_CreateBitmap
#define LoadBitmap              Images_LoadBitmap

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Images_Start( VOID )
{
 #ifdef Images
 bzero( &Images, sizeof( Images ) );
 #endif

 // ������.
 return;
}

