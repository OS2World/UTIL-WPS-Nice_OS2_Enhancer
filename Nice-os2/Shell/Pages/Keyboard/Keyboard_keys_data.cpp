// Клавиши и действия.
#define MAX_KEYS          129
#define MAX_ACTIONS       163

// Окно настроек.
typedef struct _KBDKEYSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Container_ID;
    ULONG Use_button_ID;
    ULONG Kbd_list_ID;
    ULONG Define_button_ID;

    ULONG Key_list_is_locked;
    PBYTE Key_permission;
   }
  INRSTS; INRSTS Settings;
 }
KBDKEYSPAGE;

KBDKEYSPAGE Keyboard_Keys;
