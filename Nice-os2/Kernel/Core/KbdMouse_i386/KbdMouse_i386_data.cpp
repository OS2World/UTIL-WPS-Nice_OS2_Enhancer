// Работа с мышью и клавиатурой.
typedef struct _KBDMOUSEI386
 {
  // Отлов ошибки, связанной с дерганием мыши.
  LONG Last_mouse_busy_time;
 }
KBDMOUSEI386;

KBDMOUSEI386 Krnl_KbdMouse_i386;