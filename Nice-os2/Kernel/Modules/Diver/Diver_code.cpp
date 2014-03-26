
// ��� ������ ���ﭨ� ������ �� 㬮�砭�� ���

// Frame_window - ���� ࠬ��.
LONG Diver_GetPreDefinedButtonsState( HWND Frame_window )
{
 // �᫨ ���� ���⨭�� ��� - ������.
 if( WinWindowFromID( Frame_window, FID_SYSMENU ) == NULLHANDLE ) return NO_ACTION;

 // ������, ��� �룫廊� ࠬ�� ����.
 LONG Frame_type = FrameType( Frame_window );

 // �᫨ ���� ����� ࠬ�� � ���� ��� - �ॡ���� ������ �������.
 if( Frame_type == FT_POINT ) return CLOSE_ACTION;

 // �᫨ �� ���� ����ﭭ��� ࠧ��� - �ॡ���� ������ �������.
 if( Frame_type == FT_CONST )
  if( PermissionForButtonsDrawing( Frame_window ) ) return CLOSE_ACTION;

 // �᫨ ���� ����� ������ ࠬ��:
 if( Frame_type == FT_NORMAL )
  {
   // �᫨ �� ���� �ࠢ�筨�� - ���ﭨ� ������ ����� ���� ���, ������.
   if( WindowIsCreatedBy( APP_VIEWDOC, Frame_window ) ) return NO_ACTION;

   // �᫨ �� ⥪�⮢�� ���� - ���� �ᮢ��� �� ������, ������.
   if( IsVIOWindow( Frame_window ) ) return CLOSE_ACTION | MINIMIZE_ACTION | MAXIMIZE_ACTION;

   // ������ ���ﭨ� ������.
   BYTE Draw_all_buttons = 0;

   // �᫨ �� ���� WPS - ������ ���� ���ᮢ��� �� ������.
   if( IsFolderWindow( Frame_window ) ) Draw_all_buttons = 1;

   // ��� ��, �᫨ � ���� ���� ���� � ��� த�⥫�᪮� ���� - ࠡ�稩 �⮫.
   if( !Draw_all_buttons )
    if( WinWindowFromID( Frame_window, FID_MENU ) != NULLHANDLE )
     if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
      Draw_all_buttons = 1;

   // �᫨ � ���� ������ ���� ���ᮢ��� �� ������:
   if( Draw_all_buttons )
    {
     // ��� �������� ���� �㦭� ⮫쪮 ������ �������.
     if( Painter_OneActionIsAllowed( Frame_window ) ) return CLOSE_ACTION;

     // ��� �������� ���� �� �㦭� ������ 㬥��襭��.
     if( !Painter_MinimizeActionIsAllowed( Frame_window ) ) return CLOSE_ACTION | MAXIMIZE_ACTION;

     // ��� ��⠫��� ���� �㦭� �� �� ������.
     return ALL_ACTIONS;
    }
  }

 // ������.
 return NO_ACTION;
}

// ��� ������ ᢮��⢠ ���� ���

