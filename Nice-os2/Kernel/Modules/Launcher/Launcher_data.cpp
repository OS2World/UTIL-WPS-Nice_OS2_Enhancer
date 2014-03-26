// Выполнение различных действий
typedef struct _LAUNCHER
 {
  // Внутренние переменные.
  typedef struct _RTSTS 
   {
    // Работает ли проигрыватель.
    BYTE Player_is_stopped;
    // Значение громкости для проигрывателя.
    INT Player_volume;
    // Значение громкости в MMOS2.
    SHORT MMOS2_volume; SHORT MMOS2_volume_from; SHORT MMOS2_volume_to;
   }
  RTSTS; RTSTS RTSettings;
 }
LAUNCHER;

LAUNCHER Launcher;