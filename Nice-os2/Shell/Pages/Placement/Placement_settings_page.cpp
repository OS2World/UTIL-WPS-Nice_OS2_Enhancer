
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Placement_Settings_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Placement_settings;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Arranger.Settings.Arrange_VIO_windows ) Value = 1;
     WinSendDlgItemMsg( Window, Placement_Settings.Settings.VIO_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
     WinEnableWindow( WinWindowFromID( Window, Placement_Settings.Settings.FC2_button_ID ), Value );

     Value = 0; if( Arranger.Settings.Arrange_FC2_windows ) Value = 1;
     WinSendDlgItemMsg( Window, Placement_Settings.Settings.FC2_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( Arranger.Settings.Arrange_WindowList ) Value = 1;
     WinSendDlgItemMsg( Window, Placement_Settings.Settings.WindowList_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( Arranger.Settings.Arrange_WPS_windows ) Value = 1;
     WinSendDlgItemMsg( Window, Placement_Settings.Settings.WPS_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Placement_Settings.Settings.VIO_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Arranger.Settings.Arrange_VIO_windows = 0;
           else Arranger.Settings.Arrange_VIO_windows = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Placement_Settings.Settings.FC2_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Arranger.Settings.Arrange_FC2_windows = 0;
           else Arranger.Settings.Arrange_FC2_windows = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Placement_Settings.Settings.WindowList_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Arranger.Settings.Arrange_WindowList = 0;
           else Arranger.Settings.Arrange_WindowList = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Placement_Settings.Settings.WPS_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Arranger.Settings.Arrange_WPS_windows = 0;
           else Arranger.Settings.Arrange_WPS_windows = 1;

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

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         PrfWriteProfileData( Ini_file, "Settings", "Arrange VIO windows", &Arranger.Settings.Arrange_VIO_windows, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Arrange FC2 windows", &Arranger.Settings.Arrange_FC2_windows, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Arrange WindowList",  &Arranger.Settings.Arrange_WindowList,  sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Arrange WPS windows", &Arranger.Settings.Arrange_WPS_windows, sizeof( BYTE ) );

         PrfCloseProfile( Ini_file );

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
