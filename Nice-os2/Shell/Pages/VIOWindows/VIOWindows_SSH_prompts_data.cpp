// ���� ����஥�.
typedef struct _VIOSSHPROMPTSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG SSH_Commands_button_ID;
    ULONG Use_AltTilde_button_ID;

    ULONG FileList_Container_ID;
    ULONG SelectBox_ID;
    ULONG File_list_ID;
    ULONG AddRemove_ID;
    ULONG File_Add_ID;
    ULONG File_Remove_ID;
   }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ��᫥���� ��࠭�� ��⠫��.
    CHAR FileDlg_path[ SIZE_OF_PATH ];
   }
  RTSETTINGS; RTSETTINGS RTSettings;
 }
VIOSSHPROMPTSPAGE;

VIOSSHPROMPTSPAGE VIOWindows_SSH_Prompts;

