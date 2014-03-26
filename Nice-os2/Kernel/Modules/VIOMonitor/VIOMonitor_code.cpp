
// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID VIOMonitor_VIOMonitorMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.VIOMonitor->Priority = MAKELONG( Class, Delta );
  }

 // Ждем, когда станет известно приложение, создавшее текстовое окно.
 if( Message->msg == SM_MONITOR_VIO )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Ждем, когда станет известно приложение, создавшее окно.
   for( INT Count = 0; Count < VIOMonitor.Constants.Retards_when_VIO_monitoring; Count ++ )
    {
     // Узнаем имя приложения, создавшего окно.
     CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

     // Если его удалось определить:
     if( Exe_name[ 0 ] != 0 )
      {
       // Сообщаем другим потокам о том, что имя приложения известно.
       LONG Command = (LONG) Message->mp2; HMQ Thread_queue = NULLHANDLE;

       switch( Command )
        {
         case SM_CHANGE_VIO_FONT: Thread_queue = Enhancer.Modules.Changer->Message_queue; break;
        }

       if( Thread_queue != NULLHANDLE ) WinPostQueueMsg( Thread_queue, Command, (MPARAM) Frame_window, 0 );

       // Возврат.
       return;
      }

     // Ждем некоторое время.
     Retard();

     // Если окна нет - возврат.
     if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;
    }
  }

 // Возврат.
 return;
}

// ─── Поток для слежения за текстовыми окнами ───

VOID VIOMonitor_VIOMonitorThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.VIOMonitor->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.VIOMonitor->Message_queue == NULLHANDLE )
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
   VIOMonitor_VIOMonitorMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
