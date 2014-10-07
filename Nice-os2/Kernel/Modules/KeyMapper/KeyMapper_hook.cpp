
// ─── Отключает некоторые клавиши в приложениях ───

// Message - сообщение, Discarding - внешняя переменная, указывает на то, что сообщение должно быть сброшено.
VOID KeyMapper_DiscardKeysForApplications( PQMSG Message, PBYTE Discarding )
{
 // Перед отключением клавиши надо проверить окно и состояние клавиатуры.
 BYTE Discard_key = 0;

 // Если получено сообщение о нажатии клавиши:
 if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );

   // Если это клавиша F3:
   if( KeyMapper.Settings.Discard_F3 ) if( Scan_code == SC_F3 )
    {
     // Для некоторых окон ее надо отключить.
     Discard_key = 0;

     // Узнаем окно, которое сейчас выбрано.
     HWND Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

     // Проверяем его.
     if( WindowIsCreatedBy( APP_VIEWDOC, Active_window ) ) Discard_key = 1;
     if( WindowIsCreatedBy( APP_PMMAIL, Active_window ) ) Discard_key = 1;
     if( WindowIsCreatedBy( APP_FTPPM, Active_window ) ) Discard_key = 1;
    }
  }

 // Если клавишу надо отключить:
 if( Discard_key )
  {
   // Сообщение должно быть сброшено.
   *Discarding = 1;

   // Возврат.
   return;
  }

 // Возврат.
 return;
}

// ─── Определяет клавишу Enter для ввода значения на рабочем столе ───

// Message определяет сообщение, которое передается окну.
VOID KeyMapper_DefineEnter( PQMSG Message )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // Если это не клавиша Enter - возврат.
 if( Scan_code != SC_NEWLINE ) return;

 // Если нажата клавиша Ctrl, Shift или Alt - возврат.
 if( State & KC_CTRL || State & KC_SHIFT || State & KC_ALT ) return;

 // Если это не поле ввода - возврат.
 if( !IsInputFieldWindow( Message->hwnd ) ) return;

 // Если поле ввода расположено не в окне со значками - возврат.
 if( !IsIconViewWindow( WinQueryWindow( Message->hwnd, QW_PARENT ) ) ) return;

 // Составляем сообщение о нажатии клавиши Enter.
 MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
 MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
 ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0 );

 // Изменяем сообщение, передаваемое окну.
 if( !( State & KC_KEYUP ) )
  {
   Message->mp1 = First_parameter_1;
   Message->mp2 = Second_parameter_1;
  }
 else
  {
   Message->mp1 = First_parameter_2;
   Message->mp2 = Second_parameter_2;
  }

 // Возврат.
 return;
}

// ─── Заменяет клавишу "|\" ───

