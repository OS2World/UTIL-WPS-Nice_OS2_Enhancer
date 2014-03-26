
// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsShowing( PSMHSTRUCT Message )
{
 // До того, как окно рамки становится видимым, оно получает сообщение об этом.
 HWND Window = NULLHANDLE;

 if( Message->msg == WM_ADJUSTWINDOWPOS )
  {
   PSWP Window_placement = (PSWP) Message->mp1;

   if( Window_placement != NULL )
    if( Window_placement->fl == SWP_SHOW )
     if( !WinIsWindowVisible( Message->hwnd ) )
      Window = Message->hwnd;
  }

 // Затем, если это не окно диалога, окно рабочей области получает второе сообщение.
 if( Message->msg == WM_SHOW )
  if( Message->mp1 == (MPARAM) 1 )
   Window = WinQueryWindow( Message->hwnd, QW_PARENT );

 // Проверяем окно.
 if( Window != NULLHANDLE )
  if( IsFrameWindow( Window ) )
   if( WinQueryWindow( Window, QW_PARENT ) == QueryDesktopWindow() )
    return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsMoving( PSMHSTRUCT Message )
{
 // Если идет сообщение о перемещении окна:
 if( Message->msg == WM_MOVE )
  {
   // Если окно, которому идет сообщение, не окно рамки - возврат.
   if( !IsFrameWindow( Message->hwnd ) ) return 0;

   // Узнаем окно рабочего стола.
   HWND Desktop = QueryDesktopWindow();

   // Если сообщение направляется окну рамки верхнего уровня:
   if( WinQueryWindow( Message->hwnd, QW_PARENT ) == Desktop )
    {
     // Проверяем расположение указателя мыши.
     BYTE Mouse_is_over_title = 0;

     // Если одна из кнопок мыши нажата:
     if( MouseIsBusy() )
      {
       // Узнаем окно, над которым расположен указатель мыши.
       POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );
       HWND Window_under_pointer = WinWindowFromPoint( Desktop, &Pointer, 1 );

       // Если указатель мыши расположен над другим окном, например, над окном WPS, то
       // окно рамки, которое получает сообщение WM_MOVE, передвигается самостоятельно.
       PID Process_ID_WRM = 0; WinQueryWindowProcess( Message->hwnd, &Process_ID_WRM, NULL );
       PID Process_ID_WUP = 0; WinQueryWindowProcess( Window_under_pointer, &Process_ID_WUP, NULL );
       if( Process_ID_WRM != Process_ID_WUP ) return 1;
      }
     // А если ни одна кнопка мыши не нажата:
     else
      {
       // Считаем, что окно передвигается самостоятельно.
       return 1;
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsActivating( PSMHSTRUCT Message )
{
 // Если окно становится выбранным:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 1 )
  {
   // Узнаем окно рамки.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // Если выбранным становится именно это окно, а не одно из его дочерних окон:
   if( Frame_window == Message->hwnd )
    {
     // Если у окна есть заголовок:
     if( WinWindowFromID( Frame_window, FID_TITLEBAR ) != NULLHANDLE )
      {
       // Если родительское окно - рабочий стол:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // Все в порядке, возврат.
         return 1;
        }
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsInactivating( PSMHSTRUCT Message )
{
 // Если окно перестает быть выбранным:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 0 )
  {
   // Узнаем окно рамки.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // Если выбранным становится именно это окно, а не одно из его дочерних окон:
   if( Frame_window == Message->hwnd )
    {
     // Если родительское окно - рабочий стол:
     if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
      {
       // Все в порядке, возврат.
       return 1;
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_FrameWindowIsActivating( PSMHSTRUCT Message )
{
 // Если окно становится выбранным:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 1 )
  {
   // Узнаем окно рамки.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // Если выбранным становится именно это окно, а не одно из его дочерних окон:
   if( Frame_window == Message->hwnd )
    {
     // Все в порядке, возврат.
     return 1;
    }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет сообщение, направляемое окну ───

// Все переменные - внешние. Возвращение "1" не означает, что Message->hwnd
// является окном рамки, поэтому надо будет вызвать еще QueryFrameWindow().
BYTE HookEvents_FrameWindowIsClosing( PQMSG Message )
{
 // Проверяем сообщение, передаваемое окну.
 if( ( Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_CLOSE ) ||
     ( Message->msg == WM_CLOSE ) ||
     ( Message->msg == WM_QUIT ) )
  return 1;

 // Возврат.
 return 0;
}
