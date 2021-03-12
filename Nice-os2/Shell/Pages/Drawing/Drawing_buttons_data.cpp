// Окно настроек.
typedef struct _DRWBTNSPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Buttons_WPS_ID;
    ULONG Buttons_VIO_ID;

    ULONG RollUp_Container_ID;
    ULONG RollUp_List_ID;
    ULONG RollUp_Add_ID;
    ULONG RollUp_Remove_ID;
  }
  INRSTS; INRSTS Settings;
}
DRWBTNSPAGE;

DRWBTNSPAGE Drawing_Buttons;
