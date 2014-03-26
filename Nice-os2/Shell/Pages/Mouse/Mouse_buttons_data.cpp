// Окно настроек.
typedef struct _MSEBTNSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG ScrollBars_ID;
    ULONG CapsLock_ID;
   }
  INRSTS; INRSTS Settings;
 }
MSEBTNSPAGE;

MSEBTNSPAGE Mouse_Buttons;
