
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ClipperInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Включаем и выключаем выделение строк в текстовых окнах с помощью мыши.
 if( Clipper.Settings.Mouse_in_VIO )
  {
   // Если в окне нажата или отжата кнопка мыши:
   if( ( Message->msg == WM_BUTTON1DOWN ) ||
       ( Message->msg == WM_BUTTON1UP && Clipper.Settings.Mouse_in_VIO_sends_Copy ) )
    {
     // Узнаем окно рамки.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // Если мышь нажата в окне рабочей области:
     if( Message->hwnd == WinWindowFromID( Frame_window, FID_CLIENT ) )
      {
       // Если это окно VIO:
       if( IsVIOWindow( Frame_window ) )
        {
         // Проверяем, нажата ли клавиша "Shift", если это требуется.
         BYTE Perform_action = 1;

         if( Message->msg == WM_BUTTON1DOWN )
          if( Clipper.Settings.Mouse_in_VIO_requires_Shift )
           if( !ShiftIsPressed() )
            Perform_action = 0;

         if( Perform_action )
          {
           // Выбираем действие.
           LONG Action = 0;
           if( Message->msg == WM_BUTTON1DOWN ) Action = SM_BEGIN_VIO_MARKING;
           if( Message->msg == WM_BUTTON1UP ) Action = SM_END_VIO_MARKING;

           // Включаем выделение. Это надо делать еще до того, как сообщение будет
           // отправлено в окно, потому что для начала настоящего выделения окно
           // должно получить сообщение о выборе строки меню и сообщение от мыши.
           if( Action == SM_BEGIN_VIO_MARKING ) Clipper_BeginVIOMarking( Frame_window );

           // Выключаем выделение. Посылаем сообщение в поток.
           if( Action == SM_END_VIO_MARKING ) WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, SM_END_VIO_MARKING, (MPARAM) Frame_window, 0 );
          }
        }
      }
    }
  }

 // Посылаем в окно клавиши "Ctrl + V".
 if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_POST_CTRL_V )
   Clipper_PostCtrlV( (HWND) Message->mp2 );

 // Восстанавливаем содержимое Clipboard.
 if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_RESTORE_CLIPBOARD )
   WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, SM_RESTORE_CLIPBOARD, 0, 0 );

 // Возврат.
 return;
}

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID ClipperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Включаем и выключаем выделение строк в текстовых окнах с помощью клавиатуры.
 // Это надо делать после обработки клавиш "^C/V", чтобы использовать их тоже,
 // и до переназначения клавиш 0..9 на цифровой клавиатуре.
 if( Clipper.Settings.CopyPaste_keys_in_VIO )
  {
   // Следим за нажатиями на клавиши.
   if( Message->msg == WM_CHAR )
    {
     // Смотрим, какая клавиша нажата.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // Если это клавиша "Insert":
     if( Scan_code == SC_INSERT || Scan_code == SC_NUM_0 ) if( !( State & KC_ALT ) )
      {
       // Узнаем окно рамки.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // Если клавиша нажата в окне рабочей области:
       if( Message->hwnd == WinWindowFromID( Frame_window, FID_CLIENT ) )
        {
         // Если это окно VIO и в нем можно выполнять выделение:
         if( IsVIOWindow( Frame_window ) ) if( Clipper_PermissionForMarking( Frame_window ) )
          {
           // Выбираем действие.
           LONG Thread_message = 0; BYTE Post = 0;

           if( State & KC_CTRL ) Thread_message = SM_COPY_VIO_TEXT;
           if( State & KC_SHIFT ) Thread_message = SM_PASTE_VIO_TEXT;

           // Действие надо выполнять только для нажатия, а сбрасывать сообщение - всегда.
           if( !( State & KC_KEYUP ) ) Post = 1;

           // Если действие задано и может быть выполнено:
           if( Thread_message ) if( Post )
            {
             // Посылаем сообщение в поток.
             WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Frame_window, 0 );
            }

           // Если действие задано - сообщение должно быть сброшено.
           if( Thread_message ) *Discarding = 1;
          }
        }
      }
    }
  }

 // Восстанавливаем состояние клавиатуры, если оно было изменено во время переопределения клавиши.
 if( Message->msg == WM_CHAR )
  {
   SHORT State = SHORT1FROMMP( Message->mp1 );
   if( State & KC_KEYUP ) if( PMKeyboardStateIsChanged() ) RestorePMKeyboardState();
  }

 // Возврат.
 return;
}
