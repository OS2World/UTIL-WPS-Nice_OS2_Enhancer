
// ─── Скрывает окно приложения, если оно соответствует действию ───

BYTE Launcher_CheckActiveWindowAndHideApplication( INT Action )
{
 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Узнаем окно, которое сейчас выбрано.
 HWND Active_window = WinQueryActiveWindow( Desktop );

 // Если это окно рамки и оно видимо:
 if( Active_window != NULLHANDLE )
  if( IsFrameWindow( Active_window ) )
   if( WinIsWindowVisible( Active_window ) )
    {
     // Если это и есть то окно, которое надо найти:
     if( CommandForWindowIs( Action, Active_window ) )
      {
       // Скрываем его и возвращаем ненулевое значение.
       if( HideWindowAway( Active_window ) ) return 1;
      }
    }

 // Возврат.
 return 0;
}

// ─── Вызывает окно приложения, которое соответствует действию ───

// Action - действие, которое надо выполнить.
BYTE Launcher_FindAndShowApplication( INT Action )
{
 // Находим в списке приложения, способные откликнуться на эту команду, и пробуем вызвать их.
 INT Position = 0;

 while( 1 )
  {
   // Пробуем найти первое или следующее приложение.
   Position = FindApplicationInRepository( 0, Action, Position + 1 );

   // Если ничего не найдено - возврат.
   if( Position == -1 ) return 0;

   // Пробуем вызвать окно этого приложения или окно, способное откликнуться на такую же команду.
   BYTE Success = 0; INT How_much_found = 0; HWND Window_with_menu = NULLHANDLE;

   // Перебираем окна в окне рабочего стола.
   HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Если это не окно рамки - продолжаем перебор.
     if( !IsFrameWindow( Window ) ) continue;

     // Если окно не присутствует в списке окон - продолжаем перебор.
     // Эта проверка необходима, так как сетевые обозреватели Mozilla и
     // Opera создают такие окна, и даже зачем-то Switch_handle для них.
     if( !WindowIsTouchable( Window ) )
      if( !WindowIsUsedTo( DO_IMPROVE_WORKPLACE, Window ) )
       continue;

     // Смотрим, соответствует ли окно заданным условиям.
     BYTE Show_window = 0;

     // Если окно может откликнуться на заданную команду - надо вызвать его.
     if( CommandForWindowIs( Action, Window ) ) Show_window = 1;

     // Если окно создано этим приложением - надо вызвать его.
     if( WindowIsCreatedBy( Repository.Items[ Position ].Application, Window ) ) Show_window = 1;

     // Если для приложения были заданы ключевые слова и они есть в заголовке окна - тоже.
     if( Repository.Items[ Position ].Window_keyword_1[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_2[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_3[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_4[ 0 ] != 0 )
      {
       // Узнаем заголовок окна или выбираем его из списка свойств.
       CHAR Title[ SIZE_OF_TITLE ] = ""; GetDetectedWindowTitle( Window, Title );

       // Проверяем его.
       if( Repository.Items[ Position ].Window_keyword_1[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_1, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_2[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_2, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_3[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_3, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_4[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_4, Title ) )
         Show_window = 1;
      }

     // Если это окно, которое надо вызвать:
     if( Show_window )
      {
       // Устанавливаем приложению хороший приоритет.
       SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS, Window );

       // Узнаем состояние окна рамки.
       SWP Window_state = {0}; WinQueryWindowPos( Window, &Window_state );

       // Если окно уменьшено или скрыто - восстанавливаем его.
       if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE )
        {
         // Узнаем, было ли окно увеличено.
         BYTE Maximized = 0; FindProperty( Window, PRP_MAXIMIZED, &Maximized );

         // Посылаем сообщение в окно.
         if( !Maximized ) PerformAction( Window, RESTORE_ACTION );
         else PerformAction( Window, MAXIMIZE_ACTION );
        }

       // Если окно было убрано наверх - восстанавливаем его.
       if( Window == RolledWindow() ) UnrollWindow( RolledWindow() );

       // Вызываем окно и делаем его выбранным.
       MoveWindowAbove( Window );

       // Если у окна есть заголовок, меню и рабочая область - запоминаем его.
       if( WinWindowFromID( Window, FID_TITLEBAR ) != NULLHANDLE )
        if( WinWindowFromID( Window, FID_MENU ) != NULLHANDLE )
         if( WinWindowFromID( Window, FID_CLIENT ) != NULLHANDLE )
          Window_with_menu = Window;

       // Запоминаем, что окно вызвано. Окон может быть несколько, поэтому продолжаем перебор.
       Success = 1; How_much_found ++;
      }
    }
   WinEndEnumWindows( Enumeration );

   // Если было найдено несколько окон - вызываем наверх последнее из них, у которого есть меню.
   if( Success && How_much_found > 1 && Window_with_menu != NULLHANDLE )
    if( !WindowIsActive( Window_with_menu ) ) MoveWindowAbove( Window_with_menu );

   // Если окно или несколько окон были вызваны - возврат.
   if( Success ) return 1;

   // Если используется оболочка WPS:
   if( ShellIsWPS() )
    {
     // Пробуем вызвать значок на рабочем столе, если он был задан заранее.
     for( INT Count = 0; Count < 4; Count ++ )
      {
       // Узнаем значок на рабочем столе.
       PCHAR Object_name = NULL;

       if( Count == 0 ) Object_name = Repository.Items[ Position ].WPS_name_1;
       if( Count == 1 ) Object_name = Repository.Items[ Position ].WPS_name_2;
       if( Count == 2 ) Object_name = Repository.Items[ Position ].WPS_name_3;
       if( Count == 3 ) Object_name = Repository.Items[ Position ].WPS_name_4;

       // Если значок есть - вызываем его.
       if( Object_name[ 0 ] != 0 )
        {
         HOBJECT Object = QueryWPSObject( Object_name );

         if( Object != NULLHANDLE ) Success = WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
        }

       // Если значок был вызван - возврат.
       if( Success ) return 1;
      }

     // Пробуем вызвать значок на рабочем столе, если он был найден и занесен в список.
     if( Repository.Items[ Position ].Object[ 0 ] != 0 )
      {
       // Вызываем значок.
       HOBJECT Object = QueryWPSObject( Repository.Items[ Position ].Object );

       if( Object != NULLHANDLE ) Success = WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );

       // Если значок был вызван - возврат.
       if( Success ) return 1;
      }
    }

   // Если известен путь:
   if( Repository.Items[ Position ].Path[ 0 ] != 0 )
    {
     // Пробуем вызвать приложение.
     for( INT Count = 0; Count < 4; Count ++ )
      {
       // Узнаем путь к приложению.
       PCHAR Exe_name = NULL;

       if( Count == 0 ) Exe_name = Repository.Items[ Position ].Exe_name_1;
       if( Count == 1 ) Exe_name = Repository.Items[ Position ].Exe_name_2;
       if( Count == 2 ) Exe_name = Repository.Items[ Position ].Exe_name_3;
       if( Count == 3 ) Exe_name = Repository.Items[ Position ].Exe_name_4;

       // Вызываем приложение.
       if( Exe_name[ 0 ] != 0 )
        {
         // Задаем путь к приложению.
         CHAR Path[ SIZE_OF_PATH ] = "";
         strcpy( Path, Repository.Items[ Position ].Path );
         strcat( Path, "\\" );
         strcat( Path, Exe_name );

         // Если для приложения задан файл *.cmd - вызываем его.
         CHAR Cmd_path[ SIZE_OF_PATH ] = ""; strcpy( Cmd_path, Path );

         PCHAR Extension = strifind( ".exe", Cmd_path );

         if( Extension != NULL )
          {
           *( Extension + 1 ) = 'c';
           *( Extension + 2 ) = 'm';
           *( Extension + 3 ) = 'd';
          }

         if( FileExists( Cmd_path ) ) strcpy( Path, Cmd_path );

         // Если используется оболочка WPS - вызываем значок.
         if( ShellIsWPS() )
          {
           Success = WinOpenObject( QueryWPSObject( Path ), OPEN_DEFAULT, SHOW_EXISTING );
          }
         // Иначе - вызываем приложение.
         else
          {
           Success = Execute( Path );
          }
        }

       // Если приложение было вызвано - возврат.
       if( Success ) return 1;
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Вызывает WarpCenter, eCenter или SysTray ───

// Toolbar - что надо показать.
VOID Launcher_ShowShellToolbarMenu( LONG Toolbar )
{
 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это окно меню оболочки:
   if( ( Toolbar == FIND_WARPCENTER && IsWarpCenterWindow( Window ) ) ||
       ( Toolbar == FIND_SYSTRAY && IsSysTrayWindow( Window ) ) ||
       ( Toolbar == FIND_ECENTER && IsECenterWindow( Window ) ) )
    {
     // Если окно скрыто - показываем его.
     if( !WinIsWindowVisible( Window ) ) WinShowWindow( Window, 1 );

     // Вызываем окно и делаем его выбранным.
     WinSetActiveWindow( Desktop, Window );

     // Узнаем расположение окна.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // Узнаем окно, которое расположено в левом нижнем углу этого окна.
     // Если внутреннего окна нет, будет возвращено это окно.
     INT X_Point = 15; INT Y_Point = 15;

     POINT Desktop_point = { Window_placement.x + X_Point, Window_placement.y + Window_placement.cy - Y_Point };
     HWND Inner_window = WinWindowFromPoint( Desktop, &Desktop_point, 1 );

     // Посылаем внутреннему окну сообщение о нажатии кнопки мыши.
     WinPostMsg( Inner_window, WM_BUTTON1DOWN, MRFROM2SHORT( X_Point, Y_Point ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );
     WinPostMsg( Inner_window, WM_BUTTON1UP, MRFROM2SHORT( X_Point, Y_Point ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );

     // Завершаем перебор окон.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Прячет меню WarpCenter, ECenter или SysTray ───

VOID Launcher_HideShellToolbarMenu( BYTE Activate_window_in_center = 0 )
{
 // Надо запоминать, выполнено ли действие.
 BYTE Action_is_performed = 0;
 BYTE Post_queue_message = 0;
 BYTE Frame_window = NULLHANDLE;

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Проверяем окно.
   LONG Found = 0;

   if( IsWarpCenterMenuWindow( Window ) ) Found = FIND_WARPCENTER;
   if( IsSysTrayMenuWindow( Window ) ) Found = FIND_SYSTRAY;
   if( IsECenterMenuWindow( Window ) ) Found = FIND_ECENTER;

   // Если это окно меню оболочки:
   if( Found )
    {
     // Меню WarpCenter надо передавать сообщения напрямую. Другим меню отправлять его
     // так нельзя - меню отправляет такие сообщения владельцу, который пропускает их.
     BYTE Send_messages = 0; if( Found == FIND_WARPCENTER ) Send_messages = 1;

     // Составляем сообщение о нажатии клавиши Esc.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_ESC, 0, 0 );

     // Посылаем сообщение и ждем ответа, если это требуется.
     if( Send_messages )
      {
       WinSendMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinSendMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
      }
     else
      {
       WinPostMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinPostMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
      }

     // Запоминаем, что действие выполнено.
     Action_is_performed = 1;

     // Если найден eCenter, надо выбирать окно в середине экрана, используя поток WindowManager.
     if( Found == FIND_ECENTER )
      {
       Post_queue_message = 1;
       Frame_window = QueryFrameWindow( WinQueryWindow( Window, QW_OWNER ) );
      }

     // Завершаем перебор окон.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Делаем выбранным окно в середине экрана.
 if( Action_is_performed && Activate_window_in_center )
  {
   // Если можно выбрать окно сразу же:
   if( !Post_queue_message )
    {
     // Выбираем окно.
     ActivateWindowInCenter();
    }
   // А если надо подключить поток WindowManager:
   else
    {
     // Посылаем сообщение в очередь eCenter. К тому времени, как оно придет,
     // eCenter сделает себя выбранным и можно будет переключиться в другое окно.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SELECT_ANYTHING, 0 );
    }
  }

 // Возврат.
 return;
}

// ─── Вызывает ePager ───

VOID Launcher_ToggleEPager( VOID )
{
 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это окно ePager:
   if( IsEPagerWindow( Window ) )
    {
     // Если показано меню WarpCenter - прячем его.
     if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
      {
       Launcher_HideShellToolbarMenu( 0 );
       Launcher_HideShellToolbarMenu( 0 );
      }

     // Если окно ePager не выбрано:
     if( !WindowIsActive( Window ) )
      {
       // Если окно скрыто - показываем его.
       if( !WinIsWindowVisible( Window ) ) WinShowWindow( Window, 1 );

       // Вызываем окно и делаем его выбранным.
       WinSetActiveWindow( Desktop, Window );
      }
     // А если оно уже вызвано:
     else
      {
       // Делаем выбранным окно в середине экрана.
       ActivateWindowInCenter();
      }

     // Завершаем перебор окон.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Вызывает или прячет FileBar ───

VOID Launcher_ShowFileBarMenu( VOID )
{
 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно скрыто - продолжаем перебор окон.
   if( !WinIsWindowVisible( Window ) ) continue;

   // Если это окно FileBar:
   if( IsFileBarWindow( Window ) )
    {
     // Узнаем окно меню, расположенное внутри окна рамки FileBar.
     HWND Menu_window = WinWindowFromID( Window, FID_MENU );

     // Посылаем ему сообщение о нажатии кнопки мыши.
     WinPostMsg( Menu_window, WM_BUTTON1DOWN, MRFROM2SHORT( 1, 1 ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );
     WinPostMsg( Menu_window, WM_BUTTON1UP, MRFROM2SHORT( 1, 1 ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );

     // Завершаем перебор окон.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Вызывает или прячет список окон ───

// Show_window - скрыть или показать окно, Show_at_pointer - переместить его к указателю мыши.
VOID Launcher_ShowWindowList( BYTE Show_window, LONG Show_at_pointer = 0 )
{
 // Если показано окно сообщения об ошибке - возврат.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // Звук.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // Возврат.
   return;
  }

 // Перебираем окна.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это список окон:
   if( IsWinListWindow( Window ) )
    {
     // Если окно надо показать:
     if( Show_window )
      {
       // Если окно надо передвинуть к указателю мыши:
       if( Show_at_pointer )
        {
         // Узнаем размер экрана.
         HWND Desktop = QueryDesktopWindow();

         INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
         INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

         // Узнаем расположение указателя мыши.
         POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );

         // Узнаем расположение окна.
         SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

         // Если окно увеличено - восстанавливаем его.
         if( Window_placement.fl & SWP_MAXIMIZE )
          {
           // Восстанавливаем окно.
           PerformAction( Window, RESTORE_ACTION );

           // Узнаем новый размер и расположение окна.
           WinQueryWindowPos( Window, &Window_placement );
          }

         // Задаем новый размер и расположение окна.
         INT X_Size = Window_placement.cx;
         INT Y_Size = Window_placement.cy;

         INT X_Position = Pointer.x - X_Size / 2;
         INT Y_Position = Pointer.y - Y_Size / 2;

         if( X_Position + X_Size > X_Screen ) X_Position = X_Screen - X_Size;
         if( Y_Position + Y_Size > Y_Screen ) Y_Position = Y_Screen - Y_Size;

         if( X_Position < 0 ) X_Position = 0;
         if( Y_Position < 0 ) Y_Position = 0;

         // Устанавливаем новое расположение окна.
         WinSetWindowPos( Window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
        }

       // Показываем окно.
       if( !WinIsWindowVisible( Window ) )
        {
         // Показываем окно.
         WinShowWindow( Window, 1 );

         // Вызываем окно и делаем его выбранным.
         WinSetActiveWindow( QueryDesktopWindow(), Window );
        }
      }
     // А если окно надо скрыть:
     else
      {
       // Если окно не скрыто:
       if( WinIsWindowVisible( Window ) )
        {
         // Скрываем его.
         WinShowWindow( Window, 0 );

         // Делаем выбранным окно в середине экрана.
         BYTE All_OK = ActivateWindowInCenter();

         // Если такого окна нет - вызываем выравнивание списка окон.
         if( !All_OK ) WinPostQueueMsg( Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_WIN_LIST, (MPARAM) Window, 0 );
        }
      }

     // Завершаем перебор окон.
     WinEndEnumWindows( Enumeration );

     // Возврат.
     return;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Прячет все системные окна ───

VOID Launcher_HideAllSystemWindows( VOID )
{
 // Прячем список окон и меню WarpCenter.
 if( SystemWindowIsPresent( FIND_WINDOW_LIST | FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
  {
   Launcher_ShowWindowList( 0 ); Launcher_HideShellToolbarMenu( 1 );
  }

 // Возврат.
 return;
}

// ─── Создает поток, выполняющий ожидание, и посылает ему сообщение ───

// Message, - сообщение для потока, First_parameter - первый параметр сообщения.
VOID Launcher_StartDetachedWaiterThread( ULONG Message, ULONG First_parameter )
{
 // Сбрасываем переменную для ответа от потока.
 Thread_responds.Thread_is_created = 0;

 // Создаем поток.
 TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread( &Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE );
 // Если он создан - ждем, пока в нем будет создана очередь сообщений.
 if( Thread_is_created == NO_ERROR ) while( Thread_responds.Thread_is_created == 0 ) { Retard(); }

 // Если поток удалось создать:
 if( Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1 )
  {
   // Посылаем сообщение в поток.
   HMQ Owner_queue = Enhancer.Modules.Launcher->Message_queue;
   WinPostQueueMsg( Enhancer.Modules.Waiter->Message_queue, Message, (MPARAM) First_parameter, (MPARAM) Owner_queue );

   // Забываем про него.
   Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
  }

 // Возврат.
 return;
}

// ─── Переключает повторение мелодий ───

VOID Launcher_SwitchRepeatMode( VOID )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Посылаем команду проигрывателю PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*repeat" );

 // Посылаем команду проигрывателю WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "flip repeat" );

 // Посылаем команду проигрывателю Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*repeat" );

 // Возврат.
 return;
}

// ─── Включает или приостанавливает проигрыватель ───

VOID Launcher_FlipPlayerPause( VOID )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Посылаем команду проигрывателю PM123.
 if( !Launcher.RTSettings.Player_is_stopped )
  {
   TransactNamedPipe( Pipes->PM123_pipe, "*pause on" );
   Launcher.RTSettings.Player_is_stopped = 1;
  }
 else
  {
   TransactNamedPipe( Pipes->PM123_pipe, "*pause off" );
   Launcher.RTSettings.Player_is_stopped = 0;
  }

 // Посылаем команду проигрывателю WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "flip pause" );

 // Посылаем команду проигрывателю Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*pause" );

 // Возврат.
 return;
}

// ─── Переводит проигрыватель к следующей дорожке ───

VOID Launcher_SkipPlayerTrack( VOID )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Посылаем команду проигрывателю PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*next" );

 // Посылаем команду проигрывателю WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "exit" );

 // Посылаем команду проигрывателю Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*next" );

 // Возврат.
 return;
}

// ─── Переводит проигрыватель к предыдущей дорожке ───

VOID Launcher_RollbackPlayerTrack( VOID )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Посылаем команду проигрывателю PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*previous" );

 // Посылаем команду проигрывателю Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*previous" );

 // Возврат.
 return;
}

// ─── Останавливает проигрыватель ───

VOID Launcher_StopPlayer( VOID )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Посылаем команду проигрывателю PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*stop" );

 // Посылаем команду проигрывателю WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "exit" );

 // Посылаем команду проигрывателю Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*stop" );

 // Возврат.
 return;
}

// ─── Увеличивает или уменьшает громкость ───

// Up_or_down - значение, на которое надо изменить громкость.
VOID Launcher_ChangePlayerVolume( INT Up_or_down )
{
 // Получаем указатель на список известных PIPE-соединений.
 PPIPES Pipes = GetKnownPipes();

 // Увеличиваем громкость для проигрывателя PM123.
 if( Up_or_down > 0 ) TransactNamedPipe( Pipes->PM123_pipe, "*volume +3" );
 if( Up_or_down < 0 ) TransactNamedPipe( Pipes->PM123_pipe, "*volume -3" );

 // Увеличиваем громкость для проигрывателя WarpVision.
 {
  if( Launcher.RTSettings.Player_volume == 0 ) Launcher.RTSettings.Player_volume = 25;
  else Launcher.RTSettings.Player_volume += ( Up_or_down * 5 );

  if( Launcher.RTSettings.Player_volume < 0 ) Launcher.RTSettings.Player_volume = 0;
  if( Launcher.RTSettings.Player_volume > 100 ) Launcher.RTSettings.Player_volume = 100;

  {
   CHAR Volume_string[ 25 ] = "";
   itoa( Launcher.RTSettings.Player_volume, Volume_string, 10 );

   CHAR Query_string[ SIZE_OF_PIPE_COMMAND ] = "";
   strcpy( Query_string, "set volume " ); strcat( Query_string, Volume_string );

   TransactNamedPipe( Pipes->WarpVision_pipe, Query_string );
  }
 }

 // Увеличиваем или уменьшаем громкость для проигрывателя Z!.
 if( Up_or_down > 0 ) TransactNamedPipe( Pipes->ZMP3_pipe, "*vol+" );
 if( Up_or_down < 0 ) TransactNamedPipe( Pipes->ZMP3_pipe, "*vol-" );

 // Возврат.
 return;
}

// ─── Увеличивает или уменьшает громкость ───

// Frame_window - окно приложения, Up_or_down - значение, на которое надо изменить громкость.
VOID Launcher_PostMMOS2VolumeMessages( HWND Frame_window, INT Up_or_down )
{
 // Перебираем окна, расположенные в окне рамки.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это окно движка со стрелками:
   if( IsCircularSliderWindow( Window ) )
    {
     // Узнаем выбранное значение громкости.
     // Переменная "MMOS2_volume" располагается в разделяемой области памяти,
     // поэтому доступ к ней во время обработки этого сообщения будет возможен.
     MRESULT Rc = WinSendMsg( Window, CSM_QUERYVALUE, (MPARAM) &Launcher.RTSettings.MMOS2_volume, 0 );

     // Если его удалось получить:
     if( Rc != 0 )
      {
       // Узнаем наибольшее и наименьшее возможное значение.
       WinSendMsg( Window, CSM_QUERYRANGE, (MPARAM) &Launcher.RTSettings.MMOS2_volume_from, (MPARAM) &Launcher.RTSettings.MMOS2_volume_to );

       // Задаем новое значение.
       Launcher.RTSettings.MMOS2_volume += Up_or_down * 2;
       if( Launcher.RTSettings.MMOS2_volume < Launcher.RTSettings.MMOS2_volume_from ) Launcher.RTSettings.MMOS2_volume = Launcher.RTSettings.MMOS2_volume_from;
       if( Launcher.RTSettings.MMOS2_volume > Launcher.RTSettings.MMOS2_volume_to ) Launcher.RTSettings.MMOS2_volume = Launcher.RTSettings.MMOS2_volume_to;

       WinPostMsg( Window, CSM_SETVALUE, (MPARAM) Launcher.RTSettings.MMOS2_volume, 0 );
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Увеличивает или уменьшает громкость ───

// Frame_window - окно приложения, Up_or_down - значение, на которое надо изменить громкость.
VOID Launcher_PostUniMixMessages( HWND Frame_window, INT Up_or_down )
{
 // Проверяем версию UniMixer.
 if( IsSpeedPascalWindow( Frame_window ) )
  {
   // Перебираем окна, расположенные в окне рамки.
   HENUM Enumeration = WinBeginEnumWindows( WinWindowFromID( Frame_window, FID_CLIENT ) ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Составляем сообщение о нажатии стрелки влево или вправо.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
     if( Up_or_down > 0 )
      ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_RIGHT, 0, 0 );
     else
      ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_LEFT, 0, 0 );

     // Посылаем его.
     WinPostMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
     WinPostMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
    }
   WinEndEnumWindows( Enumeration );
  }

 // Возврат.
 return;
}

// ─── Увеличивает или уменьшает громкость ───

// Up_or_down - значение, на которое надо изменить громкость.
VOID Launcher_ChangeMMOS2Volume( INT Up_or_down )
{
 // Проверяем, есть ли окно приложения, способного менять звук, и если оно есть - обращаемся к нему.
 HWND MMOS2_volume_window = FindAppWindow( APP_MMOS2_VOLUME );
 if( MMOS2_volume_window != NULLHANDLE )
  {
   // Посылаем сообщения в окно MMOS2 Volume.
   Launcher_PostMMOS2VolumeMessages( MMOS2_volume_window, Up_or_down );

   // Возврат.
   return;
  }

 HWND UniMix_window = FindAppWindow( APP_UNIAUDIO_MIXER );
 if( UniMix_window != NULLHANDLE )
  {
   // Посылаем сообщения в окно UniAudio Mixer.
   Launcher_PostUniMixMessages( UniMix_window, Up_or_down );

   // Возврат.
   return;
  }

 // Если окна нет - вызываем приложение, которое покажет его и ждем его появления.
 if( ShowCommandCanBeUsed( SHOW_MMOS2_VOLUME ) )
  {
   // Посылаем сообщение в поток, который вызовет приложение.
   WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_MMOS2_VOLUME, 0 );
   // Посылаем сообщение в поток, который выполнит ожидание.
   Launcher_StartDetachedWaiterThread( SM_WAIT_STARTING_PROCESS, APP_MMOS2_VOLUME );

   // Возврат.
   return;
  }

 if( ShowCommandCanBeUsed( SHOW_UNIAUDIO_MIXER ) )
  {
   // Посылаем сообщение в поток, который вызовет приложение.
   WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_UNIAUDIO_MIXER, 0 );
   // Посылаем сообщение в поток, который выполнит ожидание.
   Launcher_StartDetachedWaiterThread( SM_WAIT_STARTING_PROCESS, APP_UNIAUDIO_MIXER );

   // Возврат.
   return;
  }

 // Возврат.
 return;
}

// ─── Выполняет определенные действия при нажатии на клавиши ───

// Action - действие, которое нужно выполнить, Do_not_check_mouse - отключить проверку мыши.
VOID Launcher_DoSystemAction( INT Action, LONG Do_not_check_mouse = 0 )
{
 // Кнопка мыши не должна быть нажата - возможно, передвигается предмет или окно.
 if( !Do_not_check_mouse ) if( MouseIsBusy() )
  {
   // Звук.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // Возврат.
   return;
  }

 // Если показано окно сообщения об ошибке - ничего делать не нужно.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // Звук.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // Возврат.
   return;
  }

 // Устанавливаем переключатели на клавиатуре, чтобы расширитель не начинал
 // передвижение изображения, если в окна будут направляться сообщения от мыши.
 if( KeyIsToggled( SC_SCRLLOCK ) ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // Вызываем WarpCenter, ECenter или SysTray.
 if( Action == SHOW_WARPCENTER || Action == SHOW_ECENTER || Action == SHOW_SYSTRAY )
  {
   // Если меню уже показано - прячем его.
   if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
    {
     // Прячем меню.
     Launcher_HideShellToolbarMenu( 1 );
    }
   // Иначе - вызываем его.
   else
    {
     // Получаем указатель на список известных имен значков.
     POBJECTS Objects = GetKnownObjects();

     // Пробуем найти окно.
     LONG Toolbar = FIND_WARPCENTER;
     PCHAR Object_name = Objects->WarpCenter_name;

     if( Action == SHOW_SYSTRAY )
      {
       Toolbar = FIND_SYSTRAY;
       Object_name = Objects->SysTray_name;
      }

     if( Action == SHOW_ECENTER )
      {
       Toolbar = FIND_ECENTER;
       Object_name = Objects->ECenter_name;
      }

     // Если его нет:
     if( !SystemWindowIsPresent( Toolbar ) )
      {
       // Узнаем значок на рабочем столе.
       HOBJECT Object = QueryWPSObject( Object_name );

       // Если значок есть - вызываем его.
       if( Object != NULLHANDLE ) WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
      }

     // Вызываем меню.
     Launcher_ShowShellToolbarMenu( Toolbar );
    }

   // Возврат.
   return;
  }

 // Вызываем EPager.
 if( Action == SHOW_EPAGER )
  {
   // Вызываем окно ePager.
   Launcher_ToggleEPager();

   // Возврат.
   return;
  }

 // Вызываем меню FileBar.
 if( Action == SHOW_FILEBAR )
  {
   // Вызываем меню FileBar.
   Launcher_ShowFileBarMenu();

   // Возврат.
   return;
  }

 // Вызываем список окон.
 if( Action == SHOW_WINDOW_LIST )
  {
   // Если список окон уже вызван - прячем его.
   if( SystemWindowIsPresent( FIND_WINDOW_LIST, FIND_VISIBLE_WINDOW ) )
    {
     Launcher_ShowWindowList( 0 );
    }
   // Иначе - вызываем список окон.
   else
    {
     Launcher_ShowWindowList( 1 );
    }

   // Возврат.
   return;
  }

 // Делаем выбранным следующее или предыдущее окно в списке окон.
 if( Action == SHOW_NEXT_WINDOW || Action == SHOW_PREV_WINDOW )
  {
   // Если идет смена комнат - возврат.
   if( RoomsChangeIsInProcess() ) return;

   // Если используется оболочка WPS, но ее окно уменьшено, возможно зависание системы на
   // некоторое время. Оно происходит при вызове WinQueryWindow(), в чем дело - непонятно.
   if( ShellIsWPS() )
    if( GetCurrentOrNextRoom() == SHELL_ROOM )
     if( !ShellIsAvailable() ) return;

   // Узнаем окно, которое сейчас выбрано.
   HWND Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

   // Если его нет или в него нельзя было переключиться с помощью расширителя:
   if( Active_window == NULLHANDLE || !Launcher_PermissionForHotKeySwitching( Active_window ) )
    {
     // Узнаем окно в середине экрана.
     HWND Window_in_center = WindowInCenter();

     // Если оно есть и это не выбранное окно - делаем его выбранным.
     if( Window_in_center != NULLHANDLE ) if( Window_in_center != Active_window )
      {
       // Делаем выбранным окно в середине экрана.
       MoveWindowAbove( Window_in_center );

       // Возврат.
       return;
      }
    }

   // Если выбранное окно - список окон, его надо скрыть.
   if( Active_window != NULLHANDLE )
    {
     // Если это список окон - прячем его.
     if( IsWinListWindow( Active_window ) ) PerformAction( Active_window, HIDE_ACTION );
    }

   // Узнаем следующее или предыдущее окно в списке окон и запоминаем его.
   // Как ни странно, запрос "prevtop" возвращает следующее окно, а "nexttop" - предыдущее.
   LONG Query = QW_PREVTOP; if( Action == SHOW_PREV_WINDOW ) Query = QW_NEXTTOP;

   HWND Next_window = WinQueryWindow( Active_window, Query );
   HWND Primary_window = Next_window;

   // Если переключение невозможно - просматриваем список дальше.
   if( !Launcher_PermissionForHotKeySwitching( Next_window ) )
    while( 1 )
     {
      // Узнаем следующее окно в списке окон.
      Next_window = WinQueryWindow( Next_window, Query );

      // Если список пройден - возврат.
      if( Next_window == Active_window || Next_window == Primary_window ) return;

      // Если переключение возможно - завершаем перебор окон.
      if( Launcher_PermissionForHotKeySwitching( Next_window ) ) break;
     }

   // Делаем окно выбранным.
   MoveWindowAbove( Next_window );

   // Возврат.
   return;
  }

 // Если пользователь работает с окном приложения, которое соответствует этой команде -
 // прячем его и выбираем окно в середине экрана.
 if( Launcher_CheckActiveWindowAndHideApplication( Action ) ) return;

 // Если одно из известных приложений может откликнуться на эту команду - вызываем его.
 // Если для этой команды был задан значок - приложение будет вызвано в первую очередь.
 if( Launcher_FindAndShowApplication( Action ) ) return;

 // Вызываем значок на рабочем столе.
 // Он будет вызван только если для этой команды нет подходящего приложения.
 if( Action >= SHOW_OBJECT_FIRST && Action <= SHOW_OBJECT_LAST )
  {
   // Если оболочка WPS не используется:
   if( !ShellIsWPS() )
    {
     // Если в качестве оболочки используется FileBar - вызываем его.
     if( ShellIsFileBar() ) Launcher_ShowFileBarMenu();

     // Возврат.
     return;
    }

   // Вызываем принтер.
   if( Action == SHOW_PRINTER )
    {
     // Узнаем имя принтера, с которым работает пользователь.
     CHAR Name[ SIZE_OF_PATH ] = ""; QueryPrinterName( Name );

     // Если имя узнать не удалось - вызываем окно просмотра состояния всех принтеров.
     if( Name[ 0 ] == 0 )
      {
       // Посылаем сообщение в поток.
       WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_PRINTERS, 0 );

       // Возврат.
       return;
      }
    }

   // Получаем указатель на список известных имен значков.
   POBJECTS Objects = GetKnownObjects();

   // Задаем имя значка.
   CHAR Name[ SIZE_OF_PATH ] = "";

   if( Action == SHOW_DRIVES )         strcpy( Name, Objects->Drives_name );
   if( Action == SHOW_PRINTERS )       strcpy( Name, Objects->Printers_name );

   if( Action == SHOW_WINVIEWER )      strcpy( Name, Objects->Viewer_name );
   if( Action == SHOW_WPS_CLOCK )      strcpy( Name, Objects->Clock_name );
   if( Action == SHOW_PULSE )          strcpy( Name, Objects->Pulse_name );
   if( Action == SHOW_POWER_MGR )      strcpy( Name, Objects->PowerMgr_name );

   if( Action == SHOW_LAUNCHPAD )      strcpy( Name, Objects->LaunchPad_name );

   // Если имя узнать не удалось - возврат.
   if( Name[ 0 ] == NULL ) return;

   // Узнаем значок на рабочем столе.
   HOBJECT Object = QueryWPSObject( Name );

   // Если значок есть:
   if( Object != NULLHANDLE )
    {
     // Вызываем значок.
     WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
    }
   // А если значка нет - вызываем список окон.
   else
    {
     // Если список окон уже вызван - прячем его.
     if( SystemWindowIsPresent( FIND_WINDOW_LIST, FIND_VISIBLE_WINDOW ) )
      {
       Launcher_ShowWindowList( 0 );
      }
     // Иначе - вызываем список окон.
     else
      {
       Launcher_ShowWindowList( 1 );
      }
    }

   // Возврат.
   return;
  }

 // Управляем проигрывателем.
 if( Action >= MM_FIRST && Action <= MM_LAST )
  {
   // Обращаемся к проигрывателю.
   switch( Action )
    {
     case MM_VOLUME_INCREMENT:       Launcher_ChangePlayerVolume( +1 ); break;
     case MM_VOLUME_DECREMENT:       Launcher_ChangePlayerVolume( -1 ); break;
     case MM_VOLUME_INCREMENT_MMOS2: Launcher_ChangeMMOS2Volume( +1 );  break;
     case MM_VOLUME_DECREMENT_MMOS2: Launcher_ChangeMMOS2Volume( -1 );  break;

     case MM_REPEAT:                 Launcher_SwitchRepeatMode();       break;
     case MM_PAUSE:                  Launcher_FlipPlayerPause();        break;
     case MM_NEXT:                   Launcher_SkipPlayerTrack();        break;
     case MM_PREVIOUS:               Launcher_RollbackPlayerTrack();    break;
     case MM_STOP:                   Launcher_StopPlayer();             break;
    }

   // Возврат.
   return;
  }

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Launcher_LauncherMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Launcher->Priority = MAKELONG( Class, Delta );
  }

 // Выполняем требуемое действие.
 if( Message->msg == SM_DO_SYSTEM_ACTION ) Launcher_DoSystemAction( (INT) Message->mp1, (LONG) Message->mp2  );

 // Вызываем LaunchPad.
 if( Message->msg == SM_SHOW_LAUNCHPAD )
  {
   // Ждем, пока мышь не станет свободна.
   while( MouseIsBusy() ) Retard();

   // Вызываем LaunchPad.
   Launcher_DoSystemAction( SHOW_LAUNCHPAD );
  }

 // Вызываем список окон.
 if( Message->msg == SM_SHOW_WINDOW_LIST )
  {
   // Узнаем, должен ли список окон появиться рядом с указателем мыши.
   LONG Show_at_pointer = (LONG) Message->mp1;

   // Показываем его окно.
   Launcher_ShowWindowList( 1, Show_at_pointer );
  }

 // Скрываем список окон.
 if( Message->msg == SM_HIDE_WINDOW_LIST ) Launcher_ShowWindowList( 0 );

 // Скрываем меню WarpCenter.
 if( Message->msg == SM_HIDE_WARPCENTER ) Launcher_HideShellToolbarMenu( 1 );

 // Скрываем окно регулятора громкости.
 if( Message->msg == SM_STARTING_PROCESS_APPEARED )
  {
   INT App_code = (LONG) Message->mp1;
   HWND Frame_window = (HWND) Message->mp2;

   if( App_code == APP_MMOS2_VOLUME || App_code == APP_UNIAUDIO_MIXER )
    WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );
  }

 // Возврат.
 return;
}

// ─── Поток для выпонения различных действий ───

VOID Launcher_LauncherThread( VOID )
{
 // Определяем поток в системе.
 HAB Thread = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Thread == NULLHANDLE )
  {
   // При создании потока произошла ошибка.
   Thread_responds.Thread_is_created = -1;

   // Выход.
   return;
  }

 // Создаем очередь сообщений - она должна быть в каждом потоке.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Launcher->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Launcher->Message_queue == NULLHANDLE )
  {
   // Завершаем работу потока.
   WinTerminate( Thread );

   // При создании потока произошла ошибка.
   Thread_responds.Thread_is_created = -1;

   // Выход.
   return;
  }

 // Поток создан успешно.
 Thread_responds.Thread_is_created = 1;

 // Получение и обработка сообщений, приходящих в поток.
 QMSG Message = {0};
 while( WinGetMsg( Thread, &Message, 0, 0, 0 ) )
  {
   // Проверяем, не идет ли следом такое же сообщение.
   QMSG Next_message = {0};
   WinPeekMsg( Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE );
   if( Next_message.msg == Message.msg )
    if( Next_message.mp1 == Message.mp1 )
     if( Next_message.mp2 == Message.mp2 )
      if( Next_message.hwnd == Message.hwnd ) continue;

   // Обрабатываем сообщение.
   Launcher_LauncherMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
