// ��⮤� ��� �ᯮ�������� ����.
#define WindowIsPresent WindowTypes_WindowIsPresent

#define WindowType WindowTypes_WindowType
#define FrameType  WindowTypes_FrameType

// ��� ��⮤ ��� ������祭�� ����� ���

VOID WindowTypes_Start( VOID )
{
 #ifdef WindowTypes
 bzero( &WindowTypes, sizeof( WindowTypes ) );
 #endif

 // ������.
 return;
}

