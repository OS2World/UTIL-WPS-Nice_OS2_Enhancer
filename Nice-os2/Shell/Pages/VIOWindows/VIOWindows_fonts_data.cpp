// Окно настроек.
typedef struct _VIOWNDPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG AppList_Container_ID;
    ULONG SelectBox_ID;
    ULONG Selected_font_cmbox_ID;
    ULONG Application_list_ID;
    ULONG AddRemove_ID;
    ULONG Application_Add_ID;
    ULONG Application_Remove_ID;

    ULONG KnownApps_button_ID;
    ULONG SetFont_button_ID;

    // Установка шрифта в текстовых окнах.
    BYTE FontMetrics_list_is_locked;
    PINT Shell_font_X; PINT Shell_font_Y;
  }
  INRSTS; INRSTS Settings;
}
VIOWNDPAGE;

VIOWNDPAGE VIOWindows_Fonts;
