// Внутренние переменные.
typedef struct _PROCESSORTHRD
 {
  // Обработка файлов.
  TID Processor;
  HMQ Processor_queue;
  HAB Processor_anchor;

  // Текущий путь.
  CHAR Static_path[ SIZE_OF_PATH ];
 }
PROCESSORTHRD; PROCESSORTHRD Processor_Thread;

// ─── Подбирает для файла лучшее имя. ───

// Возвращаемое значение - есть ли лучшее имя, 1 или 0.
BYTE Processor_QueryBetterName( PCHAR Short_name )
{
 // Если имя "os2" - делаем эти буквы заглавными.
 if( stricmpe( Short_name, "os2" ) == EQUALLY )
  {
   Short_name[ 0 ] = 'O';
   Short_name[ 1 ] = 'S';

   return 1;
  }

 // Также можно переименовать другие файлы.
 if( stricmpe( Short_name, "wp root. sf" ) == EQUALLY ) { strcpy( Short_name, "WP Root. sf" ); return 1; }
 if( stricmpe( Short_name, "ea data. sf" ) == EQUALLY ) { strcpy( Short_name, "EA Data. sf" ); return 1; }

 if( stricmpe( Short_name, "psfonts" ) == EQUALLY )     { strcpy( Short_name, "PSFonts" );     return 1; }
 if( stricmpe( Short_name, "lotusw4" ) == EQUALLY )     { strcpy( Short_name, "LotusW4" );     return 1; }
 if( stricmpe( Short_name, "xfree86" ) == EQUALLY )     { strcpy( Short_name, "XFree86" );     return 1; }

 // Возврат.
 return 0;
}

// ─── Обрабатывает файл ───

