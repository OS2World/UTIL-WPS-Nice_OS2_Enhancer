#define MAX_VIO_MENU_FILES    16
#define MAX_VIO_MENU_TITLES   10
#define MAX_VIO_MENU_COMMANDS 100
#define MAX_VIO_FILE_STRINGS  ( MAX_VIO_MENU_COMMANDS * 2 )

// ���� � ⥪�⮢�� �����.
typedef struct _VIOMENUMANAGER
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ��������� ᯨ᮪ ������ � ���� SSH? 0 - ���, 1 - ��.
    BYTE SSH_Commands; BYTE Use_AltTilde;
    CHAR Files[ MAX_VIO_MENU_FILES ][ SIZE_OF_PATH ];
   }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ��ப� � ���� ��ࢮ�� �஢��.
    ULONG Commands_menu_ID;

    // ����� � �������.
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
