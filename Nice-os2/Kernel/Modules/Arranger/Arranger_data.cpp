// ����প� �� ��ࠢ������� ⥪�⮢�� ����.
#define ARRANGER_DELAY_VIO        7500

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
   }
  INRSTS; INRSTS Settings;
 }
ARRANGER;

ARRANGER Arranger;