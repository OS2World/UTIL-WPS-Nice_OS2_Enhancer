// Окно настроек.
typedef struct _KBDSPEEDPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Reset_Shift_button_ID;

    ULONG SpeedUp_button_ID;
    ULONG Rate_cbox_ID;
  }
  INRSTS; INRSTS Settings;
}
KBDSPEEDPAGE;

KBDSPEEDPAGE Keyboard_Speed;
