
// ��� ���뢠�� ���� �ਫ������, �᫨ ��� ᮮ⢥����� ����⢨� ���

BYTE Launcher_CheckActiveWindowAndHideApplication( INT Action )
{
 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ������ ����, ���஥ ᥩ�� ��࠭�.
 HWND Active_window = WinQueryActiveWindow( Desktop );

 // �᫨ �� ���� ࠬ�� � ��� ������:
 if( Active_window != NULLHANDLE )
  if( IsFrameWindow( Active_window ) )
   if( WinIsWindowVisible( Active_window ) )
    {
     // �᫨ �� � ���� � ����, ���஥ ���� ����:
     if( CommandForWindowIs( Action, Active_window ) )
      {
       // ���뢠�� ��� � �����頥� ���㫥��� ���祭��.
       if( HideWindowAway( Active_window ) ) return 1;
      }
    }

 // ������.
 return 0;
}

// ��� ��뢠�� ���� �ਫ������, ���஥ ᮮ⢥����� ����⢨� ���

// Action - ����⢨�, ���஥ ���� �믮�����.
BYTE Launcher_FindAndShowApplication( INT Action )
{
 // ��室�� � ᯨ᪥ �ਫ������, ᯮᮡ�� �⪫�������� �� ��� �������, � �஡㥬 �맢��� ��.
 INT Position = 0;

 while( 1 )
  {
   // �஡㥬 ���� ��ࢮ� ��� ᫥���饥 �ਫ������.
   Position = FindApplicationInRepository( 0, Action, Position + 1 );

   // �᫨ ��祣� �� ������� - ������.
   if( Position == -1 ) return 0;

   // �஡㥬 �맢��� ���� �⮣� �ਫ������ ��� ����, ᯮᮡ��� �⪫�������� �� ⠪�� �� �������.
   BYTE Success = 0; INT How_much_found = 0; HWND Window_with_menu = NULLHANDLE;

   // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
   HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ��.
     if( !IsFrameWindow( Window ) ) continue;

     // �᫨ ���� �� ��������� � ᯨ᪥ ���� - �த������ ��ॡ��.
     // �� �஢�ઠ ����室���, ⠪ ��� �⥢� ����ॢ�⥫� Mozilla �
     // Opera ᮧ���� ⠪�� ����, � ���� ��祬-� Switch_handle ��� ���.
     if( !WindowIsTouchable( Window ) )
      if( !WindowIsUsedTo( DO_IMPROVE_WORKPLACE, Window ) )
       continue;

     // ����ਬ, ᮮ⢥����� �� ���� ������� �᫮���.
     BYTE Show_window = 0;

     // �᫨ ���� ����� �⪫�������� �� �������� ������� - ���� �맢��� ���.
     if( CommandForWindowIs( Action, Window ) ) Show_window = 1;

     // �᫨ ���� ᮧ���� �⨬ �ਫ������� - ���� �맢��� ���.
     if( WindowIsCreatedBy( Repository.Items[ Position ].Application, Window ) ) Show_window = 1;

     // �᫨ ��� �ਫ������ �뫨 ������ ���祢� ᫮�� � ��� ���� � ��������� ���� - ⮦�.
     if( Repository.Items[ Position ].Window_keyword_1[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_2[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_3[ 0 ] != 0 ||
         Repository.Items[ Position ].Window_keyword_4[ 0 ] != 0 )
      {
       // ������ ��������� ���� ��� �롨ࠥ� ��� �� ᯨ᪠ ᢮���.
       CHAR Title[ SIZE_OF_TITLE ] = ""; GetDetectedWindowTitle( Window, Title );

       // �஢��塞 ���.
       if( Repository.Items[ Position ].Window_keyword_1[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_1, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_2[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_2, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_3[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_3, Title ) )
         Show_window = 1;

       if( Repository.Items[ Position ].Window_keyword_4[ 0 ] != 0 )
        if( strifind( Repository.Items[ Position ].Window_keyword_4, Title ) )
         Show_window = 1;
      }

     // �᫨ �� ����, ���஥ ���� �맢���:
     if( Show_window )
      {
       // ��⠭�������� �ਫ������ ��訩 �ਮ���.
       SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS, Window );

       // ������ ���ﭨ� ���� ࠬ��.
       SWP Window_state = {0}; WinQueryWindowPos( Window, &Window_state );

       // �᫨ ���� 㬥��襭� ��� ���� - ����⠭�������� ���.
       if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE )
        {
         // ������, �뫮 �� ���� 㢥��祭�.
         BYTE Maximized = 0; FindProperty( Window, PRP_MAXIMIZED, &Maximized );

         // ���뫠�� ᮮ�饭�� � ����.
         if( !Maximized ) PerformAction( Window, RESTORE_ACTION );
         else PerformAction( Window, MAXIMIZE_ACTION );
        }

       // �᫨ ���� �뫮 �࠭� ������ - ����⠭�������� ���.
       if( Window == RolledWindow() ) UnrollWindow( RolledWindow() );

       // ��뢠�� ���� � ������ ��� ��࠭��.
       MoveWindowAbove( Window );

       // �᫨ � ���� ���� ���������, ���� � ࠡ��� ������� - ���������� ���.
       if( WinWindowFromID( Window, FID_TITLEBAR ) != NULLHANDLE )
        if( WinWindowFromID( Window, FID_MENU ) != NULLHANDLE )
         if( WinWindowFromID( Window, FID_CLIENT ) != NULLHANDLE )
          Window_with_menu = Window;

       // ����������, �� ���� �맢���. ���� ����� ���� ��᪮�쪮, ���⮬� �த������ ��ॡ��.
       Success = 1; How_much_found ++;
      }
    }
   WinEndEnumWindows( Enumeration );

   // �᫨ �뫮 ������� ��᪮�쪮 ���� - ��뢠�� ������ ��᫥���� �� ���, � ���ண� ���� ����.
   if( Success && How_much_found > 1 && Window_with_menu != NULLHANDLE )
    if( !WindowIsActive( Window_with_menu ) ) MoveWindowAbove( Window_with_menu );

   // �᫨ ���� ��� ��᪮�쪮 ���� �뫨 �맢��� - ������.
   if( Success ) return 1;

   // �᫨ �ᯮ������ �����窠 WPS:
   if( ShellIsWPS() )
    {
     // �஡㥬 �맢��� ���箪 �� ࠡ�祬 �⮫�, �᫨ �� �� ����� ��࠭��.
     for( INT Count = 0; Count < 4; Count ++ )
      {
       // ������ ���箪 �� ࠡ�祬 �⮫�.
       PCHAR Object_name = NULL;

       if( Count == 0 ) Object_name = Repository.Items[ Position ].WPS_name_1;
       if( Count == 1 ) Object_name = Repository.Items[ Position ].WPS_name_2;
       if( Count == 2 ) Object_name = Repository.Items[ Position ].WPS_name_3;
       if( Count == 3 ) Object_name = Repository.Items[ Position ].WPS_name_4;

       // �᫨ ���箪 ���� - ��뢠�� ���.
       if( Object_name[ 0 ] != 0 )
        {
         HOBJECT Object = QueryWPSObject( Object_name );

         if( Object != NULLHANDLE ) Success = WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
        }

       // �᫨ ���箪 �� �맢�� - ������.
       if( Success ) return 1;
      }

     // �஡㥬 �맢��� ���箪 �� ࠡ�祬 �⮫�, �᫨ �� �� ������ � ����ᥭ � ᯨ᮪.
     if( Repository.Items[ Position ].Object[ 0 ] != 0 )
      {
       // ��뢠�� ���箪.
       HOBJECT Object = QueryWPSObject( Repository.Items[ Position ].Object );

       if( Object != NULLHANDLE ) Success = WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );

       // �᫨ ���箪 �� �맢�� - ������.
       if( Success ) return 1;
      }
    }

   // �᫨ �����⥭ ����:
   if( Repository.Items[ Position ].Path[ 0 ] != 0 )
    {
     // �஡㥬 �맢��� �ਫ������.
     for( INT Count = 0; Count < 4; Count ++ )
      {
       // ������ ���� � �ਫ������.
       PCHAR Exe_name = NULL;

       if( Count == 0 ) Exe_name = Repository.Items[ Position ].Exe_name_1;
       if( Count == 1 ) Exe_name = Repository.Items[ Position ].Exe_name_2;
       if( Count == 2 ) Exe_name = Repository.Items[ Position ].Exe_name_3;
       if( Count == 3 ) Exe_name = Repository.Items[ Position ].Exe_name_4;

       // ��뢠�� �ਫ������.
       if( Exe_name[ 0 ] != 0 )
        {
         // ������ ���� � �ਫ������.
         CHAR Path[ SIZE_OF_PATH ] = "";
         strcpy( Path, Repository.Items[ Position ].Path );
         strcat( Path, "\\" );
         strcat( Path, Exe_name );

         // �᫨ ��� �ਫ������ ����� 䠩� *.cmd - ��뢠�� ���.
         CHAR Cmd_path[ SIZE_OF_PATH ] = ""; strcpy( Cmd_path, Path );

         PCHAR Extension = strifind( ".exe", Cmd_path );

         if( Extension != NULL )
          {
           *( Extension + 1 ) = 'c';
           *( Extension + 2 ) = 'm';
           *( Extension + 3 ) = 'd';
          }

         if( FileExists( Cmd_path ) ) strcpy( Path, Cmd_path );

         // �᫨ �ᯮ������ �����窠 WPS - ��뢠�� ���箪.
         if( ShellIsWPS() )
          {
           Success = WinOpenObject( QueryWPSObject( Path ), OPEN_DEFAULT, SHOW_EXISTING );
          }
         // ���� - ��뢠�� �ਫ������.
         else
          {
           Success = Execute( Path );
          }
        }

       // �᫨ �ਫ������ �뫮 �맢��� - ������.
       if( Success ) return 1;
      }
    }
  }

 // ������.
 return 0;
}

