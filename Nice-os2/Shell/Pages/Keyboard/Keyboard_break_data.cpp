// Окно настроек.
typedef struct _KBDBRKPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG CB_button_ID;
    ULONG CAD_button_ID;
  }
  INRSTS; INRSTS Settings;
}
KBDBRKPAGE;

KBDBRKPAGE Keyboard_Break;
