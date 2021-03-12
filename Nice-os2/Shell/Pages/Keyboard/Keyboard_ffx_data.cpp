// Окно настроек.
typedef struct _KBDFFXPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Dash;
    ULONG Ctrl_Dash;
  }
  INRSTS; INRSTS Settings;
}
KBDFFXPAGE;

KBDFFXPAGE Keyboard_FireFox;
