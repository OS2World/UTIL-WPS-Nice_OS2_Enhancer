
// ─── Читает список окон диалогов ───

// Ini_file - файл с настройками расширителя.
VOID Applier_ReadDialogList( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte; ULONG Int; ULONG Long; ULONG Path; ULONG Name; ULONG DialogField; ULONG Title;
 ULONG Byte_data; ULONG Int_data; ULONG Long_data;

 CHAR Exe_name[ SIZE_OF_NAME ] = ""; CHAR Window_title[ SIZE_OF_TITLE ] = "";
 CHAR Field_value[ SIZE_OF_DIALOG_FIELD ] = ""; CHAR Logon_command[ SIZE_OF_PATH ] = "";

 INT Pointer;
 for( Pointer = 0; Pointer < 8; Pointer ++ )
  {
   CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PLOGONDLGBOX Dialog = NULL;
   itoa( Pointer, Number, 16 ); UpperCase( Number );
   strcpy( Dialog_name, "Logon dialog " ); strcat( Dialog_name, Number );
   switch( Pointer )
    {
     case 0: Dialog = &Applier.Settings.Dialogs.Logon_dialog_1; break;
     case 1: Dialog = &Applier.Settings.Dialogs.Logon_dialog_2; break;
     case 2: Dialog = &Applier.Settings.Dialogs.Logon_dialog_3; break;
     case 3: Dialog = &Applier.Settings.Dialogs.Logon_dialog_4; break;
     case 4: Dialog = &Applier.Settings.Dialogs.Logon_dialog_5; break;
     case 5: Dialog = &Applier.Settings.Dialogs.Logon_dialog_6; break;
     case 6: Dialog = &Applier.Settings.Dialogs.Logon_dialog_7; break;
     case 7: Dialog = &Applier.Settings.Dialogs.Logon_dialog_8; break;
    }

   strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" ); Long = sizeof( LONG );
   if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Long_data, &Long ) )
    {
     Dialog->Frame_type = Long_data;
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" ); Name = SIZE_OF_NAME;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Exe_name, &Name );
     if( Exe_name[ 0 ] != 0 ) { strcpy( Dialog->Exe_name, Exe_name ); Exe_name[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" ); Title = SIZE_OF_TITLE;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Window_title, &Title );
     if( Window_title[ 0 ] != 0 ) { strcpy( Dialog->Window_title, Window_title ); Window_title[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " command" ); Path = SIZE_OF_PATH;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Logon_command, &Path );
     if( Logon_command[ 0 ] != 0 ) { strcpy( Dialog->Logon_command, Logon_command ); Logon_command[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" ); Byte = sizeof( BYTE );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Byte_data, &Byte ) ) Dialog->Enabled = Byte_data;
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " only once" ); Byte = sizeof( BYTE );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Byte_data, &Byte ) ) Dialog->Only_once = Byte_data;
    }
  }

 for( Pointer = 0; Pointer < 8; Pointer ++ )
  {
   CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PDLGBOX Dialog = NULL;
   itoa( Pointer, Number, 16 ); UpperCase( Number );
   strcpy( Dialog_name, "Incomplete dialog " ); strcat( Dialog_name, Number );
   switch( Pointer )
    {
     case 0: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_1; break;
     case 1: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_2; break;
     case 2: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_3; break;
     case 3: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_4; break;
     case 4: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_5; break;
     case 5: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_6; break;
     case 6: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_7; break;
     case 7: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_8; break;
    }

   strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" ); Long = sizeof( LONG );
   if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Long_data, &Long ) )
    {
     Dialog->Frame_type = Long_data;
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" ); Name = SIZE_OF_NAME;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Exe_name, &Name );
     if( Exe_name[ 0 ] != 0 ) { strcpy( Dialog->Exe_name, Exe_name ); Exe_name[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" ); Title = SIZE_OF_TITLE;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Window_title, &Title );
     if( Window_title[ 0 ] != 0 ) { strcpy( Dialog->Window_title, Window_title ); Window_title[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " fields" ); Int = sizeof( INT );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Int_data, &Int ) )
      {
       INT Count; Dialog->Quantity = Int_data;
       for( Count = 0; Count < Dialog->Quantity; Count ++ )
        {
         CHAR Number[ 25 ] = ""; itoa( Count, Number, 16 ); UpperCase( Number );
         strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " field " ); strcat( Setting_name, Number ); strcat( Setting_name, " type" );
         Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Long_data, &Long ) ) Dialog->Fields[ Count ].Type = Long_data;
         strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " field " ); strcat( Setting_name, Number ); strcat( Setting_name, " value" );
         DialogField = SIZE_OF_DIALOG_FIELD; PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Field_value, &DialogField );
         if( Field_value[ 0 ] != 0 ) { strcpy( Dialog->Fields[ Count ].Value, Field_value ); Field_value[ 0 ] = 0; }
        }
      }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" ); Byte = sizeof( BYTE );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Byte_data, &Byte ) ) Dialog->Enabled = Byte_data;
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " only text" ); Byte = sizeof( BYTE );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Byte_data, &Byte ) ) Dialog->Text_fields_only = Byte_data;
    }
  }

 for( Pointer = 0; Pointer < 8; Pointer ++ )
  {
   CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PMSGDLGBOX Dialog = NULL;
   itoa( Pointer, Number, 16 ); UpperCase( Number );
   strcpy( Dialog_name, "Message dialog " ); strcat( Dialog_name, Number );
   switch( Pointer )
    {
     case 0: Dialog = &Applier.Settings.Dialogs.Message_dialog_1; break;
     case 1: Dialog = &Applier.Settings.Dialogs.Message_dialog_2; break;
     case 2: Dialog = &Applier.Settings.Dialogs.Message_dialog_3; break;
     case 3: Dialog = &Applier.Settings.Dialogs.Message_dialog_4; break;
     case 4: Dialog = &Applier.Settings.Dialogs.Message_dialog_5; break;
     case 5: Dialog = &Applier.Settings.Dialogs.Message_dialog_6; break;
     case 6: Dialog = &Applier.Settings.Dialogs.Message_dialog_7; break;
     case 7: Dialog = &Applier.Settings.Dialogs.Message_dialog_8; break;
    }

   strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" ); Long = sizeof( LONG );
   if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Long_data, &Long ) )
    {
     Dialog->Frame_type = Long_data;
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" ); Name = SIZE_OF_NAME;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Exe_name, &Name );
     if( Exe_name[ 0 ] != 0 ) { strcpy( Dialog->Exe_name, Exe_name ); Exe_name[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" ); Title = SIZE_OF_TITLE;
     PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Window_title, &Title );
     if( Window_title[ 0 ] != 0 ) { strcpy( Dialog->Window_title, Window_title ); Window_title[ 0 ] = 0; }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " buttons" ); Int = sizeof( INT );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Int_data, &Int ) )
      {
       INT Count; Dialog->Quantity = Int_data;
       for( Count = 0; Count < Dialog->Quantity; Count ++ )
        {
         CHAR Number[ 25 ] = ""; itoa( Count, Number, 16 ); UpperCase( Number );
         strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " button " ); strcat( Setting_name, Number );
         DialogField = SIZE_OF_DIALOG_FIELD; PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, Field_value, &DialogField );
         if( Field_value[ 0 ] != 0 ) { Dialog->Buttons[ Count ].Type = DLG_PUSH_BUTTON; strcpy( Dialog->Buttons[ Count ].Value, Field_value ); Field_value[ 0 ] = 0; }
        }
      }
     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " close button" ); Int = sizeof( INT );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Int_data, &Int ) ) Dialog->Close_button = Int_data;

     strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" ); Byte = sizeof( BYTE );
     if( PrfQueryProfileData( Ini_file, "Dialogs", Setting_name, &Byte_data, &Byte ) ) Dialog->Enabled = Byte_data;
    }
  }

 // Возврат.
 return;
}

