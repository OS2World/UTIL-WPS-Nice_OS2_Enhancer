
// ─── Узнает, убрано ли наверх окно OS/2 или Win-OS/2 ───

// Frame_window - окно рамки, которое надо проверить.
BYTE Performer_WindowIsRolled( HWND Frame_window )
{
 // Если это окно OS/2:
 if( !IsWindowsWindow( Frame_window ) )
  {
   // Проверяем его.
   if( Frame_window == RolledWindow() ) return 1;
  }
 // А если это окно Win-OS/2 или Odin:
 else
  {
   // Узнаем окно рабочего стола.
   HWND Desktop = QueryDesktopWindow();

   // Узнаем высоту заголовка окна.
   INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

   // Узнаем размер окна.
   RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

   // Проверяем его.
   if( Rectangle.yTop > TitleBar_height )
    if( Rectangle.yTop < TitleBar_height * 2 ) return 1;
  }

 // Возврат.
 return 0;
}

// ─── Меняет состояние кнопок в окне ───

// Frame_window - окно рамки, Command - действие.
VOID Performer_SetNextButtons( HWND Frame_window, LONG Command )
{
 // Задаем состояние кнопок для окна, когда оно будет увеличено.
 if( Command == MAXIMIZE_ACTION )
  {
   // Узнаем состояние кнопок.
   LONG Buttons = 0;
   FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

   // Прячем кнопку "Увеличить", добавляем кнопки "Восстановить" и "Убрать наверх".
   Buttons &= ~MAXIMIZE_ACTION; Buttons |= RESTORE_ACTION;
   if( PermissionForRolling( Frame_window ) ) Buttons |= ROLLUP_ACTION;

   // Задаем новое состояние кнопок.
   SetProperty( Frame_window, PRP_BUTTONS, &Buttons );
  }

 // Задаем состояние кнопок для окна, когда оно будет восстановлено.
 if( Command == RESTORE_ACTION )
  {
   // Узнаем состояние кнопок.
   LONG Buttons = 0;
   FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

   // Прячем кнопки "Восстановить" и "Убрать наверх", добавляем кнопку "Увеличить".
   Buttons &= ~RESTORE_ACTION; Buttons &= ~ROLLUP_ACTION; Buttons |= MAXIMIZE_ACTION;

   // Задаем новое состояние кнопок.
   SetProperty( Frame_window, PRP_BUTTONS, &Buttons );
  }

 // Возврат.
 return;
}

// ─── Запоминает, было ли окно увеличено. Для этого надо заранее установить состояние кнопок ───

// Frame_window - окно рамки.
VOID SetMaximizeProperty( HWND Frame_window )
{
 // Если состояние кнопок неизвестно - узнаем его.
 LONG Buttons = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

 // Для окон OS/2 - проверяем состояние кнопок.
 BYTE Maximized = 0;

 if( !IsWindowsWindow( Frame_window ) )
  {
   if( Buttons & RESTORE_ACTION ) Maximized = 1;
  }
 // Для окон Win-OS/2 и Odin - проверяем расположение окна.
 else
  {
   // Узнаем размер экрана.
   INT X_Screen = WinQuerySysValue( QueryDesktopWindow(), SV_CXSCREEN );

   // Узнаем размер окна.
   RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

   // Окно может быть увеличено или убрано наверх.
   if( Rectangle.xRight > X_Screen ) Maximized = 1;
   if( Performer_WindowIsRolled( Frame_window ) ) Maximized = 1;
  }

 // Устанавливаем свойство.
 SetProperty( Frame_window, PRP_MAXIMIZED, &Maximized );

 // Возврат.
 return;
}

// ─── Ждет, пока действие будет выполнено ───

