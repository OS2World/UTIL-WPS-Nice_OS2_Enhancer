
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY WinList_Settings_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.WinList_settings;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Remover.Settings.Remove_items_from_Window_list ) Value = 1;
     WinSendDlgItemMsg( Window, WinList_Settings.Settings.Modify_WinList_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Hidden_list_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Hidden_buttons_ID ), WinList_Settings.Settings.Hidden_Move2V_button_ID ), Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Visible_list_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Visible_buttons_ID ), WinList_Settings.Settings.Visible_Move2H_button_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Visible_buttons_ID ), WinList_Settings.Settings.Visible_Refresh_button_ID ), Value );
    }
   return 0;

   // Отображаем список.
   case SM_UPDATE_LIST:
    {
     {
      HWND Hidden_ListBox_window = WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Hidden_list_ID );

      WinSendMsg( Hidden_ListBox_window, LM_DELETEALL, 0, 0 );

      if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_1_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_2_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_3_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_4_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_5_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_6_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_7_name ) );
      if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] != 0 ) WinSendMsg( Hidden_ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Remover.Settings.WinListNames.Remove_from_list_8_name ) );
     }

     {
      HWND Visible_ListBox_window = WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Visible_list_ID );
      ShowSwitchListItems( Visible_ListBox_window );
     }
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == WinList_Settings.Settings.Modify_WinList_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Remover.Settings.Remove_items_from_Window_list = 0;
           else Remover.Settings.Remove_items_from_Window_list = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }
    }
   break;

   // Обрабатываем нажатия на кнопки.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == WinList_Settings.Settings.Hidden_Move2V_button_ID )
      {
       HWND Hidden_ListBox_window = WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Hidden_list_ID );
       INT Selected_string = (INT) WinSendMsg( Hidden_ListBox_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );

       if( Selected_string != LIT_NONE )
        {
         CHAR Name[ SIZE_OF_NAME ] = "";
         WinSendMsg( Hidden_ListBox_window, LM_QUERYITEMTEXT, MPFROM2SHORT( Selected_string, SIZE_OF_NAME ), MPFROMP( Name ) );

         ShowItemInSwitchList( Name, 1 );

         {
          CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );

          switch( Selected_string )
           {
            case 0:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_1_name, Remover.Settings.WinListNames.Remove_from_list_2_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_2_name, Remover.Settings.WinListNames.Remove_from_list_3_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_3_name, Remover.Settings.WinListNames.Remove_from_list_4_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_4_name, Remover.Settings.WinListNames.Remove_from_list_5_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Remover.Settings.WinListNames.Remove_from_list_6_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 1:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_2_name, Remover.Settings.WinListNames.Remove_from_list_3_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_3_name, Remover.Settings.WinListNames.Remove_from_list_4_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_4_name, Remover.Settings.WinListNames.Remove_from_list_5_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Remover.Settings.WinListNames.Remove_from_list_6_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 2:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_3_name, Remover.Settings.WinListNames.Remove_from_list_4_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_4_name, Remover.Settings.WinListNames.Remove_from_list_5_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Remover.Settings.WinListNames.Remove_from_list_6_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 3:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_4_name, Remover.Settings.WinListNames.Remove_from_list_5_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Remover.Settings.WinListNames.Remove_from_list_6_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 4:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Remover.Settings.WinListNames.Remove_from_list_6_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 5:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Remover.Settings.WinListNames.Remove_from_list_7_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 6:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Remover.Settings.WinListNames.Remove_from_list_8_name, SIZE_OF_NAME );
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;

            case 7:
             memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );
            break;
           }
         }

         WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
        }
      }

     if( WM_Control_Button_ID == WinList_Settings.Settings.Visible_Move2H_button_ID )
      {
       HWND Visible_ListBox_window = WinWindowFromID( WinWindowFromID( Window, WinList_Settings.Settings.Container_ID ), WinList_Settings.Settings.Visible_list_ID );
       INT Selected_string = (INT) WinSendMsg( Visible_ListBox_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );

       if( Selected_string != LIT_NONE )
        {
         CHAR Name[ SIZE_OF_NAME ] = "";
         WinSendMsg( Visible_ListBox_window, LM_QUERYITEMTEXT, MPFROM2SHORT( Selected_string, SIZE_OF_NAME ), MPFROMP( Name ) );

         BYTE Name_is_present_in_list = 0;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_1_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_2_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_3_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_4_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_5_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_6_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_7_name ) == EQUALLY ) Name_is_present_in_list = 1;
         if( strcmp( Name, Remover.Settings.WinListNames.Remove_from_list_8_name ) == EQUALLY ) Name_is_present_in_list = 1;

         if( !Name_is_present_in_list )
          {
           PCHAR Item = NULL;

           if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_8_name;
           if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_7_name;
           if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_6_name;
           if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_5_name;
           if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_4_name;
           if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_3_name;
           if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_2_name;
           if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] == 0 ) Item = Remover.Settings.WinListNames.Remove_from_list_1_name;

           if( Item != NULL )
            {
             strncpy( Item, Name, SIZE_OF_NAME );

             ShowItemInSwitchList( Name, 0 );

             WinPostMsg( Window, WM_COMMAND, (MPARAM) OK_BUTTON_ID, 0 );
            }
          }
        }
      }

     if( WM_Control_Button_ID == WinList_Settings.Settings.Visible_Refresh_button_ID )
      {
       WinSendMsg( Window, SM_UPDATE_LIST, 0, 0 );
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         BYTE Hide_known_applications = 1;

         PrfWriteProfileData( Ini_file, "Settings", "Remove items from Window list", &Remover.Settings.Remove_items_from_Window_list, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Hide known applications", &Hide_known_applications, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 1 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 2 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 3 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 4 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 5 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 6 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 7 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "WinList", "Remove from list 8 name", NULL, 0 );

         if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 1 name", Remover.Settings.WinListNames.Remove_from_list_1_name, strlen( Remover.Settings.WinListNames.Remove_from_list_1_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 2 name", Remover.Settings.WinListNames.Remove_from_list_2_name, strlen( Remover.Settings.WinListNames.Remove_from_list_2_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 3 name", Remover.Settings.WinListNames.Remove_from_list_3_name, strlen( Remover.Settings.WinListNames.Remove_from_list_3_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 4 name", Remover.Settings.WinListNames.Remove_from_list_4_name, strlen( Remover.Settings.WinListNames.Remove_from_list_4_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 5 name", Remover.Settings.WinListNames.Remove_from_list_5_name, strlen( Remover.Settings.WinListNames.Remove_from_list_5_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 6 name", Remover.Settings.WinListNames.Remove_from_list_6_name, strlen( Remover.Settings.WinListNames.Remove_from_list_6_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 7 name", Remover.Settings.WinListNames.Remove_from_list_7_name, strlen( Remover.Settings.WinListNames.Remove_from_list_7_name ) + 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "WinList", "Remove from list 8 name", Remover.Settings.WinListNames.Remove_from_list_8_name, strlen( Remover.Settings.WinListNames.Remove_from_list_8_name ) + 1 );

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       CHAR String[ 256 ] = ""; LONG Reply = 0;
       BYTE Clear_list = 0;
       LONG Code_page = Enhancer.Code_page;

       if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] != 0 || Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] != 0 ||
           Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] != 0 || Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] != 0 ||
           Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] != 0 || Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] != 0 ||
           Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] != 0 || Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] != 0 )
        {
         if( Code_page == RUSSIAN ) strcpy( String, StrConst_RU_Pages_WinList_settings_Question );
         else strcpy( String, StrConst_EN_Pages_WinList_settings_Question );

         {
          CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
          Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO );
         }

         if( Reply == MBID_YES ) Clear_list = 1;
        }

       if( Clear_list )
        {
         if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_1_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_2_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_3_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_4_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_5_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_6_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_7_name, 1 );
         if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] != 0 ) ShowItemInSwitchList( Remover.Settings.WinListNames.Remove_from_list_8_name, 1 );

         CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_1_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_2_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_3_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_4_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_5_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_6_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_7_name, Empty_name, SIZE_OF_NAME );
         memcpy( Remover.Settings.WinListNames.Remove_from_list_8_name, Empty_name, SIZE_OF_NAME );

         WinPostMsg( Window, SM_UPDATE_LIST, 0, 0 );
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
