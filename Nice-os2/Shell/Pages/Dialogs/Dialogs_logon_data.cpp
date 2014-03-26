// Окно настроек.
typedef struct _DLGLOGONPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG WinList_Container_ID;
    ULONG CommandBox_ID;
    ULONG AddRemove_ID;
    ULONG OnlyOnce_button_ID;
    ULONG Command_entry_ID;
    ULONG Command_button_ID;
    ULONG Window_list_ID;
    ULONG Window_Add_ID;
    ULONG Window_Remove_ID;
    ULONG Execute_button_ID;

    // Внутренние переменные.
    BYTE Dialog_list_is_locked;
    PLOGONDLGBOX Selected_dialog;
    BYTE Command_field_is_locked;
   }
  INRSTS; INRSTS Settings;
 }
DLGLOGONPAGE;

DLGLOGONPAGE Dialogs_Logon;
