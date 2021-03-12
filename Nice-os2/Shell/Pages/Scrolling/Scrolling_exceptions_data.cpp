// Окно настроек.
typedef struct _SCRXCPTNSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Container_Kbd_ID;
    ULONG List_Kbd_ID;
    ULONG Add_button_Kbd_ID;
    ULONG Remove_button_Kbd_ID;

    ULONG Container_Mou_ID;
    ULONG List_Mou_ID;
    ULONG Add_button_Mou_ID;
    ULONG Remove_button_Mou_ID;
  }
  INRSTS; INRSTS Settings;
}
SCRXCPTNSPAGE;

SCRXCPTNSPAGE Scrolling_Exceptions;
