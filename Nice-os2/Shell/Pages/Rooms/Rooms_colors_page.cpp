
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Rooms_Colors_WndProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Rooms_colors;

 // Проверяем сообщение.
 switch( Message )
  {
   // Отображаем настройки.
   case SM_SHOW_SETTINGS:
    {
     BYTE Value = 0; if( Rooms.Settings.Create_Rooms ) Value = 1;
     WinSendDlgItemMsg( Window, Rooms_Colors.Settings.Create_rooms_button_ID, BM_SETCHECK, MPFROMLONG( Value ), 0 );

     WinEnableWindow( WinWindowFromID( Window, Rooms_Colors.Settings.Selected_room_cmbox_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.Wallpaper_filebox_ID ), Rooms_Colors.Settings.Wallpaper_button_ID ), Value );
     WinEnableWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Button_ID ), Value );

     WinSendMsg( Window, SM_SET_PRESENTATION_PARAMETERS, 0, 0 );

     BYTE Show_colors = 1;
     if( Rooms_Colors.RTSettings.Selected_room == SHELL_ROOM ) Show_colors = 0;

     WinShowWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Show_colors );
     WinShowWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Button_ID ), Show_colors );
     WinShowWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Show_colors );
     WinShowWindow( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Show_colors );

     {
      PCHAR File_name = NULL; PCHAR Name_in_path = NULL; INT Count;
      if( Rooms_Colors.RTSettings.Selected_room == SHELL_ROOM ) File_name = Rooms.Settings.Wallpaper_for_shell_room;
      if( Rooms_Colors.RTSettings.Selected_room == NORTHERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_northern_room;
      if( Rooms_Colors.RTSettings.Selected_room == WESTERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_western_room;
      if( Rooms_Colors.RTSettings.Selected_room == EASTERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_eastern_room;
      if( Rooms_Colors.RTSettings.Selected_room == SOUTHERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_southern_room;

      HWND Label = WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.Wallpaper_filebox_ID ), Rooms_Colors.Settings.Wallpaper_name_ID );

      if( File_name[ 0 ] != 0 )
       {
        PCHAR Name_in_path = FindNameInPath( File_name ); MixedCase( Name_in_path );
        WinSetWindowText( Label, Name_in_path );
       }
      else
       {
        WinSetWindowText( Label, StrConst_EN_Pages_Rooms_colors_Wallpaper_name );
       }
     }
    }
   return 0;

   case SM_SET_PRESENTATION_PARAMETERS:
    {
     if( Rooms_Colors.RTSettings.Selected_room != SHELL_ROOM )
      {
       LONG AT_Text_color = 0;       LONG IT_Text_color = 0;
       LONG AT_Background_color = 0; LONG IT_Background_color = 0;
       LONG AT_Color_1 = 0;          LONG AT_Color_2 = 0;          LONG AT_Color_3 = 0;
       LONG IT_Color_1 = 0;          LONG IT_Color_2 = 0;          LONG IT_Color_3 = 0;

       if( Rooms_Colors.RTSettings.Selected_room == NORTHERN_ROOM )
        {
         AT_Text_color = Painter.Settings.Northern_AT_Text_color;
         IT_Text_color = Painter.Settings.Northern_IT_Text_color;
         AT_Background_color = Painter.Settings.Northern_AT_Background_color;
         IT_Background_color = Painter.Settings.Northern_IT_Background_color;

         AT_Color_1 = Painter.Settings.Northern_AT_Color_1;       IT_Color_1 = Painter.Settings.Northern_IT_Color_1;
         AT_Color_2 = Painter.Settings.Northern_AT_Color_2;       IT_Color_2 = Painter.Settings.Northern_IT_Color_2;
         AT_Color_3 = Painter.Settings.Northern_AT_Color_3;       IT_Color_3 = Painter.Settings.Northern_IT_Color_3;
        }

       if( Rooms_Colors.RTSettings.Selected_room == WESTERN_ROOM )
        {
         AT_Text_color = Painter.Settings.Western_AT_Text_color;
         IT_Text_color = Painter.Settings.Western_IT_Text_color;
         AT_Background_color = Painter.Settings.Western_AT_Background_color;
         IT_Background_color = Painter.Settings.Western_IT_Background_color;

         AT_Color_1 = Painter.Settings.Western_AT_Color_1;       IT_Color_1 = Painter.Settings.Western_IT_Color_1;
         AT_Color_2 = Painter.Settings.Western_AT_Color_2;       IT_Color_2 = Painter.Settings.Western_IT_Color_2;
         AT_Color_3 = Painter.Settings.Western_AT_Color_3;       IT_Color_3 = Painter.Settings.Western_IT_Color_3;
        }

       if( Rooms_Colors.RTSettings.Selected_room == EASTERN_ROOM )
        {
         AT_Text_color = Painter.Settings.Eastern_AT_Text_color;
         IT_Text_color = Painter.Settings.Eastern_IT_Text_color;
         AT_Background_color = Painter.Settings.Eastern_AT_Background_color;
         IT_Background_color = Painter.Settings.Eastern_IT_Background_color;

         AT_Color_1 = Painter.Settings.Eastern_AT_Color_1;       IT_Color_1 = Painter.Settings.Eastern_IT_Color_1;
         AT_Color_2 = Painter.Settings.Eastern_AT_Color_2;       IT_Color_2 = Painter.Settings.Eastern_IT_Color_2;
         AT_Color_3 = Painter.Settings.Eastern_AT_Color_3;       IT_Color_3 = Painter.Settings.Eastern_IT_Color_3;
        }

       if( Rooms_Colors.RTSettings.Selected_room == SOUTHERN_ROOM )
        {
         AT_Text_color = Painter.Settings.Southern_AT_Text_color;
         IT_Text_color = Painter.Settings.Southern_IT_Text_color;
         AT_Background_color = Painter.Settings.Southern_AT_Background_color;
         IT_Background_color = Painter.Settings.Southern_IT_Background_color;

         AT_Color_1 = Painter.Settings.Southern_AT_Color_1;       IT_Color_1 = Painter.Settings.Southern_IT_Color_1;
         AT_Color_2 = Painter.Settings.Southern_AT_Color_2;       IT_Color_2 = Painter.Settings.Southern_IT_Color_2;
         AT_Color_3 = Painter.Settings.Southern_AT_Color_3;       IT_Color_3 = Painter.Settings.Southern_IT_Color_3;
        }

       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Active_ID ), PP_FOREGROUNDCOLOR, sizeof( ULONG ), &AT_Text_color );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Active_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &AT_Background_color );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Inactive_ID ), PP_FOREGROUNDCOLOR, sizeof( ULONG ), &IT_Text_color );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Inactive_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &IT_Background_color );

       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_1_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &AT_Color_1 );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_2_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &AT_Color_2 );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_3_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &AT_Color_3 );

       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_1_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &IT_Color_1 );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_2_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &IT_Color_2 );
       WinSetPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_3_ID ), PP_BACKGROUNDCOLOR, sizeof( ULONG ), &IT_Color_3 );
      }
    }
   return 0;

   // Применяем выбранную тему.
   case SM_RECOGNIZE_THEME:
    {
     THEMEPAGEDEF Input_fields; bzero( &Input_fields, sizeof( Input_fields ) );

     Input_fields.NeonPalette_FillTB_window = WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_FillTB_ID );
     Input_fields.NeonPalette_Container_window = WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID );

     Input_fields.NeonPalette_Active_1_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_1_ID );
     Input_fields.NeonPalette_Active_2_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_2_ID );
     Input_fields.NeonPalette_Active_3_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_3_ID );

     Input_fields.NeonPalette_Inactive_1_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_1_ID );
     Input_fields.NeonPalette_Inactive_2_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_2_ID );
     Input_fields.NeonPalette_Inactive_3_window = WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_3_ID );

     RecognizeSelectedTheme( &Input_fields );
    }
   return 0;

   // Следим за полями ввода.
   case WM_CONTROL:
    {
     ULONG WM_Control_Window_ID = SHORT1FROMMP( First_parameter );
     ULONG WM_Control_Action_ID = SHORT2FROMMP( First_parameter );

     if( WM_Control_Window_ID == Rooms_Colors.Settings.Create_rooms_button_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case BN_CLICKED:
         case BN_DBLCLICKED:
          {
           ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg( Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0 );

           if( Button_is_checked ) Rooms.Settings.Create_Rooms = 0;
           else Rooms.Settings.Create_Rooms = 1;

           BroadcastMessage( SM_SHOW_SETTINGS );
          }
         break;
        }
      }

     if( WM_Control_Window_ID == Rooms_Colors.Settings.Selected_room_cmbox_ID )
      {
       switch( WM_Control_Action_ID )
        {
         case CBN_ENTER:
          {
           LONG Selected_string = (LONG) WinSendDlgItemMsg( Window, Rooms_Colors.Settings.Selected_room_cmbox_ID, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0 );

           if( Selected_string != LIT_NONE )
            {
             if( Selected_string == 0 ) Rooms_Colors.RTSettings.Selected_room = NORTHERN_ROOM;
             if( Selected_string == 1 ) Rooms_Colors.RTSettings.Selected_room = WESTERN_ROOM;
             if( Selected_string == 2 ) Rooms_Colors.RTSettings.Selected_room = EASTERN_ROOM;
             if( Selected_string == 3 ) Rooms_Colors.RTSettings.Selected_room = SOUTHERN_ROOM;
             if( Selected_string == 4 ) Rooms_Colors.RTSettings.Selected_room = SHELL_ROOM;

             BroadcastMessage( SM_SHOW_SETTINGS );
             BroadcastMessage( SM_RECOGNIZE_THEME );
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

     if( WM_Control_Button_ID == Rooms_Colors.Settings.WinTitles_Button_ID )
      {
       ShowWPSColorPalette();
      }

     if( WM_Control_Button_ID == Rooms_Colors.Settings.Wallpaper_button_ID )
      {
       FILEDLG Parameters; HWND OpenFile_window;

       bzero( &Parameters, sizeof( FILEDLG ) );
       Parameters.cbSize = sizeof( FILEDLG );
       Parameters.fl = FDS_OPEN_DIALOG | FDS_CENTER;

       LONG Code_page = Enhancer.Code_page;

       if( Code_page == RUSSIAN ) Parameters.pszTitle = StrConst_RU_Pages_Rooms_colors_Wallpaper_dialog;
       else Parameters.pszTitle = StrConst_EN_Pages_Rooms_colors_Wallpaper_dialog;

       if( Rooms_Colors.RTSettings.FileDlg_path[ 0 ] == 0 )
        {
         GetCurrentPath( Parameters.szFullFile );
         strcat( Parameters.szFullFile, "\\Bitmap\\Rooms\\*.bmp" );
        }
       else
        {
         strcpy( Parameters.szFullFile, Rooms_Colors.RTSettings.FileDlg_path );
         strcat( Parameters.szFullFile, "\\*.bmp" );
        }

       OpenFile_window = WinFileDlg( HWND_DESKTOP, Window, &Parameters );

       if( OpenFile_window != NULLHANDLE ) if( Parameters.lReturn == DID_OK )
        if( stristr( ".bmp", Parameters.szFullFile ) )
         {
          PCHAR File_name = NULL; PCHAR Name_in_path = NULL; INT Count;
          if( Rooms_Colors.RTSettings.Selected_room == SHELL_ROOM ) File_name = Rooms.Settings.Wallpaper_for_shell_room;
          if( Rooms_Colors.RTSettings.Selected_room == NORTHERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_northern_room;
          if( Rooms_Colors.RTSettings.Selected_room == WESTERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_western_room;
          if( Rooms_Colors.RTSettings.Selected_room == EASTERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_eastern_room;
          if( Rooms_Colors.RTSettings.Selected_room == SOUTHERN_ROOM ) File_name = Rooms.Settings.Wallpaper_for_southern_room;

          strncpy( File_name, Parameters.szFullFile, SIZE_OF_PATH );

          strncpy( Rooms_Colors.RTSettings.FileDlg_path, Parameters.szFullFile, SIZE_OF_PATH );
          CutNameInPath( Rooms_Colors.RTSettings.FileDlg_path );

          WinSendMsg( Window, SM_SHOW_SETTINGS, 0, 0 );
         }
      }

     if( WM_Control_Button_ID == OK_BUTTON_ID )
      {
       CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
       HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

       if( Ini_file )
        {
         // Узнаем цвета.
         if( Rooms_Colors.RTSettings.Selected_room != SHELL_ROOM )
          {
           PLONG AT_Text_color = 0;       PLONG IT_Text_color = 0;
           PLONG AT_Background_color = 0; PLONG IT_Background_color = 0;
           PLONG AT_Color_1 = 0;          PLONG AT_Color_2 = 0;          PLONG AT_Color_3 = 0;
           PLONG IT_Color_1 = 0;          PLONG IT_Color_2 = 0;          PLONG IT_Color_3 = 0;

           if( Rooms_Colors.RTSettings.Selected_room == NORTHERN_ROOM )
            {
             AT_Text_color = (PLONG) &Painter.Settings.Northern_AT_Text_color;
             IT_Text_color = (PLONG) &Painter.Settings.Northern_IT_Text_color;
             AT_Background_color = (PLONG) &Painter.Settings.Northern_AT_Background_color;
             IT_Background_color = (PLONG) &Painter.Settings.Northern_IT_Background_color;

             AT_Color_1 = (PLONG) &Painter.Settings.Northern_AT_Color_1;       IT_Color_1 = (PLONG) &Painter.Settings.Northern_IT_Color_1;
             AT_Color_2 = (PLONG) &Painter.Settings.Northern_AT_Color_2;       IT_Color_2 = (PLONG) &Painter.Settings.Northern_IT_Color_2;
             AT_Color_3 = (PLONG) &Painter.Settings.Northern_AT_Color_3;       IT_Color_3 = (PLONG) &Painter.Settings.Northern_IT_Color_3;
            }

           if( Rooms_Colors.RTSettings.Selected_room == WESTERN_ROOM )
            {
             AT_Text_color = (PLONG) &Painter.Settings.Western_AT_Text_color;
             IT_Text_color = (PLONG) &Painter.Settings.Western_IT_Text_color;
             AT_Background_color = (PLONG) &Painter.Settings.Western_AT_Background_color;
             IT_Background_color = (PLONG) &Painter.Settings.Western_IT_Background_color;

             AT_Color_1 = (PLONG) &Painter.Settings.Western_AT_Color_1;       IT_Color_1 = (PLONG) &Painter.Settings.Western_IT_Color_1;
             AT_Color_2 = (PLONG) &Painter.Settings.Western_AT_Color_2;       IT_Color_2 = (PLONG) &Painter.Settings.Western_IT_Color_2;
             AT_Color_3 = (PLONG) &Painter.Settings.Western_AT_Color_3;       IT_Color_3 = (PLONG) &Painter.Settings.Western_IT_Color_3;
            }

           if( Rooms_Colors.RTSettings.Selected_room == EASTERN_ROOM )
            {
             AT_Text_color = (PLONG) &Painter.Settings.Eastern_AT_Text_color;
             IT_Text_color = (PLONG) &Painter.Settings.Eastern_IT_Text_color;
             AT_Background_color = (PLONG) &Painter.Settings.Eastern_AT_Background_color;
             IT_Background_color = (PLONG) &Painter.Settings.Eastern_IT_Background_color;

             AT_Color_1 = (PLONG) &Painter.Settings.Eastern_AT_Color_1;       IT_Color_1 = (PLONG) &Painter.Settings.Eastern_IT_Color_1;
             AT_Color_2 = (PLONG) &Painter.Settings.Eastern_AT_Color_2;       IT_Color_2 = (PLONG) &Painter.Settings.Eastern_IT_Color_2;
             AT_Color_3 = (PLONG) &Painter.Settings.Eastern_AT_Color_3;       IT_Color_3 = (PLONG) &Painter.Settings.Eastern_IT_Color_3;
            }

           if( Rooms_Colors.RTSettings.Selected_room == SOUTHERN_ROOM )
            {
             AT_Text_color = (PLONG) &Painter.Settings.Southern_AT_Text_color;
             IT_Text_color = (PLONG) &Painter.Settings.Southern_IT_Text_color;
             AT_Background_color = (PLONG) &Painter.Settings.Southern_AT_Background_color;
             IT_Background_color = (PLONG) &Painter.Settings.Southern_IT_Background_color;

             AT_Color_1 = (PLONG) &Painter.Settings.Southern_AT_Color_1;       IT_Color_1 = (PLONG) &Painter.Settings.Southern_IT_Color_1;
             AT_Color_2 = (PLONG) &Painter.Settings.Southern_AT_Color_2;       IT_Color_2 = (PLONG) &Painter.Settings.Southern_IT_Color_2;
             AT_Color_3 = (PLONG) &Painter.Settings.Southern_AT_Color_3;       IT_Color_3 = (PLONG) &Painter.Settings.Southern_IT_Color_3;
            }

           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Active_ID ), PP_FOREGROUNDCOLOR, 0, NULL, sizeof( ULONG ), AT_Text_color, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Active_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), AT_Background_color, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Inactive_ID ), PP_FOREGROUNDCOLOR, 0, NULL, sizeof( ULONG ), IT_Text_color, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.WinTitles_Container_ID ), Rooms_Colors.Settings.WinTitles_Palette_ID ), Rooms_Colors.Settings.WinTitles_Inactive_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), IT_Background_color, QPF_NOINHERIT );

           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_1_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), AT_Color_1, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_2_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), AT_Color_2, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Active_3_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), AT_Color_3, QPF_NOINHERIT );

           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_1_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), IT_Color_1, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_2_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), IT_Color_2, QPF_NOINHERIT );
           WinQueryPresParam( WinWindowFromID( WinWindowFromID( WinWindowFromID( Window, Rooms_Colors.Settings.NeonPalette_Container_ID ), Rooms_Colors.Settings.NeonPalette_Palette_ID ), Rooms_Colors.Settings.NeonPalette_Inactive_3_ID ), PP_BACKGROUNDCOLOR, 0, NULL, sizeof( ULONG ), IT_Color_3, QPF_NOINHERIT );
          }

         // Записываем настройки.
         PrfWriteProfileData( Ini_file, "Settings", "Create Rooms", &Rooms.Settings.Create_Rooms, sizeof( BYTE ) );

         PrfWriteProfileData( Ini_file, "Settings", "Wallpaper for shell room", Rooms.Settings.Wallpaper_for_shell_room, strlen( Rooms.Settings.Wallpaper_for_shell_room ) + 1 );
         PrfWriteProfileData( Ini_file, "Settings", "Wallpaper for northern room", Rooms.Settings.Wallpaper_for_northern_room, strlen( Rooms.Settings.Wallpaper_for_northern_room ) + 1 );
         PrfWriteProfileData( Ini_file, "Settings", "Wallpaper for western room", Rooms.Settings.Wallpaper_for_western_room, strlen( Rooms.Settings.Wallpaper_for_western_room ) + 1 );
         PrfWriteProfileData( Ini_file, "Settings", "Wallpaper for eastern room", Rooms.Settings.Wallpaper_for_eastern_room, strlen( Rooms.Settings.Wallpaper_for_eastern_room ) + 1 );
         PrfWriteProfileData( Ini_file, "Settings", "Wallpaper for southern room", Rooms.Settings.Wallpaper_for_southern_room, strlen( Rooms.Settings.Wallpaper_for_southern_room ) + 1 );

         // Записываем цвета.
         PrfWriteProfileData( Ini_file, "Drawing", "Northern AT Text color", &Painter.Settings.Northern_AT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern IT Text color", &Painter.Settings.Northern_IT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern AT Background color", &Painter.Settings.Northern_AT_Background_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern IT Background color", &Painter.Settings.Northern_IT_Background_color, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Western AT Text color", &Painter.Settings.Western_AT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western IT Text color", &Painter.Settings.Western_IT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western AT Background color", &Painter.Settings.Western_AT_Background_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western IT Background color", &Painter.Settings.Western_IT_Background_color, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Eastern AT Text color", &Painter.Settings.Eastern_AT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern IT Text color", &Painter.Settings.Eastern_IT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern AT Background color", &Painter.Settings.Eastern_AT_Background_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern IT Background color", &Painter.Settings.Eastern_IT_Background_color, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Southern AT Text color", &Painter.Settings.Southern_AT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern IT Text color", &Painter.Settings.Southern_IT_Text_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern AT Background color", &Painter.Settings.Southern_AT_Background_color, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern IT Background color", &Painter.Settings.Southern_IT_Background_color, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Northern AT Color 1", &Painter.Settings.Northern_AT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern AT Color 2", &Painter.Settings.Northern_AT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern AT Color 3", &Painter.Settings.Northern_AT_Color_3, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern IT Color 1", &Painter.Settings.Northern_IT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern IT Color 2", &Painter.Settings.Northern_IT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Northern IT Color 3", &Painter.Settings.Northern_IT_Color_3, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Western AT Color 1", &Painter.Settings.Western_AT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western AT Color 2", &Painter.Settings.Western_AT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western AT Color 3", &Painter.Settings.Western_AT_Color_3, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western IT Color 1", &Painter.Settings.Western_IT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western IT Color 2", &Painter.Settings.Western_IT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Western IT Color 3", &Painter.Settings.Western_IT_Color_3, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Eastern AT Color 1", &Painter.Settings.Eastern_AT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern AT Color 2", &Painter.Settings.Eastern_AT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern AT Color 3", &Painter.Settings.Eastern_AT_Color_3, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern IT Color 1", &Painter.Settings.Eastern_IT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern IT Color 2", &Painter.Settings.Eastern_IT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Eastern IT Color 3", &Painter.Settings.Eastern_IT_Color_3, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Drawing", "Southern AT Color 1", &Painter.Settings.Southern_AT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern AT Color 2", &Painter.Settings.Southern_AT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern AT Color 3", &Painter.Settings.Southern_AT_Color_3, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern IT Color 1", &Painter.Settings.Southern_IT_Color_1, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern IT Color 2", &Painter.Settings.Southern_IT_Color_2, sizeof( LONG ) );
         PrfWriteProfileData( Ini_file, "Drawing", "Southern IT Color 3", &Painter.Settings.Southern_IT_Color_3, sizeof( LONG ) );

         PrfWriteProfileData( Ini_file, "Colors", NULL, NULL, 0 );

         PrfCloseProfile( Ini_file );

         BroadcastRSMessages();
         NiceReadSettings( 1 );
        }
      }

     if( WM_Control_Button_ID == PD_BUTTON_ID )
      {
       if( Page->SetDefSettings ) Page->SetDefSettings( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext1 ) Page->SetDefSettings_Ext1( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext2 ) Page->SetDefSettings_Ext2( Page->Settings_to_show );
       if( Page->SetDefSettings_Ext3 ) Page->SetDefSettings_Ext3( Page->Settings_to_show );

       WinSendMsg( Window, SM_SET_PRESENTATION_PARAMETERS, 0, 0 );
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