// ��� ��뢠�� WarpCenter, eCenter ��� SysTray ���

// Toolbar - �� ���� ��������.
VOID Launcher_ShowShellToolbarMenu( LONG Toolbar )
{
 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ���� ���� �����窨:
   if( ( Toolbar == FIND_WARPCENTER && IsWarpCenterWindow( Window ) ) ||
       ( Toolbar == FIND_SYSTRAY && IsSysTrayWindow( Window ) ) ||
       ( Toolbar == FIND_ECENTER && IsECenterWindow( Window ) ) )
    {
     // �᫨ ���� ���� - �����뢠�� ���.
     if( !WinIsWindowVisible( Window ) ) WinShowWindow( Window, 1 );

     // ��뢠�� ���� � ������ ��� ��࠭��.
     WinSetActiveWindow( Desktop, Window );

     // ������ �ᯮ������� ����.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // ������ ����, ���஥ �ᯮ������ � ����� ������ 㣫� �⮣� ����.
     // �᫨ ����७���� ���� ���, �㤥� �����饭� �� ����.
     INT X_Point = 15; INT Y_Point = 15;

     POINT Desktop_point = { Window_placement.x + X_Point, Window_placement.y + Window_placement.cy - Y_Point };
     HWND Inner_window = WinWindowFromPoint( Desktop, &Desktop_point, 1 );

     // ���뫠�� ����७���� ���� ᮮ�饭�� � ����⨨ ������ ���.
     WinPostMsg( Inner_window, WM_BUTTON1DOWN, MRFROM2SHORT( X_Point, Y_Point ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );
     WinPostMsg( Inner_window, WM_BUTTON1UP, MRFROM2SHORT( X_Point, Y_Point ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );

     // �����蠥� ��ॡ�� ����.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ����� ���� WarpCenter, ECenter ��� SysTray ���

VOID Launcher_HideShellToolbarMenu( BYTE Activate_window_in_center = 0 )
{
 // ���� ����������, �믮����� �� ����⢨�.
 BYTE Action_is_performed = 0;
 BYTE Post_queue_message = 0;
 BYTE Frame_window = NULLHANDLE;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �஢��塞 ����.
   LONG Found = 0;

   if( IsWarpCenterMenuWindow( Window ) ) Found = FIND_WARPCENTER;
   if( IsSysTrayMenuWindow( Window ) ) Found = FIND_SYSTRAY;
   if( IsECenterMenuWindow( Window ) ) Found = FIND_ECENTER;

   // �᫨ �� ���� ���� �����窨:
   if( Found )
    {
     // ���� WarpCenter ���� ��।����� ᮮ�饭�� �������. ��㣨� ���� ��ࠢ���� ���
     // ⠪ ����� - ���� ��ࠢ��� ⠪�� ᮮ�饭�� ���������, ����� �ய�᪠�� ��.
     BYTE Send_messages = 0; if( Found == FIND_WARPCENTER ) Send_messages = 1;

     // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ Esc.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_ESC, 0, 0 );

     // ���뫠�� ᮮ�饭�� � ���� �⢥�, �᫨ �� �ॡ����.
     if( Send_messages )
      {
       WinSendMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinSendMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
      }
     else
      {
       WinPostMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinPostMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
      }

     // ����������, �� ����⢨� �믮�����.
     Action_is_performed = 1;

     // �᫨ ������ eCenter, ���� �롨��� ���� � �।��� �࠭�, �ᯮ���� ��⮪ WindowManager.
     if( Found == FIND_ECENTER )
      {
       Post_queue_message = 1;
       Frame_window = QueryFrameWindow( WinQueryWindow( Window, QW_OWNER ) );
      }

     // �����蠥� ��ॡ�� ����.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������ ��࠭�� ���� � �।��� �࠭�.
 if( Action_is_performed && Activate_window_in_center )
  {
   // �᫨ ����� ����� ���� �ࠧ� ��:
   if( !Post_queue_message )
    {
     // �롨ࠥ� ����.
     ActivateWindowInCenter();
    }
   // � �᫨ ���� ��������� ��⮪ WindowManager:
   else
    {
     // ���뫠�� ᮮ�饭�� � ��।� eCenter. � ⮬� �६���, ��� ��� �ਤ��,
     // eCenter ᤥ���� ᥡ� ��࠭�� � ����� �㤥� ��४������� � ��㣮� ����.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SELECT_ANYTHING, 0 );
    }
  }

 // ������.
 return;
}

// ��� ��뢠�� ePager ���

VOID Launcher_ToggleEPager( VOID )
{
 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ���� ePager:
   if( IsEPagerWindow( Window ) )
    {
     // �᫨ �������� ���� WarpCenter - ���祬 ���.
     if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
      {
       Launcher_HideShellToolbarMenu( 0 );
       Launcher_HideShellToolbarMenu( 0 );
      }

     // �᫨ ���� ePager �� ��࠭�:
     if( !WindowIsActive( Window ) )
      {
       // �᫨ ���� ���� - �����뢠�� ���.
       if( !WinIsWindowVisible( Window ) ) WinShowWindow( Window, 1 );

       // ��뢠�� ���� � ������ ��� ��࠭��.
       WinSetActiveWindow( Desktop, Window );
      }
     // � �᫨ ��� 㦥 �맢���:
     else
      {
       // ������ ��࠭�� ���� � �।��� �࠭�.
       ActivateWindowInCenter();
      }

     // �����蠥� ��ॡ�� ����.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ��뢠�� ��� ����� FileBar ���

VOID Launcher_ShowFileBarMenu( VOID )
{
 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ���� - �த������ ��ॡ�� ����.
   if( !WinIsWindowVisible( Window ) ) continue;

   // �᫨ �� ���� FileBar:
   if( IsFileBarWindow( Window ) )
    {
     // ������ ���� ����, �ᯮ�������� ����� ���� ࠬ�� FileBar.
     HWND Menu_window = WinWindowFromID( Window, FID_MENU );

     // ���뫠�� ��� ᮮ�饭�� � ����⨨ ������ ���.
     WinPostMsg( Menu_window, WM_BUTTON1DOWN, MRFROM2SHORT( 1, 1 ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );
     WinPostMsg( Menu_window, WM_BUTTON1UP, MRFROM2SHORT( 1, 1 ), MRFROM2SHORT( HT_NORMAL, KC_NONE ) );

     // �����蠥� ��ॡ�� ����.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ��뢠�� ��� ����� ᯨ᮪ ���� ���

// Show_window - ����� ��� �������� ����, Show_at_pointer - ��६����� ��� � 㪠��⥫� ���.
VOID Launcher_ShowWindowList( BYTE Show_window, LONG Show_at_pointer = 0 )
{
 // �᫨ �������� ���� ᮮ�饭�� �� �訡�� - ������.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // ���.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // ������.
   return;
  }

 // ��ॡ�ࠥ� ����.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ᯨ᮪ ����:
   if( IsWinListWindow( Window ) )
    {
     // �᫨ ���� ���� ��������:
     if( Show_window )
      {
       // �᫨ ���� ���� ��।������ � 㪠��⥫� ���:
       if( Show_at_pointer )
        {
         // ������ ࠧ��� �࠭�.
         HWND Desktop = QueryDesktopWindow();

         INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
         INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

         // ������ �ᯮ������� 㪠��⥫� ���.
         POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );

         // ������ �ᯮ������� ����.
         SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

         // �᫨ ���� 㢥��祭� - ����⠭�������� ���.
         if( Window_placement.fl & SWP_MAXIMIZE )
          {
           // ����⠭�������� ����.
           PerformAction( Window, RESTORE_ACTION );

           // ������ ���� ࠧ��� � �ᯮ������� ����.
           WinQueryWindowPos( Window, &Window_placement );
          }

         // ������ ���� ࠧ��� � �ᯮ������� ����.
         INT X_Size = Window_placement.cx;
         INT Y_Size = Window_placement.cy;

         INT X_Position = Pointer.x - X_Size / 2;
         INT Y_Position = Pointer.y - Y_Size / 2;

         if( X_Position + X_Size > X_Screen ) X_Position = X_Screen - X_Size;
         if( Y_Position + Y_Size > Y_Screen ) Y_Position = Y_Screen - Y_Size;

         if( X_Position < 0 ) X_Position = 0;
         if( Y_Position < 0 ) Y_Position = 0;

         // ��⠭�������� ����� �ᯮ������� ����.
         WinSetWindowPos( Window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
        }

       // �����뢠�� ����.
       if( !WinIsWindowVisible( Window ) )
        {
         // �����뢠�� ����.
         WinShowWindow( Window, 1 );

         // ��뢠�� ���� � ������ ��� ��࠭��.
         WinSetActiveWindow( QueryDesktopWindow(), Window );
        }
      }
     // � �᫨ ���� ���� �����:
     else
      {
       // �᫨ ���� �� ����:
       if( WinIsWindowVisible( Window ) )
        {
         // ���뢠�� ���.
         WinShowWindow( Window, 0 );

         // ������ ��࠭�� ���� � �।��� �࠭�.
         BYTE All_OK = ActivateWindowInCenter();

         // �᫨ ⠪��� ���� ��� - ��뢠�� ��ࠢ������� ᯨ᪠ ����.
         if( !All_OK ) WinPostQueueMsg( Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_WIN_LIST, (MPARAM) Window, 0 );
        }
      }

     // �����蠥� ��ॡ�� ����.
     WinEndEnumWindows( Enumeration );

     // ������.
     return;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ����� �� ��⥬�� ���� ���

VOID Launcher_HideAllSystemWindows( VOID )
{
 // ���祬 ᯨ᮪ ���� � ���� WarpCenter.
 if( SystemWindowIsPresent( FIND_WINDOW_LIST | FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
  {
   Launcher_ShowWindowList( 0 ); Launcher_HideShellToolbarMenu( 1 );
  }

 // ������.
 return;
}

// ��� ������� ��⮪, �믮����騩 ��������, � ���뫠�� ��� ᮮ�饭�� ���

// Message, - ᮮ�饭�� ��� ��⮪�, First_parameter - ���� ��ࠬ��� ᮮ�饭��.
VOID Launcher_StartDetachedWaiterThread( ULONG Message, ULONG First_parameter )
{
 // ����뢠�� ��६����� ��� �⢥� �� ��⮪�.
 Thread_responds.Thread_is_created = 0;

 // ������� ��⮪.
 TID Waiter = NULLHANDLE; APIRET Thread_is_created = DosCreateThread( &Waiter, (PFNTHREAD) WaiterThread, 0, 0, THREAD_STACK_SIZE );
 // �᫨ �� ᮧ��� - ����, ���� � ��� �㤥� ᮧ���� ��।� ᮮ�饭��.
 if( Thread_is_created == NO_ERROR ) while( Thread_responds.Thread_is_created == 0 ) { Retard(); }

 // �᫨ ��⮪ 㤠���� ᮧ����:
 if( Thread_is_created == NO_ERROR && Thread_responds.Thread_is_created != -1 )
  {
   // ���뫠�� ᮮ�饭�� � ��⮪.
   HMQ Owner_queue = Enhancer.Modules.Launcher->Message_queue;
   WinPostQueueMsg( Enhancer.Modules.Waiter->Message_queue, Message, (MPARAM) First_parameter, (MPARAM) Owner_queue );

   // ���뢠�� �� ����.
   Enhancer.Modules.Waiter->Message_queue = NULLHANDLE;
  }

 // ������.
 return;
}

// ��� ��४��砥� ����७�� ������� ���

VOID Launcher_SwitchRepeatMode( VOID )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // ���뫠�� ������� �ந��뢠⥫� PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*repeat" );

 // ���뫠�� ������� �ந��뢠⥫� WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "flip repeat" );

 // ���뫠�� ������� �ந��뢠⥫� Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*repeat" );

 // ������.
 return;
}

// ��� ����砥� ��� �ਮ�⠭�������� �ந��뢠⥫� ���

VOID Launcher_FlipPlayerPause( VOID )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // ���뫠�� ������� �ந��뢠⥫� PM123.
 if( !Launcher.RTSettings.Player_is_stopped )
  {
   TransactNamedPipe( Pipes->PM123_pipe, "*pause on" );
   Launcher.RTSettings.Player_is_stopped = 1;
  }
 else
  {
   TransactNamedPipe( Pipes->PM123_pipe, "*pause off" );
   Launcher.RTSettings.Player_is_stopped = 0;
  }

 // ���뫠�� ������� �ந��뢠⥫� WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "flip pause" );

 // ���뫠�� ������� �ந��뢠⥫� Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*pause" );

 // ������.
 return;
}

// ��� ��ॢ���� �ந��뢠⥫� � ᫥���饩 ��஦�� ���

VOID Launcher_SkipPlayerTrack( VOID )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // ���뫠�� ������� �ந��뢠⥫� PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*next" );

 // ���뫠�� ������� �ந��뢠⥫� WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "exit" );

 // ���뫠�� ������� �ந��뢠⥫� Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*next" );

 // ������.
 return;
}

// ��� ��ॢ���� �ந��뢠⥫� � �।��饩 ��஦�� ���

VOID Launcher_RollbackPlayerTrack( VOID )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // ���뫠�� ������� �ந��뢠⥫� PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*previous" );

 // ���뫠�� ������� �ந��뢠⥫� Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*previous" );

 // ������.
 return;
}

// ��� ��⠭�������� �ந��뢠⥫� ���

VOID Launcher_StopPlayer( VOID )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // ���뫠�� ������� �ந��뢠⥫� PM123.
 TransactNamedPipe( Pipes->PM123_pipe, "*stop" );

 // ���뫠�� ������� �ந��뢠⥫� WarpVision.
 TransactNamedPipe( Pipes->WarpVision_pipe, "exit" );

 // ���뫠�� ������� �ந��뢠⥫� Z!.
 TransactNamedPipe( Pipes->ZMP3_pipe, "*stop" );

 // ������.
 return;
}

// ��� �����稢��� ��� 㬥��蠥� �஬����� ���

// Up_or_down - ���祭��, �� ���஥ ���� �������� �஬�����.
VOID Launcher_ChangePlayerVolume( INT Up_or_down )
{
 // ����砥� 㪠��⥫� �� ᯨ᮪ �������� PIPE-ᮥ�������.
 PPIPES Pipes = GetKnownPipes();

 // �����稢��� �஬����� ��� �ந��뢠⥫� PM123.
 if( Up_or_down > 0 ) TransactNamedPipe( Pipes->PM123_pipe, "*volume +3" );
 if( Up_or_down < 0 ) TransactNamedPipe( Pipes->PM123_pipe, "*volume -3" );

 // �����稢��� �஬����� ��� �ந��뢠⥫� WarpVision.
 {
  if( Launcher.RTSettings.Player_volume == 0 ) Launcher.RTSettings.Player_volume = 25;
  else Launcher.RTSettings.Player_volume += ( Up_or_down * 5 );

  if( Launcher.RTSettings.Player_volume < 0 ) Launcher.RTSettings.Player_volume = 0;
  if( Launcher.RTSettings.Player_volume > 100 ) Launcher.RTSettings.Player_volume = 100;

  {
   CHAR Volume_string[ 25 ] = "";
   itoa( Launcher.RTSettings.Player_volume, Volume_string, 10 );

   CHAR Query_string[ SIZE_OF_PIPE_COMMAND ] = "";
   strcpy( Query_string, "set volume " ); strcat( Query_string, Volume_string );

   TransactNamedPipe( Pipes->WarpVision_pipe, Query_string );
  }
 }

 // �����稢��� ��� 㬥��蠥� �஬����� ��� �ந��뢠⥫� Z!.
 if( Up_or_down > 0 ) TransactNamedPipe( Pipes->ZMP3_pipe, "*vol+" );
 if( Up_or_down < 0 ) TransactNamedPipe( Pipes->ZMP3_pipe, "*vol-" );

 // ������.
 return;
}

// ��� �����稢��� ��� 㬥��蠥� �஬����� ���

// Frame_window - ���� �ਫ������, Up_or_down - ���祭��, �� ���஥ ���� �������� �஬�����.
VOID Launcher_PostMMOS2VolumeMessages( HWND Frame_window, INT Up_or_down )
{
 // ��ॡ�ࠥ� ����, �ᯮ������� � ���� ࠬ��.
 HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ �� ���� ������ � ��५����:
   if( IsCircularSliderWindow( Window ) )
    {
     // ������ ��࠭��� ���祭�� �஬����.
     // ��६����� "MMOS2_volume" �ᯮ�������� � ࠧ���塞�� ������ �����,
     // ���⮬� ����� � ��� �� �६� ��ࠡ�⪨ �⮣� ᮮ�饭�� �㤥� ��������.
     MRESULT Rc = WinSendMsg( Window, CSM_QUERYVALUE, (MPARAM) &Launcher.RTSettings.MMOS2_volume, 0 );

     // �᫨ ��� 㤠���� �������:
     if( Rc != 0 )
      {
       // ������ �������襥 � �������襥 ��������� ���祭��.
       WinSendMsg( Window, CSM_QUERYRANGE, (MPARAM) &Launcher.RTSettings.MMOS2_volume_from, (MPARAM) &Launcher.RTSettings.MMOS2_volume_to );

       // ������ ����� ���祭��.
       Launcher.RTSettings.MMOS2_volume += Up_or_down * 2;
       if( Launcher.RTSettings.MMOS2_volume < Launcher.RTSettings.MMOS2_volume_from ) Launcher.RTSettings.MMOS2_volume = Launcher.RTSettings.MMOS2_volume_from;
       if( Launcher.RTSettings.MMOS2_volume > Launcher.RTSettings.MMOS2_volume_to ) Launcher.RTSettings.MMOS2_volume = Launcher.RTSettings.MMOS2_volume_to;

       WinPostMsg( Window, CSM_SETVALUE, (MPARAM) Launcher.RTSettings.MMOS2_volume, 0 );
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� �����稢��� ��� 㬥��蠥� �஬����� ���

// Frame_window - ���� �ਫ������, Up_or_down - ���祭��, �� ���஥ ���� �������� �஬�����.
VOID Launcher_PostUniMixMessages( HWND Frame_window, INT Up_or_down )
{
 // �஢��塞 ����� UniMixer.
 if( IsSpeedPascalWindow( Frame_window ) )
  {
   // ��ॡ�ࠥ� ����, �ᯮ������� � ���� ࠬ��.
   HENUM Enumeration = WinBeginEnumWindows( WinWindowFromID( Frame_window, FID_CLIENT ) ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // ���⠢�塞 ᮮ�饭�� � ����⨨ ��५�� ����� ��� ��ࠢ�.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
     if( Up_or_down > 0 )
      ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_RIGHT, 0, 0 );
     else
      ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_LEFT, 0, 0 );

     // ���뫠�� ���.
     WinPostMsg( Window, WM_CHAR, First_parameter_1, Second_parameter_1 );
     WinPostMsg( Window, WM_CHAR, First_parameter_2, Second_parameter_2 );
    }
   WinEndEnumWindows( Enumeration );
  }

 // ������.
 return;
}

// ��� �����稢��� ��� 㬥��蠥� �஬����� ���

// Up_or_down - ���祭��, �� ���஥ ���� �������� �஬�����.
VOID Launcher_ChangeMMOS2Volume( INT Up_or_down )
{
 // �஢��塞, ���� �� ���� �ਫ������, ᯮᮡ���� ������ ���, � �᫨ ��� ���� - ���頥��� � ����.
 HWND MMOS2_volume_window = FindAppWindow( APP_MMOS2_VOLUME );
 if( MMOS2_volume_window != NULLHANDLE )
  {
   // ���뫠�� ᮮ�饭�� � ���� MMOS2 Volume.
   Launcher_PostMMOS2VolumeMessages( MMOS2_volume_window, Up_or_down );

   // ������.
   return;
  }

 HWND UniMix_window = FindAppWindow( APP_UNIAUDIO_MIXER );
 if( UniMix_window != NULLHANDLE )
  {
   // ���뫠�� ᮮ�饭�� � ���� UniAudio Mixer.
   Launcher_PostUniMixMessages( UniMix_window, Up_or_down );

   // ������.
   return;
  }

 // �᫨ ���� ��� - ��뢠�� �ਫ������, ���஥ ������� ��� � ���� ��� ������.
 if( ShowCommandCanBeUsed( SHOW_MMOS2_VOLUME ) )
  {
   // ���뫠�� ᮮ�饭�� � ��⮪, ����� �맮��� �ਫ������.
   WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_MMOS2_VOLUME, 0 );
   // ���뫠�� ᮮ�饭�� � ��⮪, ����� �믮���� ��������.
   Launcher_StartDetachedWaiterThread( SM_WAIT_STARTING_PROCESS, APP_MMOS2_VOLUME );

   // ������.
   return;
  }

 if( ShowCommandCanBeUsed( SHOW_UNIAUDIO_MIXER ) )
  {
   // ���뫠�� ᮮ�饭�� � ��⮪, ����� �맮��� �ਫ������.
   WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_UNIAUDIO_MIXER, 0 );
   // ���뫠�� ᮮ�饭�� � ��⮪, ����� �믮���� ��������.
   Launcher_StartDetachedWaiterThread( SM_WAIT_STARTING_PROCESS, APP_UNIAUDIO_MIXER );

   // ������.
   return;
  }

 // ������.
 return;
}

// ��� �믮���� ��।������ ����⢨� �� ����⨨ �� ������ ���

// Action - ����⢨�, ���஥ �㦭� �믮�����, Do_not_check_mouse - �⪫���� �஢��� ���.
VOID Launcher_DoSystemAction( INT Action, LONG Do_not_check_mouse = 0 )
{
 // ������ ��� �� ������ ���� ����� - ��������, ��।�������� �।��� ��� ����.
 if( !Do_not_check_mouse ) if( MouseIsBusy() )
  {
   // ���.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // ������.
   return;
  }

 // �᫨ �������� ���� ᮮ�饭�� �� �訡�� - ��祣� ������ �� �㦭�.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // ���.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // ������.
   return;
  }

 // ��⠭�������� ��४���⥫� �� ���������, �⮡� ����⥫� �� ��稭��
 // ��।������� ����ࠦ����, �᫨ � ���� ���� ���ࠢ������ ᮮ�饭�� �� ���.
 if( KeyIsToggled( SC_SCRLLOCK ) ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // ��뢠�� WarpCenter, ECenter ��� SysTray.
 if( Action == SHOW_WARPCENTER || Action == SHOW_ECENTER || Action == SHOW_SYSTRAY )
  {
   // �᫨ ���� 㦥 �������� - ���祬 ���.
   if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
    {
     // ���祬 ����.
     Launcher_HideShellToolbarMenu( 1 );
    }
   // ���� - ��뢠�� ���.
   else
    {
     // ����砥� 㪠��⥫� �� ᯨ᮪ �������� ���� ���窮�.
     POBJECTS Objects = GetKnownObjects();

     // �஡㥬 ���� ����.
     LONG Toolbar = FIND_WARPCENTER;
     PCHAR Object_name = Objects->WarpCenter_name;

     if( Action == SHOW_SYSTRAY )
      {
       Toolbar = FIND_SYSTRAY;
       Object_name = Objects->SysTray_name;
      }

     if( Action == SHOW_ECENTER )
      {
       Toolbar = FIND_ECENTER;
       Object_name = Objects->ECenter_name;
      }

     // �᫨ ��� ���:
     if( !SystemWindowIsPresent( Toolbar ) )
      {
       // ������ ���箪 �� ࠡ�祬 �⮫�.
       HOBJECT Object = QueryWPSObject( Object_name );

       // �᫨ ���箪 ���� - ��뢠�� ���.
       if( Object != NULLHANDLE ) WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
      }

     // ��뢠�� ����.
     Launcher_ShowShellToolbarMenu( Toolbar );
    }

   // ������.
   return;
  }

 // ��뢠�� EPager.
 if( Action == SHOW_EPAGER )
  {
   // ��뢠�� ���� ePager.
   Launcher_ToggleEPager();

   // ������.
   return;
  }

 // ��뢠�� ���� FileBar.
 if( Action == SHOW_FILEBAR )
  {
   // ��뢠�� ���� FileBar.
   Launcher_ShowFileBarMenu();

   // ������.
   return;
  }

 // ��뢠�� ᯨ᮪ ����.
 if( Action == SHOW_WINDOW_LIST )
  {
   // �᫨ ᯨ᮪ ���� 㦥 �맢�� - ���祬 ���.
   if( SystemWindowIsPresent( FIND_WINDOW_LIST, FIND_VISIBLE_WINDOW ) )
    {
     Launcher_ShowWindowList( 0 );
    }
   // ���� - ��뢠�� ᯨ᮪ ����.
   else
    {
     Launcher_ShowWindowList( 1 );
    }

   // ������.
   return;
  }

 // ������ ��࠭�� ᫥���饥 ��� �।��饥 ���� � ᯨ᪥ ����.
 if( Action == SHOW_NEXT_WINDOW || Action == SHOW_PREV_WINDOW )
  {
   // �᫨ ���� ᬥ�� ������ - ������.
   if( RoomsChangeIsInProcess() ) return;

   // �᫨ �ᯮ������ �����窠 WPS, �� �� ���� 㬥��襭�, �������� ����ᠭ�� ��⥬� ��
   // �����஥ �६�. ��� �ந�室�� �� �맮�� WinQueryWindow(), � 祬 ���� - ������⭮.
   if( ShellIsWPS() )
    if( GetCurrentOrNextRoom() == SHELL_ROOM )
     if( !ShellIsAvailable() ) return;

   // ������ ����, ���஥ ᥩ�� ��࠭�.
   HWND Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

   // �᫨ ��� ��� ��� � ���� ����� �뫮 ��४������� � ������� ����⥫�:
   if( Active_window == NULLHANDLE || !Launcher_PermissionForHotKeySwitching( Active_window ) )
    {
     // ������ ���� � �।��� �࠭�.
     HWND Window_in_center = WindowInCenter();

     // �᫨ ��� ���� � �� �� ��࠭��� ���� - ������ ��� ��࠭��.
     if( Window_in_center != NULLHANDLE ) if( Window_in_center != Active_window )
      {
       // ������ ��࠭�� ���� � �।��� �࠭�.
       MoveWindowAbove( Window_in_center );

       // ������.
       return;
      }
    }

   // �᫨ ��࠭��� ���� - ᯨ᮪ ����, ��� ���� �����.
   if( Active_window != NULLHANDLE )
    {
     // �᫨ �� ᯨ᮪ ���� - ���祬 ���.
     if( IsWinListWindow( Active_window ) ) PerformAction( Active_window, HIDE_ACTION );
    }

   // ������ ᫥���饥 ��� �।��饥 ���� � ᯨ᪥ ���� � ���������� ���.
   // ��� �� ��࠭��, ����� "prevtop" �����頥� ᫥���饥 ����, � "nexttop" - �।��饥.
   LONG Query = QW_PREVTOP; if( Action == SHOW_PREV_WINDOW ) Query = QW_NEXTTOP;

   HWND Next_window = WinQueryWindow( Active_window, Query );
   HWND Primary_window = Next_window;

   // �᫨ ��४��祭�� ���������� - ��ᬠ�ਢ��� ᯨ᮪ �����.
   if( !Launcher_PermissionForHotKeySwitching( Next_window ) )
    while( 1 )
     {
      // ������ ᫥���饥 ���� � ᯨ᪥ ����.
      Next_window = WinQueryWindow( Next_window, Query );

      // �᫨ ᯨ᮪ �ன��� - ������.
      if( Next_window == Active_window || Next_window == Primary_window ) return;

      // �᫨ ��४��祭�� �������� - �����蠥� ��ॡ�� ����.
      if( Launcher_PermissionForHotKeySwitching( Next_window ) ) break;
     }

   // ������ ���� ��࠭��.
   MoveWindowAbove( Next_window );

   // ������.
   return;
  }

 // �᫨ ���짮��⥫� ࠡ�⠥� � ����� �ਫ������, ���஥ ᮮ⢥����� �⮩ ������� -
 // ���祬 ��� � �롨ࠥ� ���� � �।��� �࠭�.
 if( Launcher_CheckActiveWindowAndHideApplication( Action ) ) return;

 // �᫨ ���� �� �������� �ਫ������ ����� �⪫�������� �� ��� ������� - ��뢠�� ���.
 // �᫨ ��� �⮩ ������� �� ����� ���箪 - �ਫ������ �㤥� �맢��� � ����� ��।�.
 if( Launcher_FindAndShowApplication( Action ) ) return;

 // ��뢠�� ���箪 �� ࠡ�祬 �⮫�.
 // �� �㤥� �맢�� ⮫쪮 �᫨ ��� �⮩ ������� ��� ���室�饣� �ਫ������.
 if( Action >= SHOW_OBJECT_FIRST && Action <= SHOW_OBJECT_LAST )
  {
   // �᫨ �����窠 WPS �� �ᯮ������:
   if( !ShellIsWPS() )
    {
     // �᫨ � ����⢥ �����窨 �ᯮ������ FileBar - ��뢠�� ���.
     if( ShellIsFileBar() ) Launcher_ShowFileBarMenu();

     // ������.
     return;
    }

   // ��뢠�� �ਭ��.
   if( Action == SHOW_PRINTER )
    {
     // ������ ��� �ਭ��, � ����� ࠡ�⠥� ���짮��⥫�.
     CHAR Name[ SIZE_OF_PATH ] = ""; QueryPrinterName( Name );

     // �᫨ ��� 㧭��� �� 㤠���� - ��뢠�� ���� ��ᬮ�� ���ﭨ� ��� �ਭ�஢.
     if( Name[ 0 ] == 0 )
      {
       // ���뫠�� ᮮ�饭�� � ��⮪.
       WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) SHOW_PRINTERS, 0 );

       // ������.
       return;
      }
    }

   // ����砥� 㪠��⥫� �� ᯨ᮪ �������� ���� ���窮�.
   POBJECTS Objects = GetKnownObjects();

   // ������ ��� ���窠.
   CHAR Name[ SIZE_OF_PATH ] = "";

   if( Action == SHOW_DRIVES )         strcpy( Name, Objects->Drives_name );
   if( Action == SHOW_PRINTERS )       strcpy( Name, Objects->Printers_name );

   if( Action == SHOW_WINVIEWER )      strcpy( Name, Objects->Viewer_name );
   if( Action == SHOW_WPS_CLOCK )      strcpy( Name, Objects->Clock_name );
   if( Action == SHOW_PULSE )          strcpy( Name, Objects->Pulse_name );
   if( Action == SHOW_POWER_MGR )      strcpy( Name, Objects->PowerMgr_name );

   if( Action == SHOW_LAUNCHPAD )      strcpy( Name, Objects->LaunchPad_name );

   // �᫨ ��� 㧭��� �� 㤠���� - ������.
   if( Name[ 0 ] == NULL ) return;

   // ������ ���箪 �� ࠡ�祬 �⮫�.
   HOBJECT Object = QueryWPSObject( Name );

   // �᫨ ���箪 ����:
   if( Object != NULLHANDLE )
    {
     // ��뢠�� ���箪.
     WinOpenObject( Object, OPEN_DEFAULT, SHOW_EXISTING );
    }
   // � �᫨ ���窠 ��� - ��뢠�� ᯨ᮪ ����.
   else
    {
     // �᫨ ᯨ᮪ ���� 㦥 �맢�� - ���祬 ���.
     if( SystemWindowIsPresent( FIND_WINDOW_LIST, FIND_VISIBLE_WINDOW ) )
      {
       Launcher_ShowWindowList( 0 );
      }
     // ���� - ��뢠�� ᯨ᮪ ����.
     else
      {
       Launcher_ShowWindowList( 1 );
      }
    }

   // ������.
   return;
  }

 // ��ࠢ�塞 �ந��뢠⥫��.
 if( Action >= MM_FIRST && Action <= MM_LAST )
  {
   // ���頥��� � �ந��뢠⥫�.
   switch( Action )
    {
     case MM_VOLUME_INCREMENT:       Launcher_ChangePlayerVolume( +1 ); break;
     case MM_VOLUME_DECREMENT:       Launcher_ChangePlayerVolume( -1 ); break;
     case MM_VOLUME_INCREMENT_MMOS2: Launcher_ChangeMMOS2Volume( +1 );  break;
     case MM_VOLUME_DECREMENT_MMOS2: Launcher_ChangeMMOS2Volume( -1 );  break;

     case MM_REPEAT:                 Launcher_SwitchRepeatMode();       break;
     case MM_PAUSE:                  Launcher_FlipPlayerPause();        break;
     case MM_NEXT:                   Launcher_SkipPlayerTrack();        break;
     case MM_PREVIOUS:               Launcher_RollbackPlayerTrack();    break;
     case MM_STOP:                   Launcher_StopPlayer();             break;
    }

   // ������.
   return;
  }

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Launcher_LauncherMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Launcher->Priority = MAKELONG( Class, Delta );
  }

 // �믮��塞 �ॡ㥬�� ����⢨�.
 if( Message->msg == SM_DO_SYSTEM_ACTION ) Launcher_DoSystemAction( (INT) Message->mp1, (LONG) Message->mp2  );

 // ��뢠�� LaunchPad.
 if( Message->msg == SM_SHOW_LAUNCHPAD )
  {
   // ����, ���� ���� �� �⠭�� ᢮�����.
   while( MouseIsBusy() ) Retard();

   // ��뢠�� LaunchPad.
   Launcher_DoSystemAction( SHOW_LAUNCHPAD );
  }

 // ��뢠�� ᯨ᮪ ����.
 if( Message->msg == SM_SHOW_WINDOW_LIST )
  {
   // ������, ������ �� ᯨ᮪ ���� ������ �冷� � 㪠��⥫�� ���.
   LONG Show_at_pointer = (LONG) Message->mp1;

   // �����뢠�� ��� ����.
   Launcher_ShowWindowList( 1, Show_at_pointer );
  }

 // ���뢠�� ᯨ᮪ ����.
 if( Message->msg == SM_HIDE_WINDOW_LIST ) Launcher_ShowWindowList( 0 );

 // ���뢠�� ���� WarpCenter.
 if( Message->msg == SM_HIDE_WARPCENTER ) Launcher_HideShellToolbarMenu( 1 );

 // ���뢠�� ���� ॣ���� �஬����.
 if( Message->msg == SM_STARTING_PROCESS_APPEARED )
  {
   INT App_code = (LONG) Message->mp1;
   HWND Frame_window = (HWND) Message->mp2;

   if( App_code == APP_MMOS2_VOLUME || App_code == APP_UNIAUDIO_MIXER )
    WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� �믮����� ࠧ����� ����⢨� ���

VOID Launcher_LauncherThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE )
  {
   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Launcher->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Launcher->Message_queue == NULLHANDLE )
  {
   // �����蠥� ࠡ��� ��⮪�.
   WinTerminate( Thread );

   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ��⮪ ᮧ��� �ᯥ譮.
 Thread_responds.Thread_is_created = 1;

 // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
 QMSG Message = {0};
 while( WinGetMsg( Thread, &Message, 0, 0, 0 ) )
  {
   // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
   QMSG Next_message = {0};
   WinPeekMsg( Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE );
   if( Next_message.msg == Message.msg )
    if( Next_message.mp1 == Message.mp1 )
     if( Next_message.mp2 == Message.mp2 )
      if( Next_message.hwnd == Message.hwnd ) continue;

   // ��ࠡ��뢠�� ᮮ�饭��.
   Launcher_LauncherMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
