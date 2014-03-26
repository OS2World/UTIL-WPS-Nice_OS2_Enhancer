// Окно настроек.
typedef struct _MOUSEVIOPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Mouse_button_ID;
    ULONG Mouse_Shift_button_ID;
    ULONG Mouse_Remember_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
MOUSEVIOPAGE;

MOUSEVIOPAGE Mouse_VIO;
