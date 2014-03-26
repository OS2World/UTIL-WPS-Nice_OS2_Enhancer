
// ─── Проверяет, создано ли окно приложением HOB XServer ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_IsHobWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strfind( "XWP", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли окно апплетом Java 1.1.x ───

// Window - окно, которое надо проверить.
BYTE Krnl_Repository_IsJavaWindow( HWND Window )
{
 // Узнаем имя, под которым определено окно.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // Проверяем окно.
 if( strfind( "awt", Window_name ) )
  if( strfind( "Class", Window_name ) ) return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли окно приложением на Speed Pascal ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_IsSpeedPascalWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strfind( "Speed-Pascal", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли окно приложением на WDSibyl ───

// Window - одно из окон приложения.
BYTE Krnl_Repository_IsSibylInnerWindow( HWND Window )
{
 // Узнаем имя, под которым определено окно.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // Проверяем его.
 if( strfind( "Sibyl", Window_name ) ) return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли окно быть окном диалога ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_WindowIsDialog( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если это невидимый прямоугольник - считаем, что такого окна нет.
 if( Client_window != NULLHANDLE ) if( IsStaticWindow( Client_window ) ) Client_window = NULLHANDLE;

 // Если окна рабочей области нет:
 if( Client_window == NULLHANDLE )
  {
   // Если окно имеет рамку постоянного размера - оно может быть окном диалога.
   if( FrameType( Frame_window ) == FT_CONST ) return 1;

   // Если в окно нельзя переключиться - тоже.
   if( WinQuerySwitchHandle( Frame_window, NULLHANDLE ) == NULLHANDLE ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли окно быть окном диалога приложения ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_WindowIsAppDialog( HWND Frame_window )
{
 // Если окно может быть окном диалога:
 if( Krnl_Repository_WindowIsDialog( Frame_window ) )
  {
   // Если оно имеет владельца:
   HWND Owner_window = WinQueryWindow( Frame_window, QW_OWNER );

   if( Owner_window != NULLHANDLE ) if( Owner_window != QueryDesktopWindow() )
    if( Owner_window != QueryDesktopWindow() )
     {
      // Это окно диалога приложения, возврат.
      return 1;
     }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, является ли окно палитрой цветов или шрифтов ───

// Frame_window - окно для проверки.
BYTE Krnl_Repository_IsPaletteWindow( HWND Frame_window )
{
 // Если окно создано не оболочкой - возврат.
 if( !Repository_IsWorkplaceShellWindow( Frame_window ) ) return 0;

 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strcmp( Client_name, "PaletteClient" ) == EQUALLY ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, является ли окно списком заданий на печать ───

// Frame_window - окно для проверки.
BYTE Krnl_Repository_IsJobCnrWindow( HWND Frame_window )
{
 // Если окно создано не оболочкой - возврат.
 if( !Repository_IsWorkplaceShellWindow( Frame_window ) ) return 0;

 // Перебираем окна, расположенные в окне рамки.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

   // Проверяем его.
   if( strcmp( Window_name, "JobCnr" ) == EQUALLY )
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

// ─── Проверяет, SmartBar ли данное окно ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsSmartBarWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strcmp( Client_name, "SMARTBAR_ClientWindow" ) == EQUALLY ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть внутренним окном Mozilla ───

// Window - окно, которое надо проверить.
BYTE Krnl_Repository_IsMozillaLiningWindow( HWND Window )
{
 // Узнаем имя, под которым определено окно.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // Проверяем его.
 if( strcmp( Window_name, "MozillaWindowClass" ) == EQUALLY ) return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном рамки Mozilla ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsMozillaFrameWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть - проверяем его.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsMozillaLiningWindow( Client_window );
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть внутренним окном Qt ───

// Window - окно, которое надо проверить.
BYTE Krnl_Repository_IsQtLiningWindow( HWND Window )
{
 // Узнаем имя, под которым определено окно.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // Проверяем его.
 if( strcmp( Window_name, "QWindow" ) == EQUALLY ) return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном рамки Qt ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_IsQtFrameWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть - проверяем его.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsQtLiningWindow( Client_window );
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть внутренним окном Odin ───

// Window - окно, которое надо проверить.
BYTE Krnl_Repository_IsOdinLiningWindow( HWND Window )
{
 // Узнаем имя, под которым определено окно.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // Проверяем его.
 if( strcmp( Window_name, "Win32WindowClass" ) == EQUALLY ) return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном рамки Odin ───

// Frame_window - окно рамки.
BYTE Krnl_Repository_IsOdinFrameWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть - проверяем его.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsOdinLiningWindow( Client_window );
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном рамки EPM ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsEPMEditorWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strfind( "NewEditWndClass", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном просмотра видео ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsVideoViewerWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strfind( "VIDEO2", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, может ли данное окно быть окном просмотра видео ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsVideoPlayerWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strfind( "diveView", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Находит окно списка шрифтов в окне диалога ───

// Frame_window - окно, которое надо проверить.
HWND Krnl_Repository_FindFontListField( HWND Frame_window )
{
 // Перебираем окна в заданном окне.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно недоступно - продолжаем перебор окон.
   if( !WindowIsPresent( Window ) ) continue;

   // Если это окно списка:
   if( IsListBoxWindow( Window ) )
    {
     // Проверяем, есть ли в нем строки для задания размера шрифта.
     INT First_line = 0; INT Length = strlen( "## x ##" );
     WinSendMsg( Window, LM_QUERYITEMTEXT, MPFROM2SHORT( First_line, Length ), Krnl_Repository.RTSettings.Item_text );
     CHAR Text[ 25 ] = ""; strncpy( Text, Krnl_Repository.RTSettings.Item_text, Length );

     // Если они есть:
     if( strfind( " x ", Text ) )
      {
       // Завершаем перебор окон.
       WinEndEnumWindows( Enumeration );

       // Список найден, возврат.
       return Window;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return NULLHANDLE;
}

// ─── Проверяет, является ли окно диалогом для смены шрифта в текстовом окне ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsVIOFontMetricsDialog( HWND Frame_window )
{
 // Проверяем окно.
 if( Krnl_Repository_WindowIsDialog( Frame_window ) )
  if( IsPresentationManagerWindow( Frame_window ) )
   if( Krnl_Repository_FindFontListField( Frame_window ) != NULLHANDLE )
    return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, LaunchPad ли данное окно ───

// Window - окно, которое надо проверить.
BYTE Krnl_Repository_IsLaunchPadWindow( HWND Window )
{
 // Если окно создано не оболочкой - возврат.
 if( !Repository_IsWorkplaceShellWindow( Window ) ) return 0;

 // Если окно плоское - это LaunchPad.
 if( WinWindowFromID( Window, FID_CLIENT ) == NULLHANDLE )
  if( FrameType( Window ) == FT_FLAT )
   return 1;

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли данное окно с помощью RZ API ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsRZApiWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // Проверяем его.
   if( strcmp( Client_name, "RzFrW" ) == EQUALLY ) return 1;
   if( strifind( "RzSup_", Client_name ) ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли окно приложением GoldED ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsGoldEdWindow( HWND Frame_window )
{
 // Если это текстовое окно:
 if( Repository_IsVIOWindow( Frame_window ) )
  {
   // Узнаем имя приложения, создавшего окно.
   CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

   // Если его удалось определить:
   if( Exe_name[ 0 ] != 0 )
    {
     // Проверяем имя.
     if( strlen( Exe_name ) > 6 )
      {
       Exe_name[ 3 ] = 0; if( stricmpe( Exe_name, "Ged" ) == EQUALLY ) return 1;
      }
    }
  }

 // Возврат.
 return 0;
}

// ─── Проверяет, создано ли окно приложением HotJava ───

// Frame_window - окно, которое надо проверить.
BYTE Krnl_Repository_IsHotJavaBrowserWindow( HWND Frame_window )
{
 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // Если это окно Java:
   if( Krnl_Repository_IsJavaWindow( Client_window ) )
    {
     // Узнаем заголовок окна.
     CHAR Title[ SIZE_OF_TITLE ] = ""; GetDetectedWindowTitle( Frame_window, Title );

     // Проверяем его.
     if( strifind( "HotJava", Title ) ) return 1;
    }
  }

 // Возврат.
 return 0;
}

// ─── Находит похожее окно, используя метод для сравнения ───

// Frame_window - окно приложения, Method - метод, который будет вызываться для сравнения.
HWND Krnl_Repository_FindRelatedFrameWindow( HWND Frame_window, PISAPPWINDOW Method )
{
 // Узнаем очередь сообщений окна.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если это окно рамки и для него выполняется указанный метод:
   if( Window != Frame_window ) if( IsFrameWindow( Window ) ) if( Method( Window ) )
    {
     // Узнаем очередь сообщений окна.
     HMQ Window_queue = WinQueryWindowULong( Window, QWL_HMQ );

     // Если очереди совпадают - завершаем перебор окон.
     if( Window_queue == Message_queue )
      {
       // Завершаем перебор окон
       WinEndEnumWindows( Enumeration );

       // Возврат.
       return Window;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return NULLHANDLE;
}

// ─── Узнает имя принтера по умолчанию ───

// Name - строка для имени.
VOID Krnl_Repository_QueryPrinterName( PCHAR Name )
{
 // Имя принтера содержится в OS2.ini.
 CHAR Printer_name[ SIZE_OF_PATH ] = "";
 PrfQueryProfileString( HINI_USERPROFILE, "PM_SPOOLER", "QUEUE", "", Printer_name, SIZE_OF_PATH );

 // Если имя узнать не удалось - возврат.
 if( Printer_name[ 0 ] == 0 ) return;

 // Если последняя буква имени принтера ";" - ставим вместо нее конец строки.
 INT End_of_string = strlen( Printer_name ) - 1;
 if( Printer_name[ End_of_string ] == ';' ) Printer_name[ End_of_string ] = 0;

 // Задаем строку.
 strcpy( Name, Krnl_Repository.Settings.Objects.Printer_prtname ); strcat( Name, Printer_name ); strcat( Name, ">" );

 // Возврат.
 return;
}

