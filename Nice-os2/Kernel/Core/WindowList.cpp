// ��⮤� ��� ࠡ��� � ᯨ᪮� ����.
#define SetJumpableFlag                      Krnl_WindowList_SetJumpableFlag
#define SetProcessJumpableFlag               Krnl_WindowList_SetProcessJumpableFlag
#define WindowIsJumpable                     Krnl_WindowList_WindowIsJumpable
#define WindowIsTouchable                    Krnl_WindowList_WindowIsTouchable
#define SetAllWindowsJumpable                Krnl_WindowList_SetAllWindowsJumpable

#define FindFrameWindowInWindowList          Krnl_WindowList_FindFrameWindowInWindowList

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Krnl_WindowList_Start( VOID )
{
 #ifdef Krnl_WindowList
 bzero( &Krnl_WindowList, sizeof( Krnl_WindowList ) );
 #endif

 // ������.
 return;
}
