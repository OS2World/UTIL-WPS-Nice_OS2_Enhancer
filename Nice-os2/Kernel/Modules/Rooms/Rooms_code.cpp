
// ─── Выбирает предопределенную комнату для окна ───

// Frame_window - окно рамки.
INT Rooms_GetPreDefinedRoom( HWND Frame_window )
{
 // Если размещать приложения в комнатах не надо - возврат.
 if( !Rooms.Settings.Allocate_windows_to_Rooms ) return NO_ROOM;

 // Узнаем имя приложения, создавшего окно.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // Если его удалось определить:
 if( Exe_name[ 0 ] != 0 )
  {
   // Проверяем, есть ли приложение в списке.
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_1_name ) ) return Rooms.Settings.Allocations.Preferable_room_1;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_2_name ) ) return Rooms.Settings.Allocations.Preferable_room_2;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_3_name ) ) return Rooms.Settings.Allocations.Preferable_room_3;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_4_name ) ) return Rooms.Settings.Allocations.Preferable_room_4;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_5_name ) ) return Rooms.Settings.Allocations.Preferable_room_5;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_6_name ) ) return Rooms.Settings.Allocations.Preferable_room_6;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_7_name ) ) return Rooms.Settings.Allocations.Preferable_room_7;
   if( stric( Exe_name, Rooms.Settings.Allocations.Unit_8_name ) ) return Rooms.Settings.Allocations.Preferable_room_8;
  }

 // Узнаем окно рабочей области.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // Если оно есть:
 if( Client_window != NULLHANDLE )
  {
   // Узнаем имя, под которым определено окно рабочей области.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // Проверяем, есть ли окно в списке исключений.
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_1_name ) ) return Rooms.Settings.Allocations.Preferable_room_1;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_2_name ) ) return Rooms.Settings.Allocations.Preferable_room_2;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_3_name ) ) return Rooms.Settings.Allocations.Preferable_room_3;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_4_name ) ) return Rooms.Settings.Allocations.Preferable_room_4;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_5_name ) ) return Rooms.Settings.Allocations.Preferable_room_5;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_6_name ) ) return Rooms.Settings.Allocations.Preferable_room_6;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_7_name ) ) return Rooms.Settings.Allocations.Preferable_room_7;
   if( strc( Window_name, Rooms.Settings.Allocations.Unit_8_name ) ) return Rooms.Settings.Allocations.Preferable_room_8;
  }

 // Если надо размещать в комнатах знакомые расширителю приложения:
 if( Rooms.Settings.Allocate_known_applications )
  {
   // Если удалось определить имя приложения:
   if( Exe_name[ 0 ] != 0 )
    {
     // Проверяем его.
     if( WindowIsUsedTo( DO_BROWSE_FTP_SITES, Frame_window ) )   return NORTHERN_ROOM;
     if( WindowIsUsedTo( DO_REMOTE_CONTROL, Frame_window ) )     return NORTHERN_ROOM;
     if( WindowIsUsedTo( DO_MANAGE_FILES, Frame_window ) )       return WESTERN_ROOM;
     if( WindowIsUsedTo( DO_CONNECT_INTERNET, Frame_window ) )   return EASTERN_ROOM;
     if( WindowIsUsedTo( DO_READ_MESSAGES, Frame_window ) )      return SOUTHERN_ROOM;
    }
  }

 // Возврат.
 return NO_ROOM;
}

// ─── Подбирает наиболее подходящую комнату для окна ───

// Frame_window - окно рамки.
INT Rooms_GetMostSuitableRoom( HWND Frame_window )
{
 // Если есть предопределенная комната - используем это значение.
 INT PreDefined_room = Rooms_GetPreDefinedRoom( Frame_window );
 if( PreDefined_room != NO_ROOM && PreDefined_room != SHELL_ROOM ) return PreDefined_room;

 // Возврат.
 return NO_ROOM;
}

// ─── Восстанавливает и закрывает окна WPS, расположенные в комнатах ───

