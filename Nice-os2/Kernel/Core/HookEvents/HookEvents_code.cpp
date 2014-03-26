
// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsShowing( PSMHSTRUCT Message )
{
 // �� ⮣�, ��� ���� ࠬ�� �⠭������ ������, ��� ����砥� ᮮ�饭�� �� �⮬.
 HWND Window = NULLHANDLE;

 if( Message->msg == WM_ADJUSTWINDOWPOS )
  {
   PSWP Window_placement = (PSWP) Message->mp1;

   if( Window_placement != NULL )
    if( Window_placement->fl == SWP_SHOW )
     if( !WinIsWindowVisible( Message->hwnd ) )
      Window = Message->hwnd;
  }

 // ��⥬, �᫨ �� �� ���� �������, ���� ࠡ�祩 ������ ����砥� ��஥ ᮮ�饭��.
 if( Message->msg == WM_SHOW )
  if( Message->mp1 == (MPARAM) 1 )
   Window = WinQueryWindow( Message->hwnd, QW_PARENT );

 // �஢��塞 ����.
 if( Window != NULLHANDLE )
  if( IsFrameWindow( Window ) )
   if( WinQueryWindow( Window, QW_PARENT ) == QueryDesktopWindow() )
    return 1;

 // ������.
 return 0;
}

// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsMoving( PSMHSTRUCT Message )
{
 // �᫨ ���� ᮮ�饭�� � ��६�饭�� ����:
 if( Message->msg == WM_MOVE )
  {
   // �᫨ ����, ���஬� ���� ᮮ�饭��, �� ���� ࠬ�� - ������.
   if( !IsFrameWindow( Message->hwnd ) ) return 0;

   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // �᫨ ᮮ�饭�� ���ࠢ����� ���� ࠬ�� ���孥�� �஢��:
   if( WinQueryWindow( Message->hwnd, QW_PARENT ) == Desktop )
    {
     // �஢��塞 �ᯮ������� 㪠��⥫� ���.
     BYTE Mouse_is_over_title = 0;

     // �᫨ ���� �� ������ ��� �����:
     if( MouseIsBusy() )
      {
       // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
       POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );
       HWND Window_under_pointer = WinWindowFromPoint( Desktop, &Pointer, 1 );

       // �᫨ 㪠��⥫� ��� �ᯮ����� ��� ��㣨� �����, ���ਬ��, ��� ����� WPS, �
       // ���� ࠬ��, ���஥ ����砥� ᮮ�饭�� WM_MOVE, ��।�������� ᠬ����⥫쭮.
       PID Process_ID_WRM = 0; WinQueryWindowProcess( Message->hwnd, &Process_ID_WRM, NULL );
       PID Process_ID_WUP = 0; WinQueryWindowProcess( Window_under_pointer, &Process_ID_WUP, NULL );
       if( Process_ID_WRM != Process_ID_WUP ) return 1;
      }
     // � �᫨ �� ���� ������ ��� �� �����:
     else
      {
       // ��⠥�, �� ���� ��।�������� ᠬ����⥫쭮.
       return 1;
      }
    }
  }

 // ������.
 return 0;
}

// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsActivating( PSMHSTRUCT Message )
{
 // �᫨ ���� �⠭������ ��࠭��:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 1 )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // �᫨ ��࠭�� �⠭������ ������ �� ����, � �� ���� �� ��� ���୨� ����:
   if( Frame_window == Message->hwnd )
    {
     // �᫨ � ���� ���� ���������:
     if( WinWindowFromID( Frame_window, FID_TITLEBAR ) != NULLHANDLE )
      {
       // �᫨ த�⥫�᪮� ���� - ࠡ�稩 �⮫:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // �� � ���浪�, ������.
         return 1;
        }
      }
    }
  }

 // ������.
 return 0;
}

// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_TopFrameWindowIsInactivating( PSMHSTRUCT Message )
{
 // �᫨ ���� ����⠥� ���� ��࠭��:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 0 )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // �᫨ ��࠭�� �⠭������ ������ �� ����, � �� ���� �� ��� ���୨� ����:
   if( Frame_window == Message->hwnd )
    {
     // �᫨ த�⥫�᪮� ���� - ࠡ�稩 �⮫:
     if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
      {
       // �� � ���浪�, ������.
       return 1;
      }
    }
  }

 // ������.
 return 0;
}

// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_FrameWindowIsActivating( PSMHSTRUCT Message )
{
 // �᫨ ���� �⠭������ ��࠭��:
 if( Message->msg == WM_ACTIVATE ) if( Message->mp1 == (MPARAM) 1 )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );

   // �᫨ ��࠭�� �⠭������ ������ �� ����, � �� ���� �� ��� ���୨� ����:
   if( Frame_window == Message->hwnd )
    {
     // �� � ���浪�, ������.
     return 1;
    }
  }

 // ������.
 return 0;
}

// ��� �஢���� ᮮ�饭��, ���ࠢ�塞�� ���� ���

// �� ��६���� - ���譨�. �����饭�� "1" �� ����砥�, �� Message->hwnd
// ���� ����� ࠬ��, ���⮬� ���� �㤥� �맢��� �� QueryFrameWindow().
BYTE HookEvents_FrameWindowIsClosing( PQMSG Message )
{
 // �஢��塞 ᮮ�饭��, ��।������� ����.
 if( ( Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_CLOSE ) ||
     ( Message->msg == WM_CLOSE ) ||
     ( Message->msg == WM_QUIT ) )
  return 1;

 // ������.
 return 0;
}