// Frame_window - ���� ࠬ��, Target � Buttons_to_detect - ����� ᢮��⢮ ���� 㧭���.
// Update_frame_if_required - ࠬ�� ����� �������� �᫨ �� �ॡ����.
VOID Diver_QueryWindowProperty( HWND Frame_window, ULONG Target, LONG Buttons_to_detect = ALL_ACTIONS, BYTE Update_frame_if_required = 0 )
{
 // ������ �ᯮ������� ���� � ��� ���ﭨ�.
 SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

 // �᫨ ���� 㬥��襭� � ���箪 ��� ���� - ������.
 if( Window_state.fl & SWP_MINIMIZE || Window_state.fl & SWP_HIDE ) return;

 // ������ ���箪 ����.
 if( Target & WT_SYSMENU )
  {
   // ������ ���箪 ����.
   HPOINTER Icon = Diver_QueryWindowIcon( Frame_window );

   // �᫨ �� ����:
   if( Icon != NULLHANDLE )
    {
     // �᫨ ���箪 ��������� - ࠬ�� ������ ���� ����ᮢ���.
     HPOINTER Previous_icon = NULLHANDLE; FindProperty( Frame_window, PRP_ICON, &Previous_icon );

     if( Icon != Previous_icon )
      {
       // ��⠭�������� ᢮��⢮.
       SetProperty( Frame_window, PRP_ICON, &Icon );

       // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_SYSMENU );
      }
    }
  }

 // ������ �ਭ� ࠬ�� ����.
 if( Target & WT_SYSMENU )
  {
   // ��ࠢ�塞 ᮮ�饭�� � ����.
   Diver.RTSettings.FB_size.x = 0; Diver.RTSettings.FB_size.y = 0;
   WinSendMsg( Frame_window, WM_QUERYBORDERSIZE, (MPARAM) &Diver.RTSettings.FB_size, 0 );

   // ��ਭ�� ࠬ�� �㤥� ����� �������襥 ����祭��� ���祭��.
   INT Width = min( Diver.RTSettings.FB_size.x, Diver.RTSettings.FB_size.y );

   // �᫨ ��� �뫮 ����祭�:
   if( Width != 0 )
    {
     // �᫨ �ਭ� ���������� - ࠬ�� ������ ���� ����ᮢ���.
     INT Previous_width = 0; FindProperty( Frame_window, PRP_BORDER, &Previous_width );

     if( Width != Previous_width )
      {
       // ��⠭�������� ᢮��⢮.
       SetProperty( Frame_window, PRP_BORDER, &Width );

       // ������ ���祭�� �� 㬮�砭��.
       INT System_value = FrameWidth( Frame_window );

       // �᫨ �� ��㣮� ���祭�� - ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
       if( Width != System_value )
        {
         ULONG Update_all = WT_BORDER | WT_SYSMENU | WT_TITLEBAR | WT_MINMAX | WT_MENU;
         WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) Update_all );
        }
      }
    }
  }

 // ������ ��������� ����.
 if( Target & WT_TITLEBAR )
  {
   // ������ ��������� ����.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
   CHAR Title[ SIZE_OF_TITLE ] = ""; QueryWindowTitle( Frame_window, TitleBar_window, Title, Update_frame_if_required );

   // �᫨ ��������� ��।����:
   if( Title[ 0 ] != 0 )
    {
     // �᫨ ��������� ��������� - ࠬ�� ������ ���� ����ᮢ���.
     CHAR Previous_title[ SIZE_OF_TITLE ] = ""; FindProperty( Frame_window, PRP_TITLE, Previous_title );

     if( strcmp( Title, Previous_title ) != EQUALLY )
      {
       // ��⠭�������� ᢮��⢮.
       SetProperty( Frame_window, PRP_TITLE, Title );

       // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_TITLEBAR );
      }
    }
  }

 // ������ ���ﭨ� ������ � �ࠢ�� ���孥� 㣫� ����.
 if( Target & WT_MINMAX )
  {
   // ������, ���� �� �� ᢮��⢮ � ᯨ᪥.
   BYTE Actions_are_detected = 0; FindProperty( Frame_window, PRP_ACTIONS, &Actions_are_detected );

   // �᫨ ��� ��� - 㧭��� ���ﭨ� ������ �� 㬮�砭��.
   if( !Actions_are_detected )
    {
     // ������ ���ﭨ� ������ �� 㬮�砭��.
     LONG Buttons_state = Diver_GetPreDefinedButtonsState( Frame_window );

     // ����������, �� ���ﭨ� ������ ��।�����.
     BYTE Detected = 1; SetProperty( Frame_window, PRP_ACTIONS, &Detected );

     // �᫨ ��� ������ - ࠬ�� ������ ���� ����ᮢ���.
     if( Buttons_state != NO_ACTION )
      {
       // ��⠭�������� ᢮��⢮.
       SetProperty( Frame_window, PRP_BUTTONS, &Buttons_state );

       // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
       WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_BORDER );
      }
    }

   // ������ ���ﭨ� ������ � ����.
   LONG Buttons_state = QueryButtonsState( Frame_window, Buttons_to_detect, 1 );

   // �᫨ ���ﭨ� ������ ���������� - ࠬ�� ������ ���� ����ᮢ���.
   LONG Previous_state = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Previous_state );

   if( Buttons_state != Previous_state )
    {
     // ��⠭�������� ᢮��⢮.
     SetProperty( Frame_window, PRP_BUTTONS, &Buttons_state );

     // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
     WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_BORDER );
    }
  }

 // ������.
 return;
}

// ��� ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ���� ��� � ��।� ���� ���

// Frame_window - ���� ࠬ��.
VOID Diver_CheckWindowFrameDrawingNode( HWND Frame_window )
{
 // ���뫠�� ᮮ�饭�� � ��।�.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
 WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_DRAW_FRAME, (MPARAM) Frame_window );

 // ������.
 return;
}

// ��� �஢���� ࠬ�� ���� ����ﭭ��� ࠧ��� ���

// Frame_window - ���� ࠬ��, Window - ����, ���஥ ���� �஢����.
VOID Diver_CheckWindowFrame( HWND Frame_window, HWND Window )
{
 // ������ ࠧ��� ���� ࠬ��.
 RECT Frame_rectangle = {0}; WinQueryWindowRect( Frame_window, &Frame_rectangle );

 // �஢��塞 ࠬ��.
 if( PermissionForInnerFrameDrawing( Frame_window, Window, &Frame_rectangle ) )
  Diver_CheckWindowFrameDrawingNode( Frame_window );

 // ������.
 return;
}

// ��� �஢���� ���ﭨ� ������ � ����� �ਫ������, � ⠪�� �� ���窨 ���

// Frame_window - ���� ࠬ��.
VOID Diver_CheckWindowControls( HWND Frame_window )
{
 // ������ ��।� ᮮ�饭�� ����.
 HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );

 // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
 HENUM Enumeration = WinBeginEnumWindows( QueryDesktopWindow() ); HWND Window = NULLHANDLE;
 while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
  {
   // �᫨ ���� ���� - �த������ ��ॡ�� ����.
   if( !WinIsWindowVisible( Window ) ) continue;

   // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
   if( !IsFrameWindow( Window ) ) continue;

   // �᫨ �� � �� ᠬ�� ���� - �த������ ��ॡ�� ����.
   if( Window == Frame_window ) continue;

   // ������ ��।� ᮮ�饭�� ����.
   HMQ Window_queue = WinQueryWindowULong( Window, QWL_HMQ );

   // �᫨ ���� �ᯮ���� �� �� ��।� ᮮ�饭�� - ��� ���� �஢����.
   if( Window_queue == Message_queue ) if( PermissionForDrawing( Window ) )
    Diver_QueryWindowProperty( Window, WT_SYSMENU | WT_MINMAX, CLOSE_ACTION );
  }
 WinEndEnumWindows( Enumeration );

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Diver_DiverMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Diver->Priority = MAKELONG( Class, Delta );
  }

 // ������ ᢮��⢠ ����.
 if( Message->msg == SM_QUERY_PROPERTIES )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ������, ����� ᢮��⢮ ���� 㧭���.
   ULONG Target = (ULONG) Message->mp2;

   // ������ ���箪 � �ਭ� ࠬ�� ����.
   if( Target & WT_UNKNOWN || Target & WT_SYSMENU )
    Diver_QueryWindowProperty( Frame_window, WT_SYSMENU );

   // �᫨ ���� ��������� �뫮 ����ᮢ��� - 㧭��� ���������.
   if( Target & WT_UNKNOWN || Target & WT_TITLEBAR ) Diver_QueryWindowProperty( Frame_window, WT_TITLEBAR );

   // �᫨ ��������� ����, �� �� �� �� ��।���� - 㧭��� ���, ����� ����ᮢ뢠���� ࠬ��.
   if( Target & WT_BORDER )
    {
     // ������ ���� ���������.
     HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

     // �᫨ ��� ����:
     if( TitleBar_window != NULLHANDLE )
      {
       // ������, ���� �� � ᯨ᪥ ��������� ����.
       CHAR Title[ SIZE_OF_TITLE ] = ""; FindProperty( Frame_window, PRP_TITLE, Title );

       // �᫨ ��� ��� - 㧭��� ���.
       if( Title[ 0 ] == 0 ) Diver_QueryWindowProperty( Frame_window, WT_TITLEBAR, NO_ACTION, 1 );
      }
    }

   // ������ ���ﭨ� ������ � �ࠢ�� ���孥� 㣫� ����.
   // �஢����� ������ �� Target == WT_TITLEBAR ����� - �����
   // ���������� ����ﭭ�� �ᮢ����, ���஥ �룫廊� ��� "�������" ࠬ��.
   if( Target & WT_UNKNOWN || Target & WT_SYSMENU ) Diver_QueryWindowProperty( Frame_window, WT_MINMAX );

   // �᫨ ���ﭨ� ������ �� �� ��।����� - 㧭��� ���, ����� ����ᮢ뢠���� ࠬ��.
   if( Target & WT_BORDER )
    {
     // ������, ���� �� � ᯨ᪥ ���ﭨ� ������.
     BYTE Actions_are_detected = 0; FindProperty( Frame_window, PRP_ACTIONS, &Actions_are_detected );

     // �᫨ ��� ��� - 㧭��� ���.
     if( !Actions_are_detected ) Diver_QueryWindowProperty( Frame_window, WT_MINMAX );
    }
  }

 // �஢���� ���ﭨ� ��� ����, ����� ���� �� ���� �⠭������ ��࠭��.
 if( Message->msg == SM_CHECK_CONTROLS )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // �஢��塞 ���ﭨ� ������ � ����� �ਫ������, � ⠪�� �� ���窨.
   Diver_CheckWindowControls( Frame_window );

   // �᫨ ���� �� ����⠫� ���� ��࠭�� - �஢��塞, ��� �� � ᯨ᪥ ���� �����६���� ��࠭��� ����.
   // ��� ���� ������� ��� �஢��� �믮����� �� ���� - ��� �ᥣ�� ࠡ���� �ࠢ��쭮.
   if( WindowIsActive( Frame_window ) )
    if( !WindowIsAppDialog( Frame_window ) )
     CheckActivityProperties( Frame_window );
  }

 // �஢��塞 ࠬ�� ���� ����ﭭ��� ࠧ���.
 if( Message->msg == SM_CHECK_FRAME )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;
   // ������ ����, ���஥ ���� �஢����.
   HWND Window = (HWND) Message->mp2;

   // �᫨ ������ �� ���� ��� - ������.
   HAB Application = WinQueryAnchorBlock( Frame_window );
   if( !WinIsWindow( Application, Frame_window ) ) return;
   if( !WinIsWindow( Application, Window ) ) return;

   // �믮��塞 �஢���.
   Diver_CheckWindowFrame( Frame_window, Window );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ��।������ ᢮��� ���� ���

VOID Diver_DiverThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE )
  {
   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Diver->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Diver->Message_queue == NULLHANDLE )
  {
   // �����蠥� ࠡ��� ��⮪�.
   WinTerminate( Thread );

   // �� ᮧ����� ��⮪� �ந��諠 �訡��.
   Thread_responds.Thread_is_created = -1;

   // ��室.
   return;
  }

 // ��⮪ ᮧ��� �ᯥ譮.
 Thread_responds.Thread_is_created = 1;

 // ����祭�� � ��ࠡ�⪠ ᮮ�饭��, ��室��� � ��⮪.
 QMSG Message = {0};
 while( WinGetMsg( Thread, &Message, 0, 0, 0 ) )
  {
   // �஢��塞, �� ���� �� ᫥��� ⠪�� �� ᮮ�饭��.
   QMSG Next_message = {0};
   WinPeekMsg( Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE );
   if( Next_message.msg == Message.msg )
    if( Next_message.mp1 == Message.mp1 )
     if( Next_message.mp2 == Message.mp2 )
      if( Next_message.hwnd == Message.hwnd ) continue;

   // ��ࠡ��뢠�� ᮮ�饭��.
   Diver_DiverMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
