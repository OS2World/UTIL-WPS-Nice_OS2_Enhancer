// ���� ����஥�.
typedef struct _CLIENT_WINDOW
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG Buttons_brick_ID;

    ULONG Install_button_ID;
    ULONG Remove_button_ID;
    ULONG Cancel_button_ID;
   }
  INRSTS; INRSTS Settings;

  // ��ᯮ������� ����� �����.
  LTWALL Layout;
 }
CLIENT_WINDOW;

CLIENT_WINDOW Client_Window;
