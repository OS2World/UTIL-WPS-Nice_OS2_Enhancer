// Окно настроек.
typedef struct _SPTSTSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG ScreenSaver_button_ID;
    ULONG Animation_button_ID;
    ULONG WarpCenter_button_ID;
    ULONG RestoreWnd_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
SPTSTSPAGE;

SPTSTSPAGE SysPatches_Settings;
