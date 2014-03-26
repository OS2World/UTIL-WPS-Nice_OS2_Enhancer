
// ��� ��४��砥� ���� �� ���������� �� �ப��⪥ ���� � ������� ��� ���

// Message - ᮮ�饭��, Discarding - ������ ��६�����, 㪠�뢠�� �� �, �� ᮮ�饭�� ������ ���� ��襭�.
VOID MouseMapper_MoveInputFocusWhenScrollingNode( PQMSG Message, PBYTE Discarding )
{
 // �� �ப��⪥ ���� ���뫠�� ᮮ�饭�� � ����⨨ ������ � ��५���� � �� ᠬ�� ����
 // �� ������ �� ������. ��७�ᨬ ���� � ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
 if( Message->msg == WM_CHAR )
  {
   // ����ਬ, ����� ������ �����.
   BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
   SHORT State = SHORT1FROMMP( Message->mp1 );

   // �᫨ ���� ����⨥ ������ � ��५���:
   if( Scan_code == SC_UP || Scan_code == SC_DOWN )
    if( !( State & KC_KEYUP ) ) if( !( State & KC_PREVDOWN ) )
     {
      // �᫨ �� ������ ������ Ctrl, Alt � Shift:
      if( !( State & KC_CTRL ) ) if( !( State & KC_ALT ) ) if( !( State & KC_SHIFT ) )
       if( !CtrlIsPressed() ) if( !AltIsPressed() ) if( !ShiftIsPressed() )
        {
         // �஢��塞, ����� �� ������ � ��५��� �� ᠬ�� ����.
         BYTE Check_input_focus = 0;

         if( Scan_code == SC_UP ) if( !KeyIsPressed( SC_UP ) ) Check_input_focus = 1;
         if( Scan_code == SC_DOWN ) if( !KeyIsPressed( SC_DOWN ) ) Check_input_focus = 1;

         // ������ ����, � ���஥ ���ࠢ��� ���� � ����������.
         HWND Input_window = Message->hwnd;

         // ���� �� ������ ���� ����� ���� ��� ࠬ��.
         if( Check_input_focus )
          {
           if( IsMenuWindow( Input_window ) ) return;
           if( IsFrameWindow( Input_window ) ) return;
          }

         // �஢��塞 ����.
         if( Check_input_focus )
          {
           // ������ ���� ࠡ�祣� �⮫�.
           HWND Desktop = QueryDesktopWindow();

           // ������ ����, ��� ����� �ᯮ����� 㪠��⥫� ���.
           POINT Pointer = {0}; WinQueryPointerPos( Desktop, &Pointer );
           HWND Window_under_pointer = WinWindowFromPoint( Desktop, &Pointer, 1 );

           // �᫨ ⠪�� ���� ����:
           if( Window_under_pointer != NULLHANDLE )
            {
             // ��� ����, ࠬ�� � ����᮪ ��ᬮ�� �� �� ������ ����⢮����.
             if( IsMenuWindow( Window_under_pointer ) ) return;
             if( IsFrameWindow( Window_under_pointer ) ) return;
             if( IsScrollBarWindow( Window_under_pointer ) ) return;

             // �᫨ ���� �� ᮢ������:
             if( Window_under_pointer != Input_window )
              {
               // ������ ��।� ᮮ�饭�� ��� ����.
               HMQ Input_queue = WinQueryWindowULong( Input_window, QWL_HMQ );
               HMQ Pointer_queue = WinQueryWindowULong( Window_under_pointer, QWL_HMQ );

               // �᫨ ��� ���� ����� ����� ��।� ᮮ�饭��:
               if( Input_queue == Pointer_queue )
                {
                 // ������ ������� ���� �ਫ������, � ���ன �ᯮ����� 㪠��⥫� ���.
                 HWND Main_frame_under_pointer = QueryMainWindow( Window_under_pointer );

                 // �᫨ ⠪�� ���� ����:
                 if( Main_frame_under_pointer != NULLHANDLE )
                  {
                   // �᫨ � ��� ����� ��४����� ���� �� ����������:
                   if( MouseMapper_PermissionForInputFocusMoving( Main_frame_under_pointer ) )
                    {
                     // ������ ������� ���� �ਫ������ ��� ����, � ���஥ ���ࠢ��� ����.
                     HWND Main_input_frame = QueryMainWindow( Input_window );

                     // �᫨ �� ���� � � �� ����:
                     if( Main_input_frame == Main_frame_under_pointer )
                      {
                       // ��४��砥� ���� �� ����������.
                       WinSetFocus( Desktop, Window_under_pointer );

                       // �� ᮮ�饭�� ������ ��ࠡ��뢠���� ����⥫�� ⠪, ��� ��� ���
                       // �।�����祭� ��� ������ ���� � ��᫥ �⮣� ��� ������ ���� ��襭�.
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

 // ������.
 return;
}

// ��� ������� ���ﭨ� ��� ��� ���뫠����� ᮮ�饭�� ���

// Message - ᮮ�饭��, ��।������� ����.
VOID MouseMapper_ChangeMouseState( PQMSG Message )
{
 // ������ ���ﭨ� ���.
 HWND Desktop = QueryDesktopWindow();

 BYTE Mouse_state[ 256 ]; bzero( Mouse_state, sizeof( BYTE ) * 256 );
 WinSetKeyboardStateTable( Desktop, Mouse_state, 0 );

 // �몫�砥� �� ������ ��� � ����砥� ���� �� ���.
 Mouse_state[ VK_BUTTON1 ] = 0;
 Mouse_state[ VK_BUTTON2 ] = 0;
 Mouse_state[ VK_BUTTON3 ] = 0;

 if( Message != NULL )
  {
   if( Message->msg == WM_BUTTON1DOWN ) Mouse_state[ VK_BUTTON1 ] = SET_BUTTON_PRESSED;
   if( Message->msg == WM_BUTTON2DOWN ) Mouse_state[ VK_BUTTON2 ] = SET_BUTTON_PRESSED;
   if( Message->msg == WM_BUTTON3DOWN ) Mouse_state[ VK_BUTTON3 ] = SET_BUTTON_PRESSED;
  }

 // ��⠭�������� ����� ���ﭨ� ���.
 WinSetKeyboardStateTable( Desktop, Mouse_state, 1 );

 // ����������, �� ���ﭨ� ��� ��������.
 if( Message != NULL )
  {
   // ����������, �� ���ﭨ� ��� ��������.
   MouseMapper.RTSettings.Mouse_state_is_changed = 1;

   // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���ﭨ� ����� �㤥� ������ �����.
   HMQ Message_queue = WinQueryWindowULong( Message->hwnd, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_MSE_MODIFIERS, 0 );
  }
 // ��� ����������, �� ���ﭨ� ��� ����⠭������.
 else
  {
   // ����������, �� ���ﭨ� ��� ����⠭������.
   MouseMapper.RTSettings.Mouse_state_is_changed = 0;
  }

 // ������.
 return;
}

// ��� ����⠭�������� ���ﭨ� ��� ���

VOID MouseMapper_RestoreMouseState( VOID )
{
 // ����⠭�������� ���ﭨ� ���.
 MouseMapper_ChangeMouseState( NULL );

 // ������.
 return;
}

// ��� ������� ᮮ�饭�� �� ��� ���

// Message - ᮮ�饭��, ��।������� ����.
VOID MouseMapper_InvertMouseButtons( PQMSG Message )
{
 // ��� ࠬ�� � ���������� �� �� ������ ����⢮����.
 if( IsFrameWindow( Message->hwnd ) ) return;
 if( IsTitleBarWindow( Message->hwnd ) ) return;

 // ���塞 ���� ᮮ�饭��.
 // ���� PS/2 ��⠥� �ࠢ�� ������ ��ன �� ����, ���� PC Systems - ���쥩.
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

 // �� ����⨨ ������ - ���塞 ���ﭨ� ��� �� �६� ����⢨� ����������� ᮮ�饭��.
 if( Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN )
  MouseMapper_ChangeMouseState( Message );

 // �� �⦠⨨ ������ - ��⠭�������� ��४���⥫� �� ���������.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock )
  if( Message->msg == WM_BUTTON1UP || Message->msg == WM_BUTTON2UP || Message->msg == WM_BUTTON3UP )
   if( KeyIsToggled( SC_CAPSLOCK ) || KeyIsPressed( SC_CAPSLOCK ) )
    WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_SET_NUM_LOCK, 0, 0 );

 // ������.
 return;
}

// ��� ������� ᮮ�饭�� �� ��� ���

// Message - ᮮ�饭��, ��।������� ����.
VOID MouseMapper_DefineRightMouseButtonNode( PQMSG Message )
{
 // �஢��塞 ᮮ�饭��, ��।������� ����.
 // ���� PS/2 ��⠥� �ࠢ�� ������ ��ன �� ����, ���� PC Systems - ���쥩.
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

 // �᫨ ��祣� ������ �� ���� - ������.
 if( !Right_button_down_message ) if( !Right_button_up_message ) return;

 // �᫨ ������ ��� �뫠 �����:
 if( Right_button_down_message )
  {
   // �஢��塞 ���� � �ᯮ������� 㪠��⥫� ���.
   BYTE Invert_buttons = 0; BYTE Check_pointer_position = 0;

   // �᫨ �� ����᪠ ��ᬮ�� OS/2 - �஢��塞 ����.
   // ��� ��� ����᮪ ��ᬮ�� �������� ������ ����������, �� ��� ���ਭ����� �ࠢ�� ������ ���.
   if( IsScrollBarWindow( Message->hwnd ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // ������� �ਫ������ �஢����� ᮮ�饭��, ����� �롨��� �� �� ��।�,
     // � ��뢠�� ���� �� ����⨨ �ࠢ�� ������ ���. ��� ��� �� ���� ��������.
     if( WindowIsCreatedBy( APP_NEWVIEW, Frame_window ) ) Invert_buttons = 1;
    }

   // �᫨ �� ���� Mozilla, Odin ��� Qt - �ॡ����� �������⥫�� �஢�ન.
   if( IsMozillaLiningWindow( Message->hwnd ) ||
       IsOdinLiningWindow( Message->hwnd ) ||
       IsQtLiningWindow( Message->hwnd ) ) Check_pointer_position = 1;

   // �஢��塞 �ᯮ������� 㪠��⥫� ���.
   if( Check_pointer_position )
    {
     // ������ ࠧ��� ����.
     RECT Rectangle = {0}; WinQueryWindowRect( Message->hwnd, &Rectangle );

     // ������ ���� ࠡ�祣� �⮫�.
     HWND Desktop = QueryDesktopWindow();

     // ������ �ਭ� ����᪨ ��ᬮ��.
     INT Scrollbar_width = Max( WinQuerySysValue( Desktop, SV_CXVSCROLL ), WinQuerySysValue( Desktop, SV_CYHSCROLL ) );

     // ������ �ᯮ������� 㪠��⥫� ���.
     POINT Pointer = { SHORT1FROMMP( Message->mp1 ), SHORT2FROMMP( Message->mp1 ) };

     // �஢��塞 ���.
     INT Limit = Scrollbar_width * 2;

     if( Pointer.x > Rectangle.xRight - Limit )
      if( Pointer.y > 0 && Pointer.y < Rectangle.yTop ) Invert_buttons = 1;
    }

   // �᫨ ���� �������� ������ ���:
   if( Invert_buttons )
    {
     // �����塞 ᮮ�饭��.
     MouseMapper_InvertMouseButtons( Message );

     // ����������, �� ������ ��� ��������.
     MouseMapper.RTSettings.Buttons_are_inverted = 1;
    }
  }

 // �᫨ ������ ��� �뫠 �⦠�:
 if( Right_button_up_message )
  {
   // ������ ����� ���� �⦠� � �� ����, ���⮬� ���� � ����᪠�� ��ᬮ�� ���筮
   // ��뢠�� WinSetCapture � ��墠�뢠�� ���� �� ���, � ᮮ�饭�� �� �⦠⨨ ������
   // ��� ⮦� ���ࠢ����� ���. �᫨ ��������� �� ᮮ�饭��, ���� ��祣� �� ������.
   if( MouseMapper.RTSettings.Buttons_are_inverted )
    {
     // �����塞 ᮮ�饭��.
     MouseMapper_InvertMouseButtons( Message );

     // ����������, �� ������ ��� �����饭� � ���筮� ���ﭨ�.
     MouseMapper.RTSettings.Buttons_are_inverted = 0;
    }
  }

 // ������.
 return;
}

// ��� �ᯮ��㥬 �।��� ������ ��� ��� ࠡ��� � Clipboard ���

// Message - ᮮ�饭��, Discarding - ᮮ�饭�� ������ ���� ��襭�.
VOID MouseMapper_MiddleButtonCopyPasteNode( PQMSG Message, PBYTE Discarding )
{
 // �஢��塞 ᮮ�饭��.
 // ���� PS/2 ��⠥� �।��� ������ ���쥩, ���� PC Systems - ��ன �� ����.
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

 // �� ᮮ�饭�� �� �।��� ������ ��� ������ ���� ��襭�.
 if( Message->msg == WM_MB_Down )         *Discarding = 1;
 if( Message->msg == WM_MB_Up )           *Discarding = 1;
 if( Message->msg == WM_MB_DblClk )       *Discarding = 1;
 if( Message->msg == WM_MB_Motion_start ) *Discarding = 1;
 if( Message->msg == WM_MB_Motion_end )   *Discarding = 1;
 if( Message->msg == WM_MB_Click )        *Discarding = 1;

 // �᫨ ᮮ�饭�� �뫮 �� � ����⨨ �।��� ������ - ����� ��祣� ������ �� ����, ������.
 if( Message->msg != WM_MB_Down ) return;

 // �᫨ �᫮ ������ ��� �� ࠢ�� �६ - ������.
 if( WinQuerySysValue( QueryDesktopWindow(), SV_CMOUSEBUTTONS ) != 3 ) return;

 // �᫨ ����� ������ Ctrl, Shift ��� Alt - ������.
 if( CtrlIsPressed() || AltIsPressed() || ShiftIsPressed() ) return;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // �஢��塞 ᮮ�饭��. �� ����� ���� �����୮� ��� ������� ����⨥ �� ������.
 BYTE Middle_button_clicked = 0; BYTE Middle_button_double_clicked = 0;

 // ������ ⥪�饥 �६�.
 LONG Current_time = WinGetCurrentTime( Enhancer.Application );

 // �᫨ �����⭮ �६� �।��饣� ������:
 if( MouseMapper.RTSettings.WM_MB_Down_time != 0 )
  if( Current_time > MouseMapper.RTSettings.WM_MB_Down_time )
   {
    // ������ �६�, �����筮� ��� �������� ������ �� ������ ���.
    LONG DblClk_delta = WinQuerySysValue( Desktop, SV_DBLCLKTIME );

    // �᫨ ࠧ��� ����� �⮣� �६���:
    if( Current_time - MouseMapper.RTSettings.WM_MB_Down_time < DblClk_delta )
     {
      // �� ������� ����⨥ �� ������ ���.
      Middle_button_double_clicked = 1;

      // �६� ��᫥����� ������ �� �।��� ������ ��� - �������⭮.
      MouseMapper.RTSettings.WM_MB_Down_time = 0;
     }
   }

 // �᫨ �� �� ������� ����⨥ �� ������ ���:
 if( !Middle_button_double_clicked )
  {
   // �� �����୮� ����⨥ �� ������ ���.
   Middle_button_clicked = 1;

   // ���������� ⥪�饥 �६�.
   MouseMapper.RTSettings.WM_MB_Down_time = Current_time;
  }

 // �᫨ ��祣� ������ �� ���� - ������.
 if( !Middle_button_clicked ) if( !Middle_button_double_clicked ) return;

 // ������ ����, � ���஥ ���ࠢ��� ���� �� ����������.
 HWND Input_window = WinQueryFocus( Desktop );

 // �᫨ ��� ����:
 if( Input_window != NULLHANDLE )
  {
   // ���⠢�塞 ᮮ�饭��.
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

   // ���뫠�� ᮮ�饭�� � ��⮪. �� �㤥� ����� ���������� �������� ������.
   WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Input_window, (MPARAM) Accelerator );
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID MouseMapperInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // �⪫�砥� ������� ����⨥ ��� �� ���⨭�� � ����� ���孥� 㣫� ����.
 if( MouseMapper.Settings.Suppress_double_click_in_sysmenu )
  if( Message->msg == WM_BUTTON1DBLCLK || Message->msg == WM_BUTTON2DBLCLK || Message->msg == WM_BUTTON3DBLCLK )
   if( WindowType( Message->hwnd ) == WT_SYSMENU )
    *Discarding = 1;

 // �ᯮ��㥬 �।��� ������ ��� ��� ����������� � ��⠢�� ⥪��.
 if( MouseMapper.Settings.Use_middle_button_for_CopyPaste )
  {
   // ��ࠡ��뢠�� ᮮ�饭�� � ����⨨ �� ������ ���.
   if( ( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST ) ||
       ( Message->msg >= WM_EXTMOUSEFIRST && Message->msg <= WM_EXTMOUSELAST ) )
    MouseMapper_MiddleButtonCopyPasteNode( Message, Discarding );

   // ����뢠�� ᮮ�饭�� � �������� ��� �᫨ ���� �������� �������� ������.
   // �� �⮬ 㪠��⥫� ��� �� �㤥� �������.
   if( MouseMapper.RTSettings.WM_MB_Down_time ) if( Message->msg == WM_MOUSEMOVE )
    if( WinQueryPointer( QueryDesktopWindow() ) == Resources.Pointer_for_CopyPaste )
     *Discarding = 1;
  }

 // �ᯮ��㥬 �ࠢ�� ������ ��� ����� � �������� �����.
 if( MouseMapper.Settings.Use_right_button_in_scrollbars )
  if( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST )
   MouseMapper_DefineRightMouseButtonNode( Message );

 // ���塞 ������ ��� �᫨ ����祭 Caps Lock.
 // ������ WinKey �� ������ ���� ����� - ��� �ᯮ������ �� �맮�� ���� WarpCenter,
 // � �� ����⨨ �� ��� � ���� WarpCenter ���뫠���� ᮮ�饭�� � ����⨨ ������ ���.
 if( MouseMapper.Settings.Invert_mouse_buttons_with_Caps_Lock )
  if( ( Message->msg >= WM_BUTTONCLICKFIRST && Message->msg <= WM_BUTTONCLICKLAST ) ||
      ( Message->msg >= WM_EXTMOUSEFIRST && Message->msg <= WM_EXTMOUSELAST ) )
   if( !WinKeyIsPressed() )
    if( KeyIsToggled( SC_CAPSLOCK ) || KeyIsPressed( SC_CAPSLOCK ) )
     MouseMapper_InvertMouseButtons( Message );

 // ����⠭�������� ���ﭨ� ���.
 // �� ᮮ�饭�� ���뫠���� � ��।� ���� �� ������ ᮮ�饭�� �� ���.
 if( MouseMapper.RTSettings.Mouse_state_is_changed )
  if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
   if( Message->mp1 == (MPARAM) MRK_MSE_MODIFIERS )
    MouseMapper_RestoreMouseState();

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID MouseMapperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ��७�ᨬ ���� �� ���������� ��� 㪠��⥫� ��� �� �ப��⪥.
 if( MouseMapper.Settings.Move_input_focus_when_scrolling ) if( Message->msg == WM_CHAR )
  MouseMapper_MoveInputFocusWhenScrollingNode( Message, Discarding );

 // ������.
 return;
}