// Message определяет сообщение, которое передается окну, Discarding - сообщение должно быть сброшено.
VOID KeyMapper_DefineDashKey( PQMSG Message, PBYTE Discarding )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 BYTE Repeat = CHAR3FROMMP( Message->mp1 );
 USHORT State = SHORT1FROMMP( Message->mp1 );

 USHORT VKey = SHORT1FROMMP( Message->mp2 );
 USHORT Character = SHORT2FROMMP( Message->mp2 );

 // Должна быть нажата или отжата клавиша "|\".
 if( Scan_code != SC_DASH ) return;

 // Запоминаем состояние клавиш Ctrl и Shift.
 BYTE Ctrl_is_pressed = CtrlIsPressed();
 BYTE Shift_is_pressed = ShiftIsPressed();

 // Переопределяем клавишу так, чтобы она набирала тире.
 if( KeyMapper.Settings.Define_Dash && !Ctrl_is_pressed )
  {
   // Если это окно Mozilla - действие выполнит другой поток.
   BYTE Redirect_message = 0;

   if( WindowIsCreatedBy( APP_MOZILLA, Message->hwnd ) ||
       WindowIsCreatedBy( APP_FIREFOX, Message->hwnd ) ||
       WindowIsCreatedBy( APP_THUNDERBIRD, Message->hwnd ) )
    {
     Redirect_message = 1;
     *Discarding = 1;
    }

   // Если надо направить сообщение в другой поток:
   if( Redirect_message )
    {
     // Если идет нажатие клавиши:
     if( !( State & KC_KEYUP ) )
      {
       // Узнаем состояние CapsLock.
       BYTE CapsLock_is_ON = KeyIsToggled( SC_CAPSLOCK );

       // Посылаем сообщение в поток.
       LONG Thread_message = SM_FFX_PASTE_DASH;

       if( Shift_is_pressed ) Thread_message = SM_FFX_PASTE_QUOTES_1;
       if( Shift_is_pressed && CapsLock_is_ON ) Thread_message = SM_FFX_PASTE_QUOTES_2;

       WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Message->hwnd, 0 );
      }
    }
   // А если надо выполнить действие сразу же:
   else
    {
     // Если сообщение идет в текстовое окно - запоминаем это.
     BYTE Window_is_VIO = 0; if( IsVIOWindow( QueryFrameWindow( Message->hwnd ) ) ) Window_is_VIO = 1;

     // Задаем новое значение в зависимости от страны.
     SHORT Dash = 196; SHORT Quote = 34; SHORT New_character = 0;
     if( Shift_is_pressed ) New_character = Quote;
     else New_character = Dash;

     // Составляем сообщение о нажатии клавиши "|\".
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     if( !Window_is_VIO ) ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_DASH, New_character, 0 );
     else ComposeWMCharMessageForVIOWindow( &First_parameter_1, &Second_parameter_1, SC_DASH, New_character );

     // Изменяем сообщение, передаваемое окну.
     if( !( State & KC_KEYUP ) )
      {
       Message->mp1 = First_parameter_1;
       Message->mp2 = Second_parameter_1;
      }
     else
      {
       if( !Window_is_VIO )
        {
         Message->mp1 = First_parameter_2;
         Message->mp2 = Second_parameter_2;
        }
       else
        {
         *Discarding = 1;
        }
      }
    }

   // Возврат.
   return;
  }

 // Переопределяем клавишу так, чтобы она посылала "Ctrl + W".
 if( KeyMapper.Settings.Define_Ctrl_Dash && Ctrl_is_pressed )
  {
   // Задаем сочетание клавиш.
   CHAR New_character_code = 'W';
   BYTE New_scan_code = SC_W;
   LONG New_modifiers = KC_CTRL;

   if( IsEntryFieldWindow( Message->hwnd ) || IsInputFieldWindow( Message->hwnd ) ) New_character_code = 0;

   // Узнаем окно рамки и главное окно приложения.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );
   HWND Main_window = QueryMainWindow( Frame_window );

   // Смотрим, задан ли ускоритель для окна.
   LONG Accelerator = 0;
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Frame_window, New_scan_code, New_modifiers );
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Main_window, New_scan_code, New_modifiers );

   // Если ускоритель есть:
   if( Accelerator != 0 )
    {
     // Посылаем главному окну приложения сообщение о том, что должно быть выполнено действие, связанное с этим ускорителем.
     if( !( State & KC_KEYUP ) ) WinPostMsg( Main_window, WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );

     // Сообщение должно быть сброшено.
     *Discarding = 1;
    }
   // А если он не задан:
   else
    {
     // Составляем сообщение о нажатии клавиши "|\".
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers );

     // Изменяем сообщение, передаваемое окну.
     if( !( State & KC_KEYUP ) )
      {
       Message->mp1 = First_parameter_1;
       Message->mp2 = Second_parameter_1;
      }
     else
      {
       Message->mp1 = First_parameter_2;
       Message->mp2 = Second_parameter_2;
      }

     // Меняем состояние клавиатуры на время действия сообщения.
     if( !( State & KC_KEYUP ) ) ChangePMKeyboardState( Message, New_scan_code, New_modifiers );
    }

   // Возврат.
   return;
  }

 // Возврат.
 return;
}

// ─── Обрабатывает сообщения о нажатии на клавиши для Clipboard ───

// Message - сообщение, передаваемое окну, Discarding - сообщение должно быть сброшено.
VOID KeyMapper_ClipboardKeysNode( PQMSG Message, PBYTE Discarding )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // Если клавиша Ctrl не нажата - возврат.
 if( !( State & KC_CTRL ) ) return;
 if( !CtrlIsPressed() ) return;

 // Задаем сочетание клавиш.
 CHAR New_character_code = 0;
 BYTE New_scan_code = 0;
 LONG New_modifiers = 0;

 if( Scan_code == SC_C ) { New_scan_code = SC_INSERT;    New_modifiers = KC_CTRL;  }
 if( Scan_code == SC_V ) { New_scan_code = SC_INSERT;    New_modifiers = KC_SHIFT; }
 if( Scan_code == SC_X ) { New_scan_code = SC_DELETE;    New_modifiers = KC_SHIFT; }
 if( Scan_code == SC_Z ) { New_scan_code = SC_BACKSPACE; New_modifiers = KC_ALT;   }

 // Если значение не задано - возврат.
 if( !New_scan_code ) return;

 // Узнаем окно рамки и главное окно приложения.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );
 HWND Main_window = QueryMainWindow( Frame_window );

 // Если надо переопределять клавиши:
 BYTE Define_keys = 0;

 if( WindowIsCreatedBy( APP_MED, Main_window ) ) Define_keys = 1;
 if( WindowIsCreatedBy( APP_PMVIEW, Main_window ) ) Define_keys = 1;

 if( Define_keys )
  {
   // Смотрим, задан ли ускоритель для окна.
   LONG Accelerator = 0;
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Frame_window, New_scan_code, New_modifiers );
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Main_window, New_scan_code, New_modifiers );

   // Если ускоритель есть:
   if( Accelerator != 0 )
    {
     // Посылаем главному окну приложения сообщение о том, что должно быть выполнено действие, связанное с этим ускорителем.
     if( !( State & KC_KEYUP ) ) WinPostMsg( Main_window, WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );

     // Сообщение должно быть сброшено.
     *Discarding = 1;
    }
   // А если он не задан:
   else
    {
     // Составляем сообщение о нажатии клавиши.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers );

     // Изменяем сообщение, передаваемое окну.
     if( !( State & KC_KEYUP ) )
      {
       Message->mp1 = First_parameter_1;
       Message->mp2 = Second_parameter_1;
      }
     else
      {
       Message->mp1 = First_parameter_2;
       Message->mp2 = Second_parameter_2;
      }

     // Меняем состояние клавиатуры на время действия сообщения.
     if( !( State & KC_KEYUP ) ) ChangePMKeyboardState( Message, New_scan_code, New_modifiers );
    }
  }

 // Возврат.
 return;
}

