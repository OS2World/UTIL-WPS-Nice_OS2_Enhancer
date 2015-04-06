
// ��� �롨ࠥ� �।��।������� ������� ��� ���� ���

// Frame_window - ���� ࠬ��.
INT Rooms_GetPreDefinedRoom( HWND Frame_window )
{
 // �᫨ ࠧ����� �ਫ������ � ������� �� ���� - ������.
 if( !Rooms.Settings.Allocate_windows_to_Rooms ) return NO_ROOM;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥.
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_1_name ) ) return Rooms.Settings.Allocations.Preferable_room_1;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_2_name ) ) return Rooms.Settings.Allocations.Preferable_room_2;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_3_name ) ) return Rooms.Settings.Allocations.Preferable_room_3;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_4_name ) ) return Rooms.Settings.Allocations.Preferable_room_4;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_5_name ) ) return Rooms.Settings.Allocations.Preferable_room_5;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_6_name ) ) return Rooms.Settings.Allocations.Preferable_room_6;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_7_name ) ) return Rooms.Settings.Allocations.Preferable_room_7;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_8_name ) ) return Rooms.Settings.Allocations.Preferable_room_8;
  }

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_1_name ) ) return Rooms.Settings.Allocations.Preferable_room_1;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_2_name ) ) return Rooms.Settings.Allocations.Preferable_room_2;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_3_name ) ) return Rooms.Settings.Allocations.Preferable_room_3;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_4_name ) ) return Rooms.Settings.Allocations.Preferable_room_4;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_5_name ) ) return Rooms.Settings.Allocations.Preferable_room_5;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_6_name ) ) return Rooms.Settings.Allocations.Preferable_room_6;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_7_name ) ) return Rooms.Settings.Allocations.Preferable_room_7;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_8_name ) ) return Rooms.Settings.Allocations.Preferable_room_8;
  }

 // �᫨ ���� ࠧ����� � ������� ������� ����⥫� �ਫ������:
 if( Rooms.Settings.Allocate_known_applications )
  {
   // �᫨ 㤠���� ��।����� ��� �ਫ������:
   if( Exe_name[ 0 ] != 0 )
    {
     // �஢��塞 ���.
     if( WindowIsUsedTo( DO_BROWSE_FTP_SITES, Frame_window ) )   return NORTHERN_ROOM;
     if( WindowIsUsedTo( DO_REMOTE_CONTROL, Frame_window ) )     return NORTHERN_ROOM;
     if( WindowIsUsedTo( DO_MANAGE_FILES, Frame_window ) )       return WESTERN_ROOM;
     if( WindowIsUsedTo( DO_CONNECT_INTERNET, Frame_window ) )   return EASTERN_ROOM;
     if( WindowIsUsedTo( DO_READ_MESSAGES, Frame_window ) )      return SOUTHERN_ROOM;
    }
  }

 // ������.
 return NO_ROOM;
}

// ��� �����ࠥ� �������� ���室���� ������� ��� ���� ���

// Frame_window - ���� ࠬ��.
INT Rooms_GetMostSuitableRoom( HWND Frame_window )
{
 // �᫨ ���� �।��।������� ������ - �ᯮ��㥬 �� ���祭��.
 INT PreDefined_room = Rooms_GetPreDefinedRoom( Frame_window );
 if( PreDefined_room != NO_ROOM && PreDefined_room != SHELL_ROOM ) return PreDefined_room;

 // ������.
 return NO_ROOM;
}

// ��� ����⠭�������� � ����뢠�� ���� WPS, �ᯮ������� � ������� ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID Rooms_RestoreAndCloseOuterWPSWindows( HWND Desktop )
{
 // �᫨ �ᯮ������ �����窠 WPS:
 if( ShellIsWPS() )
  {
   // ������ ࠧ��� �࠭�.
   INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
   INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

   // ������ ���� �����窨.
   HWND Shell_window = GetDetectedShellWindow();

   // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
   HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // �᫨ �� �� ���� �����窨:
     if( Window != Shell_window )
      {
       // ������ �������, � ���ன �ᯮ������ ����.
       INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

       // �᫨ �� �� ������ � ����� �����窨:
       if( Window_room != SHELL_ROOM )
        {
         // �᫨ �� ���� WPS:
         if( IsFolderWindow( Window ) )
          {
           // ������ �ᯮ������� ���� � ��� ���ﭨ�.
           SWP Window_state = {0}; WinQueryWindowPos( Window, &Window_state );

           // �᫨ ���� 㬥��襭� � ���箪 ��� ����:
           if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE )
            {
             // ��⠭�������� ����-�������� ������ ��� ����. ��� ����뢠�� �࠭, �� ��祣� �� ����.
             ShowCurtainWindow( Desktop );

             // �⪫�砥� ���⠢�� �� ����⨨ ����, �⮡� ��� ����뢠���� ����॥.
             DisableAnimation( Window );

             // ����⠭�������� � ����뢠�� ���.
             PerformAction( Window, RESTORE_ACTION );
             PerformAction( Window, CLOSE_ACTION );
            }
          }
        }
      }
    }
   WinEndEnumWindows( Enumeration );
  }

 // ������.
 return;
}

