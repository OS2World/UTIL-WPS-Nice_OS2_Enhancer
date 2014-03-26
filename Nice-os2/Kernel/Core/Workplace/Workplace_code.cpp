
// ��� �஢���� ᢮��⢠ ���� ���

// Frame_window - ���� ��� �஢�ન.
BYTE Workplace_HasShellWindowControls( HWND Frame_window )
{
 // ���� �����窨 ����� ⮫쪮 ���������, � ���� ��� ���⨭�� � ������.
 if( WinWindowFromID( Frame_window, FID_TITLEBAR ) == NULLHANDLE ) return 0;
 if( WinWindowFromID( Frame_window, FID_CLIENT ) == NULLHANDLE ) return 0;

 if( WinWindowFromID( Frame_window, FID_SYSMENU ) != NULLHANDLE ) return 0;
 if( WinWindowFromID( Frame_window, FID_MINMAX ) != NULLHANDLE ) return 0;

 // ������.
 return 1;
}

// ��� �஢���� �ᯮ������� ���� ���

// Frame_window - ���� ��� �஢�ન, Window_placement - �ᯮ������� ����.
BYTE Workplace_HasShellPlacement( HWND Frame_window, PSWP Window_placement )
{
 // ���� ������ ����� ᢮��⢠ ���� �����窨.
 if( !Workplace_HasShellWindowControls( Frame_window ) ) return 0;

 // ������ ࠧ��� �࠭�.
 INT X_Screen = WinQuerySysValue( QueryDesktopWindow(), SV_CXSCREEN );

 // ���� �����窨 ������ ���� �ᯮ������ �� �।����� �࠭�.
 INT Required_width = X_Screen + FrameWidth( Frame_window ) * 2;

 // �᫨ �� ⠪ - �����頥� 1.
 if( Window_placement->x <= 0 )
  if( Window_placement->x + Window_placement->cx >= X_Screen )
   if( Window_placement->cx == Required_width )
    return 1;

 // ���� �����頥� 0.
 return 0;
}

// ��� ������ ���� �����窨 ���

HWND Workplace_QueryShellWindow( VOID )
{
 // ���� �����窨.
 HWND Shell_window = NULLHANDLE;

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� �� ����:
   if( WinIsWindowVisible( Window ) )
    {
     // �᫨ �� ���� WPS:
     if( IsFolderWindow( Window ) )
      {
       // ������ �ᯮ������� ���� � ��� ���ﭨ�.
       SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

       // ���� �����窨 ������ ���� �ᯮ������ �� �।����� �࠭�.
       if( Workplace_HasShellPlacement( Window, &Window_placement ) )
        {
         // �᫨ ���� �����窨 �� �� ������� - ���������� ���.
         if( Shell_window == NULLHANDLE ) Shell_window = Window;
         // � �᫨ ��� �뫮 �������:
         else
          {
           // ���� �����窨 ����� ���� ⮫쪮 ����.
           Shell_window = NULLHANDLE;

           // �����蠥� ��ॡ�� ����.
           break;
          }
        }
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // �����頥� ���� �����窨.
 return Shell_window;
}

// ��� ������, � ����� ���ﭨ� ���� �����窨 ���

// �����頥��� ���祭��: 1 - ���� ����㯭�, 0 - ���� 㬥��襭�.
BYTE Workplace_ShellIsAvailable( VOID )
{
 // �஢��塞, �������� �� ���� �����窨.
 if( Workplace_QueryShellWindow() != NULLHANDLE ) return 1;
 else return 0;
}

// ��� �����頥� ���� �����窨, ��������� ࠭�� ���

HWND Workplace_GetDetectedShellWindow( VOID )
{
 // �᫨ ���� �����窨 ��� - 㧭��� ���.
 if( !WinIsWindow( WinQueryAnchorBlock( Workplace.RTSettings.Shell_window ), Workplace.RTSettings.Shell_window ) )
  Workplace.RTSettings.Shell_window = Workplace_QueryShellWindow();

 // �����頥� ���� �����窨.
 return Workplace.RTSettings.Shell_window;
}

// ��� ���������� ���� �����窨, �᫨ ��� ������� �� �믮������ �����-���� ����⢨� ���

VOID Workplace_RememberShellWindow( HWND Window )
{
 // ���������� ���� �����窨.
 Workplace.RTSettings.Shell_window = Window;

 // ������.
 return;
}
