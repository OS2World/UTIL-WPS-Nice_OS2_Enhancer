
// ��� ��ᯠ娢��� ⥪�⮢�� ���� ���

BYTE Arranger_SpreadVIOWindow( HWND Frame_window )
{
 // �஢��塞, ���� �� � ���� ����᪨ ��ᬮ��.
 if( !WinWindowFromID( Frame_window, FID_VERTSCROLL ) &&
     !WinWindowFromID( Frame_window, FID_HORZSCROLL ) ) return 0;

 // ������� ������� �����, �⮡� ���� ����� ������ ᢮� �������襥 ��������� �ᯮ�������.
 PSWP Window_position = NULL;
 APIRET Report = DosAllocSharedMem( (PPVOID) &Window_position, NULL, sizeof( SWP ), PAG_ALLOCATE | OBJ_GIVEABLE );

 if( Report == NO_ERROR )
  {
   // ������� ��६���� ��� �������襣� ࠧ��� ����.
   INT Max_X = 0;
   INT Max_Y = 0;

   // ������塞 ������� ����� ��ﬨ.
   bzero( Window_position, 0 );

   // ��।��� ������� ����� �ਫ������, ᮧ���襬� ����.
   PID Process_ID = 0;
   WinQueryWindowProcess( Frame_window, &Process_ID, NULL );
   Report = DosGiveSharedMem( Window_position, Process_ID, PAG_READ | PAG_WRITE );

   if( Report == NO_ERROR )
    {
     // ���ࠢ�塞 ���� ᮮ�饭��, �⮡� ��� ����⠫� ᢮� �ᯮ������� � 㢥��祭��� ����.
     Window_position->fl = SWP_MAXIMIZE | SWP_NOADJUST | SWP_NOREDRAW;
     WinSendMsg( Frame_window, WM_ADJUSTWINDOWPOS, Window_position, 0 );

     // �᫨ �� �ᯮ������� ����祭�:
     if( Window_position->cx != 0 && Window_position->cy != 0 )
      {
       // ���������� ���
       Max_X = Window_position->cx;
       Max_Y = Window_position->cy;

       // ������ �।��饥 ᮮ�饭��, ���� ����� �������� ᢮� �ᯮ�������.
       // �।������ ��� ���᫨�� ᢮� �ᯮ������� � ��� ��몭������� ����.
       Window_position->fl = SWP_RESTORE | SWP_NOADJUST | SWP_NOREDRAW;
       WinSendMsg( Frame_window, WM_ADJUSTWINDOWPOS, Window_position, 0 );
      }
    }

   // �᢮������� ������.
   DosFreeMem( Window_position ); Window_position = NULL;

   // �᫨ �ᯮ������� �뫮 ����祭�:
   if( Max_X != 0 && Max_Y != 0 )
    {
     // ������ ࠧ��� � �ᯮ������� ����.
     SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

     // �᫨ ����祭�� ���祭�� �� ᮢ������:
     if( Window_placement.cx != Max_X || Window_placement.cy != Max_Y )
      {
       // �⠢�� ����-�������� ������ ��� ����.
       // �� ������� �������� ���� �� �࠭� (������ � ������묨 ��������⠬�).
       ShowCurtainWindow( QueryDesktopWindow() );

       // ������ ����� �ᯮ������� ����.
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, Max_X, Max_Y, SWP_SIZE );

       // ������.
       return 1;
      }
    }
  }

 // ������.
 return 0;
}

// ��� ��ࠢ������ ���� ���

