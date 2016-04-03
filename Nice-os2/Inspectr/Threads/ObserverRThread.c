
// ─── Обрабатывает разобранную строку ───

VOID ObserverR_ProcessReportData( PCHAR Object, PCHAR Exe_name, PCHAR Parameters, PCHAR Work_directory )
{
 // Просматриваем список известных приложений и сравниваем значения.
 INT Count = 0;

 if( stristr( ":\\", Exe_name ) ) Exe_name = FindNameInPath( Exe_name );

 for( Count = 0; Count < Repository.Length; Count ++ )
  {
   if( Repository.Items[ Count ].Object_INI_setting_name[ 0 ] != 0 )
    {
     BYTE Name_is_found = 0; INT Str_count = 0;

     // Пробуем найти имя файла приложения. Путь может указывать на файл "*.exe" или "*.cmd".
     for( Str_count = 0; Str_count < 6; Str_count ++ )
      {
       CHAR Name[ SIZE_OF_NAME ] = "";
       if( Str_count == 0 || Str_count == 3 ) strcpy( Name, Repository.Items[ Count ].Exe_name_1 );
       if( Str_count == 1 || Str_count == 4 ) strcpy( Name, Repository.Items[ Count ].Exe_name_2 );
       if( Str_count == 2 || Str_count == 5 ) strcpy( Name, Repository.Items[ Count ].Exe_name_3 );

       if( Name[ 0 ] != 0 && Name[ 0 ] != '*' )
        {
         if( Str_count > 2 )
          {
           PCHAR Extension = stristr( ".exe", Name );

           if( Extension != NULL )
            {
             *( Extension + 1 ) = 'c';
             *( Extension + 2 ) = 'm';
             *( Extension + 3 ) = 'd';
            }
          }

         if( stric( Name, Exe_name ) ) Name_is_found = 1;
         if( stristr( Name, Parameters ) ) Name_is_found = 1;
        }
      }

     // Пробуем найти ключевое слово.
     for( Str_count = 0; Str_count < 4; Str_count ++ )
      {
       CHAR Name[ SIZE_OF_NAME ] = "";
       if( Str_count == 0 ) strcpy( Name, Repository.Items[ Count ].WPS_keyword_1 );
       if( Str_count == 1 ) strcpy( Name, Repository.Items[ Count ].WPS_keyword_2 );
       if( Str_count == 2 ) strcpy( Name, Repository.Items[ Count ].WPS_keyword_3 );
       if( Str_count == 3 ) strcpy( Name, Repository.Items[ Count ].WPS_keyword_4 );

       if( Name[ 0 ] != 0 )
        {
         if( stristr( Name, Object ) ) Name_is_found = 1;
         if( stristr( Name, Exe_name ) ) Name_is_found = 1;
         if( stristr( Name, Parameters ) ) Name_is_found = 1;
         if( stristr( Name, Work_directory ) ) Name_is_found = 1;
        }
      }

     // Если что-то было найдено - запоминаем значок на рабочем столе и показываем его в окне.
     // Прекращать обработку не надо, так как пользователь может задать свои приложения, похожие
     // на уже присутствующие в списке, и для них надо будет запомнить те же самые значения.
     if( Name_is_found )
      {
       if( !strc( Repository.Items[ Count ].Known_WPS_object, Object ) )
        {
         strcpy( Repository.Items[ Count ].Known_WPS_object, Object );
         Inspector.Write_settings = 1;
        }

       if( InnerLimits.Inserted_lines < MAX_INSERTED_LINES )
        {
         InnerLimits.Inserted_lines ++;

         CHAR Status_string[ SIZE_OF_TITLE ] = "";

         UpperCase( Exe_name ); LowerCase( &Exe_name[ 1 ] );
         strcpy( Status_string, Exe_name );
         strcat( Status_string, " - " );
         strcat( Status_string, Object );

         WinSendDlgItemMsg( Inspector.Client_window, Client_Window.Settings.List_ID, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Status_string ) );
        }
      }
    }
  }

 // Отображаем имя в строке состояния.
 if( WinIsWindowShowing( Inspector.Frame_window ) )
  {
   CHAR Status_string[ SIZE_OF_TITLE ] = ">> "; strcat( Status_string, Object );
   WinSetWindowText( WinWindowFromID( Inspector.Client_window, Client_Window.Settings.Text_ID ), Status_string );
  }

 // Возврат.
 return;
}

// ─── Разбирает строку отчета ───

