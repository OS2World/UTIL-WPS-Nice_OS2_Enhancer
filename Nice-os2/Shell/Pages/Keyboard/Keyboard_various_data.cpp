// ���� ����஥�.
typedef struct _KBDVRSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Keep_NumLock;
    ULONG NumLock_cbox;
    ULONG NumKeys;

    ULONG Ctrl_CV;
    ULONG WPS_Enter;
    ULONG CUA_F3;

    // ����७��� ��६����.
    ULONG Turn_Num_Lock;
   }
  INRSTS; INRSTS Settings;
 }
KBDVRSPAGE;

KBDVRSPAGE Keyboard_Various;
