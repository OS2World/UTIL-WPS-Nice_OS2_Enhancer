
// ��� �������� ���� ���

// Frame_window - ����, ���஥ ���� ��������.
VOID Repaint_UpdateWindow( HWND Frame_window )
{
 // ��������� ����, ������ � ⠪ ����� ������ ���� ����ᮢ���.
 // ����뢠�� ��譨� 䫠��� "FCF_*" � �⮬ ᮮ�饭�� ����� - ���� ࠬ�� ��祣� �� �㤥� ������.
 WinPostMsg( Frame_window, WM_UPDATEFRAME, MPFROMP( FCF_SYSMENU | FCF_TITLEBAR | FCF_MAXBUTTON | FCF_MINBUTTON | FCF_HIDEBUTTON | FCF_MENU ), 0 );

 // �� ���� ������ ���� ����ᮢ���.
 WinInvalidateRect( Frame_window, NULL, 1 );

 // ������.
 return;
}

// ��� �������� ࠬ�� ����, ������� �ࠢ����� �ਭ� ���

// Frame_window - ����, ���஥ ���� ��������.
VOID Repaint_UpdateFrameBorder( HWND Frame_window )
{
 // �᫨ ���� ����� ������ ࠬ��:
 if( FrameType( Frame_window ) == FT_NORMAL )
  {
   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // ������ �ਭ� ࠬ�� �� 㬮�砭��.
   INT Normal_frame = Min( WinQuerySysValue( Desktop, SV_CXSIZEBORDER ), WinQuerySysValue( Desktop, SV_CYSIZEBORDER ) );

   // ���뫠�� ᮮ�饭�� � ����.
   WinPostMsg( Frame_window, WM_SETBORDERSIZE, (MPARAM) Normal_frame, (MPARAM) Normal_frame );
  }

 // ������.
 return;
}

// ��� �������� �� ���� ���

// Parent_window - த�⥫�᪮� ���� ��� ���� ࠡ�祣� �⮫�.
// �� �६� ࠡ��� �������� ������ �맮�, �� �⮬ Recursive_calling != 0.
VOID Repaint_UpdateAllWindows( HWND Parent_window, BYTE Recursive_calling = 0 )
{
 // �᫨ ���� ���� ��������� - ���� ᤥ���� ����প�.
 BYTE Do_retard = 0;

 // ������ ���� �����窨.
 HWND Shell_window = GetDetectedShellWindow();

 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( Parent_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ���� �����窨 - �த������ ��ॡ�� ����.
   if( Window == Shell_window ) continue;

   // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
   if( !IsFrameWindow( Window ) ) continue;

   // �᫨ �� ���� ࠬ�� ᯨ᪠ ���� - ��� ᢮��⢠ ���� 㧭��� ��࠭��.
   if( IsWinListWindow( Window ) )
    {
     // ���뫠�� ᮮ�饭�� � ��⮪.
     WinPostQueueMsg( Enhancer.Modules.Diver->Message_queue, SM_QUERY_PROPERTIES, (MPARAM) Window, (MPARAM) WT_UNKNOWN );
    }

   // ������ ࠧ��� ࠬ�� ����.
   Repaint_UpdateFrameBorder( Window );

   // �᫨ ���� ���� - �த������ ��ॡ�� ����.
   if( !WinIsWindowVisible( Window ) ) continue;

   // ������塞 ����.
   Repaint_UpdateWindow( Window );

   // �᫨ �� �� ������ �맮�:
   if( !Recursive_calling )
    {
     // � ���� ࠡ�祩 ������ ����� ���� �ᯮ������ ��㣨� ���� ࠬ��. ��ॡ�ࠥ� �� ⮦�.
     HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
     if( Client_window != NULLHANDLE ) Repaint_UpdateAllWindows( Client_window, RECURSIVE_CALLING );

     // ���� �㤥� �믮����� ����প�.
     Do_retard = 1;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ���� �����஥ �६�, �᫨ �� �ॡ����.
 if( Do_retard ) Retard();

 // ������.
 return;
}