// ��� ������ ����ࠦ���� ��� ����訢���� ࠡ�祣� �⮫� ���

VOID Rooms_DeleteDesktopWallpaper( VOID )
{
 // ����塞 ����ࠦ����.
 if( Rooms.RTSettings.Wallpaper != NULLHANDLE )
  {
   GpiDeleteBitmap( Rooms.RTSettings.Wallpaper );
   Rooms.RTSettings.Wallpaper = NULLHANDLE;
  }

 // ������.
 return;
}

// ��� ������� ����ࠦ���� ��� ����訢���� ࠡ�祣� �⮫� ���

// Desktop - ���� ࠡ�祣� �⮫�, New_room - ������.
VOID Rooms_CreateDesktopWallpaper( HWND Desktop, INT New_room )
{
 // ����塞 ����ࠦ����, ᮧ������ ࠭��.
 Rooms_DeleteDesktopWallpaper();

 // ������ ��� 䠩�� � ����ࠦ�����.
 CHAR File_name[ SIZE_OF_PATH ] = "";

 if( New_room == SHELL_ROOM ) if( !ShellIsWPS() ) strcpy( File_name, Rooms.Settings.Wallpaper_for_shell_room );
 if( New_room == NORTHERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_northern_room );
 if( New_room == WESTERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_western_room );
 if( New_room == EASTERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_eastern_room );
 if( New_room == SOUTHERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_southern_room );

 // ����㦠�� ����ࠦ���� � ��᪠.
 HBITMAP Loaded_image = NULLHANDLE; INT Bitmap_width = 0; INT Bitmap_height = 0;
 LoadBitmap( Enhancer.Application, File_name, &Loaded_image, &Bitmap_width, &Bitmap_height );

 // �᫨ ����ࠦ���� ��� - ������.
 if( Loaded_image == NULLHANDLE ) return;

 // ������� ����࠭�⢮ �⮡ࠦ����.
 HPS Wallpaper_memory_space = CreatePresentationSpace( Enhancer.Application );

 // ������ ࠧ��� �࠭�.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // ������� ����ࠦ���� � ����� ࠧ��஬ � �࠭.
 HBITMAP Bitmap = CreateBitmap( Wallpaper_memory_space, X_Screen, Y_Screen );

 // ������塞 ����ࠦ���� � �����.
 if( Bitmap_width > X_Screen / 4 * 3 || Bitmap_height > Y_Screen / 4 * 3 )
  {
   GpiSetBitmap( Wallpaper_memory_space, Bitmap );

   POINT Point = { ( X_Screen - Bitmap_width ) / 2, ( Y_Screen - Bitmap_height ) / 2 };
   WinDrawBitmap( Wallpaper_memory_space, Loaded_image, NULL, &Point, 0, 0, DBM_NORMAL );

   GpiSetBitmap( Wallpaper_memory_space, NULLHANDLE );
  }
 else
  {
   GpiSetBitmap( Wallpaper_memory_space, Bitmap );

   for( INT X_Count = 0; X_Count < X_Screen; X_Count += Bitmap_width )
    for( INT Y_Count = 0; Y_Count < Y_Screen; Y_Count += Bitmap_height )
     {
      POINT Point = { X_Count, Y_Count };
      WinDrawBitmap( Wallpaper_memory_space, Loaded_image, NULL, &Point, 0, 0, DBM_NORMAL );
     }

   GpiSetBitmap( Wallpaper_memory_space, NULLHANDLE );
  }

 // ����뢠�� ����࠭�⢮ �⮡ࠦ����.
 GpiDestroyPS( Wallpaper_memory_space );

 // ����塞 ����㦥���� ����ࠦ����.
 GpiDeleteBitmap( Loaded_image ); Loaded_image = NULLHANDLE;

 // ���������� ����祭��� ����ࠦ����.
 Rooms.RTSettings.Wallpaper = Bitmap;

 // ������.
 return;
}

