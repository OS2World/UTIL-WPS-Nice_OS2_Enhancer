// Управление переключателями на клавиатуре.
typedef struct _KBDLOCKS
 {
  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Состояние Ctrl + Alt + Del.
    BYTE Ctrl_Alt_Del_is_disabled;
   }
  RTSTS; RTSTS RTSettings;
 }
KBDLOCKS;

KBDLOCKS KbdLocks;