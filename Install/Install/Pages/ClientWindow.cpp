
// ─── Метод для подключения класса ───

VOID ClientWindow_Start( VOID )
{
 #ifdef Client_Window
 bzero( &Client_Window, sizeof( Client_Window ) );
 #endif

 {
  // Задаем ID полей ввода.
  Client_Window.Settings.Buttons_brick_ID  = 1001;

  Client_Window.Settings.Install_button_ID = 1002;
  Client_Window.Settings.Remove_button_ID  = 1003;
  Client_Window.Settings.Cancel_button_ID  = 1004;
 }

 // Возврат.
 return;
}

