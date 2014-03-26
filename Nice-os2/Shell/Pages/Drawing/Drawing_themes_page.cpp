
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Drawing_Themes_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Drawing_themes;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Painter.Settings.Draw_frames ) Value = 1;
     WinSendDlgItemMsg( Window, Drawing_Themes.Settings.Theme_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     HWND Theme_list_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Theme_list_ID );
     WinEnableWindow( Theme_list_window, Value );
     HWND FileBox_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Texture_filebox_ID );
     WinEnableWindow( FileBox_window, Value );

     if( Painter.Settings.TitleBar_pattern[ 0 ] != 0 )
      {
       PCHAR Name_in_path = FindNameInPath( Painter.Settings.TitleBar_pattern ); MixedCase( Name_in_path );
       WinSetDlgItemText( WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Texture_filebox_ID ), Drawing_Themes.Settings.Texture_name_ID, Name_in_path );
      }
     else
      {
       WinSetDlgItemText( WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Texture_filebox_ID ), Drawing_Themes.Settings.Texture_name_ID, StrConst_EN_Pages_Drawing_themes_Texture_name );
      }
    }
   return 0;

   // Распознаем настройки.
   case SM_RECOGNIZE_SELECTION:
    {
     HWND Theme_list_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Theme_list_ID );

     INT Selected_string = (INT) WinSendMsg( Theme_list_window, LM_QUERYSELECTION, MPFROMLONG( LIT_FIRST ), MPFROMLONG( 0 ) );

     if( Selected_string != LIT_NONE )
      {
       ULONG Previous_theme = Painter.Settings.Theme;

       switch( Selected_string )
        {
         case 0: Painter.Settings.Theme = PAINTER_THEME_ECOMSTATION;  break;
         case 1: Painter.Settings.Theme = PAINTER_THEME_CLASSIC_GRAY; break;
         case 2: Painter.Settings.Theme = PAINTER_THEME_CLASSIC_RGB;  break;
         case 3: Painter.Settings.Theme = PAINTER_THEME_WHITE_SNOW;   break;
        }

       {
        HWND FileBox_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Texture_filebox_ID );

        BYTE Show_pattern_filebox = 1;
        if( Painter.Settings.Theme != PAINTER_THEME_ECOMSTATION ) Show_pattern_filebox = 0;

        BYTE Update_page_window = 0;
        if( ( Previous_theme != PAINTER_THEME_ECOMSTATION && Painter.Settings.Theme == PAINTER_THEME_ECOMSTATION ) ||
            ( Previous_theme == PAINTER_THEME_ECOMSTATION && Painter.Settings.Theme != PAINTER_THEME_ECOMSTATION ) )
         {
          if( WinIsWindowVisible( FileBox_window ) ) Update_page_window = 1;
         }

        WinShowWindow( FileBox_window, Show_pattern_filebox );
        if( Update_page_window ) UpdatePageWindow( Page );
       }
      }
    }
   return 0;

   // Применяем выбранную тему.
   case SM_RECOGNIZE_THEME:
    {
     INT String_to_select = LIT_NONE;

     switch( Painter.Settings.Theme )
      {
       case PAINTER_THEME_ECOMSTATION:  String_to_select = 0; break;
       case PAINTER_THEME_CLASSIC_GRAY: String_to_select = 1; break;
       case PAINTER_THEME_CLASSIC_RGB:  String_to_select = 2; break;
       case PAINTER_THEME_WHITE_SNOW:   String_to_select = 3; break;
      }

     HWND Theme_list_window = WinWindowFromID( WinWindowFromID( Window, Drawing_Themes.Settings.Container_ID ), Drawing_Themes.Settings.Theme_list_ID );
     WinSendMsg( Theme_list_window, LM_SELECTITEM, MPFROMLONG( String_to_select ), MPFROMLONG( 1 ) );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Drawing_Themes.Settings.Theme_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Painter.Settings.Draw_frames = 0;
           else Painter.Settings.Draw_frames = 1;

           WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Drawing_Themes.Settings.Theme_list_ID )
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
    }
   return 0;

   // Обрабатываем нажатия на кнопки.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == Drawing_Themes.Settings.Texture_button_ID )
      {
       FILEDLG Parameters; HWND OpenFile_window;
       CHAR File_mask[ SIZE_OF_PATH ] = ""; CHAR Search_pattern[] = "Bitmap\\Themes\\*.bmp";

       bzero( &Parameters, sizeof( FILEDLG ) );
       Parameters.cbSize = sizeof( FILEDLG );
       Parameters.fl = FDS_OPEN_DIALOG | FDS_CENTER;

       LONG Code_page = Enhancer.Code_page;

       if( Code_page == RUSSIAN ) Parameters.pszTitle = StrConst_RU_Pages_Drawing_themes_Texture_dialog;
       else Parameters.pszTitle = StrConst_EN_Pages_Drawing_themes_Texture_dialog;

       CHAR Current_directory[ SIZE_OF_PATH ] = "";
       GetCurrentPath( Current_directory );
       strcpy( File_mask, Current_directory );
       strcat( File_mask, "\\" );
       strcat( File_mask, Search_pattern );
       strcpy( Parameters.szFullFile, File_mask );

       OpenFile_window = WinFileDlg( HWND_DESKTOP, Window, &Parameters );

       if( OpenFile_window != NULLHANDLE ) if( Parameters.lReturn == DID_OK )
        if( strifind( ".bmp", Parameters.szFullFile ) )
         {
          strncpy( Painter.Settings.TitleBar_pattern, Parameters.szFullFile, SIZE_OF_PATH );

          WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
         }
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         PrfWriteProfileData( Ini_file, "Settings", "Draw frames", &Painter.Settings.Draw_frames, sizeof( BYTE ) );
         PrfWriteProfileData( Ini_file, "Settings", "Theme", &Painter.Settings.Theme, sizeof( INT ) );

         PrfWriteProfileData( Ini_file, "Settings", "TitleBar pattern", Painter.Settings.TitleBar_pattern, strlen( Painter.Settings.TitleBar_pattern ) + 1 );

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings( 1 );
        }

       BroadcastMessage( SM_RECOGNIZE_THEME );
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
