
// ─── Проверяет, установлен ли FileBar в качестве оболочки ───

BYTE Krnl_Environment_ShellIsFileBar( VOID )
{
 // FileBar может быть вызван после расширителя.
 if( Krnl_Environment.RTSettings.Shell_is_FileBar ) return 1;

 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно скрыто - продолжаем перебор окон.
   if( !WinIsWindowVisible( Window ) ) continue;

   // Если это FileBar - считаем, что он используется в качестве оболочки.
   if( IsFileBarWindow( Window ) )
    {
     Krnl_Environment.RTSettings.Shell_is_FileBar = 1;
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return Krnl_Environment.RTSettings.Shell_is_FileBar;
}

// ─── Узнает, установлена ли оболочка WPS ───

// Возвращаемое значение: 1 - WPS, 0 - другая оболочка.
BYTE Krnl_Environment_ShellIsWPS( VOID )
{
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно скрыто - продолжаем перебор окон.
   if( !WinIsWindowVisible( Window ) ) continue;

   // Если это окно WPS - используется оболочка WPS.
   if( IsFolderWindow( Window ) )
    {
     // Завершаем перебор окон.
     WinEndEnumWindows( Enumeration );

     // Возврат.
     return 1;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return 0;
}

// ─── Узнает страну, которая установлена для окна ───

// Window - окно, Window_is_VIO - что это за окно.
ULONG Krnl_Environment_QueryCodePage( HWND Window, INT Window_is_VIO = -1 )
{
 // Узнаем, что это за окно, если требуется.
 if( Window_is_VIO == -1 )
  {
   if( IsVIOWindow( QueryFrameWindow( Window ) ) ) Window_is_VIO = 1;
   else Window_is_VIO = 0;
  }

 // Для текстовых окон возвращаем значение по умолчанию.
 if( Window_is_VIO ) return Environment_QuerySystemCodePage();

 // Возвращаем страну, которая установлена для окна.
 return WinQueryCp( WinQueryWindowULong( Window, QWL_HMQ ) );
}

// ─── Сообщает, вызвана ли заставка ───

BYTE Krnl_Environment_SystemIsLocked( VOID )
{
 // Проверяем, вызвана ли заставка.
 if( Krnl_Environment.RTSettings.System_is_locked ) return 1;

 // Возврат.
 return 0;
}

// ─── Сообщает окно заставки ───

HWND Krnl_Environment_LockupFrame( VOID )
{
 // Возвращаем окно заставки.
 return Krnl_Environment.RTSettings.Lockup_frame;
}

// ─── Сообщает, может ли заставка быть закрыта ───

BYTE Krnl_Environment_ScreenSaverCanBeClosed( VOID )
{
 // Проверяем, вызвана ли заставка.
 if( Krnl_Environment.RTSettings.Screen_Saver_can_be_closed ) return 1;

 // Возврат.
 return 0;
}

// ─── Находит окно "Startup.cmd" ───

BYTE Krnl_Environment_StartupCmdIsPresent( VOID )
{
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это не окно рамки - продолжаем перебор окон.
   if( !IsFrameWindow( Window ) ) continue;

   // Если это текстовое окно - проверяем его заголовок.
   if( IsVIOWindow( Window ) )
    {
     // Узнаем заголовок окна.
     CHAR Title[ SIZE_OF_TITLE ] = ""; WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Title );

     // Если в нем встречается слово "Startup":
     if( strifind( "Startup", Title ) )
      {
       // Завершаем перебор окон.
       WinEndEnumWindows( Enumeration );

       // Окно присутствует, возврат.
       return 1;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return 0;
}
