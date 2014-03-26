
// ─── Определяет цифровые клавиши как 1..9 ───

// Message определяет сообщение, которое передается окну.
VOID Controller_DefineNumKeys( PQMSG Message )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // Это должна быть цифровая клавиша, но не "-" и не "+".
 if( Scan_code < SC_NUM_FIRST || Scan_code > SC_NUM_LAST ) return;
 if( Scan_code == SC_NUM_MINUS || Scan_code == SC_NUM_PLUS ) return;

 // Если нажата клавиша Ctrl, Shift или Alt - возврат.
 if( State & KC_CTRL || State & KC_SHIFT || State & KC_ALT ) return;

 // Узнаем окно рамки.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );

 // Если это окно Win-OS/2, то переопределять клавиши не надо, возврат.
 if( IsWindowsWindow( Frame_window ) ) return;

 // Если это текстовое окно, то переопределять клавиши не надо, возврат.
 if( IsVIOWindow( Frame_window ) ) return;

 // Если окно создано редактором FTE, то переопределять клавиши не надо, возврат.
 if( WindowIsCreatedBy( APP_FTEPM, Message->hwnd ) ) return;

 // Задаем новое значение.
 SHORT New_character = 0; BYTE New_scan_code = 0;

 switch( Scan_code )
  {
   case SC_NUM_7: New_character = '7'; New_scan_code =  8; break;
   case SC_NUM_8: New_character = '8'; New_scan_code =  9; break;
   case SC_NUM_9: New_character = '9'; New_scan_code = 10; break;
   case SC_NUM_4: New_character = '4'; New_scan_code =  5; break;
   case SC_NUM_5: New_character = '5'; New_scan_code =  6; break;
   case SC_NUM_6: New_character = '6'; New_scan_code =  7; break;
   case SC_NUM_1: New_character = '1'; New_scan_code =  2; break;
   case SC_NUM_2: New_character = '2'; New_scan_code =  3; break;
   case SC_NUM_3: New_character = '3'; New_scan_code =  4; break;
   case SC_NUM_0: New_character = '0'; New_scan_code = 11; break;
   case SC_NUM_P: New_character = '.'; New_scan_code = 52; break;
  }

 // Составляем сообщение о нажатии цифровой клавиши.
 MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
 MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
 ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character, 0 );

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

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID ControllerKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Отключаем клавиши прерываний.
 if( Controller.Settings.Suppress_CtrlAltDel || Controller.Settings.Suppress_CtrlBreak ) if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // Отключаем Ctrl + Alt + Del, если не вызван хранитель экрана.
   if( Controller.Settings.Suppress_CtrlAltDel )
    if( !( SystemIsLocked() && ShellIsWPS() ) )
     {
      // При нажатии Ctrl или Alt отключаем клавиши перезагрузки OS/2, если другая клавиша тоже нажата.
      if( !( State & KC_KEYUP ) )
       {
        if( Scan_code == SC_LEFT_CTRL || Scan_code == SC_RIGHT_CTRL )
         if( State & KC_ALT || AltIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, 0, 0 );

        if( Scan_code == SC_LEFT_ALT || Scan_code == SC_RIGHT_ALT )
         if( State & KC_CTRL || CtrlIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, 0, 0 );
       }

      // При отжатии Ctrl или Alt снова включаем их если другая клавиша не нажата.
      if( State & KC_KEYUP )
       {
        if( Scan_code == SC_LEFT_CTRL || Scan_code == SC_RIGHT_CTRL )
         if( !( State & KC_ALT ) ) if( !AltIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, (MPARAM) 1, 0 );

        if( Scan_code == SC_LEFT_ALT || Scan_code == SC_RIGHT_ALT )
         if( !( State & KC_CTRL ) ) if( !CtrlIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, (MPARAM) 1, 0 );
       }
     }

   // Отключаем Ctrl + Break.
   if( Controller.Settings.Suppress_CtrlBreak )
    {
     // Сбрасываем сообщение.
     if( Scan_code == SC_BREAK ) *Discarding = 1;
    }
  }

 // Устанавливаем переключатели при нажатии и отжатии Num Lock.
 if( Controller.Settings.Turn_Num_Lock ) if( Message->msg == WM_CHAR )
  {
   // Смотрим, какая клавиша нажата.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );

   // Если это Num Lock - устанавливаем переключатели.
   if( Scan_code == SC_NUMLOCK ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );
  }

 // Определяем цифровые клавиши как 1..9. Изменяем пришедшее сообщение.
 if( Controller.Settings.Turn_Num_Lock ) if( Controller.Settings.Define_Num_keys )
  if( Message->msg == WM_CHAR ) Controller_DefineNumKeys( Message );

 // Выключаем клавиши "Shift" на клавиатуре
 if( Controller.Settings.Reset_Shift_keys )
  if( Message->msg == WM_CHAR )
   {
    // Если на клавиатуре отжата клавиша:
    SHORT State = SHORT1FROMMP( Message->mp1 );
    if( State & KC_KEYUP )
     {
      // Смотрим, что за клавиша была только что отжата пользователем.
      BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
      USHORT Character = SHORT2FROMMP( Message->mp2 );

      // Если это не клавиша с буквой и не клавиша со стрелкой:
      if( (
           Character <= ' ' || Character > '~'
          ) && (
           Scan_code != SC_LEFT      && Scan_code != SC_RIGHT &&
           Scan_code != SC_UP        && Scan_code != SC_DOWN  &&
           Scan_code != SC_HOME      && Scan_code != SC_END   &&
           Scan_code != SC_PAGEUP    && Scan_code != SC_PAGEDOWN
          ) && (
           Scan_code != SC_NUM_2     && Scan_code != SC_NUM_4 &&
           Scan_code != SC_NUM_5     && Scan_code != SC_NUM_6 &&
           Scan_code != SC_NUM_8
          ) && (
           Scan_code != SC_NUM_SLASH && Scan_code != SC_NUM_MULTIPLE &&
           Scan_code != SC_NUM_MINUS && Scan_code != SC_NUM_PLUS     &&
           Scan_code != SC_NUM_ENTER
          ) )
       {
        // Посылаем сообщение в поток. Все клавиши будут сброшены в исходное состояние.
        WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_RESET_SHIFT_KEYS, 0, 0 );
       }
     }
   }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ControllerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // Включаем Num Lock и выполняем "разгон" клавиатуры.
 // Это можно делать когда окно рамки становится выбранным.
 if( Controller.Settings.Turn_Num_Lock || Controller.Settings.SpeedUp_keyboard )
  if( !RoomsChangeIsInProcess() ) if( TopFrameWindowIsActivating( Message ) )
   {
    if( Controller.Settings.Turn_Num_Lock ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );
    if( Controller.Settings.SpeedUp_keyboard ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SPEEDUP_KEYBOARD, 0, 0 );
   }

 // Возврат.
 return;
}

