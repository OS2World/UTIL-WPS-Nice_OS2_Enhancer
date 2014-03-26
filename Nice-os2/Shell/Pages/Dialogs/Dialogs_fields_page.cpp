
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Dialogs_Fields_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Dialogs_fields;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Applier.Settings.Remember_dialog_fields ) Value = 1;
     WinSendDlgItemMsg( Window, Dialogs_Fields.Settings.Remember_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Window_list_ID ), Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Restore_button_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.TextOnly_button_ID ), Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.AddRemove_ID ), Dialogs_Fields.Settings.Window_Add_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.AddRemove_ID ), Dialogs_Fields.Settings.Window_Remove_ID ), Value );
    }
   return 0;

   // Заполняем список окон.
   case SM_UPDATE_LIST:
    {
     INT Max_strings = 8; PCHAR Strings[ 8 ]; INT Count;
     for( Count = 0; Count < Max_strings; Count ++ ) DosAllocMem( (PPVOID) &Strings[ Count ], SIZE_OF_TITLE, PAG_ALLOCATE );

     strncpy( Strings[ 0 ], Applier.Settings.Dialogs.Incomplete_dialog_1.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 1 ], Applier.Settings.Dialogs.Incomplete_dialog_2.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 2 ], Applier.Settings.Dialogs.Incomplete_dialog_3.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 3 ], Applier.Settings.Dialogs.Incomplete_dialog_4.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 4 ], Applier.Settings.Dialogs.Incomplete_dialog_5.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 5 ], Applier.Settings.Dialogs.Incomplete_dialog_6.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 6 ], Applier.Settings.Dialogs.Incomplete_dialog_7.Window_title, SIZE_OF_TITLE );
     strncpy( Strings[ 7 ], Applier.Settings.Dialogs.Incomplete_dialog_8.Window_title, SIZE_OF_TITLE );

     for( Count = 0; Count < Max_strings; Count ++ )
      {
       INT Space = 0; INT Length = strlen( Strings[ Count ] );

       for( Space = Length; Space > 7; Space -- )
        if( Strings[ Count ][ Space ] == ' ' )
         {
          strcpy( &Strings[ Count ][ Space ], "..." );
          break;
         }
      }

     for( Count = 0; Count < Max_strings; Count ++ )
      if( Strings[ Count ][ 0 ] != 0 )
       strcat( Strings[ Count ], " (" );

     strcat( Strings[ 0 ], Applier.Settings.Dialogs.Incomplete_dialog_1.Exe_name );
     strcat( Strings[ 1 ], Applier.Settings.Dialogs.Incomplete_dialog_2.Exe_name );
     strcat( Strings[ 2 ], Applier.Settings.Dialogs.Incomplete_dialog_3.Exe_name );
     strcat( Strings[ 3 ], Applier.Settings.Dialogs.Incomplete_dialog_4.Exe_name );
     strcat( Strings[ 4 ], Applier.Settings.Dialogs.Incomplete_dialog_5.Exe_name );
     strcat( Strings[ 5 ], Applier.Settings.Dialogs.Incomplete_dialog_6.Exe_name );
     strcat( Strings[ 6 ], Applier.Settings.Dialogs.Incomplete_dialog_7.Exe_name );
     strcat( Strings[ 7 ], Applier.Settings.Dialogs.Incomplete_dialog_8.Exe_name );

     for( Count = 0; Count < Max_strings; Count ++ )
      if( Strings[ Count ][ 0 ] != 0 )
       strcat( Strings[ Count ], ")" );

     {
      HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Window_list_ID );

      Dialogs_Fields.Settings.Dialog_list_is_locked = 1;
      WinShowWindow( List_window, 0 );

      WinSendMsg( List_window, LM_DELETEALL, 0, 0 );
      for( Count = 0; Count < Max_strings; Count ++ )
       {
        if( Strings[ Count ][ 0 ] == 0 ) break;
        WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Strings[ Count ] ) );
       }

      WinShowWindow( List_window, 1 );
      Dialogs_Fields.Settings.Dialog_list_is_locked = 0;
     }

     for( Count = 0; Count < Max_strings; Count ++ ) { DosFreeMem( Strings[ Count ] ); Strings[ Count ] = NULL; }
    }
   return 0;

   // Читаем список диалогов.
   case SM_READ_LIST:
    {
     CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
     HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

     if( Ini_file )
      {
       ReadDialogList( Ini_file );
       PrfCloseProfile( Ini_file );
      }
    }
   return 0;

   // Распознаем настройки.
   case SM_RECOGNIZE_SELECTION:
    {
     if( !Dialogs_Fields.Settings.Dialog_list_is_locked )
      {
       PDLGBOX Dialog = Dialogs_Fields.Settings.Selected_dialog;

       BYTE Enabled = 0;  if( Dialog ) Enabled = Dialog->Enabled;
       BYTE TextOnly = 0; if( Dialog ) TextOnly = Dialog->Text_fields_only;

       WinSendMsg( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Restore_button_ID ), BM_SETCHECK, MPFROMLONG( Enabled ), 0 );
       WinSendMsg( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.TextOnly_button_ID ), BM_SETCHECK, MPFROMLONG( TextOnly ), 0 );
      }
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Dialogs_Fields.Settings.Remember_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Applier.Settings.Remember_dialog_fields = 0;
           else Applier.Settings.Remember_dialog_fields = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Dialogs_Fields.Settings.Window_list_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case LN_SELECT:
          {
           if( !Dialogs_Fields.Settings.Dialog_list_is_locked )
            {
             HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Window_list_ID );

             INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
             if( Selected_string == LIT_NONE ) return 0;

             {
              Dialogs_Fields.Settings.Selected_dialog = NULL;

              switch( Selected_string )
               {
                case 0: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_1; break;
                case 1: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_2; break;
                case 2: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_3; break;
                case 3: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_4; break;
                case 4: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_5; break;
                case 5: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_6; break;
                case 6: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_7; break;
                case 7: Dialogs_Fields.Settings.Selected_dialog = &Applier.Settings.Dialogs.Incomplete_dialog_8; break;
               }
             }

             WinSendMsg( Window, SM_RECOGNIZE_SELECTION, 0, 0 );
            }
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Dialogs_Fields.Settings.Restore_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           if( Dialogs_Fields.Settings.Selected_dialog != NULL )
            {
             PDLGBOX Dialog = Dialogs_Fields.Settings.Selected_dialog;

             ULONG Button_is_checked = (ULONG) WinSendMsg( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Restore_button_ID ), BM_QUERYCHECK, 0, 0 );

             if( Button_is_checked ) Dialog->Enabled = 0;
             else Dialog->Enabled = 1;

             WinSendMsg( Window, SM_RECOGNIZE_SELECTION, 0, 0 );
            }
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Dialogs_Fields.Settings.TextOnly_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           if( Dialogs_Fields.Settings.Selected_dialog != NULL )
            {
             PDLGBOX Dialog = Dialogs_Fields.Settings.Selected_dialog;

             ULONG Button_is_checked = (ULONG) WinSendMsg( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.TextOnly_button_ID ), BM_QUERYCHECK, 0, 0 );

             if( Button_is_checked ) Dialog->Text_fields_only = 0;
             else Dialog->Text_fields_only = 1;

             WinSendMsg( Window, SM_RECOGNIZE_SELECTION, 0, 0 );
            }
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

     if( WM_Control_Button_ID == Dialogs_Fields.Settings.Window_Add_ID )
      {
       if( Applier.Settings.Dialogs.Incomplete_dialog_1.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_2.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_3.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_4.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_5.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_6.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_7.Frame_type != 0 )
       if( Applier.Settings.Dialogs.Incomplete_dialog_8.Frame_type != 0 ) return 0;

       if( !Enhancer.Detector_dialog.Detector_is_running )
        {
         Enhancer.Detector_dialog.Customer_window = Window;

         Enhancer.Detector_dialog.Scan_dialog = 1;
         Enhancer.Detector_dialog.Scan_fields_in_dialog = 1;
         Enhancer.Detector_dialog.Include_shell_windows = 1;

         OpenDETECTOR();
        }
      }

     if( WM_Control_Button_ID == Dialogs_Fields.Settings.Window_Remove_ID )
      {
       HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Dialogs_Fields.Settings.WinList_Container_ID ), Dialogs_Fields.Settings.ControlBox_ID ), Dialogs_Fields.Settings.Window_list_ID );

       INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
       if( Selected_string == LIT_NONE ) return 0;

       WinSendMsg( List_window, LM_DELETEITEM, MPFROMLONG( Selected_string ), 0 );

       {
        CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
        switch( Selected_string )
         {
          case 0:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_1, &Applier.Settings.Dialogs.Incomplete_dialog_2, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_2, &Applier.Settings.Dialogs.Incomplete_dialog_3, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_4, &Applier.Settings.Dialogs.Incomplete_dialog_5, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 1:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_2, &Applier.Settings.Dialogs.Incomplete_dialog_3, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_4, &Applier.Settings.Dialogs.Incomplete_dialog_5, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 2:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_3, &Applier.Settings.Dialogs.Incomplete_dialog_4, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_4, &Applier.Settings.Dialogs.Incomplete_dialog_5, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 3:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_4, &Applier.Settings.Dialogs.Incomplete_dialog_5, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 4:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_5, &Applier.Settings.Dialogs.Incomplete_dialog_6, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 5:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_6, &Applier.Settings.Dialogs.Incomplete_dialog_7, sizeof( DLGBOX ) );
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 6:
           memcpy( &Applier.Settings.Dialogs.Incomplete_dialog_7, &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;

          case 7:
           bzero( &Applier.Settings.Dialogs.Incomplete_dialog_8, sizeof( DLGBOX ) );
          break;
         }
       }

       WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         PrfWriteProfileData( Ini_file, "Settings", "Remember dialog fields", &Applier.Settings.Remember_dialog_fields, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Dialogs", NULL, NULL, 0 );

         PrfCloseProfile( Ini_file );

         WriteDialogList( NULL );

         BroadcastRSMessages();
         NiceReadSettings();
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
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
