
// ─── Задает состояние кнопок по умолчанию ───

// Frame_window - окно рамки.
LONG Diver_GetPreDefinedButtonsState( HWND Frame_window )
{
 // Если окна картинки нет - возврат.
 if( WinWindowFromID( Frame_window, FID_SYSMENU ) == NULLHANDLE ) return NO_ACTION;

 // Узнаем, как выглядит рамка окна.
 LONG Frame_type = FrameType( Frame_window );

 // Если окно имеет рамку в одну точку - требуется кнопка закрытия.
 if( Frame_type == FT_POINT ) return CLOSE_ACTION;

 // Если это окно постоянного размера - требуется кнопка закрытия.
 if( Frame_type == FT_CONST )
  if( PermissionForButtonsDrawing( Frame_window ) ) return CLOSE_ACTION;

 // Если окно имеет обычную рамку:
 if( Frame_type == FT_NORMAL )
  {
   // Если это окно справочника - состояние кнопок может быть любым, возврат.
   if( WindowIsCreatedBy( APP_VIEWDOC, Frame_window ) ) return NO_ACTION;

   // Если это текстовое окно - надо рисовать все кнопки, возврат.
   if( IsVIOWindow( Frame_window ) ) return CLOSE_ACTION | MINIMIZE_ACTION | MAXIMIZE_ACTION;

   // Задаем состояние кнопок.
   BYTE Draw_all_buttons = 0;

   // Если это окно WPS - должны быть нарисованы все кнопки.
   if( IsFolderWindow( Frame_window ) ) Draw_all_buttons = 1;

   // Так же, если в окне есть меню и его родительское окно - рабочий стол.
   if( !Draw_all_buttons )
    if( WinWindowFromID( Frame_window, FID_MENU ) != NULLHANDLE )
     if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
      Draw_all_buttons = 1;

   // Если в окне должны быть нарисованы все кнопки:
   if( Draw_all_buttons )
    {
     // Для некоторых окон нужна только кнопка закрытия.
     if( Painter_OneActionIsAllowed( Frame_window ) ) return CLOSE_ACTION;

     // Для некоторых окон не нужна кнопка уменьшения.
     if( !Painter_MinimizeActionIsAllowed( Frame_window ) ) return CLOSE_ACTION | MAXIMIZE_ACTION;

     // Для остальных окон нужны все три кнопки.
     return ALL_ACTIONS;
    }
  }

 // Возврат.
 return NO_ACTION;
}

// ─── Узнает свойства окна ───

