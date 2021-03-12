// Окно настроек.
typedef struct _WLSTSTSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Modify_WinList_button_ID;
    ULONG Container_ID;
    ULONG Hidden_list_ID;
    ULONG Hidden_buttons_ID;
    ULONG Hidden_Move2V_button_ID;
    ULONG Visible_list_ID;
    ULONG Visible_buttons_ID;
    ULONG Visible_Move2H_button_ID;
    ULONG Visible_Refresh_button_ID;
  }
  INRSTS; INRSTS Settings;
}
WLSTSTSPAGE;

WLSTSTSPAGE WinList_Settings;
