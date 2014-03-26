
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY VIOWindows_SSH_Prompts_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.VIOWindows_SSH_prompts;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( VIOMenuManager.Settings.SSH_Commands ) Value = 1;
     WinSendDlgItemMsg( Window, VIOWindows_SSH_Prompts.Settings.SSH_Commands_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableControl( Window, VIOWindows_SSH_Prompts.Settings.Use_AltTilde_button_ID, Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID ), VIOWindows_SSH_Prompts.Settings.SelectBox_ID ), VIOWindows_SSH_Prompts.Settings.File_list_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID ), VIOWindows_SSH_Prompts.Settings.AddRemove_ID ), VIOWindows_SSH_Prompts.Settings.File_Add_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID ), VIOWindows_SSH_Prompts.Settings.AddRemove_ID ), VIOWindows_SSH_Prompts.Settings.File_Remove_ID ), Value );

     Value = 0; if( VIOMenuManager.Settings.Use_AltTilde ) Value = 1;
     WinSendDlgItemMsg( Window, VIOWindows_SSH_Prompts.Settings.Use_AltTilde_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // Распознаем настройки.
   case SM_UPDATE_LIST:
    {
     HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID ), VIOWindows_SSH_Prompts.Settings.SelectBox_ID ), VIOWindows_SSH_Prompts.Settings.File_list_ID );

     WinSendMsg( List_window, LM_DELETEALL, 0, 0 );

     for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
      if( VIOMenuManager.Settings.Files[ Count ][ 0 ] != 0 )
       WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( FindNameInPath( VIOMenuManager.Settings.Files[ Count ] ) ) );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == VIOWindows_SSH_Prompts.Settings.SSH_Commands_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) VIOMenuManager.Settings.SSH_Commands = 0;
           else VIOMenuManager.Settings.SSH_Commands = 1;

           BroadcastMessage( SM_SHOW_SETTINGS );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == VIOWindows_SSH_Prompts.Settings.Use_AltTilde_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) VIOMenuManager.Settings.Use_AltTilde = 0;
           else VIOMenuManager.Settings.Use_AltTilde = 1;

           BroadcastMessage( SM_SHOW_SETTINGS );
          }
         break;
        }
      }
    }
   return 0;

   // Обрабатываем нажатия на кнопки.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == VIOWindows_SSH_Prompts.Settings.File_Add_ID )
      {
       BYTE List_is_full = 1;
       for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
        if( VIOMenuManager.Settings.Files[ Count ][ 0 ] == 0 ) { List_is_full = 0; break; }

       if( List_is_full ) return 0;

       FILEDLG Parameters; HWND OpenFile_window;

       bzero( &Parameters, sizeof( FILEDLG ) );
       Parameters.cbSize = sizeof( FILEDLG );
       Parameters.fl = FDS_OPEN_DIALOG | FDS_CENTER;

       LONG Code_page = Enhancer.Code_page;

       if( Code_page == RUSSIAN ) Parameters.pszTitle = StrConst_RU_Pages_VIOWindows_SSH_prompts_Dialog;
       else Parameters.pszTitle = StrConst_EN_Pages_VIOWindows_SSH_prompts_Dialog;

       {
        ULONG Current_drive = 0; ULONG Drive_map = 0;
        DosQueryCurrentDisk( &Current_drive, &Drive_map );
        Parameters.szFullFile[ 0 ] = (CHAR) Current_drive + 64;
        Parameters.szFullFile[ 1 ] = 0;
        strcat( Parameters.szFullFile, ":\\*.txt" );
       }

       OpenFile_window = WinFileDlg( HWND_DESKTOP, Window, &Parameters );

       if( OpenFile_window != NULLHANDLE ) if( Parameters.lReturn == DID_OK )
        if( strifind( ".txt", Parameters.szFullFile ) )
         {
          BYTE Already_present = 0;
          for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
           if( VIOMenuManager.Settings.Files[ Count ][ 0 ] != 0 )
            if( stricmpe( VIOMenuManager.Settings.Files[ Count ], Parameters.szFullFile ) == EQUALLY )
             {
              Already_present = 1;
              break;
             }

          if( !Already_present )
           {
            for( Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
             if( VIOMenuManager.Settings.Files[ Count ][ 0 ] == 0 )
              {
               strncpy( VIOMenuManager.Settings.Files[ Count ], Parameters.szFullFile, SIZE_OF_PATH );
               break;
              }

            BroadcastRSMessages();
           }
         }
      }

     if( WM_Control_Button_ID == VIOWindows_SSH_Prompts.Settings.File_Remove_ID )
      {
       HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID ), VIOWindows_SSH_Prompts.Settings.SelectBox_ID ), VIOWindows_SSH_Prompts.Settings.File_list_ID );

       INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
       if( Selected_string == LIT_NONE ) return 0;

       WinSendMsg( List_window, LM_DELETEITEM, MPFROMLONG( Selected_string ), 0 );

       for( INT Count = Selected_string; Count < MAX_VIO_MENU_FILES - 1; Count ++ )
        memcpy( VIOMenuManager.Settings.Files[ Count ], VIOMenuManager.Settings.Files[ Count + 1 ], SIZE_OF_PATH );

       bzero( VIOMenuManager.Settings.Files[ MAX_VIO_MENU_FILES - 1 ], SIZE_OF_PATH );

       WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         PrfWriteProfileData( Ini_file, "Settings", "SSH Commands", &VIOMenuManager.Settings.SSH_Commands, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Use AltTilde", &VIOMenuManager.Settings.Use_AltTilde, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "SSH prompts", NULL, NULL, 0 );

         for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
          {
           if( VIOMenuManager.Settings.Files[ Count ][ 0 ] != 0 )
            {
             CHAR Number[ 4 ] = ""; itoa( Count, Number, 10 );
             CHAR Ini_record_name[ SIZE_OF_NAME ] = "File "; strcat( Ini_record_name, Number );

             PrfWriteProfileData( Ini_file, "SSH prompts", Ini_record_name, VIOMenuManager.Settings.Files[ Count ], strlen( VIOMenuManager.Settings.Files[ Count ] ) + 1 );
            }
          }

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       BYTE Files_are_present = 0;

       for( INT Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
        if( VIOMenuManager.Settings.Files[ Count ][ 0 ] != 0 )
         {
          Files_are_present = 1;
          break;
         }

       if( Files_are_present )
        {
         CHAR String[ 256 ] = ""; LONG Reply = 0;
         BYTE Clear_list = 0;

         LONG Code_page = Enhancer.Code_page;

         if( Code_page == RUSSIAN ) strcpy( String, StrConst_RU_Pages_VIOWindows_SSH_prompts_Question );
         else strcpy( String, StrConst_EN_Pages_VIOWindows_SSH_prompts_Question );

         {
          CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
          Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO );
         }

         if( Reply == MBID_YES ) Clear_list = 1;

         if( Clear_list )
          {
           CHAR Empty_path[ SIZE_OF_PATH ] = ""; bzero( Empty_path, SIZE_OF_PATH );

           for( Count = 0; Count < MAX_VIO_MENU_FILES; Count ++ )
            memcpy( VIOMenuManager.Settings.Files[ Count ], Empty_path, SIZE_OF_PATH );

           WinPostMsg( Window, SM_UPDATE_LIST, 0, 0 );
          }
        }

       if( Page->SetDefSettings ) Page->SetDefSettings( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext1 ) Page->SetDefSettings_Ext1( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext2 ) Page->SetDefSettings_Ext2( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext3 ) Page->SetDefSettings_Ext3( Page->Settings_to_show );

       WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
      }

     if( WM_Control_Button_ID == HP_BUTTON_ID )
      {
       Help( Page->Settings_to_show, Enhancer.Code_page );
      }
    }
   return 0;
  }

 // Возврат.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}


