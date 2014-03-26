// ����७��� ��६����.
typedef struct _PROCESSORTHRD
 {
  // ��ࠡ�⪠ 䠩���.
  TID Processor;
  HMQ Processor_queue;
  HAB Processor_anchor;

  // ����騩 ����.
  CHAR Static_path[ SIZE_OF_PATH ];
 }
PROCESSORTHRD; PROCESSORTHRD Processor_Thread;

// ��� �����ࠥ� ��� 䠩�� ���襥 ���. ���

// �����頥��� ���祭�� - ���� �� ���襥 ���, 1 ��� 0.
BYTE Processor_QueryBetterName( PCHAR Short_name )
{
 // �᫨ ��� "os2" - ������ �� �㪢� �������묨.
 if( stricmpe( Short_name, "os2" ) == EQUALLY )
  {
   Short_name[ 0 ] = 'O';
   Short_name[ 1 ] = 'S';

   return 1;
  }

 // ����� ����� ��२�������� ��㣨� 䠩��.
 if( stricmpe( Short_name, "wp root. sf" ) == EQUALLY ) { strcpy( Short_name, "WP Root. sf" ); return 1; }
 if( stricmpe( Short_name, "ea data. sf" ) == EQUALLY ) { strcpy( Short_name, "EA Data. sf" ); return 1; }

 if( stricmpe( Short_name, "psfonts" ) == EQUALLY )     { strcpy( Short_name, "PSFonts" );     return 1; }
 if( stricmpe( Short_name, "lotusw4" ) == EQUALLY )     { strcpy( Short_name, "LotusW4" );     return 1; }
 if( stricmpe( Short_name, "xfree86" ) == EQUALLY )     { strcpy( Short_name, "XFree86" );     return 1; }

 // ������.
 return 0;
}

// ��� ��ࠡ��뢠�� 䠩� ���

VOID Processor_ProcessFile( PCHAR File_name )
{
 // ��७� ��᪠ � ��⠫��, � ���ண� ��稭����� ��ࠡ�⪠, �ண��� �� �㦭�.
 if( stricmpe( File_name, Names.Task.Root_directory ) == EQUALLY ) return;

 {
  // �롨ࠥ� ��� 䠩��.
  PCHAR Name_in_path = FindNameInPath( File_name ); CHAR Better_name[ SIZE_OF_PATH ] = "";

  // �᫨ ��� �� ������� - ������.
  if( Name_in_path == NULL ) return;

  // �ਢ���� ����� � �ࠢ��쭮�� ����.
  if( Names.Task.Convert_names )
   {
    // �᫨ � ����� ���� �������� � ����� �㪢� - �� ���� ��࠭���.
    BYTE Convert_name = 0;

    if( Name_in_path[ 0 ] != '.' && strfind( ".", Name_in_path ) )
     {
      strcpy( Better_name, Name_in_path ); UpperCase( Better_name );
      if( strcmp( Better_name, Name_in_path ) == EQUALLY ) Convert_name = 1;
     }

    // �᫨ 䠩� ����� ��ࠡ����:
    if( Convert_name )
     {
      // �஢��塞, ���� �� ��� 䠩�� ���襥 ���.
      BYTE Better_name_is_exists = 0;
      strcpy( Better_name, Name_in_path );
      Better_name_is_exists = Processor_QueryBetterName( Better_name );

      // �᫨ ��� ��� - �ਢ���� ��� � �ࠢ��쭮�� ����.
      if( !Better_name_is_exists ) MixedCase( Better_name );

      // �᫨ ��� ���������� - ��२�����뢠�� 䠩�.
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

 // ������ ��� ���窠 ⠪�� ��, ��� ��� 䠩��.
 if( Names.Task.Revise_differences )
  {
   BYTE Convert_name = 1;
   if( stricmpe( &File_name[ 1 ], ":\\OS2\\Bitmap" ) == EQUALLY ) Convert_name = 0;

   if( Convert_name ) DiscardEA( File_name, ".LONGNAME" );
  }

 // ����塞 ����ࠦ���� ��� 䠩���, ����� � ⠪ �� ᮤ�ঠ�.
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

 // ����塞 ����ன�� ��� 䠩��� � ����ࠦ���ﬨ � ��㪮�.
 if( Names.Task.Remove_images )
  {
   PCHAR Extensions[] = { ".mpg", ".avi", ".mid", ".wav" };
   INT Quantity = 4; BYTE Process_file = 0; INT Count;

   for( Count = 0; Count < Quantity; Count ++ )
    if( strifind( Extensions[ Count ], Name_in_path ) ) Process_file = 1;

   if( Process_file ) DiscardEA( File_name, ".MMPREF_MMGENERIC" );
  }

 // ����뢠�� "⨯", �᫨ ���� ���७��.
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

 // ����뢠�� ��ਡ�� "Read only".
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

  // �⮡ࠦ��� ��� � ��ப� ���ﭨ�.
  if( WinIsWindowVisible( Names.Frame_window ) && WinIsWindowShowing( Names.Frame_window ) )
   {
    Names.Settings.InputField_is_locked = 1;
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_FIELD ), Name_in_path );
    Names.Settings.InputField_is_locked = 0;
   }
 }

 // �᫨ ��ࠡ�⪠ ������ ���� �४�饭� - �����蠥� ��⮪.
 if( !Names.Processing )
  {
   // �⮡ࠦ��� ���� � ��ப� ���ﭨ�.
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

   // �� ������ "�⮯" �㤥� ������� "��室".
   if( Names.Settings.Code_page == RUSSIAN )
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Exit );
   else
    WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Exit );

   // �����蠥� ��⮪.
   WinDestroyMsgQueue( Processor_Thread.Processor_queue );
   WinTerminate( Processor_Thread.Processor_anchor );
   Processor_Thread.Processor = NULLHANDLE;
   DosExit( EXIT_THREAD, 0 );
  }

 // ������.
 return;
}

