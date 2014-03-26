
// ─── Проверяет, можно ли обрабатывать весь диск начиная с корня ───

BYTE PermissionForDriveCheck( PCHAR Drive_name, BYTE Display_messages )
{
 // Если метка диска содержит что-то кроме обычных букв - диск обрабатывать нельзя.
 {
  CHAR Label[ SIZE_OF_NAME ] = ""; QueryDriveLabel( Drive_name, Label );

  if( DriveLabelHasSpecialChars( Label ) )
   {
    if( Display_messages )
     {
      if( Names.Settings.Code_page == RUSSIAN )
       WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Drive_is_protected, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
      else
       WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Drive_is_protected, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
     }

    return 0;
   }
 }

 // Если на диске есть каталоги Unix - диск обрабатывать нельзя.
 {
  CHAR Unix_directory[ 10 ] = "";
  Unix_directory[ 0 ] = Drive_name[ 0 ];
  strcpy( &Unix_directory[ 1 ], ":\\usr" );

  if( FileExists( Unix_directory ) )
   {
    if( Display_messages )
     {
      if( Names.Settings.Code_page == RUSSIAN )
       WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Unix_structures, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
      else
       WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Unix_structures, Names.Frame_window_title, NULLHANDLE, NULLHANDLE );
     }

    return 0;
   }
 }

 // Возврат.
 return 1;
}

// ─── Проверяет, можно ли обрабатывать файлы в каталоге ───

BYTE Permission( PCHAR Directory_name )
{
 BYTE Permission = 1;

 // Если это каталог рабочего стола - ничего делать не надо.
 if( Permission )
  {
   // Узнаем число и названия атрибутов.
   CHAR EA_Name[] = ".CLASSINFO";
   PGEA2LIST Descriptions = NULL; ULONG Descriptions_size = 4096;

   if( DosAllocMem( (PPVOID) &Descriptions, Descriptions_size, PAG_ALLOCATE ) == NO_ERROR )
    {
     ULONG Quantity = DEA_GET_ATTRS;

     bzero( Descriptions, Descriptions_size );
     DosEnumAttribute( ENUMEA_REFTYPE_PATH, Directory_name, 1, Descriptions, Descriptions_size, &Quantity, ENUMEA_LEVEL_NO_VALUE );

     if( !Quantity )
      {
       DosFreeMem( Descriptions ); Descriptions = NULL;
      }
     else
      {
       INT Name_length = strlen( EA_Name );

       // Структуры имеют разную длину, поэтому выполняем поиск строки.
       BYTE Success = 0; PBYTE One_byte = (PBYTE) Descriptions; INT Count;
       for( Count = 0; Count < Descriptions_size - strlen( EA_Name ) - 1; Count ++ )
        if( strcmp( &One_byte[ Count ], EA_Name ) == EQUALLY ) { Success = 1; break; }

       DosFreeMem( Descriptions ); Descriptions = NULL;

       // Если название найдено:
       if( Success )
        {
         PGEA2LIST InputData = NULL; PFEA2LIST OutputData = NULL; LONG Data_size = 16384;

         // Узнаем значение.
         if( DosAllocMem( (PPVOID) &InputData, Data_size, PAG_ALLOCATE ) == NO_ERROR &&
             DosAllocMem( (PPVOID) &OutputData, Data_size, PAG_ALLOCATE ) == NO_ERROR )
          {
           // Требуются сведения об одном атрибуте.
           bzero( InputData, Data_size );
           strcpy( InputData->list[0].szName, EA_Name );
           InputData->list[0].cbName = (BYTE) Name_length;
           InputData->cbList = sizeof( GEA2LIST ) + Name_length + 1;

           bzero( OutputData, Data_size );
           OutputData->cbList = Data_size;

           // Получаем значение.
           {
            EAOP2 Reference = { InputData, OutputData, 0 };
            DosQueryPathInfo( Directory_name, FIL_QUERYEASFROMLIST, &Reference, sizeof( Reference ) );
           }

           // Если оно получено:
           if( OutputData->cbList )
            {
             // Проверяем его.
             PBYTE One_byte = (PBYTE) OutputData; LONG Limit = OutputData->cbList - 1; INT Count;
             for( Count = 0; Count < Limit; Count ++ ) if( One_byte[ Count ] == 0 ) One_byte[ Count ] = '.';
             One_byte[ Limit ] = 0;

             if( Permission ) if( strfind( "WPDesktop", (PBYTE) OutputData ) ) Permission = 0;
             if( Permission ) if( strfind( "WPVault", (PBYTE) OutputData ) ) Permission = 0;

             OutputData->cbList = (ULONG) 0;
            }

           DosFreeMem( InputData ); InputData = NULL;
           DosFreeMem( OutputData ); OutputData = NULL;
          }
        }
      }
    }
  }

 // Если в каталоге есть Unix-файлы - следует пропустить его.
 if( Permission )
  {
   if( Names.Task.Convert_names )
    {
     PCHAR Unix_file = NULL;
     APIRET Report = DosAllocMem( (PPVOID) &Unix_file, strlen( Directory_name ) + SIZE_OF_NAME, PAG_ALLOCATE );

     if( Report == NO_ERROR )
      {
       strcpy( Unix_file, Directory_name );

       if( Permission ) { strcat( Unix_file, "\\.htaccess" );  if( FileExists( Unix_file ) ) Permission = 0; CutNameInPath( Unix_file ); }
       if( Permission ) { strcat( Unix_file, "\\.ftpaccess" ); if( FileExists( Unix_file ) ) Permission = 0; CutNameInPath( Unix_file ); }
       if( Permission ) { strcat( Unix_file, "\\.cshrc" );     if( FileExists( Unix_file ) ) Permission = 0; CutNameInPath( Unix_file ); }
       if( Permission ) { strcat( Unix_file, "\\.bashrc" );    if( FileExists( Unix_file ) ) Permission = 0; CutNameInPath( Unix_file ); }

       DosFreeMem( Unix_file ); Unix_file = NULL;
      }
    }
  }

 // Возврат.
 return Permission;
}

