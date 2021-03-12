// ���� ��� ����. �� ���祭�� ������� � INI. ������ �� ������⥫쭮.
#define PAINTER_THEME_PHOENIX              1
#define PAINTER_THEME_BLUE_LION            5
#define PAINTER_THEME_ECOMSTATION         10
#define PAINTER_THEME_CLASSIC_GRAY        20
#define PAINTER_THEME_CLASSIC_RGB         30
#define PAINTER_THEME_WHITE_SNOW          40

// ����ᮢ뢠�� ࠬ��.
#define PA_METHOD_CALLED_BY_WINDOW_MANAGER 1

// �������襥 ��ࠡ��뢠���� �᫮ ���� � ���� ࠬ��.
#define PAINTER_MAX_CONTROLS              50

// ��᫮ �஢�ப ࠧ��� � �ᯮ������� ���� ࠬ��.
#define MAX_FCHECKS                       5

// ��ꥤ������ ᮮ�饭��.
typedef struct _PAINTERDEMAND
{
  // ���� ࠬ��.
  HWND Frame_window;
  // ����, �ॡ��饥 ����ᮢ����.
  ULONG Target;
}
PAINTERDEMAND; typedef PAINTERDEMAND* PPAINTERDEMAND;

#define PAINTER_DEMAND_TABLE              256

// �⫮� �訡��, ��뢠�饩 "�������" ࠬ��.
typedef struct _MSGQUEUEINFO
{
  // ��।� ᮮ�饭��.
  HMQ Queue;
  // ���稪 ᮮ�饭��.
  INT Quantity;
  // �६� ��᫥����� 㢥��祭�� ���稪�.
  LONG Time;
}
MSGQUEUEINFO; typedef MSGQUEUEINFO* PMSGQUEUEINFO;

#define PAINTER_MONITORING_QUEUES         64
#define PAINTER_STUBBORN_PID_TABLE        16

// �᪫�祭��.
typedef struct _PAINTER_EXCEPTIONS
{
  CHAR Drawing_1[SIZE_OF_NAME];
  CHAR Drawing_2[SIZE_OF_NAME];
  CHAR Drawing_3[SIZE_OF_NAME];
  CHAR Drawing_4[SIZE_OF_NAME];
  CHAR Drawing_5[SIZE_OF_NAME];
  CHAR Drawing_6[SIZE_OF_NAME];
  CHAR Drawing_7[SIZE_OF_NAME];
  CHAR Drawing_8[SIZE_OF_NAME];

  CHAR BorderDrawing_1[SIZE_OF_NAME];
  CHAR BorderDrawing_2[SIZE_OF_NAME];
  CHAR BorderDrawing_3[SIZE_OF_NAME];
  CHAR BorderDrawing_4[SIZE_OF_NAME];
  CHAR BorderDrawing_5[SIZE_OF_NAME];
  CHAR BorderDrawing_6[SIZE_OF_NAME];
  CHAR BorderDrawing_7[SIZE_OF_NAME];
  CHAR BorderDrawing_8[SIZE_OF_NAME];

  CHAR Rolling_1[SIZE_OF_NAME];
  CHAR Rolling_2[SIZE_OF_NAME];
  CHAR Rolling_3[SIZE_OF_NAME];
  CHAR Rolling_4[SIZE_OF_NAME];
  CHAR Rolling_5[SIZE_OF_NAME];
  CHAR Rolling_6[SIZE_OF_NAME];
  CHAR Rolling_7[SIZE_OF_NAME];
  CHAR Rolling_8[SIZE_OF_NAME];
}
PAINTER_EXCEPTIONS;

