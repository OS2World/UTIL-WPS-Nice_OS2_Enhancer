// ���� ����஥�.
typedef struct _SPTSTSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG ScreenSaver_button_ID;
    ULONG Animation_button_ID;
    ULONG WarpCenter_button_ID;
    ULONG RestoreWnd_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
SPTSTSPAGE;

SPTSTSPAGE SysPatches_Settings;
