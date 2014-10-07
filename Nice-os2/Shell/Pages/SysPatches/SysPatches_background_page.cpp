
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY SysPatches_Background_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.SysPatches_background;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     PCHAR Name_in_path = FindNameInPath( SysPatches_Background.Settings.Folder_background_name ); MixedCase( Name_in_path );
     WinSetWindowText( WinWindowFromID( WinWindowFromID( Window, SysPatches_Background.Settings.Wallpaper_filebox_ID ), SysPatches_Background.Settings.Wallpaper_name_ID ), Name_in_path );
    }
   return 0;

   // Обновляем окно.
   case WM_TIMER:
   case SM_RECOGNIZE_THEME:
    {
     // Если есть изображение для окон рабочего стола:
     if( SysPatches_Background.Settings.Folder_background != NULLHANDLE )
      {
       HWND Example_window = WinWindowFromID( Window, SysPatches_Background.Settings.Example_ID );

       if( Example_window != NULLHANDLE && WinIsWindowShowing( Example_window ) )
        {
         HPS Presentation_space = WinGetPS( Example_window );

         if( Presentation_space != NULLHANDLE )
          {
           {
            INT Margin = 5; RECT Wallpaper_rectangle = {0};
            WinQueryWindowRect( Example_window, &Wallpaper_rectangle );
            Wallpaper_rectangle.xLeft += Margin; Wallpaper_rectangle.xRight -= ( Margin + 1 );
            Wallpaper_rectangle.yBottom += Margin; Wallpaper_rectangle.yTop -= ( Margin + 1 ) * 2;
            GpiSetGraphicsField( Presentation_space, &Wallpaper_rectangle );
           }

           RECT Window_rectangle = {0};
           WinQueryWindowRect( Example_window, &Window_rectangle );

           INT Window_width = Window_rectangle.xRight - Window_rectangle.xLeft;
           INT Window_height = Window_rectangle.yTop - Window_rectangle.yBottom;

           RECT Bitmap_rectangle = { 0, 0, SysPatches_Background.Settings.Folder_background_width, SysPatches_Background.Settings.Folder_background_height };

           for( INT X_Count = 0; X_Count < Window_width; X_Count += SysPatches_Background.Settings.Folder_background_width )
            for( INT Y_Count = 0; Y_Count < Window_height; Y_Count += SysPatches_Background.Settings.Folder_background_height )
             {
              POINT Point = { X_Count, Y_Count };
              WinDrawBitmap( Presentation_space, SysPatches_Background.Settings.Folder_background, &Bitmap_rectangle, &Point, 0, 0, DBM_NORMAL );
             }
          }

         WinReleasePS( Presentation_space );
        }
      }
    }
   return 0;

   // Обрабатываем нажатия на кнопки.
   case WM_COMMAND:
    {
     ULONG WM_Control_Button_ID = SHORT1FROMMP( First_parameter );

     if( WM_Control_Button_ID == SysPatches_Background.Settings.Wallpaper_button_ID )
      {
       FILEDLG Parameters; HWND OpenFile_window;

       bzero( &Parameters, sizeof( FILEDLG ) );
       Parameters.cbSize = sizeof( FILEDLG );
       Parameters.fl = FDS_OPEN_DIALOG | FDS_CENTER;

       LONG Code_page = Enhancer.Code_page;

       if( Code_page == RUSSIAN ) Parameters.pszTitle = StrConst_RU_Pages_SysPatches_background_Wallpaper_dialog;
       else Parameters.pszTitle = StrConst_EN_Pages_SysPatches_background_Wallpaper_dialog;

       if( SysPatches_Background.RTSettings.FileDlg_path[ 0 ] == 0 )
        {
         GetCurrentPath( Parameters.szFullFile );
         strcat( Parameters.szFullFile, "\\Bitmap\\WPShell\\*.bmp" );
        }
       else
        {
         strcpy( Parameters.szFullFile, SysPatches_Background.RTSettings.FileDlg_path );
         strcat( Parameters.szFullFile, "\\*.bmp" );
        }

       OpenFile_window = WinFileDlg( HWND_DESKTOP, Window, &Parameters );

       if( OpenFile_window != NULLHANDLE ) if( Parameters.lReturn == DID_OK )
        if( stristr( ".bmp", Parameters.szFullFile ) )
         {
          strncpy( SysPatches_Background.Settings.Folder_background_name, Parameters.szFullFile, SIZE_OF_PATH );

          strncpy( SysPatches_Background.RTSettings.FileDlg_path, Parameters.szFullFile, SIZE_OF_PATH );
          CutNameInPath( SysPatches_Background.RTSettings.FileDlg_path );

          LoadBitmap( Enhancer.Application, SysPatches_Background.Settings.Folder_background_name, &SysPatches_Background.Settings.Folder_background, &SysPatches_Background.Settings.Folder_background_width, &SysPatches_Background.Settings.Folder_background_height );
          BroadcastRSMessages();
         }
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         if( SysPatches_Background.Settings.Folder_background_name[ 0 ] != 0 )
          {
           CHAR String[ SIZE_OF_PATH ] = "";
           strcpy( String, SysPatches_Background.Settings.Folder_background_name );
           strcat( String, ",T,1,I,204 204 204" );

           PrfWriteProfileData( HINI_USERPROFILE, "PM_SystemBackground", "DefaultFolderBackground", String, strlen( String ) + 1 );

           for( INT Blink = 0; Blink < 3; Blink ++ )
            {
             LONG White_color = MAKERGB( 255, 255, 255 );
             LONG Red_color   = MAKERGB( 128,   0,   0 );

             WinSetPresParam( WinWindowFromID( Window, SysPatches_Background.Settings.Comment_ID ), PP_FOREGROUNDCOLOR, sizeof( ULONG ), &White_color );
             DosSleep( 250 );
             WinSetPresParam( WinWindowFromID( Window, SysPatches_Background.Settings.Comment_ID ), PP_FOREGROUNDCOLOR, sizeof( ULONG ), &Red_color );
             DosSleep( 250 );
            }
          }

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings();
        }
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
