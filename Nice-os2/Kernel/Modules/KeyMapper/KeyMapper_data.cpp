// Замена клавиш в оконных приложениях.
typedef struct _KEYMAPPER
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Включить клавиши для того, чтобы запоминать и вставлять текст? 0 - нет, 1 - да.
    BYTE Define_Ctrl_CV;
    // Определить клавишу "|\"? 0 - нет, 1 - да.
    BYTE Define_Dash;
    BYTE Define_Ctrl_Dash;
    // Определить клавишу Enter для ввода значения на рабочем столе? 0 - нет, 1 - да.
    BYTE Define_Enter;
    // Отключить клавишу F3, если она используется как "ускоритель"? 0 - нет, 1 - да.
    BYTE Discard_F3;
    // Включить клавиши "Alt + F4 / F9" в текстовых окнах? 0 - нет, 1 - да.
    BYTE Enable_WMKeys_in_VIO;
   }
  INRSTS; INRSTS Settings;
 }
KEYMAPPER;

KEYMAPPER KeyMapper;