// ─── Включает клавиши управления окном в VIO ───

// Message - сообщение, Discarding - внешняя переменная, указывает на то, что сообщение должно быть сброшено.
VOID KeyMapper_EnableWinMgrKeysInVIO( PQMSG Message, PBYTE Discarding )
{
 // Если получено сообщение о нажатии клавиши:
 if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // Если это клавиша F4 или F9 и нажата клавиша Alt без Shift и Ctrl:
   if( ( Scan_code == SC_F4 || Scan_code == SC_F9 ) &&
       ( State & KC_ALT ) && !( State & KC_SHIFT ) && !( State & KC_CTRL ) )
    {
     // Клавиша может быть нажата в текстовом окне, которое закроется, и отжата
     // в другом текстовом окне. Проверяем, что происходит нажатие клавиши, и она
     // не была нажата раньше - то есть, действие выполняется при первом нажатии.
     if( !( State & KC_KEYUP ) && !( State & KC_PREVDOWN ) )
      {
       // Узнаем окно рамки.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // Если это окно VIO:
       if( IsVIOWindow( Frame_window ) )
        {
         // Выполняем действие.
         if( Scan_code == SC_F4 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Frame_window, (MPARAM) CLOSE_ACTION );
         if( Scan_code == SC_F9 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );

         // Сообщение должно быть сброшено.
         *Discarding = 1;
        }
      }
    }
  }

 // Возврат.
 return;
}

// ─── Включает клавиши управления окном в Qt-окнах ───

// Message - сообщение, Discarding - внешняя переменная, указывает на то, что сообщение должно быть сброшено.
VOID KeyMapper_EnableWinMgrKeysInQt( PQMSG Message, PBYTE Discarding )
{
 // Если получено сообщение о нажатии клавиши:
 if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // Если это клавиша F9 и нажата клавиша Alt без Shift и Ctrl:
   if( ( Scan_code == SC_F9 ) &&
       ( State & KC_ALT ) && !( State & KC_SHIFT ) && !( State & KC_CTRL ) )
    {
     // Клавиша может быть нажата в одном окне, и отжата в другом.
     // Проверяем, что происходит нажатие клавиши, и она не была нажата раньше.
     if( !( State & KC_KEYUP ) && !( State & KC_PREVDOWN ) )
      {
       // Узнаем окно рамки.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // Если это окно VIO:
       if( IsQtFrameWindow( Frame_window ) )
        {
         // Выполняем действие.
         if( Scan_code == SC_F9 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );

         // Сообщение должно быть сброшено.
         *Discarding = 1;
        }
      }
    }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID MapperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Включаем клавиши для того, чтобы запоминаеть и вставлять текст.
 if( KeyMapper.Settings.Define_Ctrl_CV )
  if( Message->msg == WM_CHAR )
   KeyMapper_ClipboardKeysNode( Message, Discarding );

 // Определяем клавишу "|\". Изменяем пришедшее сообщение.
 if( KeyMapper.Settings.Define_Dash || KeyMapper.Settings.Define_Ctrl_Dash )
  if( Message->msg == WM_CHAR )
   KeyMapper_DefineDashKey( Message, Discarding );

 // Определяем клавишу Enter для ввода значения на рабочем столе. Изменяем пришедшее сообщение.
 if( KeyMapper.Settings.Define_Enter )
  if( Message->msg == WM_CHAR )
   KeyMapper_DefineEnter( Message );

 // Отключаем некоторые клавиши в приложениях.
 if( KeyMapper.Settings.Discard_F3 )
  if( Message->msg == WM_CHAR )
   KeyMapper_DiscardKeysForApplications( Message, Discarding );

 // Включаем клавиши управления окном в VIO.
 if( KeyMapper.Settings.Enable_WMKeys_in_VIO )
  if( Message->msg == WM_CHAR )
   KeyMapper_EnableWinMgrKeysInVIO( Message, Discarding );

 // Включаем клавиши управления окном в Qt.
 if( KeyMapper.Settings.Define_Alt_F9 )
  if( Message->msg == WM_CHAR )
   KeyMapper_EnableWinMgrKeysInQt( Message, Discarding );

 // Восстанавливаем состояние клавиатуры, если оно было изменено во время переопределения клавиши.
 if( Message->msg == WM_CHAR )
  {
   SHORT State = SHORT1FROMMP( Message->mp1 );
   if( State & KC_KEYUP ) if( PMKeyboardStateIsChanged() ) RestorePMKeyboardState();
  }

 // Возврат.
 return;
}
