
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Drawing_Buttons_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Drawing_buttons;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Painter.Settings.Accelerate_folders_closing ) Value = 1;
     WinSendDlgItemMsg( Window, Drawing_Buttons.Settings.Buttons_WPS_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( !Painter.Settings.Rollup_VIO_windows ) Value = 1;
     WinSendDlgItemMsg( Window, Drawing_Buttons.Settings.Buttons_VIO_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // Отображаем список исключений.
   case SM_UPDATE_LIST:
    {
     HWND List_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Buttons.Settings.RollUp_Container_ID ), Drawing_Buttons.Settings.RollUp_List_ID );

     WinSendMsg( List_window, LM_DELETEALL, 0, 0 );

     if( Painter.Settings.Exceptions.Rolling_1[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_1 ) );
     if( Painter.Settings.Exceptions.Rolling_2[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_2 ) );
     if( Painter.Settings.Exceptions.Rolling_3[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_3 ) );
     if( Painter.Settings.Exceptions.Rolling_4[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_4 ) );
     if( Painter.Settings.Exceptions.Rolling_5[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_5 ) );
     if( Painter.Settings.Exceptions.Rolling_6[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_6 ) );
     if( Painter.Settings.Exceptions.Rolling_7[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_7 ) );
     if( Painter.Settings.Exceptions.Rolling_8[ 0 ] != 0 ) WinSendMsg( List_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( Painter.Settings.Exceptions.Rolling_8 ) );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Drawing_Buttons.Settings.Buttons_WPS_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Painter.Settings.Accelerate_folders_closing = 0;
           else Painter.Settings.Accelerate_folders_closing = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Drawing_Buttons.Settings.Buttons_VIO_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Painter.Settings.Rollup_VIO_windows = 1;
           else Painter.Settings.Rollup_VIO_windows = 0;

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

     if( WM_Control_Button_ID == Drawing_Buttons.Settings.RollUp_Add_ID )
      {
       if( Painter.Settings.Exceptions.Rolling_1[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_2[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_3[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_4[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_5[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_6[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_7[ 0 ] != 0 )
       if( Painter.Settings.Exceptions.Rolling_8[ 0 ] != 0 ) return 0;

       if( !Enhancer.Detector_dialog.Detector_is_running )
        {
         Enhancer.Detector_dialog.Customer_window = Window;

         Enhancer.Detector_dialog.Window_name_1 = Painter.Settings.Exceptions.Rolling_1;
         Enhancer.Detector_dialog.Window_name_2 = Painter.Settings.Exceptions.Rolling_2;
         Enhancer.Detector_dialog.Window_name_3 = Painter.Settings.Exceptions.Rolling_3;
         Enhancer.Detector_dialog.Window_name_4 = Painter.Settings.Exceptions.Rolling_4;
         Enhancer.Detector_dialog.Window_name_5 = Painter.Settings.Exceptions.Rolling_5;
         Enhancer.Detector_dialog.Window_name_6 = Painter.Settings.Exceptions.Rolling_6;
         Enhancer.Detector_dialog.Window_name_7 = Painter.Settings.Exceptions.Rolling_7;
         Enhancer.Detector_dialog.Window_name_8 = Painter.Settings.Exceptions.Rolling_8;

         OpenDETECTOR();
        }
      }

     if( WM_Control_Button_ID == Drawing_Buttons.Settings.RollUp_Remove_ID )
      {
       HWND List_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Buttons.Settings.RollUp_Container_ID ), Drawing_Buttons.Settings.RollUp_List_ID );

       INT Selected_string = (INT) WinSendMsg( List_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );
       if( Selected_string == LIT_NONE ) return 0;

       WinSendMsg( List_window, LM_DELETEITEM, MPFROMLONG( Selected_string ), 0 );

       {
        CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
        switch( Selected_string )
         {
          case 0:
           memcpy( Painter.Settings.Exceptions.Rolling_1, Painter.Settings.Exceptions.Rolling_2, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_2, Painter.Settings.Exceptions.Rolling_3, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_3, Painter.Settings.Exceptions.Rolling_4, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_4, Painter.Settings.Exceptions.Rolling_5, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_5, Painter.Settings.Exceptions.Rolling_6, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 1:
           memcpy( Painter.Settings.Exceptions.Rolling_2, Painter.Settings.Exceptions.Rolling_3, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_3, Painter.Settings.Exceptions.Rolling_4, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_4, Painter.Settings.Exceptions.Rolling_5, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_5, Painter.Settings.Exceptions.Rolling_6, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 2:
           memcpy( Painter.Settings.Exceptions.Rolling_3, Painter.Settings.Exceptions.Rolling_4, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_4, Painter.Settings.Exceptions.Rolling_5, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_5, Painter.Settings.Exceptions.Rolling_6, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 3:
           memcpy( Painter.Settings.Exceptions.Rolling_4, Painter.Settings.Exceptions.Rolling_5, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_5, Painter.Settings.Exceptions.Rolling_6, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 4:
           memcpy( Painter.Settings.Exceptions.Rolling_5, Painter.Settings.Exceptions.Rolling_6, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 5:
           memcpy( Painter.Settings.Exceptions.Rolling_6, Painter.Settings.Exceptions.Rolling_7, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 6:
           memcpy( Painter.Settings.Exceptions.Rolling_7, Painter.Settings.Exceptions.Rolling_8, SIZE_OF_NAME );
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
          break;

          case 7:
           memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );
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
         PrfWriteProfileData( Ini_file, "Settings", "Accelerate folders closing", &Painter.Settings.Accelerate_folders_closing, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Rollup VIO windows", &Painter.Settings.Rollup_VIO_windows, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 1", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 2", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 3", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 4", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 5", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 6", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 7", NULL, 0 );
         PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 8", NULL, 0 );

         if( Painter.Settings.Exceptions.Rolling_1[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 1", Painter.Settings.Exceptions.Rolling_1, strlen( Painter.Settings.Exceptions.Rolling_1 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_2[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 2", Painter.Settings.Exceptions.Rolling_2, strlen( Painter.Settings.Exceptions.Rolling_2 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_3[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 3", Painter.Settings.Exceptions.Rolling_3, strlen( Painter.Settings.Exceptions.Rolling_3 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_4[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 4", Painter.Settings.Exceptions.Rolling_4, strlen( Painter.Settings.Exceptions.Rolling_4 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_5[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 5", Painter.Settings.Exceptions.Rolling_5, strlen( Painter.Settings.Exceptions.Rolling_5 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_6[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 6", Painter.Settings.Exceptions.Rolling_6, strlen( Painter.Settings.Exceptions.Rolling_6 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_7[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 7", Painter.Settings.Exceptions.Rolling_7, strlen( Painter.Settings.Exceptions.Rolling_7 ) + 1 );
         if( Painter.Settings.Exceptions.Rolling_8[ 0 ] != 0 ) PrfWriteProfileData( Ini_file, "ExceptionList", "Rolling 8", Painter.Settings.Exceptions.Rolling_8, strlen( Painter.Settings.Exceptions.Rolling_8 ) + 1 );

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings( 1 );
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       CHAR String[ 256 ] = ""; LONG Reply = 0;
       BYTE Clear_list = 0;
       LONG Code_page = Enhancer.Code_page;

       if( Painter.Settings.Exceptions.Rolling_1[ 0 ] != 0 || Painter.Settings.Exceptions.Rolling_2[ 0 ] != 0 ||
           Painter.Settings.Exceptions.Rolling_3[ 0 ] != 0 || Painter.Settings.Exceptions.Rolling_4[ 0 ] != 0 ||
           Painter.Settings.Exceptions.Rolling_5[ 0 ] != 0 || Painter.Settings.Exceptions.Rolling_6[ 0 ] != 0 ||
           Painter.Settings.Exceptions.Rolling_7[ 0 ] != 0 || Painter.Settings.Exceptions.Rolling_8[ 0 ] != 0 )
        {
         if( Code_page == RUSSIAN ) strcpy( String, StrConst_RU_Pages_Drawing_buttons_Question );
         else strcpy( String, StrConst_EN_Pages_Drawing_buttons_Question );

         {
          CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
          Reply = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, String, Title, 0, MB_YESNO );
         }

         if( Reply == MBID_YES ) Clear_list = 1;
        }

       if( Clear_list )
        {
         CHAR Empty_name[ SIZE_OF_NAME ] = ""; bzero( Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_1, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_2, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_3, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_4, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_5, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_6, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_7, Empty_name, SIZE_OF_NAME );
         memcpy( Painter.Settings.Exceptions.Rolling_8, Empty_name, SIZE_OF_NAME );

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
