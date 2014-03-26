// ��� ��⠭�������� ����-�������� ������ ��� ���� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID Curtain_ShowCurtainWindow( HWND Desktop )
{
 // �᫨ ���� �� ��������:
 if( !WinIsWindowVisible( Curtain.Curtain_window ) )
  {
   // ������ ࠧ��� �࠭�.
   INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
   INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

   // ��⠭�������� ����-�������� ������ ��� ����. ��� ����뢠�� �࠭, �� ��祣� �� ����.
   WinSetWindowPos( Curtain.Curtain_window, HWND_TOP, 0, 0, X_Screen, Y_Screen, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER | SWP_NOADJUST );
   WinShowWindow( Curtain.Curtain_window, 1 );

   // ��७��ࠢ�塞 ���� �� ���������� � �� ����.
   WinSetFocus( Desktop, Curtain.Curtain_window );
  }

 // ������.
 return;
}

// ��� ����� ����-��������, �᫨ ��� �뫮 ������ ���

// Activate_window_in_center - ���� ����� ���� � �।��� �࠭�.
VOID Curtain_HideCurtainWindow( BYTE Activate_window_in_center = 0 )
{
 // �᫨ ���� ������ - ���祬 ���.
 if( WinIsWindowVisible( Curtain.Curtain_window ) )
  {
   // ���祬 ����-��������.
   WinSetWindowPos( Curtain.Curtain_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER | SWP_NOADJUST );
   WinShowWindow( Curtain.Curtain_window, 0 );

   // ������ ��࠭�� ���� � �।��� �࠭�.
   if( Activate_window_in_center ) ActivateWindowInCenter();
  }

 // ������.
 return;
}

// ��� ����-������᪠, ���஥ ����뢠�� �࠭ � ��祣� �� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Curtain_WindowProc( HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter )
{
 // �᫨ ���� �⠭������ ������:
 if( Message == WM_SHOW ) if( First_parameter == (MPARAM) 1 )
  {
   // ����᪠�� ���稪 �६���.
   WinStartTimer( Enhancer.Application, Window, 1, Curtain.Constants.Curtain_present_time );

   // ������.
   return 0;
  }

 // �᫨ ���� �⠭������ �����:
 if( Message == WM_SHOW ) if( First_parameter == (MPARAM) 0 )
  {
   // ��⠭�������� ���稪 �६���.
   WinStopTimer( Enhancer.Application, Window, 1 );

   // ������.
   return 0;
  }

 // ����饭�� � ⮬, �� ���� ������ ���� ����ᮢ���:
 if( Message == WM_PAINT )
  {
   // ���� ��祣� �� ����.
   RECT Rectangle = {0}; 
   HPS Presentation_space = WinBeginPaint( Window, NULLHANDLE, &Rectangle );
   WinEndPaint( Presentation_space );

   // ������.
   return 0;
  }

 // ����饭�� �� ���稪� �६���:
 if( Message == WM_TIMER )
  {
   // ���祬 ����.
   Curtain_HideCurtainWindow();

   // ������.
   return 0;
  }

 // ����� ������ ���:
 if( Message == WM_BUTTON1DOWN || Message == WM_BUTTON1DBLCLK ||
     Message == WM_BUTTON2DOWN || Message == WM_BUTTON2DBLCLK ||
     Message == WM_BUTTON3DOWN || Message == WM_BUTTON3DBLCLK )
  {
   // ���祬 ����.
   Curtain_HideCurtainWindow();

   // ������.
   return 0;
  }

 // ��㣮� ᮮ�饭�� - �� ��ࠡ��뢠����.
 return WinDefWindowProc( Window, Message, First_parameter, Second_parameter );
}

// ��� ������� ����-�������� ���

VOID Curtain_CreateCurtain()
{
 // ��।��塞 ���� � ��⥬�.
 CHAR Curtain_class_name[] = "CurtainWndClass";

 WinRegisterClass( Enhancer.Application, Curtain_class_name, (PFNWP) Curtain_WindowProc, 0, 0 );

 // ������ ࠧ��� �࠭�.
 HWND Desktop = QueryDesktopWindow();

 // ������� ����.
 Curtain.Curtain_window = WinCreateWindow( Desktop, Curtain_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_BOTTOM, 0, NULL, NULL );
 WinShowWindow( Curtain.Curtain_window, 0 );

 // ������.
 return;
}

// ��� ����뢠�� ����-�������� ���

VOID Curtain_DestroyCurtain( VOID )
{
 // ����뢠�� ����.
 WinDestroyWindow( Curtain.Curtain_window ); Curtain.Curtain_window = NULLHANDLE;

 // ������.
 return;
}

