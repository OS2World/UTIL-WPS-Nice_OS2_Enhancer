// Окно настроек.
typedef struct _DLGBOXESPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG WinList_Container_ID;
    ULONG ButtonBox_ID;
    ULONG AddRemove_ID;
    ULONG UseCmd_button_ID;
    ULONG Action_label_ID;
    ULONG Action_cmbox_ID;
    ULONG Window_list_ID;
    ULONG Window_Add_ID;
    ULONG Window_Remove_ID;
    ULONG SendYes_button_ID;

    // Внутренние переменные.
    BYTE Dialog_list_is_locked;
    PMSGDLGBOX Selected_dialog;
    BYTE Action_list_is_locked;
  }
  INRSTS; INRSTS Settings;
}
DLGBOXESPAGE;

DLGBOXESPAGE Dialogs_Boxes;
