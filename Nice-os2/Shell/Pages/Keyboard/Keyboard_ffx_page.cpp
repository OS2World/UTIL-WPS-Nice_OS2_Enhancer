
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Keyboard_FireFox_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Keyboard_ffx;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( KeyMapper.Settings.Define_Dash ) Value = 1;
     WinSendDlgItemMsg( Window, Keyboard_FireFox.Settings.Dash, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( KeyMapper.Settings.Define_Ctrl_Dash ) Value = 1;
     WinSendDlgItemMsg( Window, Keyboard_FireFox.Settings.Ctrl_Dash, BM_SETCHECK, MPFROMLONG( Value ), 0 );
    }
   return 0;

   // Проверяем другие настройки.
   case SM_CHECK_OTHER_SETTINGS:
    {
     CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
     HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

     if( Ini_file )
      {
       ULONG Byte = 0; ULONG Byte_data = 0;
       ULONG CopyPaste_keys_in_VIO = 0; ULONG Mouse_in_VIO = 0;

       Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", INI_CLIPPER_VIO_COPYPASTE, &Byte_data, &Byte ) ) CopyPaste_keys_in_VIO = Byte_data;
       Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", INI_CLIPPER_VIO_MOUSE, &Byte_data, &Byte ) ) Mouse_in_VIO = Byte_data;

       if( !CopyPaste_keys_in_VIO && !Mouse_in_VIO ) WinEnableControl( Window, Keyboard_FireFox.Settings.Dash, 0 );
      }
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Keyboard_FireFox.Settings.Dash )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) KeyMapper.Settings.Define_Dash = 0;
           else KeyMapper.Settings.Define_Dash = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Keyboard_FireFox.Settings.Ctrl_Dash )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) KeyMapper.Settings.Define_Ctrl_Dash = 0;
           else KeyMapper.Settings.Define_Ctrl_Dash = 1;

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
         PrfWriteProfileData( Ini_file, "Settings", "Define Dash", &KeyMapper.Settings.Define_Dash, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Define Ctrl + Dash", &KeyMapper.Settings.Define_Ctrl_Dash, sizeof( BYTE ) );

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