// Desktop - окно рабочего стола.
VOID Rooms_RestoreAndCloseOuterWPSWindows( HWND Desktop )
{
 // Если используется оболочка WPS:
 if( ShellIsWPS() )
  {
   // Узнаем размер экрана.
   INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
   INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

   // Узнаем окно оболочки.
   HWND Shell_window = GetDetectedShellWindow();

   // Перебираем окна в окне рабочего стола.
   HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Если это не окно оболочки:
     if( Window != Shell_window )
      {
       // Узнаем комнату, в которой расположено окно.
       INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

       // Если это не комната с окном оболочки:
       if( Window_room != SHELL_ROOM )
        {
         // Если это окно WPS:
         if( IsFolderWindow( Window ) )
          {
           // Узнаем расположение окна и его состояние.
           SWP Window_state = {0}; WinQueryWindowPos( Window, &Window_state );

           // Если окно уменьшено в значок или скрыто:
           if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE )
            {
             // Устанавливаем окно-занавеску поверх всех окон. Оно закрывает экран, но ничего не рисует.
             ShowCurtainWindow( Desktop );

             // Отключаем заставку при открытии окна, чтобы оно закрывалось быстрее.
             DisableAnimation( Window );

             // Восстанавливаем и закрываем его.
             PerformAction( Window, RESTORE_ACTION );
             PerformAction( Window, CLOSE_ACTION );
            }
          }
        }
      }
    }
   WinEndEnumWindows( Enumeration );
  }

 // Возврат.
 return;
}

// ─── Удаляет изображение для закрашивания рабочего стола ───

VOID Rooms_DeleteDesktopWallpaper( VOID )
{
 // Удаляем изображения.
 if( Rooms.RTSettings.Wallpaper != NULLHANDLE )
  {
   GpiDeleteBitmap( Rooms.RTSettings.Wallpaper );
   Rooms.RTSettings.Wallpaper = NULLHANDLE;
  }

 // Возврат.
 return;
}

// ─── Создает изображения для закрашивания рабочего стола ───

// Desktop - окно рабочего стола, New_room - комната.
VOID Rooms_CreateDesktopWallpaper( HWND Desktop, INT New_room )
{
 // Удаляем изображение, созданное раньше.
 Rooms_DeleteDesktopWallpaper();

 // Задаем имя файла с изображением.
 CHAR File_name[ SIZE_OF_PATH ] = "";

 if( New_room == SHELL_ROOM ) if( !ShellIsWPS() ) strcpy( File_name, Rooms.Settings.Wallpaper_for_shell_room );
 if( New_room == NORTHERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_northern_room );
 if( New_room == WESTERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_western_room );
 if( New_room == EASTERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_eastern_room );
 if( New_room == SOUTHERN_ROOM ) strcpy( File_name, Rooms.Settings.Wallpaper_for_southern_room );

 // Загружаем изображение с диска.
 HBITMAP Loaded_image = NULLHANDLE; INT Bitmap_width = 0; INT Bitmap_height = 0;
 LoadBitmap( Enhancer.Application, File_name, &Loaded_image, &Bitmap_width, &Bitmap_height );

 // Если изображения нет - возврат.
 if( Loaded_image == NULLHANDLE ) return;

 // Создаем пространство отображения.
 HPS Wallpaper_memory_space = CreatePresentationSpace( Enhancer.Application );

 // Узнаем размер экрана.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // Создаем изображение в памяти размером с экран.
 HBITMAP Bitmap = CreateBitmap( Wallpaper_memory_space, X_Screen, Y_Screen );

 // Заполняем изображение в памяти.
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

 // Сбрасываем пространство отображения.
 GpiDestroyPS( Wallpaper_memory_space );

 // Удаляем загруженное изображение.
 GpiDeleteBitmap( Loaded_image ); Loaded_image = NULLHANDLE;

 // Запоминаем полученное изображение.
 Rooms.RTSettings.Wallpaper = Bitmap;

 // Возврат.
 return;
}

// ─── Закрашивает рабочий стол ───

