// Выделение строк в окнах.
typedef struct _MARKER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Определить "Ctrl/Shift+Ins" в текстовых окнах? 0 - нет, 1 - да.
    BYTE CopyPaste_keys_in_VIO;

    // Включать действия с мышью в текстовых окнах? 0 - нет, 1 - да.
    BYTE Mouse_in_VIO;
    BYTE Mouse_in_VIO_requires_Shift;
    BYTE Mouse_in_VIO_sends_Copy;
  }
  INRSTS; INRSTS Settings;

  // Временные переменные.
  typedef struct _RTSTS
  {
    // Содержимое Clipboard на всемя нажатия FireFox-клавиш.
    PBYTE Clipboard_data_Text; INT Clipboard_data_Text_length;
    PBYTE Clipboard_data_UCS2; INT Clipboard_data_UCS2_length;
  }
  RTSTS; RTSTS RTSettings;
}
MARKER;

MARKER Clipper;