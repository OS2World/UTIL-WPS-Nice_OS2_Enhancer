#define MAX_VIO_MENU_FILES    16
#define MAX_VIO_MENU_TITLES   10
#define MAX_VIO_MENU_COMMANDS 100
#define MAX_VIO_FILE_STRINGS  ( MAX_VIO_MENU_COMMANDS * 2 )

// Меню в текстовых окнах.
typedef struct _VIOMENUMANAGER
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Добавлять список команд в окна SSH? 0 - нет, 1 - да.
    BYTE SSH_Commands; BYTE Use_AltTilde;
    CHAR Files[ MAX_VIO_MENU_FILES ][ SIZE_OF_PATH ];
   }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Строка в меню первого уровня.
    ULONG Commands_menu_ID;

    // Файлы и команды.
    typedef struct _PROMPTFILE
     {
      BYTE Active; FDATE Date; FTIME Time;
      CHAR Titles[ MAX_VIO_MENU_TITLES ][ SIZE_OF_NAME ];
      CHAR Commands[ MAX_VIO_MENU_COMMANDS ][ SIZE_OF_ITEM_TEXT ];
     }
    PROMPTFILE; PROMPTFILE Files[ MAX_VIO_MENU_FILES ];
   }
  RTSTS; RTSTS RTSettings;
 }
VIOMENUMANAGER;

VIOMENUMANAGER VIOMenuManager;
