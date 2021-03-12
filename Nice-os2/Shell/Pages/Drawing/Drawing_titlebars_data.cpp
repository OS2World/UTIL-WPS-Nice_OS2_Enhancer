// Окно настроек.
typedef struct _DRWTBARSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG NeonPalette_Container_ID;
    ULONG NeonPalette_Palette_ID;
    ULONG NeonPalette_Inactive_1_ID;
    ULONG NeonPalette_Inactive_2_ID;
    ULONG NeonPalette_Inactive_3_ID;
    ULONG NeonPalette_Active_1_ID;
    ULONG NeonPalette_Active_2_ID;
    ULONG NeonPalette_Active_3_ID;
    ULONG NeonPalette_FillTB_ID;

    ULONG WinTitles_Container_ID;
    ULONG WinTitles_Palette_ID;
    ULONG WinTitles_Inactive_ID;
    ULONG WinTitles_Active_ID;
    ULONG WinTitles_Button_ID;
    ULONG WinTitles_DrawText_ID;
  }
  INRSTS; INRSTS Settings;
}
DRWTBARSPAGE;

DRWTBARSPAGE Drawing_Titlebars;
