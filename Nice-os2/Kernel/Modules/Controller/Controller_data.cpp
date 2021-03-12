// Управление переключателями на клавиатуре.
typedef struct _CONTROLLER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Включать Num Lock? 0 - не трогать, 1 - включать, 2 - выключать.
    BYTE Turn_Num_Lock;
    // Определить цифровые клавиши как 1..9? 0 - нет, 1 - да.
    BYTE Define_Num_keys;

    // Сбрасывать клавиши "Shift"? 0 - нет, 1 - да.
    BYTE Reset_Shift_keys;

    // Разогнать клавиатуру? 0 - нет, 1 - да.
    BYTE SpeedUp_keyboard; BYTE Keyboard_rate;

    // Отключить Ctrl + Alt + Del? 0 - нет, 1 - да.
    BYTE Suppress_CtrlAltDel;
    // Отключить Ctrl + Break? 0 - нет, 1 - да.
    BYTE Suppress_CtrlBreak;
  }
  INRSTS; INRSTS Settings;
}
CONTROLLER;

CONTROLLER Controller;