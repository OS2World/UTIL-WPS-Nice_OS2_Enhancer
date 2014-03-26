
// ─── Распахивает текстовое окно ───

BYTE Arranger_SpreadVIOWindow( HWND Frame_window )
{
 // Проверяем, есть ли в окне полоски просмотра.
 if( !WinWindowFromID( Frame_window, FID_VERTSCROLL ) &&
     !WinWindowFromID( Frame_window, FID_HORZSCROLL ) ) return 0;

 // Создаем область памяти, чтобы окно могло вернуть свое наибольшее возможное расположение.
 PSWP Window_position = NULL;
 APIRET Report = DosAllocSharedMem( (PPVOID) &Window_position, NULL, sizeof( SWP ), PAG_ALLOCATE | OBJ_GIVEABLE );

 if( Report == NO_ERROR )
  {
   // Создаем переменные для наибольшего размера окна.
   INT Max_X = 0;
   INT Max_Y = 0;

   // Заполняем область памяти нулями.
   bzero( Window_position, 0 );

   // Передаем область памяти приложению, создавшему окно.
   PID Process_ID = 0;
   WinQueryWindowProcess( Frame_window, &Process_ID, NULL );
   Report = DosGiveSharedMem( Window_position, Process_ID, PAG_READ | PAG_WRITE );

   if( Report == NO_ERROR )
    {
     // Направляем окну сообщение, чтобы оно рассчитало свое расположение в увеличенном виде.
     Window_position->fl = SWP_MAXIMIZE | SWP_NOADJUST | SWP_NOREDRAW;
     WinSendMsg( Frame_window, WM_ADJUSTWINDOWPOS, Window_position, 0 );

     // Если это расположение получено:
     if( Window_position->cx != 0 && Window_position->cy != 0 )
      {
       // Запоминаем его
       Max_X = Window_position->cx;
       Max_Y = Window_position->cy;

       // Увидев предыдущее сообщение, окно могло изменить свое расположение.
       // Предлагаем ему вычислить свое расположение в его обыкновенном виде.
       Window_position->fl = SWP_RESTORE | SWP_NOADJUST | SWP_NOREDRAW;
       WinSendMsg( Frame_window, WM_ADJUSTWINDOWPOS, Window_position, 0 );
      }
    }

   // Освобождаем память.
   DosFreeMem( Window_position ); Window_position = NULL;

   // Если расположение было получено:
   if( Max_X != 0 && Max_Y != 0 )
    {
     // Узнаем размер и расположение окна.
     SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

     // Если полученные значения не совпадают:
     if( Window_placement.cx != Max_X || Window_placement.cy != Max_Y )
      {
       // Ставим окно-занавеску поверх всех окон.
       // Это поможет избежать мусора на экране (появляется с некоторыми видеокартами).
       ShowCurtainWindow( QueryDesktopWindow() );

       // Задаем новое расположение окна.
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, Max_X, Max_Y, SWP_SIZE );

       // Возврат.
       return 1;
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Выравнивает окна ───

// Action определяет действие, Frame_window - окно рамки.
VOID Arranger_ArrangeWindows( ULONG Action, HWND Frame_window )
{
 // Если идет смена комнат - возврат.
 if( SynchronizeArrangerAndRooms() )
  if( Action != SM_ARRANGE_WIN_LIST )
   if( Action != SM_ARRANGE_VIO_IN_ROOM )
    if( !TimeForRoomsSwitchingIsGone() ) return;

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Узнаем расположение окна в родительском окне - то есть в окне рабочего стола.
 SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

 // Если окно уменьшено или скрыто - возврат.
 if( Window_placement.fl & SWP_MINIMIZE || Window_placement.fl & SWP_HIDE )
  if( Action != SM_ARRANGE_WIN_LIST )
   return;

 // Узнаем размер экрана.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // Узнаем высоту заголовка окна.
 INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

 // В некоторых случаях окно надо будет вызвать наверх.
 BYTE Activate_window = 0;
 // А также поставить окно-занавеску поверх всех окон.
 BYTE Show_curtain = 0;

 // Выравниваем текстовые окна при переходе между комнатами.
 if( Action == SM_ARRANGE_VIO_IN_ROOM )
  if( Window_placement.fl & SWP_MAXIMIZE )
   Action = SM_ARRANGE_VIO;

 // Выравниваем окна File Commander, когда они занимают весь экран.
 if( Action == SM_ARRANGE_FC2 )
  {
   if( Window_placement.cx > X_Screen )
    {
     Action = SM_ARRANGE_VIO; Show_curtain = 1;
     ULONG No_more = 1; SetProperty( Frame_window, PRP_TIME_OF_ARRANGE, &No_more );
    }
   else
    {
     return;
    }
  }

 // Выравниваем текстовые окна по середине экрана.
 if( Action == SM_ARRANGE_VIO )
  {
   // Распахиваем окно до наибольшего возможного размера.
   if( Window_placement.cx < X_Screen )
    {
     // Изменяем размер окна.
     BYTE Window_position_is_changed = Arranger_SpreadVIOWindow( Frame_window );

     // Узнаем новый размер и расположение окна.
     if( Window_position_is_changed ) WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // Задаем новый размер и расположение окна.
   INT X_Size = Window_placement.cx;
   INT Y_Size = Window_placement.cy;
   INT X_Position = 0;
   INT Y_Position = 0;

   if( X_Size > X_Screen )
    {
     INT Normal_frame = FrameWidth( Frame_window );

     X_Position = Normal_frame * (-1);
     Y_Position = Y_Screen - Y_Size + Normal_frame;
    }
   else
    {
     X_Position = ( X_Screen - X_Size ) / 2;
     Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;
    }

   // Если требуется выравнивание:
   if( X_Position != Window_placement.x || Y_Position != Window_placement.y || Window_placement.fl & SWP_MAXIMIZE )
    {
     // Ставим окно-занавеску поверх всех окон.
     // Она могла быть поставлена еще раньше, во время изменения размера окна.
     if( Show_curtain ) ShowCurtainWindow( QueryDesktopWindow() );
     // Задаем новое расположение окна.
     WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
    }

   // Окно должно быть вызвано наверх.
   Activate_window = 1;
  }

 // Выравниваем окна WPS и Object Desktop Archiver.
 if( Action == SM_ARRANGE_WPS )
  {
   // Если окно увеличено - восстанавливаем его.
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     // Восстанавливаем окно.
     PerformAction( Frame_window, RESTORE_ACTION );

     // Узнаем новый размер и расположение окна.
     WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // Задаем новый размер и расположение окна.
   INT X_Size = X_Screen * 3 / 4 + Rnd( TitleBar_height * 2 );
   INT Y_Size = Y_Screen * 3 / 4 + Rnd( TitleBar_height * 2 );
   INT X_Position = ( X_Screen - X_Size ) / 2;
   INT Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;

   // Выравниваем окно WPS по середине экрана.
   // Действие выполняется только для окон, имеющих размер по умолчанию.
   if( Action == SM_ARRANGE_WPS )
    {
     INT Default_width_Min = X_Screen / 1.25;
     INT Default_width_Max = X_Screen / 1.25 + 10;

     // Если требуется выравнивание:
     if( Window_placement.cx >= Default_width_Min && Window_placement.cx <= Default_width_Max )
      {
       // Задаем новое расположение окна.
       WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
      }
     }

   // Окно должно быть вызвано наверх.
   Activate_window = 1;
  }

 // Выравниваем другие окна.
 if( Action == SM_ARRANGE_WIN_LIST )
  {
   // Если окно увеличено - восстанавливаем его.
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     // Восстанавливаем окно.
     PerformAction( Frame_window, RESTORE_ACTION );

     // Узнаем новый размер и расположение окна.
     WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // Задаем новый размер и расположение окна.
   INT X_Size = Window_placement.cx;
   INT Y_Size = Window_placement.cy;
   INT X_Position = ( X_Screen - X_Size ) / 2;
   INT Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;

   // Если требуется выравнивание:
   if( X_Position != Window_placement.x || Y_Position != Window_placement.y || Window_placement.fl & SWP_MAXIMIZE )
    {
     // Задаем новое расположение окна.
     WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
    }
  }

 // Прячем окно-занавеску.
 HideCurtainWindow();

 // Делаем окно выбранным.
 if( Activate_window ) MoveWindowAbove( Frame_window );

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Arranger_ArrangerMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Arranger->Priority = MAKELONG( Class, Delta );
  }

 // Выравниваем окна по середине экрана.
 if( Message->msg >= SM_ARRANGE_FIRST && Message->msg <= SM_ARRANGE_LAST )
  {
   // Узнаем окно рамки и действие.
   HWND Frame_window = (HWND) Message->mp1;
   ULONG Action = Message->msg;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Выравниваем окно.
   Arranger_ArrangeWindows( Action, Frame_window );
  }

 // Возврат.
 return;
}

// ─── Поток для выравнивания окон ───

VOID Arranger_ArrangerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Arranger->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Arranger->Message_queue == NULLHANDLE )
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
   Arranger_ArrangerMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