// Desktop - окно рабочего стола.
VOID Rooms_FillDesktop( HWND Desktop )
{
 // Если изображения для закрашивания нет - возврат.
 if( Rooms.RTSettings.Wallpaper == NULLHANDLE ) return;

 // Работаем в пространстве отображения окна.
 HPS Presentation_space = WinGetPS( Desktop );

 // Если пространство отображения не получено - возврат.
 if( Presentation_space == NULLHANDLE ) return;

 // Узнаем размер экрана.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // Задаем расположение изображения.
 POINT Image_points[ 3 ] = { 0, 0, X_Screen, Y_Screen, 0, 0 };
 PPOINT Points = Image_points;

 // Создаем пространство отображения.
 HPS Wallpaper_memory_space = CreatePresentationSpace( Enhancer.Application );

 // Переносим изображение в окно.
 GpiSetBitmap( Wallpaper_memory_space, Rooms.RTSettings.Wallpaper );
 GpiBitBlt( Presentation_space, Wallpaper_memory_space, 3, Points, ROP_SRCCOPY, BBO_IGNORE );
 GpiSetBitmap( Wallpaper_memory_space, NULLHANDLE );

 // Сбрасываем пространство отображения.
 GpiDestroyPS( Wallpaper_memory_space );

 // Завершаем работу в пространстве отображения окна.
 WinReleasePS( Presentation_space );

 // Возврат.
 return;
}

// ─── Скрывает или показывает окна ───