// ��� ����訢��� ࠡ�稩 �⮫ ���

// Desktop - ���� ࠡ�祣� �⮫�.
VOID Rooms_FillDesktop( HWND Desktop )
{
 // �᫨ ����ࠦ���� ��� ����訢���� ��� - ������.
 if( Rooms.RTSettings.Wallpaper == NULLHANDLE ) return;

 // ����⠥� � ����࠭�⢥ �⮡ࠦ���� ����.
 HPS Presentation_space = WinGetPS( Desktop );

 // �᫨ ����࠭�⢮ �⮡ࠦ���� �� ����祭� - ������.
 if( Presentation_space == NULLHANDLE ) return;

 // ������ ࠧ��� �࠭�.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // ������ �ᯮ������� ����ࠦ����.
 POINT Image_points[ 3 ] = { 0, 0, X_Screen, Y_Screen, 0, 0 };
 PPOINT Points = Image_points;

 // ������� ����࠭�⢮ �⮡ࠦ����.
 HPS Wallpaper_memory_space = CreatePresentationSpace( Enhancer.Application );

 // ��७�ᨬ ����ࠦ���� � ����.
 GpiSetBitmap( Wallpaper_memory_space, Rooms.RTSettings.Wallpaper );
 GpiBitBlt( Presentation_space, Wallpaper_memory_space, 3, Points, ROP_SRCCOPY, BBO_IGNORE );
 GpiSetBitmap( Wallpaper_memory_space, NULLHANDLE );

 // ����뢠�� ����࠭�⢮ �⮡ࠦ����.
 GpiDestroyPS( Wallpaper_memory_space );

 // �����蠥� ࠡ��� � ����࠭�⢥ �⮡ࠦ���� ����.
 WinReleasePS( Presentation_space );

 // ������.
 return;
}

// ��� ���뢠�� ��� �����뢠�� ���� ���

