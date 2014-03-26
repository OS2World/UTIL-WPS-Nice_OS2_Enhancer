
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Installer_ClientWindowProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 switch( Message )
  {
   // Выполняем действия при создании окна.
   case WM_CREATE:
    {
     WinPostMsg( Window, MY_CREATE, 0, 0 );
    }
   return 0;

   case MY_CREATE:
    {
     // Задаем заголовок окна приложения.
     if( Installer.Code_page == RUSSIAN ) strcpy( Installer.Frame_window_title, StrConst_RU_Title );
     else strcpy( Installer.Frame_window_title, StrConst_EN_Title );

     WinSetWindowText( Installer.Frame_window, Installer.Frame_window_title );

     // Устанавливаем картинку в левом верхнем углу окна.
     WinSendMsg( Installer.Frame_window, WM_SETICON, (MPARAM) WinLoadPointer( HWND_DESKTOP, NULLHANDLE, 1 ), 0 );

     // Задаем расположение окна.
     {
      INT X_Screen = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
      INT Y_Screen = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

      INT Window_width  = X_Screen / 3; if( X_Screen < 1024 ) Window_width  *= 1.25;
      INT Window_height = Y_Screen / 3; if( X_Screen < 1024 ) Window_height *= 1.25;

      INT Window_position_X = ( X_Screen - Window_width ) / 2;
      INT Window_position_Y = ( Y_Screen - Window_height ) / 2 + ( Y_Screen - Window_height ) / 4 / 2;

      WinSetWindowPos( Installer.Frame_window, HWND_TOP, Window_position_X, Window_position_Y, Window_width, Window_height, SWP_ZORDER | SWP_MOVE | SWP_SIZE | SWP_NOADJUST );
      WinSetActiveWindow( HWND_DESKTOP, Installer.Frame_window );
     }

     // Добавляем его в список окон.
     {
      SWCNTRL Task; HSWITCH Switch_handle = NULLHANDLE;

      bzero( &Task, sizeof( SWCNTRL ) );
      Task.hwnd = Installer.Frame_window;
      Task.hwndIcon = (HPOINTER) WinSendMsg( Installer.Frame_window, WM_QUERYICON, 0, 0 );
      WinQueryWindowProcess( Installer.Frame_window, &Task.idProcess, NULL );
      strcpy( Task.szSwtitle, Installer.Frame_window_title );

      Task.uchVisibility = SWL_VISIBLE;
      Task.fbJump = SWL_JUMPABLE;

      Switch_handle = WinCreateSwitchEntry( Installer.Application, &Task );
      WinChangeSwitchEntry( Switch_handle, &Task );
     }

     // Создаем поля ввода в окне рабочей области.
     ClientWindow_CreatePage( Installer.Client_window );
    }
   return 0;

   // Передвигаем поля ввода.
   case MY_APPLY_LAYOUT:
    {
     LitApplyLayout( &Client_Window.Layout );
    }
   return 0;

   // Включаем и отключаем поля ввода.
   case MY_ENABLE_BUTTONS:
    {
     ULONG Action = (ULONG) First_parameter;

     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, Client_Window.Settings.Buttons_brick_ID ), Client_Window.Settings.Install_button_ID ), Action );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, Client_Window.Settings.Buttons_brick_ID ), Client_Window.Settings.Remove_button_ID ), Action );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, Client_Window.Settings.Buttons_brick_ID ), Client_Window.Settings.Cancel_button_ID ), Action );

     if( !Action )
      WinSendMsg( WinWindowFromID( Installer.Frame_window, FID_SYSMENU ), MM_SETITEMATTR, MPFROM2SHORT( SC_CLOSE, INCLUDE_SUBMENUS ), MPFROM2SHORT( MIA_DISABLED, MIA_DISABLED ) );
     else
      WinSendMsg( WinWindowFromID( Installer.Frame_window, FID_SYSMENU ), MM_SETITEMATTR, MPFROM2SHORT( SC_CLOSE, INCLUDE_SUBMENUS ), MPFROM2SHORT( MIA_DISABLED, 0 ) );
    }
   return 0;

   // Обрабатываем нажатия на кнопки.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == Client_Window.Settings.Install_button_ID )
      {
       StartInstallerThread( NIA_INSTALL );
      }

     if( WM_Control_Button_ID == Client_Window.Settings.Remove_button_ID )
      {
       StartInstallerThread( NIA_REMOVE );
      }

     if( WM_Control_Button_ID == Client_Window.Settings.Cancel_button_ID )
      {
       WinPostMsg( Installer.Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, 0 );
      }
    }
   return 0;

   // Закрашиваем пространство окна.
   case WM_PAINT:
    {
     RECT Rectangle = {0};
     HPS Presentation_space = WinBeginPaint( Window, 0, &Rectangle );

     if( Presentation_space )
      {
       LONG Color_table[ 2^8 ]; bzero( Color_table, sizeof( Color_table ) );
       GpiQueryLogColorTable( Presentation_space, 0, 0, 2^8, Color_table );

       LONG Color_index = ( 2^8 - 1 );
       WinQueryPresParam( Window, PP_BACKGROUNDCOLOR, 0, NULL, sizeof( Color_table[ Color_index ] ), &Color_table[ Color_index ], QPF_NOINHERIT );
       GpiCreateLogColorTable( Presentation_space, 0, LCOLF_CONSECRGB, 0, 2^8, Color_table );

       WinFillRect( Presentation_space, &Rectangle, Color_index );
       WinEndPaint( Presentation_space );
      }
    }
   return 0;

   // Сообщаем окну рамки, что содержимое окна рабочей области закрашивать не следует.
   case WM_ERASEBACKGROUND:
   return (MPARAM) 0;

   // Выполняем действия при нажатии на кнопку закрытия окна.
   case WM_CLOSE:
    {
     // Убираем окно приложения из списка окон.
     WinRemoveSwitchEntry( WinQuerySwitchHandle( Installer.Frame_window, 0 ) );

     // Передаем сообщение обработчику.
     WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
    }
   return 0;
  }

 // Возврат.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}
