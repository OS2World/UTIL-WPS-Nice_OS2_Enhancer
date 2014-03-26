
// ─── Узнает, должно ли это окно удаляться из списка окон ───

// WinList_title - название в списке окон.
BYTE Remover_WindowWillBeHidden( PCHAR WinList_title )
{
 // Если надо удалять строки из списка окон:
 if( Remover.Settings.Remove_items_from_Window_list )
  {
   // Проверяем окно.
   for( INT Item_count = 0; Item_count < 8; Item_count ++ )
    {
     PCHAR Item_name = Remover.Settings.WinListNames.Remove_from_list_1_name;
     if( Item_count == 1 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_2_name;
     if( Item_count == 2 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_3_name;
     if( Item_count == 3 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_4_name;
     if( Item_count == 4 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_5_name;
     if( Item_count == 5 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_6_name;
     if( Item_count == 6 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_7_name;
     if( Item_count == 7 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_8_name;

     if( Item_name[ 0 ] != 0 )
      if( strifind( Item_name, WinList_title ) ) return 1;
    }
  }

 // Возврат.
 return 0;
}

// ─── Скрывает или показывает строки в списке окон ───

// Show_items - скрыть или показать строки, Hide_known_applications - скрыть известные приложения.
VOID Remover_ShowAllItemsInSwitchList( BYTE Show_or_hide, BYTE Hide_known_applications = 0 )
{
 // Окно оболочки прятать нельзя.
 PCHAR Shell_window_item = NULL;

 if( ShellIsWPS() )
  {
   // Узнаем окно оболочки.
   HWND Shell_window = GetDetectedShellWindow();

   if( Shell_window != NULLHANDLE )
    {
     // Узнаем, есть ли оно в списке окон.
     HSWITCH Switch_handle = WinQuerySwitchHandle( Shell_window, NULLHANDLE );
     SWCNTRL Task; bzero( &Task, sizeof( SWCNTRL ) );

     // Если его нет - добавляем его.
     if( Switch_handle == NULLHANDLE )
      {
       Task.hwnd = Shell_window;
       GetDefaultShellTitle( Task.szSwtitle );

       Task.uchVisibility = SWL_VISIBLE;
       Task.fbJump = SWL_JUMPABLE;

       HSWITCH Switch_handle = WinAddSwitchEntry( &Task );
      }
     // Если оно есть - делаем его видимым в списке.
     else
      {
       WinQuerySwitchEntry( Switch_handle, &Task );

       if( Task.uchVisibility != SWL_VISIBLE || Task.fbJump != SWL_JUMPABLE )
        ShowItemInSwitchList( Switch_handle, Task, 1 );
      }

     // Запоминаем строку.
     Shell_window_item = Task.szSwtitle;
    }
  }

 // Узнаем список окон.
 PSWBLOCK SWBlock = NULL; QuerySwitchList( &SWBlock );

 // Показываем или скрываем строки.
 {
  INT Count; INT Item_count;

  for( Count = 0; Count < SWBlock->cswentry; Count ++ )
   {
    BYTE Hide_this_item = 0;

    // Скрываем приложения, известные расширителю.
    if( Hide_known_applications )
     {
      HWND Frame_window = SWBlock->aswentry[ Count ].swctl.hwnd;

      if( !Hide_this_item && IsECenterWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IsWarpCenterWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IsLaunchPadWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IslSwitcherWindow( Frame_window ) ) Hide_this_item = 1;

      if( !Hide_this_item && ShellIsWPS() )
       {
        if( WindowIsUsedTo( DO_IMPROVE_WORKPLACE, Frame_window ) )
         if( !WindowIsCreatedBy( APP_NICE, Frame_window ) )
          Hide_this_item = 1;

        if( !Hide_this_item && IsSysTrayWindow( Frame_window ) ) Hide_this_item = 1;
        if( !Hide_this_item && IsSmartBarWindow( Frame_window ) ) Hide_this_item = 1;
       }
     }

    // Скрываем приложения, заданные пользователем.
    for( Item_count = 0; Item_count < 8; Item_count ++ )
     {
      PCHAR Item_name = Remover.Settings.WinListNames.Remove_from_list_1_name;
      if( Item_count == 1 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_2_name;
      if( Item_count == 2 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_3_name;
      if( Item_count == 3 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_4_name;
      if( Item_count == 4 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_5_name;
      if( Item_count == 5 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_6_name;
      if( Item_count == 6 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_7_name;
      if( Item_count == 7 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_8_name;

      if( Item_name[ 0 ] != 0 )
       {
        PCHAR Title = SWBlock->aswentry[ Count ].swctl.szSwtitle;

        #ifndef INCLUDED_BY_SHELL

        if( Shell_window_item != NULL )
         if( strcmp( Title, Shell_window_item ) == EQUALLY ) continue;

        #endif

        if( strcmp( Title, Item_name ) == EQUALLY ) Hide_this_item = 1;
       }

       if( Hide_this_item ) break;
     }

    // Скрываем строки.
    if( Hide_this_item )
     {
      HSWITCH Switch_handle = SWBlock->aswentry[ Count ].hswitch;
      SWCNTRL Task = SWBlock->aswentry[ Count ].swctl;

      ShowItemInSwitchList( Switch_handle, Task, Show_or_hide );
     }
   }
 }

 // Освобождаем память.
 FreeSwitchListMemory( SWBlock ); SWBlock = NULL;

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Remover_RemoverMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Remover->Priority = MAKELONG( Class, Delta );
  }

 // Скрываем строки в списке окон.
 if( Message->msg == SM_REMOVE_ITEMS ) Remover_ShowAllItemsInSwitchList( 0, Remover.Settings.Hide_known_applications );

 // Возврат.
 return;
}


// ─── Поток для удаления строк из списка окон ───

VOID Remover_RemoverThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Remover->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Remover->Message_queue == NULLHANDLE )
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
   Remover_RemoverMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