// Frame_window - окно рамки, Performed_action - действие, которое выполняется с окном.
// Возвращаемое значение: 1 если действие выполнено и состояние окна изменилось, иначе 0.
BYTE Performer_WaitForNewWindowState( HWND Frame_window, LONG Performed_action )
{
 // Если это окно диалога приложения и оно имеет владельца - ожидание бесполезно, возврат.
 if( WindowIsAppDialog( Frame_window ) ) return 1;

 // Окно может не отвечать на сообщения, поэтому задержка выполняется в течение некоторого времени.
 INT Time = WinGetCurrentTime( Enhancer.Application );
 LONG Current_time = Time + 1;

 while( Current_time > Time && Current_time - Time < 1000 )
  {
   // Узнаем расположение окна и его состояние.
   SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

   // Проверяем состояние окна.
   BYTE State_is_changed = 0;

   if( Performed_action == MAXIMIZE_ACTION ) if( Window_state.fl & SWP_MAXIMIZE ) State_is_changed = 1;
   if( Performed_action == MINIMIZE_ACTION ) if( Window_state.fl & SWP_MINIMIZE ) State_is_changed = 1;
   if( Performed_action == HIDE_ACTION ) if( Window_state.fl & SWP_HIDE ) State_is_changed = 1;

   if( Performed_action == RESTORE_ACTION )
    if( !( Window_state.fl & SWP_MAXIMIZE ) )
     if( !( Window_state.fl & SWP_MINIMIZE ) )
      State_is_changed = 1;

   // Если оно изменилось - проверяем размер окна.
   if( State_is_changed )
    {
     // Узнаем предыдущий размер окна.
     INT Previous_width = 0; FindProperty( Frame_window, PRP_PREVIOUS_WIDTH, &Previous_width );
     INT Previous_height = 0; FindProperty( Frame_window, PRP_PREVIOUS_HEIGHT, &Previous_height );

     // Если он был задан:
     if( Previous_width > 0 && Previous_height > 0 )
      {
       // Узнаем размер окна.
       RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

       // Проверяем его ширину.
       INT Width = Rectangle.xRight - Rectangle.xLeft;
       INT Height = Rectangle.yTop - Rectangle.yBottom;

       if( Width == Previous_width || Height == Previous_height ) State_is_changed = 0;
      }
    }

   // Если все в порядке - возврат.
   if( State_is_changed ) return 1;

   // Ждем некоторое время.
   Retard();

   // Узнаем текущее время.
   Current_time = WinGetCurrentTime( Enhancer.Application );
  }

 // Возврат.
 return 0;
}

// ─── Выполняет определенное действие ───

