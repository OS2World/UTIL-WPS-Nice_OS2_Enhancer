// ���� ����஥�.
typedef struct _MOUSEVIOPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Mouse_button_ID;
    ULONG Mouse_Shift_button_ID;
    ULONG Mouse_Remember_button_ID;
   }
  INRSTS; INRSTS Settings;
 }
MOUSEVIOPAGE;

MOUSEVIOPAGE Mouse_VIO;
