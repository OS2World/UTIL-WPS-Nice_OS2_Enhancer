// ���� ����஥�.
typedef struct _KBDSPEEDPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG Reset_Shift_button_ID;

    ULONG SpeedUp_button_ID;
    ULONG Rate_cbox_ID;
  }
  INRSTS; INRSTS Settings;
}
KBDSPEEDPAGE;

KBDSPEEDPAGE Keyboard_Speed;
