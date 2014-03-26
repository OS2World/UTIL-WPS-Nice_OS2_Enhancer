
// ─── Запоминает или вставляет текст при нажатии на кнопку мыши ───

// Input_window - окно, с которым работает пользователь, Action - действие.
// Accelerator - значение для сообщения WM_COMMAND, если оно было найдено.
VOID MouseMapper_ClipboardMouseAction( HWND Input_window, LONG Action, LONG Accelerator )
{
 // Выбираем действие.
 BYTE Perform_copy = 0; BYTE Perform_paste = 0;

 if( Action == MOUSE_CLIPBOARD_COPY ) Perform_copy = 1;
 if( Action == MOUSE_CLIPBOARD_PASTE ) Perform_paste = 1;

 // Узнаем окно рамки.
 HWND Frame_window = QueryFrameWindow( Input_window );

 // Если мышь нажата в окне рабочей области:
 if( Input_window == WinWindowFromID( Frame_window, FID_CLIENT ) )
  {
   // Если это окно VIO:
   if( IsVIOWindow( Frame_window ) )
    {
     // Посылаем сообщение в поток.
     LONG Thread_message = SM_COPY_VIO_TEXT;
     if( Perform_paste ) Thread_message = SM_PASTE_VIO_TEXT;

     WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Frame_window, 0 );

     // Больше ничего делать не надо, возврат.
     return;
    }
  }

 // Если задан ускоритель:
 if( Accelerator != 0 )
  {
   // Посылаем главному окну приложения сообщение о том, что должно быть выполнено действие, связанное с этим ускорителем.
   WinPostMsg( QueryMainWindow( Frame_window ), WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );
  }
 // А если он не задан:
 else
  {
   // Составляем сообщение о нажатии клавиши.
   INT New_scan_code = SC_INSERT;
   INT Modifiers = KC_CTRL; if( Perform_paste ) Modifiers = KC_SHIFT;

   MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
   MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

   ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, 0, Modifiers );

   // Меняем состояние клавиатуры на время действия сообщения.
   QMSG Message = {0};
   ChangePMKeyboardState( &Message, New_scan_code, Modifiers, 0 );

   // Посылаем в окно сообщение о нажатии клавиши.
   WinPostMsg( Input_window, WM_CHAR, First_parameter_1, Second_parameter_1 );

   // Посылаем в очередь окна сообщение WM_MARK. Когда оно будет получено, состояние можно будет вернуть назад.
   HMQ Message_queue = WinQueryWindowULong( Input_window, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_KBD_MODIFIERS, 0 );

   // Посылаем в окно сообщение об отжатии клавиши.
   WinPostMsg( Input_window, WM_CHAR, First_parameter_2, Second_parameter_2 );
  }

 // Возврат.
 return;
}