// ��� ���⠢��� ������ ��� 䠩��. ���

VOID Processor_MakePathname( PCHAR Static_path, PCHAR Path, PCHAR Name )
{
 // ���⠢�塞 ���.
 if( Path[ 0 ] == 0 ) strcpy( Processor_Thread.Static_path, Name );
 else
  {
   strcpy( Processor_Thread.Static_path, Path );
   strcat( Processor_Thread.Static_path, "\\" );
   strcat( Processor_Thread.Static_path, Name );
  }

 // ������.
 return;
}

// ��� �믮���� ���� 䠩��� ���

// Path - ����, � ���ண� ���� ����� ����, Include_dirs - ���� �� ��ࠡ��뢠�� ��⠫���.
VOID FindFiles( PCHAR Path, BYTE Include_dirs )
{
 PCHAR Path_mask = NULL; APIRET Report = NO_ERROR;

 // �᫨ 䠩�� � ��⠫��� ��ࠡ��뢠�� ����� - ������.
 if( !Permission( Path ) ) return;

 // ������ ����� ��� ���᪠.
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
  // ��室�� ���� 䠩�.
  HDIR Directory = HDIR_CREATE;
  ULONG All_files = FILE_READONLY | FILE_HIDDEN | FILE_SYSTEM | FILE_ARCHIVED;
  FILEFINDBUF3 Find_buffer = { 0 };
  ULONG Buffer_length = sizeof( FILEFINDBUF3 );
  ULONG Find_count = 1;

  APIRET Report = DosFindFirst( Path_mask, &Directory, All_files, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // �᫨ 䠩��� ��� - ���室�� � ��ॡ��� ��⠫����.
  BYTE Perform_directory_search = 0;
  if( Report == ERROR_NO_MORE_FILES ) Perform_directory_search = 1;
  // � �᫨ 䠩� ������ - ��ࠡ��뢠�� ���.
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

   // ��ॡ�ࠥ� 䠩��.
   if( !Perform_directory_search )
    while( Report == NO_ERROR )
     {
      // ��室�� ᫥���騩 䠩�.
      Find_count = 1;
      Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

      // ��ࠡ��뢠�� ���.
      if( Report == NO_ERROR )
       {
        Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
        Processor_ProcessFile( Processor_Thread.Static_path );
       }
     }

  // �����蠥� ����.
  DosFindClose( Directory );

  // ��ॡ�� ��⠫����. ��室�� ���� ��⠫��.
  Directory = HDIR_CREATE;
  Find_count = 1;

  Report = DosFindFirst( Path_mask, &Directory, All_files | MUST_HAVE_DIRECTORY, &Find_buffer, Buffer_length, &Find_count, FIL_STANDARD );

  // �᫨ ��⠫�� ������ - ��ࠡ��뢠�� ���.
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

  // ��ॡ�ࠥ� ��⠫���.
  while( Report == NO_ERROR )
   {
    // ��室�� ᫥���騩 ��⠫��.
    Find_count = 1;
    Report = DosFindNext( Directory, &Find_buffer, Buffer_length, &Find_count );

    // ��ࠡ��뢠�� ���.
    if( Report == NO_ERROR )
     {
      if( strcmp( Find_buffer.achName, "." ) == EQUALLY ) continue;
      if( strcmp( Find_buffer.achName, ".." ) == EQUALLY ) continue;
      Processor_MakePathname( Processor_Thread.Static_path, Path, Find_buffer.achName );
     }
    else break;

    // �⮡� ��ࠡ���� 䠩�� � �⮬ ��⠫���, ��뢠�� FindFiles() ����୮.
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

  // �����蠥� ����.
  DosFindClose( Directory );
 }

 // �᢮������� ������.
 DosFreeMem( Path_mask );

 // ������.
 return;
}

// ��� ��⮪ ��� ��ࠡ�⪨ 䠩���. ���

VOID Processor_ProcessorThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );
 Processor_Thread.Processor_anchor = Thread;

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE ) return;

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 {
  HMQ Messages_queue = WinCreateMsgQueue( Thread, 0 );
  Processor_Thread.Processor_queue = Messages_queue;

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if( Messages_queue == NULLHANDLE )
   {
    WinTerminate( Thread );
    return;
   }
 }

 // � ��ப� ���ﭨ� �㤥� ��� 䠩��.
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_RU_Name ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_PATH_LABEL ), StrConst_EN_Name ); 

 // �� ������ "��室" �㤥� ������� "�⮯".
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Stop ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Stop );

 // ��ࠡ��뢠�� 䠩��. ��� ������� 䠩�� ��뢠���� Processor_ProcessFile().
 DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MINIMUM, 0 );
 FindFiles( Names.Task.Root_directory, 1 );
 DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

 // ��ࠡ�⪠ �����襭�.
 Names.Processing = 0;

 // � ��ப� ���ﭨ� �㤥� ����.
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

 // �� ������ "�⮯" �㤥� ������� "��室".
 if( Names.Settings.Code_page == RUSSIAN )
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_RU_Exit ); 
 else
  WinSetWindowText( WinWindowFromID( Names.Frame_window, ID_MAINWNDFORM_STOP_BUTTON ), StrConst_EN_Exit ); 

 // ����饭��.
 if( Names.Settings.Code_page == RUSSIAN )
  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_All_done, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
 else
  WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_All_done, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );

 // �����蠥� ��⮪.
 WinDestroyMsgQueue( Processor_Thread.Processor_queue );
 WinTerminate( Processor_Thread.Processor_anchor );
 Processor_Thread.Processor = NULLHANDLE;
 DosExit( EXIT_THREAD, 0 );
}

// ��� ����᪠�� ��⮪ ��� ��ࠡ�⪨ 䠩��� ���

VOID StartProcessing( VOID )
{
 // �᫨ ��ࠡ�⪠ 㦥 ���� - ������.
 if( Names.Processing ) return;

 // ������� ��⮪.
 DosCreateThread( &Processor_Thread.Processor, (PFNTHREAD) Processor_ProcessorThread, 0, 0, 32768 );

 // ����������, �� �� ࠡ�⠥�.
 Names.Processing = 1;

 // ������.
 return;
}
