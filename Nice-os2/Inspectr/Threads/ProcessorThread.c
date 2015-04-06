
// ��� ��ࠡ��뢠�� 䠩� ���

VOID Processor_ProcessFile( PCHAR File_name )
{
 // �롨ࠥ� ��� 䠩��.
 PCHAR Name = FindNameInPath( File_name ); INT Position = -1;

 // �᫨ ��� �� ������� - ������.
 if( Name == NULL ) return;

 // �᫨ �ਫ������ ���� � ᯨ᪥ - ���������� ��� � �����뢠�� � ����.
 Position = FindExeNameInRepository( Name );

 if( Position != -1 )
  if( Repository.Items[ Position ].Path_INI_setting_name[ 0 ] != 0 )
   {
    CHAR Path[ SIZE_OF_PATH ] = ""; strcpy( Path, File_name ); CutNameInPath( Path );

    if( !strc( Repository.Items[ Position ].Path, Path ) )
     {
      strcpy( Repository.Items[ Position ].Path, Path );
      Inspector.Write_settings = 1;
     }

     if( InnerLimits.Inserted_lines < MAX_INSERTED_LINES )
      {
       InnerLimits.Inserted_lines ++;

       CHAR Status_string[ SIZE_OF_TITLE ] = "";

       UpperCase( Name ); LowerCase( &Name[ 1 ] );
       strcpy( Status_string, Name );
       strcat( Status_string, " - " );
       strcat( Status_string, Repository.Items[ Position ].Path );

       WinSendDlgItemMsg( Inspector.Client_window, Client_Window.Settings.List_ID, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Status_string ) );
      }
   }

 // �⮡ࠦ��� ��� � ��ப� ���ﭨ�.
 if( WinIsWindowShowing( Inspector.Frame_window ) )
  {
   CHAR Status_string[ SIZE_OF_TITLE ] = ">> ";

   UpperCase( Name ); LowerCase( &Name[ 1 ] );
   strcat( Status_string, Name );

   WinSetWindowText( WinWindowFromID( Inspector.Client_window, Client_Window.Settings.Text_ID ), Status_string );
  }

 // ������.
 return;
}

// ��� ���⠢��� ������ ��� 䠩��. ���

VOID Processor_MakePathname( PCHAR Static_path, PCHAR Path, PCHAR Name )
{
 // ���⠢�塞 ���.
 if( Path[ 0 ] == 0 ) strcpy( Static_path, Name );
 else
  {
   strcpy( Static_path, Path );
   strcat( Static_path, "\\" );
   strcat( Static_path, Name );
  }

 // ������.
 return;
}

// ��� �믮���� ���� 䠩��� ���

