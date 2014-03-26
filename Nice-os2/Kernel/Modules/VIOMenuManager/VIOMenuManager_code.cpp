// ─── Читает команды из файла ───

// Все переменные - внешние.
VOID VIOMenuManager_ReadSSHCommandFile( INT File_number, PFILESTATUS3 Attributes )
{
 // Пробуем открыть файл.
 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READONLY;

 HFILE File = NULLHANDLE; ULONG Report = 0;
 PCHAR File_name = VIOMenuManager.Settings.Files[ File_number ];
 APIRET RC = DosOpen( File_name, &File, &Report, 0, FILE_NORMAL, Action, Mode, NULL );

 // Если файл не был открыт - возврат.
 if( RC != NO_ERROR ) return;

 // Отводим память для текста.
 PCHAR Text = NULL; ULONG Length = ( MAX_VIO_MENU_COMMANDS * SIZE_OF_ITEM_TEXT ) * 2;
 if( DosAllocMem( (PPVOID) &Text, Length, PAG_ALLOCATE ) != NO_ERROR ) { DosClose( File ); return; }

 // Читаем содержимое файла.
 memset( Text, 0, Length );
 DosRead( File, Text, Length, &Length );

 // Закрываем файл.
 DosClose( File ); File = NULLHANDLE;

 // Если файл что-то содержит:
 if( Length  > 0 )
  {
   // Если файл не начинается с '#' - возврат.
   if( Text[ 0 ] != '#' ) { DosFreeMem( Text ); return; }

   // Если в файле встречаются нулевые символы - возврат.
   for( INT Position = 0; Position < Length; Position ++ )
    if( Text[ Position ] == 0 ) { DosFreeMem( Text ); return; }

   // Оставляем только буквы и цифры, символы "0x0A" забиваем нулями.
   // При этом последовательность "0x0D:0x0A" дает лишнюю пустую строку.
   for( Position = 0; Position < Length; Position ++ )
    {
     if( Text[ Position ] == 0x0D ) { Text[ Position ] = 0; continue; }
     if( Text[ Position ] == 0x0A ) { Text[ Position ] = 0; continue; }

     if( Text[ Position ] < ' ' ) { Text[ Position ] = ' '; continue; }
     if( Text[ Position ] > '~' ) { Text[ Position ] = ' '; continue; }
    }

   // Расставляем указатели на строки.
   PCHAR Strings[ MAX_VIO_FILE_STRINGS ]; bzero( Strings, sizeof( Strings ) );

   INT Strings_quantity = 0;

   {
    Strings[ Strings_quantity ] = &Text[ 0 ]; Strings_quantity ++;

    for( Position = 0; ( Position < Length - 1 ) && ( Strings_quantity < MAX_VIO_FILE_STRINGS ); Position ++ )
     {
      if( Text[ Position ] == 0 && Text[ Position + 1 ] != 0 )
       {
        Strings[ Strings_quantity ] = &Text[ Position + 1 ];
        Strings_quantity ++;
       }
     }
   }

   // Если строки действительно есть:
   if( Strings_quantity )
    {
     // Стираем все данные для этого файла.
     {
      for( INT Count = 0; Count < MAX_VIO_MENU_TITLES; Count ++ )
       VIOMenuManager.RTSettings.Files[ File_number ].Titles[ Count ][ 0 ] = 0;

      for( Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++ )
       VIOMenuManager.RTSettings.Files[ File_number ].Commands[ Count ][ 0 ] = 0;
     }

     // Запоминаем строки, содержащие заголовки окон.
     {
      INT Required_string_length = strlen( "# SSH" );

      INT Titles_quantity = 0;

      for( INT Number = 0; ( Number < Strings_quantity ) && ( Titles_quantity < MAX_VIO_MENU_TITLES ); Number ++ )
       {
        if( Strings[ Number ] == NULL ) continue;
        if( strlen( Strings[ Number ] ) < Required_string_length ) continue;

        if( Strings[ Number ][ 0 ] == '#' )
         {
          INT Offset = 1;
          if( Strings[ Number ][ Offset ] == ' ' ) Offset ++;

          if( Strings[ Number ][ Offset ] )
           {
            strncpy( VIOMenuManager.RTSettings.Files[ File_number ].Titles[ Titles_quantity ], &Strings[ Number ][ Offset ], SIZE_OF_NAME );
            Titles_quantity ++;
           }
         }
        else
         {
          break;
         }
       }
     }

     // Запоминаем строки, содержащие команды.
     {
      INT Required_string_length = strlen( "ls" );

      INT Commands_quantity = 0;

      for( INT Number = 0; ( Number < Strings_quantity ) && ( Commands_quantity < MAX_VIO_MENU_COMMANDS ); Number ++ )
       {
        if( Strings[ Number ] == NULL ) continue;
        if( strlen( Strings[ Number ] ) < Required_string_length ) continue;

        if( Strings[ Number ][ 0 ] == '#' )
         {
          continue;
         }
        else
         {
          if( Strings[ Number ] )
           {
            strncpy( VIOMenuManager.RTSettings.Files[ File_number ].Commands[ Commands_quantity ], Strings[ Number ], SIZE_OF_ITEM_TEXT );
            Commands_quantity ++;
           }
         }
       }
     }
    }
  }

 // Освобождаем память.
 DosFreeMem( Text ); Text = NULL;

 // Делаем запись "включенной".
 VIOMenuManager.RTSettings.Files[ File_number ].Active = 1;

 // Запоминаем время изменения файла.
 VIOMenuManager.RTSettings.Files[ File_number ].Date.year    = Attributes->fdateLastWrite.year;
 VIOMenuManager.RTSettings.Files[ File_number ].Date.month   = Attributes->fdateLastWrite.month;
 VIOMenuManager.RTSettings.Files[ File_number ].Date.day     = Attributes->fdateLastWrite.day;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.hours   = Attributes->ftimeLastWrite.hours;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.minutes = Attributes->ftimeLastWrite.minutes;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.twosecs = Attributes->ftimeLastWrite.twosecs;

 // Возврат.
 return;
}

