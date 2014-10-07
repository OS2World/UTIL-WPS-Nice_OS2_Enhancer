
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Rooms_Tune( HINI Ini_file )
{
 // ���������� ����ࠦ���� ��� ������.
 CHAR Shell_wallpaper[ SIZE_OF_PATH ] = "";    strcpy( Shell_wallpaper, Rooms.Settings.Wallpaper_for_shell_room );
 CHAR Northern_wallpaper[ SIZE_OF_PATH ] = ""; strcpy( Northern_wallpaper, Rooms.Settings.Wallpaper_for_northern_room );
 CHAR Western_wallpaper[ SIZE_OF_PATH ] = "";  strcpy( Western_wallpaper, Rooms.Settings.Wallpaper_for_western_room );
 CHAR Eastern_wallpaper[ SIZE_OF_PATH ] = "";  strcpy( Eastern_wallpaper, Rooms.Settings.Wallpaper_for_eastern_room );
 CHAR Southern_wallpaper[ SIZE_OF_PATH ] = ""; strcpy( Southern_wallpaper, Rooms.Settings.Wallpaper_for_southern_room );

 // ��⠥� ����ன��.
 Rooms_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Rooms_ReadSettings( Ini_file );

 // �஢��塞 ����� 䠩��� ��� ���⠢��.
 for( INT Count = 0; Count < 5; Count ++ )
  {
   // �롨ࠥ� ��� 䠩��.
   PCHAR Wallpaper = NULL;
   if( Count == 0 ) Wallpaper = Rooms.Settings.Wallpaper_for_shell_room;
   if( Count == 1 ) Wallpaper = Rooms.Settings.Wallpaper_for_northern_room;
   if( Count == 2 ) Wallpaper = Rooms.Settings.Wallpaper_for_western_room;
   if( Count == 3 ) Wallpaper = Rooms.Settings.Wallpaper_for_eastern_room;
   if( Count == 4 ) Wallpaper = Rooms.Settings.Wallpaper_for_southern_room;

   // �᫨ 䠩� ������ �ᯮ�������� � ��⠫��� ����⥫�:
   CHAR Old_style_name[ SIZE_OF_PATH ] = "";
   strcpy( Old_style_name, "\\Enhancer\\Bitmap\\" );
   strcat( Old_style_name, FindNameInPath( Wallpaper ) );

   if( stristr( Old_style_name, Wallpaper ) )
    {
     // ������ �����騩 ����.
     CHAR New_path[ SIZE_OF_PATH ] = "";

     GetCurrentPath( New_path );
     strcat( New_path, "\\Bitmap\\Rooms\\" );
     strcat( New_path, FindNameInPath( Wallpaper ) );

     strcpy( Wallpaper, New_path );
    }
  }

 // �᫨ ������� �⪫�祭�:
 if( !Rooms.Settings.Create_Rooms )
  if( GetCurrentOrNextRoom() != SHELL_ROOM )
   {
    // ���室�� � ������� � ����� �����窨.
    Rooms_GoToRoom( SHELL_ROOM );

    // ������ �� ���� ����㯭묨 ��� ��४��祭��.
    SetAllWindowsJumpable( QueryDesktopWindow() );
   }

 // �᫨ ������� ����祭� � ���⠢�� �������� - ��⠭�������� ���⠢�� ��� ࠡ�祣� �⮫�.
 if( Rooms.Settings.Create_Rooms ) if( Rooms.Settings.Draw_wallpaper )
  {
   // ����ਬ, ���� �� ����訢��� ���� ࠡ�祣� �⮫�.
   BYTE Redraw_desktop = 0;

   // �᫨ �����窠 WPS �� �ᯮ������ - ���� ᮧ���� ����ࠦ���� � ������� ࠡ�稩 �⮫.
   if( !ShellIsWPS() )
    if( GetCurrentOrNextRoom() == SHELL_ROOM )
     if( Rooms.RTSettings.Wallpaper == NULLHANDLE )
      {
       Rooms_CreateDesktopWallpaper( QueryDesktopWindow(), SHELL_ROOM );
       Redraw_desktop = 1;
      }

   // �᫨ ����ࠦ���� ���������� - ���� ᮧ���� ����ࠦ���� ������ � ������� ࠡ�稩 �⮫.
   if( !stric( Shell_wallpaper, Rooms.Settings.Wallpaper_for_shell_room )       ||
       !stric( Northern_wallpaper, Rooms.Settings.Wallpaper_for_northern_room ) ||
       !stric( Western_wallpaper, Rooms.Settings.Wallpaper_for_western_room )   ||
       !stric( Eastern_wallpaper, Rooms.Settings.Wallpaper_for_eastern_room )   ||
       !stric( Southern_wallpaper, Rooms.Settings.Wallpaper_for_southern_room ) )
     {
      Rooms_CreateDesktopWallpaper( QueryDesktopWindow(), GetCurrentOrNextRoom() );
      Redraw_desktop = 1;
     }

   if( Redraw_desktop ) Rooms_FillDesktop( QueryDesktopWindow() );
  }

 // �᫨ ���� �����窨 �뫮 ���� �� �।��饬 ����᪥ - �����뢠�� ���.
 if( Rooms.Settings.Create_Rooms ) if( !ShellIsAvailable() ) Rooms_RetrieveShellWindow();

 // ����������, �� ��⮪ ������ ���� ᮧ���.
 if( Rooms.Settings.Create_Rooms ) Enhancer.Modules.Rooms->Required = 1;

 // ������.
 return;
}
