
// ─── Переключает ввод от клавиатуры при прокрутке окна с помощью мыши ───

// Message - сообщение, Discarding - внешняя переменная, указывает на то, что сообщение должно быть сброшено.
VOID MouseMapper_MoveInputFocusWhenScrollingNode( PQMSG Message, PBYTE Discarding )
{
 // При прокрутке мышь посылает сообщения о нажатии клавиш со стрелками и на самом деле
 // эти клавиши не нажаты. Переносим ввод в окно, над которым расположен указатель мыши.
 if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // Если идет нажатие клавиши со стрелкой:
   if( Scan_code == SC_UP || Scan_code == SC_DOWN )
    if( !( State & KC_KEYUP ) ) if( !( State & KC_PREVDOWN ) )
     {
      // Если не нажаты клавиши Ctrl, Alt и Shift:
      if( !( State & KC_CTRL ) ) if( !( State & KC_ALT ) ) if( !( State & KC_SHIFT ) )
       if( !CtrlIsPressed() ) if( !AltIsPressed() ) if( !ShiftIsPressed() )
        {
         // Проверяем, нажата ли клавиша со стрелкой на самом деле.
         BYTE Check_input_focus = 0;

         if( Scan_code == SC_UP ) if( !KeyIsPressed( SC_UP ) ) Check_input_focus = 1;
         if( Scan_code == SC_DOWN ) if( !KeyIsPressed( SC_DOWN ) ) Check_input_focus = 1;

         // Узнаем окно, в которое направлен ввод с клавиатуры.
         HWND Input_window = Message->hwnd;

         // Окно не должно быть окном меню или рамки.
         if( Check_input_focus )
          {
           if( IsMenuWindow( Input_window ) ) return;
           if( IsFrameWindow( Input_window ) ) return;
          }

         // Проверяем окна.
         if( Check_input_focus )
          {
           // Узнаем окно рабочего стола.
           HWND Desktop = QueryDesktopWindow();

           // Узнаем окно, над которым расположен указатель мыши.
           POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );
           HWND Window_under_pointer = WinWindowFromPoint( Desktop, &Pointer, 1 );

           // Если такое окно есть:
           if( Window_under_pointer != NULLHANDLE )
            {
             // Для меню, рамок и полосок просмотра это не должно действовать.
             if( IsMenuWindow( Window_under_pointer ) ) return;
             if( IsFrameWindow( Window_under_pointer ) ) return;
             if( IsScrollBarWindow( Window_under_pointer ) ) return;

             // Если окна не совпадают:
             if( Window_under_pointer != Input_window )
              {
               // Узнаем очереди сообщений для окон.
               HMQ Input_queue = WinQueryWindowULong( Input_window, QWL_HMQ );
               HMQ Pointer_queue = WinQueryWindowULong( Window_under_pointer, QWL_HMQ );

               // Если оба окна имеют общую очередь сообщений:
               if( Input_queue == Pointer_queue )
                {
                 // Узнаем главное окно приложения, в которой расположен указатель мыши.
                 HWND Main_frame_under_pointer = QueryMainWindow( Window_under_pointer );

                 // Если такое окно есть:
                 if( Main_frame_under_pointer != NULLHANDLE )
                  {
                   // Если в нем можно переключать ввод от клавиатуры:
                   if( MouseMapper_PermissionForInputFocusMoving( Main_frame_under_pointer ) )
                    {
                     // Узнаем главное окно приложения для окна, в которое направлен ввод.
                     HWND Main_input_frame = QueryMainWindow( Input_window );

                     // Если это одно и то же окно:
                     if( Main_input_frame == Main_frame_under_pointer )
                      {
                       // Переключаем ввод от клавиатуры.
                       WinSetFocus( Desktop, Window_under_pointer );

                       // Это сообщение должно обрабатываться расширителем так, как будто оно
                       // предназначено для нового окна и после этого оно должно быть сброшено.
                       Message->hwnd = Window_under_pointer; *Discarding = 1;
                      }
                    }
                  }
                }
              }
            }
          }
        }
     }
   }

 // Возврат.
 return;
}

// ─── Заменяет состояние мыши для присылаемого сообщения ───

