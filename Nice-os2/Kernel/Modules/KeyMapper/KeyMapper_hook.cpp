
// ��� �⪫�砥� ������� ������ � �ਫ������� ���

// Message - ᮮ�饭��, Discarding - ������ ��६�����, 㪠�뢠�� �� �, �� ᮮ�饭�� ������ ���� ��襭�.
VOID KeyMapper_DiscardKeysForApplications( PQMSG Message, PBYTE Discarding )
{
 // ��। �⪫�祭��� ������ ���� �஢���� ���� � ���ﭨ� ����������.
 BYTE Discard_key = 0;

 // �᫨ ����祭� ᮮ�饭�� � ����⨨ ������:
 if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );

   // �᫨ �� ������ F3:
   if( KeyMapper.Settings.Discard_F3 ) if( Scan_code == SC_F3 )
    {
     // ��� �������� ���� �� ���� �⪫����.
     Discard_key = 0;

     // ������ ����, ���஥ ᥩ�� ��࠭�.
     HWND Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

     // �஢��塞 ���.
     if( WindowIsCreatedBy( APP_VIEWDOC, Active_window ) ) Discard_key = 1;
     if( WindowIsCreatedBy( APP_PMMAIL, Active_window ) ) Discard_key = 1;
     if( WindowIsCreatedBy( APP_FTPPM, Active_window ) ) Discard_key = 1;
    }
  }

 // �᫨ ������� ���� �⪫����:
 if( Discard_key )
  {
   // ����饭�� ������ ���� ��襭�.
   *Discarding = 1;

   // ������.
   return;
  }

 // ������.
 return;
}

// ��� ��।���� ������� Enter ��� ����� ���祭�� �� ࠡ�祬 �⮫� ���

// Message ��।���� ᮮ�饭��, ���஥ ��।����� ����.
VOID KeyMapper_DefineEnter( PQMSG Message )
{
 // ����ਬ, ����� ������ �����.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // �᫨ �� �� ������ Enter - ������.
 if( Scan_code != SC_NEWLINE ) return;

 // �᫨ ����� ������ Ctrl, Shift ��� Alt - ������.
 if( State & KC_CTRL || State & KC_SHIFT || State & KC_ALT ) return;

 // �᫨ �� �� ���� ����� - ������.
 if( !IsInputFieldWindow( Message->hwnd ) ) return;

 // �᫨ ���� ����� �ᯮ������ �� � ���� � ���窠�� - ������.
 if( !IsIconViewWindow( WinQueryWindow( Message->hwnd, QW_PARENT ) ) ) return;

 // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ Enter.
 MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
 MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
 ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0 );

 // �����塞 ᮮ�饭��, ��।������� ����.
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

 // ������.
 return;
}

// ��� ������� ������� "|\" ���

