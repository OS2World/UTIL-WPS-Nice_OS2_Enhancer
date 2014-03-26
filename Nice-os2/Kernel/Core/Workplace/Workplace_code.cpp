
// ─── Проверяет свойства окна ───

// Frame_window - окно для проверки.
BYTE Workplace_HasShellWindowControls( HWND Frame_window )
{
 // Окно оболочки имеет только заголовок, у него нет картинки и кнопок.
 if( WinWindowFromID( Frame_window, FID_TITLEBAR ) == NULLHANDLE ) return 0;
 if( WinWindowFromID( Frame_window, FID_CLIENT ) == NULLHANDLE ) return 0;

 if( WinWindowFromID( Frame_window, FID_SYSMENU ) != NULLHANDLE ) return 0;
 if( WinWindowFromID( Frame_window, FID_MINMAX ) != NULLHANDLE ) return 0;

 // Возврат.
 return 1;
}

// ─── Проверяет расположение окна ───

// Frame_window - окно для проверки, Window_placement - расположение окна.
BYTE Workplace_HasShellPlacement( HWND Frame_window, PSWP Window_placement )
{
 // Окно должно иметь свойства окна оболочки.
 if( !Workplace_HasShellWindowControls( Frame_window ) ) return 0;

 // Узнаем размер экрана.
 INT X_Screen = WinQuerySysValue( QueryDesktopWindow(), SV_CXSCREEN );

 // Окно оболочки должно быть расположено за пределами экрана.
 INT Required_width = X_Screen + FrameWidth( Frame_window ) * 2;

 // Если это так - возвращаем 1.
 if( Window_placement->x <= 0 )
  if( Window_placement->x + Window_placement->cx >= X_Screen )
   if( Window_placement->cx == Required_width )
    return 1;

 // Иначе возвращаем 0.
 return 0;
}

// ─── Узнает окно оболочки ───

HWND Workplace_QueryShellWindow( VOID )
{
 // Окно оболочки.
 HWND Shell_window = NULLHANDLE;

 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно не скрыто:
   if( WinIsWindowVisible( Window ) )
    {
     // Если это окно WPS:
     if( IsFolderWindow( Window ) )
      {
       // Узнаем расположение окна и его состояние.
       SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

       // Окно оболочки должно быть расположено за пределами экрана.
       if( Workplace_HasShellPlacement( Window, &Window_placement ) )
        {
         // Если окно оболочки еще не найдено - запоминаем его.
         if( Shell_window == NULLHANDLE ) Shell_window = Window;
         // А если оно было найдено:
         else
          {
           // Окно оболочки может быть только одно.
           Shell_window = NULLHANDLE;

           // Завершаем перебор окон.
           break;
          }
        }
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возвращаем окно оболочки.
 return Shell_window;
}

// ─── Узнает, в каком состоянии окно оболочки ───

// Возвращаемое значение: 1 - окно доступно, 0 - окно уменьшено.
BYTE Workplace_ShellIsAvailable( VOID )
{
 // Проверяем, показано ли окно оболочки.
 if( Workplace_QueryShellWindow() != NULLHANDLE ) return 1;
 else return 0;
}

// ─── Возвращает окно оболочки, найденное ранее ───

HWND Workplace_GetDetectedShellWindow( VOID )
{
 // Если окна оболочки нет - узнаем его.
 if( !WinIsWindow( WinQueryAnchorBlock( Workplace.RTSettings.Shell_window ), Workplace.RTSettings.Shell_window ) )
  Workplace.RTSettings.Shell_window = Workplace_QueryShellWindow();

 // Возвращаем окно оболочки.
 return Workplace.RTSettings.Shell_window;
}

// ─── Запоминает окно оболочки, если оно найдено при выполнении каких-либо действий ───

VOID Workplace_RememberShellWindow( HWND Window )
{
 // Запоминаем окно оболочки.
 Workplace.RTSettings.Shell_window = Window;

 // Возврат.
 return;
}
