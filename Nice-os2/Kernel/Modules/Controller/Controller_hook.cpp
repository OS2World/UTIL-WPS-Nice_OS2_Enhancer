
// ��� ��।���� ��஢� ������ ��� 1..9 ���

// Message ��।���� ᮮ�饭��, ���஥ ��।����� ����.
VOID Controller_DefineNumKeys( PQMSG Message )
{
 // ����ਬ, ����� ������ �����.
 BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
 SHORT State = SHORT1FROMMP( Message->mp1 );

 // �� ������ ���� ��஢�� ������, �� �� "-" � �� "+".
 if( Scan_code < SC_NUM_FIRST || Scan_code > SC_NUM_LAST ) return;
 if( Scan_code == SC_NUM_MINUS || Scan_code == SC_NUM_PLUS ) return;

 // �᫨ ����� ������ Ctrl, Shift ��� Alt - ������.
 if( State & KC_CTRL || State & KC_SHIFT || State & KC_ALT ) return;

 // ������ ���� ࠬ��.
 HWND Frame_window = QueryFrameWindow( Message->hwnd );

 // �᫨ �� ���� Win-OS/2, � ��८�।����� ������ �� ����, ������.
 if( IsWindowsWindow( Frame_window ) ) return;

 // �᫨ �� ⥪�⮢�� ����, � ��८�।����� ������ �� ����, ������.
 if( IsVIOWindow( Frame_window ) ) return;

 // �᫨ ���� ᮧ���� ।���஬ FTE, � ��८�।����� ������ �� ����, ������.
 if( WindowIsCreatedBy( APP_FTEPM, Message->hwnd ) ) return;

 // ������ ����� ���祭��.
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

 // ���⠢�塞 ᮮ�饭�� � ����⨨ ��஢�� ������.
 MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
 MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
 ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, New_character, 0 );

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

// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID ControllerKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // �⪫�砥� ������ ���뢠���.
 if( Controller.Settings.Suppress_CtrlAltDel || Controller.Settings.Suppress_CtrlBreak ) if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // �⪫�砥� Ctrl + Alt + Del, �᫨ �� �맢�� �࠭�⥫� �࠭�.
   if( Controller.Settings.Suppress_CtrlAltDel )
    if( !( SystemIsLocked() && ShellIsWPS() ) )
     {
      // �� ����⨨ Ctrl ��� Alt �⪫�砥� ������ ��१���㧪� OS/2, �᫨ ��㣠� ������ ⮦� �����.
      if( !( State & KC_KEYUP ) )
       {
        if( Scan_code == SC_LEFT_CTRL || Scan_code == SC_RIGHT_CTRL )
         if( State & KC_ALT || AltIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, 0, 0 );

        if( Scan_code == SC_LEFT_ALT || Scan_code == SC_RIGHT_ALT )
         if( State & KC_CTRL || CtrlIsPressed() )
          WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_CTRL_ALT_DEL, 0, 0 );
       }

      // �� �⦠⨨ Ctrl ��� Alt ᭮�� ����砥� �� �᫨ ��㣠� ������ �� �����.
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

   // �⪫�砥� Ctrl + Break.
   if( Controller.Settings.Suppress_CtrlBreak )
    {
     // ����뢠�� ᮮ�饭��.
     if( Scan_code == SC_BREAK ) *Discarding = 1;
    }
  }

 // ��⠭�������� ��४���⥫� �� ����⨨ � �⦠⨨ Num Lock.
 if( Controller.Settings.Turn_Num_Lock ) if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );

   // �᫨ �� Num Lock - ��⠭�������� ��४���⥫�.
   if( Scan_code == SC_NUMLOCK ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );
  }

 // ��।��塞 ��஢� ������ ��� 1..9. �����塞 ��襤襥 ᮮ�饭��.
 if( Controller.Settings.Turn_Num_Lock ) if( Controller.Settings.Define_Num_keys )
  if( Message->msg == WM_CHAR ) Controller_DefineNumKeys( Message );

 // �몫�砥� ������ "Shift" �� ���������
 if( Controller.Settings.Reset_Shift_keys )
  if( Message->msg == WM_CHAR )
   {
    // �᫨ �� ��������� �⦠� ������:
    SHORT State = SHORT1FROMMP( Message->mp1 );
    if( State & KC_KEYUP )
     {
      // ����ਬ, �� �� ������ �뫠 ⮫쪮 �� �⦠� ���짮��⥫��.
      BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
      USHORT Character = SHORT2FROMMP( Message->mp2 );

      // �᫨ �� �� ������ � �㪢�� � �� ������ � ��५���:
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
        // ���뫠�� ᮮ�饭�� � ��⮪. �� ������ ���� ��襭� � ��室��� ���ﭨ�.
        WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_RESET_SHIFT_KEYS, 0, 0 );
       }
     }
   }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ControllerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // ����砥� Num Lock � �믮��塞 "ࠧ���" ����������.
 // �� ����� ������ ����� ���� ࠬ�� �⠭������ ��࠭��.
 if( Controller.Settings.Turn_Num_Lock || Controller.Settings.SpeedUp_keyboard )
  if( !RoomsChangeIsInProcess() ) if( TopFrameWindowIsActivating( Message ) )
   {
    if( Controller.Settings.Turn_Num_Lock ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );
    if( Controller.Settings.SpeedUp_keyboard ) WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SPEEDUP_KEYBOARD, 0, 0 );
   }

 // ������.
 return;
}