VOID ObserverR_ParseReportLine( PCHAR Line )
{
 // Разбираем строку и отдаем ее обработчику.
 PCHAR Begin_of_line = strstr( "", Line );
 PCHAR End_of_line = strstr( "", Line );

 if( Begin_of_line != NULL && End_of_line != NULL )
  {
   PCHAR Object = NULL; PCHAR Exe_name = NULL; PCHAR Parameters = NULL; PCHAR Work_directory = NULL;

   Object = Begin_of_line + 1;
   Exe_name = strstr( "■", Object ); *Exe_name = 0; Exe_name ++;
   Parameters = strstr( "■", Exe_name ); *Parameters = 0; Parameters ++;
   Work_directory = strstr( "■", Parameters ); *Work_directory = 0; Work_directory ++;

   ObserverR_ProcessReportData( Object, Exe_name, Parameters, Work_directory );
  }

 // Возврат.
 return;
}

// ─── Читает отчет и завершает просмотр значков на рабочем столе ───

VOID ObserverR_ReadExplorerReport( VOID )
{
 // Читаем вывод от него, пока не будет получен признак конца отчета.
 BYTE Byte = 0xFF; BYTE End_of_report = 0x00; CHAR Line[ SIZE_OF_PATH ] = ""; INT Position = 0;

 while( Byte != End_of_report )
  {
   ULONG Length = 0; Byte = 0; DosRead( Inspector.Pipe_ReadHandle_2, &Byte, 1, &Length );

   if( Byte != 0 )
    {
     BYTE Parse_line = 0;
     if( Byte == '\n' || Byte == 0x0D || Byte == 0x0A ) Parse_line = 1;
     if( Position == SIZE_OF_PATH - 1 ) Parse_line = 1;

     if( !Parse_line )
      {
       Line[ Position ] = Byte; Position ++;
      }
     else
      {
       Line[ Position ] = 0; ObserverR_ParseReportLine( Line );

       Line[ 0 ] = 0; Position = 0;
      }
    }
  }

 // Восстанавливаем потоки ввода/вывода.
 DosResetBuffer( STD_IN );
 DosResetBuffer( STD_OUT );
 DosResetBuffer( STD_ERR );

 DosClose( Inspector.Saved_StdInHandle );  Inspector.Saved_StdInHandle = NULLHANDLE;
 DosClose( Inspector.Saved_StdOutHandle ); Inspector.Saved_StdOutHandle = NULLHANDLE;
 DosClose( Inspector.Saved_StdErrHandle ); Inspector.Saved_StdErrHandle = NULLHANDLE;

 DosClose( Inspector.Pipe_ReadHandle_1 );  Inspector.Pipe_ReadHandle_1 = NULLHANDLE;
 DosClose( Inspector.Pipe_WriteHandle_1 ); Inspector.Pipe_WriteHandle_1 = NULLHANDLE;
 DosClose( Inspector.Pipe_ReadHandle_2 );  Inspector.Pipe_ReadHandle_2 = NULLHANDLE;
 DosClose( Inspector.Pipe_WriteHandle_2 ); Inspector.Pipe_WriteHandle_2 = NULLHANDLE;

 // Возврат.
 return;
}

// ─── Поток для чтения отчета ───

VOID ObserverR_ObserverReportReaderThread( VOID )
{
 // Определяем поток в системе.
 HAB Thread = WinInitialize( 0 );

 // Создаем очередь сообщений - она должна быть в каждом потоке.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 );

 // Если это сделать не удалось - выход.
 if( Thread == NULLHANDLE || Message_queue == NULLHANDLE ) DosExit( EXIT_THREAD, 0 );

 // Читаем отчет и завершаем просмотр значков на рабочем столе.
 DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );
 ObserverR_ReadExplorerReport();
 DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

 // Записываем настройки и завершаем работу приложения.
 Threads_WriteSettingsAndCloseMainWindow();

 // Завершаем поток.
 Inspector.ObserverReportReading = 0;

 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );

 DosExit( EXIT_THREAD, 0 );
}

// ─── Запускает поток для чтения отчета ───

VOID StartObserverReportReading( VOID )
{
 // Если обработка уже идет - возврат.
 if( Inspector.ObserverReportReading ) return;

 // Создаем поток.
 {
  TID Thread_ID = 0; DosCreateThread( &Thread_ID, (PFNTHREAD) ObserverR_ObserverReportReaderThread, 0, 0, 32768 );
 }

 // Запоминаем, что он работает.
 Inspector.ObserverReportReading = 1;

 // Возврат.
 return;
}
