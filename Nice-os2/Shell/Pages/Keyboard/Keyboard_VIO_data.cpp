// Окно настроек.
typedef struct _KBDVIOPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG CopyPaste_button_ID;
    ULONG WinCloseHide_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
KBDVIOPAGE;

KBDVIOPAGE Keyboard_VIO;
