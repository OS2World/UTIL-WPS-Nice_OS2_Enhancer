
// ─── Определяет, какие кнопки надо рисовать в случае, если все строки меню недоступны ───

// Frame_window - окно рамки.
LONG Painter_PossibleAllowedActions( HWND Frame_window )
{
 // Для некоторых окон кнопки нужны всегда.
 if( IsRZApiWindow( Frame_window ) ) return ALL_ACTIONS;

 // Возврат.
 return NO_ACTION;
}

// ─── Определяет, надо ли рисовать для окна кнопку уменьшения ───

// Frame_window - окно рамки.
BYTE Painter_MinimizeActionIsAllowed( HWND Frame_window )
{
 // Эту кнопку можно отключить для окон WPS.
 if( Painter.Settings.Accelerate_folders_closing )
  {
   // Если это одно из окон WPS или MDesk - кнопку рисовать не надо, возврат.
   if( IsFolderWindow( Frame_window ) ) return 0;
   if( IsJobCnrWindow( Frame_window ) ) return 0;
   if( IsMDeskWindow( Frame_window ) ) return 0;
  }

 // Возврат.
 return 1;
}

// ─── Определяет, надо ли рисовать для окна только кнопку закрытия ───

// Frame_window - окно рамки.
LONG Painter_OneActionIsAllowed( HWND Frame_window )
{
 // Для окон WPS:
 if( Painter.Settings.Accelerate_folders_closing )
  {
   if( IsWinListWindow( Frame_window ) ) return HIDE_ACTION;
   if( IsPaletteWindow( Frame_window ) ) return CLOSE_ACTION;
  }

 // Для окон Java:
 if( IsJavaWindow( WinWindowFromID( Frame_window, FID_CLIENT ) ) &&
     WindowIsCreatedBy( APP_APPLETVIEWER, Frame_window ) ) return CLOSE_ACTION;

 // Возврат.
 return NO_ACTION;
}

// ─── Узнает состояние кнопок в правом верхнем углу окна ───

