
// ─── Проверяет, можно ли рисовать что-то, кроме заголовка ───

// Frame_window - окно рамки.
BYTE Painter_PermissionForCompleteDrawing( HWND Frame_window )
{
 // Если окно не задано - возврат.
 if( Frame_window == NULLHANDLE ) return 0;

 // Для окон ODIN надо рисовать только заголовок.
 if( IsWindowsWindow( Frame_window ) ) return 0;

 // То же самое - для окон WarpVision.
 if( IsVideoPlayerWindow( Frame_window ) ) return 0;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // То же ограничение - для окон PMMail.
   if( WindowIsCreatedBy( APP_PMMAIL, Frame_window ) ) return 0;

   // И для окон VisualAge C++ 4.x и Embellish.
   if( WindowIsCreatedBy( APP_VACPP, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_EMBELLISH, Frame_window ) ) return 0;

   // И для некоторых окон PM123.
   if( WinWindowFromID( Frame_window, FID_TITLEBAR ) == NULLHANDLE )
    if( WindowIsCreatedBy( APP_PM123, Frame_window ) ) return 0;

   // Проверяем, есть ли приложение в списке исключений.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_8 ) == EQUALLY ) return 0;
  }

 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_8 ) == EQUALLY ) return 0;
  }

 // Узнаем PID приложения, создавшего окно.
 PID Process_ID = 0; TID Thread_ID = 0;
 WinQueryWindowProcess( Frame_window, &Process_ID, &Thread_ID );

 // Проверяем его.
 if( Process_ID )
  {
   for( INT Process_count = 0; Process_count < PAINTER_STUBBORN_PID_TABLE; Process_count ++)
    if( Painter.RTSettings.Stubborn_processes[ Process_count ] == Process_ID ) return 0;
  }

 // Возврат.
 return 1;
}

// ─── Проверяет, можно ли рисовать для окна новые кнопки ───

// Frame_window - окно рамки.
BYTE Painter_PermissionForButtonsDrawing( HWND Frame_window )
{
 // Проверка нужна только в случае, если окна настоящих кнопок нет - тогда
 // может возникнуть постоянное рисование, которое выглядит как "мигание" рамки.
 if( WinWindowFromID( Frame_window, FID_MINMAX ) != NULLHANDLE ) return 1;

 // Для некоторых окон рисовать кнопки не надо.
 if( WindowIsCreatedBy( APP_WORDPRO, Frame_window ) ) return 0;

 // Возврат.
 return 1;
}

// ─── Проверяет, можно ли рисовать кнопку "Убрать наверх" ───

// Frame_window - окно рамки.
BYTE Painter_PermissionForRolling( HWND Frame_window )
{
 // Если родительское окно - не окно рабочего стола, то рисовать кнопку не надо.
 if( WinQueryWindow( Frame_window, QW_PARENT ) != QueryDesktopWindow() ) return 0;

 // Для текстовых окон рисование этой кнопки должно быть отключено.
 if( !Painter.Settings.Rollup_VIO_windows ) if( IsVIOWindow( Frame_window ) ) return 0;

 // И для некоторых других окон.
 if( IsHobWindow( Frame_window ) ) return 0;
 if( IsEPMEditorWindow( Frame_window ) ) return 0;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Проверяем, есть ли приложение в списке исключений.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_8 ) == EQUALLY ) return 0;
  }

 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_8 ) == EQUALLY ) return 0;
  }

 // Возврат.
 return 1;
}

// ─── Узнает, как надо рисовать рамку для окна постоянного размера ───