// ─── Читает команды из файлов настроек ───

VOID VIOMenuManager_PrepareOrUpdateSSHCommandSet( VOID )
{
 // Просматриваем список файлов и читаем их, если требуется.
 for( INT File_number = 0; File_number < MAX_VIO_MENU_FILES; File_number ++ )
  {
   // Если имя файла не задано - продолжаем перебор.
   PCHAR File_name = VIOMenuManager.Settings.Files[ File_number ];
   if( File_name[ 0 ] == 0 ) continue;

   // Узнаем свойства файла.
   FILESTATUS3 Attributes; memset( &Attributes, 0, sizeof( Attributes ) );
   APIRET RC = DosQueryPathInfo( File_name, FIL_STANDARD, &Attributes, sizeof( Attributes ) );

   // Если файла нет - делаем запись "выключенной" и продолжаем перебор.
   if( RC != NO_ERROR )
    {
     VIOMenuManager.RTSettings.Files[ File_number ].Active = 0;
     continue;
    }

   // Смотрим, надо ли считывать файл.
   BYTE Read_file = 0;
   BYTE Update_file = 0;

   // Проверяем, "включена" ли запись для этого файла.
   BYTE Record_is_active = VIOMenuManager.RTSettings.Files[ File_number ].Active;
   if( !Record_is_active ) Read_file = 1;

   // Проверяем, есть ли хоть одна команда для этого файла.
   PCHAR First_command = VIOMenuManager.RTSettings.Files[ File_number ].Commands[ 0 ];
   if( First_command[ 0 ] == 0 ) Read_file = 1;

   // Проверяем время изменения файла.
   if( !Read_file )
    {
     if( Attributes.fdateLastWrite.year    != VIOMenuManager.RTSettings.Files[ File_number ].Date.year    ) Update_file = 1;
     if( Attributes.fdateLastWrite.month   != VIOMenuManager.RTSettings.Files[ File_number ].Date.month   ) Update_file = 1;
     if( Attributes.fdateLastWrite.day     != VIOMenuManager.RTSettings.Files[ File_number ].Date.day     ) Update_file = 1;
     if( Attributes.ftimeLastWrite.hours   != VIOMenuManager.RTSettings.Files[ File_number ].Time.hours   ) Update_file = 1;
     if( Attributes.ftimeLastWrite.minutes != VIOMenuManager.RTSettings.Files[ File_number ].Time.minutes ) Update_file = 1;
     if( Attributes.ftimeLastWrite.twosecs != VIOMenuManager.RTSettings.Files[ File_number ].Time.twosecs ) Update_file = 1;
    }

   // Читаем файл, если это требуется.
   if( Read_file || Update_file ) VIOMenuManager_ReadSSHCommandFile( File_number, &Attributes );
  }

 // Возврат.
 return;
}

