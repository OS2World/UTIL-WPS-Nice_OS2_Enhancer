// ������ ᯨ᪠ ���� ��� ��।������� ����ࠦ����. ������ �� ���祭�� ������⥫쭮.
#define SCROLLER_SCRLIST_SIZE             125

// ����� ����� ��� ��墠� ����ࠦ���� � ����.
#define SCROLLER_SCRLIST_LINE             150

// ��������� �����ন������ ᪮����.
#define SCROLLER_MAX_VELOCITY_DD_D        ( 50 / 1 )

// �ᯮ��㥬� ������.
#define SCROLLER_USE_CAPS_LOCK            1
#define SCROLLER_USE_SCROLL_LOCK          2
#define SCROLLER_USE_SHIFT                3

// ���ᮡ� �������� ��।������� ����ࠦ���� � ���� (�� 㬮�砭�� �㫥��� ���祭��).
#define SCROLLING_UNKNOWN                 0
#define SCROLLING_DISABLED                0
#define SCROLLING_COMMON                  1
#define SCROLLING_DISCRETE_SBCTL_MB       2
#define SCROLLING_DISCRETE_SBCTL_KBD      3
#define SCROLLING_DISCRETE_SCROLLMSG      4
#define SCROLLING_DISCRETE_SCROLLMSG_IFW  5

// ������� �� 㬮�砭��.
#define SCROLLER_DEF_SPEED_X              8
#define SCROLLER_DEF_SPEED_Y              16

// ���᮪ ����, � ������ �ந�室�� ��।������� ����ࠦ����.
typedef struct _SCRLIST
 {
  // ���, ��� ����� ��।����� ����.
  CHAR Name[ SIZE_OF_NAME ];
  // ������� ��।������� ����ࠦ����.
  INT X_Velocity_DD; INT X_Velocity_D;
  INT Y_Velocity_DD; INT Y_Velocity_D;
  // ����� ��������� ����⥫��.
  BYTE PreDefined; BYTE Method;
 }
SCRLIST; typedef SCRLIST* PSCRLIST;

// �᪫�祭��.
typedef struct _SCROLLER_EXCEPTIONS
 {
  // ���᮪ �᪫�祭��, ������� ���짮��⥫��.
  CHAR Scrolling_1[ SIZE_OF_NAME ];
  CHAR Scrolling_2[ SIZE_OF_NAME ];
  CHAR Scrolling_3[ SIZE_OF_NAME ];
  CHAR Scrolling_4[ SIZE_OF_NAME ];
  CHAR Scrolling_5[ SIZE_OF_NAME ];
  CHAR Scrolling_6[ SIZE_OF_NAME ];
  CHAR Scrolling_7[ SIZE_OF_NAME ];
  CHAR Scrolling_8[ SIZE_OF_NAME ];

  CHAR KeyScrolling_1[ SIZE_OF_NAME ];
  CHAR KeyScrolling_2[ SIZE_OF_NAME ];
  CHAR KeyScrolling_3[ SIZE_OF_NAME ];
  CHAR KeyScrolling_4[ SIZE_OF_NAME ];
  CHAR KeyScrolling_5[ SIZE_OF_NAME ];
  CHAR KeyScrolling_6[ SIZE_OF_NAME ];
  CHAR KeyScrolling_7[ SIZE_OF_NAME ];
  CHAR KeyScrolling_8[ SIZE_OF_NAME ];
 }
SCROLLER_EXCEPTIONS;

// ��।������� ����ࠦ���� � �����.
typedef struct _SCROLLER
 {
  // ���᮪ ���� ����, � ������ ����� ������� ����ࠦ����.
  SCRLIST Scrolling_list[ SCROLLER_SCRLIST_SIZE ];

  // ����ன��.
  typedef struct _INRSTS
   {
    // �������� ����ࠦ���� � ����� �� ����⮬ Scroll Lock? 0 - ���, 1 - ��.
    BYTE Key_scrolling;
    // ������� ��।������� ����ࠦ���� �� ��ᬮ�� ������? 0 - ���, 1 - ��.
    BYTE Smooth_scrolling;
    // �������� ����ࠦ���� � ����� � ������� ���? 0 - ���, 1..3 - �᫨ ����� �ࠢ�� ������.
    BYTE Image_dragging;
    // �����⥫� ���, �ᯮ��㥬� ��� ��।������� ����ࠦ����.
    INT Number_of_pointer;

    // ���᮪ �᪫�祭��.
    SCROLLER_EXCEPTIONS Exceptions;
   }
  INRSTS; INRSTS Settings;

  typedef struct _RTSTS
   {
    // ����뢠��, �� ᪮���� ��।������� ����ࠦ���� ���������� �� ����.
    BYTE Detection_is_disabled;
    // �᫨ 1 ��� 2, � ��।������� ⮫쪮 ��稭�����, �᫨ 3 ��� 4 - �த��������.
    BYTE Step_of_scrolling;
    // ���� ��।������� ����ࠦ����. 0 - ���, 1 - ��.
    BYTE Dragging;
    // ����᪨ ��ᬮ�� � ����.
    HWND VSB_Control; HWND HSB_Control;
    // ��窠, � ���ன ��稭����� ��।�������.
    POINT Start_point; 
    // ��ᯮ������� ������� ����᮪ ��ᬮ�� � �⮩ �窥.
    USHORT Start_VSB_position; USHORT Start_HSB_position;
    // ��窠, � ���ன 㪠��⥫� �� � ���� ࠧ.
    POINT Previous_step_point;
    // ������� ��।�������.
    INT X_Velocity_DD; INT X_Velocity_D;
    INT Y_Velocity_DD; INT Y_Velocity_D;
    // ��࠭�� ᯮᮡ ��।�������.
    INT Dragging_method;
    // ��࠭��� ����.
    HWND Target_window;

    // ��६����, �⮡� ���������� �窨 � ���� ��� '>', � ��⥬ �᪠�� �� � ��।����� ᪮����.
    HWND Scrolling_window; 
    BYTE Messages_is_redirected; 
    INT ScrList_position;
    SHORT Slider_position;

    LONG Line_1[ SCROLLER_SCRLIST_LINE ]; 
    LONG Line_2[ SCROLLER_SCRLIST_LINE ];

    // ��६���� ��� �࠭���� ���ﭨ� ����᪨ ��ᬮ��.
    SBCDATA SB_State; SBCDATA VSB_State; SBCDATA HSB_State;
   }
  RTSTS; RTSTS RTSettings;
 }
SCROLLER; typedef SCROLLER* PSCROLLER;

// ��६���� ������ ���� �ᯮ������ � ࠧ���塞�� ������ �����.
SCROLLER Scroller;