// Desktop - ���� ࠡ�祣� �⮫�, New_room - ����� ������, Current_room - ⥪��� ������.
VOID Rooms_ChangeWindowSet( HWND Desktop, INT New_room, INT Current_room )
{
 // �᫨ ���� ����, ���஥ �࠭� ������ - ����⠭�������� ���.
 HWND Rolled_window = RolledWindow(); LONG Rolled_window_buttons = 0;

 if( Rolled_window != NULLHANDLE )
  if( Rooms_PermissionForRoomActions( Rolled_window ) )
   {
    // ���������� ���ﭨ� ������ � ����.
    Rolled_window_buttons = QueryButtonsState( Rolled_window, MINIMIZE_ACTION, 0 );

    // �᫨ ࠬ�� ��� ������ �ᮢ��� �� ���� - ����������, �� �� ���� 㢥��祭�.
    if( !DrawFramesSettingIsON() || !DrawButtonsSettingIsON() ) SetNextButtons( Rolled_window, MAXIMIZE_ACTION );

    // ����⠭�������� ����.
    UnrollWindow( Rolled_window );
    // ��� ⮣�, �⮡� �뫮 ��⠭������ ����� ���ﭨ� ������ � �� ���室� � ��� �������
    // ���� �뫮 ����⠭������ (� �� 㢥��祭�), ���� ��।����� ��ࠬ��� "PA_METHOD_CALLED_BY_WINDOW_MANAGER".
    PerformAction( Rolled_window, RESTORE_ACTION, 0, PA_METHOD_CALLED_BY_WINDOW_MANAGER );

    // �⮤������ ���� �� �� ��⠫�� ����.
    WinSetWindowPos( Rolled_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST );
   }

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // ������ �������, � ���ன �ᯮ������ ����.
   INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

   // ������ �।��।������� �������.
   INT PreDefined_room = Rooms_GetPreDefinedRoom( Window );

   // ���뢠�� �� ���� � ������, � ����� ����� ��४�������.
   BYTE Minimize_window = 0;

   if( Window_room == Current_room ) Minimize_window = 1;

   if( PreDefined_room != NO_ROOM )
    {
     if( Minimize_window ) if( PreDefined_room == New_room ) Minimize_window = 0;
    }

   if( Minimize_window ) if( !PermissionForSwitching( Window ) ) Minimize_window = 0;
   if( Minimize_window ) if( !Rooms_PermissionForRoomActions( Window ) ) Minimize_window = 0;

   if( Minimize_window )
    {
     // ������ ���ﭨ� ������ � ��������� ����.
     LONG Buttons = 0;

     // ���� Win-OS/2 � Odin ����� ⮫쪮 㬥����� � ���箪.
     if( IsWindowsWindow( Window ) )
      {
       Buttons = MINIMIZE_ACTION;
      }
     // ���� OS/2 ����� 㬥����� � ��뢠��.
     else
      {
       // ��� ����, ���஥ �뫮 �࠭� ������ ���ﭨ� ������ �����⭮ ��࠭��.
       if( Window != Rolled_window ) Buttons = QueryButtonsState( Window, MINIMIZE_ACTION | MAXIMIZE_ACTION, 0 );
       else Buttons = Rolled_window_buttons;
      }

     // �᫨ �� ���� OS/2:
     if( !IsWindowsWindow( Window ) )
      {
       // �᫨ ࠬ�� ��� ������ �ᮢ��� �� ���� - ���������� ���ﭨ� ������.
       // ��� �㤥� �ᯮ�짮���� �� �맮�� SetMaximizeProperty() � �� ����⠭������� ����.
       if( !DrawFramesSettingIsON() || !DrawButtonsSettingIsON() || !PermissionForDrawing( Window ) )
        {
         SetProperty( Window, PRP_BUTTONS, &Buttons );
        }
      }

     // �᫨ ���� ����� ���� 㬥��襭� � ���箪:
     if( Buttons & MINIMIZE_ACTION )
      {
       // ���������� ࠧ��� ����.
       RECT Rectangle = {0}; WinQueryWindowRect( Window, &Rectangle );

       INT Width = Rectangle.xRight - Rectangle.xLeft;
       INT Height = Rectangle.yTop - Rectangle.yBottom;

       SetProperty( Window, PRP_PREVIOUS_WIDTH, &Width );
       SetProperty( Window, PRP_PREVIOUS_HEIGHT, &Height );

       // �����蠥� ���� � ���箪.
       // ��� ������ ���� ��७�ᥭ� � ᯨ᮪ ���窮� ������ ����.
       LONG Action = MINIMIZE_ACTION;

       SetProperty( Window, PRP_PERFORMED_ACTION, &Action );
       BYTE Action_completed = PerformAction( Window, Action );

       // ���뢠�� ����, �᫨ ����⢨� �� �뫮 �믮����� � ���� �� �� ��⠥��� �� �࠭�.
       // �� ���� ������ ��� ���� ODIN, ����� �� ������ �������� �� ᮮ�饭��.
       if( !Action_completed ) WinShowWindow( Window, 0 );

       // ������ ���� ������㯭� ��� ��४��祭��.
       WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
      }
     // � �᫨ ���� ����� ⮫쪮 �����:
     else
      {
       // ���뢠�� ����.
       WinShowWindow( Window, 0 );

       // ������ ���� ������㯭� ��� ��४��祭��.
       WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
      }
    }

   // �����뢠�� ���� ��� ����� �������.
   BYTE Restore_window = 0;

   if( Window_room == New_room ) Restore_window = 1;

   if( PreDefined_room != NO_ROOM )
    {
     if( Restore_window )
      {
       if( PreDefined_room != New_room ) Restore_window = 0;
      }
     else
      {
       if( PreDefined_room == New_room ) Restore_window = 1;
      }
    }

   if( Restore_window ) if( PermissionForSwitching( Window ) ) Restore_window = 0;
   if( Restore_window ) if( !Rooms_PermissionForRoomActions( Window ) ) Restore_window = 0;

   if( Restore_window )
    {
     // �᫨ ���� ������:
     if( WinIsWindowVisible( Window ) )
      {
       // ������, �뫮 �� ���� 㢥��祭�.
       BYTE Maximized = 0; FindProperty( Window, PRP_MAXIMIZED, &Maximized );

       // ���뫠�� ᮮ�饭�� � ����.
       if( !IsWindowsWindow( Window ) )
        {
         LONG Action = RESTORE_ACTION;
         if( Maximized ) Action = MAXIMIZE_ACTION;

         SetProperty( Window, PRP_PERFORMED_ACTION, &Action );
         PerformAction( Window, Action );
        }
       else
        {
         LONG Action = RESTORE_ACTION;

         SetProperty( Window, PRP_PERFORMED_ACTION, &Action );
         PerformAction( Window, Action );

         if( Maximized )
          {
           Action = MAXIMIZE_ACTION;

           SetProperty( Window, PRP_PERFORMED_ACTION, &Action );
           PerformAction( Window, Action );
          }
        }

       // ��ࠢ������ ⥪�⮢� ����, ����� �뫨 㢥��祭�.
       if( Maximized ) if( IsVIOWindow( Window ) )
        {
         // ���뫠�� � ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� ��ࠢ������.
         WinPostMsg( Window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) SM_ARRANGE_VIO_IN_ROOM );
        }
      }
     // � �᫨ ��� ����:
     else
      {
       // ������ ���� ������.
       // �� ���� ������ ��� ���� ODIN � ��� �� ����, � ������ �����⢥��� ����⢨�� �뫮 "����� ����".
       WinShowWindow( Window, 1 );
      }

     // ������ ���� ����㯭� ��� ��४��祭��.
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_JUMPABLE );
    }

   // �⮤������ ����� LaunchPad.
   if( IsLaunchPadWindow( Window ) ) WinSetWindowPos( Window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST );

   // ���뢠�� ᯨ᮪ ����.
   if( IsWinListWindow( Window ) ) PerformAction( Window, HIDE_ACTION );
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ���뢠�� ��� �����뢠�� ���� �����窨 ���

