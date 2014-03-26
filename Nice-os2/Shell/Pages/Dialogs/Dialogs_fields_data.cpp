// Окно настроек.
typedef struct _DLGFIELDSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG WinList_Container_ID;
    ULONG ControlBox_ID;
    ULONG AddRemove_ID;
    ULONG TextOnly_button_ID;
    ULONG Restore_button_ID;
    ULONG Window_list_ID;
    ULONG Window_Add_ID;
    ULONG Window_Remove_ID;
    ULONG Remember_button_ID;

    // Внутренние переменные.
    BYTE Dialog_list_is_locked;
    PDLGBOX Selected_dialog;
   }
  INRSTS; INRSTS Settings;
 }
DLGFIELDSPAGE;

DLGFIELDSPAGE Dialogs_Fields;