// Frame_window - окно рамки, Target - какие кнопки надо проверить, Consider_all_settings - учитывать все настройки для кнопок.
LONG Painter_QueryButtonsState( HWND Frame_window, ULONG Target, BYTE Consider_all_settings )
{
 // Кнопки могут быть заданы неправильно.
 if( Target & RESTORE_ACTION || Target & ROLLUP_ACTION )
  {
   Target &= ~RESTORE_ACTION;
   Target &= ~ROLLUP_ACTION;

   Target |= MAXIMIZE_ACTION;
  }

 // Узнаем окно картинки в левом верхнем углу окна.
 HWND SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );

 // Узнаем окно обычных кнопок.
 HWND MinMax_window = WinWindowFromID( Frame_window, FID_MINMAX );

 // Если окна картинки и окна обычных кнопок нет - рисовать новые кнопки не надо. Приложение может
 // вести себя как угодно, например, Regedit воспринимает нажатие на кнопку закрытия как нажатие "ОК".
 if( SysMenu_window == NULLHANDLE ) if( MinMax_window == NULLHANDLE ) return NO_ACTION;

 // Если есть окно картинки - узнаем состояние меню, которое появляется при нажатии на нее.
 // Если окна картинки нет, но есть окно обычных кнопок - узнаем их состояние.
 BYTE Ask_SysMenu = 0; if( SysMenu_window != NULLHANDLE ) Ask_SysMenu = 1;
 BYTE Ask_MinMax = 0; if( SysMenu_window == NULLHANDLE ) if( MinMax_window != NULLHANDLE ) Ask_MinMax = 1;

 // Если кнопки рисовать нельзя - возврат.
 if( !Painter_PermissionForButtonsDrawing( Frame_window ) ) return NO_ACTION;

 // Узнаем состояние кнопок.
 LONG Draw_maximize_button = 0; LONG Draw_minimize_button = 0; LONG Draw_close_button = 0;
 LONG Draw_rollup_button = 0; LONG Draw_restore_button = 0; LONG Draw_hide_button = 0;

 // Если запрашивается состояние меню - проверяем, показана ли картинка и заголовок.
 if( Ask_SysMenu )
  {
   // Если окно картинки не показано - рисовать кнопки не надо, возврат.
   if( !WindowIsPresent( SysMenu_window ) ) return NO_ACTION;

   // Узнаем окно заголовка.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

   // Если окно заголовка не показано - рисовать кнопки не надо, возврат.
   if( !WindowIsPresent( TitleBar_window ) ) return NO_ACTION;
  }

 // Если запрашивается состояние кнопок - проверяем, показан ли заголовок.
 if( Ask_MinMax )
  {
   // Узнаем окно заголовка.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

   // Если окно заголовка не показано - рисовать кнопки не надо, возврат.
   if( !WindowIsPresent( TitleBar_window ) ) return NO_ACTION;
  }

 // Для некоторых окон надо рисовать только кнопку закрытия.
 if( Consider_all_settings )
  {
   // Узнаем, так ли это.
   LONG Action = Painter_OneActionIsAllowed( Frame_window );
   if( Action != NO_ACTION ) return Action;
  }

 // Узнаем текущее состояние кнопок.
 LONG Current_state = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Current_state );

 // Если оно неизвестно и кнопки надо рисовать - надо узнать состояние строк меню для окна.
 if( Current_state == NO_ACTION )
  if( Painter.Settings.Draw_frames ) if( Painter.Settings.Draw_buttons )
   Target = ALL_ACTIONS;

 if( Target & MAXIMIZE_ACTION )
  {
   if( Ask_SysMenu ) Draw_maximize_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MAXIMIZE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_maximize_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MAXIMIZE, 0 ), 0 );
  }
 else
  {
   Draw_maximize_button = Current_state & MAXIMIZE_ACTION;
   Draw_rollup_button = Current_state & ROLLUP_ACTION;
  }

 if( Target & MINIMIZE_ACTION )
  {
   if( Ask_SysMenu ) Draw_minimize_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MINIMIZE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_minimize_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MINIMIZE, 0 ), 0 );
  }
 else
  {
   Draw_minimize_button = Current_state & MINIMIZE_ACTION;
  }

 if( Target & CLOSE_ACTION )
  {
   if( Ask_SysMenu ) Draw_close_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_CLOSE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_close_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_CLOSE, 0 ), 0 );
  }
 else
  {
   Draw_close_button = Current_state & CLOSE_ACTION;
  }

 // Вместо кнопки уменьшения может быть кнопка сокрытия.
 if( !Draw_minimize_button )
  {
   if( Target & MINIMIZE_ACTION )
    {
     if( Ask_SysMenu ) Draw_hide_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_HIDE, INCLUDE_SUBMENUS ), 0 );
     if( Ask_MinMax ) Draw_hide_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_HIDE, 0 ), 0 );
    }
   else
    {
     Draw_hide_button = Current_state & HIDE_ACTION;
    }
  }

 // Для некоторых окон эти кнопки рисовать не надо.
 if( Consider_all_settings ) if( Draw_minimize_button || Draw_hide_button )
  if( !Painter_MinimizeActionIsAllowed( Frame_window ) )
   Draw_minimize_button = Draw_hide_button = 0;

 // Если окно увеличено - надо рисовать кнопки "Восстановить" и "Убрать наверх".
 // Если кнопки увеличения нет - должны быть две другие кнопки.
 if( !Draw_maximize_button )
  {
   // Узнаем расположение окна и его состояние.
   SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

   // Если оно увеличено - надо рисовать кнопки "Восстановить" и "Убрать наверх".
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     Draw_rollup_button = 1;
     Draw_restore_button = 1;
    }
  }

 // Для некоторых окон рисовать кнопку "Убрать наверх" не надо.
 if( Consider_all_settings ) if( Draw_rollup_button )
  Draw_rollup_button = Painter_PermissionForRolling( Frame_window );

 // Для окон постоянного размера не надо рисовать кнопку увеличения.
 if( Draw_maximize_button || Draw_restore_button )
  if( FrameType( Frame_window ) == FT_CONST )
   Draw_maximize_button = Draw_restore_button = Draw_rollup_button = 0;

 // Если запрашивается состояние меню и все его строки недоступны - надо рисовать кнопки по умолчанию.
 if( Ask_SysMenu )
  if( !Draw_maximize_button && !Draw_minimize_button && !Draw_rollup_button && !Draw_close_button )
   return Painter_PossibleAllowedActions( Frame_window );

 // Задаем состояние кнопок.
 LONG Buttons_state = NO_ACTION;
 if( Draw_maximize_button ) Buttons_state |= MAXIMIZE_ACTION;
 if( Draw_minimize_button ) Buttons_state |= MINIMIZE_ACTION;
 if( Draw_hide_button ) Buttons_state |= HIDE_ACTION;
 if( Draw_restore_button ) Buttons_state |= RESTORE_ACTION;
 if( Draw_rollup_button ) Buttons_state |= ROLLUP_ACTION;
 if( Draw_close_button ) Buttons_state |= CLOSE_ACTION;

 // Возврат.
 return Buttons_state;
}
