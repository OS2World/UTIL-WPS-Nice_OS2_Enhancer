// ���� ����஥�.
typedef struct _DRWBTNSPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG Buttons_WPS_ID;
    ULONG Buttons_VIO_ID;

    ULONG RollUp_Container_ID;
    ULONG RollUp_List_ID;
    ULONG RollUp_Add_ID;
    ULONG RollUp_Remove_ID;
  }
  INRSTS; INRSTS Settings;
}
DRWBTNSPAGE;

DRWBTNSPAGE Drawing_Buttons;
