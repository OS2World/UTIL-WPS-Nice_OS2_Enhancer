
// ─── Находит в заданном окне полоску просмотра ───

// Window - окно, Type - какую полоску надо найти, значение "SBS_*".
// Target_window_placement - расположение окна, для которого должна быть найдена полоска.
// Возвращаемое значение: окно полоски просмотра или NULLHANDLE.
HWND Scroller_FindScrollBar( HWND Window, BYTE Type, PSWP Target_window_placement = NULL )
{
 // Если расположение окна не указано - задаем пустые значения.
 HWND Desktop = QueryDesktopWindow();

 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 SWP Default_placement = { 0, Y_Screen * 2, X_Screen * 2, Y_Screen * (-1), X_Screen * (-1), NULLHANDLE, NULLHANDLE, 0, 0 };
 if( Target_window_placement == NULL ) Target_window_placement = &Default_placement;

 // Изначально окно полоски неизвестно.
 HWND Scroll_bar = NULLHANDLE;

 {
  // Перебираем окна, пока не найдем полоску.
  HENUM Enumeration = WinBeginEnumWindows( Window ); HWND Current_window = NULLHANDLE; 
  while( ( Current_window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // Если окно не скрыто:
    if( WinIsWindowVisible( Current_window ) )
     {
      // Если это полоска просмотра:
      if( IsScrollBarWindow( Current_window ) )
       {
        // Узнаем, как она расположена.
        SWP Rectangle = {0}; WinQueryWindowPos( Current_window, &Rectangle );

        // Если мы ищем как раз такую полоску - завершаем перебор окон.
        if( Type == SBS_VERT ) if( Rectangle.cy > Rectangle.cx )
         if( Rectangle.y + Rectangle.cy / 2 > Target_window_placement->y )
          if( Rectangle.y + Rectangle.cy / 2 < Target_window_placement->y + Target_window_placement->cy )
           { Scroll_bar = Current_window; break; }

        if( Type == SBS_HORZ ) if( Rectangle.cx > Rectangle.cy )
         if( Rectangle.x + Rectangle.cx / 2 > Target_window_placement->x )
          if( Rectangle.x + Rectangle.cx / 2 < Target_window_placement->x + Target_window_placement->cx )
           { Scroll_bar = Current_window; break; }
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // Возвращаем указатель на полоску, если она была найдена, или NULLHANDLE.
 return Scroll_bar;
}

// ─── Узнает состояние полоски просмотра ───

// ScrollBar - окно полоски просмотра, ее состояние надо вернуть в SB_State.
// Эта структура должна располагаться в разделяемой памяти, иначе возникнет ошибка.
VOID Scroller_QueryScrollBarState( HWND ScrollBar, PSBCDATA SB_State )
{
 // Полоска просмотра может быть отключена.
 SB_State->sHilite = WinIsWindowEnabled( ScrollBar );

 // Узнаем число делений. Значения posLast >= posFirst >= 0.
 MRESULT Bounds = WinSendMsg( ScrollBar, SBM_QUERYRANGE, 0, 0 );
 SB_State->posFirst = SHORT1FROMMP( Bounds );
 SB_State->posLast  = SHORT2FROMMP( Bounds );

 // Узнаем положение движка в полоске.
 MRESULT Slider = WinSendMsg( ScrollBar, SBM_QUERYPOS, 0, 0 );
 SB_State->posThumb = SHORT1FROMMP( Slider );

 // Возврат.
 return;
}
