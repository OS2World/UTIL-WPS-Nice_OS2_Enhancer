
// ��� �஢����, ��⠭����� �� FileBar � ����⢥ �����窨 ���

BYTE Krnl_Environment_ShellIsFileBar( VOID )
{
 // FileBar ����� ���� �맢�� ��᫥ ����⥫�.
 if( Krnl_Environment.RTSettings.Shell_is_FileBar ) return 1;

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ���� - �த������ ��ॡ�� ����.
   if( !WinIsWindowVisible( Window ) ) continue;

   // �᫨ �� FileBar - ��⠥�, �� �� �ᯮ������ � ����⢥ �����窨.
   if( IsFileBarWindow( Window ) )
    {
     Krnl_Environment.RTSettings.Shell_is_FileBar = 1;
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return Krnl_Environment.RTSettings.Shell_is_FileBar;
}

// ��� ������, ��⠭������ �� �����窠 WPS ���

// �����頥��� ���祭��: 1 - WPS, 0 - ��㣠� �����窠.
BYTE Krnl_Environment_ShellIsWPS( VOID )
{
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ���� - �த������ ��ॡ�� ����.
   if( !WinIsWindowVisible( Window ) ) continue;

   // �᫨ �� ���� WPS - �ᯮ������ �����窠 WPS.
   if( IsFolderWindow( Window ) )
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

// ��� ������ ��࠭�, ����� ��⠭������ ��� ���� ���

// Window - ����, Window_is_VIO - �� �� �� ����.
ULONG Krnl_Environment_QueryCodePage( HWND Window, INT Window_is_VIO = -1 )
{
 // ������, �� �� �� ����, �᫨ �ॡ����.
 if( Window_is_VIO == -1 )
  {
   if( IsVIOWindow( QueryFrameWindow( Window ) ) ) Window_is_VIO = 1;
   else Window_is_VIO = 0;
  }

 // ��� ⥪�⮢�� ���� �����頥� ���祭�� �� 㬮�砭��.
 if( Window_is_VIO ) return Environment_QuerySystemCodePage();

 // �����頥� ��࠭�, ����� ��⠭������ ��� ����.
 return WinQueryCp( WinQueryWindowULong( Window, QWL_HMQ ) );
}

// ��� ����頥�, �맢��� �� ���⠢�� ���

BYTE Krnl_Environment_SystemIsLocked( VOID )
{
 // �஢��塞, �맢��� �� ���⠢��.
 if( Krnl_Environment.RTSettings.System_is_locked ) return 1;

 // ������.
 return 0;
}

// ��� ����頥� ���� ���⠢�� ���

HWND Krnl_Environment_LockupFrame( VOID )
{
 // �����頥� ���� ���⠢��.
 return Krnl_Environment.RTSettings.Lockup_frame;
}

// ��� ����頥�, ����� �� ���⠢�� ���� ������ ���

BYTE Krnl_Environment_ScreenSaverCanBeClosed( VOID )
{
 // �஢��塞, �맢��� �� ���⠢��.
 if( Krnl_Environment.RTSettings.Screen_Saver_can_be_closed ) return 1;

 // ������.
 return 0;
}

// ��� ��室�� ���� "Startup.cmd" ���

BYTE Krnl_Environment_StartupCmdIsPresent( VOID )
{
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
   if( !IsFrameWindow( Window ) ) continue;

   // �᫨ �� ⥪�⮢�� ���� - �஢��塞 ��� ���������.
   if( IsVIOWindow( Window ) )
    {
     // ������ ��������� ����.
     CHAR Title[ SIZE_OF_TITLE ] = ""; WinQueryWindowText( WinWindowFromID( Window, FID_TITLEBAR ), SIZE_OF_TITLE, Title );

     // �᫨ � ��� ����砥��� ᫮�� "Startup":
     if( strifind( "Startup", Title ) )
      {
       // �����蠥� ��ॡ�� ����.
       WinEndEnumWindows( Enumeration );

       // ���� ���������, ������.
       return 1;
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return 0;
}
