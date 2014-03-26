// Окно настроек.
typedef struct _CLIENT_WINDOW
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Buttons_brick_ID;

    ULONG Install_button_ID;
    ULONG Remove_button_ID;
    ULONG Cancel_button_ID;
   }
  INRSTS; INRSTS Settings;

  // Расположение полей ввода.
  LTWALL Layout;
 }
CLIENT_WINDOW;

CLIENT_WINDOW Client_Window;