// Все переменные - внешние, возвращаемое значение - надо ли рисовать внутреннюю рамку.
BYTE Painter_PermissionForInnerFrameDrawing( HWND Frame_window, HWND Window, PRECT Rectangle )
{
 // Если у окна постоянного размера есть меню - рисовать внутреннюю рамку не надо.
 if( WinWindowFromID( Frame_window, FID_MENU ) != NULLHANDLE ) return 0;

 // Узнаем ширину рамки окна.
 INT Const_frame = 0; FindProperty( Frame_window, PRP_BORDER, &Const_frame );
 if( !Const_frame ) Const_frame = FrameWidth( Frame_window );

 // Узнаем высоту окна заголовка.
 HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
 RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );

 // Проверяем окна.
 while( Window != Frame_window && Window != NULLHANDLE )
  {
   // Узнаем расположение окна.
   SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

   // Если окно будет мешать внутренней рамке - ее надо перерисовать.
   INT Limit = Rectangle->yTop - Const_frame - TitleBar_rectangle.yTop;
   if( Window_placement.y + Window_placement.cy == Limit )
    if( WinIsWindowVisible( Window ) ) return 1;

   // Узнаем родительское окно.
   Window = WinQueryWindow( Window, QW_PARENT );
  }

 // Возврат.
 return 0;
}

// ─── Выбирает окно для рисования ───

// Все переменные - внешние.
HWND Painter_ChooseWindowForDrawing( HWND Window, PLONG Window_type )
{
 // Узнаем вид окна.
 *Window_type = WT_UNKNOWN;
 switch( WindowType( Window ) )
  {
   // Если это окно рамки - проверяем его.
   case WT_BORDER:
    {
     // Узнаем, как выглядит рамка окна.
     LONG Frame_type = FrameType( Window );

     // Если рамка не нарисована - ничего рисовать не надо.
     if( Frame_type == FT_RECT ) return NULLHANDLE;

     // Если рабочая область окна - окно Win-OS/2 или Odin, то ничего рисовать не надо.
     if( IsWindowsWindow( Window ) ) return NULLHANDLE;

     // Иначе - рисовать можно.
     *Window_type = WT_BORDER; return Window;
    }
   break;

   // Если это окно картинки - рисовать можно.
   case WT_SYSMENU:
    if( Painter.Settings.Draw_system_menus ) { *Window_type = WT_SYSMENU; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // Если это окно заголовка - рисовать можно.
   case WT_TITLEBAR:
    if( Painter.Settings.Draw_titles ) { *Window_type = WT_TITLEBAR; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // Если это окно кнопок - рисовать можно.
   case WT_MINMAX:
    if( Painter.Settings.Draw_buttons ) { *Window_type = WT_MINMAX; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // Если это окно меню - рисовать можно.
   case WT_MENU:
    if( Painter.Settings.Draw_menus ) { *Window_type = WT_MENU; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // Иначе - ничего рисовать не надо.
   default:
   return NULLHANDLE;
  }

 // Возврат.
 return NULLHANDLE;
}

// ─── Проверяет, можно ли перерисовать окно. Возвращает вид рамки окна ───

// Window - окно. Возвращаемое значение: NULLHANDLE - если нельзя, иначе - рамка окна.
// Переменная Window_type будет указывать на то, какое это окно - рамка, заголовок, и т.д.
HWND Painter_PermissionForDrawing( HWND Window, PLONG Window_type = NULL )
{
 // Выбираем окно для рисования.
 LONG Type = WT_UNKNOWN; if( Window_type == NULL ) Window_type = &Type;
 HWND Frame_window = Painter_ChooseWindowForDrawing( Window, Window_type );

 // Если окно неизвестно - возврат.
 if( Frame_window == NULLHANDLE ) return NULLHANDLE;

 // Для некоторых окон рисовать рамку не надо.
 if( IslSwitcherWindow( Frame_window ) ) return NULLHANDLE;
 if( IsSmartBarWindow( Frame_window ) ) return NULLHANDLE;
 if( IsVideoViewerWindow( Frame_window ) ) return NULLHANDLE;

 // Для некоторых окон надо рисовать только заголовок. Все остальные запросы отсекаются.
 if( *Window_type != WT_TITLEBAR )
  if( !Painter_PermissionForCompleteDrawing( Frame_window ) )
   return NULLHANDLE;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Проверяем, есть ли приложение в списке исключений.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_1 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_2 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_3 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_4 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_5 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_6 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_7 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_8 ) == EQUALLY ) return NULLHANDLE;
  }

 // Узнаем окно рабочей области для окна рамки.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_8 ) == EQUALLY ) return 0;
  }

 // Возврат.
 return Frame_window;
}

