
// ��� ��⮤ ��� ������祭�� ����� ���

VOID ClientWindow_Start( VOID )
{
 #ifdef Client_Window
 bzero( &Client_Window, sizeof( Client_Window ) );
 #endif

 {
  // ������ ID ����� �����.
  Client_Window.Settings.List_ID = 1001;
  Client_Window.Settings.Text_ID = 1002;
 }

 // ������.
 return;
}

