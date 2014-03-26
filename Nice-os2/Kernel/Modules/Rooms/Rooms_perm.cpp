
// ─── Проверяет, можно ли прятать окно при смене комнат ───

// Frame_window - окно рамки.
BYTE Rooms_PermissionForRoomActions( HWND Frame_window )
{
 // Если окно недоступно - возврат.
 if( !FrameWindowIsAccessible( Frame_window ) ) return 0;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Проверяем, есть ли приложение в списке исключений.
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Rooms.Settings.Exceptions.Rooms_8 ) == EQUALLY ) return 0;
  }

 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Rooms.Settings.Exceptions.Rooms_8 ) == EQUALLY ) return 0;
  }

 // Возврат.
 return 1;
}
