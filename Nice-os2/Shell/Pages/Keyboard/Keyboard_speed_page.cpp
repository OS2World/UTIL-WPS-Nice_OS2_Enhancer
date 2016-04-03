
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Keyboard_Speed_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Keyboard_speed;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Controller.Settings.Reset_Shift_keys ) Value = 1;
     WinSendDlgItemMsg( Window, Keyboard_Speed.Settings.Reset_Shift_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     Value = 0; if( Controller.Settings.SpeedUp_keyboard ) Value = 1;
     WinSendDlgItemMsg( Window, Keyboard_Speed.Settings.SpeedUp_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableControl( Window, Keyboard_Speed.Settings.Rate_cbox_ID, Value );

     if( Controller.Settings.SpeedUp_keyboard )
      {
       INT Selected_string = LIT_NONE;
       if( Controller.Settings.Keyboard_rate == ( 12 * 2 ) ) Selected_string = 0;
       if( Controller.Settings.Keyboard_rate == ( 12 * 3 ) ) Selected_string = 1;

       WinSendDlgItemMsg( Window, Keyboard_Speed.Settings.Rate_cbox_ID, LM_SELECTITEM, MPFROMLONG( Selected_string ), MPFROMLONG( 1 ) );
      }
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Keyboard_Speed.Settings.Reset_Shift_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Controller.Settings.Reset_Shift_keys = 0;
           else Controller.Settings.Reset_Shift_keys = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Keyboard_Speed.Settings.SpeedUp_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Controller.Settings.SpeedUp_keyboard = 0;
           else Controller.Settings.SpeedUp_keyboard = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Keyboard_Speed.Settings.Rate_cbox_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case CBN_ENTER:
          {
           LONG Selected_string = (LONG) WinSendDlgItemMsg( Window, Keyboard_Speed.Settings.Rate_cbox_ID, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0 );

           if( Selected_string != LIT_NONE )
            {
             if( Selected_string == 0 ) Controller.Settings.Keyboard_rate = ( 12 * 2 );
             if( Selected_string == 1 ) Controller.Settings.Keyboard_rate = ( 12 * 3 );
            }

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
         PrfWriteProfileData( Ini_file, "Settings", "Reset Shift keys", &Controller.Settings.Reset_Shift_keys, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "Settings", "Speed up keyboard", &Controller.Settings.SpeedUp_keyboard, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Keyboard rate", &Controller.Settings.Keyboard_rate, sizeof( BYTE ) );

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