// Frame_window - окно рамки, Command - действие.
// Возвращаемое значение: 1 если действие выполнено, иначе 0.
// Во время работы возможен повторный вызов, при этом Recursive_calling != 0.
// Called_by_WindowManager - вызов идет от потока для выполнения действий при нажатии на кнопки.
BYTE Performer_PerformAction( HWND Frame_window, LONG Command, BYTE Recursive_calling = 0, BYTE Called_by_WindowManager = 0 )
{
 // Это может быть окно Win-OS/2 или Odin.
 BYTE Is_Windows_window = IsWindowsWindow( Frame_window );

 // Выполняем действие.
 switch( Command )
  {
   // Увеличиваем окно.
   case MAXIMIZE_ACTION:
    {
     // Если это не окно Win-OS/2 или Odin:
     if( !Is_Windows_window )
      {
       // Задаем новое состояние кнопок.
       if( Called_by_WindowManager ) Performer_SetNextButtons( Frame_window, MAXIMIZE_ACTION );

       // Размер прямоугольника для кнопок может измениться. Перерисовываем заголовок и кнопки.
       if( DrawFramesSettingIsON() ) if( WinIsWindowShowing( Frame_window ) )
        WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) ( WT_TITLEBAR | WT_BORDER ) );
      }

     // Запоминаем, было ли окно увеличено.
     SetMaximizeProperty( Frame_window );

     // Меняем состояние окна.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_MAXIMIZE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_MAXIMIZE );
       WinSetWindowPos( Frame_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );
      }

     // Если это не окно Win-OS/2 или Odin:
     if( !Is_Windows_window )
      {
       // Обновляем окно, чтобы не было мусора.
       if( DrawFramesSettingIsON() ) UpdateWindow( Frame_window );
      }
    }
   break;

   // Восстанавливаем окно.
   case RESTORE_ACTION:
    {
     // Если это не окно Win-OS/2 или Odin:
     if( !Is_Windows_window )
      {
       // Задаем новое состояние кнопок.
       if( Called_by_WindowManager ) Performer_SetNextButtons( Frame_window, RESTORE_ACTION );

       // Размер прямоугольника для кнопок может измениться. Перерисовываем заголовок и кнопки.
       if( DrawFramesSettingIsON() ) if( WinIsWindowShowing( Frame_window ) )
        WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) ( WT_TITLEBAR | WT_BORDER ) );
      }

     // Запоминаем, было ли окно увеличено.
     SetMaximizeProperty( Frame_window );

     // Меняем состояние окна.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_RESTORE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_RESTORE );
       WinSetWindowPos( Frame_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );
      }

     // Если это не окно Win-OS/2 или Odin:
     if( !Is_Windows_window )
      {
       // Обновляем окно, чтобы не было мусора.
       if( DrawFramesSettingIsON() ) UpdateWindow( Frame_window );
      }
    }
   break;

   // Уменьшаем окно.
   case MINIMIZE_ACTION:
    {
     // Запоминаем, было ли окно увеличено.
     SetMaximizeProperty( Frame_window );

     // Меняем состояние окна.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_MINIMIZE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_MINIMIZE );
      }
    }
   break;

   // Прячем окно.
   case HIDE_ACTION:
    {
     // Запоминаем, было ли окно увеличено.
     SetMaximizeProperty( Frame_window );

     // Меняем состояние окна.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_HIDE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_HIDE );
      }
    }
   break;

   // Убираем окно наверх.
   case ROLLUP_ACTION:
    {
     // Если это повторный вызов - возврат.
     if( Recursive_calling ) return 0;

     // Если окно не убрано наверх:
     if( Frame_window != RolledWindow() )
      {
       // Если есть другое окно, которое убрано наверх:
       if( RolledWindow() != NULLHANDLE )
        if( WinIsWindow( WinQueryAnchorBlock( RolledWindow() ), RolledWindow() ) )
         {
          // Узнаем расположение и состояние окна.
          SWP Window_placement = {0}; WinQueryWindowPos( RolledWindow(), &Window_placement );

          // Если окно увеличено:
          if( Window_placement.fl & SWP_MAXIMIZE )
           {
            // Если окна имеют общее родительское окно - скрываем окно, которое было убрано наверх
            if( WinQueryWindow( RolledWindow(), QW_PARENT ) == WinQueryWindow( Frame_window, QW_PARENT ) )
             {
              // Узнаем состояние кнопок.
              LONG Buttons = 0; FindProperty( RolledWindow(), PRP_BUTTONS, &Buttons );

              // Скрываем окно или восстанавливаем его.
              INT Command = 0;
              if( Buttons & MINIMIZE_ACTION ) Command = MINIMIZE_ACTION;
              else if( Buttons & HIDE_ACTION ) Command = HIDE_ACTION;
              else if( Buttons & RESTORE_ACTION ) Command = RESTORE_ACTION;

              // Выполняем определенное действие. Посылаем сообщение в поток.
              WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) RolledWindow(), (MPARAM) Command );

              // Окно - неизвестно.
              RememberRolledWindow( NULLHANDLE );
             }
            // Иначе - возвращаем его в обычное состояние.
            else
             {
              // Возвращаем окно в обычное состояние.
              Performer_UnrollWindow( RolledWindow() );
             }
           }
         }

       // Узнаем расположение окна.
       SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

       // Запоминаем окно и его расположение.
       RememberRolledWindow( Frame_window, &Window_placement );

       // Узнаем размер родительского окна.
       HWND Parent_window = WinQueryWindow( Frame_window, QW_PARENT );
       RECT Parent_rectangle = {0}; WinQueryWindowRect( Parent_window, &Parent_rectangle );
       // Чтобы можно было сравнивать точки, уменьшаем значения на единицу.
       Parent_rectangle.xRight --; Parent_rectangle.yTop --;

       // Если окно выступает за пределы родительского окна - уменьшаем прямоугольник.
       INT Top_point = Window_placement.y + Window_placement.cy;
       if( Top_point > Parent_rectangle.yTop )
        {
         INT Offset = Top_point - Parent_rectangle.yTop;
         Window_placement.y -= Offset; Top_point -= Offset;
        }
       if( Window_placement.cx > Parent_rectangle.xRight )
        {
         Window_placement.x = 0;
         Window_placement.cx = Parent_rectangle.xRight + 1;
        }

       // Узнаем размер окна.
       RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );
       // Чтобы можно было сравнивать точки, уменьшаем значения на единицу.
       Rectangle.xRight --; Rectangle.yTop --;

       // Узнаем прямоугольник для кнопок, которые нарисованы в окне.
       RECT All_buttons = {0}; INT Size = CalculateButtonRectangles( Frame_window, &Rectangle, NULLHANDLE, NULL, NULL, NULL, NULL, NULL, &All_buttons );

       // Рассчитываем точки.
       INT Offset = Rectangle.yTop - All_buttons.yTop + 1;
       INT Height = Size + Offset + Offset - 1;
       Window_placement.cy = Height;
       Window_placement.y = Top_point - Window_placement.cy + 1;

       // Передвигаем окно рамки.
       WinSetWindowPos( Frame_window, NULLHANDLE, Window_placement.x, Window_placement.y, Window_placement.cx, Window_placement.cy, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       // Проверяем, как расположено окно.
       SWP New_placement = {0}; WinQueryWindowPos( Frame_window, &New_placement );

       // Если окно вышло за пределы родительского окна:
       INT Limit = Offset * 2;
       if( New_placement.y + New_placement.cy > Parent_rectangle.yTop + Limit )
        {
         // Восстанавливаем окно.
         Performer_PerformAction( Frame_window, RESTORE_ACTION, RECURSIVE_CALLING );

         // Окно - неизвестно.
         RememberRolledWindow( NULLHANDLE );

         // Возврат.
         return 0;
        }

       // Если в окне можно рисовать что-то кроме заголовка:
       if( PermissionForCompleteDrawing( Frame_window ) )
        {
         // Задаем правильное расположение окна картинки, заголовка и других окон. Посылаем сообщение в поток.
         WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_PREPARE_CONTROLS, (MPARAM) Frame_window, 0 );
        }

       // Делаем выбранным окно в середине экрана.
       ActivateWindowInCenter();
      }
     // А если окно убрано наверх - возвращаем его в обычное состояние.
     else
      {
       Performer_UnrollWindow( Frame_window );
      }

     // Обновляем окно, чтобы не было мусора.
     UpdateWindow( Frame_window );
    }
   break;

   // Закрываем окно.
   case CLOSE_ACTION:
    {
     // Направляем сообщения в окно.
     WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
    }
   break;
  }

 // Узнаем действие, которое выполняется с окном.
 BYTE Performed_action = 0; FindProperty( Frame_window, PRP_PERFORMED_ACTION, &Performed_action );

 BYTE Action_completed = 1;

 // Если надо ждать его завершения:
 if( Performed_action )
  {
   // Ждем, пока оно будет выполнено.
   Action_completed = Performer_WaitForNewWindowState( Frame_window, Performed_action );

   // Сбрасываем все связанные с ним свойства.
   Performed_action = 0; SetProperty( Frame_window, PRP_PERFORMED_ACTION, &Performed_action );

   INT Width = -1;  SetProperty( Frame_window, PRP_PREVIOUS_WIDTH, &Width );
   INT Height = -1; SetProperty( Frame_window, PRP_PREVIOUS_HEIGHT, &Height );
  }

 // Возврат.
 return Action_completed;
}

