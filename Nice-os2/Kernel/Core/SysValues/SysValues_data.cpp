// �������襥 �᫮ 梥⮢, ���祭�� ������ ���������� ����⥫�� (�ᥣ�� �⭮� �᫮).
#define SYSVALUES_SYSCLRS_TO_CHANGE     32
// �������襥 �᫮ ����஥�, ���祭�� ������ ���������� ����⥫��.
#define SYSVALUES_SYSVALS_TO_CHANGE     16

// ������ ��� ��⠢����� ����⥫�.
typedef struct _PREFERRED_SYSTEM_COLORS
 {
  // ����� ��������.
  ULONG cb;

  // ������ ��� ���������� ��� ���� ᢥ⫮-��� 梥�?
  BYTE Normalize_window_background;
  // ������ ��������� ����?
  typedef struct _HRWT
   {
    BYTE For_neon_theme;
    BYTE For_grayed_theme;
   }
  HRWT; HRWT Hide_real_window_title;
  // ��⠭����� ��� ���� ࠡ�祣� �⮫� ��� 梥�?
  BYTE Set_black_desktop_background;
 }
PREFERRED_SYSTEM_COLORS; typedef PREFERRED_SYSTEM_COLORS* PPREFERRED_SYSTEM_COLORS;

typedef struct _PREFERRED_SYSTEM_VALUES
 {
  // ����� ��������.
  ULONG cb;

  // �������� �ਭ� ࠬ��?
  BYTE Change_border_width; INT New_border_width;
  // �⪫���� ������� "PrintScreen"?
  BYTE Disable_PrintScreen;
  // �⪫���� "����⢨� ����� � ����� VIO"?
  BYTE Disable_VIO_mouse_actions;
 }
PREFERRED_SYSTEM_VALUES; typedef PREFERRED_SYSTEM_VALUES* PPREFERRED_SYSTEM_VALUES;

// ��������� ����஥� � 梥⮢ �����窨 OS/2.
typedef struct _SYSVALUES
 {
  // ���� � ����ன�� OS/2 �� � ��᫥ ����᪠ ����⥫�.
  SYSCLR_ENTRY Old_colors[ SYSVALUES_SYSCLRS_TO_CHANGE ];
  SYSCLR_ENTRY New_colors[ SYSVALUES_SYSCLRS_TO_CHANGE ];

  SYSVAL_ENTRY Old_values[ SYSVALUES_SYSVALS_TO_CHANGE ];
  SYSVAL_ENTRY New_values[ SYSVALUES_SYSVALS_TO_CHANGE ];
 }
SYSVALUES; SYSVALUES SysValues;
