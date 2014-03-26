
// ��� �஢����, ����� �� ������ ��� �� ���窥 ᯨ᪠ ���� � WarpCenter ���

// Message - ᮮ�饭��, ���஥ ��।����� ����.
BYTE Patcher_WinListMenuIsPressed( PQMSG Message )
{
 // ������ ࠧ���� ����.
 RECT Rectangle = {0}; WinQueryWindowRect( Message->hwnd, &Rectangle );

 // ������ �ᯮ������� ���窠 ��� ᯨ᪠ ����.
 INT X_Left = 0; INT X_Right = 0;
 if( Rectangle.yTop == Patcher.Constants.Big_WarpCenter ) { X_Left = Patcher.Constants.Big_WarpCenter_X1; X_Right = Patcher.Constants.Big_WarpCenter_X2; }
 else { X_Left = Patcher.Constants.Small_WarpCenter_X1; X_Right = Patcher.Constants.Small_WarpCenter_X2; }

 // �᫨ ������ ��� �⦠� �� ���窥 ᯨ᪠ ���� - �����頥� 1.
 POINT Mouse_point = { SHORT1FROMMP( Message->mp1 ), SHORT2FROMMP( Message->mp1 ) };
 if( Mouse_point.x >= X_Left && Mouse_point.x <= X_Right ) return 1;

 // ������.
 return 0;
}

// ��� ��⠭�������� ���⠢�� �� ����⨨ ⮫쪮 ��� ���� WPS ���

// Window - ����, ���஥ ���� �஢����.
VOID Patcher_ChangeAnimation( HWND Window )
{
 // ������ ᢮��⢠ ����.
 ULONG Window_style = WinQueryWindowULong( Window, QWL_STYLE );

 // �᫨ ���⠢�� �⪫�祭� - ������.
 if( !( Window_style & WS_ANIMATE ) ) return;

 // �஢��塞 ���� - �� ������ ���� ���� ࠬ�� ��� ���� WPS.
 BYTE Window_is_frame = 0;  if( IsFrameWindow( Window ) ) Window_is_frame = 1;
 BYTE Window_is_folder = 0; if( IsFolderWindow( Window ) ) Window_is_folder = 1;

 // �᫨ �� �� ���� ࠬ�� - ������.
 if( !Window_is_frame ) if( !Window_is_folder ) return;

 // ����⥫�᪮� ���� ������ ���� ����� ࠡ�祣� �⮫�.
 if( WinQueryWindow( Window, QW_PARENT ) != QueryDesktopWindow() ) return;

 // ��� �������� ���� ���⠢�� �� ����⨨ �⪫���� �� ����.
 if( Window_is_frame )
  {
   if( IsJobCnrWindow( Window ) ) Window_is_folder = 1;
  }

 // �᫨ �� �� ���� WPS � ���⠢�� ������ ���� �������� - �⪫�砥� ��.
 if( !Window_is_folder ) if( Window_style & WS_ANIMATE )
  {
   // �⪫�砥� ���⠢��.
   Window_style = Window_style & ~WS_ANIMATE;

   // ��⠭�������� ᢮��⢠ ࠬ�� ����.
   WinSetWindowULong( Window, QWL_STYLE, Window_style );
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PatcherInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ����⠭�������� ���� ��। �����⨥�.
 if( Patcher.Settings.Restore_windows_before_closing )
  {
   // �᫨ ���� ����뢠����:
   if( FrameWindowIsClosing( Message ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ �� �� ���� ������� � � ���� ����� ��४������� �� ᯨ᪠ ����:
     if( !WindowIsAppDialog( Frame_window ) ) if( WindowIsTouchable( Frame_window ) )
      {
       // �᫨ த�⥫�᪮� ���� - ࠡ�稩 �⮫:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // ������ �ᯮ������� ���� � ��� ���ﭨ�.
         SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

         // ����ਬ, ���� �� �����뢠�� ����.
         BYTE Restore_window = 0;

         // �᫨ ���� 㬥��襭� � ���箪 - ���� ����⠭����� ���.
         if( Window_state.fl & SWP_MINIMIZE ) Restore_window = 1;

         // �᫨ ���� ���� � �� ��ࢮ� ᮮ�饭�� � �����⨨ - ���� ����⠭����� ���.
         if( Window_state.fl & SWP_HIDE )
          {
           // �஢��塞 ���ﭨ� ����.
           BYTE Close_message_is_received = 0; FindProperty( Frame_window, PRP_CLOSE_RECEIVED, &Close_message_is_received );
           if( !Close_message_is_received ) Restore_window = 1;
          }

         // �᫨ ���� ����⠭����� ����:
         if( Restore_window )
          {
           // ������ ���� ������.
           WinShowWindow( Frame_window, 1 );

           // ���ࠢ�塞 � ���� ᮮ�饭�� � ⮬, �� ��� ������ ���� ����⠭������.
           WinSendMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_RESTORE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
          }

         // ����������, �� ���� ����砥� ᮮ�饭�� � �����⨨.
         BYTE Close_message_is_received = 1; SetProperty( Frame_window, PRP_CLOSE_RECEIVED, &Close_message_is_received );
        }
      }
    }
  }


 // ��뢠�� � WarpCenter ����� ᯨ᮪ ����.
 if( Patcher.Settings.Patch_WarpCenter )
  {
   // �᫨ ������ ��� ����� �� WarpCenter - ���������� ��.
   if( Message->msg == WM_BUTTON1DOWN )
    if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
     Patcher.RTSettings.WinListMenu_is_pressed = 1;

   // �᫨ 㪠��⥫� ��� ��६�饭 � ��㣮� ���� - WarpCenter �� �����.
   if( Patcher.RTSettings.WinListMenu_is_pressed )
    if( Message->msg >= WM_MOUSEFIRST && Message->msg <= WM_MOUSELAST )
     if( !IsWarpCenterWindow( Message->hwnd ) ) Patcher.RTSettings.WinListMenu_is_pressed = 0;

   // �᫨ ������ ��� �⦠� �� WarpCenter:
   if( Patcher.RTSettings.WinListMenu_is_pressed )
    if( Message->msg == WM_BUTTON1UP )
     if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
      {
       // WarpCenter �� �����.
       Patcher.RTSettings.WinListMenu_is_pressed = 0;

       // �믮��塞 ����⢨�. ���뫠�� ᮮ�饭�� � ��⮪.
       WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_SHOW_WINDOW_LIST, 0, 0 );

       // �����塞 ᮮ�饭�� ⠪, ��� ��� ������ ��� �⦠� � ��㣮� �窥.
       Message->mp1 = MPFROM2SHORT( -1, -1 );
      }

   // �᫨ �믮����� ������� ����⨥ - ��� ᮮ�饭��.
   if( Message->msg == WM_BUTTON1DBLCLK )
    if( IsWarpCenterWindow( Message->hwnd ) ) if( Patcher_WinListMenuIsPressed( Message ) )
     *Discarding = 1;
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PatcherSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // ��⠭�������� ���⠢�� �� ����⨨ ⮫쪮 ��� ���� WPS.
 // ��� �⮣� ���� ��ࠡ��뢠�� ��� ᮮ�饭��, � ⮫쪮 ⠪�� ��ࠧ��.
 if( Patcher.Settings.Limited_animation )
  if( Message->msg == WM_MOVE ||
    ( Message->msg == WM_ACTIVATE && Message->mp1 == (MPARAM) 1 ) )
   {
    // �⪫�砥� ���⠢��.
    Patcher_ChangeAnimation( Message->hwnd );
   }

 // ������.
 return;
}
