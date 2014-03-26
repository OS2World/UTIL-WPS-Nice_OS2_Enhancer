
// ��� �஢����, ᮧ���� �� ���� �ਫ������� HOB XServer ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_IsHobWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strfind( "XWP", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ���� �����⮬ Java 1.1.x ���

// Window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsJavaWindow( HWND Window )
{
 // ������ ���, ��� ����� ��।����� ����.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // �஢��塞 ����.
 if( strfind( "awt", Window_name ) )
  if( strfind( "Class", Window_name ) ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ���� �ਫ������� �� Speed Pascal ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_IsSpeedPascalWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strfind( "Speed-Pascal", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ���� �ਫ������� �� WDSibyl ���

// Window - ���� �� ���� �ਫ������.
BYTE Krnl_Repository_IsSibylInnerWindow( HWND Window )
{
 // ������ ���, ��� ����� ��।����� ����.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // �஢��塞 ���.
 if( strfind( "Sibyl", Window_name ) ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ���� ���� ����� ������� ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_WindowIsDialog( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ �� �������� ��אַ㣮�쭨� - ��⠥�, �� ⠪��� ���� ���.
 if( Client_window != NULLHANDLE ) if( IsStaticWindow( Client_window ) ) Client_window = NULLHANDLE;

 // �᫨ ���� ࠡ�祩 ������ ���:
 if( Client_window == NULLHANDLE )
  {
   // �᫨ ���� ����� ࠬ�� ����ﭭ��� ࠧ��� - ��� ����� ���� ����� �������.
   if( FrameType( Frame_window ) == FT_CONST ) return 1;

   // �᫨ � ���� ����� ��४������� - ⮦�.
   if( WinQuerySwitchHandle( Frame_window, NULLHANDLE ) == NULLHANDLE ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ���� ���� ����� ������� �ਫ������ ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_WindowIsAppDialog( HWND Frame_window )
{
 // �᫨ ���� ����� ���� ����� �������:
 if( Krnl_Repository_WindowIsDialog( Frame_window ) )
  {
   // �᫨ ��� ����� ��������:
   HWND Owner_window = WinQueryWindow( Frame_window, QW_OWNER );

   if( Owner_window != NULLHANDLE ) if( Owner_window != QueryDesktopWindow() )
    if( Owner_window != QueryDesktopWindow() )
     {
      // �� ���� ������� �ਫ������, ������.
      return 1;
     }
  }

 // ������.
 return 0;
}

// ��� �஢����, ���� �� ���� �����ன 梥⮢ ��� ���⮢ ���

// Frame_window - ���� ��� �஢�ન.
BYTE Krnl_Repository_IsPaletteWindow( HWND Frame_window )
{
 // �᫨ ���� ᮧ���� �� �����窮� - ������.
 if( !Repository_IsWorkplaceShellWindow( Frame_window ) ) return 0;

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strcmp( Client_name, "PaletteClient" ) == EQUALLY ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ���� �� ���� ᯨ᪮� ������� �� ����� ���

// Frame_window - ���� ��� �஢�ન.
BYTE Krnl_Repository_IsJobCnrWindow( HWND Frame_window )
{
 // �᫨ ���� ᮧ���� �� �����窮� - ������.
 if( !Repository_IsWorkplaceShellWindow( Frame_window ) ) return 0;

 // ��ॡ�ࠥ� ����, �ᯮ������� � ���� ࠬ��.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

   // �஢��塞 ���.
   if( strcmp( Window_name, "JobCnr" ) == EQUALLY )
    {
     // �����蠥� ��ॡ�� ����.
     WinEndEnumWindows( Enumeration );

     // ������.
     return 1;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return 0;
}

// ��� �஢����, SmartBar �� ������ ���� ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsSmartBarWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strcmp( Client_name, "SMARTBAR_ClientWindow" ) == EQUALLY ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����७��� ����� Mozilla ���

// Window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsMozillaLiningWindow( HWND Window )
{
 // ������ ���, ��� ����� ��।����� ����.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // �஢��塞 ���.
 if( strcmp( Window_name, "MozillaWindowClass" ) == EQUALLY ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ࠬ�� Mozilla ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsMozillaFrameWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ���� - �஢��塞 ���.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsMozillaLiningWindow( Client_window );
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����७��� ����� Qt ���

// Window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsQtLiningWindow( HWND Window )
{
 // ������ ���, ��� ����� ��।����� ����.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // �஢��塞 ���.
 if( strcmp( Window_name, "QWindow" ) == EQUALLY ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ࠬ�� Qt ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_IsQtFrameWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ���� - �஢��塞 ���.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsQtLiningWindow( Client_window );
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����७��� ����� Odin ���

// Window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsOdinLiningWindow( HWND Window )
{
 // ������ ���, ��� ����� ��।����� ����.
 CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Window, SIZE_OF_NAME, Window_name );

 // �஢��塞 ���.
 if( strcmp( Window_name, "Win32WindowClass" ) == EQUALLY ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ࠬ�� Odin ���

// Frame_window - ���� ࠬ��.
BYTE Krnl_Repository_IsOdinFrameWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ���� - �஢��塞 ���.
 if( Client_window != NULLHANDLE ) 
  {
   return Krnl_Repository_IsOdinLiningWindow( Client_window );
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ࠬ�� EPM ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsEPMEditorWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strfind( "NewEditWndClass", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ��ᬮ�� ����� ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsVideoViewerWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strfind( "VIDEO2", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ������ ���� ���� ����� ��ᬮ�� ����� ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsVideoPlayerWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strfind( "diveView", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� ��室�� ���� ᯨ᪠ ���⮢ � ���� ������� ���

// Frame_window - ����, ���஥ ���� �஢����.
HWND Krnl_Repository_FindFontListField( HWND Frame_window )
{
 // ��ॡ�ࠥ� ���� � �������� ����.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ������㯭� - �த������ ��ॡ�� ����.
   if( !WindowIsPresent( Window ) ) continue;

   // �᫨ �� ���� ᯨ᪠:
   if( IsListBoxWindow( Window ) )
    {
     // �஢��塞, ���� �� � ��� ��ப� ��� ������� ࠧ��� ����.
     INT First_line = 0; INT Length = strlen( "## x ##" );
     WinSendMsg( Window, LM_QUERYITEMTEXT, MPFROM2SHORT( First_line, Length ), Krnl_Repository.RTSettings.Item_text );
     CHAR Text[ 25 ] = ""; strncpy( Text, Krnl_Repository.RTSettings.Item_text, Length );

     // �᫨ ��� ����:
     if( strfind( " x ", Text ) )
      {
       // �����蠥� ��ॡ�� ����.
       WinEndEnumWindows( Enumeration );

       // ���᮪ ������, ������.
       return Window;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return NULLHANDLE;
}

// ��� �஢����, ���� �� ���� �������� ��� ᬥ�� ���� � ⥪�⮢�� ���� ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsVIOFontMetricsDialog( HWND Frame_window )
{
 // �஢��塞 ����.
 if( Krnl_Repository_WindowIsDialog( Frame_window ) )
  if( IsPresentationManagerWindow( Frame_window ) )
   if( Krnl_Repository_FindFontListField( Frame_window ) != NULLHANDLE )
    return 1;

 // ������.
 return 0;
}

// ��� �஢����, LaunchPad �� ������ ���� ���

// Window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsLaunchPadWindow( HWND Window )
{
 // �᫨ ���� ᮧ���� �� �����窮� - ������.
 if( !Repository_IsWorkplaceShellWindow( Window ) ) return 0;

 // �᫨ ���� ���᪮� - �� LaunchPad.
 if( WinWindowFromID( Window, FID_CLIENT ) == NULLHANDLE )
  if( FrameType( Window ) == FT_FLAT )
   return 1;

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ������ ���� � ������� RZ API ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsRZApiWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ����.
   CHAR Client_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Client_name );

   // �஢��塞 ���.
   if( strcmp( Client_name, "RzFrW" ) == EQUALLY ) return 1;
   if( strifind( "RzSup_", Client_name ) ) return 1;
  }

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ���� �ਫ������� GoldED ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsGoldEdWindow( HWND Frame_window )
{
 // �᫨ �� ⥪�⮢�� ����:
 if( Repository_IsVIOWindow( Frame_window ) )
  {
   // ������ ��� �ਫ������, ᮧ���襣� ����.
   CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

   // �᫨ ��� 㤠���� ��।�����:
   if( Exe_name[ 0 ] != 0 )
    {
     // �஢��塞 ���.
     if( strlen( Exe_name ) > 6 )
      {
       Exe_name[ 3 ] = 0; if( stricmpe( Exe_name, "Ged" ) == EQUALLY ) return 1;
      }
    }
  }

 // ������.
 return 0;
}

// ��� �஢����, ᮧ���� �� ���� �ਫ������� HotJava ���

// Frame_window - ����, ���஥ ���� �஢����.
BYTE Krnl_Repository_IsHotJavaBrowserWindow( HWND Frame_window )
{
 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 if( Client_window != NULLHANDLE )
  {
   // �᫨ �� ���� Java:
   if( Krnl_Repository_IsJavaWindow( Client_window ) )
    {
     // ������ ��������� ����.
     CHAR Title[ SIZE_OF_TITLE ] = ""; GetDetectedWindowTitle( Frame_window, Title );

     // �஢��塞 ���.
     if( strifind( "HotJava", Title ) ) return 1;
    }
  }

 // ������.
 return 0;
}

// ��� ��室�� ��宦�� ����, �ᯮ���� ��⮤ ��� �ࠢ����� ���

// Frame_window - ���� �ਫ������, Method - ��⮤, ����� �㤥� ��뢠���� ��� �ࠢ�����.
HWND Krnl_Repository_FindRelatedFrameWindow( HWND Frame_window, PISAPPWINDOW Method )
{
 // ������ ��।� ᮮ�饭�� ����.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ���� ࠬ�� � ��� ���� �믮������ 㪠����� ��⮤:
   if( Window != Frame_window ) if( IsFrameWindow( Window ) ) if( Method( Window ) )
    {
     // ������ ��।� ᮮ�饭�� ����.
     HMQ Window_queue = WinQueryWindowULong( Window, QWL_HMQ );

     // �᫨ ��।� ᮢ������ - �����蠥� ��ॡ�� ����.
     if( Window_queue == Message_queue )
      {
       // �����蠥� ��ॡ�� ����
       WinEndEnumWindows( Enumeration );

       // ������.
       return Window;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return NULLHANDLE;
}

// ��� ������ ��� �ਭ�� �� 㬮�砭�� ���

// Name - ��ப� ��� �����.
VOID Krnl_Repository_QueryPrinterName( PCHAR Name )
{
 // ��� �ਭ�� ᮤ�ন��� � OS2.ini.
 CHAR Printer_name[ SIZE_OF_PATH ] = "";
 PrfQueryProfileString( HINI_USERPROFILE, "PM_SPOOLER", "QUEUE", "", Printer_name, SIZE_OF_PATH );

 // �᫨ ��� 㧭��� �� 㤠���� - ������.
 if( Printer_name[ 0 ] == 0 ) return;

 // �᫨ ��᫥���� �㪢� ����� �ਭ�� ";" - �⠢�� ����� ��� ����� ��ப�.
 INT End_of_string = strlen( Printer_name ) - 1;
 if( Printer_name[ End_of_string ] == ';' ) Printer_name[ End_of_string ] = 0;

 // ������ ��ப�.
 strcpy( Name, Krnl_Repository.Settings.Objects.Printer_prtname ); strcat( Name, Printer_name ); strcat( Name, ">" );

 // ������.
 return;
}

