// ���� ����஥�.
typedef struct _DLGFIELDSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG WinList_Container_ID;
    ULONG ControlBox_ID;
    ULONG AddRemove_ID;
    ULONG TextOnly_button_ID;
    ULONG Restore_button_ID;
    ULONG Window_list_ID;
    ULONG Window_Add_ID;
    ULONG Window_Remove_ID;
    ULONG Remember_button_ID;

    // ����७��� ��६����.
    BYTE Dialog_list_is_locked;
    PDLGBOX Selected_dialog;
   }
  INRSTS; INRSTS Settings;
 }
DLGFIELDSPAGE;

DLGFIELDSPAGE Dialogs_Fields;
