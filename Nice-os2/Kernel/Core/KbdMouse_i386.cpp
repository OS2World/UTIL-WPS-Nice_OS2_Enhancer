#ifdef I386_ARCHITECTURE

// ��⮤� ��� ࠡ��� � ��������ன � �����.
#define ComposeWMCharMessage             Krnl_KbdMouse_i386_ComposeWMCharMessage
#define ComposeWMCharMessageForVIOWindow Krnl_KbdMouse_i386_ComposeWMCharMessageForVIOWindow
#define FindRelatedWMCommandAccelerator  Krnl_KbdMouse_i386_FindRelatedWMCommandAccelerator

#define KeyIsPressed                     Krnl_KbdMouse_i386_KeyIsPressed
#define KeyIsToggled                     Krnl_KbdMouse_i386_KeyIsToggled
#define CtrlIsPressed                    Krnl_KbdMouse_i386_CtrlIsPressed
#define AltIsPressed                     Krnl_KbdMouse_i386_AltIsPressed
#define ShiftIsPressed                   Krnl_KbdMouse_i386_ShiftIsPressed
#define WinKeyIsPressed                  Krnl_KbdMouse_i386_WinKeyIsPressed

#define MouseCanBeBusy                   Krnl_KbdMouse_i386_MouseCanBeBusy

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Krnl_KbdMouse_i386_Start( VOID )
{
 #ifdef Krnl_KbdMouse_i386
 bzero( &Krnl_KbdMouse_i386, sizeof( Krnl_KbdMouse_i386 ) );
 #endif

 // ������.
 return;
}

#endif