// Path - ����, � ���ண� ���� ����� ����, Include_dirs - ���� �� ��ࠡ��뢠�� ��⠫���.
VOID Processor_FindFiles( PCHAR Path, BYTE Include_dirs )
{
 // ���� �᪠�� ⮫쪮 �ᯮ��塞� 䠩��.
 CHAR Search_mask[] = "*.exe";

 // ����騩 ���� ᮤ�ন��� �����.
 PCHAR Path_mask = NULL; PCHAR Path_mask_directories = NULL;

 // ������ ����� ��� ���᪠.
 APIRET Report = DosAllocMem( (PPVOID) &Path_mask, strlen( Path ) + SIZE_OF_NAME, PAG_ALLOCATE );
 if( Report != NO_ERROR ) return;

 Report = DosAllocMem( (PPVOID) &Path_mask_directories, strlen( Path ) + SIZE_OF_NAME, PAG_ALLOCATE );
 if( Report != NO_ERROR ) return;

 if( Path[ 0 ] == 0 )
  {
   strcpy( Path_mask, Search_mask );
   strcpy( Path_mask_directories, "*" );
  }
 else
  {
   strcpy( Path_mask, Path );
   strcpy( Path_mask_directories, Path );

   if( !strc( Path, Search_mask ) ) if( Path[ strlen( Path ) - 1 ] != '\\' )
    {
     strcat( Path_mask, "\\" ); strcat( Path_mask, Search_mask );
     strcat( Path_mask_directories, "\\" ); strcat( Path_mask_directories, "*" );
    }
  }

 {
  // ��室�� ���� 䠩�.
  HDIR Directory = HDIR_CREATE;
  ULONG All_files = FILE_READONLY | FILE_HIDDEN | FILE_SYSTEM | FILE_ARCHIVED;
  FILEFINDBUF3 Find_buffer = {0};
  ULONG Buffer_length = sizeof( FILEFINDBUF3 );
  ULONG Find_count = 1;

  APIRET Report = DosFindFirst( Path_mask, &Directory, All_files, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // �᫨ 䠩��� ��� - ���室�� � ��ॡ��� ��⠫����.
  BYTE Perform_directory_search = 0;

  if( Report == ERROR_NO_MORE_FILES )
   {
    Perform_directory_search = 1;
   }
  // � �᫨ 䠩� ������ - ��ࠡ��뢠�� ���.
  else
   {
    if( Report == NO_ERROR )
     {
      Processor_MakePathname( Processor.Static_path, Path, Find_buffer.achName );
      Processor_ProcessFile( Processor.Static_path );
     }
    else
     {
      DosFindClose( Directory );

      DosFreeMem( Path_mask ); Path_mask = NULL;
      DosFreeMem( Path_mask_directories ); Path_mask_directories = NULL;
      return;
     }
   }

   // ��ॡ�ࠥ� 䠩��.
   if( !Perform_directory_search )
    {
     while( Report == NO_ERROR )
      {
       // ��室�� ᫥���騩 䠩�.
       Find_count = 1;
       Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

       // ��ࠡ��뢠�� ���.
       if( Report == NO_ERROR )
        {
         Processor_MakePathname( Processor.Static_path, Path, Find_buffer.achName );
         Processor_ProcessFile( Processor.Static_path );
        }
      }
    }

  // �����蠥� ����.
  DosFindClose( Directory );

  // ��ॡ�� ��⠫����. ��室�� ���� ��⠫��.
  Directory = HDIR_CREATE;
  Find_count = 1;

  Report = DosFindFirst( Path_mask_directories, &Directory, All_files | MUST_HAVE_DIRECTORY, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // �᫨ ��⠫�� ������ - ��ࠡ��뢠�� ���.
  if( Report == NO_ERROR )
   {
    Processor_MakePathname( Processor.Static_path, Path, Find_buffer.achName );
    if( Include_dirs ) if( Path[ 0 ] != 0 ) Processor_ProcessFile( Path );
   }
  else
   {
    DosFindClose( Directory );

    DosFreeMem( Path_mask ); Path_mask = NULL;
    DosFreeMem( Path_mask_directories ); Path_mask_directories = NULL;
    return;
   }

  // ��ॡ�ࠥ� ��⠫���.
  while( Report == NO_ERROR )
   {
    // ��室�� ᫥���騩 ��⠫��.
    Find_count = 1;
    Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

    // ��ࠡ��뢠�� ���.
    BYTE Process_directory = 1;

    if( Report == NO_ERROR )
     {
      if( strc( Find_buffer.achName, "." ) ) continue;
      if( strc( Find_buffer.achName, ".." ) ) continue;

      Processor_MakePathname( Processor.Static_path, Path, Find_buffer.achName );

      {
       strcat( Processor.Static_path, "\\index.html" );
       if( FileExists( Processor.Static_path ) ) Process_directory = 0;
       CutNameInPath( Processor.Static_path );

       strcat( Processor.Static_path, "\\.htaccess" );
       if( FileExists( Processor.Static_path ) ) Process_directory = 0;
       CutNameInPath( Processor.Static_path );
      }
     }
    else
     {
      break;
     }

    // �⮡� ��ࠡ���� 䠩�� � �⮬ ��⠫���, ��뢠�� FindFiles() ����୮.
    if( Process_directory )
     {
      PCHAR New_path = NULL;
      APIRET Report = DosAllocMem( (PPVOID) &New_path, strlen( Processor.Static_path ) + SIZE_OF_NAME, PAG_ALLOCATE );

      if( Report == NO_ERROR )
       {
        strcpy( New_path, Processor.Static_path );

        Processor_FindFiles( New_path, Include_dirs );
        DosFreeMem( New_path ); New_path = NULL;
       }
     }
    }

  // �����蠥� ����.
  DosFindClose( Directory );
 }

 // �᢮������� ������.
 DosFreeMem( Path_mask ); Path_mask = NULL;
 DosFreeMem( Path_mask_directories ); Path_mask_directories = NULL;

 // ������.
 return;
}

// ��� ��⮪ ��� ��ࠡ�⪨ 䠩��� ���

VOID Processor_ProcessorThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE || Message_queue == NULLHANDLE ) DosExit( EXIT_THREAD, 0 );

 // ��ᬠ�ਢ��� 䠩�� �� ����㧮筮� ��᪥.
 ULONG Boot_drive = 0; DosQuerySysInfo( QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PULONG) &Boot_drive, sizeof( Boot_drive ) );

 if( Boot_drive )
  {
   CHAR Drive_name[ 3 ] = "*:"; Drive_name[ 0 ] = (CHAR) Boot_drive + 64;

   if( DriveIsAvailable( Drive_name ) )
    {
     DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );
     Processor_FindFiles( Drive_name, 0 );
     DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );
    }
  }

 // ��頥� ��ப� ���ﭨ�.
 WinSetWindowText( WinWindowFromID( Inspector.Client_window, Client_Window.Settings.Text_ID ), ">>" );

 // ��뢠�� ��⮪ ��� ��ᬮ�� ���窮� �� ࠡ�祬 �⮫�.
 StartObserving();

 // �����蠥� ��⮪.
 Inspector.Processing = 0;

 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );

 DosExit( EXIT_THREAD, 0 );
}

// ��� ����᪠�� ��⮪ ��� ��ࠡ�⪨ 䠩��� ���

VOID StartProcessing( VOID )
{
 // �᫨ ��ࠡ�⪠ 㦥 ���� - ������.
 if( Inspector.Processing ) return;

 // ����뢠�� ����७��� ��६����.
 bzero( &Processor, sizeof( Processor ) );
 bzero( &InnerLimits, sizeof( InnerLimits ) );

 // ������� ��⮪.
 {
  TID Thread_ID = 0; DosCreateThread( &Thread_ID, (PFNTHREAD) Processor_ProcessorThread, 0, 0, 32768 );
 }

 // ����������, �� �� ࠡ�⠥�.
 Inspector.Processing = 1;

 // ������.
 return;
}
