// Окно настроек.
typedef struct _MSEMENUSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Sysmenu_ID;
  }
  INRSTS; INRSTS Settings;
}
MSEMENUSPAGE;

MSEMENUSPAGE Mouse_Menus;