// ��ᮢ���� ࠬ�� ��� ����.
typedef struct _PAINTER
{
  // ����ﭭ� ����稭�.
  typedef struct _CONSTANTS
  {
    // ���祭�� �६��� � ���稪� ��� ��।������ "�������" ࠬ�� �� �ᮢ����.
    INT Permanent_drawing;
    INT Drawing_check_timeout;
  }
  CONSTANTS; CONSTANTS Constants;

  // ����ன��.
  typedef struct _INRSTS
  {
    // �������� ࠬ�� ����? 0 - ���, 1 - ��.
    BYTE Draw_frames;
    // ���� ��� ࠬ��.
    INT Theme;
    // ��ᮢ��� ����� ࠬ��? 0 - ���, 1 - ��.
    BYTE Draw_normal_frames;
    // ��ᮢ��� ࠬ�� ��� ���� ����ﭭ��� ࠧ���? 0 - ���, 1 - ��.
    BYTE Draw_const_frames;
    // ��ᮢ��� ࠬ�� � 1 ���? 0 - ���, 1 - ��.
    BYTE Draw_point_frames;
    // ��ᮢ��� ࠬ�� ��� ���᪨� ����? 0 - ���, 1 - ��.
    BYTE Draw_flat_frames;
    // ��ᮢ��� ���⨭�� � �ࠢ�� ���孥� 㣫� ����? 0 - ���, 1 - ��.
    BYTE Draw_system_menus;
    // ��ᮢ��� ��������� ����? 0 - ���, 1 - ��.
    BYTE Draw_titles;
    // ���� ��� ⥪�� � ���������.
    ULONG AT_Text_color;          ULONG IT_Text_color;
    ULONG Northern_AT_Text_color; ULONG Northern_IT_Text_color;
    ULONG Western_AT_Text_color;  ULONG Western_IT_Text_color;
    ULONG Eastern_AT_Text_color;  ULONG Eastern_IT_Text_color;
    ULONG Southern_AT_Text_color; ULONG Southern_IT_Text_color;
    // ���� ��� ���������� ����������.
    ULONG AT_Background_color;          ULONG IT_Background_color;
    ULONG Northern_AT_Background_color; ULONG Northern_IT_Background_color;
    ULONG Western_AT_Background_color;  ULONG Western_IT_Background_color;
    ULONG Eastern_AT_Background_color;  ULONG Eastern_IT_Background_color;
    ULONG Southern_AT_Background_color; ULONG Southern_IT_Background_color;
    // ����ન���� ��ꥬ ��������� ��� ���� ����ﭭ��� ࠧ���? 0 - ���, 1 - ��.
    BYTE Draw_volume_lines;
    // ����ન���� ��ꥬ ���� ����? 0 - ���, 1 - ��.
    BYTE Draw_menus;
    // ��ᮢ��� ������ � �ࠢ�� ���孥� 㣫� ����? 0 - ���, 1 - ��.
    BYTE Draw_buttons;
    // ��⠢���� ��� ���� WPS ⮫쪮 ������ �������? 0 - ���, 1 - ��.
    BYTE Accelerate_folders_closing;
    // ��ᮢ��� ������ "����� ������" ��� ⥪�⮢�� ����? 0 - ���, 1 - ��.
    BYTE Rollup_VIO_windows;

    // ���� ��� ����ࠦ����.
    LONG AT_Color_1;          LONG AT_Color_2;          LONG AT_Color_3;
    LONG IT_Color_1;          LONG IT_Color_2;          LONG IT_Color_3;
    LONG Northern_AT_Color_1; LONG Northern_AT_Color_2; LONG Northern_AT_Color_3;
    LONG Northern_IT_Color_1; LONG Northern_IT_Color_2; LONG Northern_IT_Color_3;
    LONG Western_AT_Color_1;  LONG Western_AT_Color_2;  LONG Western_AT_Color_3;
    LONG Western_IT_Color_1;  LONG Western_IT_Color_2;  LONG Western_IT_Color_3;
    LONG Eastern_AT_Color_1;  LONG Eastern_AT_Color_2;  LONG Eastern_AT_Color_3;
    LONG Eastern_IT_Color_1;  LONG Eastern_IT_Color_2;  LONG Eastern_IT_Color_3;
    LONG Southern_AT_Color_1; LONG Southern_AT_Color_2; LONG Southern_AT_Color_3;
    LONG Southern_IT_Color_1; LONG Southern_IT_Color_2; LONG Southern_IT_Color_3;

    // ���� ��� ����ࠦ����.
    CHAR TitleBar_pattern[SIZE_OF_PATH];

    // �� ������ ��⥬�� 梥�? 0 - ���, 1 - ��.
    BYTE Keep_frame_colors;

    // ���᮪ �᪫�祭��.
    PAINTER_EXCEPTIONS Exceptions;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ����, � ���஬ ����� ������ � ���������.
    HWND Selected_window;
    // ����� ������ �����.
    LONG Selected_button;
    // ���� ���⨭��, �᫨ �� ��࠭�.
    HWND Prev_selected_menu;

    // ����ࠦ���� ��� ���������� ���������.
    HBITMAP AT_Bitmap; HBITMAP IT_Bitmap; INT AT_Bitmap_width; INT AT_Bitmap_height;

    // ���� ��� ���������, ����㦥��� � ��᪠.
    CHAR Pattern_name[SIZE_OF_NAME];
    HBITMAP Pattern; INT Pattern_width; INT Pattern_height;

    // ��ꥤ������ ᮮ�饭��.
    PAINTERDEMAND Demand[PAINTER_DEMAND_TABLE];

    // �⫮� �訡��, ����� ��뢠�� "�������" ࠬ��.
    MSGQUEUEINFO Drawing_windows[PAINTER_MONITORING_QUEUES];
    ULONG Stubborn_processes[PAINTER_STUBBORN_PID_TABLE];
  }
  RTSTS; RTSTS RTSettings;
}
PAINTER; PAINTER Painter;
