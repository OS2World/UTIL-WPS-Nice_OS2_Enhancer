// Окно настроек.
typedef struct _KBDRPSTRYPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG CheckWPS_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
KBDRPSTRYPAGE;

KBDRPSTRYPAGE Keyboard_Repository;
