
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Rooms_Tune( HINI Ini_file )
{
 // Запоминаем изображения для комнат.
 CHAR Shell_wallpaper[ SIZE_OF_PATH ] = "";    strcpy( Shell_wallpaper, Rooms.Settings.Wallpaper_for_shell_room );
 CHAR Northern_wallpaper[ SIZE_OF_PATH ] = ""; strcpy( Northern_wallpaper, Rooms.Settings.Wallpaper_for_northern_room );
 CHAR Western_wallpaper[ SIZE_OF_PATH ] = "";  strcpy( Western_wallpaper, Rooms.Settings.Wallpaper_for_western_room );
 CHAR Eastern_wallpaper[ SIZE_OF_PATH ] = "";  strcpy( Eastern_wallpaper, Rooms.Settings.Wallpaper_for_eastern_room );
 CHAR Southern_wallpaper[ SIZE_OF_PATH ] = ""; strcpy( Southern_wallpaper, Rooms.Settings.Wallpaper_for_southern_room );

 // Читаем настройки.
 Rooms_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Rooms_ReadSettings( Ini_file );

 // Проверяем имена файлов для заставок.
 for( INT Count = 0; Count < 5; Count ++ )
  {
   // Выбираем имя файла.
   PCHAR Wallpaper = NULL;
   if( Count == 0 ) Wallpaper = Rooms.Settings.Wallpaper_for_shell_room;
   if( Count == 1 ) Wallpaper = Rooms.Settings.Wallpaper_for_northern_room;
   if( Count == 2 ) Wallpaper = Rooms.Settings.Wallpaper_for_western_room;
   if( Count == 3 ) Wallpaper = Rooms.Settings.Wallpaper_for_eastern_room;
   if( Count == 4 ) Wallpaper = Rooms.Settings.Wallpaper_for_southern_room;

   // Если файл должен располагаться в каталоге расширителя:
   CHAR Old_style_name[ SIZE_OF_PATH ] = "";
   strcpy( Old_style_name, "\\Enhancer\\Bitmap\\" );
   strcat( Old_style_name, FindNameInPath( Wallpaper ) );

   if( stristr( Old_style_name, Wallpaper ) )
    {
     // Задаем настоящий путь.
     CHAR New_path[ SIZE_OF_PATH ] = "";

     GetCurrentPath( New_path );
     strcat( New_path, "\\Bitmap\\Rooms\\" );
     strcat( New_path, FindNameInPath( Wallpaper ) );

     strcpy( Wallpaper, New_path );
    }
  }

 // Если комнаты отключены:
 if( !Rooms.Settings.Create_Rooms )
  if( GetCurrentOrNextRoom() != SHELL_ROOM )
   {
    // Переходим в комнату с окном оболочки.
    Rooms_GoToRoom( SHELL_ROOM );

    // Делаем все окна доступными для переключения.
    SetAllWindowsJumpable( QueryDesktopWindow() );
   }

 // Если комнаты включены и заставка изменена - устанавливаем заставку для рабочего стола.
 if( Rooms.Settings.Create_Rooms ) if( Rooms.Settings.Draw_wallpaper )
  {
   // Смотрим, надо ли закрашивать окно рабочего стола.
   BYTE Redraw_desktop = 0;

   // Если оболочка WPS не используется - надо создать изображение и закрасить рабочий стол.
   if( !ShellIsWPS() )
    if( GetCurrentOrNextRoom() == SHELL_ROOM )
     if( Rooms.RTSettings.Wallpaper == NULLHANDLE )
      {
       Rooms_CreateDesktopWallpaper( QueryDesktopWindow(), SHELL_ROOM );
       Redraw_desktop = 1;
      }

   // Если изображение изменилось - надо создать изображения заново и закрасить рабочий стол.
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

 // Если окно оболочки было скрыто при предыдущем запуске - показываем его.
 if( Rooms.Settings.Create_Rooms ) if( !ShellIsAvailable() ) Rooms_RetrieveShellWindow();

 // Запоминаем, что поток должен быть создан.
 if( Rooms.Settings.Create_Rooms ) Enhancer.Modules.Rooms->Required = 1;

 // Возврат.
 return;
}