// Message - сообщение, передаваемое окну.
VOID MouseMapper_ChangeMouseState( PQMSG Message )
{
 // Узнаем состояние мыши.
 HWND Desktop = QueryDesktopWindow();

 BYTE Mouse_state[ 256 ]; bzero( Mouse_state, sizeof( BYTE ) * 256 );
 WinSetKeyboardStateTable( Desktop, Mouse_state, 0 );

 // Выключаем все кнопки мыши и включаем одну из них.
 Mouse_state[ VK_BUTTON1 ] = 0;
 Mouse_state[ VK_BUTTON2 ] = 0;
 Mouse_state[ VK_BUTTON3 ] = 0;

 if( Message != NULL )
  {
   if( Message->msg == WM_BUTTON1DOWN ) Mouse_state[ VK_BUTTON1 ] = SET_BUTTON_PRESSED;
   if( Message->msg == WM_BUTTON2DOWN ) Mouse_state[ VK_BUTTON2 ] = SET_BUTTON_PRESSED;
   if( Message->msg == WM_BUTTON3DOWN ) Mouse_state[ VK_BUTTON3 ] = SET_BUTTON_PRESSED;
  }

 // Устанавливаем новое состояние мыши.
 WinSetKeyboardStateTable( Desktop, Mouse_state, 1 );

 // Запоминаем, что состояние мыши изменено.
 if( Message != NULL )
  {
   // Запоминаем, что состояние мыши изменено.
   MouseMapper.RTSettings.Mouse_state_is_changed = 1;

   // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, состояние можно будет вернуть назад.
   HMQ Message_queue = WinQueryWindowULong( Message->hwnd, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_MSE_MODIFIERS, 0 );
  }
 // Или запоминаем, что состояние мыши восстановлено.
 else
  {
   // Запоминаем, что состояние мыши восстановлено.
   MouseMapper.RTSettings.Mouse_state_is_changed = 0;
  }

 // Возврат.
 return;
}

// ─── Восстанавливает состояние мыши ───

VOID MouseMapper_RestoreMouseState( VOID )
{
 // Восстанавливаем состояние мыши.
 MouseMapper_ChangeMouseState( NULL );

 // Возврат.
 return;
}

// ─── Заменяет сообщения от мыши ───

// Message - сообщение, передаваемое окну.
VOID MouseMapper_InvertMouseButtons( PQMSG Message )
{
 // Для рамок и заголовков это не должно действовать.
 if( IsFrameWindow( Message->hwnd ) ) return;
 if( IsTitleBarWindow( Message->hwnd ) ) return;

 // Меняем поле сообщения.
 // Мышь PS/2 считает правую кнопку второй по счету, мышь PC Systems - третьей.
 switch( Message->msg )
  {
   case WM_BUTTON1DOWN:        Message->msg = WM_BUTTON2DOWN;        break;
   case WM_BUTTON1UP:          Message->msg = WM_BUTTON2UP;          break;
   case WM_BUTTON1DBLCLK:      Message->msg = WM_BUTTON2DBLCLK;      break;
   case WM_BUTTON1MOTIONSTART: Message->msg = WM_BUTTON2MOTIONSTART; break;
   case WM_BUTTON1MOTIONEND:   Message->msg = WM_BUTTON2MOTIONEND;   break;
   case WM_BUTTON1CLICK:       Message->msg = WM_BUTTON2CLICK;       break;

   case WM_BUTTON2DOWN:        Message->msg = WM_BUTTON1DOWN;        break;
   case WM_BUTTON2UP:          Message->msg = WM_BUTTON1UP;          break;
   case WM_BUTTON2DBLCLK:      Message->msg = WM_BUTTON1DBLCLK;      break;
   case WM_BUTTON2MOTIONSTART: Message->msg = WM_BUTTON1MOTIONSTART; break;
   case WM_BUTTON2MOTIONEND:   Message->msg = WM_BUTTON1MOTIONEND;   break;
   case WM_BUTTON2CLICK:       Message->msg = WM_BUTTON1CLICK;       break;

   case WM_BUTTON3DOWN:        Message->msg = WM_BUTTON1DOWN;        break;
   case WM_BUTTON3UP:          Message->msg = WM_BUTTON1UP;          break;
   case WM_BUTTON3DBLCLK:      Message->msg = WM_BUTTON1DBLCLK;      break;
   case WM_BUTTON3MOTIONSTART: Message->msg = WM_BUTTON1MOTIONSTART; break;
   case WM_BUTTON3MOTIONEND:   Message->msg = WM_BUTTON1MOTIONEND;   break;
   case WM_BUTTON3CLICK:       Message->msg = WM_BUTTON1CLICK;       break;
  }

 // При нажатии кнопки - меняем состояние мыши на время действия измененного сообщения.
 if( Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN )
  MouseMapper_ChangeMouseState( Message );

 // При отжатии кнопки - устанавливаем переключатели на клавиатуре.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock )
  if( Message->msg == WM_BUTTON1UP || Message->msg == WM_BUTTON2UP || Message->msg == WM_BUTTON3UP )
   if( KeyIsToggled( SC_CAPSLOCK ) || KeyIsPressed( SC_CAPSLOCK ) )
    WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // Возврат.
 return;
}