// Desktop - окно рабочего стола, New_room - новая комната, Current_room - текущая комната.
VOID Rooms_ChangeWindowSet( HWND Desktop, INT New_room, INT Current_room )
{
 // Если есть окно, которое убрано наверх - восстанавливаем его.
 HWND Rolled_window = RolledWindow(); LONG Rolled_window_buttons = 0;

 if( Rolled_window != NULLHANDLE )
  if( Rooms_PermissionForRoomActions( Rolled_window ) )
   {
    // Запоминаем состояние кнопок в окне.
    Rolled_window_buttons = QueryButtonsState( Rolled_window, MINIMIZE_ACTION, 0 );

    // Если рамки или кнопки рисовать не надо - запоминаем, что это окно увеличено.
    if( !DrawFramesSettingIsON() || !DrawButtonsSettingIsON() ) SetNextButtons( Rolled_window, MAXIMIZE_ACTION );

    // Восстанавливаем окно.
    UnrollWindow( Rolled_window );
    // Для того, чтобы было установлено новое состояние кнопок и при переходе в эту комнату
    // окно было восстановлено (а не увеличено), надо передавать параметр "PA_METHOD_CALLED_BY_WINDOW_MANAGER".
    PerformAction( Rolled_window, RESTORE_ACTION, 0, PA_METHOD_CALLED_BY_WINDOW_MANAGER );

    // Отодвигаем окно за все остальные окна.
    WinSetWindowPos( Rolled_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST );
   }

 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Узнаем комнату, в которой расположено окно.
   INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

   // Узнаем предопределенную комнату.
   INT PreDefined_room = Rooms_GetPreDefinedRoom( Window );

   // Скрываем все окна в комнате, в которые можно переключиться.
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
     // Узнаем состояние кнопок в заголовке окна.
     LONG Buttons = 0;

     // Окна Win-OS/2 и Odin можно только уменьшать в значок.
     if( IsWindowsWindow( Window ) )
      {
       Buttons = MINIMIZE_ACTION;
      }
     // Окна OS/2 можно уменьшать и скрывать.
     else
      {
       // Для окна, которое было убрано наверх состояние кнопок известно заранее.
       if( Window != Rolled_window ) Buttons = QueryButtonsState( Window, MINIMIZE_ACTION | MAXIMIZE_ACTION, 0 );
       else Buttons = Rolled_window_buttons;
      }

     // Если это окно OS/2:
     if( !IsWindowsWindow( Window ) )
      {
       // Если рамки или кнопки рисовать не надо - запоминаем состояние кнопок.
       // Оно будет использовано при вызове SetMaximizeProperty() и при восстановлении окна.
       if( !DrawFramesSettingIsON() || !DrawButtonsSettingIsON() || !PermissionForDrawing( Window ) )
        {
         SetProperty( Window, PRP_BUTTONS, &Buttons );
        }
      }

     // Если окно может быть уменьшено в значок:
     if( Buttons & MINIMIZE_ACTION )
      {
       // Запоминаем размер окна.
       RECT Rectangle = {0}; WinQueryWindowRect( Window, &Rectangle );

       INT Width = Rectangle.xRight - Rectangle.xLeft;
       INT Height = Rectangle.yTop - Rectangle.yBottom;

       SetProperty( Window, PRP_PREVIOUS_WIDTH, &Width );
       SetProperty( Window, PRP_PREVIOUS_HEIGHT, &Height );

       // Уменьшаем окно в значок.
       // Оно должно быть перенесено в список значков скрытых окон.
       LONG Action = MINIMIZE_ACTION;

       SetProperty( Window, PRP_PERFORMED_ACTION, &Action );
       BYTE Action_completed = PerformAction( Window, Action );

       // Скрываем окно, если действие не было выполнено и окно все еще остается на экране.
       // Это надо делать для окон ODIN, которые не обращают внимание на сообщения.
       if( !Action_completed ) WinShowWindow( Window, 0 );

       // Делаем окно недоступным для переключения.
       WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
      }
     // А если окно можно только скрыть:
     else
      {
       // Скрываем окно.
       WinShowWindow( Window, 0 );

       // Делаем окно недоступным для переключения.
       WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
      }
    }

   // Показываем окна для новой комнаты.
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
     // Если окно видимо:
     if( WinIsWindowVisible( Window ) )
      {
       // Узнаем, было ли окно увеличено.
       BYTE Maximized = 0; FindProperty( Window, PRP_MAXIMIZED, &Maximized );

       // Посылаем сообщение в окно.
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

       // Выравниваем текстовые окна, которые были увеличены.
       if( Maximized ) if( IsVIOWindow( Window ) )
        {
         // Посылаем в окно сообщение WM_MARK. Когда оно будет получено, окно можно будет выравнивать.
         WinPostMsg( Window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) SM_ARRANGE_VIO_IN_ROOM );
        }
      }
     // А если оно скрыто:
     else
      {
       // Делаем окно видимым.
       // Это надо делать для окон ODIN и для тех окон, у которых единственным действием было "скрыть окно".
       WinShowWindow( Window, 1 );
      }

     // Делаем окно доступным для переключения.
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_JUMPABLE );
    }

   // Отодвигаем назад LaunchPad.
   if( IsLaunchPadWindow( Window ) ) WinSetWindowPos( Window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST );

   // Скрываем список окон.
   if( IsWinListWindow( Window ) ) PerformAction( Window, HIDE_ACTION );
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Скрывает или показывает окно оболочки ───

// Window - окно оболочки, Show_window - скрыть или показать окно.
VOID Rooms_ShowShellWindow( HWND Window, BYTE Show_window )
{
 // Если окно оболочки надо скрыть:
 if( !Show_window )
  {
   // Узнаем расположение окна.
   SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

   // Если это настоящее окно оболочки:
   if( Window == GetDetectedShellWindow() )
    {
     // Если оно не скрыто:
     HWND Desktop = QueryDesktopWindow();

     INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
     INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

     INT New_X_placement = X_Screen * (-10);
     INT New_Y_placement = Y_Screen * (-10);

     if( Window_placement.x != New_X_placement )
      {
       // Запоминаем расположение окна.
       Rooms.RTSettings.Shell_window_angle.x = Window_placement.x;
       Rooms.RTSettings.Shell_window_angle.y = Window_placement.y;

       // Передвигаем окно за пределы экрана. Уменьшать или скрывать окно
       // оболочки нельзя - тогда оно тянет за собой еще несколько окон.
       WinSetWindowPos( Window, NULLHANDLE, New_X_placement, New_Y_placement, 0, 0, SWP_MOVE | SWP_NOADJUST );
      }
    }
  }
 // А если окно оболочки надо показать:
 else
  {
   // Передвигаем окно обратно.
   WinSetWindowPos( Window, NULLHANDLE, Rooms.RTSettings.Shell_window_angle.x, Rooms.RTSettings.Shell_window_angle.y, 0, 0, SWP_MOVE | SWP_NOADJUST );
  }
}

