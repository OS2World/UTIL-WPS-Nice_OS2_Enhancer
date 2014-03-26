// Изменение состояния клавиатуры.
typedef struct _KBDSTATE
 {
  // Состояние клавиатуры изменено.
  BYTE Keyboard_state_is_changed;
 }
KBDSTATE;

KBDSTATE KbdState;