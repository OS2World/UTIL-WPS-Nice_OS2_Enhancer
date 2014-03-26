// ─── Воспроизводит звук при нажатии на клавишу ───

VOID Clicker_KeyboardEcho( VOID )
{
 // Вызываем проигрыватель.
 if( FileExists( Clicker.RTSettings.Keyboard_exe ) )
  {
   CHAR Current_directory[ SIZE_OF_PATH ] = ""; GetCurrentPath( Current_directory );

   CHAR Player_path[ SIZE_OF_PATH ] = "";
   strcpy( Player_path, Clicker.RTSettings.Keyboard_exe ); CutNameInPath( Player_path );

   DosSetDefaultDisk( DriveNumberFromPath( Player_path ) ); DosSetCurrentDir( Player_path );
   CHAR Error_string[ 1 ] = ""; RESULTCODES Return_codes;
   DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_BACKGROUND, NULL, NULL, &Return_codes, Clicker.RTSettings.Keyboard_exe );
   DosSetDefaultDisk( DriveNumberFromPath( Current_directory ) ); DosSetCurrentDir( Current_directory );
  }

 // Возврат.
 return;
}

// ─── Переносит файл со звуком от клавиатуры на диск в памяти ───

VOID Clicker_CopyEchoFileToRAMDrive( VOID )
{
 // Узнаем диск в памяти.
 CHAR Memory_drive_directory[ SIZE_OF_PATH ] = ""; FindRAMDrive( Memory_drive_directory );

 // Если он есть:
 if( Memory_drive_directory[ 0 ] != 0 )
  {
   // Узнаем временный каталог.
   CHAR Temp_directory[ SIZE_OF_PATH ] = ""; QueryTempDirectory( Temp_directory );

   // Если он не задан - считаем, что это корень RAM-диска.
   if( Temp_directory[ 0 ] == 0 ) strcpy( Temp_directory, Memory_drive_directory );

   // Если временный каталог расположен на RAM-диске - используем его.
   // Это правило применится и в случае, если было выполнено предыдущее действие.
   UpperCase( Temp_directory );
   if( Temp_directory[ 0 ] == Memory_drive_directory[ 0 ] )
    strcpy( Memory_drive_directory, Temp_directory );

   // Больше с временным каталогом ничего делать не надо.
   Temp_directory[ 0 ] = 0;

   // Удаляем наклонную черту в конце строки, если она есть.
   CutLastSlash( Memory_drive_directory );

   // Переносим файл со звуком и проигрыватель, а также запоминаем новое расположение.
   for( INT Count = 0; Count < 2; Count ++ )
    {
     PCHAR Source_name = "";
     if( Count == 0 ) Source_name = Clicker.RTSettings.Keyboard_wav;
     if( Count == 1 ) Source_name = Clicker.RTSettings.Keyboard_exe;

     CHAR New_name[ SIZE_OF_PATH ] = "";
     strcpy( New_name, Memory_drive_directory ); strcat( New_name, "\\" );
     strcat( New_name, FindNameInPath( Source_name ) );

     DosForceDelete( New_name );
     DosCopy( Source_name, New_name, 0 );

     strcpy( Source_name, New_name );
    }
  }

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Clicker_ClickerMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Clicker->Priority = MAKELONG( Class, Delta );
  }

 // Воспроизводим звук.
 if( Message->msg == SM_CLICK ) if( Clicker.Settings.Keyboard_echo ) Clicker_KeyboardEcho();

 // Возврат.
 return;
}

// ─── Поток для воспроизведения звука при нажатии на клавишу ───

VOID Clicker_ClickerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Clicker->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Clicker->Message_queue == NULLHANDLE )
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
   Clicker_ClickerMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
