// ��⮤ ��� �맮�� ��।���⥫�.
#define OpenDETECTOR Detector_OpenDETECTOR

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Detector_Start (VOID)
{
  #ifdef Detector_Form
  bzero (&Detector_Form, sizeof (Detector_Form));
  #endif

  // ������ ����ﭭ� ����稭�.
  Detector_Form.Constants.Delay_time_ms = 500;

  // ������.
  return;
}

