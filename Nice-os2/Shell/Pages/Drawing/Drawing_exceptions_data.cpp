// ���� ����஥�.
typedef struct _DRWXCPTNSPAGE
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Container_BorderDraw_ID;
    ULONG List_BorderDraw_ID;
    ULONG Add_button_BorderDraw_ID;
    ULONG Remove_button_BorderDraw_ID;

    ULONG Container_Disable_ID;
    ULONG List_Disable_ID;
    ULONG Add_button_Disable_ID;
    ULONG Remove_button_Disable_ID;
   }
  INRSTS; INRSTS Settings;
 }
DRWXCPTNSPAGE;

DRWXCPTNSPAGE Drawing_Exceptions;
