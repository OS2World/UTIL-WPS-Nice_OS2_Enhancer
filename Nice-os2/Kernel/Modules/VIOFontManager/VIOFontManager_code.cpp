
// ─── Вызывает окно смены шрифта ───

// Frame_window - текстовое окно.
VOID VIOFontManager_OpenVIOFontMetricsDialog( HWND Frame_window )
{
 // Если на экране уже есть окно выбора шрифта - возврат.
 if( SystemWindowIsPresent( FIND_VIO_FONT_DIALOG, FIND_VISIBLE_WINDOW ) ) return;

 // Узнаем окно картинки.
 HWND SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );

 // Если его нет - возврат.
 if( !WinIsWindow( WinQueryAnchorBlock( SysMenu_window ), SysMenu_window ) ) return;

 // Узнаем, есть ли в меню строка для вызова окна смены шрифта.
 BYTE Menu_item_is_present = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_VIO_FONT, INCLUDE_SUBMENUS ), 0 );

 // Если она есть:
 if( Menu_item_is_present )
  {
   // Скрываем окно.
   WinShowWindow( Frame_window, 0 );

   // Посылаем в окно сообщение от меню.
   WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_FONT, MPFROM2SHORT( CMDSRC_MENU, 0 ) );

   // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, шрифт можно будет менять.
   HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SET_VIO_FONT, (MPARAM) Frame_window );
  }

 // Возврат.
 return;
}

// ─── Выбирает в нем требуемый шрифт и применяет его ───

// Frame_window - текстовое окно.
VOID VIOFontManager_SubmitVIOFontMetricsDialog( HWND Frame_window )
{
 // Находим окно со списком шрифтов.
 HWND Font_dialog = NULLHANDLE;

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 {
  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
  while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // Если окно скрыто - продолжаем перебор окон.
    if( !WinIsWindowVisible( Window ) ) continue;

    // Если это не окно рамки - продолжаем перебор окон.
    if( !IsFrameWindow( Window ) ) continue;

    // Если это окно для выбора шрифта:
    if( IsVIOFontMetricsDialog( Window ) )
     {
      // Узнаем его владельца:
      HWND Owner_frame = QueryFrameWindow( WinQueryWindow( Window, QW_OWNER ) );

      // Если это текстовое окно, для которого надо менять шрифт:
      if( Owner_frame == Frame_window )
       {
        // Запоминаем окно для выбора шрифта.
        Font_dialog = Window;

        // Завершаем перебор окон.
        break;
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // Если окно найдено:
 if( Font_dialog != NULLHANDLE )
  {
   // Узнаем размер шрифта.
   INT X = 0; INT Y = 0;

   // Для некоторых окон размер шрифта заранее.
   if( VIOFontManager_VIOFontIsPreDefined( Frame_window ) ) { X = 10; Y = 6; }

   // Узнаем имя приложения, создавшего окно.
   CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

   // Если его удалось определить:
   if( Exe_name[ 0 ] != 0 )
    {
     // Запоминаем размер шрифта
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_1; Y = VIOFontManager.Settings.VIOFontMetrics.Y_1; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_2; Y = VIOFontManager.Settings.VIOFontMetrics.Y_2; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_3; Y = VIOFontManager.Settings.VIOFontMetrics.Y_3; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_4; Y = VIOFontManager.Settings.VIOFontMetrics.Y_4; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_5; Y = VIOFontManager.Settings.VIOFontMetrics.Y_5; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_6; Y = VIOFontManager.Settings.VIOFontMetrics.Y_6; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_7; Y = VIOFontManager.Settings.VIOFontMetrics.Y_7; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_8; Y = VIOFontManager.Settings.VIOFontMetrics.Y_8; }
    }

   // Если шрифт задан:
   if( X != 0 && Y != 0 )
    {
     // Если в окне диалога выбора шрифтов есть окно рабочей области - используем его.
     HWND Client_window = WinWindowFromID( Font_dialog, FID_CLIENT );
     if( Client_window != NULLHANDLE ) Font_dialog = Client_window;

     // Составляем строку для выбора в списке.
     // Строк две, так как в разных версиях OS/2 шрифты задаются по-разному.
     CHAR Metrics_X[ 25 ] = ""; itoa( X, Metrics_X, 10 );
     CHAR Metrics_Y[ 25 ] = ""; itoa( Y, Metrics_Y, 10 );

     CHAR String_without_spaces[ 25 ] = "";
     strcat( String_without_spaces, Metrics_X );
     strcat( String_without_spaces, " x " );
     strcat( String_without_spaces, Metrics_Y );

     CHAR String_with_spaces[ 25 ] = "";
     if( strlen( Metrics_X ) == 1 ) strcat( String_with_spaces, " " );
     strcat( String_with_spaces, Metrics_X );
     strcat( String_with_spaces, " x " );
     if( strlen( Metrics_Y ) == 1 ) strcat( String_with_spaces, " " );
     strcat( String_with_spaces, Metrics_Y );

     // Находим строку в списке.
     HWND List_field = FindFontListField( Font_dialog ); LONG Index = LIT_NONE;

     if( Index == LIT_NONE )
      {
       strcpy( VIOFontManager.RTSettings.Item_text, String_without_spaces );
       Index = (LONG) WinSendMsg( List_field, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), VIOFontManager.RTSettings.Item_text );
      }

     if( Index == LIT_NONE )
      {
       strcpy( VIOFontManager.RTSettings.Item_text, String_with_spaces );
       Index = (LONG) WinSendMsg( List_field, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), VIOFontManager.RTSettings.Item_text );
      }

     // Если она есть:
     if( Index != LIT_NONE )
      {
       // Делаем ее выбранной.
       WinSendMsg( List_field, LM_SELECTITEM, (MPARAM) Index, (MPARAM) 1 );

       // Составляем сообщение о нажатии клавиши Enter.
       MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
       MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
       ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0 );

       // Посылаем его.
       WinPostMsg( List_field, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinPostMsg( List_field, WM_CHAR, First_parameter_2, Second_parameter_2 );

       // Ждем некоторое время.
       for( INT Step = 0; Step < 12; Step ++ )
        {
         // Останавливаем выполнение потока.
         Retard();
         // Если окна выбора шрифта на экране нет - прекращаем ожидание.
         if( !SystemWindowIsPresent( FIND_VIO_FONT_DIALOG, FIND_VISIBLE_WINDOW ) ) break;
        }
      }

     // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, окно можно будет сделать видимым и выровнять по середине экрана.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SHOW_AND_ARRANGE, (MPARAM) Frame_window );
    }
  }

 // Возврат.
 return;
}