// Action ��।���� ����⢨�, Frame_window - ���� ࠬ��.
VOID Arranger_ArrangeWindows( ULONG Action, HWND Frame_window )
{
 // �᫨ ���� ᬥ�� ������ - ������.
 if( SynchronizeArrangerAndRooms() )
  if( Action != SM_ARRANGE_WIN_LIST )
   if( Action != SM_ARRANGE_VIO_IN_ROOM )
    if( !TimeForRoomsSwitchingIsGone() ) return;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 // ������ �ᯮ������� ���� � த�⥫�᪮� ���� - � ���� � ���� ࠡ�祣� �⮫�.
 SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

 // �᫨ ���� 㬥��襭� ��� ���� - ������.
 if( Window_placement.fl & SWP_MINIMIZE || Window_placement.fl & SWP_HIDE )
  if( Action != SM_ARRANGE_WIN_LIST )
   return;

 // ������ ࠧ��� �࠭�.
 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 // ������ ����� ��������� ����.
 INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

 // � �������� ����� ���� ���� �㤥� �맢��� ������.
 BYTE Activate_window = 0;
 // � ⠪�� ���⠢��� ����-�������� ������ ��� ����.
 BYTE Show_curtain = 0;

 // ��ࠢ������ ⥪�⮢� ���� �� ���室� ����� �����⠬�.
 if( Action == SM_ARRANGE_VIO_IN_ROOM )
  if( Window_placement.fl & SWP_MAXIMIZE )
   Action = SM_ARRANGE_VIO;

 // ��ࠢ������ ���� File Commander, ����� ��� �������� ���� �࠭.
 if( Action == SM_ARRANGE_FC2 )
  {
   if( Window_placement.cx > X_Screen )
    {
     Action = SM_ARRANGE_VIO; Show_curtain = 1;
     ULONG No_more = 1; SetProperty( Frame_window, PRP_TIME_OF_ARRANGE, &No_more );
    }
   else
    {
     return;
    }
  }

 // ��ࠢ������ ⥪�⮢� ���� �� �।��� �࠭�.
 if( Action == SM_ARRANGE_VIO )
  {
   // ��ᯠ娢��� ���� �� �������襣� ���������� ࠧ���.
   if( Window_placement.cx < X_Screen )
    {
     // �����塞 ࠧ��� ����.
     BYTE Window_position_is_changed = Arranger_SpreadVIOWindow( Frame_window );

     // ������ ���� ࠧ��� � �ᯮ������� ����.
     if( Window_position_is_changed ) WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // ������ ���� ࠧ��� � �ᯮ������� ����.
   INT X_Size = Window_placement.cx;
   INT Y_Size = Window_placement.cy;
   INT X_Position = 0;
   INT Y_Position = 0;

   if( X_Size > X_Screen )
    {
     INT Normal_frame = FrameWidth( Frame_window );

     X_Position = Normal_frame * (-1);
     Y_Position = Y_Screen - Y_Size + Normal_frame;
    }
   else
    {
     X_Position = ( X_Screen - X_Size ) / 2;
     Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;
    }

   // �᫨ �ॡ���� ��ࠢ�������:
   if( X_Position != Window_placement.x || Y_Position != Window_placement.y || Window_placement.fl & SWP_MAXIMIZE )
    {
     // �⠢�� ����-�������� ������ ��� ����.
     // ��� ����� ���� ���⠢���� �� ࠭��, �� �६� ��������� ࠧ��� ����.
     if( Show_curtain ) ShowCurtainWindow( QueryDesktopWindow() );
     // ������ ����� �ᯮ������� ����.
     WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
    }

   // ���� ������ ���� �맢��� ������.
   Activate_window = 1;
  }

 // ��ࠢ������ ���� WPS � Object Desktop Archiver.
 if( Action == SM_ARRANGE_WPS )
  {
   // �᫨ ���� 㢥��祭� - ����⠭�������� ���.
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     // ����⠭�������� ����.
     PerformAction( Frame_window, RESTORE_ACTION );

     // ������ ���� ࠧ��� � �ᯮ������� ����.
     WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // ������ ���� ࠧ��� � �ᯮ������� ����.
   INT X_Size = X_Screen * 3 / 4 + Rnd( TitleBar_height * 2 );
   INT Y_Size = Y_Screen * 3 / 4 + Rnd( TitleBar_height * 2 );
   INT X_Position = ( X_Screen - X_Size ) / 2;
   INT Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;

   // ��ࠢ������ ���� WPS �� �।��� �࠭�.
   // ����⢨� �믮������ ⮫쪮 ��� ����, ������ ࠧ��� �� 㬮�砭��.
   if( Action == SM_ARRANGE_WPS )
    {
     INT Default_width_Min = X_Screen / 1.25;
     INT Default_width_Max = X_Screen / 1.25 + 10;

     // �᫨ �ॡ���� ��ࠢ�������:
     if( Window_placement.cx >= Default_width_Min && Window_placement.cx <= Default_width_Max )
      {
       // ������ ����� �ᯮ������� ����.
       WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
      }
     }

   // ���� ������ ���� �맢��� ������.
   Activate_window = 1;
  }

 // ��ࠢ������ ��㣨� ����.
 if( Action == SM_ARRANGE_WIN_LIST )
  {
   // �᫨ ���� 㢥��祭� - ����⠭�������� ���.
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     // ����⠭�������� ����.
     PerformAction( Frame_window, RESTORE_ACTION );

     // ������ ���� ࠧ��� � �ᯮ������� ����.
     WinQueryWindowPos( Frame_window, &Window_placement );
    }

   // ������ ���� ࠧ��� � �ᯮ������� ����.
   INT X_Size = Window_placement.cx;
   INT Y_Size = Window_placement.cy;
   INT X_Position = ( X_Screen - X_Size ) / 2;
   INT Y_Position = ( Y_Screen - Y_Size ) * 3 / 4;

   // �᫨ �ॡ���� ��ࠢ�������:
   if( X_Position != Window_placement.x || Y_Position != Window_placement.y || Window_placement.fl & SWP_MAXIMIZE )
    {
     // ������ ����� �ᯮ������� ����.
     WinSetWindowPos( Frame_window, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE );
    }
  }

 // ���祬 ����-��������.
 HideCurtainWindow();

 // ������ ���� ��࠭��.
 if( Activate_window ) MoveWindowAbove( Frame_window );

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Arranger_ArrangerMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Arranger->Priority = MAKELONG( Class, Delta );
  }

 // ��ࠢ������ ���� �� �।��� �࠭�.
 if( Message->msg >= SM_ARRANGE_FIRST && Message->msg <= SM_ARRANGE_LAST )
  {
   // ������ ���� ࠬ�� � ����⢨�.
   HWND Frame_window = (HWND) Message->mp1;
   ULONG Action = Message->msg;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ��ࠢ������ ����.
   Arranger_ArrangeWindows( Action, Frame_window );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ��ࠢ������� ���� ���

VOID Arranger_ArrangerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Arranger->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Arranger->Message_queue == NULLHANDLE )
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
   Arranger_ArrangerMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
