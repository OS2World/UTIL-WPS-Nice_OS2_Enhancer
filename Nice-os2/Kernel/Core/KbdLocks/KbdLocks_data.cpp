// ��ࠢ����� ��४���⥫ﬨ �� ���������.
typedef struct _KBDLOCKS
 {
  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ����ﭨ� Ctrl + Alt + Del.
    BYTE Ctrl_Alt_Del_is_disabled;
   }
  RTSTS; RTSTS RTSettings;
 }
KBDLOCKS;

KBDLOCKS KbdLocks;