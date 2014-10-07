// Окно настроек.
typedef struct _KBDACTIONSPAGE
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Поля ввода в окне.
    ULONG Detect_button_ID;

    ULONG ExeName_filebox_ID;
    ULONG ExeName_label_ID;
    ULONG ExeName_name_ID;
    ULONG ExeName_button_ID;

    ULONG SplitView_ID;
    ULONG Key_list_ID;
    ULONG Action_list_ID;

    // Внутренние переменные.
    BYTE Key_list_is_locked;
    BYTE Action_list_is_locked;

    PINT Key_code;
    PCHAR UserTool_name;
    PCHAR UserTool_path;

    // Клавиши и действия.
    typedef struct _KEYPTR
     {
      PINT Key; PINT Scan_code; PBYTE Permission;
     }
    KEYPTR;

    typedef struct _ACTIONS
     {
      KEYPTR Keys[ MAX_KEYS ]; INT Actions[ MAX_ACTIONS ];
     }
    ACTIONS; ACTIONS Actions;
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
KBDACTIONSPAGE;

KBDACTIONSPAGE Keyboard_Actions;