// ─── Находит скрытое окно оболочки и показывает его ───

VOID Rooms_RetrieveShellWindow( VOID )
{
 // Узнаем, как расположено окно WarpCenter.
 BYTE WarpCenter_is_in_top = 1;

 // Перебираем окна в окне рабочего стола.
 HWND Desktop = QueryDesktopWindow();
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно не скрыто и это окно WarpCenter:
   if( WinIsWindowVisible( Window ) ) if( IsWarpCenterWindow( Window ) )
    {
     // Узнаем расположение окна.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // Проверяем расположение окна.
     if( Window_placement.y <= 0 ) WarpCenter_is_in_top = 0;

     // Завершаем перебор окон.
     break;
    }
  }
 WinEndEnumWindows( Enumeration );

 // Перебираем окна в окне рабочего стола.
 Enumeration = WinBeginEnumWindows( Desktop ); Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно не скрыто:
   if( WinIsWindowVisible( Window ) )
    {
     // Если это окно WPS:
     if( IsFolderWindow( Window ) )
      {
       // Если оно имеет свойства окна оболочки - задаем новое расположение окна.
       if( HasShellWindowControls( Window ) )
        {
         // Если окно WarpCenter расположено вверху:
         if( WarpCenter_is_in_top )
          {
           // Левый нижний угол окна должен выходить за пределы экрана.
           INT Frame_width = FrameWidth( Window );
           Rooms.RTSettings.Shell_window_angle.x = Rooms.RTSettings.Shell_window_angle.y = Frame_width * (-1);
          }
         // А если окно WarpCenter расположено внизу:
         else
          {
           // Узнаем размер экрана.
           INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

           // Узнаем высоту заголовка окна.
           INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

           // Узнаем размер окна.
           RECT Rectangle = {0}; WinQueryWindowRect( Window, &Rectangle );

           // Левый нижний угол окна должен касаться окна WarpCenter.
           INT Frame_width = FrameWidth( Window );
           Rooms.RTSettings.Shell_window_angle.x = Frame_width * (-1);

           INT Y_Top = Y_Screen + TitleBar_height + Frame_width;
           Rooms.RTSettings.Shell_window_angle.y = Y_Top - Rectangle.yTop;
          }

         // Показываем окно.
         RememberShellWindow( Window ); Rooms_ShowShellWindow( Window, 1 );
        }
      }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Возврат.
 return;
}

// ─── Переходит в комнату ───

