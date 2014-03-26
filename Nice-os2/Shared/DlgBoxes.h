// ������������ ����� �����.
#define DLG_INPUT_FIELD      1
#define DLG_ENTRY_FIELD      2

#define DLG_COMBO_BOX        3
#define DLG_LIST_BOX         4

#define DLG_SPIN_BUTTON      5
#define DLG_CHECKBOX_BUTTON  6
#define DLG_RADIO_BUTTON     7

#define DLG_PUSH_BUTTON      8

#define DLG_SLIDER           9

#define DLG_STATIC          10

// ����� ����� ����� � ���� � ᢮��⢠ ����.
#define DLG_MAX_FIELDS       50
#define DLG_MAX_BUTTONS      10

// ���� ����� � ���� �������.
typedef struct _DLGFIELD
 {
  // ���� ���� �����.
  HWND Window;
  // ��� ���� �����.
  LONG Type;
  // ���祭�� � ⥪�⮢�� ����. ��� "[x]" �� ����� ���� "-1", "0", "1" � �. �.
  CHAR Value[ SIZE_OF_DIALOG_FIELD ];
  // ���� ᮤ�ন� ⥪�⮢�� ���祭��, �ਣ����� ��� ���쭥�襣� �ᯮ�짮�����.
  BYTE Useful;
 }
DLGFIELD; typedef DLGFIELD* PDLGFIELD;

// �ந����쭮� ���� ������� � ����� ����� � ���.
typedef struct _DLGBOX
 {
  // ��� ࠬ�� ����.
  LONG Frame_type;
  // ��� �ਫ������, ᮧ���襣� ����.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // ��������� ����. ��� ���᪮�� ���� ᮮ�饭�� - ⥪�� ������.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // ����� ����� ����� � ���� � �� ���祭��.
  DLGFIELD Fields[ DLG_MAX_FIELDS ];
  INT Quantity;

  // ����⢨� ��������.
  BYTE Enabled; BYTE Text_fields_only;
 }
DLGBOX; typedef DLGBOX* PDLGBOX; typedef PDLGBOX* PPDLGBOX;

// ����� ��� �ᯮ������ �ਫ������ ��᫥ ����� ��஫�.
typedef struct _LOGONSCRIPTDATA
 {
  // ���祭��, ���࠭�� ���짮��⥫��.
  DLGFIELD Values[ DLG_MAX_FIELDS ];
  INT Quantity;

  // �ਫ������, �맢��襥 ���� ����� ��஫�.
  PID Process_ID;
 }
LOGONSCRIPTDATA; typedef LOGONSCRIPTDATA* PLOGONSCRIPTDATA;

// ���� ��� ����� ��஫�.
typedef struct _LOGONDLGBOX
 {
  // ��� ࠬ�� ����.
  LONG Frame_type;
  // ��� �ਫ������, ᮧ���襣� ����.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // ��������� ����. ��� ���᪮�� ���� ᮮ�饭�� - ⥪�� ������.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // �������, �易���� � ����� ��� ����� ��஫�.
  CHAR Logon_command[ SIZE_OF_PATH ];

  // ����� ��� �ᯮ������ �ਫ������ ��᫥ ����� ��஫�.
  LOGONSCRIPTDATA Parameters;

  // ����⢨� ��������.
  BYTE Enabled; BYTE Only_once; BYTE Action_performed;
 }
LOGONDLGBOX; typedef LOGONDLGBOX* PLOGONDLGBOX; typedef PLOGONDLGBOX* PPLOGONDLGBOX;

// ���� ᮮ�饭��.
typedef struct _MSGDLGBOX
 {
  // ��� ࠬ�� ����.
  LONG Frame_type;
  // ��� �ਫ������, ᮧ���襣� ����.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // ��������� ����. ��� ���᪮�� ���� ᮮ�饭�� - ⥪�� ������.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // ������ � ����.
  DLGFIELD Buttons[ DLG_MAX_BUTTONS ];
  INT Quantity; INT Close_button;

  // ����⢨� ��������.
  BYTE Enabled;
 }
MSGDLGBOX; typedef MSGDLGBOX* PMSGDLGBOX; typedef PMSGDLGBOX* PPMSGDLGBOX;
