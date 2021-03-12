// ����প� �� ��ࠢ������� ⥪�⮢�� ����.
#define ARRANGER_DELAY_VIO        12500

// ��ࠢ������� ����.
typedef struct _ARRANGER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ��ࠢ������ ⥪�⮢� ����? 0 - ���, 1 - ��.
    BYTE Arrange_VIO_windows; BYTE Arrange_FC2_windows;
    // ��ࠢ������ ᯨ᮪ ����? 0 - ���, 1 - ��.
    BYTE Arrange_WindowList;
    // ��ࠢ������ ���� WPS? 0 - ���, 1 - ��.
    BYTE Arrange_WPS_windows;
    // ��ࠢ������ ���� ��㧥஢? 0 - ���, 1 - ��.
    BYTE Arrange_Browser_windows;
    // ��ࠢ������ ���� �⥢�� ᮥ����⥫��? 0 - ���, 1 - ��.
    BYTE Arrange_Network_windows;
    // ��ࠢ������ ���� XWorkplace? 0 - ���, 1 - ��.
    BYTE Arrange_XWP_windows;
  }
  INRSTS; INRSTS Settings;
}
ARRANGER;

ARRANGER Arranger;