VOID Processor_ProcessFile( PCHAR File_name )
{
 // Корень диска и каталог, с которого начинается обработка, трогать не нужно.
 if( stricmpe( File_name, Names.Task.Root_directory ) == EQUALLY ) return;

 {
  // Выбираем имя файла.
  PCHAR Name_in_path = FindNameInPath( File_name ); CHAR Better_name[ SIZE_OF_PATH ] = "";

  // Если имя не найдено - возврат.
  if( Name_in_path == NULL ) return;

  // Приводим имена к правильному виду.
  if( Names.Task.Convert_names )
   {
    // Если в имени есть заглавные и строчные буквы - их надо сохранить.
    BYTE Convert_name = 0;

    if( Name_in_path[ 0 ] != '.' && strfind( ".", Name_in_path ) )
     {
      strcpy( Better_name, Name_in_path ); UpperCase( Better_name );
      if( strcmp( Better_name, Name_in_path ) == EQUALLY ) Convert_name = 1;
     }

    // Если файл можно обработать:
    if( Convert_name )
     {
      // Проверяем, есть ли для файла лучшее имя.
      BYTE Better_name_is_exists = 0;
      strcpy( Better_name, Name_in_path );
      Better_name_is_exists = Processor_QueryBetterName( Better_name );

      // Если его нет - приводим имя к правильному виду.
      if( !Better_name_is_exists ) MixedCase( Better_name );

      // Если имя изменилось - переименовываем файл.
      if( strcmp( Name_in_path, Better_name ) != EQUALLY )
       {
        strcpy( Name_in_path, Better_name );

        {
         APIRET Report = DosMove( File_name, File_name );
         if( Report != NO_ERROR )
          {
           DosReplaceModule( File_name, NULL, NULL );
           DosMove( File_name, File_name );
          }
        }
       }
     }
   }

 // Делаем имя значка таким же, как имя файла.
 if( Names.Task.Revise_differences )
  {
   BYTE Convert_name = 1;
   if( stricmpe( &File_name[ 1 ], ":\\OS2\\Bitmap" ) == EQUALLY ) Convert_name = 0;

   if( Convert_name ) DiscardEA( File_name, ".LONGNAME" );
  }

 // Удаляем изображения для файлов, которые и так их содержат.
 if( Names.Task.Remove_images )
  {
   PCHAR Extensions[] = { ".bmp",  ".cur",  ".dcx",  ".fit",  ".gif",  ".ico",  ".iff",  ".jpg", \
                          ".jpeg", ".lgo",  ".mac",  ".msp",  ".pbm",  ".pcd",  ".pcx",  ".pgm", \ 
                          ".pic",  ".png",  ".pnm",  ".ppm",  ".ptr",  ".ras",  ".rle",  ".sgi", \ 
                          ".shw",  ".tga",  ".tif",  ".tiff", ".wpg",  ".xbm",  ".xpm",  ".xwd" };
   INT Quantity = 32; BYTE Process_file = 0; INT Count;

   for( Count = 0; Count < Quantity; Count ++ )
    if( strifind( Extensions[ Count ], Name_in_path ) ) Process_file = 1;

   if( Process_file )
    if( strifind( ".ico", Name_in_path ) || strifind( ".ptr", Name_in_path ) )
     {
      DiscardEA( File_name, ".ICON" );
     }
    else
     {
      DiscardEA( File_name, ".MMPREF_MMIMAGE" );
      DiscardEA( File_name, "GRPHFILEINFO" );
     }
  }

 // Удаляем настройки для файлов с изображениями и звуком.
 if( Names.Task.Remove_images )
  {
   PCHAR Extensions[] = { ".mpg", ".avi", ".mid", ".wav" };
   INT Quantity = 4; BYTE Process_file = 0; INT Count;

   for( Count = 0; Count < Quantity; Count ++ )
    if( strifind( Extensions[ Count ], Name_in_path ) ) Process_file = 1;

   if( Process_file ) DiscardEA( File_name, ".MMPREF_MMGENERIC" );
  }

 // Сбрасываем "тип", если есть расширение.
 if( Names.Task.Remove_types )
  {
   if( strfind( ".", File_name ) )
    {
     DiscardEA( File_name, ".TYPE" );

     DiscardEA( File_name, "MR.ED.TXTPOS" );
     DiscardEA( File_name, "MR.ED.MB0" );
     DiscardEA( File_name, "MR.ED.MB1" );
     DiscardEA( File_name, "MR.ED.MB2" );
     DiscardEA( File_name, "MR.ED.MB3" );
     DiscardEA( File_name, "MR.ED.MB4" );
     DiscardEA( File_name, "MR.ED.MB5" );

     DiscardEA( File_name, ".APPTYPE" );
     DiscardEA( File_name, ".CHECKSUM" );

     if( strifind( ".dll", File_name ) ) DiscardEA( File_name, ".ICON" );
    }
  }

 // Сбрасываем атрибут "Read only".
 if( Names.Task.Turn_OFF_ReadOnly )
  {
   FILESTATUS3 Attributes = {0};
   DosQueryPathInfo( File_name, FIL_STANDARD, &Attributes, sizeof( Attributes ) );

   if( Attributes.attrFile & FILE_READONLY )
    {
     Attributes.attrFile &= ~FILE_READONLY;
     DosSetPathInfo( File_name, FIL_STANDARD, &Attributes, sizeof( Attributes ), 0 );
    }
  }

  // Отображаем имя в строке состояния.
  if( WinIsWindowVisible( Names.Frame_window ) && WinIsWindowShowing( Names.Frame_window ) )
   {
    Names.Settings.InputField_is_locked = 1;
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_FIELD ), Name_in_path );
    Names.Settings.InputField_is_locked = 0;
   }
 }

 // Если обработка должна быть прекращена - завершаем поток.
 if( !Names.Processing )
  {
   // Отображаем путь в строке состояния.
   if( strlen( Names.Task.Root_directory ) == 2 ) { Names.Task.Root_directory[ 2 ] = '\\'; Names.Task.Root_directory[ 3 ] = 0; }
    {
     Names.Settings.InputField_is_locked = 1;
     WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_FIELD ), Names.Task.Root_directory );
     Names.Settings.InputField_is_locked = 0;
    }

   if( Names.Settings.Code_page == RUSSIAN )
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_RU_Path ); 
   else
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_EN_Path ); 

   // На кнопке "Стоп" будет надпись "Выход".
   if( Names.Settings.Code_page == RUSSIAN )
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Exit );
   else
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Exit );

   // Завершаем поток.
   WinDestroyMsgQueue( Processor_Thread.Processor_queue );
   WinTerminate( Processor_Thread.Processor_anchor );
   Processor_Thread.Processor = NULLHANDLE;
   DosExit( EXIT_THREAD, 0 );
  }

 // Возврат.
 return;
}

