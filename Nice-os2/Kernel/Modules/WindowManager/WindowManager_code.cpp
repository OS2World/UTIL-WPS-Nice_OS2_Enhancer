
// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID WindowManager_WindowManagerMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.WindowManager->Priority = MAKELONG( Class, Delta );
  }

 // Выполняем определенное действие.
 if( Message->msg == SM_PERFORM_ACTION )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;
   LONG Command = (LONG) Message->mp2;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Выполняем действие.
   PerformAction( Frame_window, Command, 0, PA_METHOD_CALLED_BY_WINDOW_MANAGER );
  }

 // Скрываем или прячем окно.
 if( Message->msg == SM_HIDE_WINDOW_AWAY )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Выполняем действие.
   HideWindowAway( Frame_window );
  }

 // Делаем выбранным окно в середине экрана.
 if( Message->msg == SM_ACTIVATE_ANYTHING )
  {
   // Ждем некоторое время.
   Retard();

   // Делаем выбранным окно в середине экрана.
   ActivateWindowInCenter();
  }

 // Делаем выбранным окно в середине экрана после смены комнат.
 if( Message->msg == SM_RETARD_AND_ACTIVATE )
  {
   // Узнаем комнату, выбранную пользователем.
   INT Room = GetCurrentOrNextRoom();

   // Уменьшаем приоритет.
   DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MINIMUM, 0 );

   // Ждем некоторое время.
   for( INT Count = 0; Count < 5; Count ++ ) Retard();

   // Восстанавливаем приоритет.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.WindowManager->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.WindowManager->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Если пользователь выбрал другую комнату, вызвал окно WarpCenter или список окон - ничего делать не надо.
   BYTE Activate_window_in_center = 1;
   if( Activate_window_in_center ) if( Room != GetCurrentOrNextRoom() ) Activate_window_in_center = 0;
   if( Activate_window_in_center ) if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW | FIND_ALL_TOOLBAR_MENUS | FIND_WINDOW_LIST | FIND_LSWITCHER_PANEL, FIND_VISIBLE_WINDOW ) ) Activate_window_in_center = 0;

   // Делаем выбранным окно в середине экрана.
   if( Activate_window_in_center ) ActivateWindowInCenter();

   // Выставляем приоритеты для приложений.
   SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS );
  }

 // Возврат.
 return;
}

// ─── Поток для обработки нажатий на кнопки ───

VOID WindowManager_WindowManagerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.WindowManager->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.WindowManager->Message_queue == NULLHANDLE )
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
   WindowManager_WindowManagerMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
