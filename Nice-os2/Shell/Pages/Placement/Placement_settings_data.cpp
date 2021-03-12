// Окно настроек.
typedef struct _PLCMNTSTSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG VIO_button_ID;
    ULONG FC2_button_ID;
    ULONG WindowList_button_ID;
    ULONG WPS_button_ID;
    ULONG Browser_button_ID;
    ULONG Network_button_ID;
    ULONG XWP_button_ID;
  }
  INRSTS; INRSTS Settings;
}
PLCMNTSTSPAGE;

PLCMNTSTSPAGE Placement_Settings;
