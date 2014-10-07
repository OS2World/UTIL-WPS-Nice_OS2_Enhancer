
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Keyboard_Actions_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Keyboard_actions;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Definer.Settings.Define_keys ) Value = 1;

     WinEnableWindow( WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Key_list_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Action_list_ID ), Value );

     WinShowWindow( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.Detect_button_ID ), Value );
     WinShowWindow( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.ExeName_filebox_ID ), Value );
    }
   return 0;

   // Распознаем настройки.
   case SM_RECOGNIZE_SELECTION:
    {
     if( !Keyboard_Actions.Settings.Key_list_is_locked )
      {
       HWND Key_list_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Key_list_ID );
       HWND Action_list_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Action_list_ID );

       LONG Key_number = (LONG) WinSendMsg( Key_list_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );

       INT Action = DO_NOT_DEFINE;
       if( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Key != EMPTY_KEY_ITEM )
        Action = *( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Key );

       Keyboard_Actions.Settings.Key_code = (PINT) Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Scan_code;

       {
        INT Required_action_number = 0;
        for( INT Count = 0; Count < MAX_ACTIONS; Count ++ )
         if( Keyboard_Actions.Settings.Actions.Actions[ Count ] == Action )
          { Required_action_number = Count; break; }

        WinSendMsg( Action_list_window, LM_SELECTITEM, MPFROMLONG( Required_action_number ), MPFROMLONG( 1 ) );
       }

       HWND FileBox_window = WinWindowFromID( Page->Window, Keyboard_Actions.Settings.ExeName_filebox_ID );
       HWND Detect_button = WinWindowFromID( Page->Window, Keyboard_Actions.Settings.Detect_button_ID );

       {
        BYTE Higher_level_permission = 0;
        if( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Permission != NULL )
         Higher_level_permission = *( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Permission );

        WinEnableWindow( Action_list_window, Higher_level_permission );

        WinEnableWindow( WinWindowFromID( FileBox_window, Keyboard_Actions.Settings.ExeName_label_ID ), Higher_level_permission );
        WinEnableWindow( WinWindowFromID( FileBox_window, Keyboard_Actions.Settings.ExeName_name_ID ), Higher_level_permission );
        WinEnableWindow( WinWindowFromID( FileBox_window, Keyboard_Actions.Settings.ExeName_button_ID ), Higher_level_permission );

        WinEnableWindow( Detect_button, Higher_level_permission );
       }

       {
        BYTE Show_detect_button = 0;
        if( Keyboard_Actions.Settings.Key_code != NULL ) Show_detect_button = 1;

        BYTE Update_page_window = 0;
        if( !Show_detect_button )
         {
          if( WinIsWindowVisible( Detect_button ) ) Update_page_window = 1;
         }

        WinShowWindow( Detect_button, Show_detect_button );
        if( Update_page_window ) UpdatePageWindow( Page );
       }
      }
    }
   return 0;

   // Распознаем настройки, если выбрана строка во втором списке.
   case SM_RECOGNIZE_L2_SELECTION:
    {
     if( !Keyboard_Actions.Settings.Action_list_is_locked )
      {
       HWND Key_list_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Key_list_ID );
       HWND Action_list_window = WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.SplitView_ID ), Keyboard_Actions.Settings.Action_list_ID );

       LONG Key_number = (LONG) WinSendMsg( Key_list_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );

       INT Action = DO_NOT_DEFINE;

       {
        INT Action_number = (LONG) WinSendMsg( Action_list_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
        if( Action_number >= 0 ) Action = Keyboard_Actions.Settings.Actions.Actions[ Action_number ];
       }

       if( Action != EMPTY_ACTION_ITEM )
        if( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Key != EMPTY_KEY_ITEM )
         *( Keyboard_Actions.Settings.Actions.Keys[ Key_number ].Key ) = Action;

       INT Position = -1;

       if( Action == SHOW_USER_TOOL_1 ) Position = FindApplicationInRepository( APP_USER_TOOL_1 );
       if( Action == SHOW_USER_TOOL_2 ) Position = FindApplicationInRepository( APP_USER_TOOL_2 );
       if( Action == SHOW_USER_TOOL_3 ) Position = FindApplicationInRepository( APP_USER_TOOL_3 );
       if( Action == SHOW_USER_TOOL_4 ) Position = FindApplicationInRepository( APP_USER_TOOL_4 );
       if( Action == SHOW_USER_TOOL_5 ) Position = FindApplicationInRepository( APP_USER_TOOL_5 );
       if( Action == SHOW_USER_TOOL_6 ) Position = FindApplicationInRepository( APP_USER_TOOL_6 );
       if( Action == SHOW_USER_TOOL_7 ) Position = FindApplicationInRepository( APP_USER_TOOL_7 );
       if( Action == SHOW_USER_TOOL_8 ) Position = FindApplicationInRepository( APP_USER_TOOL_8 );
       if( Action == SHOW_USER_TOOL_9 ) Position = FindApplicationInRepository( APP_USER_TOOL_9 );
       if( Action == SHOW_USER_TOOL_A ) Position = FindApplicationInRepository( APP_USER_TOOL_A );
       if( Action == SHOW_USER_TOOL_B ) Position = FindApplicationInRepository( APP_USER_TOOL_B );
       if( Action == SHOW_USER_TOOL_C ) Position = FindApplicationInRepository( APP_USER_TOOL_C );
       if( Action == SHOW_USER_TOOL_D ) Position = FindApplicationInRepository( APP_USER_TOOL_D );
       if( Action == SHOW_USER_TOOL_E ) Position = FindApplicationInRepository( APP_USER_TOOL_E );
       if( Action == SHOW_USER_TOOL_F ) Position = FindApplicationInRepository( APP_USER_TOOL_F );

       Keyboard_Actions.Settings.UserTool_name = NULL;
       Keyboard_Actions.Settings.UserTool_path = NULL;

       if( Position != -1 )
        {
         Keyboard_Actions.Settings.UserTool_name = Repository.Items[ Position ].Exe_name_1;
         Keyboard_Actions.Settings.UserTool_path = Repository.Items[ Position ].Path;

         WinSetWindowText( WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.ExeName_filebox_ID ), Keyboard_Actions.Settings.ExeName_name_ID ), Keyboard_Actions.Settings.UserTool_name );
        }

       {
        HWND FileBox_window = WinWindowFromID( Page->Window, Keyboard_Actions.Settings.ExeName_filebox_ID );

        BYTE Show_tool_filebox = 1;
        if( Position == -1 ) Show_tool_filebox = 0;

        BYTE Update_page_window = 0;
        if( !Show_tool_filebox )
         {
          if( WinIsWindowVisible( FileBox_window ) ) Update_page_window = 1;
         }

        WinShowWindow( FileBox_window, Show_tool_filebox );
        if( Update_page_window ) UpdatePageWindow( Page );
       }
      }
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Keyboard_Actions.Settings.Key_list_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case LN_SELECT:
          {
           WinSendMsg( Window, SM_RECOGNIZE_SELECTION, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Keyboard_Actions.Settings.Action_list_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case LN_SELECT:
          {
           WinSendMsg( Window, SM_RECOGNIZE_L2_SELECTION, 0, 0 );
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

     if( WM_Control_Button_ID == Keyboard_Actions.Settings.ExeName_button_ID )
      {
       if( Keyboard_Actions.Settings.UserTool_name != NULL && Keyboard_Actions.Settings.UserTool_path != NULL )
        {
         FILEDLG Parameters;
         bzero( &Parameters, sizeof( FILEDLG ) );
         Parameters.cbSize = sizeof( FILEDLG );
         Parameters.fl = FDS_OPEN_DIALOG | FDS_CENTER;

         LONG Code_page = Enhancer.Code_page;
         if( Code_page == RUSSIAN ) Parameters.pszTitle = StrConst_RU_Pages_Keyboard_actions_ExeName_dialog;
         else Parameters.pszTitle = StrConst_EN_Pages_Keyboard_actions_ExeName_dialog;

         if( Keyboard_Actions.RTSettings.FileDlg_path[ 0 ] == 0 )
          {
           GetCurrentPath( Parameters.szFullFile );
           strcat( Parameters.szFullFile, "\\*.exe;*.cmd" );
          }
         else
          {
           strcpy( Parameters.szFullFile, Keyboard_Actions.RTSettings.FileDlg_path );
           strcat( Parameters.szFullFile, "\\*.exe;*.cmd" );
          }

         HWND OpenFile_window = WinFileDlg( HWND_DESKTOP, Window, &Parameters );

         if( OpenFile_window != NULLHANDLE ) if( Parameters.lReturn == DID_OK )
          {
           bzero( Keyboard_Actions.Settings.UserTool_name, SIZE_OF_NAME );
           strcpy( Keyboard_Actions.Settings.UserTool_name, FindNameInPath( Parameters.szFullFile ) );

           bzero( Keyboard_Actions.Settings.UserTool_path, SIZE_OF_PATH );
           strcpy( Keyboard_Actions.Settings.UserTool_path, Parameters.szFullFile );
           CutNameInPath( Keyboard_Actions.Settings.UserTool_path );

           strncpy( Keyboard_Actions.RTSettings.FileDlg_path, Parameters.szFullFile, SIZE_OF_PATH );
           CutNameInPath( Keyboard_Actions.RTSettings.FileDlg_path );

           WinSetWindowText( WinWindowFromID( WinWindowFromID( Page->Window, Keyboard_Actions.Settings.ExeName_filebox_ID ), Keyboard_Actions.Settings.ExeName_name_ID ), Keyboard_Actions.Settings.UserTool_name );
          }
        }
      }

     if( WM_Control_Button_ID == Keyboard_Actions.Settings.Detect_button_ID )
      {
       if( Keyboard_Actions.Settings.Key_code != NULL )
        {
         if( !Enhancer.Detector_dialog.Detector_is_running )
          {
           Enhancer.Detector_dialog.Customer_window = Window;
           Enhancer.Detector_dialog.Key_code = Keyboard_Actions.Settings.Key_code;

           OpenDETECTOR();
          }
        }
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         #include "Pages\\Keyboard\\Keyboard_actions_save.cpp"

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
         NiceReadRepository();
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
