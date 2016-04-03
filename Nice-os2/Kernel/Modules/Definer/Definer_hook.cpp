
// ─── Заменяет сообщения о нажатии на клавиши ───

// Message - сообщение, передаваемое окну, State - состояние клавиши, Action - действие, Discarding - сообщение должно быть сброшено.
VOID Definer_ChangeKeyMessage( PQMSG Message, SHORT State, INT Action, PBYTE Discarding )
{
 // Узнаем окно рамки.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );

 // Если это текстовое окно - возврат.
 if( IsVIOWindow( Frame_window ) ) return;

 // Если это приложение для работы с диском - возврат.
 if( WindowIsUsedTo( DO_MANAGE_FILES, Frame_window ) ) return;

 // Если это окно редактора Mr.Ed - возврат.
 if( WindowIsCreatedBy( APP_MED, Frame_window ) ) return;

 // Если это плоское окно, например, LaunchPad - возврат.
 if( FrameType( Message->hwnd ) == FT_FLAT ) return;

 // Задаем новое значение.
 BYTE New_scan_code = 0; LONG Modifiers = 0; CHAR Character = 0;

 switch( Action )
  {
   case CHAR_ESC:        New_scan_code = SC_ESC; break;

   case CHAR_CTRL_F1:    New_scan_code = SC_F1;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F2:    New_scan_code = SC_F2;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F3:    New_scan_code = SC_F3;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F4:    New_scan_code = SC_F4;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F5:    New_scan_code = SC_F5;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F6:    New_scan_code = SC_F6;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F7:    New_scan_code = SC_F7;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F8:    New_scan_code = SC_F8;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F9:    New_scan_code = SC_F9;    Modifiers = KC_CTRL; break;
   case CHAR_CTRL_F10:   New_scan_code = SC_F10;   Modifiers = KC_CTRL; break;

   case CHAR_ALT_F1:     New_scan_code = SC_F1;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F2:     New_scan_code = SC_F2;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F3:     New_scan_code = SC_F3;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F4:     New_scan_code = SC_F4;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F5:     New_scan_code = SC_F5;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F6:     New_scan_code = SC_F6;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F7:     New_scan_code = SC_F7;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F8:     New_scan_code = SC_F8;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F9:     New_scan_code = SC_F9;    Modifiers = KC_ALT; break;
   case CHAR_ALT_F10:    New_scan_code = SC_F10;   Modifiers = KC_ALT; break;

   case CHAR_ALT_LEFT:   New_scan_code = SC_LEFT;  Modifiers = KC_ALT; break;
   case CHAR_ALT_RIGHT:  New_scan_code = SC_RIGHT; Modifiers = KC_ALT; break;

   case CHAR_CTRL_A:     New_scan_code = SC_A;     Modifiers = KC_CTRL; Character = 'a'; break;
   case CHAR_CTRL_B:     New_scan_code = SC_B;     Modifiers = KC_CTRL; Character = 'b'; break;
   case CHAR_CTRL_C:     New_scan_code = SC_C;     Modifiers = KC_CTRL; Character = 'c'; break;
   case CHAR_CTRL_D:     New_scan_code = SC_D;     Modifiers = KC_CTRL; Character = 'd'; break;
   case CHAR_CTRL_E:     New_scan_code = SC_E;     Modifiers = KC_CTRL; Character = 'e'; break;
   case CHAR_CTRL_F:     New_scan_code = SC_F;     Modifiers = KC_CTRL; Character = 'f'; break;
   case CHAR_CTRL_G:     New_scan_code = SC_G;     Modifiers = KC_CTRL; Character = 'g'; break;
   case CHAR_CTRL_H:     New_scan_code = SC_H;     Modifiers = KC_CTRL; Character = 'h'; break;
   case CHAR_CTRL_I:     New_scan_code = SC_I;     Modifiers = KC_CTRL; Character = 'i'; break;
   case CHAR_CTRL_J:     New_scan_code = SC_J;     Modifiers = KC_CTRL; Character = 'j'; break;
   case CHAR_CTRL_K:     New_scan_code = SC_K;     Modifiers = KC_CTRL; Character = 'k'; break;
   case CHAR_CTRL_L:     New_scan_code = SC_L;     Modifiers = KC_CTRL; Character = 'l'; break;
   case CHAR_CTRL_M:     New_scan_code = SC_M;     Modifiers = KC_CTRL; Character = 'm'; break;
   case CHAR_CTRL_N:     New_scan_code = SC_N;     Modifiers = KC_CTRL; Character = 'n'; break;
   case CHAR_CTRL_O:     New_scan_code = SC_O;     Modifiers = KC_CTRL; Character = 'o'; break;
   case CHAR_CTRL_P:     New_scan_code = SC_P;     Modifiers = KC_CTRL; Character = 'p'; break;
   case CHAR_CTRL_Q:     New_scan_code = SC_Q;     Modifiers = KC_CTRL; Character = 'q'; break;
   case CHAR_CTRL_R:     New_scan_code = SC_R;     Modifiers = KC_CTRL; Character = 'r'; break;
   case CHAR_CTRL_S:     New_scan_code = SC_S;     Modifiers = KC_CTRL; Character = 's'; break;
   case CHAR_CTRL_T:     New_scan_code = SC_T;     Modifiers = KC_CTRL; Character = 't'; break;
   case CHAR_CTRL_U:     New_scan_code = SC_U;     Modifiers = KC_CTRL; Character = 'u'; break;
   case CHAR_CTRL_V:     New_scan_code = SC_V;     Modifiers = KC_CTRL; Character = 'v'; break;
   case CHAR_CTRL_W:     New_scan_code = SC_W;     Modifiers = KC_CTRL; Character = 'w'; break;
   case CHAR_CTRL_X:     New_scan_code = SC_X;     Modifiers = KC_CTRL; Character = 'x'; break;
   case CHAR_CTRL_Y:     New_scan_code = SC_Y;     Modifiers = KC_CTRL; Character = 'y'; break;
   case CHAR_CTRL_Z:     New_scan_code = SC_Z;     Modifiers = KC_CTRL; Character = 'z'; break;

   case CHAR_ALT_A:      New_scan_code = SC_A;     Modifiers = KC_ALT;  Character = 'a'; break;
   case CHAR_ALT_B:      New_scan_code = SC_B;     Modifiers = KC_ALT;  Character = 'b'; break;
   case CHAR_ALT_C:      New_scan_code = SC_C;     Modifiers = KC_ALT;  Character = 'c'; break;
   case CHAR_ALT_D:      New_scan_code = SC_D;     Modifiers = KC_ALT;  Character = 'd'; break;
   case CHAR_ALT_E:      New_scan_code = SC_E;     Modifiers = KC_ALT;  Character = 'e'; break;
   case CHAR_ALT_F:      New_scan_code = SC_F;     Modifiers = KC_ALT;  Character = 'f'; break;
   case CHAR_ALT_G:      New_scan_code = SC_G;     Modifiers = KC_ALT;  Character = 'g'; break;
   case CHAR_ALT_H:      New_scan_code = SC_H;     Modifiers = KC_ALT;  Character = 'h'; break;
   case CHAR_ALT_I:      New_scan_code = SC_I;     Modifiers = KC_ALT;  Character = 'i'; break;
   case CHAR_ALT_J:      New_scan_code = SC_J;     Modifiers = KC_ALT;  Character = 'j'; break;
   case CHAR_ALT_K:      New_scan_code = SC_K;     Modifiers = KC_ALT;  Character = 'k'; break;
   case CHAR_ALT_L:      New_scan_code = SC_L;     Modifiers = KC_ALT;  Character = 'l'; break;
   case CHAR_ALT_M:      New_scan_code = SC_M;     Modifiers = KC_ALT;  Character = 'm'; break;
   case CHAR_ALT_N:      New_scan_code = SC_N;     Modifiers = KC_ALT;  Character = 'n'; break;
   case CHAR_ALT_O:      New_scan_code = SC_O;     Modifiers = KC_ALT;  Character = 'o'; break;
   case CHAR_ALT_P:      New_scan_code = SC_P;     Modifiers = KC_ALT;  Character = 'p'; break;
   case CHAR_ALT_Q:      New_scan_code = SC_Q;     Modifiers = KC_ALT;  Character = 'q'; break;
   case CHAR_ALT_R:      New_scan_code = SC_R;     Modifiers = KC_ALT;  Character = 'r'; break;
   case CHAR_ALT_S:      New_scan_code = SC_S;     Modifiers = KC_ALT;  Character = 's'; break;
   case CHAR_ALT_T:      New_scan_code = SC_T;     Modifiers = KC_ALT;  Character = 't'; break;
   case CHAR_ALT_U:      New_scan_code = SC_U;     Modifiers = KC_ALT;  Character = 'u'; break;
   case CHAR_ALT_V:      New_scan_code = SC_V;     Modifiers = KC_ALT;  Character = 'w'; break;
   case CHAR_ALT_W:      New_scan_code = SC_W;     Modifiers = KC_ALT;  Character = 'w'; break;
   case CHAR_ALT_X:      New_scan_code = SC_X;     Modifiers = KC_ALT;  Character = 'x'; break;
   case CHAR_ALT_Y:      New_scan_code = SC_Y;     Modifiers = KC_ALT;  Character = 'y'; break;
   case CHAR_ALT_Z:      New_scan_code = SC_Z;     Modifiers = KC_ALT;  Character = 'z'; break;
  }

 // Если клавиша не задана - возврат.
 if( New_scan_code == 0 ) return;

 // Составляем сообщение о нажатии клавиши.
 MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
 MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
 ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, Character, Modifiers );

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
 if( !( State & KC_KEYUP ) ) ChangePMKeyboardState( Message, New_scan_code, Modifiers );

 // Возврат.
 return;
}