// Message ��।���� ᮮ�饭��, ���஥ ��।����� ����, Discarding - ᮮ�饭�� ������ ���� ��襭�.
VOID KeyMapper_DefineDashKey( PQMSG Message, PBYTE Discarding )
{
 // ����ਬ, ����� ������ �����.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 BYTE Repeat = CHAR3FROMMP( Message->mp1 );
 USHORT State = SHORT1FROMMP( Message->mp1 );

 USHORT VKey = SHORT1FROMMP( Message->mp2 );
 USHORT Character = SHORT2FROMMP( Message->mp2 );

 // ������ ���� ����� ��� �⦠� ������ "|\".
 if( Scan_code != SC_DASH ) return;

 // ���������� ���ﭨ� ������ Ctrl � Shift.
 BYTE Ctrl_is_pressed = CtrlIsPressed();
 BYTE Shift_is_pressed = ShiftIsPressed();

 // ��८�।��塞 ������� ⠪, �⮡� ��� ����ࠫ� ��.
 if( KeyMapper.Settings.Define_Dash && !Ctrl_is_pressed )
  {
   // �᫨ �� ���� Mozilla - ����⢨� �믮���� ��㣮� ��⮪.
   BYTE Redirect_message = 0;

   if( WindowIsCreatedBy( APP_MOZILLA, Message->hwnd ) ||
       WindowIsCreatedBy( APP_FIREFOX, Message->hwnd ) ||
       WindowIsCreatedBy( APP_THUNDERBIRD, Message->hwnd ) )
    {
     Redirect_message = 1;
     *Discarding = 1;
    }

   // �᫨ ���� ���ࠢ��� ᮮ�饭�� � ��㣮� ��⮪:
   if( Redirect_message )
    {
     // �᫨ ���� ����⨥ ������:
     if( !( State & KC_KEYUP ) )
      {
       // ������ ���ﭨ� CapsLock.
       BYTE CapsLock_is_ON = KeyIsToggled( SC_CAPSLOCK );

       // ���뫠�� ᮮ�饭�� � ��⮪.
       LONG Thread_message = SM_FFX_PASTE_DASH;

       if( Shift_is_pressed ) Thread_message = SM_FFX_PASTE_QUOTES_1;
       if( Shift_is_pressed && CapsLock_is_ON ) Thread_message = SM_FFX_PASTE_QUOTES_2;

       WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Message->hwnd, 0 );
      }
    }
   // � �᫨ ���� �믮����� ����⢨� �ࠧ� ��:
   else
    {
     // �᫨ ᮮ�饭�� ���� � ⥪�⮢�� ���� - ���������� ��.
     BYTE Window_is_VIO = 0; if( IsVIOWindow( QueryFrameWindow( Message->hwnd ) ) ) Window_is_VIO = 1;

     // ������ ����� ���祭�� � ����ᨬ��� �� ��࠭�.
     SHORT Dash = 196; SHORT Quote = 34; SHORT New_character = 0;
     if( Shift_is_pressed ) New_character = Quote;
     else New_character = Dash;

     // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ "|\".
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     if( !Window_is_VIO ) ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_DASH, New_character, 0 );
     else ComposeWMCharMessageForVIOWindow( &First_parameter_1, &Second_parameter_1, SC_DASH, New_character );

     // �����塞 ᮮ�饭��, ��।������� ����.
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

   // ������.
   return;
  }

 // ��८�।��塞 ������� ⠪, �⮡� ��� ���뫠�� "Ctrl + W".
 if( KeyMapper.Settings.Define_Ctrl_Dash && Ctrl_is_pressed )
  {
   // ������ ��⠭�� ������.
   CHAR New_character_code = 'W';
   BYTE New_scan_code = SC_W;
   LONG New_modifiers = KC_CTRL;

   if( IsEntryFieldWindow( Message->hwnd ) || IsInputFieldWindow( Message->hwnd ) ) New_character_code = 0;

   // ������ ���� ࠬ�� � ������� ���� �ਫ������.
   HWND Frame_window = QueryFrameWindow( Message->hwnd );
   HWND Main_window = QueryMainWindow( Frame_window );

   // ����ਬ, ����� �� �᪮�⥫� ��� ����.
   LONG Accelerator = 0;
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Frame_window, New_scan_code, New_modifiers );
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Main_window, New_scan_code, New_modifiers );

   // �᫨ �᪮�⥫� ����:
   if( Accelerator != 0 )
    {
     // ���뫠�� �������� ���� �ਫ������ ᮮ�饭�� � ⮬, �� ������ ���� �믮����� ����⢨�, �易���� � �⨬ �᪮�⥫��.
     if( !( State & KC_KEYUP ) ) WinPostMsg( Main_window, WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );

     // ����饭�� ������ ���� ��襭�.
     *Discarding = 1;
    }
   // � �᫨ �� �� �����:
   else
    {
     // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ "|\".
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers );

     // �����塞 ᮮ�饭��, ��।������� ����.
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

     // ���塞 ���ﭨ� ���������� �� �६� ����⢨� ᮮ�饭��.
     if( !( State & KC_KEYUP ) ) ChangePMKeyboardState( Message, New_scan_code, New_modifiers );
    }

   // ������.
   return;
  }

 // ������.
 return;
}

// ��� ��ࠡ��뢠�� ᮮ�饭�� � ����⨨ �� ������ ��� Clipboard ���

