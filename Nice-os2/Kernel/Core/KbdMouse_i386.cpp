#ifdef I386_ARCHITECTURE

// Методы для работы с клавиатурой и мышью.
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

// ─── Метод для подключения класса ───

VOID Krnl_KbdMouse_i386_Start( VOID )
{
 #ifdef Krnl_KbdMouse_i386
 bzero( &Krnl_KbdMouse_i386, sizeof( Krnl_KbdMouse_i386 ) );
 #endif

 // Возврат.
 return;
}

#endif