// ─── Проверяет, есть ли в списке строки, соответствующие окну ───

// Frame_window - окно рамки.
BYTE VIOMenuManager_CheckCommandSubset( HWND Frame_window )
{
 // Узнаем, какие строки будут добавлены в окно.
 INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

 // Проверяем, есть ли они.
 if( File_number == -1 ) return 0;
 if( VIOMenuManager.RTSettings.Files[ File_number ].Active == 0 ) return 0;
 if( VIOMenuManager.RTSettings.Files[ File_number ].Commands[ 0 ][ 0 ] == 0 ) return 0;

 // Возврат.
 return 1;
}

// ─── Отправляет команду в окно ───

// Frame_window - окно рамки, Position - номер строки в списке команд.
VOID VIOMenuManager_PostCommandCharacters( HWND Frame_window, ULONG Position )
{
 // Если известны команды для этого окна:
 INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

 if( File_number != -1 )
  {
   // Если номер задан верно:
   if( Position >= 0 && Position < MAX_VIO_MENU_COMMANDS )
    {
     // Узнаем окно рабочей области.
     HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

     // Перебираем буквы в строке.
     PCHAR String = VIOMenuManager.RTSettings.Files[ File_number ].Commands[ Position ];
     INT Length = strlen( String );

     for( INT Count = 0; Count < Length; Count ++ )
      {
       // Выбираем букву.
       CHAR Character = String[ Count ];

       // Посылаем "~" только в случае, если это последняя буква в строке, а также если за ней
       // стоит еще одна "~" или пробел. При этом нельзя выходить за последнюю букву в строке.
       if( Character == '~' )
        {
         BYTE Post_Tilde = 0;
         if( !Post_Tilde ) if( Count == Length - 1 ) Post_Tilde = 1;
         if( !Post_Tilde ) if( String[ Count + 1 ] == '~' ) Post_Tilde = 1;
         if( !Post_Tilde ) if( String[ Count + 1 ] == ' ' ) Post_Tilde = 1;
         if( !Post_Tilde ) continue;
        }

       // Составляем сообщение о нажатии клавиши.
       MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
       ComposeWMCharMessageForVIOWindow( &First_parameter_1, &Second_parameter_1, 0, Character );

       // Посылаем его.
       WinPostMsg( Client_window, WM_CHAR, First_parameter_1, Second_parameter_1 );
      }
    }
  }

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID VIOMenuManager_VIOMenuManagerMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.VIOMenuManager->Priority = MAKELONG( Class, Delta );
  }

 // Читаем строки меню для окон SSH из файлов настроек.
 if( Message->msg == SM_CHECK_ALL_COMMANDS )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Узнаем, какие сообщения надо отправить в очередь окна.
   INT Markers_quantity = (INT) Message->mp2;

   // Читаем строки и заполняем список.
   // Если строки уже прочитаны - проверяем, изменились ли файлы.
   VIOMenuManager_PrepareOrUpdateSSHCommandSet();

   // Смотрим, есть ли в списке команды для этого окна.
   BYTE Commands_are_present = VIOMenuManager_CheckCommandSubset( Frame_window );

   // Если они были считаны и присутствуют в памяти - можно их добавить и показать:
   if( Commands_are_present )
    {
     // Посылаем в окно одно или два сообщения WM_MARK.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     if( Markers_quantity >= 1 ) WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_ADD_VIO_MENU_ITEMS, (MPARAM) Frame_window );
     if( Markers_quantity == 2 ) WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SHOW_VIO_MENU_ITEMS, (MPARAM) Frame_window );
    }
  }

 // Отправляем команду в окно.
 if( Message->msg == SM_POST_VIO_MENU_ITEM )
  {
   // Узнаем окно рамки.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Узнаем номер строки в списке команд.
   ULONG Position = (ULONG) Message->mp2;

   // Отправляем команду в окно.
   VIOMenuManager_PostCommandCharacters( Frame_window, Position );
  }

 // Возврат.
 return;
}

// ─── Поток для добавления строк в меню текстовых окон ───

VOID VIOMenuManager_VIOMenuManagerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.VIOMenuManager->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.VIOMenuManager->Message_queue == NULLHANDLE )
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
   VIOMenuManager_VIOMenuManagerMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
