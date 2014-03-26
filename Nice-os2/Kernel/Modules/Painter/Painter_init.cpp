
// ─── Задает настройки для рисования на основе выбранной темы ───

VOID Painter_SetDrawingRules( VOID )
{
 // Задаем правила в зависимости от темы.
 switch( Painter.Settings.Theme )
  {
   case PAINTER_THEME_ECOMSTATION:
    {
     Painter.Settings.Draw_normal_frames = 0;
     Painter.Settings.Draw_const_frames = 0;
     Painter.Settings.Draw_point_frames = 0;
     Painter.Settings.Draw_flat_frames = 0;
     Painter.Settings.Draw_volume_lines = 0;
     Painter.Settings.Draw_system_menus = 0;
     Painter.Settings.Draw_titles = 1;
     Painter.Settings.Draw_menus = 0;
     Painter.Settings.Draw_buttons = 0;
    }
   break;

   case PAINTER_THEME_CLASSIC_GRAY:
   case PAINTER_THEME_CLASSIC_RGB:
    {
     Painter.Settings.Draw_normal_frames = 1;
     Painter.Settings.Draw_const_frames = 1;
     Painter.Settings.Draw_point_frames = 1;
     Painter.Settings.Draw_flat_frames = 1;
     Painter.Settings.Draw_volume_lines = 1;
     Painter.Settings.Draw_system_menus = 1;
     Painter.Settings.Draw_titles = 1;
     Painter.Settings.Draw_menus = 1;
     Painter.Settings.Draw_buttons = 1;
    }
   break;

   case PAINTER_THEME_WHITE_SNOW:
    {
     Painter.Settings.Draw_normal_frames = 1;
     Painter.Settings.Draw_const_frames = 1;
     Painter.Settings.Draw_point_frames = 1;
     Painter.Settings.Draw_flat_frames = 1;
     Painter.Settings.Draw_volume_lines = 0;
     Painter.Settings.Draw_system_menus = 1;
     Painter.Settings.Draw_titles = 1;
     Painter.Settings.Draw_menus = 0;
     Painter.Settings.Draw_buttons = 1;
    }
   break;
  }

 // Возврат.
 return;
}

// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID Painter_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &Painter.Settings.Exceptions, sizeof( PAINTER_EXCEPTIONS ) );
  }

 if( Division == SET_ALL_SETTINGS || Division == SET_DRAWING )
  {
   Painter.Settings.Draw_frames = 0;

   Painter.Settings.Accelerate_folders_closing = 1;
   Painter.Settings.Rollup_VIO_windows = 0;
   Painter.Settings.Keep_frame_colors = 1;

   Painter.Settings.Theme = PAINTER_THEME_ECOMSTATION; Painter_SetDrawingRules();

   GetCurrentPath( Painter.Settings.TitleBar_pattern );
   strcat( Painter.Settings.TitleBar_pattern, "\\Bitmap\\Themes\\Clouds.bmp" );
  }

 // Задаем цвета для заголовков окон.
 if( Division == SET_ALL_SETTINGS || Division == SET_ROOMS || Division == SET_DRAWING )
  {
   INT LLL = 255; INT LL = 204; INT L = 160; INT DDD =  96; INT DD =  64; INT D =  32;
   INT XXX = 252; INT XX = 192; INT X = 128; INT III = 242; INT II = 224; INT I = 192;

   // Цвета для текста и заполнения заголовков.
   Painter.Settings.AT_Text_color          = MAKERGB( LLL, LLL,  LL );
   Painter.Settings.Northern_AT_Text_color = MAKERGB( XXX, XXX, LLL );
   Painter.Settings.Western_AT_Text_color  = MAKERGB( XXX, LLL, XXX );
   Painter.Settings.Eastern_AT_Text_color  = MAKERGB( XXX, LLL, LLL );
   Painter.Settings.Southern_AT_Text_color = MAKERGB( LLL, LLL, XXX );

   Painter.Settings.AT_Background_color          = MAKERGB(  DD,   0,   0 );
   Painter.Settings.Northern_AT_Background_color = MAKERGB(   0,   0,  DD );
   Painter.Settings.Western_AT_Background_color  = MAKERGB(   0,  DD,   0 );
   Painter.Settings.Eastern_AT_Background_color  = MAKERGB(   0,  DD,  DD );
   Painter.Settings.Southern_AT_Background_color = MAKERGB(  DD,  DD,   0 );

   Painter.Settings.IT_Text_color          = MAKERGB(   0,   0,   0 );
   Painter.Settings.Northern_IT_Text_color = MAKERGB(   0,   0,   0 );
   Painter.Settings.Western_IT_Text_color  = MAKERGB(   0,   0,   0 );
   Painter.Settings.Eastern_IT_Text_color  = MAKERGB(   0,   0,   0 );
   Painter.Settings.Southern_IT_Text_color = MAKERGB(   0,   0,   0 );

   Painter.Settings.IT_Background_color          = MAKERGB(  LL,  LL,  LL );
   Painter.Settings.Northern_IT_Background_color = MAKERGB(  LL,  LL,  LL );
   Painter.Settings.Western_IT_Background_color  = MAKERGB(  LL,  LL,  LL );
   Painter.Settings.Eastern_IT_Background_color  = MAKERGB(  LL,  LL,  LL );
   Painter.Settings.Southern_IT_Background_color = MAKERGB(  LL,  LL,  LL );

   // Цвета для заголовков по краям.
   Painter.Settings.AT_Color_1          = MAKERGB(  D,  D,  D );
   Painter.Settings.AT_Color_3          = MAKERGB(  D,  D,  D );
   Painter.Settings.Northern_AT_Color_1 = MAKERGB(  D,  D,  D );
   Painter.Settings.Northern_AT_Color_3 = MAKERGB(  D,  D,  D );
   Painter.Settings.Western_AT_Color_1  = MAKERGB(  D,  D,  D );
   Painter.Settings.Western_AT_Color_3  = MAKERGB(  D,  D,  D );
   Painter.Settings.Eastern_AT_Color_1  = MAKERGB(  D,  D,  D );
   Painter.Settings.Eastern_AT_Color_3  = MAKERGB(  D,  D,  D );
   Painter.Settings.Southern_AT_Color_1 = MAKERGB(  D,  D,  D );
   Painter.Settings.Southern_AT_Color_3 = MAKERGB(  D,  D,  D );

   Painter.Settings.IT_Color_1          = MAKERGB( LL, LL, LL );
   Painter.Settings.IT_Color_3          = MAKERGB( LL, LL, LL );
   Painter.Settings.Northern_IT_Color_1 = MAKERGB( LL, LL, LL );
   Painter.Settings.Northern_IT_Color_3 = MAKERGB( LL, LL, LL );
   Painter.Settings.Western_IT_Color_1  = MAKERGB( LL, LL, LL );
   Painter.Settings.Western_IT_Color_3  = MAKERGB( LL, LL, LL );
   Painter.Settings.Eastern_IT_Color_1  = MAKERGB( LL, LL, LL );
   Painter.Settings.Eastern_IT_Color_3  = MAKERGB( LL, LL, LL );
   Painter.Settings.Southern_IT_Color_1 = MAKERGB( LL, LL, LL );
   Painter.Settings.Southern_IT_Color_3 = MAKERGB( LL, LL, LL );

   // В каждой комнате - свои цвета.
   {
    Painter.Settings.AT_Color_2          = MAKERGB(   0,  LL,  LL );
    Painter.Settings.IT_Color_2          = MAKERGB(  LL, LLL, LLL );

    Painter.Settings.Northern_AT_Color_2 = MAKERGB(   0,   L,  LL );
    Painter.Settings.Northern_IT_Color_2 = MAKERGB(  LL, III, LLL );

    Painter.Settings.Western_AT_Color_2  = MAKERGB(   0,   L,  DD );
    Painter.Settings.Western_IT_Color_2  = MAKERGB(   I, III,   I );

    Painter.Settings.Eastern_AT_Color_2  = MAKERGB(   0,  LL,   L );
    Painter.Settings.Eastern_IT_Color_2  = MAKERGB(  LL, LLL, III );

    Painter.Settings.Southern_AT_Color_2 = MAKERGB(  LL,   X,  DD );
    Painter.Settings.Southern_IT_Color_2 = MAKERGB( III,  II,   I );
   }
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Painter_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Int = 0; ULONG Long = 0; ULONG Name = 0; ULONG Path = 0; ULONG Byte_data = 0; ULONG Int_data = 0; ULONG Long_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Draw frames", &Byte_data, &Byte ) ) Painter.Settings.Draw_frames = Byte_data;
 Int  = sizeof( INT );  if( PrfQueryProfileData( Ini_file, "Settings", "Theme", &Int_data, &Int ) ) Painter.Settings.Theme = Int_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Accelerate folders closing", &Byte_data, &Byte ) ) Painter.Settings.Accelerate_folders_closing = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Rollup VIO windows", &Byte_data, &Byte ) ) Painter.Settings.Rollup_VIO_windows = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Keep frame colors", &Byte_data, &Byte ) ) Painter.Settings.Keep_frame_colors = Byte_data;

 {
  CHAR Item[ SIZE_OF_PATH ] = "";

  Path = SIZE_OF_PATH; PrfQueryProfileData( Ini_file, "Settings", "TitleBar pattern", Item, &Path );
  if( Item[ 0 ] != 0 ) { strcpy( Painter.Settings.TitleBar_pattern, Item ); Item[ 0 ] = 0; }
 }

 // Читаем цвета.
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "AT Text color", &Long_data, &Long ) ) Painter.Settings.AT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "AT Background color", &Long_data, &Long ) ) Painter.Settings.AT_Background_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "IT Text color", &Long_data, &Long ) ) Painter.Settings.IT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "IT Background color", &Long_data, &Long ) ) Painter.Settings.IT_Background_color = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern AT Text color", &Long_data, &Long ) ) Painter.Settings.Northern_AT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern IT Text color", &Long_data, &Long ) ) Painter.Settings.Northern_IT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern AT Background color", &Long_data, &Long ) ) Painter.Settings.Northern_AT_Background_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern IT Background color", &Long_data, &Long ) ) Painter.Settings.Northern_IT_Background_color = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western AT Text color", &Long_data, &Long ) ) Painter.Settings.Western_AT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western IT Text color", &Long_data, &Long ) ) Painter.Settings.Western_IT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western AT Background color", &Long_data, &Long ) ) Painter.Settings.Western_AT_Background_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western IT Background color", &Long_data, &Long ) ) Painter.Settings.Western_IT_Background_color = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern AT Text color", &Long_data, &Long ) ) Painter.Settings.Eastern_AT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern IT Text color", &Long_data, &Long ) ) Painter.Settings.Eastern_IT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern AT Background color", &Long_data, &Long ) ) Painter.Settings.Eastern_AT_Background_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern IT Background color", &Long_data, &Long ) ) Painter.Settings.Eastern_IT_Background_color = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern AT Text color", &Long_data, &Long ) ) Painter.Settings.Southern_AT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern IT Text color", &Long_data, &Long ) ) Painter.Settings.Southern_IT_Text_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern AT Background color", &Long_data, &Long ) ) Painter.Settings.Southern_AT_Background_color = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern IT Background color", &Long_data, &Long ) ) Painter.Settings.Southern_IT_Background_color = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "AT Color 1", &Long_data, &Long ) ) Painter.Settings.AT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "AT Color 2", &Long_data, &Long ) ) Painter.Settings.AT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "AT Color 3", &Long_data, &Long ) ) Painter.Settings.AT_Color_3 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "IT Color 1", &Long_data, &Long ) ) Painter.Settings.IT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "IT Color 2", &Long_data, &Long ) ) Painter.Settings.IT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "IT Color 3", &Long_data, &Long ) ) Painter.Settings.IT_Color_3 = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern AT Color 1", &Long_data, &Long ) ) Painter.Settings.Northern_AT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern AT Color 2", &Long_data, &Long ) ) Painter.Settings.Northern_AT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern AT Color 3", &Long_data, &Long ) ) Painter.Settings.Northern_AT_Color_3 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern IT Color 1", &Long_data, &Long ) ) Painter.Settings.Northern_IT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern IT Color 2", &Long_data, &Long ) ) Painter.Settings.Northern_IT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Northern IT Color 3", &Long_data, &Long ) ) Painter.Settings.Northern_IT_Color_3 = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western AT Color 1", &Long_data, &Long ) ) Painter.Settings.Western_AT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western AT Color 2", &Long_data, &Long ) ) Painter.Settings.Western_AT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western AT Color 3", &Long_data, &Long ) ) Painter.Settings.Western_AT_Color_3 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western IT Color 1", &Long_data, &Long ) ) Painter.Settings.Western_IT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western IT Color 2", &Long_data, &Long ) ) Painter.Settings.Western_IT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Western IT Color 3", &Long_data, &Long ) ) Painter.Settings.Western_IT_Color_3 = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern AT Color 1", &Long_data, &Long ) ) Painter.Settings.Eastern_AT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern AT Color 2", &Long_data, &Long ) ) Painter.Settings.Eastern_AT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern AT Color 3", &Long_data, &Long ) ) Painter.Settings.Eastern_AT_Color_3 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern IT Color 1", &Long_data, &Long ) ) Painter.Settings.Eastern_IT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern IT Color 2", &Long_data, &Long ) ) Painter.Settings.Eastern_IT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Eastern IT Color 3", &Long_data, &Long ) ) Painter.Settings.Eastern_IT_Color_3 = Long_data;

 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern AT Color 1", &Long_data, &Long ) ) Painter.Settings.Southern_AT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern AT Color 2", &Long_data, &Long ) ) Painter.Settings.Southern_AT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern AT Color 3", &Long_data, &Long ) ) Painter.Settings.Southern_AT_Color_3 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern IT Color 1", &Long_data, &Long ) ) Painter.Settings.Southern_IT_Color_1 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern IT Color 2", &Long_data, &Long ) ) Painter.Settings.Southern_IT_Color_2 = Long_data;
 Long = sizeof( LONG ); if( PrfQueryProfileData( Ini_file, "Drawing", "Southern IT Color 3", &Long_data, &Long ) ) Painter.Settings.Southern_IT_Color_3 = Long_data;

 // Читаем список исключений.
 {
  CHAR Item[ SIZE_OF_NAME ] = "";

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 1", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_1, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 2", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_2, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 3", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_3, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 4", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_4, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 5", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_5, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 6", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_6, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 7", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_7, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Drawing 8", Item, &Name ); strcpy( Painter.Settings.Exceptions.Drawing_8, Item ); Item[ 0 ] = 0;

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 1", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_1, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 2", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_2, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 3", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_3, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 4", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_4, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 5", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_5, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 6", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_6, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 7", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_7, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "BorderDrawing 8", Item, &Name ); strcpy( Painter.Settings.Exceptions.BorderDrawing_8, Item ); Item[ 0 ] = 0;

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 1", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_1, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 2", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_2, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 3", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_3, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 4", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_4, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 5", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_5, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 6", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_6, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 7", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_7, Item ); Item[ 0 ] = 0;
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "ExceptionList", "Rolling 8", Item, &Name ); strcpy( Painter.Settings.Exceptions.Rolling_8, Item ); Item[ 0 ] = 0;
 }

 // Возврат.
 return;
}

// ─── Читает настройки для того, чтобы показывать их в окне выбора цвета "Комнатах" ───

// Ini_file - файл настроек.
VOID Painter_ReadSettingsForRooms( HINI Ini_file )
{
 // Сбрасываем все переменные.
 bzero( &Painter, sizeof( Painter ) );

 // Задаем цвета по умолчанию и читаем настройки.
 Painter_SetPreDefinedSettings( SET_ROOMS );
 Painter_ReadSettings( Ini_file );

 // Возврат.
 return;
}