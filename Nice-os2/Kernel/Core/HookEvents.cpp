// ��⮤� ��� �஢�ન ��᫥�������� ᮮ�饭��.
#define TopFrameWindowIsShowing       HookEvents_TopFrameWindowIsShowing
#define TopFrameWindowIsMoving        HookEvents_TopFrameWindowIsMoving
#define TopFrameWindowIsActivating    HookEvents_TopFrameWindowIsActivating
#define TopFrameWindowIsInactivating  HookEvents_TopFrameWindowIsInactivating
#define FrameWindowIsActivating       HookEvents_FrameWindowIsActivating

#define FrameWindowIsClosing          HookEvents_FrameWindowIsClosing

// ��� ��⮤ ��� ������祭�� ����� ���

VOID HookEvents_Start( VOID )
{
 #ifdef HookEvents
 bzero( &HookEvents, sizeof( HookEvents ) );
 #endif

 // ������.
 return;
}

