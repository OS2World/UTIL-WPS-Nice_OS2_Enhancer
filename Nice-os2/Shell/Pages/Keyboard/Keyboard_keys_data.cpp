// ������ � ����⢨�.
#define MAX_KEYS          129
#define MAX_ACTIONS       163

// ���� ����஥�.
typedef struct _KBDKEYSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
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