// ─── Посылает сообщение в поток, выполняющий действия при нажатии на клавиши ───

// Action - действие, которое нужно выполнить, Do_not_check_mouse - отключить проверку мыши.
VOID Definer_GoDefine( INT Action, LONG Do_not_check_mouse = 0 )
{
 // Освобождаем указатель мыши.
 ResetPointer();

 // Посылаем сообщение в поток.
 WinPostQueueMsg( Enhancer.Modules.Launcher->Message_queue, SM_DO_SYSTEM_ACTION, (MPARAM) Action, (MPARAM) Do_not_check_mouse );

 // Возврат.
 return;
}

// ─── Обрабатывает сообщения о нажатии на клавиши ───

// Message - сообщение, передаваемое окну, Discarding - сообщение должно быть сброшено.
VOID Definer_DefineKeysNode( PQMSG Message, PBYTE Discarding )
{
 // Смотрим, какая клавиша нажата.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // Узнаем действие, которое надо выполнить.
 INT Action = 0;

 // Всегда требуется проверка, действительно ли клавиши нажаты.
 // Для правой клавиши Alt надо проверять, нажата ли клавиша Shift.
 // В некоторых случаях Scan-код может быть сброшен переключателем раскладок.
 BYTE Key_should_be_pressed = 1;

 BYTE Check_modifiers = 1;
 BYTE Ctrl_is_required = 0;
 BYTE Alt_is_required = 0;
 BYTE Shift_is_required = 0;

 if( Definer.Settings.Define_common_keys ) if( Scan_code != 0 )
  {
   if( Definer.Settings.Keys.F11 ) if( Scan_code == SC_F11 ) Action = Definer.Settings.Keys.F11;
   if( Definer.Settings.Keys.Shift_F11 ) if( Scan_code == SC_F11 ) if( State & KC_SHIFT ) { Action = Definer.Settings.Keys.Shift_F11; Shift_is_required = 1; }
   if( Definer.Settings.Keys.F12 ) if( Scan_code == SC_F12 ) Action = Definer.Settings.Keys.F12;
   if( Definer.Settings.Keys.Shift_F12 ) if( Scan_code == SC_F12 ) if( State & KC_SHIFT ) { Action = Definer.Settings.Keys.Shift_F12; Shift_is_required = 1; }

   if( Definer.Settings.Keys.PrtScr ) if( Scan_code == SC_PRSCR ) Action = Definer.Settings.Keys.PrtScr;
   if( Definer.Settings.Keys.Pause ) if( Scan_code == SC_PAUSE ) Action = Definer.Settings.Keys.Pause;

   if( Definer.Settings.Keys.SysRq )
    {
     if( Scan_code == SC_SYSRQ ) { Action = Definer.Settings.Keys.SysRq; Check_modifiers = 0; }
     if( Scan_code == SC_PRSCR ) if( State & KC_ALT ) { Action = Definer.Settings.Keys.SysRq; Alt_is_required = 1; }
     if( Scan_code == SC_PRSCR ) if( State & KC_CTRL ) { Action = Definer.Settings.Keys.SysRq; Ctrl_is_required = 1; }
    }

   if( Definer.Settings.Keys.Right_Alt ) if( Scan_code == SC_RIGHT_ALT ) if( !ShiftIsPressed() ) { Action = Definer.Settings.Keys.Right_Alt; Check_modifiers = 0; }
   if( Definer.Settings.Keys.Shift_Right_Alt ) if( Scan_code == SC_RIGHT_ALT ) if( ShiftIsPressed() ) { Action = Definer.Settings.Keys.Shift_Right_Alt; Check_modifiers = 0; }

   if( Definer.Settings.Keys.Left_WinKey ) if( Scan_code == SC_LEFT_WINKEY ) Action = Definer.Settings.Keys.Left_WinKey;
   if( Definer.Settings.Keys.Right_WinKey ) if( Scan_code == SC_RIGHT_WINKEY ) Action = Definer.Settings.Keys.Right_WinKey;
   if( Definer.Settings.Keys.TaskList ) if( Scan_code == SC_WINDOW_LIST ) Action = Definer.Settings.Keys.TaskList;
  }

 if( Definer.Settings.Define_function_keys ) if( Scan_code != 0 )
  {
   if( Definer.Settings.Keys.F1 ) if( Scan_code == SC_F1 ) Action = Definer.Settings.Keys.F1;
   if( Definer.Settings.Keys.F2 ) if( Scan_code == SC_F2 ) Action = Definer.Settings.Keys.F2;
   if( Definer.Settings.Keys.F3 ) if( Scan_code == SC_F3 ) Action = Definer.Settings.Keys.F3;
   if( Definer.Settings.Keys.F4 ) if( Scan_code == SC_F4 ) Action = Definer.Settings.Keys.F4;
   if( Definer.Settings.Keys.F5 ) if( Scan_code == SC_F5 ) Action = Definer.Settings.Keys.F5;
   if( Definer.Settings.Keys.F6 ) if( Scan_code == SC_F6 ) Action = Definer.Settings.Keys.F6;
   if( Definer.Settings.Keys.F7 ) if( Scan_code == SC_F7 ) Action = Definer.Settings.Keys.F7;
   if( Definer.Settings.Keys.F8 ) if( Scan_code == SC_F8 ) Action = Definer.Settings.Keys.F8;
   if( Definer.Settings.Keys.F9 ) if( Scan_code == SC_F9 ) Action = Definer.Settings.Keys.F9;
   if( Definer.Settings.Keys.F10 ) if( Scan_code == SC_F10 ) Action = Definer.Settings.Keys.F10;
  }

 if( Definer.Settings.Define_quick_keys )
  if( State & KC_SHIFT ) if( WinKeyIsPressed() )
   {
    BYTE Action_is_changed = 0;

    if( Scan_code != 0 )
     {
      if( Definer.Settings.Keys.WinKey_Backslash ) if( Scan_code == SC_BACKSLASH ) { Action = Definer.Settings.Keys.WinKey_Backslash; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_Backspace ) if( Scan_code == SC_BACKSPACE ) { Action = Definer.Settings.Keys.WinKey_Backspace; Action_is_changed = 1; }
     }
    else
     {
      if( QuerySystemCodePage() == RUSSIAN && QueryCodePage( Message->hwnd ) == RUSSIAN )
       {
        SHORT Character = SHORT1FROMMP( Message->mp2 );

        if( Character == '|' || Character == '\\' ||
            Character == '(' || Character == ')' ) { Action = Definer.Settings.Keys.WinKey_Backslash; Action_is_changed = 1; }
       }
     }

    if( Action_is_changed ) Shift_is_required = 1;
   }

 if( Definer.Settings.Define_numeric_keys ) if( Scan_code != 0 )
  if( State & KC_SHIFT ) if( WinKeyIsPressed() )
   {
    BYTE Action_is_changed = 0;

    if( Definer.Settings.Keys.WinKey_Num_Slash ) if( Scan_code == SC_NUM_SLASH ) { Action = Definer.Settings.Keys.WinKey_Num_Slash; Action_is_changed = 1; }
    if( Definer.Settings.Keys.WinKey_Num_Multiple ) if( Scan_code == SC_NUM_MULTIPLE ) { Action = Definer.Settings.Keys.WinKey_Num_Multiple; Action_is_changed = 1; }
    if( Definer.Settings.Keys.WinKey_Num_Minus ) if( Scan_code == SC_NUM_MINUS ) { Action = Definer.Settings.Keys.WinKey_Num_Minus; Action_is_changed = 1; }
    if( Definer.Settings.Keys.WinKey_Num_Plus ) if( Scan_code == SC_NUM_PLUS ) { Action = Definer.Settings.Keys.WinKey_Num_Plus; Action_is_changed = 1; }
    if( Definer.Settings.Keys.WinKey_Num_Enter ) if( Scan_code == SC_NUM_ENTER ) { Action = Definer.Settings.Keys.WinKey_Num_Enter; Action_is_changed = 1; }

    if( Action_is_changed ) Shift_is_required = 1;
   }

 if( Definer.Settings.Define_pointer_keys )
  if( State & KC_SHIFT ) if( WinKeyIsPressed() )
   {
    BYTE Action_is_changed = 0;

    if( Scan_code != 0 )
     {
      if( Definer.Settings.Keys.WinKey_F1 ) if( Scan_code == SC_F1 ) { Action = Definer.Settings.Keys.WinKey_F1; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F2 ) if( Scan_code == SC_F2 ) { Action = Definer.Settings.Keys.WinKey_F2; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F3 ) if( Scan_code == SC_F3 ) { Action = Definer.Settings.Keys.WinKey_F3; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F4 ) if( Scan_code == SC_F4 ) { Action = Definer.Settings.Keys.WinKey_F4; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F5 ) if( Scan_code == SC_F5 ) { Action = Definer.Settings.Keys.WinKey_F5; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F6 ) if( Scan_code == SC_F6 ) { Action = Definer.Settings.Keys.WinKey_F6; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F7 ) if( Scan_code == SC_F7 ) { Action = Definer.Settings.Keys.WinKey_F7; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F8 ) if( Scan_code == SC_F8 ) { Action = Definer.Settings.Keys.WinKey_F8; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F9 ) if( Scan_code == SC_F9 ) { Action = Definer.Settings.Keys.WinKey_F9; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F10 ) if( Scan_code == SC_F10 ) { Action = Definer.Settings.Keys.WinKey_F10; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F11 ) if( Scan_code == SC_F11 ) { Action = Definer.Settings.Keys.WinKey_F11; Action_is_changed = 1; }
      if( Definer.Settings.Keys.WinKey_F12 ) if( Scan_code == SC_F12 ) { Action = Definer.Settings.Keys.WinKey_F12; Action_is_changed = 1; }
     }

    if( Scan_code != 0 )
     {
      if( Scan_code >= SC_A_MIN && Scan_code <= SC_A_MAX )
       {
        if( Scan_code == SC_A ) if( Definer.Settings.Keys.WinKey_A ) { Action = Definer.Settings.Keys.WinKey_A; Action_is_changed = 1; }
        if( Scan_code == SC_B ) if( Definer.Settings.Keys.WinKey_B ) { Action = Definer.Settings.Keys.WinKey_B; Action_is_changed = 1; }
        if( Scan_code == SC_C ) if( Definer.Settings.Keys.WinKey_C ) { Action = Definer.Settings.Keys.WinKey_C; Action_is_changed = 1; }
        if( Scan_code == SC_D ) if( Definer.Settings.Keys.WinKey_D ) { Action = Definer.Settings.Keys.WinKey_D; Action_is_changed = 1; }
        if( Scan_code == SC_E ) if( Definer.Settings.Keys.WinKey_E ) { Action = Definer.Settings.Keys.WinKey_E; Action_is_changed = 1; }
        if( Scan_code == SC_F ) if( Definer.Settings.Keys.WinKey_F ) { Action = Definer.Settings.Keys.WinKey_F; Action_is_changed = 1; }
        if( Scan_code == SC_G ) if( Definer.Settings.Keys.WinKey_G ) { Action = Definer.Settings.Keys.WinKey_G; Action_is_changed = 1; }
        if( Scan_code == SC_H ) if( Definer.Settings.Keys.WinKey_H ) { Action = Definer.Settings.Keys.WinKey_H; Action_is_changed = 1; }
        if( Scan_code == SC_I ) if( Definer.Settings.Keys.WinKey_I ) { Action = Definer.Settings.Keys.WinKey_I; Action_is_changed = 1; }
        if( Scan_code == SC_J ) if( Definer.Settings.Keys.WinKey_J ) { Action = Definer.Settings.Keys.WinKey_J; Action_is_changed = 1; }
        if( Scan_code == SC_K ) if( Definer.Settings.Keys.WinKey_K ) { Action = Definer.Settings.Keys.WinKey_K; Action_is_changed = 1; }
        if( Scan_code == SC_L ) if( Definer.Settings.Keys.WinKey_L ) { Action = Definer.Settings.Keys.WinKey_L; Action_is_changed = 1; }
        if( Scan_code == SC_M ) if( Definer.Settings.Keys.WinKey_M ) { Action = Definer.Settings.Keys.WinKey_M; Action_is_changed = 1; }
        if( Scan_code == SC_N ) if( Definer.Settings.Keys.WinKey_N ) { Action = Definer.Settings.Keys.WinKey_N; Action_is_changed = 1; }
        if( Scan_code == SC_O ) if( Definer.Settings.Keys.WinKey_O ) { Action = Definer.Settings.Keys.WinKey_O; Action_is_changed = 1; }
        if( Scan_code == SC_P ) if( Definer.Settings.Keys.WinKey_P ) { Action = Definer.Settings.Keys.WinKey_P; Action_is_changed = 1; }
        if( Scan_code == SC_Q ) if( Definer.Settings.Keys.WinKey_Q ) { Action = Definer.Settings.Keys.WinKey_Q; Action_is_changed = 1; }
        if( Scan_code == SC_R ) if( Definer.Settings.Keys.WinKey_R ) { Action = Definer.Settings.Keys.WinKey_R; Action_is_changed = 1; }
        if( Scan_code == SC_S ) if( Definer.Settings.Keys.WinKey_S ) { Action = Definer.Settings.Keys.WinKey_S; Action_is_changed = 1; }
        if( Scan_code == SC_T ) if( Definer.Settings.Keys.WinKey_T ) { Action = Definer.Settings.Keys.WinKey_T; Action_is_changed = 1; }
        if( Scan_code == SC_U ) if( Definer.Settings.Keys.WinKey_U ) { Action = Definer.Settings.Keys.WinKey_U; Action_is_changed = 1; }
        if( Scan_code == SC_V ) if( Definer.Settings.Keys.WinKey_V ) { Action = Definer.Settings.Keys.WinKey_V; Action_is_changed = 1; }
        if( Scan_code == SC_W ) if( Definer.Settings.Keys.WinKey_W ) { Action = Definer.Settings.Keys.WinKey_W; Action_is_changed = 1; }
        if( Scan_code == SC_X ) if( Definer.Settings.Keys.WinKey_X ) { Action = Definer.Settings.Keys.WinKey_X; Action_is_changed = 1; }
        if( Scan_code == SC_Y ) if( Definer.Settings.Keys.WinKey_Y ) { Action = Definer.Settings.Keys.WinKey_Y; Action_is_changed = 1; }
        if( Scan_code == SC_Z ) if( Definer.Settings.Keys.WinKey_Z ) { Action = Definer.Settings.Keys.WinKey_Z; Action_is_changed = 1; }
       }
     }
    else
     {
      if( QuerySystemCodePage() == RUSSIAN && QueryCodePage( Message->hwnd ) == RUSSIAN )
       {
        SHORT Character = SHORT1FROMMP( Message->mp2 );

        if( ( Character >= 128 && Character <= 175 ) || ( Character >= 224 && Character <= 239 ) )
         {
          if( Character == 'Ф' || Character == 'ф' ) if( Definer.Settings.Keys.WinKey_A ) { Action = Definer.Settings.Keys.WinKey_A; Action_is_changed = 1; }
          if( Character == 'И' || Character == 'и' ) if( Definer.Settings.Keys.WinKey_B ) { Action = Definer.Settings.Keys.WinKey_B; Action_is_changed = 1; }
          if( Character == 'С' || Character == 'с' ) if( Definer.Settings.Keys.WinKey_C ) { Action = Definer.Settings.Keys.WinKey_C; Action_is_changed = 1; }
          if( Character == 'В' || Character == 'в' ) if( Definer.Settings.Keys.WinKey_D ) { Action = Definer.Settings.Keys.WinKey_D; Action_is_changed = 1; }
          if( Character == 'У' || Character == 'у' ) if( Definer.Settings.Keys.WinKey_E ) { Action = Definer.Settings.Keys.WinKey_E; Action_is_changed = 1; }
          if( Character == 'А' || Character == 'а' ) if( Definer.Settings.Keys.WinKey_F ) { Action = Definer.Settings.Keys.WinKey_F; Action_is_changed = 1; }
          if( Character == 'П' || Character == 'п' ) if( Definer.Settings.Keys.WinKey_G ) { Action = Definer.Settings.Keys.WinKey_G; Action_is_changed = 1; }
          if( Character == 'Р' || Character == 'р' ) if( Definer.Settings.Keys.WinKey_H ) { Action = Definer.Settings.Keys.WinKey_H; Action_is_changed = 1; }
          if( Character == 'Ш' || Character == 'ш' ) if( Definer.Settings.Keys.WinKey_I ) { Action = Definer.Settings.Keys.WinKey_I; Action_is_changed = 1; }
          if( Character == 'О' || Character == 'о' ) if( Definer.Settings.Keys.WinKey_J ) { Action = Definer.Settings.Keys.WinKey_J; Action_is_changed = 1; }
          if( Character == 'Л' || Character == 'л' ) if( Definer.Settings.Keys.WinKey_K ) { Action = Definer.Settings.Keys.WinKey_K; Action_is_changed = 1; }
          if( Character == 'Д' || Character == 'д' ) if( Definer.Settings.Keys.WinKey_L ) { Action = Definer.Settings.Keys.WinKey_L; Action_is_changed = 1; }
          if( Character == 'Ь' || Character == 'ь' ) if( Definer.Settings.Keys.WinKey_M ) { Action = Definer.Settings.Keys.WinKey_M; Action_is_changed = 1; }
          if( Character == 'Т' || Character == 'т' ) if( Definer.Settings.Keys.WinKey_N ) { Action = Definer.Settings.Keys.WinKey_N; Action_is_changed = 1; }
          if( Character == 'Щ' || Character == 'щ' ) if( Definer.Settings.Keys.WinKey_O ) { Action = Definer.Settings.Keys.WinKey_O; Action_is_changed = 1; }
          if( Character == 'З' || Character == 'з' ) if( Definer.Settings.Keys.WinKey_P ) { Action = Definer.Settings.Keys.WinKey_P; Action_is_changed = 1; }
          if( Character == 'Й' || Character == 'й' ) if( Definer.Settings.Keys.WinKey_Q ) { Action = Definer.Settings.Keys.WinKey_Q; Action_is_changed = 1; }
          if( Character == 'К' || Character == 'к' ) if( Definer.Settings.Keys.WinKey_R ) { Action = Definer.Settings.Keys.WinKey_R; Action_is_changed = 1; }
          if( Character == 'Ы' || Character == 'ы' ) if( Definer.Settings.Keys.WinKey_S ) { Action = Definer.Settings.Keys.WinKey_S; Action_is_changed = 1; }
          if( Character == 'Е' || Character == 'е' ) if( Definer.Settings.Keys.WinKey_T ) { Action = Definer.Settings.Keys.WinKey_T; Action_is_changed = 1; }
          if( Character == 'Г' || Character == 'г' ) if( Definer.Settings.Keys.WinKey_U ) { Action = Definer.Settings.Keys.WinKey_U; Action_is_changed = 1; }
          if( Character == 'М' || Character == 'м' ) if( Definer.Settings.Keys.WinKey_V ) { Action = Definer.Settings.Keys.WinKey_V; Action_is_changed = 1; }
          if( Character == 'Ц' || Character == 'ц' ) if( Definer.Settings.Keys.WinKey_W ) { Action = Definer.Settings.Keys.WinKey_W; Action_is_changed = 1; }
          if( Character == 'Ч' || Character == 'ч' ) if( Definer.Settings.Keys.WinKey_X ) { Action = Definer.Settings.Keys.WinKey_X; Action_is_changed = 1; }
          if( Character == 'Н' || Character == 'н' ) if( Definer.Settings.Keys.WinKey_Y ) { Action = Definer.Settings.Keys.WinKey_Y; Action_is_changed = 1; }
          if( Character == 'Я' || Character == 'я' ) if( Definer.Settings.Keys.WinKey_Z ) { Action = Definer.Settings.Keys.WinKey_Z; Action_is_changed = 1; }
         }
       }
     }

    if( Action_is_changed ) Shift_is_required = 1;
   }

 if( Definer.Settings.Define_power_keys ) if( Scan_code != 0 )
  {
   SHORT Character = SHORT1FROMMP( Message->mp2 );

   if( Definer.Settings.Keys.Power ) if( Scan_code == SC_ACPI_POWER && Character == 'P' ) { Action = Definer.Settings.Keys.Power; Key_should_be_pressed = 0; }
   if( Definer.Settings.Keys.Sleep ) if( Scan_code == SC_ACPI_SLEEP && Character == 'S' ) { Action = Definer.Settings.Keys.Sleep; Key_should_be_pressed = 0; }
   if( Definer.Settings.Keys.WakeUp ) if( Scan_code == SC_ACPI_WAKE_UP ) Action = Definer.Settings.Keys.WakeUp;
  }

 if( Definer.Settings.Define_multimedia_keys ) if( Scan_code != 0 )
  {
   SHORT Character = SHORT1FROMMP( Message->mp2 );

   if( Definer.Settings.Keys.Play ) if( Scan_code == SC_MM_PLAY ) Action = Definer.Settings.Keys.Play;
   if( Definer.Settings.Keys.Stop ) if( Scan_code == SC_MM_STOP ) Action = Definer.Settings.Keys.Stop;
   if( Definer.Settings.Keys.Previous_track ) if( Scan_code == SC_MM_PREVIOUS_TRACK ) Action = Definer.Settings.Keys.Previous_track;
   if( Definer.Settings.Keys.Next_track ) if( Scan_code == SC_MM_NEXT_TRACK ) Action = Definer.Settings.Keys.Next_track;
   if( Definer.Settings.Keys.Volume_decrement ) if( Scan_code == SC_MM_VOLUME_DECREMENT ) Action = Definer.Settings.Keys.Volume_decrement;
   if( Definer.Settings.Keys.Volume_increment ) if( Scan_code == SC_MM_VOLUME_INCREMENT ) Action = Definer.Settings.Keys.Volume_increment;
   if( Definer.Settings.Keys.Mute ) if( Scan_code == SC_MM_MUTE ) Action = Definer.Settings.Keys.Mute;
   if( Definer.Settings.Keys.Media ) if( Scan_code == SC_MM_MEDIA && Character == 'M' ) { Action = Definer.Settings.Keys.Media; Key_should_be_pressed = 0; }
  }

 if( Definer.Settings.Define_toolkit_keys ) if( Scan_code != 0 )
  {
   SHORT Character = SHORT1FROMMP( Message->mp2 );

   if( Definer.Settings.Keys.Terminal ) if( Scan_code == SC_APP_TERMINAL ) Action = Definer.Settings.Keys.Terminal;
   if( Definer.Settings.Keys.Calculator ) if( Scan_code == SC_APP_CALCULATOR ) Action = Definer.Settings.Keys.Calculator;
   if( Definer.Settings.Keys.Browser ) if( Scan_code == SC_APP_BROWSER ) Action = Definer.Settings.Keys.Browser;
   if( Definer.Settings.Keys.Mail_reader ) if( Scan_code == SC_APP_MAIL_READER && Character == 'M' ) { Action = Definer.Settings.Keys.Mail_reader; Key_should_be_pressed = 0; }
   if( Definer.Settings.Keys.Search ) if( Scan_code == SC_APP_SEARCH ) Action = Definer.Settings.Keys.Search;
   if( Definer.Settings.Keys.Bookmarks ) if( Scan_code == SC_APP_BOOKMARKS ) Action = Definer.Settings.Keys.Bookmarks;
  }

 if( Definer.Settings.Define_internet_keys ) if( Scan_code != 0 )
  {
   if( Definer.Settings.Keys.Back ) if( Scan_code == SC_WEB_BACK ) Action = Definer.Settings.Keys.Back;
   if( Definer.Settings.Keys.Forward ) if( Scan_code == SC_WEB_FORWARD ) Action = Definer.Settings.Keys.Forward;
   if( Definer.Settings.Keys.Cancel ) if( Scan_code == SC_WEB_CANCEL ) Action = Definer.Settings.Keys.Cancel;
   if( Definer.Settings.Keys.Refresh ) if( Scan_code == SC_WEB_REFRESH ) Action = Definer.Settings.Keys.Refresh;
  }

 if( Definer.Settings.Define_scrolling_keys ) if( Scan_code != 0 )
  {
   SHORT Character = SHORT1FROMMP( Message->mp2 );

   if( Definer.Settings.Keys.PageLeft ) if( Scan_code == SC_PAGE_LEFT && Character == 'L' ) { Action = Definer.Settings.Keys.PageLeft; Key_should_be_pressed = 0; }
   if( Definer.Settings.Keys.PageLeft ) if( Scan_code == SC_PAGE_RIGHT && Character == 'R' ) { Action = Definer.Settings.Keys.PageRight; Key_should_be_pressed = 0; }
  }

 if( Definer.Settings.Define_user_keys ) if( Scan_code != 0 )
  {
   if( Definer.Settings.Keys.UserKey_1 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_1 ) Action = Definer.Settings.Keys.UserKey_1;
   if( Definer.Settings.Keys.UserKey_2 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_2 ) Action = Definer.Settings.Keys.UserKey_2;
   if( Definer.Settings.Keys.UserKey_3 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_3 ) Action = Definer.Settings.Keys.UserKey_3;
   if( Definer.Settings.Keys.UserKey_4 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_4 ) Action = Definer.Settings.Keys.UserKey_4;
   if( Definer.Settings.Keys.UserKey_5 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_5 ) Action = Definer.Settings.Keys.UserKey_5;
   if( Definer.Settings.Keys.UserKey_6 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_6 ) Action = Definer.Settings.Keys.UserKey_6;
   if( Definer.Settings.Keys.UserKey_7 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_7 ) Action = Definer.Settings.Keys.UserKey_7;
   if( Definer.Settings.Keys.UserKey_8 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_8 ) Action = Definer.Settings.Keys.UserKey_8;
   if( Definer.Settings.Keys.UserKey_9 ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_9 ) Action = Definer.Settings.Keys.UserKey_9;
   if( Definer.Settings.Keys.UserKey_A ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_A ) Action = Definer.Settings.Keys.UserKey_A;
   if( Definer.Settings.Keys.UserKey_B ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_B ) Action = Definer.Settings.Keys.UserKey_B;
   if( Definer.Settings.Keys.UserKey_C ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_C ) Action = Definer.Settings.Keys.UserKey_C;
   if( Definer.Settings.Keys.UserKey_D ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_D ) Action = Definer.Settings.Keys.UserKey_D;
   if( Definer.Settings.Keys.UserKey_E ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_E ) Action = Definer.Settings.Keys.UserKey_E;
   if( Definer.Settings.Keys.UserKey_F ) if( Scan_code == Definer.Settings.Keys.SC_UserKey_F ) Action = Definer.Settings.Keys.UserKey_F;
  }

 if( Definer.Settings.Define_Cherry_keys ) if( Scan_code != 0 )
  {
  }

 if( Definer.Settings.Define_Compaq_keys ) if( Scan_code != 0 )
  {
   if( Definer.Settings.Keys.Compaq_i ) if( Scan_code == SC_CMQ_I ) Action = Definer.Settings.Keys.Compaq_i;
   if( Definer.Settings.Keys.Compaq_Home ) if( Scan_code == SC_CMQ_HOME ) Action = Definer.Settings.Keys.Compaq_Home;
   if( Definer.Settings.Keys.Compaq_Search ) if( Scan_code == SC_CMQ_SEARCH ) Action = Definer.Settings.Keys.Compaq_Search;
   if( Definer.Settings.Keys.Compaq_Mail ) if( Scan_code == SC_CMQ_MAIL ) Action = Definer.Settings.Keys.Compaq_Mail;
   if( Definer.Settings.Keys.Compaq_People ) if( Scan_code == SC_CMQ_PEOPLE ) Action = Definer.Settings.Keys.Compaq_People;
   if( Definer.Settings.Keys.Compaq_Bench ) if( Scan_code == SC_CMQ_BENCH ) Action = Definer.Settings.Keys.Compaq_Bench;
   if( Definer.Settings.Keys.Compaq_Chat ) if( Scan_code == SC_CMQ_CHAT ) Action = Definer.Settings.Keys.Compaq_Chat;
   if( Definer.Settings.Keys.Compaq_Reading ) if( Scan_code == SC_CMQ_READING ) Action = Definer.Settings.Keys.Compaq_Reading;
  }

 // Если действие было задано:
 if( Action != 0 )
  {
   // Если требуется подменить сообщение:
   if( Action >= CHAR_FIRST && Action <= CHAR_LAST )
    {
     // Выполняем замену. После этого могут применяться другие правила, и если пользователь
     // определил "F11/F12" как "Ctrl + C/V", они будут изменены на "Ctrl/Shift + Insert".
     // Также сообщение может быть заменено на WM_COMMAND, если для него найдется ускоритель.
     Definer_ChangeKeyMessage( Message, State, Action, Discarding );
    }
   // А если требуется выполнить действие:
   else
    {
     // Действие надо выполнять только при нажатии на клавишу.
     if( State & KC_KEYUP ) Action = 0;

     // Если клавиша удерживается в нажатом состоянии - действие выполнять не надо.
     if( State & KC_PREVDOWN )
      if( Action != MM_VOLUME_INCREMENT && Action != MM_VOLUME_DECREMENT )
       if( Action != MM_VOLUME_INCREMENT_MMOS2 && Action != MM_VOLUME_DECREMENT_MMOS2 )
        Action = 0;

     // Если вызвана заставка - переключать окна не надо.
     if( SystemIsLocked() )
      if( Action < MM_FIRST || Action > MM_LAST )
       Action = 0;

     // Если во время получения сообщения клавиша уже не нажата - действие выполнять не надо.
     if( Key_should_be_pressed ) if( Scan_code != 0 ) if( !KeyIsPressed( Scan_code ) ) Action = 0;

     // Проверяем клавиши Ctrl, Alt и Shift.
     if( Check_modifiers )
      {
       if( Ctrl_is_required != -1 )
        {
         if( !Ctrl_is_required ) if( CtrlIsPressed() ) Action = 0;
         if( Ctrl_is_required ) if( !CtrlIsPressed() ) Action = 0;
        }

       if( Alt_is_required != -1 )
        {
         if( !Alt_is_required ) if( AltIsPressed() ) Action = 0;
         if( Alt_is_required ) if( !AltIsPressed() ) Action = 0;
        }

       if( Shift_is_required != -1 )
        {
         if( !Shift_is_required ) if( ShiftIsPressed() ) Action = 0;
         if( Shift_is_required ) if( !ShiftIsPressed() ) Action = 0;
        }
      }

     // Если действие надо выполнить:
     if( Action )
      {
       // Выполняем действие.
       Definer_GoDefine( Action );
      }

     // Сообщение должно быть сброшено.
     *Discarding = 1;
    }
  }

 // Возврат.
 return;
}

// ─── Слежение за сообщениями от клавиатуры ───

// Все переменные - внешние.
VOID DefinerKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // Определяем некоторые клавиши. Посылаем сообщение в поток и сбрасываем пришедшее сообщение.
 if( Definer.Settings.Define_keys )
  if( Message->msg == WM_CHAR )
   Definer_DefineKeysNode( Message, Discarding );

 // Восстанавливаем состояние клавиатуры, если оно было изменено во время переопределения клавиши.
 if( Message->msg == WM_CHAR )
  {
   SHORT State = SHORT1FROMMP( Message->mp1 );
   if( State & KC_KEYUP ) if( PMKeyboardStateIsChanged() ) RestorePMKeyboardState();
  }

 // Возврат.
 return;
}
