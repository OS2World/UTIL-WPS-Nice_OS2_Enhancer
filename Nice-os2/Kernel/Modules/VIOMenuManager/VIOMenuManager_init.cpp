
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID VIOMenuManager_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS || Division == SET_VIO_WINDOWS )
  {
   VIOMenuManager.Settings.SSH_Commands = 0;
   VIOMenuManager.Settings.Use_AltTilde = 1;

   {
    BYTE List_is_empty = 1;
    for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
     if( VIOMenuManager.Settings.Files[ Count ][ 0 ] != 0 ) { List_is_empty = 0; break; }

    if( List_is_empty )
     {
      GetCurrentPath( VIOMenuManager.Settings.Files[ 0 ] );
      strcat( VIOMenuManager.Settings.Files[ 0 ], "\\Prompts\\SSH.txt" );
     }
   }
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID VIOMenuManager_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Int = 0; ULONG Name = 0; ULONG Byte_data = 0; ULONG Int_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "SSH Commands", &Byte_data, &Byte ) ) VIOMenuManager.Settings.SSH_Commands = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Use AltTilde", &Byte_data, &Byte ) ) VIOMenuManager.Settings.Use_AltTilde = Byte_data;

 for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
  {
   VIOMenuManager.Settings.Files[ Count ][ 0 ] = 0;
   VIOMenuManager.RTSettings.Files[ Count ].Active = 0;

   {
    CHAR Number[ 4 ] = ""; itoa( Count, Number, 10 );
    CHAR Ini_record_name[ SIZE_OF_NAME ] = "File "; strcat( Ini_record_name, Number );

    CHAR Item[ SIZE_OF_PATH ] = ""; ULONG Path = SIZE_OF_PATH;
    PrfQueryProfileData( Ini_file, "SSH prompts", Ini_record_name, Item, &Path );

    if( Item[ 0 ] != 0 ) { strcpy( VIOMenuManager.Settings.Files[ Count ], Item ); Item[ 0 ] = 0; }
   }
  }

 // Возврат.
 return;
}