// Frame_window - окно рамки, Target и Buttons_to_detect - какое свойство надо узнать.
// Update_frame_if_required - рамку можно обновить если это требуется.
VOID Diver_QueryWindowProperty( HWND Frame_window, ULONG Target, LONG Buttons_to_detect = ALL_ACTIONS, BYTE Update_frame_if_required = 0 )
{
 // Узнаем расположение окна и его состояние.
 SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

 // Если окно уменьшено в значок или скрыто - возврат.
 if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE ) return;

 // Узнаем значок окна.
 if( Target & WT_SYSMENU )
  {
   // Узнаем значок окна.
   HPOINTER Icon = Diver_QueryWindowIcon( Frame_window );

   // Если он есть:
   if( Icon != NULLHANDLE )
    {
     // Если значок изменился - рамка должна быть перерисована.
     HPOINTER Previous_icon = NULLHANDLE; FindProperty( Frame_window, PRP_ICON, &Previous_icon );

     if( Icon != Previous_icon )
      {
       // Устанавливаем свойство.
       SetProperty( Frame_window, PRP_ICON, &Icon );

       // Посылаем сообщение в поток рисования.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_SYSMENU );
      }
    }
  }

 // Узнаем ширину рамки окна.
 if( Target & WT_SYSMENU )
  {
   // Отправляем сообщение в окно.
   Diver.RTSettings.FB_size.x = 0; Diver.RTSettings.FB_size.y = 0;
   WinSendMsg( Frame_window, WM_QUERYBORDERSIZE, (MPARAM) &Diver.RTSettings.FB_size, 0 );

   // Шириной рамки будем считать наименьшее полученное значение.
   INT Width = min( Diver.RTSettings.FB_size.x, Diver.RTSettings.FB_size.y );

   // Если оно было получено:
   if( Width != 0 )
    {
     // Если ширина изменилась - рамка должна быть перерисована.
     INT Previous_width = 0; FindProperty( Frame_window, PRP_BORDER, &Previous_width );

     if( Width != Previous_width )
      {
       // Устанавливаем свойство.
       SetProperty( Frame_window, PRP_BORDER, &Width );

       // Узнаем значение по умолчанию.
       INT System_value = FrameWidth( Frame_window );

       // Если это другое значение - посылаем сообщение в поток рисования.
       if( Width != System_value )
        {
         ULONG Update_all = WT_BORDER | WT_SYSMENU | WT_TITLEBAR | WT_MINMAX | WT_MENU;
         WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Update_all );
        }
      }
    }
  }

 // Узнаем заголовок окна.
 if( Target & WT_TITLEBAR )
  {
   // Узнаем заголовок окна.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
   CHAR Title[ SIZE_OF_TITLE ] = ""; QueryWindowTitle( Frame_window, TitleBar_window, Title, Update_frame_if_required );

   // Если заголовок определен:
   if( Title[ 0 ] != 0 )
    {
     // Если заголовок изменился - рамка должна быть перерисована.
     CHAR Previous_title[ SIZE_OF_TITLE ] = ""; FindProperty( Frame_window, PRP_TITLE, Previous_title );

     if( strcmp( Title, Previous_title ) != EQUALLY )
      {
       // Устанавливаем свойство.
       SetProperty( Frame_window, PRP_TITLE, Title );

       // Посылаем сообщение в поток рисования.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_TITLEBAR );
      }
    }
  }

 // Узнаем состояние кнопок в правом верхнем углу окна.
 if( Target & WT_MINMAX )
  {
   // Узнаем, есть ли это свойство в списке.
   BYTE Actions_are_detected = 0; FindProperty( Frame_window, PRP_ACTIONS, &Actions_are_detected );

   // Если его нет - узнаем состояние кнопок по умолчанию.
   if( !Actions_are_detected )
    {
     // Узнаем состояние кнопок по умолчанию.
     LONG Buttons_state = Diver_GetPreDefinedButtonsState( Frame_window );

     // Запоминаем, что состояние кнопок определено.
     BYTE Detected = 1; SetProperty( Frame_window, PRP_ACTIONS, &Detected );

     // Если оно задано - рамка должна быть перерисована.
     if( Buttons_state != NO_ACTION )
      {
       // Устанавливаем свойство.
       SetProperty( Frame_window, PRP_BUTTONS, &Buttons_state );

       // Посылаем сообщение в поток рисования.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_BORDER );
      }
    }

   // Узнаем состояние кнопок в окне.
   LONG Buttons_state = QueryButtonsState( Frame_window, Buttons_to_detect, 1 );

   // Если состояние кнопок изменилось - рамка должна быть перерисована.
   LONG Previous_state = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Previous_state );

   if( Buttons_state != Previous_state )
    {
     // Устанавливаем свойство.
     SetProperty( Frame_window, PRP_BUTTONS, &Buttons_state );

     // Посылаем сообщение в поток рисования.
     WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_BORDER );
    }
  }

 // Возврат.
 return;
}

// ─── Посылает сообщение в поток рисования или в очередь окна ───

// Frame_window - окно рамки.
VOID Diver_CheckWindowFrameDrawingNode( HWND Frame_window )
{
 // Посылаем сообщение в очередь.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
 WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Frame_window );

 // Возврат.
 return;
}

// ─── Проверяет рамки окон постоянного размера ───

// Frame_window - окно рамки, Window - окно, которое надо проверить.
VOID Diver_CheckWindowFrame( HWND Frame_window, HWND Window )
{
 // Узнаем размер окна рамки.
 RECT Frame_rectangle = {0}; WinQueryWindowRect( Frame_window, &Frame_rectangle );

 // Проверяем рамку.
 if( PermissionForInnerFrameDrawing( Frame_window, Window, &Frame_rectangle ) )
  Diver_CheckWindowFrameDrawingNode( Frame_window );

 // Возврат.
 return;
}

// ─── Проверяет состояние кнопок в окнах приложения, а также их значки ───

