
// ─── Меняет значок окна ───

// Frame_window - окно рамки, New_icon - новый значок.
VOID Changer_ChangeWindowIcon( HWND Frame_window, HPOINTER New_icon )
{
 // Узнаем значок, который используется сейчас.
 HPOINTER Current_icon = (HPOINTER) WinSendMsg( Frame_window, WM_QUERYICON, 0, 0 );

 // Меняем его.
 if( Current_icon != New_icon )
  {
   // Задаем новый значок.
   WinSendMsg( Frame_window, WM_SETICON, (MPARAM) New_icon, 0 );

   // Посылаем сообщение в поток рисования.
   WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_SYSMENU );
  }

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Changer_ChangerMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Changer->Priority = MAKELONG( Class, Delta );
  }

 // Меняем значок окна.
 if( Message->msg == SM_CHANGE_ICON )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;
   // Узнаем значок, который должен быть установлен.
   HPOINTER New_icon = (HPOINTER) Message->mp2;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Меняем значок.
   Changer_ChangeWindowIcon( Frame_window, New_icon );
  }

 // Сбрасываем значок, который был загружен с диска.
 if( Message->msg == SM_FREE_FILE_ICON )
  {
   // Узнаем значок.
   HPOINTER Icon = (HPOINTER) Message->mp1;

   // Освобождаем память.
   WinFreeFileIcon( Icon );
  }

 // Делаем окно доступным или недоступным для переключения.
 if( Message->msg == SM_SET_JUMPABLE )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Узнаем свойство.
   ULONG Jumpable = (ULONG) Message->mp2;

   // Меняем его.
   if( Frame_window != GetDetectedShellWindow() ) SetJumpableFlag( Frame_window, Jumpable );
  }

 // Меняем шрифт для текстовых окон - первый и второй шаги.
 if( Message->msg == SM_CHANGE_VIO_FONT || Message->msg == SM_APPLY_VIO_FONT )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если шрифт менять не надо - возврат.
   if( !VIOFontMustBeChanged( Frame_window ) ) return;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Шаг первый: вызываем окно смены шрифта и ждем его появления.
   if( Message->msg == SM_CHANGE_VIO_FONT )
    {
     // Проверяем состояние окна.
     BYTE VIO_font_dialog = 0; FindProperty( Frame_window, PRP_VIO_FONT_DIALOG, &VIO_font_dialog );
     // Если для этого окна уже был вызван диалог выбора шрифта - возврат.
     if( VIO_font_dialog ) return;

     // Вызываем окно смены шрифта.
     OpenVIOFontMetricsDialog( Frame_window );

     // Запоминаем, что окно было показано.
     VIO_font_dialog = 1; SetProperty( Frame_window, PRP_VIO_FONT_DIALOG, &VIO_font_dialog );
    }

   // Шаг второй: выбираем в нем шрифт и применяем его.
   if( Message->msg == SM_APPLY_VIO_FONT )
    {
     // Выбираем шрифт.
     SubmitVIOFontMetricsDialog( Frame_window );
    }
  }

 // Делаем окно видимым.
 if( Message->msg == SM_SHOW_AND_ARRANGE )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна рамки нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Делаем окно видимым.
   if( !WinIsWindowVisible( Frame_window ) ) WinShowWindow( Frame_window, 1 );

   // Если надо выравнивать текстовые окна:
   if( ArrangeVIOWindows() )
    {
     // Посылаем в окно сообщение WM_MARK. Когда оно будет получено, окно можно будет выравнивать.
     WinPostMsg( Frame_window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) SM_ARRANGE_VIO );
    }
  }

 // Возврат.
 return;
}

// ─── Поток для изменения свойств окон ───

VOID Changer_ChangerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Changer->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Changer->Message_queue == NULLHANDLE )
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
   Changer_ChangerMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
