// ���� � ᮮ�饭�ﬨ �� �訡���.
typedef struct _LOGPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ��� ᮮ�饭��.
    LONG Field_ID;
   }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ���� ����� ��������.
    BYTE Field_is_changed;
   }
  RTSETTINGS; RTSETTINGS RTSettings;
 }
LOGPAGE;

LOGPAGE Log;