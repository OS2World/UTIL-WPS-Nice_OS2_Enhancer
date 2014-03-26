// ─── Создает поток, выполняющий ожидание, и посылает ему сообщение ───

VOID Scroller_StartWaiterToWriteSettings( VOID )
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
   HMQ Owner_queue = Enhancer.Modules.Scroller->Message_queue;
   WinPostQueueMsg( Enhancer.Modules.Waiter->Message_queue, SM_WAIT_SOME_TIME, 0, (MPARAM) Owner_queue );

   // Забываем про него.
   Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
  }

 // Возврат.
 return;
}

// ─── Записывает настройки для передвижения изображения ───

VOID Scroller_WriteSettingsAfterWaiting( VOID )
{
 // Открываем файл настроек.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // Если это сделать не удалось - возврат.
 if( Ini_file == NULLHANDLE ) return;

 // Записываем настройки.
 PrfWriteProfileData( Ini_file, "Scrolling", NULL, NULL, 0 );

 INT Position = 0;
 for( INT Count = 0; Count < SCROLLER_SCRLIST_SIZE; Count ++ )
  if( Scroller.Scrolling_list[ Count ].Name[ 0 ] != 0 )
   if( Scroller.Scrolling_list[ Count ].PreDefined == 0 ) 
    if( Scroller.Scrolling_list[ Count ].Method == SCROLLING_COMMON )
     if( Scroller.Scrolling_list[ Count ].X_Velocity_DD != 0 ) if( Scroller.Scrolling_list[ Count ].X_Velocity_D != 0 )
      if( Scroller.Scrolling_list[ Count ].Y_Velocity_DD != 0 ) if( Scroller.Scrolling_list[ Count ].Y_Velocity_D != 0 )
       if( Scroller.Scrolling_list[ Count ].X_Velocity_DD >= Scroller.Scrolling_list[ Count ].X_Velocity_D )
        if( Scroller.Scrolling_list[ Count ].Y_Velocity_DD >= Scroller.Scrolling_list[ Count ].Y_Velocity_D )
         if( Scroller.Scrolling_list[ Count ].X_Velocity_DD / Scroller.Scrolling_list[ Count ].X_Velocity_D < SCROLLER_MAX_VELOCITY_DD_D )
          if( Scroller.Scrolling_list[ Count ].Y_Velocity_DD / Scroller.Scrolling_list[ Count ].Y_Velocity_D < SCROLLER_MAX_VELOCITY_DD_D )
           {
            CHAR Number[ 25 ] = ""; itoa( Position, Number, 10 ); CHAR Setting_name[ 25 ] = "";

            strcpy( Setting_name, Number ); strcat( Setting_name, " N" );
            PrfWriteProfileData( Ini_file, "Scrolling", Setting_name, Scroller.Scrolling_list[ Count ].Name, strlen( Scroller.Scrolling_list[ Count ].Name ) + 1 );

            strcpy( Setting_name, Number ); strcat( Setting_name, " X DD" );
            PrfWriteProfileData( Ini_file, "Scrolling", Setting_name, &Scroller.Scrolling_list[ Count ].X_Velocity_DD, sizeof( INT ) );
            strcpy( Setting_name, Number ); strcat( Setting_name, " X D" );
            PrfWriteProfileData( Ini_file, "Scrolling", Setting_name, &Scroller.Scrolling_list[ Count ].X_Velocity_D, sizeof( INT ) );

            strcpy( Setting_name, Number ); strcat( Setting_name, " Y DD" );
            PrfWriteProfileData( Ini_file, "Scrolling", Setting_name, &Scroller.Scrolling_list[ Count ].Y_Velocity_DD, sizeof( INT ) );
            strcpy( Setting_name, Number ); strcat( Setting_name, " Y D" );
            PrfWriteProfileData( Ini_file, "Scrolling", Setting_name, &Scroller.Scrolling_list[ Count ].Y_Velocity_D, sizeof( INT ) );

            Position ++;
           }

 // Удаляем настройки предыдущих версий.
 PrfWriteProfileData( Ini_file, "ScrList", NULL, NULL, 0 );

 // Закрываем файл настроек.
 PrfCloseProfile( Ini_file ); Ini_file = NULLHANDLE;

 // Возврат.
 return;
}