// Message - ᮮ�饭��, ��।������� ����, Discarding - ᮮ�饭�� ������ ���� ��襭�.
VOID KeyMapper_ClipboardKeysNode( PQMSG Message, PBYTE Discarding )
{
 // ����ਬ, ����� ������ �����.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // �᫨ ������ Ctrl �� ����� - ������.
 if( !( State & KC_CTRL ) ) return;
 if( !CtrlIsPressed() ) return;

 // ������ ��⠭�� ������.
 CHAR New_character_code = 0;
 BYTE New_scan_code = 0;
 LONG New_modifiers = 0;

 if( Scan_code == SC_C ) { New_scan_code = SC_INSERT;    New_modifiers = KC_CTRL;  }
 if( Scan_code == SC_V ) { New_scan_code = SC_INSERT;    New_modifiers = KC_SHIFT; }
 if( Scan_code == SC_X ) { New_scan_code = SC_DELETE;    New_modifiers = KC_SHIFT; }
 if( Scan_code == SC_Z ) { New_scan_code = SC_BACKSPACE; New_modifiers = KC_ALT;   }

 // �᫨ ���祭�� �� ������ - ������.
 if( !New_scan_code ) return;

 // ������ ���� ࠬ�� � ������� ���� �ਫ������.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );
 HWND Main_window = QueryMainWindow( Frame_window );

 // �᫨ ���� ��८�।����� ������:
 BYTE Define_keys = 0;

 if( WindowIsCreatedBy( APP_MED, Main_window ) ) Define_keys = 1;
 if( WindowIsCreatedBy( APP_PMVIEW, Main_window ) ) Define_keys = 1;

 if( Define_keys )
  {
   // ����ਬ, ����� �� �᪮�⥫� ��� ����.
   LONG Accelerator = 0;
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Frame_window, New_scan_code, New_modifiers );
   if( !Accelerator ) Accelerator = FindRelatedWMCommandAccelerator( Main_window, New_scan_code, New_modifiers );

   // �᫨ �᪮�⥫� ����:
   if( Accelerator != 0 )
    {
     // ���뫠�� �������� ���� �ਫ������ ᮮ�饭�� � ⮬, �� ������ ���� �믮����� ����⢨�, �易���� � �⨬ �᪮�⥫��.
     if( !( State & KC_KEYUP ) ) WinPostMsg( Main_window, WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );

     // ����饭�� ������ ���� ��襭�.
     *Discarding = 1;
    }
   // � �᫨ �� �� �����:
   else
    {
     // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
     MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
     MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

     ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character_code, New_modifiers );

     // �����塞 ᮮ�饭��, ��।������� ����.
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

     // ���塞 ���ﭨ� ���������� �� �६� ����⢨� ᮮ�饭��.
     if( !( State & KC_KEYUP ) ) ChangePMKeyboardState( Message, New_scan_code, New_modifiers );
    }
  }

 // ������.
 return;
}

// ��� ����砥� ������ �ࠢ����� ����� � VIO ���

// Message - ᮮ�饭��, Discarding - ������ ��६�����, 㪠�뢠�� �� �, �� ᮮ�饭�� ������ ���� ��襭�.
VOID KeyMapper_EnableWinMgrKeysInVIO( PQMSG Message, PBYTE Discarding )
{
 // �᫨ ����祭� ᮮ�饭�� � ����⨨ ������:
 if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // �᫨ �� ������ F4 ��� F9 � ����� ������ Alt ��� Shift � Ctrl:
   if( ( Scan_code == SC_F4 || Scan_code == SC_F9 ) &&
       ( State & KC_ALT ) && !( State & KC_SHIFT ) && !( State & KC_CTRL ) )
    {
     // ������ ����� ���� ����� � ⥪�⮢�� ����, ���஥ ���஥���, � �⦠�
     // � ��㣮� ⥪�⮢�� ����. �஢��塞, �� �ந�室�� ����⨥ ������, � ���
     // �� �뫠 ����� ࠭�� - � ����, ����⢨� �믮������ �� ��ࢮ� ����⨨.
     if( !( State & KC_KEYUP ) && !( State & KC_PREVDOWN ) )
      {
       // ������ ���� ࠬ��.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // �᫨ �� ���� VIO:
       if( IsVIOWindow( Frame_window ) )
        {
         // �믮��塞 ����⢨�.
         if( Scan_code == SC_F4 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) Frame_window, (MPARAM) CLOSE_ACTION );
         if( Scan_code == SC_F9 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );

         // ����饭�� ������ ���� ��襭�.
         *Discarding = 1;
        }
      }
    }
  }

 // ������.
 return;
}