// Room - комната, в которую надо перейти.
VOID Rooms_GoToRoom( INT New_room )
{
 // Если показано окно сообщения об ошибке - возврат.
 if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW, FIND_VISIBLE_WINDOW ) )
  {
   // Звук.
   WinAlarm( QueryDesktopWindow(), WA_NOTE );

   // Возврат.
   return;
  }

 // Если комната та же самая:
 if( New_room == GetCurrentOrNextRoom() )
  {
   // Если это комната с окном оболочки и оно недоступно - пробуем показать его.
   if( ShellIsWPS() ) if( GetCurrentOrNextRoom() == SHELL_ROOM )
    if( !ShellIsAvailable() )
     if( WinIsWindow( WinQueryAnchorBlock( GetDetectedShellWindow() ), GetDetectedShellWindow() ) )
      Rooms_RetrieveShellWindow();

   // Делаем выбранным окно в середине экрана.
   ActivateWindowInCenter();

   // Возврат.
   return;
  }

 // Если показано меню WarpCenter - прячем его.
 if( SystemWindowIsPresent( FIND_ALL_TOOLBAR_MENUS, FIND_VISIBLE_WINDOW ) )
  HideShellToolbarMenu( 1 );

 // Если используется оболочка WPS:
 if( ShellIsWPS() )
  {
   // Узнаем окно оболочки.
   HWND Detected_shell_window = GetDetectedShellWindow();

   // Если надо покинуть комнату с окном оболочки - запоминаем его.
   if( GetCurrentOrNextRoom() == SHELL_ROOM )
    {
     // Если оно сейчас недоступно - возврат.
     HWND Shell_window = QueryShellWindow();

     if( Shell_window == NULLHANDLE )
      {
       // Пробуем показать окно оболочки.
       if( WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
        Rooms_RetrieveShellWindow();

       // Возврат.
       return;
      }

     // Запоминаем окно оболочки.
     RememberShellWindow( Shell_window );
    }

   // Если надо перейти в другую комнату и окна оболочки нет - возврат.
   if( New_room != SHELL_ROOM )
    if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
     {
      // Возврат.
      return;
     }

   // Если надо вернуться в комнату с окном оболочки и его нет - запоминаем новое окно.
   if( New_room == SHELL_ROOM )
    if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
     {
      // Смотрим, есть ли новое окно.
      HWND Shell_window = QueryShellWindow();

      // Если оно есть - запоминаем его.
      if( Shell_window != NULLHANDLE )
       {
        // Запоминаем окно оболочки.
        RememberShellWindow( Shell_window );
        Rooms.RTSettings.Shell_window_angle.x = ROOMS_DO_NOT_RESTORE_WINDOW;
       }
      // А если его нет - возврат.
      else
       {
        // Окно оболочки неизвестно.
        RememberShellWindow( NULLHANDLE );

        // Возврат.
        return;
       }
     }
  }

 // На время переключения считаем, что комната неизвестна.
 INT Current_room = GetCurrentOrNextRoom(); SetCurrentAndNextRoom( NO_ROOM, New_room );

 // Запоминаем текущее время, чтобы добиться правильной работы потоков после смены комнат.
 RememberRoomsSwitchingTime(); Rooms.Settings.Synchronize_arranger_and_rooms = 1;

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Устанавливаем окно-занавеску поверх всех окон. Оно закрывает экран, но ничего не рисует.
 ShowCurtainWindow( Desktop );

 // Снижаем приоритеты для всех приложений.
 SetDynamicPriorityLevels( SDPL_SUPPRESS_ALL_PROCESSES );

 // Если используется оболочка WPS:
 if( ShellIsWPS() )
  {
   // Если надо перейти в комнату с окном оболочки - показываем его.
   // Это надо сделать как можно раньше - на случай, если поток повиснет.
   if( New_room == SHELL_ROOM )
    if( Rooms.RTSettings.Shell_window_angle.x != ROOMS_DO_NOT_RESTORE_WINDOW )
     Rooms_ShowShellWindow( GetDetectedShellWindow(), 1 );
  }

 // Некоторые окна могли быть скрыты пользователем, тогда они нигде не расположены.
 // Они появятся в другой комнате, когда будут выбраны пользователем в списке окон.
 // Перебираем окна в окне рабочего стола.
 HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // Если окно можно прятать при смене комнат:
   if( Rooms_PermissionForRoomActions( Window ) )
    {
     // Узнаем комнату, в которой расположено окно.
     INT Window_room = NO_ROOM; FindProperty( Window, PRP_ROOM, &Window_room );

     // Если оно расположено в этой комнате и было уменьшено или скрыто - сбрасываем свойство.
     // Если окно не расположено ни в одной комнате и в него нельзя переключиться - сбрасываем свойство.
     if( Window_room == Current_room || !Window_room )
      if( !PermissionForSwitching( Window ) )
       {
        // Запоминаем комнату.
        INT Room = Rooms_GetMostSuitableRoom( Window ); Rooms_SetRoomProperty( Window, Room );

        // Отодвигаем окно за все остальные окна.
        WinSetWindowPos( Window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );

        // Делаем окно недоступным для переключения.
        WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_NOTJUMPABLE );
       }

     // Если окно не расположено ни в одной комнате и в него можно переключиться - считаем,
     // что оно расположено в этой комнате. Это бывает, когда настройка включается во время работы.
     if( !Window_room )
      if( PermissionForSwitching( Window ) )
       {
        // Запоминаем комнату.
        Rooms_SetRoomProperty( Window, Current_room );

        // Делаем окно недоступным для переключения.
        WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SET_JUMPABLE, (MPARAM) Window, (MPARAM) SWL_JUMPABLE );
       }
    }
  }
 WinEndEnumWindows( Enumeration );

 // Меняем набор окон.
 LONG Animation_is_allowed = WinQuerySysValue( Desktop, SV_ANIMATION );
 if( Animation_is_allowed ) WinSetSysValue( Desktop, SV_ANIMATION, 0 );

 Rooms_ChangeWindowSet( Desktop, New_room, Current_room );

 if( Animation_is_allowed ) WinSetSysValue( Desktop, SV_ANIMATION, 1 );

 // Если используется оболочка WPS:
 if( ShellIsWPS() )
  {
   // Если надо покинуть комнату с окном оболочки - скрываем его.
   if( New_room != SHELL_ROOM )
    Rooms_ShowShellWindow( GetDetectedShellWindow(), 0 );
  }

 // Меняем изображения для закрашивания заголовка.
 if( DifferentTitleBarImagesAreRequired() ) CreateTitleBarImages();

 // Меняем заставку для рабочего стола.
 if( Rooms.Settings.Draw_wallpaper )
  {
   if( New_room != SHELL_ROOM )
    Rooms_CreateDesktopWallpaper( Desktop, New_room );
   else
    Rooms_DeleteDesktopWallpaper();
  }

 // Скрываем окно-занавеску, а если она уже была скрыта - обновляем окно рабочего стола.
 if( WinIsWindowVisible( CurtainWindow() ) ) HideCurtainWindow();
 else WinInvalidateRect( Desktop, NULL, 0 );

 // Запоминаем новую комнату.
 SetCurrentAndNextRoom( New_room, NO_ROOM );

 // Устанавливаем переключатели на клавиатуре.
 WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // Освобождаем указатель мыши.
 ResetPointer();

 // Надо сделать выбранным окно в середине экрана.
 WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_RETARD_AND_ACTIVATE, 0, 0 );

 // Если используется оболочка WPS:
 if( ShellIsWPS() )
  {
   // При переходе в комнату с окном оболочки оно может быть скрыто - его надо удерживать некоторое время.
   if( New_room == SHELL_ROOM ) WinPostQueueMsg( Enhancer.Modules.Rooms->Message_queue, SM_HOLD_SHELL_WINDOW, 0, 0 );
  }

 // Возврат.
 return;
}

