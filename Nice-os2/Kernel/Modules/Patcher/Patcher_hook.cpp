
// ─── Проверяет, нажата ли кнопка мыши на значке списка окон в WarpCenter ───

// Message - сообщение, которое передается окну.
BYTE Patcher_WinListMenuIsPressed( PQMSG Message )
{
 // Узнаем размеры окна.
 RECT Rectangle = {0}; WinQueryWindowRect( Message->hwnd, &Rectangle );

 // Задаем расположение значка для списка окон.
 INT X_Left = 0; INT X_Right = 0;
 if( Rectangle.yTop == Patcher.Constants.Big_WarpCenter ) { X_Left = Patcher.Constants.Big_WarpCenter_X1; X_Right = Patcher.Constants.Big_WarpCenter_X2; }
 else { X_Left = Patcher.Constants.Small_WarpCenter_X1; X_Right = Patcher.Constants.Small_WarpCenter_X2; }

 // Если кнопка мыши отжата на значке списка окон - возвращаем 1.
 POINT Mouse_point = { SHORT1FROMMP( Message->mp1 ), SHORT2FROMMP( Message->mp1 ) };
 if( Mouse_point.x >= X_Left && Mouse_point.x <= X_Right ) return 1;

 // Возврат.
 return 0;
}

// ─── Устанавливает заставку при открытии только для окон WPS ───

// Window - окно, которое надо проверить.
VOID Patcher_ChangeAnimation( HWND Window )
{
 // Узнаем свойства окна.
 ULONG Window_style = WinQueryWindowULong( Window, QWL_STYLE );

 // Если заставка отключена - возврат.
 if( !( Window_style & WS_ANIMATE ) ) return;

 // Проверяем окно - это должно быть окно рамки или окно WPS.
 BYTE Window_is_frame = 0;  if( IsFrameWindow( Window ) ) Window_is_frame = 1;
 BYTE Window_is_folder = 0; if( IsFolderWindow( Window ) ) Window_is_folder = 1;

 // Если это не окно рамки - возврат.
 if( !Window_is_frame ) if( !Window_is_folder ) return;

 // Родительское окно должно быть окном рабочего стола.
 if( WinQueryWindow( Window, QW_PARENT ) != QueryDesktopWindow() ) return;

 // Для некоторых окон заставку при открытии отключать не надо.
 if( Window_is_frame )
  {
   if( IsJobCnrWindow( Window ) ) Window_is_folder = 1;
  }

 // Если это не окно WPS и заставка должна быть показана - отключаем ее.
 if( !Window_is_folder ) if( Window_style & WS_ANIMATE )
  {
   // Отключаем заставку.
   Window_style = Window_style & ~WS_ANIMATE;

   // Устанавливаем свойства рамки окна.
   WinSetWindowULong( Window, QWL_STYLE, Window_style );
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PatcherInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Восстанавливаем окна перед закрытием.
 if( Patcher.Settings.Restore_windows_before_closing )
  {
   // Если окно закрывается:
   if( FrameWindowIsClosing( Message ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если это не окно диалога и в него можно переключиться из списка окон:
     if( !WindowIsAppDialog( Frame_window ) ) if( WindowIsTouchable( Frame_window ) )
      {
       // Если родительское окно - рабочий стол:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // Узнаем расположение окна и его состояние.
         SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

         // Смотрим, надо ли показывать окно.
         BYTE Restore_window = 0;

         // Если окно уменьшено в значок - надо восстановить его.
         if( Window_state.fl & SWP_MINIMIZE ) Restore_window = 1;

         // Если окно скрыто и это первое сообщение о закрытии - надо восстановить его.
         if( Window_state.fl & SWP_HIDE )
          {
           // Проверяем состояние окна.
           BYTE Close_message_is_received = 0; FindProperty( Frame_window, PRP_CLOSE_RECEIVED, &Close_message_is_received );
           if( !Close_message_is_received ) Restore_window = 1;
          }

         // Если надо восстановить окно:
         if( Restore_window )
          {
           // Делаем окно видимым.
           WinShowWindow( Frame_window, 1 );

           // Направляем в окно сообщение о том, что оно должно быть восстановлено.
           WinSendMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_RESTORE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
          }

         // Запоминаем, что окно получает сообщение о закрытии.
         BYTE Close_message_is_received = 1; SetProperty( Frame_window, PRP_CLOSE_RECEIVED, &Close_message_is_received );
        }
      }
    }
  }


 // Вызываем в WarpCenter обычный список окон.
 if( Patcher.Settings.Patch_WarpCenter )
  {
   // Если кнопка мыши нажата на WarpCenter - запоминаем это.
   if( Message->msg == WM_BUTTON1DOWN )
    if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
     Patcher.RTSettings.WinListMenu_is_pressed = 1;

   // Если указатель мыши перемещен в другое окно - WarpCenter не нажат.
   if( Patcher.RTSettings.WinListMenu_is_pressed )
    if( Message->msg >= WM_MOUSEFIRST && Message->msg <= WM_MOUSELAST )
     if( !IsWarpCenterWindow( Message->hwnd ) ) Patcher.RTSettings.WinListMenu_is_pressed = 0;

   // Если кнопка мыши отжата на WarpCenter:
   if( Patcher.RTSettings.WinListMenu_is_pressed )
    if( Message->msg == WM_BUTTON1UP )
     if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
      {
       // WarpCenter не нажат.
       Patcher.RTSettings.WinListMenu_is_pressed = 0;

       // Выполняем действие. Посылаем сообщение в поток.
       WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_SHOW_WINDOW_LIST, 0, 0 );

       // Изменяем сообщение так, как будто кнопка мыши отжата в другой точке.
       Message->mp1 = MPFROM2SHORT( -1, -1 );
      }

   // Если выполнено двойное нажатие - сброс сообщения.
   if( Message->msg == WM_BUTTON1DBLCLK )
    if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
     *Discarding = 1;
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID PatcherSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Устанавливаем заставки при открытии только для окон WPS.
 // Для этого надо обрабатывать два сообщения, и только таким образом.
 if( Patcher.Settings.Limited_animation )
  if( Message->msg == WM_MOVE ||
    ( Message->msg == WM_ACTIVATE && Message->mp1 == (MPARAM) 1 ) )
   {
    // Отключаем заставку.
    Patcher_ChangeAnimation( Message->hwnd );
   }

 // Возврат.
 return;
}
