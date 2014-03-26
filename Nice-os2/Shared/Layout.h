// ���祭�� ��� ������� ࠧ��஢ ����.
#define LTM_X                0
#define LTM_Y                0
#define LTM_CX               0
#define LTM_CY               0

#define LTM_FULL_WIDTH       1.00
#define LTM_FULL_HEIGHT      1.00
#define LTM_VSPLIT_WIDTH     0.50
#define LTM_HSPLIT_HEIGHT    0.50

#define LTM_COMMON_WIDTH     ( LTM_FULL_WIDTH )
#define LTM_COMMON_HEIGHT    ( (ULONG) ( WinQuerySysValue( HWND_DESKTOP, SV_CYMENU ) >= 22 ) ? \
                                       ( WinQuerySysValue( HWND_DESKTOP, SV_CYMENU ) ) : 22 )
#define LTM_BUTTON_WIDTH     ( LTM_FULL_WIDTH  )
#define LTM_BUTTON_HEIGHT    ( (ULONG) ( LTM_COMMON_HEIGHT * 1.33333 ) )
#define LTM_COMBOBOX_WIDTH   ( LTM_FULL_WIDTH  )
#define LTM_COMBOBOX_HEIGHT  ( LTM_COMMON_HEIGHT )
#define LTM_COMBOBOX_LIST    ( (ULONG) ( LTM_COMMON_HEIGHT * 5 ) )

#define LTM_TOP_FRAME_WIDTH  0.75
#define LTM_TOP_FRAME_HEIGHT 0.75
#define LTM_TOP_FRAME_MARGIN 0.01

// ��אַ㣮�쭨� ��� ���� �����.
typedef struct _LTBRICK
 {
  // ������ ��������.
  ULONG cb;
  // ����, ᮧ�������� ��࠭��.
  HWND hwnd;

  // ������ ���� � �窠� ��� � %% �� ࠧ��� த�⥫�᪮�� ����.
  // �������� � ��⮬ ⮣�, �� Layout �� ४��ᨢ��, � ࠧ����
  // ���� ����� �⮣� ���� ���뢠���� �� ���� - ��� ���� 
  // �ᯮ������ ⮫쪮 ࠧ��� த�⥫�᪮�� ����.
  FLOAT prpWidthInParent;
  FLOAT prpHeightInParent;

  // ����� �� �ࠥ�, �᫨ ����� ���� �� ��㣨� ����.
  FLOAT prpMargin;
  // �����ﭨ� ����� ���ﬨ �����, �᫨ ��� ���� ����� ����.
  FLOAT prpGap;

  // ������� ���� ����, �᫨ ��� ���筮 ��४�뢠���� ��㣨�� ������ �
  // ������ ���� ����� ⮫쪮 ��� ������ ���� (⠪��� ���� "WC_COMBOBOX").
  // �� ���祭�� �������� ⮫쪮 � �窠� (�ॡ������ Presentation Manager).
  ULONG ulBoxHeight;
 }
LTBRICK; typedef LTBRICK* PLTBRICK;

// ���᮪ ��אַ㣮�쭨��� ��� ����� �����.
// ����� ���祭�� �����頥��� ��᫥ ᮧ����� ᯨ᪠.
typedef struct _LTWALL
 {
  // ����, ��� ���ண� ᮧ������ ᯨ᮪.
  HWND hwnd;

  // �����⥫� �� ᯨ᮪ ��אַ㣮�쭨��� � ����� �����.
  LTBRICK* pList;

  // ����� ᯨ᪠ � �᫮ ����� ����� � ���.
  ULONG ulLength; ULONG ulQuantity;
 }
LTWALL; typedef LTWALL* PLTWALL;
