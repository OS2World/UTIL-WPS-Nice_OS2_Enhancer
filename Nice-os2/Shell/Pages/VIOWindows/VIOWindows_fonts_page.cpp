
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY VIOWindows_Fonts_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.VIOWindows_fonts;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( VIOFontManager.Settings.Change_VIO_font_metrics ) Value = 1;
     WinSendDlgItemMsg( Window, VIOWindows_Fonts.Settings.SetFont_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableControl( Window, VIOWindows_Fonts.Settings.KnownApps_button_ID, Value );

     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Selected_font_cmbox_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Application_list_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.AddRemove_ID ), VIOWindows_Fonts.Settings.Application_Add_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.AddRemove_ID ), VIOWindows_Fonts.Settings.Application_Remove_ID ), Value );

     Value = 0; if( VIOFontManager.Settings.Change_fonts_for_known_applications ) Value = 1;
     WinSendDlgItemMsg( Window, VIOWindows_Fonts.Settings.KnownApps_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // Распознаем настройки.
   case SM_UPDATE_LIST:
    {
     HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Application_list_ID );

     VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 1;
     WinShowWindow( List_window, 0 );

     WinSendMsg( List_window, LM_DELETEALL, 0, 0 );

     if( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name ) );
     if( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name ) );

     WinShowWindow( List_window, 1 );
     VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 0;

     HWND ComboBox_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Selected_font_cmbox_ID );

     WinSendMsg( ComboBox_window, LM_SELECTITEM, MPFROMLONG( LIT_NONE ), MPFROMLONG( 1 ) );
     WinSetWindowText( ComboBox_window, "" );

     WinSendMsg( List_window, LM_SELECTITEM, MPFROMLONG( LIT_NONE ), MPFROMLONG( 1 ) );
     WinSendMsg( List_window, LM_SELECTITEM, MPFROMLONG( 0 ), MPFROMLONG( 1 ) );

     VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_1; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_1;
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == VIOWindows_Fonts.Settings.SetFont_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) VIOFontManager.Settings.Change_VIO_font_metrics = 0;
           else VIOFontManager.Settings.Change_VIO_font_metrics = 1;

           BroadcastMessage( SM_SHOW_SETTINGS );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == VIOWindows_Fonts.Settings.KnownApps_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) VIOFontManager.Settings.Change_fonts_for_known_applications = 0;
           else VIOFontManager.Settings.Change_fonts_for_known_applications = 1;

           BroadcastMessage( SM_SHOW_SETTINGS );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == VIOWindows_Fonts.Settings.Application_list_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case LN_SELECT:
          {
           if( !VIOWindows_Fonts.Settings.FontMetrics_list_is_locked )
            {
             HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Application_list_ID );

             INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
             if( Selected_string == LIT_NONE ) return 0;

             {
              CHAR Metrics_X[ SIZE_OF_NAME ] = "";
              CHAR Metrics_Y[ SIZE_OF_NAME ] = "";
              INT Font_string = 0;

              switch( Selected_string )
               {
                case 0: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_1; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_1; break;
                case 1: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_2; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_2; break;
                case 2: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_3; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_3; break;
                case 3: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_4; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_4; break;
                case 4: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_5; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_5; break;
                case 5: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_6; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_6; break;
                case 6: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_7; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_7; break;
                case 7: VIOWindows_Fonts.Settings.Shell_font_X = &VIOFontManager.Settings.VIOFontMetrics.X_8; VIOWindows_Fonts.Settings.Shell_font_Y = &VIOFontManager.Settings.VIOFontMetrics.Y_8; break;
               }

              if( VIOWindows_Fonts.Settings.Shell_font_X != NULL )
               {
                itoa( *VIOWindows_Fonts.Settings.Shell_font_X, Metrics_X, 10 ); if( strc( Metrics_X, "0" ) ) Metrics_X[ 0 ] = 0;
                itoa( *VIOWindows_Fonts.Settings.Shell_font_Y, Metrics_Y, 10 ); if( strc( Metrics_Y, "0" ) ) Metrics_Y[ 0 ] = 0;

                HWND ComboBox_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Selected_font_cmbox_ID );

                if( Metrics_X[ 0 ] != 0 )
                 {
                  CHAR Metrics[ SIZE_OF_NAME ] = ""; strcpy( Metrics, Metrics_X ); strcat( Metrics, " x " ); strcat( Metrics, Metrics_Y );
                  Font_string = (LONG) WinSendMsg( ComboBox_window, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), Metrics );
                 }
                else
                 {
                  Font_string = LIT_NONE;
                 }

                VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 1;
                WinSendMsg( ComboBox_window, LM_SELECTITEM, (MPARAM) Font_string, (MPARAM) 1 );
                if( Font_string == LIT_NONE ) WinSetWindowText( ComboBox_window, "" );
                VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 0;
               }
             }
            }
          }
         break;
        }
      }

     if( WM_Control_Window_ID == VIOWindows_Fonts.Settings.Selected_font_cmbox_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case CBN_ENTER:
          {
           if( !VIOWindows_Fonts.Settings.FontMetrics_list_is_locked )
            {
             HWND ComboBox_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Selected_font_cmbox_ID );
             LONG Selected_string = (LONG) WinSendMsg( ComboBox_window, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0 );

             if( Selected_string != LIT_NONE )
              {
               CHAR String[ SIZE_OF_NAME ] = "";
               WinSendMsg( ComboBox_window, LM_QUERYITEMTEXT, MPFROM2SHORT( Selected_string, SIZE_OF_NAME ), String );

               if( String[ 0 ] != 0 )
                {
                 if( String[ 2 ] == ' ' && String[ 3 ] == 'x' && String[ 4 ] == ' ' )
                  {
                   CHAR Metrics_X[ SIZE_OF_NAME ] = "";
                   CHAR Metrics_Y[ SIZE_OF_NAME ] = "";

                   strcpy( Metrics_X, String ); Metrics_X[ 2 ] = 0;
                   strcpy( Metrics_Y, &String[ 5 ] );

                   if( VIOWindows_Fonts.Settings.Shell_font_X != NULL )
                    {
                     *VIOWindows_Fonts.Settings.Shell_font_X = atoi( Metrics_X );
                     *VIOWindows_Fonts.Settings.Shell_font_Y = atoi( Metrics_Y );
                    }
                  }
                }
              }
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

     if( WM_Control_Button_ID == VIOWindows_Fonts.Settings.Application_Add_ID )
      {
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name[ 0 ] != 0 )
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name[ 0 ] != 0 ) return 0;

       if( !Enhancer.Detector_dialog.Detector_is_running )
        {
         Enhancer.Detector_dialog.Customer_window = Window;
         Enhancer.Detector_dialog.Include_VIO_windows_only = 1;

         Enhancer.Detector_dialog.Window_name_1 = VIOFontManager.Settings.VIOFontMetrics.Shell_1_name;
         Enhancer.Detector_dialog.Window_name_2 = VIOFontManager.Settings.VIOFontMetrics.Shell_2_name;
         Enhancer.Detector_dialog.Window_name_3 = VIOFontManager.Settings.VIOFontMetrics.Shell_3_name;
         Enhancer.Detector_dialog.Window_name_4 = VIOFontManager.Settings.VIOFontMetrics.Shell_4_name;
         Enhancer.Detector_dialog.Window_name_5 = VIOFontManager.Settings.VIOFontMetrics.Shell_5_name;
         Enhancer.Detector_dialog.Window_name_6 = VIOFontManager.Settings.VIOFontMetrics.Shell_6_name;
         Enhancer.Detector_dialog.Window_name_7 = VIOFontManager.Settings.VIOFontMetrics.Shell_7_name;
         Enhancer.Detector_dialog.Window_name_8 = VIOFontManager.Settings.VIOFontMetrics.Shell_8_name;

         OpenDETECTOR();
        }
      }

     if( WM_Control_Button_ID == VIOWindows_Fonts.Settings.Application_Remove_ID )
      {
       HWND List_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, VIOWindows_Fonts.Settings.AppList_Container_ID ), VIOWindows_Fonts.Settings.SelectBox_ID ), VIOWindows_Fonts.Settings.Application_list_ID );

       INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
       if( Selected_string == LIT_NONE ) return 0;

       WinSendMsg( List_window, LM_DELETEITEM, MPFROMLONG( Selected_string ), 0 );

       {
        CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
        switch( Selected_string )
         {
          case 0:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 1:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 2:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 3:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 4:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 5:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 6:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
          break;

          case 7:
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );
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
         PrfWriteProfileData( Ini_file, "Settings", "Change VIO font metrics", &VIOFontManager.Settings.Change_VIO_font_metrics, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Change fonts for known applications", &VIOFontManager.Settings.Change_fonts_for_known_applications, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "FontMetrics", NULL, NULL, 0 );

         if( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 1 name", VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 1", &VIOFontManager.Settings.VIOFontMetrics.X_1, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 1", &VIOFontManager.Settings.VIOFontMetrics.Y_1, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 2 name", VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 2", &VIOFontManager.Settings.VIOFontMetrics.X_2, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 2", &VIOFontManager.Settings.VIOFontMetrics.Y_2, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 3 name", VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 3", &VIOFontManager.Settings.VIOFontMetrics.X_3, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 3", &VIOFontManager.Settings.VIOFontMetrics.Y_3, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 4 name", VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 4", &VIOFontManager.Settings.VIOFontMetrics.X_4, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 4", &VIOFontManager.Settings.VIOFontMetrics.Y_4, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 5 name", VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 5", &VIOFontManager.Settings.VIOFontMetrics.X_5, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 5", &VIOFontManager.Settings.VIOFontMetrics.Y_5, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 6 name", VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 6", &VIOFontManager.Settings.VIOFontMetrics.X_6, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 6", &VIOFontManager.Settings.VIOFontMetrics.Y_6, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 7 name", VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 7", &VIOFontManager.Settings.VIOFontMetrics.X_7, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 7", &VIOFontManager.Settings.VIOFontMetrics.Y_7, sizeof( INT ) );
          }
         if( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name[ 0 ] != 0 )
          {
           PrfWriteProfileData( Ini_file, "FontMetrics", "Shell 8 name", VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, strlen( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name ) + 1 );
           PrfWriteProfileData( Ini_file, "FontMetrics", "X 8", &VIOFontManager.Settings.VIOFontMetrics.X_8, sizeof( INT ) );
           PrfWriteProfileData( Ini_file, "FontMetrics", "Y 8", &VIOFontManager.Settings.VIOFontMetrics.Y_8, sizeof( INT ) );
          }

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       if( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name[ 0 ] != 0 || VIOFontManager.Settings.VIOFontMetrics.Shell_2_name[ 0 ] != 0 ||
           VIOFontManager.Settings.VIOFontMetrics.Shell_3_name[ 0 ] != 0 || VIOFontManager.Settings.VIOFontMetrics.Shell_4_name[ 0 ] != 0 ||
           VIOFontManager.Settings.VIOFontMetrics.Shell_5_name[ 0 ] != 0 || VIOFontManager.Settings.VIOFontMetrics.Shell_6_name[ 0 ] != 0 ||
           VIOFontManager.Settings.VIOFontMetrics.Shell_7_name[ 0 ] != 0 || VIOFontManager.Settings.VIOFontMetrics.Shell_8_name[ 0 ] != 0 )
        {
         CHAR String[ 256 ] = ""; LONG Reply = 0;
         BYTE Clear_list = 0;

         LONG Code_page = Enhancer.Code_page;

         if( Code_page == RUSSIAN ) strcpy( String, StrConst_RU_Pages_VIOWindows_fonts_Question );
         else strcpy( String, StrConst_EN_Pages_VIOWindows_fonts_Question );

         {
          CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
          Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO );
         }

         if( Reply == MBID_YES ) Clear_list = 1;

         if( Clear_list )
          {
           CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );

           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, Empty_name, SIZE_OF_NAME );
           memcpy( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Empty_name, SIZE_OF_NAME );

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
