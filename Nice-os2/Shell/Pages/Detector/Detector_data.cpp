// ���� ��।���⥫�.
typedef struct _DETECTORFORM
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ����७��� ��६����.
    HWND Detected_window;
  }
  INRSTS; INRSTS Settings;

  // ����ﭭ� ����稭�.
  typedef struct _CONSTANTS
  {
    // ����প� ���稪� �६���.
    INT Delay_time_ms;
  }
  CONSTANTS; CONSTANTS Constants;
}
DETECTORFORM;

DETECTORFORM Detector_Form;
