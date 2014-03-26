
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Priority_Sedative_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Priority_sedative;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( PriorityManager.Settings.Normalize_priority ) Value = 1;
     WinSendDlgItemMsg( Window, Priority_Sedative.Settings.Normalize_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Priority_Sedative.Settings.WinList_Container_ID ), Priority_Sedative.Settings.SelectBox_ID ), Priority_Sedative.Settings.Window_list_ID ), Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Priority_Sedative.Settings.WinList_Container_ID ), Priority_Sedative.Settings.AddRemove_ID ), Priority_Sedative.Settings.Window_Add_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Priority_Sedative.Settings.WinList_Container_ID ), Priority_Sedative.Settings.AddRemove_ID ), Priority_Sedative.Settings.Window_Remove_ID ), Value );
    }
   return 0;

   // Отображаем список окон.
   case SM_UPDATE_LIST:
    {
     HWND ListBox_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Priority_Sedative.Settings.WinList_Container_ID ), Priority_Sedative.Settings.SelectBox_ID ), Priority_Sedative.Settings.Window_list_ID );

     WinSendMsg( ListBox_window, LM_DELETEALL, 0, 0 );

     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) );
     if( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name[ 0 ] != 0 ) WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Priority_Sedative.Settings.Normalize_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) PriorityManager.Settings.Normalize_priority = 0;
           else PriorityManager.Settings.Normalize_priority = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
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

     if( WM_Control_Button_ID == Priority_Sedative.Settings.Window_Add_ID )
      {
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name[ 0 ] != 0 )
       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name[ 0 ] != 0 ) return 0;

       if( !Enhancer.Detector_dialog.Detector_is_running )
        {
         Enhancer.Detector_dialog.Customer_window = Window;

         Enhancer.Detector_dialog.Window_name_1 = PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name;
         Enhancer.Detector_dialog.Window_name_2 = PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name;
         Enhancer.Detector_dialog.Window_name_3 = PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name;
         Enhancer.Detector_dialog.Window_name_4 = PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name;
         Enhancer.Detector_dialog.Window_name_5 = PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name;
         Enhancer.Detector_dialog.Window_name_6 = PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name;
         Enhancer.Detector_dialog.Window_name_7 = PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name;
         Enhancer.Detector_dialog.Window_name_8 = PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name;

         OpenDETECTOR();
        }
      }

     if( WM_Control_Button_ID == Priority_Sedative.Settings.Window_Remove_ID )
      {
       HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Priority_Sedative.Settings.WinList_Container_ID ), Priority_Sedative.Settings.SelectBox_ID ), Priority_Sedative.Settings.Window_list_ID );

       INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
       if( Selected_string == LIT_NONE ) return 0;

       WinSendMsg( List_window, LM_DELETEITEM, MPFROMLONG( Selected_string ), 0 );

       {
        CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
        switch( Selected_string )
         {
          case 0:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 1:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 2:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 3:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 4:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 5:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 6:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, SIZE_OF_NAME );
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 7:
           memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );
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
         PrfWriteProfileData( Ini_file, "Settings", "Normalize priority", &PriorityManager.Settings.Normalize_priority, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 1 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 2 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 3 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 4 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 5 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 6 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 7 name", NULL, 0 );
         PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 8 name", NULL, 0 );

         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 1 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 2 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 3 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 4 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 5 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 6 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 7 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) + 1 );
         if( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "Priority", "Exceeded priority 8 name", PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, strlen( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) + 1 );

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

       if( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name[ 0 ] != 0 || PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name[ 0 ] != 0 ||
           PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name[ 0 ] != 0 || PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name[ 0 ] != 0 ||
           PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name[ 0 ] != 0 || PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name[ 0 ] != 0 ||
           PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name[ 0 ] != 0 || PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name[ 0 ] != 0 )
        {
         if( Code_page == RUSSIAN ) strcpy( String, StrConst_RU_Pages_Priority_sedative_Question );
         else strcpy( String, StrConst_EN_Pages_Priority_sedative_Question );

         {
          CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
          Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO );
         }

         if( Reply == MBID_YES ) Clear_list = 1;
        }

       if( Clear_list )
        {
         CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, Empty_name, SIZE_OF_NAME );
         memcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Empty_name, SIZE_OF_NAME );

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