// Window - ���� �����窨, Show_window - ����� ��� �������� ����.
VOID Rooms_ShowShellWindow( HWND Window, BYTE Show_window )
{
 // �᫨ ���� �����窨 ���� �����:
 if( !Show_window )
  {
   // ������ �ᯮ������� ����.
   SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

   // �᫨ �� �����饥 ���� �����窨:
   if( Window == GetDetectedShellWindow() )
    {
     // �᫨ ��� �� ����:
     HWND Desktop = QueryDesktopWindow();

     INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
     INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

     INT New_X_placement = X_Screen * (-10);
     INT New_Y_placement = Y_Screen * (-10);

     if( Window_placement.x != New_X_placement )
      {
       // ���������� �ᯮ������� ����.
       Rooms.RTSettings.Shell_window_angle.x = Window_placement.x;
       Rooms.RTSettings.Shell_window_angle.y = Window_placement.y;

       // ��।������ ���� �� �।��� �࠭�. �������� ��� ��뢠�� ����
       // �����窨 ����� - ⮣�� ��� �ﭥ� �� ᮡ�� �� ��᪮�쪮 ����.
       WinSetWindowPos( Window, NULLHANDLE, New_X_placement, New_Y_placement, 0, 0, SWP_MOVE | SWP_NOADJUST );
      }
    }
  }
 // � �᫨ ���� �����窨 ���� ��������:
 else
  {
   // ��।������ ���� ���⭮.
   WinSetWindowPos( Window, NULLHANDLE, Rooms.RTSettings.Shell_window_angle.x, Rooms.RTSettings.Shell_window_angle.y, 0, 0, SWP_MOVE | SWP_NOADJUST );
  }
}

// ��� ��室�� ���⮥ ���� �����窨 � �����뢠�� ��� ���

