
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Rooms_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &Rooms.Settings.Allocations, sizeof( ALLOCATIONS ) );
   bzero( &Rooms.Settings.Exceptions, sizeof( ROOMS_EXCEPTIONS ) );
  }

 if( Division == SET_ALL_SETTINGS || Division == SET_ROOMS )
  {
   Rooms.Settings.Create_Rooms = 0;
   Rooms.Settings.Allocate_windows_to_Rooms = 0;
   Rooms.Settings.Allocate_known_applications = 0;
   Rooms.Settings.Draw_wallpaper = 1;
   Rooms.Settings.Switch_by_WarpCenter = 1;
   Rooms.Settings.Switch_by_keyboard = 1;
   Rooms.Settings.Synchronize_arranger_and_rooms = 1;

   {
    CHAR Current_directory[ SIZE_OF_PATH ] = ""; GetCurrentPath( Current_directory );

    strcpy( Rooms.Settings.Wallpaper_for_shell_room, Current_directory );
    strcat( Rooms.Settings.Wallpaper_for_shell_room, "\\Bitmap\\WPShell\\Forest.bmp" );

    strcpy( Rooms.Settings.Wallpaper_for_northern_room, Current_directory );
    strcat( Rooms.Settings.Wallpaper_for_northern_room, "\\Bitmap\\Rooms\\Forward-cloth.bmp" );
    strcpy( Rooms.Settings.Wallpaper_for_western_room, Current_directory );
    strcat( Rooms.Settings.Wallpaper_for_western_room, "\\Bitmap\\Rooms\\Left-nature.bmp" );
    strcpy( Rooms.Settings.Wallpaper_for_eastern_room, Current_directory );
    strcat( Rooms.Settings.Wallpaper_for_eastern_room, "\\Bitmap\\Rooms\\Right-stone.bmp" );
    strcpy( Rooms.Settings.Wallpaper_for_southern_room, Current_directory );
    strcat( Rooms.Settings.Wallpaper_for_southern_room, "\\Bitmap\\Rooms\\Backward-cloth.bmp" );
   }
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Rooms_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Int = 0; ULONG Path = 0; ULONG Name = 0; ULONG Byte_data = 0; ULONG Int_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Create Rooms", &Byte_data, &Byte ) ) Rooms.Settings.Create_Rooms = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Attach windows to Rooms", &Byte_data, &Byte ) ) Rooms.Settings.Allocate_windows_to_Rooms = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Attach known applications", &Byte_data, &Byte ) ) Rooms.Settings.Allocate_known_applications = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Draw wallpaper", &Byte_data, &Byte ) ) Rooms.Settings.Draw_wallpaper = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Switch by WarpCenter", &Byte_data, &Byte ) ) Rooms.Settings.Switch_by_WarpCenter = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Switch by keyboard", &Byte_data, &Byte ) ) Rooms.Settings.Switch_by_keyboard = Byte_data;

 {
  CHAR Item[ SIZE_OF_PATH ] = "";

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "Wallpaper for shell room", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Wallpaper_for_shell_room, Item ); Item[ 0 ] = 0; }

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "Wallpaper for northern room", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Wallpaper_for_northern_room, Item ); Item[ 0 ] = 0; }

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "Wallpaper for western room", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Wallpaper_for_western_room, Item ); Item[ 0 ] = 0; }

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "Wallpaper for eastern room", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Wallpaper_for_eastern_room, Item ); Item[ 0 ] = 0; }

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "Wallpaper for southern room", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Wallpaper_for_southern_room, Item ); Item[ 0 ] = 0; }
 }

 {
  CHAR Item[ SIZE_OF_PATH ] = "";

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 1 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_1_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 2 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_2_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 3 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_3_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 4 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_4_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 5 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_5_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 6 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_6_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 7 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_7_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Allocations", "Unit 8 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( Rooms.Settings.Allocations.Unit_8_name, Item ); Item[ 0 ] = 0; }
 }

 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 1", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_1 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 2", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_2 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 3", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_3 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 4", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_4 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 5", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_5 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 6", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_6 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 7", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_7 = Int_data;
 Int = sizeof( INT ); if( PrfQueryProfileData( Ini_file, "Allocations", "Preferable room 8", &Int_data, &Int ) ) Rooms.Settings.Allocations.Preferable_room_8 = Int_data;

 // Читаем список исключений.
 {
  CHAR Item[ SIZE_OF_NAME ] = "";

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 1", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_1, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 2", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_2, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 3", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_3, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 4", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_4, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 5", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_5, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 6", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_6, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 7", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_7, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rooms 8", Item, &Name ); strcpy( Rooms.Settings.Exceptions.Rooms_8, Item ); Item[ 0 ] = 0;
 }

 // Возврат.
 return;
}
