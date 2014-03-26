#define INCL_DOS
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSERRORS

#include <OS2.h>

// ─── Приложение ───

VOID main( VOID )
{
 // Узнаем состояние клавиатуры.
 SHIFTSTATE Shift_state = {0};

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

 HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
 DosOpen( "\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0 );

 ULONG Length = sizeof( Shift_state ); ULONG No_data = 0; APIRET Result = ERROR_OPEN_FAILED;
 if( Keyboard ) Result = DosDevIOCtl( Keyboard, IOCTL_KEYBOARD, KBD_GETSHIFTSTATE, NULL, 0, &No_data, &Shift_state, sizeof( Shift_state ), &Length );

 // Включаем Num Lock.
 Shift_state.fsState |= NUMLOCK_ON;

 // Выключаем все остальное.
 Shift_state.fsState &= ~CAPSLOCK_ON;
 Shift_state.fsState &= ~SCROLLLOCK_ON;
 Shift_state.fsState &= ~INSERT_ON;

 // Устанавливаем новое состояние клавиатуры.
 if( Result == NO_ERROR )
  {
   ULONG Length = sizeof( Shift_state ); ULONG No_data = 0;
   DosDevIOCtl( Keyboard, IOCTL_KEYBOARD, KBD_SETSHIFTSTATE, &Shift_state, sizeof( Shift_state ), &Length, 0, 0, &No_data );
  }

 DosClose( Keyboard ); Keyboard = NULLHANDLE;

 // Выход.
 DosExit( EXIT_PROCESS, 0 );
}
