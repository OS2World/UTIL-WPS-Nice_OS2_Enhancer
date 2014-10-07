// Окно настроек.
typedef struct _VIOSSHPROMPTSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
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

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Последний выбранный каталог.
    CHAR FileDlg_path[ SIZE_OF_PATH ];
   }
  RTSETTINGS; RTSETTINGS RTSettings;
 }
VIOSSHPROMPTSPAGE;

VIOSSHPROMPTSPAGE VIOWindows_SSH_Prompts;