// ─── Составляет полное имя файла. ───

VOID Processor_MakePathname( PCHAR Static_path, PCHAR Path, PCHAR Name )
{
 // Составляем имя.
 if( Path[ 0 ] == 0 ) strcpy( Processor_Thread.Static_path, Name );
 else
  {
   strcpy( Processor_Thread.Static_path, Path );
   strcat( Processor_Thread.Static_path, "\\" );
   strcat( Processor_Thread.Static_path, Name );
  }

 // Возврат.
 return;
}

// ─── Выполняет поиск файлов ───

// Path - путь, с которого надо начать поиск, Include_dirs - надо ли обрабатывать каталоги.
VOID FindFiles( PCHAR Path, BYTE Include_dirs )
{
 PCHAR Path_mask = NULL; APIRET Report = NO_ERROR;

 // Если файлы в каталоге обрабатывать нельзя - возврат.
 if( !Permission( Path ) ) return;

 // Задаем имена для поиска.
 Report = DosAllocMem( (PPVOID) &Path_mask, strlen( Path ) + SIZE_OF_NAME, PAG_ALLOCATE );

 if( Report != NO_ERROR ) return;

 if( Path[ 0 ] == 0 ) strcpy( Path_mask, "*" );
 else
  {
   strcpy( Path_mask, Path );

   if( strcmp( Path, "*" ) != EQUALLY ) if( Path[ strlen( Path ) - 1 ] != '\\' )
    strcat( Path_mask, "\\*" );
  }

 {
  // Находим первый файл.
  HDIR Directory = HDIR_CREATE;
  ULONG All_files = FILE_READONLY | FILE_HIDDEN | FILE_SYSTEM | FILE_ARCHIVED;
  FILEFINDBUF3 Find_buffer = { 0 };
  ULONG Buffer_length = sizeof( FILEFINDBUF3 );
  ULONG Find_count = 1;

  APIRET Report = DosFindFirst( Path_mask, &Directory, All_files, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // Если файлов нет - переходим к перебору каталогов.
  BYTE Perform_directory_search = 0;
  if( Report == ERROR_NO_MORE_FILES ) Perform_directory_search = 1;
  // А если файл найден - обрабатываем его.
  else
   if( Report == NO_ERROR )
    {
     Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
     Processor_ProcessFile( Processor_Thread.Static_path );
    }
   else
    {
     DosFindClose( Directory );

     DosFreeMem( Path_mask );
     return;
    }

   // Перебираем файлы.
   if( !Perform_directory_search )
    while( Report == NO_ERROR )
     {
      // Находим следующий файл.
      Find_count = 1;
      Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

      // Обрабатываем его.
      if( Report == NO_ERROR )
       {
        Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
        Processor_ProcessFile( Processor_Thread.Static_path );
       }
     }

  // Завершаем поиск.
  DosFindClose( Directory );

  // Перебор каталогов. Находим первый каталог.
  Directory = HDIR_CREATE;
  Find_count = 1;

  Report = DosFindFirst( Path_mask, &Directory, All_files | MUST_HAVE_DIRECTORY, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // Если каталог найден - обрабатываем его.
  if( Report == NO_ERROR )
   {
    Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
    if( Include_dirs ) if( Path[ 0 ] != 0 ) Processor_ProcessFile( Path );
   }
  else
   {
    DosFindClose( Directory );

    DosFreeMem( Path_mask );
    return;
   }

  // Перебираем каталоги.
  while( Report == NO_ERROR )
   {
    // Находим следующий каталог.
    Find_count = 1;
    Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

    // Обрабатываем его.
    if( Report == NO_ERROR )
     {
      if( strcmp( Find_buffer.achName, "." ) == EQUALLY ) continue;
      if( strcmp( Find_buffer.achName, ".." ) == EQUALLY ) continue;
      Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
     }
    else break;

    // Чтобы обработать файлы в этом каталоге, вызываем FindFiles() повторно.
    {
     PCHAR New_path = NULL;
     APIRET Report = DosAllocMem( (PPVOID) &New_path, strlen( Processor_Thread.Static_path ) + SIZE_OF_NAME, PAG_ALLOCATE );

     if( Report == NO_ERROR )
      {
       strcpy( New_path, Processor_Thread.Static_path );
       FindFiles( New_path, Include_dirs );
       DosFreeMem( New_path );
      }
    }
   }

  // Завершаем поиск.
  DosFindClose( Directory );
 }

 // Освобождаем память.
 DosFreeMem( Path_mask );

 // Возврат.
 return;
}

// ─── Поток для обработки файлов. ───

VOID Processor_ProcessorThread( VOID )
{
 // Определяем поток в системе.
 HAB Thread = WinInitialize( 0 );
 Processor_Thread.Processor_anchor = Thread;

 // Если это сделать не удалось - выход.
 if( Thread == NULLHANDLE ) return;

 // Создаем очередь сообщений - она должна быть в каждом потоке.
 {
  HMQ Messages_queue = WinCreateMsgQueue( Thread, 0 );
  Processor_Thread.Processor_queue = Messages_queue;

  // Если очередь создать не удалось - выход.
  if( Messages_queue == NULLHANDLE )
   {
    WinTerminate( Thread );
    return;
   }
 }

 // В строке состояния будет имя файла.
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_RU_Name ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_EN_Name ); 

 // На кнопке "Выход" будет надпись "Стоп".
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Stop ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Stop );

 // Обрабатываем файлы. Для каждого файла вызывается Processor_ProcessFile().
 DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MINIMUM, 0 );
 FindFiles( Names.Task.Root_directory, 1 );
 DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

 // Обработка завершена.
 Names.Processing = 0;

 // В строке состояния будет путь.
 if( strlen( Names.Task.Root_directory ) == 2 ) { Names.Task.Root_directory[ 2 ] = '\\'; Names.Task.Root_directory[ 3 ] = 0; }
  {
   Names.Settings.InputField_is_locked = 1;
   WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_FIELD ), Names.Task.Root_directory );
   Names.Settings.InputField_is_locked = 0;
  }

 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_RU_Path ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_EN_Path ); 

 // На кнопке "Стоп" будет надпись "Выход".
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Exit ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Exit ); 

 // Сообщение.
 if( Names.Settings.Code_page == RUSSIAN )
  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_All_done, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
 else
  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_All_done, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );

 // Завершаем поток.
 WinDestroyMsgQueue( Processor_Thread.Processor_queue );
 WinTerminate( Processor_Thread.Processor_anchor );
 Processor_Thread.Processor = NULLHANDLE;
 DosExit( EXIT_THREAD, 0 );
}

// ─── Запускает поток для обработки файлов ───

VOID StartProcessing( VOID )
{
 // Если обработка уже идет - возврат.
 if( Names.Processing ) return;

 // Создаем поток.
 DosCreateThread( &Processor_Thread.Processor, (PFNTHREAD) Processor_ProcessorThread, 0, 0, 32768 );

 // Запоминаем, что он работает.
 Names.Processing = 1;

 // Возврат.
 return;
}
