// ���� ����஥�.
typedef struct _CLIENT_WINDOW
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ���� ����� � ����.
    ULONG List_ID;
    ULONG Text_ID;
   }
  INRSTS; INRSTS Settings;

  // ��ᯮ������� ����� �����.
  LTWALL Layout;
 }
CLIENT_WINDOW;

CLIENT_WINDOW Client_Window;
