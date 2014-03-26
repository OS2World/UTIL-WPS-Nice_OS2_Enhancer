// Окно настроек.
typedef struct _CLIENT_WINDOW
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG List_ID;
    ULONG Text_ID;
   }
  INRSTS; INRSTS Settings;

  // Расположение полей ввода.
  LTWALL Layout;
 }
CLIENT_WINDOW;

CLIENT_WINDOW Client_Window;