// ─── Проверяет окно, которое становится выбранным ───

// Frame_window - окно, которое надо проверить.
VOID Rooms_CheckActivatedWindow( HWND Frame_window )
{
 // Если окно расположено так же, как окно оболочки - надо спрятать его.
 BYTE Shell_is_changed = 0;

 // Узнаем расположение окна.
 SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

 // Проверяем окно.
 if( HasShellPlacement( Frame_window, &Window_placement ) ) Shell_is_changed = 1;

 // Если это окно оболочки - надо сделать выбранным другое окно.
 HWND Detected_shell_window = GetDetectedShellWindow();
 BYTE Shell_is_selected = 0;
 if( !Shell_is_changed ) if( Frame_window == Detected_shell_window ) Shell_is_selected = 1;

 // Если окна оболочки нет - запоминаем новое окно.
 if( Shell_is_changed )
  if( !WinIsWindow( WinQueryAnchorBlock( Detected_shell_window ), Detected_shell_window ) )
   RememberShellWindow( Frame_window );

 // Если показано окно WarpCenter - он может мешать, возврат.
 if( SystemWindowIsPresent( FIND_WARPCENTER, FIND_VISIBLE_WINDOW ) ) return;

 // Прячем окно и выбираем окно в середине экрана.
 if( Shell_is_changed ) Rooms_ShowShellWindow( Frame_window, 0 );
 if( Shell_is_changed || Shell_is_selected ) ActivateWindowInCenter();

 // Возврат.
 return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Rooms_RoomsMessageProcessing( PQMSG Message )
{
 // Устанавливаем приоритет потока.
 if( Message->msg == SM_PRIORITY )
  {
   // Устанавливаем приоритет.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // Запоминаем приоритет.
   Enhancer.Modules.Rooms->Priority = MAKELONG( Class, Delta );
  }

 // Переходим в комнату.
 if( Message->msg == SM_GO_TO_ROOM )
  {
   // Ждем, пока мышь не станет свободна.
   while( MouseIsBusy() ) Retard();

   // Узнаем комнату.
   INT Room = (INT) Message->mp1;

   // Переходим в нее.
   Rooms_GoToRoom( Room );
  }

 // Удерживаем окно оболочки после смены комнат.
 if( Message->msg == SM_HOLD_SHELL_WINDOW )
  {
   // Запоминаем окно оболочки.
   HWND Shell_window = GetDetectedShellWindow();

   // Проверяем его.
   for( INT Count = 0; Count < Rooms.Constants.Retards_after_room_change; Count ++ )
    {
     // Ждем некоторое время.
     Retard();

     // Если окна оболочки нет - завершаем проверки.
     if( !WinIsWindow( WinQueryAnchorBlock( Shell_window ), Shell_window ) ) break;

     // Если окно оболочки недоступно - пробуем показать его.
     if( !ShellIsAvailable() ) Rooms_RetrieveShellWindow();

     // Через несколько шагов - уменьшаем приоритет.
     if( Count == 3 ) DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );
    }

   // Восстанавливаем приоритет.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.Rooms->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.Rooms->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );
  }

 // Проверяем окно, которое становится выбранным.
 if( Message->msg == SM_CHECK_WINDOW )
  {
   // Узнаем окно, которое надо проверить.
   HWND Frame_window = (HWND) Message->mp1;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // Проверяем окно.
   Rooms_CheckActivatedWindow( Frame_window );
  }

 // Закрашиваем окно рабочего стола. Это надо делать в том же потоке, который меняет заставку.
 if( Message->msg == SM_FILL_DESKTOP )
  {
   // Узнаем окно, которое надо закрасить.
   HWND Desktop = (HWND) Message->mp1;

   // Если окна нет - возврат.
   if( !WinIsWindow( WinQueryAnchorBlock( Desktop ), Desktop ) ) return;

   // Уменьшаем приоритет.
   DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

   // Закрашиваем рабочий стол.
   Rooms_FillDesktop( Desktop );

   // Восстанавливаем приоритет.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.Rooms->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.Rooms->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );
  }

 // Возврат.
 return;
}

