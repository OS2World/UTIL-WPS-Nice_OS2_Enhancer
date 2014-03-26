
// ─── Подготавливает окна для рисования ───

// *_window - окно рамки, заголовок, кнопки уменьшения и увеличения. *_rectangle - их размеры.
// Возвращаемое значение: 1 - рядом с заголовком есть дополнительные окна, 0 - нет таких окон.
BYTE Painter_PrepareWindowControls( HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, HWND TitleBar_window, HWND SysMenu_window, HWND MinMax_window )
{
 // Окно обычных кнопок сжимается в "|" и располагается слева от новых кнопок. Окно
 // заголовка растягивается или сжимается так, чтобы оно касалось новых кнопок. Все
 // окна, расположенные между ними, передвигаются вправо или влево. Можно проверять
 // расположение обычных кнопок и узнавать смещение для заголовка и других окон.
 // Если окна обычных кнопок нет - просто передвигаем окна.
 BYTE Controls_are_present = 0;

 // Если окна заголовка, картинки и кнопок неизвестны - узнаем их.
 if( TitleBar_window == NULLHANDLE ) TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
 if( SysMenu_window == NULLHANDLE ) SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );
 if( MinMax_window == NULLHANDLE ) MinMax_window = WinWindowFromID( Frame_window, FID_MINMAX );

 // Если окно заголовка есть - узнаем его расположение.
 SWP TitleBar_placement = {0};
 if( TitleBar_window != NULLHANDLE ) WinQueryWindowPos( TitleBar_window, &TitleBar_placement );

 // Если есть окно заголовка - проверяем его расположение внутри окна рамки:
 if( TitleBar_window != NULLHANDLE )
  {
   // Если высота заголовка больше его ширины - возврат.
   if( TitleBar_placement.cy > TitleBar_placement.cx ) return 0;

   // Иногда окна постоянного размера располагают заголовок и картинку в левом верхнем углу
   // не так, как надо, полагая, что ширина их рамки равна ширине рамки окна переменного размера.
   if( Frame_type == FT_CONST )
    {
     // Узнаем ширину рамки окна.
     INT Const_frame = 0; FindProperty( Frame_window, PRP_BORDER, &Const_frame );
     if( !Const_frame ) Const_frame = FrameWidth( Frame_window );

     // Проверяем расположение окна заголовка. Если оно не на месте:
     if( TitleBar_placement.y + TitleBar_placement.cy < Frame_rectangle->yTop - Const_frame + 1 )
      if( TitleBar_placement.y + TitleBar_placement.cy > Frame_rectangle->yTop - Const_frame * 2 )
       {
        // Задаем правильное расположение окна.
        INT Offset = ( Frame_rectangle->yTop - Const_frame + 1 ) - ( TitleBar_placement.y + TitleBar_placement.cy );
        TitleBar_placement.y += Offset; TitleBar_placement.x -= Offset; TitleBar_placement.cx += Offset * 2;
        WinSetWindowPos( TitleBar_window, NULLHANDLE, TitleBar_placement.x, TitleBar_placement.y, TitleBar_placement.cx, TitleBar_placement.cy, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

        // Если есть окно картинки - проверяем его расположение внутри окна рамки.
        if( SysMenu_window != NULLHANDLE )
         {
          // Узнаем расположение окна картинки.
          SWP SysMenu_placement = {0};
          if( SysMenu_window != NULLHANDLE ) WinQueryWindowPos( SysMenu_window, &SysMenu_placement );

          // Проверяем расположение окна картинки. Если оно не на месте:
          if( SysMenu_placement.y + SysMenu_placement.cy < Frame_rectangle->yTop - Const_frame + 1 )
           if( SysMenu_placement.y + SysMenu_placement.cy > Frame_rectangle->yTop - Const_frame * 2 )
            {
             // Задаем правильное расположение окна.
             INT Offset = ( Frame_rectangle->yTop - Const_frame + 1 ) - ( SysMenu_placement.y + SysMenu_placement.cy );
             SysMenu_placement.y += Offset; SysMenu_placement.x -= Offset;
             WinSetWindowPos( SysMenu_window, NULLHANDLE, SysMenu_placement.x, SysMenu_placement.y, SysMenu_placement.cx, SysMenu_placement.cy, SWP_MOVE | SWP_NOADJUST );
            }
         }
       }
    }
  }

 // Если кнопки рисовать не надо - возврат.
 if( !Painter.Settings.Draw_buttons ) return 0;

 // Узнаем размер окна заголовка
 RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );

 // Узнаем прямоугольник для кнопок, которые будут нарисованы в окне.
 RECT All_buttons = {0};
 INT Size = Painter_CalculateButtonRectangles( Frame_window, Frame_rectangle, TitleBar_window, &TitleBar_rectangle, NULL, NULL, NULL, NULL, &All_buttons );

 // Если окно обычных кнопок есть - узнаем его расположение.
 SWP MinMax_placement = {0};
 if( MinMax_window != NULLHANDLE ) WinQueryWindowPos( MinMax_window, &MinMax_placement );

 // Запоминаем, есть ли кнопки, чтобы точно проверять расположение окон.
 BYTE MinMax_is_available = 1;

 // Окна кнопок может не быть.
 if( MinMax_window == NULLHANDLE ) MinMax_is_available = 0;

 // При создании окна рамки окно обычных кнопок сжато и располагаются справа от
 // прямоугольника, который для него предназначен. Затем оно меняет расположение.
 if( MinMax_placement.x == All_buttons.xRight + 1 )
  if( MinMax_placement.cx == 0 ) MinMax_is_available = 0;

 // Если кнопки не готовы и их нет - возврат.
 if( !MinMax_is_available )
  if( All_buttons.xLeft == All_buttons.xRight )
   return 0;

 // Если есть окно заголовка:
 if( TitleBar_window != NULLHANDLE )
  {
   // Надо запомнить окна, которые должны быть передвинуты и те, которые мешают кнопкам.
   HWND Controls[ PAINTER_MAX_CONTROLS ]; RECT Controls_rects[ PAINTER_MAX_CONTROLS ];
   HWND Fields[ PAINTER_MAX_CONTROLS ]; RECT Fields_rects[ PAINTER_MAX_CONTROLS ];
   INT Controls_quantity = 0; INT Fields_quantity = 0;

   // Проверять, мешают ли окна кнопкам надо только если окно убрано наверх.
   BYTE Hide_fields = 0;
   if( Frame_window == RolledWindow() ) Hide_fields = 1;

   // Запоминаем окна, которые проверять не надо.
   HWND Menu_window = WinWindowFromID( Frame_window, FID_MENU );
   HWND HSBar_window = WinWindowFromID( Frame_window, FID_HORZSCROLL );
   HWND VSBar_window = WinWindowFromID( Frame_window, FID_VERTSCROLL );

   // Перебираем окна, расположеные в окне рамки и проверяем их.
   HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // Если это окно заголовка, обычные кнопки и т. п. - продолжаем перебор.
     if( Window == SysMenu_window || Window == TitleBar_window || Window == MinMax_window ||
         Window == Menu_window    || Window == HSBar_window    || Window == VSBar_window )
      continue;

     // Узнаем расположение окна.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // Если окно расположено между заголовком и кнопками - его надо передвинуть.
     POINT Central_point = { Window_placement.x + Window_placement.cx / 2, Window_placement.y + Window_placement.cy / 2 };
     if( Central_point.y > TitleBar_placement.y )
      if( Central_point.y < TitleBar_placement.y + TitleBar_placement.cy )
       if( MinMax_is_available && ( Central_point.x > TitleBar_placement.x + TitleBar_placement.cx ) ||
          !MinMax_is_available && ( Central_point.x > TitleBar_placement.x + TitleBar_placement.cx / 2 ) )
        if( WinIsWindowVisible( Window ) )
         {
          // Запоминаем окно и его расположение.
          if( Controls_quantity < PAINTER_MAX_CONTROLS )
           {
            Controls[ Controls_quantity ] = Window;

            Controls_rects[ Controls_quantity ].xLeft = Window_placement.x;
            Controls_rects[ Controls_quantity ].xRight = Window_placement.x + Window_placement.cx;
            Controls_rects[ Controls_quantity ].yBottom = Window_placement.y;
            Controls_rects[ Controls_quantity ].yTop = Window_placement.y + Window_placement.cy;

            Controls_quantity ++;
           }
         }

     // Проверяем, может ли окно мешать кнопкам.
     if( Hide_fields )
      {
       // Если окно закрывает кнопки - его надо сжать.
       BYTE Wring_out = 0;
       // Окно может частично закрывать кнопки.
       INT X_Allowable_space = 1; INT Y_Allowable_space = Size * 2 / 3;
       // Проверяем расположение прямоугольников слева направо.
       if( Window_placement.y <= All_buttons.yTop &&
           Window_placement.y + Window_placement.cy > All_buttons.yBottom )
        {
         if( Window_placement.x >= All_buttons.xLeft &&
             Window_placement.x < All_buttons.xRight ) Wring_out = 1;
         if( Window_placement.x + Window_placement.cx > All_buttons.xLeft + X_Allowable_space &&
             Window_placement.x + Window_placement.cx <= All_buttons.xRight ) Wring_out = 1;
        }
       // Проверяем расположение прямоугольников сверху вниз.
       if( Window_placement.x <= All_buttons.xRight &&
           Window_placement.x + Window_placement.cx > All_buttons.xLeft )
        {
         if( Window_placement.y >= All_buttons.yBottom &&
             Window_placement.y < All_buttons.yTop ) Wring_out = 1;
         if( Window_placement.y + Window_placement.cy > All_buttons.yBottom + Y_Allowable_space &&
             Window_placement.y + Window_placement.cy <= All_buttons.yTop ) Wring_out = 1;
        }

       // Запоминаем окно и его расположение.
       if( Wring_out )
        if( Fields_quantity < PAINTER_MAX_CONTROLS )
         {
          Fields[ Fields_quantity ] = Window;

          Fields_rects[ Fields_quantity ].xLeft = Window_placement.x;
          Fields_rects[ Fields_quantity ].xRight = Window_placement.x + Window_placement.cx;
          Fields_rects[ Fields_quantity ].yBottom = Window_placement.y;
          Fields_rects[ Fields_quantity ].yTop = Window_placement.y + Window_placement.cy;

          Fields_quantity ++;
         }
      }
    }
   WinEndEnumWindows( Enumeration );

   // Находим крайнее правое окно и запоминаем его расположение.
   INT Right_point = 0;
   for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
    if( Controls_rects[ Controls_count ].xRight > Right_point )
     Right_point = Controls_rects[ Controls_count ].xRight;

   // Если кнопки еще не подготовлены - надо проверить расположение окон. Окна могут быть
   // расположены слева от прямоугольника для кнопок, то есть так, как будто кнопки есть.
   if( !MinMax_is_available )
    if( All_buttons.xLeft != All_buttons.xRight )
     if( Right_point < All_buttons.xLeft + Size / 2 )
      Controls_quantity = 0;

   // Вычисляем смещение для окон, расположение которых будет изменено.
   INT Offset = 0;
   if( MinMax_window != NULLHANDLE ) Offset = All_buttons.xLeft - MinMax_placement.x;
   else
    if( Controls_quantity != 0 ) Offset = All_buttons.xLeft - Right_point;
    else Offset = Size;

   // Может быть принято решение о том, чтобы сжать все окна.
   BYTE Hide_controls = 0;

   // Передвигаем окна, если это требуется.
   if( Offset != 0 || Hide_controls )
    for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
     {
      // Передвигаем окно или сжимаем его.
      INT X = 0; INT Y = 0; INT Width = 0;
      INT Height = Controls_rects[ Controls_count ].yTop - Controls_rects[ Controls_count ].yBottom;
      if( !Hide_controls )
       {
        X = Controls_rects[ Controls_count ].xLeft + Offset;
        Y = Controls_rects[ Controls_count ].yBottom;
        Width = Controls_rects[ Controls_count ].xRight - Controls_rects[ Controls_count ].xLeft;
       }
      else
       {
        X = All_buttons.xLeft;
        Y = All_buttons.yBottom;
        Width = 0;
       }

       // Передвигаем окно.
       WinSetWindowPos( Controls[ Controls_count ], NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       // Окно должно быть перерисовано. При движении оно может не сделать этого.
       WinInvalidateRect( Controls[ Controls_count ], NULL, 0 );
     }

   // Прячем окна, которые мешают кнопкам.
   if( Hide_fields )
    {
     // Проверяем, нет ли повторов в списках окон.
     if( Controls_quantity != 0 && Fields_quantity != 0 )
      for( INT Fields_count = 0; Fields_count < Fields_quantity; Fields_count ++ )
       for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
        {
         // Если встречаются одинаковые записи:
         if( Fields[ Fields_count ] == Controls[ Controls_count ] )
          {
           // Сдвигаем список к началу на одну запись.
           for( INT Count = Fields_count; Count < Fields_quantity - 1; Count ++ )
            {
             Fields[ Count ] = Fields[ Count + 1 ];
             memcpy( &Fields_rects[ Count ], &Fields_rects[ Count + 1 ], sizeof( RECT ) );
            }

           // Уменьшаем счетчик.
           Fields_quantity --;
          }
        }

     // Сжимаем окна, если они есть.
     if( Fields_quantity != 0 )
      for( INT Fields_count = 0; Fields_count < Fields_quantity; Fields_count ++ )
       {
        // Задаем новое расположение окна
        INT X = Fields_rects[ Fields_count ].xLeft;
        INT Y = Fields_rects[ Fields_count ].yBottom;
        INT Width = Fields_rects[ Fields_count ].xRight - Fields_rects[ Fields_count ].xLeft;
        INT Height = 0;

        // Передвигаем окно.
        WinSetWindowPos( Fields[ Fields_count ], NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );
       }
    }

   // Проверяем, надо ли менять окно заголовка.
   BYTE Change_TitleBar = 0;
   INT New_width = All_buttons.xLeft - TitleBar_placement.x;
   if( Controls_quantity != 0 ) New_width = TitleBar_placement.cx + Offset;

   // Если заголовок должен быть сдвинут вправо или влево:
   if( !Hide_controls )
    {
     // Проверяем смещение.
     if( Offset != 0 ) Change_TitleBar = 1;
    }
   // А если заголовок должен касаться новых кнопок:
   else
    {
     // Проверяем расположение окна заголовка.
     if( TitleBar_placement.cx != New_width ) Change_TitleBar = 1;
    }

   // Если для окна надо рисовать только кнопку закрытия - надо двигать окно заголовка.
   if( !Change_TitleBar ) if( Painter_OneActionIsAllowed( Frame_window ) ) Change_TitleBar = 1;

   // Передвигаем правый край окна заголовка.
   if( Change_TitleBar )
    {
     INT X = TitleBar_placement.x;
     INT Y = TitleBar_placement.y;
     INT Height = TitleBar_placement.cy;

     for( INT Corrections_count = 0; Corrections_count < 10; Corrections_count ++ )
      {
       WinSetWindowPos( TitleBar_window, NULLHANDLE, X, Y, New_width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );
       if( TitleBar_rectangle.xRight - TitleBar_rectangle.xLeft == New_width ) break;
      }
    }

   // Запоминаем, были ли передвинуты окна в окне рамки.
   if( Controls_quantity != 0 ) Controls_are_present = 1;
  }

 // Прячем окно обычных кнопок.
 if( MinMax_window != NULLHANDLE )
  {
   // Проверяем, надо ли прятать кнопки.
   BYTE Change_MinMax = 0;
   if( MinMax_placement.cx != 0 ) Change_MinMax = 1;
   if( MinMax_placement.x != All_buttons.xLeft ) Change_MinMax = 1;

   // Прячем окно кнопок, если это требуется.
   if( Change_MinMax )
    {
     // Сжимаем окно.
     INT X = All_buttons.xLeft;
     INT Y = All_buttons.yBottom;
     INT Width = 0;
     INT Height = MinMax_placement.cy;

     WinSetWindowPos( MinMax_window, NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );
    }
  }

 // Возврат.
 return Controls_are_present;
}
