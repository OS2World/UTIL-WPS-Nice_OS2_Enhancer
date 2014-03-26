// ��� ��⠥� ������� �� 䠩�� ���

// �� ��६���� - ���譨�.
VOID VIOMenuManager_ReadSSHCommandFile( INT File_number, PFILESTATUS3 Attributes )
{
 // �஡㥬 ������ 䠩�.
 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READONLY;

 HFILE File = NULLHANDLE; ULONG Report = 0;
 PCHAR File_name = VIOMenuManager.Settings.Files[ File_number ];
 APIRET RC = DosOpen( File_name, &File, &Report, 0, FILE_NORMAL, Action, Mode, NULL );

 // �᫨ 䠩� �� �� ����� - ������.
 if( RC != NO_ERROR ) return;

 // �⢮��� ������ ��� ⥪��.
 PCHAR Text = NULL; ULONG Length = ( MAX_VIO_MENU_COMMANDS * SIZE_OF_ITEM_TEXT ) * 2;
 if( DosAllocMem( (PPVOID) &Text, Length, PAG_ALLOCATE ) != NO_ERROR ) { DosClose( File ); return; }

 // ��⠥� ᮤ�ন��� 䠩��.
 memset( Text, 0, Length );
 DosRead( File, Text, Length, &Length );

 // ����뢠�� 䠩�.
 DosClose( File ); File = NULLHANDLE;

 // �᫨ 䠩� ��-� ᮤ�ন�:
 if( Length  > 0 )
  {
   // �᫨ 䠩� �� ��稭����� � '#' - ������.
   if( Text[ 0 ] != '#' ) { DosFreeMem( Text ); return; }

   // �᫨ � 䠩�� ��������� �㫥�� ᨬ���� - ������.
   for( INT Position = 0; Position < Length; Position ++ )
    if( Text[ Position ] == 0 ) { DosFreeMem( Text ); return; }

   // ��⠢�塞 ⮫쪮 �㪢� � ����, ᨬ���� "0x0A" �������� ��ﬨ.
   // �� �⮬ ��᫥����⥫쭮��� "0x0D:0x0A" ���� ����� ������ ��ப�.
   for( Position = 0; Position < Length; Position ++ )
    {
     if( Text[ Position ] == 0x0D ) { Text[ Position ] = 0; continue; }
     if( Text[ Position ] == 0x0A ) { Text[ Position ] = 0; continue; }

     if( Text[ Position ] < ' ' ) { Text[ Position ] = ' '; continue; }
     if( Text[ Position ] > '~' ) { Text[ Position ] = ' '; continue; }
    }

   // ����⠢�塞 㪠��⥫� �� ��ப�.
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

   // �᫨ ��ப� ����⢨⥫쭮 ����:
   if( Strings_quantity )
    {
     // ��ࠥ� �� ����� ��� �⮣� 䠩��.
     {
      for( INT Count = 0; Count < MAX_VIO_MENU_TITLES; Count ++ )
       VIOMenuManager.RTSettings.Files[ File_number ].Titles[ Count ][ 0 ] = 0;

      for( Count = 0; Count < MAX_VIO_MENU_COMMANDS; Count ++ )
       VIOMenuManager.RTSettings.Files[ File_number ].Commands[ Count ][ 0 ] = 0;
     }

     // ���������� ��ப�, ᮤ�ঠ騥 ��������� ����.
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

     // ���������� ��ப�, ᮤ�ঠ騥 �������.
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

 // �᢮������� ������.
 DosFreeMem( Text ); Text = NULL;

 // ������ ������ "����祭���".
 VIOMenuManager.RTSettings.Files[ File_number ].Active = 1;

 // ���������� �६� ��������� 䠩��.
 VIOMenuManager.RTSettings.Files[ File_number ].Date.year    = Attributes->fdateLastWrite.year;
 VIOMenuManager.RTSettings.Files[ File_number ].Date.month   = Attributes->fdateLastWrite.month;
 VIOMenuManager.RTSettings.Files[ File_number ].Date.day     = Attributes->fdateLastWrite.day;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.hours   = Attributes->ftimeLastWrite.hours;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.minutes = Attributes->ftimeLastWrite.minutes;
 VIOMenuManager.RTSettings.Files[ File_number ].Time.twosecs = Attributes->ftimeLastWrite.twosecs;

 // ������.
 return;
}

// ��� ��⠥� ������� �� 䠩��� ����஥� ���

VOID VIOMenuManager_PrepareOrUpdateSSHCommandSet( VOID )
{
 // ��ᬠ�ਢ��� ᯨ᮪ 䠩��� � �⠥� ��, �᫨ �ॡ����.
 for( INT File_number = 0; File_number < MAX_VIO_MENU_FILES; File_number ++ )
  {
   // �᫨ ��� 䠩�� �� ������ - �த������ ��ॡ��.
   PCHAR File_name = VIOMenuManager.Settings.Files[ File_number ];
   if( File_name[ 0 ] == 0 ) continue;

   // ������ ᢮��⢠ 䠩��.
   FILESTATUS3 Attributes; memset( &Attributes, 0, sizeof( Attributes ) );
   APIRET RC = DosQueryPathInfo( File_name, FIL_STANDARD, &Attributes, sizeof( Attributes ) );

   // �᫨ 䠩�� ��� - ������ ������ "�몫�祭���" � �த������ ��ॡ��.
   if( RC != NO_ERROR )
    {
     VIOMenuManager.RTSettings.Files[ File_number ].Active = 0;
     continue;
    }

   // ����ਬ, ���� �� ���뢠�� 䠩�.
   BYTE Read_file = 0;
   BYTE Update_file = 0;

   // �஢��塞, "����祭�" �� ������ ��� �⮣� 䠩��.
   BYTE Record_is_active = VIOMenuManager.RTSettings.Files[ File_number ].Active;
   if( !Record_is_active ) Read_file = 1;

   // �஢��塞, ���� �� ��� ���� ������� ��� �⮣� 䠩��.
   PCHAR First_command = VIOMenuManager.RTSettings.Files[ File_number ].Commands[ 0 ];
   if( First_command[ 0 ] == 0 ) Read_file = 1;

   // �஢��塞 �६� ��������� 䠩��.
   if( !Read_file )
    {
     if( Attributes.fdateLastWrite.year    != VIOMenuManager.RTSettings.Files[ File_number ].Date.year    ) Update_file = 1;
     if( Attributes.fdateLastWrite.month   != VIOMenuManager.RTSettings.Files[ File_number ].Date.month   ) Update_file = 1;
     if( Attributes.fdateLastWrite.day     != VIOMenuManager.RTSettings.Files[ File_number ].Date.day     ) Update_file = 1;
     if( Attributes.ftimeLastWrite.hours   != VIOMenuManager.RTSettings.Files[ File_number ].Time.hours   ) Update_file = 1;
     if( Attributes.ftimeLastWrite.minutes != VIOMenuManager.RTSettings.Files[ File_number ].Time.minutes ) Update_file = 1;
     if( Attributes.ftimeLastWrite.twosecs != VIOMenuManager.RTSettings.Files[ File_number ].Time.twosecs ) Update_file = 1;
    }

   // ��⠥� 䠩�, �᫨ �� �ॡ����.
   if( Read_file || Update_file ) VIOMenuManager_ReadSSHCommandFile( File_number, &Attributes );
  }

 // ������.
 return;
}

// ��� �஢����, ���� �� � ᯨ᪥ ��ப�, ᮮ⢥�����騥 ���� ���

// Frame_window - ���� ࠬ��.
BYTE VIOMenuManager_CheckCommandSubset( HWND Frame_window )
{
 // ������, ����� ��ப� ���� ��������� � ����.
 INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

 // �஢��塞, ���� �� ���.
 if( File_number == -1 ) return 0;
 if( VIOMenuManager.RTSettings.Files[ File_number ].Active == 0 ) return 0;
 if( VIOMenuManager.RTSettings.Files[ File_number ].Commands[ 0 ][ 0 ] == 0 ) return 0;

 // ������.
 return 1;
}

// ��� ��ࠢ��� ������� � ���� ���

// Frame_window - ���� ࠬ��, Position - ����� ��ப� � ᯨ᪥ ������.
VOID VIOMenuManager_PostCommandCharacters( HWND Frame_window, ULONG Position )
{
 // �᫨ ������� ������� ��� �⮣� ����:
 INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

 if( File_number != -1 )
  {
   // �᫨ ����� ����� ��୮:
   if( Position >= 0 && Position < MAX_VIO_MENU_COMMANDS )
    {
     // ������ ���� ࠡ�祩 ������.
     HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

     // ��ॡ�ࠥ� �㪢� � ��ப�.
     PCHAR String = VIOMenuManager.RTSettings.Files[ File_number ].Commands[ Position ];
     INT Length = strlen( String );

     for( INT Count = 0; Count < Length; Count ++ )
      {
       // �롨ࠥ� �㪢�.
       CHAR Character = String[ Count ];

       // ���뫠�� "~" ⮫쪮 � ��砥, �᫨ �� ��᫥���� �㪢� � ��ப�, � ⠪�� �᫨ �� ���
       // �⮨� �� ���� "~" ��� �஡��. �� �⮬ ����� ��室��� �� ��᫥���� �㪢� � ��ப�.
       if( Character == '~' )
        {
         BYTE Post_Tilde = 0;
         if( !Post_Tilde ) if( Count == Length - 1 ) Post_Tilde = 1;
         if( !Post_Tilde ) if( String[ Count + 1 ] == '~' ) Post_Tilde = 1;
         if( !Post_Tilde ) if( String[ Count + 1 ] == ' ' ) Post_Tilde = 1;
         if( !Post_Tilde ) continue;
        }

       // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
       MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
       ComposeWMCharMessageForVIOWindow( &First_parameter_1, &Second_parameter_1, 0, Character );

       // ���뫠�� ���.
       WinPostMsg( Client_window, WM_CHAR, First_parameter_1, Second_parameter_1 );
      }
    }
  }

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID VIOMenuManager_VIOMenuManagerMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.VIOMenuManager->Priority = MAKELONG( Class, Delta );
  }

 // ��⠥� ��ப� ���� ��� ���� SSH �� 䠩��� ����஥�.
 if( Message->msg == SM_CHECK_ALL_COMMANDS )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ������, ����� ᮮ�饭�� ���� ��ࠢ��� � ��।� ����.
   INT Markers_quantity = (INT) Message->mp2;

   // ��⠥� ��ப� � ������塞 ᯨ᮪.
   // �᫨ ��ப� 㦥 ���⠭� - �஢��塞, ���������� �� 䠩��.
   VIOMenuManager_PrepareOrUpdateSSHCommandSet();

   // ����ਬ, ���� �� � ᯨ᪥ ������� ��� �⮣� ����.
   BYTE Commands_are_present = VIOMenuManager_CheckCommandSubset( Frame_window );

   // �᫨ ��� �뫨 ��⠭� � ���������� � ����� - ����� �� �������� � ��������:
   if( Commands_are_present )
    {
     // ���뫠�� � ���� ���� ��� ��� ᮮ�饭�� WM_MARK.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     if( Markers_quantity >= 1 ) WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_ADD_VIO_MENU_ITEMS, (MPARAM) Frame_window );
     if( Markers_quantity == 2 ) WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SHOW_VIO_MENU_ITEMS, (MPARAM) Frame_window );
    }
  }

 // ��ࠢ�塞 ������� � ����.
 if( Message->msg == SM_POST_VIO_MENU_ITEM )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ������ ����� ��ப� � ᯨ᪥ ������.
   ULONG Position = (ULONG) Message->mp2;

   // ��ࠢ�塞 ������� � ����.
   VIOMenuManager_PostCommandCharacters( Frame_window, Position );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ���������� ��ப � ���� ⥪�⮢�� ���� ���

VOID VIOMenuManager_VIOMenuManagerThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE )
  {
   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.VIOMenuManager->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.VIOMenuManager->Message_queue == NULLHANDLE )
  {
   // �����蠥� ࠡ��� ��⮪�.
   WinTerminate( Thread );

   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ��⮪ ᮧ��� �ᯥ譮.
 Thread_responds.Thread_is_created = 1;

 // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
 QMSG Message = {0};
 while( WinGetMsg( Thread, &Message, 0, 0, 0 ) )
  {
   // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
   QMSG Next_message = {0};
   WinPeekMsg( Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE );
   if( Next_message.msg == Message.msg )
    if( Next_message.mp1 == Message.mp1 )
     if( Next_message.mp2 == Message.mp2 )
      if( Next_message.hwnd == Message.hwnd ) continue;

   // ��ࠡ��뢠�� ᮮ�饭��.
   VIOMenuManager_VIOMenuManagerMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