// ─── Поток для перехода между комнатами ───

VOID Rooms_RoomsThread( VOID )
{
 // Определяем поток в системе.
 HAB Thread = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Thread == NULLHANDLE )
  {
   // При создании потока произошла ошибка.
   Thread_responds.Thread_is_created = -1;

   // Выход.
   return;
  }

 // Создаем очередь сообщений - она должна быть в каждом потоке.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Rooms->Message_queue = Message_queue;

 // Если очередь создать не удалось - выход.
 if( Enhancer.Modules.Rooms->Message_queue == NULLHANDLE )
  {
   // Завершаем работу потока.
   WinTerminate( Thread );

   // При создании потока произошла ошибка.
   Thread_responds.Thread_is_created = -1;

   // Выход.
   return;
  }

 // Поток создан успешно.
 Thread_responds.Thread_is_created = 1;

 // Получение и обработка сообщений, приходящих в поток.
 QMSG Message = {0};
 while( WinGetMsg( Thread, &Message, 0, 0, 0 ) )
  {
   // Проверяем, не идет ли следом такое же сообщение.
   QMSG Next_message = {0};
   WinPeekMsg( Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE );
   if( Next_message.msg == Message.msg )
    if( Next_message.mp1 == Message.mp1 )
     if( Next_message.mp2 == Message.mp2 ) 
      if( Next_message.hwnd == Message.hwnd ) continue;

   // Обрабатываем сообщение.
   Rooms_RoomsMessageProcessing( &Message );
  }

 // Завершаем работу потока.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}

