
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Mouse_Clipboard_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Mouse_clipboard;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( MouseMapper.Settings.Use_middle_button_for_CopyPaste ) Value = 1;
     WinSendDlgItemMsg( Window, Mouse_Clipboard.Settings.Use_MB_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );
     WinEnableWindow( WinWindowFromID( Window, Mouse_Clipboard.Settings.Mouse_cmbox_ID ), Value );

     BYTE Enabled = 1;
     if( WinQuerySysValue( QueryDesktopWindow(), SV_CMOUSEBUTTONS ) != 3 ) Enabled = 0;

     WinEnableWindow( WinWindowFromID( Window, Mouse_Clipboard.Settings.Use_MB_ID ), Enabled );
     WinEnableWindow( WinWindowFromID( Window, Mouse_Clipboard.Settings.Mouse_cmbox_ID ), Enabled );

     if( MouseMapper.Settings.Use_middle_button_for_CopyPaste )
      {
       INT Selected_string = MouseMapper.Settings.Use_middle_button_for_CopyPaste - 1;
       WinSendDlgItemMsg( Window, Mouse_Clipboard.Settings.Mouse_cmbox_ID, LM_SELECTITEM, MPFROMLONG( Selected_string ), MPFROMLONG( 1 ) );
      }
    }
   return 0;

   // Распознаем настройки.
   case SM_RECOGNIZE_SELECTION:
    {
     LONG Selected_string = (LONG) WinSendDlgItemMsg( Window, Mouse_Clipboard.Settings.Mouse_cmbox_ID, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0 );
     if( Selected_string != LIT_NONE ) MouseMapper.Settings.Use_middle_button_for_CopyPaste = Selected_string + 1;
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Mouse_Clipboard.Settings.Use_MB_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) MouseMapper.Settings.Use_middle_button_for_CopyPaste = 0;
           else MouseMapper.Settings.Use_middle_button_for_CopyPaste = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Mouse_Clipboard.Settings.Mouse_cmbox_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case CBN_ENTER:
          {
           WinSendMsg( Window, SM_RECOGNIZE_SELECTION, 0, 0 );
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
         PrfWriteProfileData( Ini_file, "Settings", "Use middle button for CopyPaste", &MouseMapper.Settings.Use_middle_button_for_CopyPaste, sizeof( BYTE ) );

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
