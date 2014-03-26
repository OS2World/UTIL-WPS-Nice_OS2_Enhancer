
// ─── Метод для подключения класса ───

VOID ClientWindow_Start( VOID )
{
 #ifdef Client_Window
 bzero( &Client_Window, sizeof( Client_Window ) );
 #endif

 {
  // Задаем ID полей ввода.
  Client_Window.Settings.List_ID = 1001;
  Client_Window.Settings.Text_ID = 1002;
 }

 // Возврат.
 return;
}