// ─── Записывает список окон диалогов ───

// Changed_list_entry указывает на то, какие данные надо записать. Может быть NULL.
VOID Applier_WriteDialogList( PVOID Changed_list_entry )
{
 // Открываем файл настроек.
 CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
 HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

 // Если это сделать не удалось - возврат.
 if( Ini_file == NULLHANDLE ) return;

 // Записываем настройки.
 {
  INT Pointer;
  for( Pointer = 0; Pointer < 8; Pointer ++ )
   {
    CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PLOGONDLGBOX Dialog = NULL;
    itoa( Pointer, Number, 16 ); UpperCase( Number );
    strcpy( Dialog_name, "Logon dialog " ); strcat( Dialog_name, Number );
    switch( Pointer )
     {
      case 0: Dialog = &Applier.Settings.Dialogs.Logon_dialog_1; break;
      case 1: Dialog = &Applier.Settings.Dialogs.Logon_dialog_2; break;
      case 2: Dialog = &Applier.Settings.Dialogs.Logon_dialog_3; break;
      case 3: Dialog = &Applier.Settings.Dialogs.Logon_dialog_4; break;
      case 4: Dialog = &Applier.Settings.Dialogs.Logon_dialog_5; break;
      case 5: Dialog = &Applier.Settings.Dialogs.Logon_dialog_6; break;
      case 6: Dialog = &Applier.Settings.Dialogs.Logon_dialog_7; break;
      case 7: Dialog = &Applier.Settings.Dialogs.Logon_dialog_8; break;
     }
    if( Changed_list_entry != NULL ) if( Dialog != Changed_list_entry ) continue;

    if( Dialog->Frame_type != 0 )
     {
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Frame_type, sizeof( LONG ) );
      if( Dialog->Exe_name[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Exe_name, strlen( Dialog->Exe_name ) + 1 );
       }
      if( Dialog->Window_title[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Window_title, strlen( Dialog->Window_title ) + 1 );
       }
      if( Dialog->Logon_command[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " command" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Logon_command, strlen( Dialog->Logon_command ) + 1 );
       }
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Enabled, sizeof( BYTE ) );
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " only once" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Only_once, sizeof( BYTE ) );
     }
   }
 }

 {
  INT Pointer; INT Count;
  for( Pointer = 0; Pointer < 8; Pointer ++ )
   {
    CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PDLGBOX Dialog = NULL;
    itoa( Pointer, Number, 16 ); UpperCase( Number );
    strcpy( Dialog_name, "Incomplete dialog " ); strcat( Dialog_name, Number );
    switch( Pointer )
     {
      case 0: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_1; break;
      case 1: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_2; break;
      case 2: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_3; break;
      case 3: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_4; break;
      case 4: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_5; break;
      case 5: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_6; break;
      case 6: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_7; break;
      case 7: Dialog = &Applier.Settings.Dialogs.Incomplete_dialog_8; break;
     }
    if( Changed_list_entry != NULL ) if( Dialog != Changed_list_entry ) continue;

    if( Dialog->Frame_type != 0 )
     {
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Frame_type, sizeof( LONG ) );
      if( Dialog->Exe_name[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Exe_name, strlen( Dialog->Exe_name ) + 1 );
       }
      if( Dialog->Window_title[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Window_title, strlen( Dialog->Window_title ) + 1 );
       }
      if( Dialog->Quantity )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " fields" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Quantity, sizeof( INT ) );
        for( Count = 0; Count < Dialog->Quantity; Count ++ )
         {
          CHAR Number[ 25 ] = ""; itoa( Count, Number, 16 ); UpperCase( Number );
          strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " field " ); strcat( Setting_name, Number ); strcat( Setting_name, " type" );
          PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Fields[ Count ].Type, sizeof( LONG ) );
          strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " field " ); strcat( Setting_name, Number ); strcat( Setting_name, " value" );
          PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Fields[ Count ].Value, strlen( Dialog->Fields[ Count ].Value ) + 1 );
         }
       }
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Enabled, sizeof( BYTE ) );
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " only text" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Text_fields_only, sizeof( BYTE ) );
     }
   }
 }

 {
  INT Pointer; INT Count;
  for( Pointer = 0; Pointer < 8; Pointer ++ )
   {
    CHAR Dialog_name[ SIZE_OF_NAME ] = ""; CHAR Number[ 25 ] = ""; CHAR Setting_name[ 50 ] = ""; PMSGDLGBOX Dialog = NULL;
    itoa( Pointer, Number, 16 ); UpperCase( Number );
    strcpy( Dialog_name, "Message dialog " ); strcat( Dialog_name, Number );
    switch( Pointer )
     {
      case 0: Dialog = &Applier.Settings.Dialogs.Message_dialog_1; break;
      case 1: Dialog = &Applier.Settings.Dialogs.Message_dialog_2; break;
      case 2: Dialog = &Applier.Settings.Dialogs.Message_dialog_3; break;
      case 3: Dialog = &Applier.Settings.Dialogs.Message_dialog_4; break;
      case 4: Dialog = &Applier.Settings.Dialogs.Message_dialog_5; break;
      case 5: Dialog = &Applier.Settings.Dialogs.Message_dialog_6; break;
      case 6: Dialog = &Applier.Settings.Dialogs.Message_dialog_7; break;
      case 7: Dialog = &Applier.Settings.Dialogs.Message_dialog_8; break;
     }
    if( Changed_list_entry != NULL ) if( Dialog != Changed_list_entry ) continue;

    if( Dialog->Frame_type != 0 )
     {
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " frame" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Frame_type, sizeof( LONG ) );
      if( Dialog->Exe_name[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " exe name" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Exe_name, strlen( Dialog->Exe_name ) + 1 );
       }
      if( Dialog->Window_title[ 0 ] != 0 )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " title" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Window_title, strlen( Dialog->Window_title ) + 1 );
       }
      if( Dialog->Quantity )
       {
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " buttons" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Quantity, sizeof( INT ) );
        for( Count = 0; Count < Dialog->Quantity; Count ++ )
         {
          CHAR Number[ 25 ] = ""; itoa( Count, Number, 16 ); UpperCase( Number );
          strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " button " ); strcat( Setting_name, Number );
          PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, Dialog->Buttons[ Count ].Value, strlen( Dialog->Buttons[ Count ].Value ) + 1 );
         }
        strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " close button" );
        PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Close_button, sizeof( INT ) );
       }
      strcpy( Setting_name, Dialog_name ); strcat( Setting_name, " enabled" );
      PrfWriteProfileData( Ini_file, "Dialogs", Setting_name, &Dialog->Enabled, sizeof( BYTE ) );
     }
   }
 }

 // Закрываем файл настроек.
 PrfCloseProfile( Ini_file ); Ini_file = NULLHANDLE;

 // Возврат.
 return;
}