// ─── Заменяет сообщения от мыши ───

// Message - сообщение, передаваемое окну.
VOID MouseMapper_DefineRightMouseButtonNode( PQMSG Message )
{
 // Проверяем сообщение, передаваемое окну.
 // Мышь PS/2 считает правую кнопку второй по счету, мышь PC Systems - третьей.
 BYTE Right_button_down_message = 0; BYTE Right_button_up_message = 0;

 switch( Message->msg )
  {
   case WM_BUTTON2DOWN:   Right_button_down_message = 1; break;
   case WM_BUTTON2DBLCLK: Right_button_down_message = 1; break;
   case WM_BUTTON2UP:     Right_button_up_message   = 1; break;

   case WM_BUTTON3DOWN:   Right_button_down_message = 1; break;
   case WM_BUTTON3DBLCLK: Right_button_down_message = 1; break;
   case WM_BUTTON3UP:     Right_button_up_message   = 1; break;
  }

 // Если ничего делать не надо - возврат.
 if( !Right_button_down_message ) if( !Right_button_up_message ) return;

 // Если кнопка мыши была нажата:
 if( Right_button_down_message )
  {
   // Проверяем окно и расположение указателя мыши.
   BYTE Invert_buttons = 0; BYTE Check_pointer_position = 0;

   // Если это полоска просмотра OS/2 - проверяем окно.
   // Для всех полосок просмотра заменить кнопки невозможно, но они воспринимают правую кнопку хорошо.
   if( IsScrollBarWindow( Message->hwnd ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Некоторые приложения проверяют сообщения, когда выбирают их из очереди,
     // и вызывают меню при нажатии правой кнопки мыши. Для них ее надо заменить.
     if( WindowIsCreatedBy( APP_NEWVIEW, Frame_window ) ) Invert_buttons = 1;
    }

   // Если это окно Mozilla, Odin или Qt - требуются дополнительные проверки.
   if( IsMozillaLiningWindow( Message->hwnd ) ||
       IsOdinLiningWindow( Message->hwnd ) ||
       IsQtLiningWindow( Message->hwnd ) ) Check_pointer_position = 1;

   // Проверяем расположение указателя мыши.
   if( Check_pointer_position )
    {
     // Узнаем размер окна.
     RECT Rectangle = {0}; WinQueryWindowRect( Message->hwnd, &Rectangle );

     // Узнаем окно рабочего стола.
     HWND Desktop = QueryDesktopWindow();

     // Узнаем ширину полоски просмотра.
     INT Scrollbar_width = Max( WinQuerySysValue( Desktop, SV_CXVSCROLL ), WinQuerySysValue( Desktop, SV_CYHSCROLL ) );

     // Узнаем расположение указателя мыши.
     POINT Pointer = { SHORT1FROMMP( Message->mp1 ), SHORT2FROMMP( Message->mp1 ) };

     // Проверяем его.
     INT Limit = Scrollbar_width * 2;

     if( Pointer.x > Rectangle.xRight - Limit )
      if( Pointer.y > 0 && Pointer.y < Rectangle.yTop ) Invert_buttons = 1;
    }

   // Если надо заменить кнопки мыши:
   if( Invert_buttons )
    {
     // Заменяем сообщение.
     MouseMapper_InvertMouseButtons( Message );

     // Запоминаем, что кнопки мыши изменены.
     MouseMapper.RTSettings.Buttons_are_inverted = 1;
    }
  }

 // Если кнопка мыши была отжата:
 if( Right_button_up_message )
  {
   // Кнопка может быть отжата в любом окне, поэтому окно с полосками просмотра обычно
   // вызывает WinSetCapture и захватывает ввод от мыши, и сообщение об отжатии кнопки
   // мыши тоже направляется ему. Если подменить это сообщение, окно ничего не заметит.
   if( MouseMapper.RTSettings.Buttons_are_inverted )
    {
     // Заменяем сообщение.
     MouseMapper_InvertMouseButtons( Message );

     // Запоминаем, что кнопки мыши возвращены в обычное состояние.
     MouseMapper.RTSettings.Buttons_are_inverted = 0;
    }
  }

 // Возврат.
 return;
}

// ─── Используем среднюю кнопку мыши для работы с Clipboard ───

// Message - сообщение, Discarding - сообщение должно быть сброшено.
VOID MouseMapper_MiddleButtonCopyPasteNode( PQMSG Message, PBYTE Discarding )
{
 // Проверяем сообщение.
 // Мышь PS/2 считает среднюю кнопку третьей, мышь PC Systems - второй по счету.
 LONG WM_MB_Down = WM_BUTTON3DOWN;
 LONG WM_MB_Up = WM_BUTTON3UP;
 LONG WM_MB_DblClk = WM_BUTTON3DBLCLK;
 LONG WM_MB_Motion_start = WM_BUTTON3MOTIONSTART;
 LONG WM_MB_Motion_end = WM_BUTTON3MOTIONEND;
 LONG WM_MB_Click = WM_BUTTON3CLICK;

 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste == 2 )
  {
   WM_MB_Down = WM_BUTTON2DOWN;
   WM_MB_Up = WM_BUTTON2UP;
   WM_MB_DblClk = WM_BUTTON2DBLCLK;
   WM_MB_Motion_start = WM_BUTTON2MOTIONSTART;
   WM_MB_Motion_end = WM_BUTTON2MOTIONEND;
   WM_MB_Click = WM_BUTTON2CLICK;
  }

 // Все сообщения от средней кнопки мыши должны быть сброшены.
 if( Message->msg == WM_MB_Down )         *Discarding = 1;
 if( Message->msg == WM_MB_Up )           *Discarding = 1;
 if( Message->msg == WM_MB_DblClk )       *Discarding = 1;
 if( Message->msg == WM_MB_Motion_start ) *Discarding = 1;
 if( Message->msg == WM_MB_Motion_end )   *Discarding = 1;
 if( Message->msg == WM_MB_Click )        *Discarding = 1;

 // Если сообщение было не о нажатии средней кнопки - больше ничего делать не надо, возврат.
 if( Message->msg != WM_MB_Down ) return;

 // Если число кнопок мыши не равно трем - возврат.
 if( WinQuerySysValue( QueryDesktopWindow(), SV_CMOUSEBUTTONS ) != 3 ) return;

 // Если нажата клавиша Ctrl, Shift или Alt - возврат.
 if( CtrlIsPressed() || AltIsPressed() || ShiftIsPressed() ) return;

 // Узнаем окно рабочего стола.
 HWND Desktop = QueryDesktopWindow();

 // Проверяем сообщение. Это может быть одинарное или двойное нажатие на кнопку.
 BYTE Middle_button_clicked = 0; BYTE Middle_button_double_clicked = 0;

 // Узнаем текущее время.
 LONG Current_time = WinGetCurrentTime( Enhancer.Application );

 // Если известно время предыдущего нажатия:
 if( MouseMapper.RTSettings.WM_MB_Down_time != 0 )
  if( Current_time > MouseMapper.RTSettings.WM_MB_Down_time )
   {
    // Узнаем время, достаточное для двойного нажатия на кнопку мыши.
    LONG DblClk_delta = WinQuerySysValue( Desktop, SV_DBLCLKTIME );

    // Если разница меньше этого времени:
    if( Current_time - MouseMapper.RTSettings.WM_MB_Down_time < DblClk_delta )
     {
      // Это двойное нажатие на кнопку мыши.
      Middle_button_double_clicked = 1;

      // Время последнего нажатия на среднюю кнопку мыши - неизвестно.
      MouseMapper.RTSettings.WM_MB_Down_time = 0;
     }
   }

 // Если это не двойное нажатие на кнопку мыши:
 if( !Middle_button_double_clicked )
  {
   // Это одинарное нажатие на кнопку мыши.
   Middle_button_clicked = 1;

   // Запоминаем текущее время.
   MouseMapper.RTSettings.WM_MB_Down_time = Current_time;
  }

 // Если ничего делать не надо - возврат.
 if( !Middle_button_clicked ) if( !Middle_button_double_clicked ) return;

 // Узнаем окно, в которое направлен ввод от клавиатуры.
 HWND Input_window = WinQueryFocus( Desktop );

 // Если оно есть:
 if( Input_window != NULLHANDLE )
  {
   // Составляем сообщение.
   LONG Thread_message = 0; LONG Accelerator = 0;

   if( Middle_button_clicked )
    {
     Thread_message = SM_MB_CLICK;
     Accelerator = FindRelatedWMCommandAccelerator( QueryMainWindow( Input_window ), SC_INSERT, KC_CTRL );
    }

   if( Middle_button_double_clicked )
    {
     Thread_message = SM_MB_DOUBLECLICK;
     Accelerator = FindRelatedWMCommandAccelerator( QueryMainWindow( Input_window ), SC_INSERT, KC_SHIFT );
    }

   // Посылаем сообщение в поток. Он будет ждать возможного двойного нажатия.
   WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Input_window, (MPARAM) Accelerator );
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID MouseMapperInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Отключаем двойное нажатие мыши на картинку в левом верхнем углу окна.
 if( MouseMapper.Settings.Suppress_double_click_in_sysmenu )
  if( Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK )
   if( WindowType( Message->hwnd ) == WT_SYSMENU )
    *Discarding = 1;

 // Используем среднюю кнопку мыши для запоминания и вставки текста.
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste )
  {
   // Обрабатываем сообщения о нажатии на кнопки мыши.
   if( ( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST ) ||
       ( Message->msg >= WM_EXTMOUSEFIRST && Message->msg <= WM_EXTMOUSELAST ) )
    MouseMapper_MiddleButtonCopyPasteNode( Message, Discarding );

   // Сбрасываем сообщения о движении мыши если идет ожидание двойного нажатия.
   // При этом указатель мыши не будет изменен.
   if( MouseMapper.RTSettings.WM_MB_Down_time ) if( Message->msg == WM_MOUSEMOVE )
    if( WinQueryPointer( QueryDesktopWindow() ) == Resources.Pointer_for_CopyPaste )
     *Discarding = 1;
  }

 // Используем правую кнопку как левую в некоторых окнах.
 if( MouseMapper.Settings.Use_right_button_in_scrollbars )
  if( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST )
   MouseMapper_DefineRightMouseButtonNode( Message );

 // Меняем кнопки мыши если включен Caps Lock.
 // Клавиша WinKey не должна быть нажата - она используется при вызове меню WarpCenter,
 // и при нажатии на нее в окно WarpCenter посылаются сообщения о нажатии кнопки мыши.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock )
  if( ( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST ) ||
      ( Message->msg >= WM_EXTMOUSEFIRST && Message->msg <= WM_EXTMOUSELAST ) )
   if( !WinKeyIsPressed() )
    if( KeyIsToggled( SC_CAPSLOCK ) || KeyIsPressed( SC_CAPSLOCK ) )
     MouseMapper_InvertMouseButtons( Message );

 // Восстанавливаем состояние мыши.
 // Это сообщение посылается в очередь окна при замене сообщений от мыши.
 if( MouseMapper.RTSettings.Mouse_state_is_changed )
  if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
   if( Message->mp1 == (MPARAM) MRK_MSE_MODIFIERS )
    MouseMapper_RestoreMouseState();

 // Возврат.
 return;
}

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID MouseMapperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Переносим ввод от клавиатуры под указатель мыши при прокрутке.
 if( MouseMapper.Settings.Move_input_focus_when_scrolling ) if( Message->msg == WM_CHAR )
  MouseMapper_MoveInputFocusWhenScrollingNode( Message, Discarding );

 // Возврат.
 return;
}
