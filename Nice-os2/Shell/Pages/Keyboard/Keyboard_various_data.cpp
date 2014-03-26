// Окно настроек.
typedef struct _KBDVRSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Keep_NumLock;
    ULONG NumLock_cbox;
    ULONG NumKeys;

    ULONG Ctrl_CV;
    ULONG WPS_Enter;
    ULONG CUA_F3;

    // Внутренние переменные.
    ULONG Turn_Num_Lock;
   }
  INRSTS; INRSTS Settings;
 }
KBDVRSPAGE;

KBDVRSPAGE Keyboard_Various;