// Frame_window - окно рамки.
VOID Diver_CheckWindowControls( HWND Frame_window )
{
 // Узнаем очередь сообщений окна.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );

 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно скрыто - продолжаем перебор окон.
   if( !WinIsWindowVisible( Window ) ) continue;

   // Если это не окно рамки - продолжаем перебор окон.
   if( !IsFrameWindow( Window ) ) continue;

   // Если это то же самое окно - продолжаем перебор окон.
   if( Window == Frame_window ) continue;

   // Узнаем очередь сообщений окна.
   HMQ Window_queue = WinQueryWindowULong( Window, QWL_HMQ );

   // Если окно использует ту же очередь сообщений - его надо проверить.
   if( Window_queue == Message_queue ) if( PermissionForDrawing( Window ) )
    Diver_QueryWindowProperty( Window, WT_SYSMENU | WT_MINMAX, CLOSE_ACTION );
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Diver_DiverMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Diver->Priority = MAKELONG( Class, Delta );
  }

 // Узнаем свойства окна.
 if( Message->msg == SM_QUERY_PROPERTIES )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Узнаем, какое свойство надо узнать.
   ULONG Target = (ULONG) Message->mp2;

   // Узнаем значок и ширину рамки окна.
   if( Target & WT_UNKNOWN || Target & WT_SYSMENU )
    Diver_QueryWindowProperty( Frame_window, WT_SYSMENU );

   // Если окно заголовка было перерисовано - узнаем заголовок.
   if( Target & WT_UNKNOWN || Target & WT_TITLEBAR ) Diver_QueryWindowProperty( Frame_window, WT_TITLEBAR );

   // Если заголовок есть, но он еще не определен - узнаем его, когда перерисовывается рамка.
   if( Target & WT_BORDER )
    {
     // Узнаем окно заголовка.
     HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

     // Если оно есть:
     if( TitleBar_window != NULLHANDLE )
      {
       // Узнаем, есть ли в списке заголовок окна.
       CHAR Title[ SIZE_OF_TITLE ] = ""; FindProperty( Frame_window, PRP_TITLE, Title );

       // Если его нет - узнаем его.
       if( Title[ 0 ] == 0 ) Diver_QueryWindowProperty( Frame_window, WT_TITLEBAR, NO_ACTION, 1 );
      }
    }

   // Узнаем состояние кнопок в правом верхнем углу окна.
   // Проверять кнопки при Target == WT_TITLEBAR нельзя - может
   // возникнуть постоянное рисование, которое выглядит как "мигание" рамки.
   if( Target & WT_UNKNOWN || Target & WT_SYSMENU ) Diver_QueryWindowProperty( Frame_window, WT_MINMAX );

   // Если состояние кнопок еще не определено - узнаем его, когда перерисовывается рамка.
   if( Target & WT_BORDER )
    {
     // Узнаем, есть ли в списке состояние кнопок.
     BYTE Actions_are_detected = 0; FindProperty( Frame_window, PRP_ACTIONS, &Actions_are_detected );

     // Если его нет - узнаем его.
     if( !Actions_are_detected ) Diver_QueryWindowProperty( Frame_window, WT_MINMAX );
    }
  }

 // Проверяет состояние всех окон, когда одно из окон становится выбранным.
 if( Message->msg == SM_CHECK_CONTROLS )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Проверяем состояние кнопок в окнах приложения, а также их значки.
   Diver_CheckWindowControls( Frame_window );

   // Если окно не перестало быть выбранным - проверяем, нет ли в списке двух одновременно выбранных окон.
   // Для окон диалога эту проверку выполнять не надо - они всегда работают правильно.
   if( WindowIsActive( Frame_window ) )
    if( !WindowIsAppDialog( Frame_window ) )
     CheckActivityProperties( Frame_window );
  }

 // Проверяем рамки окон постоянного размера.
 if( Message->msg == SM_CHECK_FRAME )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;
   // Узнаем окно, которое надо проверить.
   HWND Window = (HWND) Message->mp2;

   // Если одного из окон нет - возврат.
   HAB Application = WinQueryAnchorBlock( Frame_window );
   if( !WinIsWindow( Application, Frame_window ) ) return;
   if( !WinIsWindow( Application, Window ) ) return;

   // Выполняем проверку.
   Diver_CheckWindowFrame( Frame_window, Window );
  }

 // Возврат.
 return;
}

// ─── Поток для определения свойств окон ───

VOID Diver_DiverThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Diver->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Diver->Message_queue == NULLHANDLE )
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
   Diver_DiverMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