VOID Rooms_RetrieveShellWindow( VOID )
{
 // ������, ��� �ᯮ������ ���� WarpCenter.
 BYTE WarpCenter_is_in_top = 1;

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� �� ���� � �� ���� WarpCenter:
   if( WinIsWindowVisible( Window ) ) if( IsWarpCenterWindow( Window ) )
    {
     // ������ �ᯮ������� ����.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // �஢��塞 �ᯮ������� ����.
     if( Window_placement.y <= 0 ) WarpCenter_is_in_top = 0;

     // �����蠥� ��ॡ�� ����.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 Enumeration = WinBeginEnumWindows( Desktop ); Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� �� ����:
   if( WinIsWindowVisible( Window ) )
    {
     // �᫨ �� ���� WPS:
     if( IsFolderWindow( Window ) )
      {
       // �᫨ ��� ����� ᢮��⢠ ���� �����窨 - ������ ����� �ᯮ������� ����.
       if( HasShellWindowControls( Window ) )
        {
         // �᫨ ���� WarpCenter �ᯮ������ ������:
         if( WarpCenter_is_in_top )
          {
           // ���� ������ 㣮� ���� ������ ��室��� �� �।��� �࠭�.
           INT Frame_width = FrameWidth( Window );
           Rooms.RTSettings.Shell_window_angle.x = Rooms.RTSettings.Shell_window_angle.y = Frame_width * (-1);
          }
         // � �᫨ ���� WarpCenter �ᯮ������ �����:
         else
          {
           // ������ ࠧ��� �࠭�.
           INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

           // ������ ����� ��������� ����.
           INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

           // ������ ࠧ��� ����.
           RECT Rectangle = {0}; WinQueryWindowRect( Window, &Rectangle );

           // ���� ������ 㣮� ���� ������ ������� ���� WarpCenter.
           INT Frame_width = FrameWidth( Window );
           Rooms.RTSettings.Shell_window_angle.x = Frame_width * (-1);

           INT Y_Top = Y_Screen + TitleBar_height + Frame_width;
           Rooms.RTSettings.Shell_window_angle.y = Y_Top - Rectangle.yTop;
          }

         // �����뢠�� ����.
         RememberShellWindow( Window ); Rooms_ShowShellWindow( Window, 1 );
        }
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ���室�� � ������� ���

// Room - ������, � ������ ���� ��३�.
VOID Rooms_GoToRoom( INT New_room )
{
 // �᫨ �������� ���� ᮮ�饭�� �� �訡�� - ������.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // ���.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // ������.
   return;
  }

 // �᫨ ������ � �� ᠬ��:
 if( New_room == GetCurrentOrNextRoom() )
  {
   // �᫨ �� ������ � ����� �����窨 � ��� ������㯭� - �஡㥬 �������� ���.
   if( ShellIsWPS() ) if( GetCurrentOrNextRoom() == SHELL_ROOM )
    if( !ShellIsAvailable() )
     if( WinIsWindow( WinQueryAnchorBlock( GetDetectedShellWindow() ), GetDetectedShellWindow() ) )
      Rooms_RetrieveShellWindow();

   // ������ ��࠭�� ���� � �।��� �࠭�.
   ActivateWindowInCenter();

   // ������.
   return;
  }

 // �᫨ �������� ���� WarpCenter - ���祬 ���.
 if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
  HideShellToolbarMenu( 1 );

 // �᫨ �ᯮ������ �����窠 WPS:
 if( ShellIsWPS() )
  {
   // ������ ���� �����窨.
   HWND Detected_shell_window = GetDetectedShellWindow();

   // �᫨ ���� �������� ������� � ����� �����窨 - ���������� ���.
   if( GetCurrentOrNextRoom() == SHELL_ROOM )
    {
     // �᫨ ��� ᥩ�� ������㯭� - ������.
     HWND Shell_window = QueryShellWindow();

     if( Shell_window == NULLHANDLE )
      {
       // �஡㥬 �������� ���� �����窨.
       if( WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
        Rooms_RetrieveShellWindow();

       // ������.
       return;
      }

     // ���������� ���� �����窨.
     RememberShellWindow( Shell_window );
    }

   // �᫨ ���� ��३� � ����� ������� � ���� �����窨 ��� - ������.
   if( New_room != SHELL_ROOM )
    if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
     {
      // ������.
      return;
     }

   // �᫨ ���� �������� � ������� � ����� �����窨 � ��� ��� - ���������� ����� ����.
   if( New_room == SHELL_ROOM )
    if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
     {
      // ����ਬ, ���� �� ����� ����.
      HWND Shell_window = QueryShellWindow();

      // �᫨ ��� ���� - ���������� ���.
      if( Shell_window != NULLHANDLE )
       {
        // ���������� ���� �����窨.
        RememberShellWindow( Shell_window );
        Rooms.RTSettings.Shell_window_angle.x = ROOMS_DO_NOT_RESTORE_WINDOW;
       }
      // � �᫨ ��� ��� - ������.
      else
       {
        // ���� �����窨 �������⭮.
        RememberShellWindow( NULLHANDLE );

        // ������.
        return;
       }
     }
  }

 // �� �६� ��४��祭�� ��⠥�, �� ������ �������⭠.
 INT Current_room = GetCurrentOrNextRoom(); SetCurrentAndNextRoom( NO_ROOM, New_room );

 // ���������� ⥪�饥 �६�, �⮡� �������� �ࠢ��쭮� ࠡ��� ��⮪�� ��᫥ ᬥ�� ������.
 RememberRoomsSwitchingTime(); Rooms.Settings.Synchronize_arranger_and_rooms = 1;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ��⠭�������� ����-�������� ������ ��� ����. ��� ����뢠�� �࠭, �� ��祣� �� ����.
 ShowCurtainWindow( Desktop );

 // ������� �ਮ���� ��� ��� �ਫ������.
 SetDynamicPriorityLevels( SDPL_SUPPRESS_ALL_PROCESSES );

 // �᫨ �ᯮ������ �����窠 WPS:
 if( ShellIsWPS() )
  {
   // �᫨ ���� ��३� � ������� � ����� �����窨 - �����뢠�� ���.
   // �� ���� ᤥ���� ��� ����� ࠭�� - �� ��砩, �᫨ ��⮪ ����᭥�.
   if( New_room == SHELL_ROOM )
    if( Rooms.RTSettings.Shell_window_angle.x != ROOMS_DO_NOT_RESTORE_WINDOW )
     Rooms_ShowShellWindow( GetDetectedShellWindow(), 1 );
  }

 // ������� ���� ����� ���� ����� ���짮��⥫��, ⮣�� ��� ����� �� �ᯮ������.
 // ��� ������� � ��㣮� ������, ����� ���� ��࠭� ���짮��⥫�� � ᯨ᪥ ����.
 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ����� ������ �� ᬥ�� ������:
   if( Rooms_PermissionForRoomActions( Window ) )
    {
     // ������ �������, � ���ன �ᯮ������ ����.
     INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

     // �᫨ ��� �ᯮ������ � �⮩ ������ � �뫮 㬥��襭� ��� ���� - ���뢠�� ᢮��⢮.
     // �᫨ ���� �� �ᯮ������ �� � ����� ������ � � ���� ����� ��४������� - ���뢠�� ᢮��⢮.
     if( Window_room == Current_room || !Window_room )
      if( !PermissionForSwitching( Window ) )
       {
        // ���������� �������.
        INT Room = Rooms_GetMostSuitableRoom( Window ); Rooms_SetRoomProperty( Window, Room );

        // �⮤������ ���� �� �� ��⠫�� ����.
        WinSetWindowPos( Window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );

        // ������ ���� ������㯭� ��� ��४��祭��.
        WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
       }

     // �᫨ ���� �� �ᯮ������ �� � ����� ������ � � ���� ����� ��४������� - ��⠥�,
     // �� ��� �ᯮ������ � �⮩ ������. �� �뢠��, ����� ����ன�� ����砥��� �� �६� ࠡ���.
     if( !Window_room )
      if( PermissionForSwitching( Window ) )
       {
        // ���������� �������.
        Rooms_SetRoomProperty( Window, Current_room );

        // ������ ���� ������㯭� ��� ��४��祭��.
        WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_JUMPABLE );
       }
    }
  }
 WinEndEnumWindows( Enumeration );

 // ���塞 ����� ����.
 LONG Animation_is_allowed = WinQuerySysValue( Desktop, SV_ANIMATION );
 if( Animation_is_allowed ) WinSetSysValue( Desktop, SV_ANIMATION, 0 );

 Rooms_ChangeWindowSet( Desktop, New_room, Current_room );

 if( Animation_is_allowed ) WinSetSysValue( Desktop, SV_ANIMATION, 1 );

 // �᫨ �ᯮ������ �����窠 WPS:
 if( ShellIsWPS() )
  {
   // �᫨ ���� �������� ������� � ����� �����窨 - ��뢠�� ���.
   if( New_room != SHELL_ROOM )
    Rooms_ShowShellWindow( GetDetectedShellWindow(), 0 );
  }

 // ���塞 ����ࠦ���� ��� ����訢���� ���������.
 if( DifferentTitleBarImagesAreRequired() ) CreateTitleBarImages();

 // ���塞 ���⠢�� ��� ࠡ�祣� �⮫�.
 if( Rooms.Settings.Draw_wallpaper )
  {
   if( New_room != SHELL_ROOM )
    Rooms_CreateDesktopWallpaper( Desktop, New_room );
   else
    Rooms_DeleteDesktopWallpaper();
  }

 // ���뢠�� ����-��������, � �᫨ ��� 㦥 �뫠 ���� - ������塞 ���� ࠡ�祣� �⮫�.
 if( WinIsWindowVisible( CurtainWindow() ) ) HideCurtainWindow();
 else WinInvalidateRect( Desktop, NULL, 0 );

 // ���������� ����� �������.
 SetCurrentAndNextRoom( New_room, NO_ROOM );

 // ��⠭�������� ��४���⥫� �� ���������.
 WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // �᢮������� 㪠��⥫� ���.
 ResetPointer();

 // ���� ᤥ���� ��࠭�� ���� � �।��� �࠭�.
 WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_RETARD_AND_ACTIVATE, 0, 0 );

 // �᫨ �ᯮ������ �����窠 WPS:
 if( ShellIsWPS() )
  {
   // �� ���室� � ������� � ����� �����窨 ��� ����� ���� ���� - ��� ���� 㤥ন���� �����஥ �६�.
   if( New_room == SHELL_ROOM ) WinPostQueueMsg( Enhancer.Modules.Rooms->Message_queue, SM_HOLD_SHELL_WINDOW, 0, 0 );
  }

 // ������.
 return;
}

// ��� �஢���� ����, ���஥ �⠭������ ��࠭�� ���

// Frame_window - ����, ���஥ ���� �஢����.
VOID Rooms_CheckActivatedWindow( HWND Frame_window )
{
 // �᫨ ���� �ᯮ������ ⠪ ��, ��� ���� �����窨 - ���� ������ ���.
 BYTE Shell_is_changed = 0;

 // ������ �ᯮ������� ����.
 SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

 // �஢��塞 ����.
 if( HasShellPlacement( Frame_window, &Window_placement ) ) Shell_is_changed = 1;

 // �᫨ �� ���� �����窨 - ���� ᤥ���� ��࠭�� ��㣮� ����.
 HWND Detected_shell_window = GetDetectedShellWindow();
 BYTE Shell_is_selected = 0;
 if( !Shell_is_changed ) if( Frame_window == Detected_shell_window ) Shell_is_selected = 1;

 // �᫨ ���� �����窨 ��� - ���������� ����� ����.
 if( Shell_is_changed )
  if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
   RememberShellWindow( Frame_window );

 // �᫨ �������� ���� WarpCenter - �� ����� �����, ������.
 if( SystemWindowIsPresent( FIND_WARPCENTER, FIND_VISIBLE_WINDOW ) ) return;

 // ���祬 ���� � �롨ࠥ� ���� � �।��� �࠭�.
 if( Shell_is_changed ) Rooms_ShowShellWindow( Frame_window, 0 );
 if( Shell_is_changed || Shell_is_selected ) ActivateWindowInCenter();

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Rooms_RoomsMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Rooms->Priority = MAKELONG( Class, Delta );
  }

 // ���室�� � �������.
 if( Message->msg == SM_GO_TO_ROOM )
  {
   // ����, ���� ���� �� �⠭�� ᢮�����.
   while( MouseIsBusy() ) Retard();

   // ������ �������.
   INT Room = (INT) Message->mp1;

   // ���室�� � ���.
   Rooms_GoToRoom( Room );
  }

 // ���ন���� ���� �����窨 ��᫥ ᬥ�� ������.
 if( Message->msg == SM_HOLD_SHELL_WINDOW )
  {
   // ���������� ���� �����窨.
   HWND Shell_window = GetDetectedShellWindow();

   // �஢��塞 ���.
   for( INT Count = 0; Count < Rooms.Constants.Retards_after_room_change; Count ++ )
    {
     // ���� �����஥ �६�.
     Retard();

     // �᫨ ���� �����窨 ��� - �����蠥� �஢�ન.
     if( !WinIsWindow( WinQueryAnchorBlock( Shell_window ), Shell_window ) ) break;

     // �᫨ ���� �����窨 ������㯭� - �஡㥬 �������� ���.
     if( !ShellIsAvailable() ) Rooms_RetrieveShellWindow();

     // ��१ ��᪮�쪮 蠣�� - 㬥��蠥� �ਮ���.
     if( Count == 3 ) DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );
    }

   // ����⠭�������� �ਮ���.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.Rooms->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.Rooms->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );
  }

 // �஢��塞 ����, ���஥ �⠭������ ��࠭��.
 if( Message->msg == SM_CHECK_WINDOW )
  {
   // ������ ����, ���஥ ���� �஢����.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // �஢��塞 ����.
   Rooms_CheckActivatedWindow( Frame_window );
  }

 // ����訢��� ���� ࠡ�祣� �⮫�. �� ���� ������ � ⮬ �� ��⮪�, ����� ����� ���⠢��.
 if( Message->msg == SM_FILL_DESKTOP )
  {
   // ������ ����, ���஥ ���� �������.
   HWND Desktop = (HWND) Message->mp1;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Desktop ), Desktop ) ) return;

   // �����蠥� �ਮ���.
   DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

   // ����訢��� ࠡ�稩 �⮫.
   Rooms_FillDesktop( Desktop );

   // ����⠭�������� �ਮ���.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.Rooms->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.Rooms->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ���室� ����� �����⠬� ���

VOID Rooms_RoomsThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Rooms->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Rooms->Message_queue == NULLHANDLE )
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
   Rooms_RoomsMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}