// ��� ����砥� ������ �ࠢ����� ����� � Qt-����� ���

// Message - ᮮ�饭��, Discarding - ������ ��६�����, 㪠�뢠�� �� �, �� ᮮ�饭�� ������ ���� ��襭�.
VOID KeyMapper_EnableWinMgrKeysInQt( PQMSG Message, PBYTE Discarding )
{
 // �᫨ ����祭� ᮮ�饭�� � ����⨨ ������:
 if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // �᫨ �� ������ F9 � ����� ������ Alt ��� Shift � Ctrl:
   if( ( Scan_code == SC_F9 ) &&
       ( State & KC_ALT ) && !( State & KC_SHIFT ) && !( State & KC_CTRL ) )
    {
     // ������ ����� ���� ����� � ����� ����, � �⦠� � ��㣮�.
     // �஢��塞, �� �ந�室�� ����⨥ ������, � ��� �� �뫠 ����� ࠭��.
     if( !( State & KC_KEYUP ) && !( State & KC_PREVDOWN ) )
      {
       // ������ ���� ࠬ��.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // �᫨ �� ���� VIO:
       if( IsQtFrameWindow( Frame_window ) )
        {
         // �믮��塞 ����⢨�.
         if( Scan_code == SC_F9 ) WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_HIDE_WINDOW_AWAY, (MPARAM) Frame_window, 0 );

         // ����饭�� ������ ���� ��襭�.
         *Discarding = 1;
        }
      }
    }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID MapperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ����砥� ������ ��� ⮣�, �⮡� ����������� � ��⠢���� ⥪��.
 if( KeyMapper.Settings.Define_Ctrl_CV )
  if( Message->msg == WM_CHAR )
   KeyMapper_ClipboardKeysNode( Message, Discarding );

 // ��।��塞 ������� "|\". �����塞 ��襤襥 ᮮ�饭��.
 if( KeyMapper.Settings.Define_Dash || KeyMapper.Settings.Define_Ctrl_Dash )
  if( Message->msg == WM_CHAR )
   KeyMapper_DefineDashKey( Message, Discarding );

 // ��।��塞 ������� Enter ��� ����� ���祭�� �� ࠡ�祬 �⮫�. �����塞 ��襤襥 ᮮ�饭��.
 if( KeyMapper.Settings.Define_Enter )
  if( Message->msg == WM_CHAR )
   KeyMapper_DefineEnter( Message );

 // �⪫�砥� ������� ������ � �ਫ�������.
 if( KeyMapper.Settings.Discard_F3 )
  if( Message->msg == WM_CHAR )
   KeyMapper_DiscardKeysForApplications( Message, Discarding );

 // ����砥� ������ �ࠢ����� ����� � VIO.
 if( KeyMapper.Settings.Enable_WMKeys_in_VIO )
  if( Message->msg == WM_CHAR )
   KeyMapper_EnableWinMgrKeysInVIO( Message, Discarding );

 // ����砥� ������ �ࠢ����� ����� � Qt.
 if( KeyMapper.Settings.Define_Alt_F9 )
  if( Message->msg == WM_CHAR )
   KeyMapper_EnableWinMgrKeysInQt( Message, Discarding );

 // ����⠭�������� ���ﭨ� ����������, �᫨ ��� �뫮 �������� �� �६� ��८�।������ ������.
 if( Message->msg == WM_CHAR )
  {
   SHORT State = SHORT1FROMMP( Message->mp1 );
   if( State & KC_KEYUP ) if( PMKeyboardStateIsChanged() ) RestorePMKeyboardState();
  }

 // ������.
 return;
}
