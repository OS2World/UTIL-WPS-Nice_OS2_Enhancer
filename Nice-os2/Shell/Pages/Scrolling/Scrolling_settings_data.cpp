// ���� ����஥�.
typedef struct _SCRSTNGSSPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG Mouse_pointer_cmbox_ID;
    ULONG Mouse_pointer_button_ID;

    ULONG Mouse_scrolling_cmbox_ID;
    ULONG Mouse_scrolling_button_ID;

    ULONG Keyboard_scrolling_button_ID;
    ULONG Smooth_scrolling_button_ID;
  }
  INRSTS; INRSTS Settings;
}
SCRSTNGSSPAGE;

SCRSTNGSSPAGE Scrolling_Settings;