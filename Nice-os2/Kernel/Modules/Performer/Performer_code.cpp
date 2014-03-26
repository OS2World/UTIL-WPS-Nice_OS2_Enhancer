
// ��� ������, �࠭� �� ������ ���� OS/2 ��� Win-OS/2 ���

// Frame_window - ���� ࠬ��, ���஥ ���� �஢����.
BYTE Performer_WindowIsRolled( HWND Frame_window )
{
 // �᫨ �� ���� OS/2:
 if( !IsWindowsWindow( Frame_window ) )
  {
   // �஢��塞 ���.
   if( Frame_window == RolledWindow() ) return 1;
  }
 // � �᫨ �� ���� Win-OS/2 ��� Odin:
 else
  {
   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // ������ ����� ��������� ����.
   INT TitleBar_height = WinQuerySysValue( Desktop, SV_CYMINMAXBUTTON );

   // ������ ࠧ��� ����.
   RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

   // �஢��塞 ���.
   if( Rectangle.yTop > TitleBar_height )
    if( Rectangle.yTop < TitleBar_height * 2 ) return 1;
  }

 // ������.
 return 0;
}

// ��� ����� ���ﭨ� ������ � ���� ���

// Frame_window - ���� ࠬ��, Command - ����⢨�.
VOID Performer_SetNextButtons( HWND Frame_window, LONG Command )
{
 // ������ ���ﭨ� ������ ��� ����, ����� ��� �㤥� 㢥��祭�.
 if( Command == MAXIMIZE_ACTION )
  {
   // ������ ���ﭨ� ������.
   LONG Buttons = 0;
   FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

   // ���祬 ������ "��������", ������塞 ������ "����⠭�����" � "����� ������".
   Buttons &= ~MAXIMIZE_ACTION; Buttons |= RESTORE_ACTION;
   if( PermissionForRolling( Frame_window ) ) Buttons |= ROLLUP_ACTION;

   // ������ ����� ���ﭨ� ������.
   SetProperty( Frame_window, PRP_BUTTONS, &Buttons );
  }

 // ������ ���ﭨ� ������ ��� ����, ����� ��� �㤥� ����⠭������.
 if( Command == RESTORE_ACTION )
  {
   // ������ ���ﭨ� ������.
   LONG Buttons = 0;
   FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

   // ���祬 ������ "����⠭�����" � "����� ������", ������塞 ������ "��������".
   Buttons &= ~RESTORE_ACTION; Buttons &= ~ROLLUP_ACTION; Buttons |= MAXIMIZE_ACTION;

   // ������ ����� ���ﭨ� ������.
   SetProperty( Frame_window, PRP_BUTTONS, &Buttons );
  }

 // ������.
 return;
}

// ��� ����������, �뫮 �� ���� 㢥��祭�. ��� �⮣� ���� ��࠭�� ��⠭����� ���ﭨ� ������ ���

// Frame_window - ���� ࠬ��.
VOID SetMaximizeProperty( HWND Frame_window )
{
 // �᫨ ���ﭨ� ������ �������⭮ - 㧭��� ���.
 LONG Buttons = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Buttons );

 // ��� ���� OS/2 - �஢��塞 ���ﭨ� ������.
 BYTE Maximized = 0;

 if( !IsWindowsWindow( Frame_window ) )
  {
   if( Buttons & RESTORE_ACTION ) Maximized = 1;
  }
 // ��� ���� Win-OS/2 � Odin - �஢��塞 �ᯮ������� ����.
 else
  {
   // ������ ࠧ��� �࠭�.
   INT X_Screen = WinQuerySysValue( QueryDesktopWindow(), SV_CXSCREEN );

   // ������ ࠧ��� ����.
   RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

   // ���� ����� ���� 㢥��祭� ��� �࠭� ������.
   if( Rectangle.xRight > X_Screen ) Maximized = 1;
   if( Performer_WindowIsRolled( Frame_window ) ) Maximized = 1;
  }

 // ��⠭�������� ᢮��⢮.
 SetProperty( Frame_window, PRP_MAXIMIZED, &Maximized );

 // ������.
 return;
}

// ��� ����, ���� ����⢨� �㤥� �믮����� ���

// Frame_window - ���� ࠬ��, Performed_action - ����⢨�, ���஥ �믮������ � �����.
// �����頥��� ���祭��: 1 �᫨ ����⢨� �믮����� � ���ﭨ� ���� ����������, ���� 0.
BYTE Performer_WaitForNewWindowState( HWND Frame_window, LONG Performed_action )
{
 // �᫨ �� ���� ������� �ਫ������ � ��� ����� �������� - �������� ��ᯮ�����, ������.
 if( WindowIsAppDialog( Frame_window ) ) return 1;

 // ���� ����� �� �⢥��� �� ᮮ�饭��, ���⮬� ����প� �믮������ � �祭�� �����ண� �६���.
 INT Time = WinGetCurrentTime( Enhancer.Application );
 LONG Current_time = Time + 1;

 while( Current_time > Time && Current_time - Time < 1000 )
  {
   // ������ �ᯮ������� ���� � ��� ���ﭨ�.
   SWP Window_state = {0}; WinQueryWindowPos( Frame_window, &Window_state );

   // �஢��塞 ���ﭨ� ����.
   BYTE State_is_changed = 0;

   if( Performed_action == MAXIMIZE_ACTION ) if( Window_state.fl & SWP_MAXIMIZE ) State_is_changed = 1;
   if( Performed_action == MINIMIZE_ACTION ) if( Window_state.fl & SWP_MINIMIZE ) State_is_changed = 1;
   if( Performed_action == HIDE_ACTION ) if( Window_state.fl & SWP_HIDE ) State_is_changed = 1;

   if( Performed_action == RESTORE_ACTION )
    if( !( Window_state.fl & SWP_MAXIMIZE ) )
     if( !( Window_state.fl & SWP_MINIMIZE ) )
      State_is_changed = 1;

   // �᫨ ��� ���������� - �஢��塞 ࠧ��� ����.
   if( State_is_changed )
    {
     // ������ �।��騩 ࠧ��� ����.
     INT Previous_width = 0; FindProperty( Frame_window, PRP_PREVIOUS_WIDTH, &Previous_width );
     INT Previous_height = 0; FindProperty( Frame_window, PRP_PREVIOUS_HEIGHT, &Previous_height );

     // �᫨ �� �� �����:
     if( Previous_width > 0 && Previous_height > 0 )
      {
       // ������ ࠧ��� ����.
       RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );

       // �஢��塞 ��� �ਭ�.
       INT Width = Rectangle.xRight - Rectangle.xLeft;
       INT Height = Rectangle.yTop - Rectangle.yBottom;

       if( Width == Previous_width || Height == Previous_height ) State_is_changed = 0;
      }
    }

   // �᫨ �� � ���浪� - ������.
   if( State_is_changed ) return 1;

   // ���� �����஥ �६�.
   Retard();

   // ������ ⥪�饥 �६�.
   Current_time = WinGetCurrentTime( Enhancer.Application );
  }

 // ������.
 return 0;
}

// ��� �믮���� ��।������� ����⢨� ���

// Frame_window - ���� ࠬ��, Command - ����⢨�.
// �����頥��� ���祭��: 1 �᫨ ����⢨� �믮�����, ���� 0.
// �� �६� ࠡ��� �������� ������ �맮�, �� �⮬ Recursive_calling != 0.
// Called_by_WindowManager - �맮� ���� �� ��⮪� ��� �믮������ ����⢨� �� ����⨨ �� ������.
BYTE Performer_PerformAction( HWND Frame_window, LONG Command, BYTE Recursive_calling = 0, BYTE Called_by_WindowManager = 0 )
{
 // �� ����� ���� ���� Win-OS/2 ��� Odin.
 BYTE Is_Windows_window = IsWindowsWindow( Frame_window );

 // �믮��塞 ����⢨�.
 switch( Command )
  {
   // �����稢��� ����.
   case MAXIMIZE_ACTION:
    {
     // �᫨ �� �� ���� Win-OS/2 ��� Odin:
     if( !Is_Windows_window )
      {
       // ������ ����� ���ﭨ� ������.
       if( Called_by_WindowManager ) Performer_SetNextButtons( Frame_window, MAXIMIZE_ACTION );

       // ������ ��אַ㣮�쭨�� ��� ������ ����� ����������. ����ᮢ뢠�� ��������� � ������.
       if( DrawFramesSettingIsON() ) if( WinIsWindowShowing( Frame_window ) )
        WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) ( WT_TITLEBAR | WT_BORDER ) );
      }

     // ����������, �뫮 �� ���� 㢥��祭�.
     SetMaximizeProperty( Frame_window );

     // ���塞 ���ﭨ� ����.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_MAXIMIZE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_MAXIMIZE );
       WinSetWindowPos( Frame_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );
      }

     // �᫨ �� �� ���� Win-OS/2 ��� Odin:
     if( !Is_Windows_window )
      {
       // ������塞 ����, �⮡� �� �뫮 ����.
       if( DrawFramesSettingIsON() ) UpdateWindow( Frame_window );
      }
    }
   break;

   // ����⠭�������� ����.
   case RESTORE_ACTION:
    {
     // �᫨ �� �� ���� Win-OS/2 ��� Odin:
     if( !Is_Windows_window )
      {
       // ������ ����� ���ﭨ� ������.
       if( Called_by_WindowManager ) Performer_SetNextButtons( Frame_window, RESTORE_ACTION );

       // ������ ��אַ㣮�쭨�� ��� ������ ����� ����������. ����ᮢ뢠�� ��������� � ������.
       if( DrawFramesSettingIsON() ) if( WinIsWindowShowing( Frame_window ) )
        WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) ( WT_TITLEBAR | WT_BORDER ) );
      }

     // ����������, �뫮 �� ���� 㢥��祭�.
     SetMaximizeProperty( Frame_window );

     // ���塞 ���ﭨ� ����.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_RESTORE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_RESTORE );
       WinSetWindowPos( Frame_window, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );
      }

     // �᫨ �� �� ���� Win-OS/2 ��� Odin:
     if( !Is_Windows_window )
      {
       // ������塞 ����, �⮡� �� �뫮 ����.
       if( DrawFramesSettingIsON() ) UpdateWindow( Frame_window );
      }
    }
   break;

   // �����蠥� ����.
   case MINIMIZE_ACTION:
    {
     // ����������, �뫮 �� ���� 㢥��祭�.
     SetMaximizeProperty( Frame_window );

     // ���塞 ���ﭨ� ����.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_MINIMIZE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_MINIMIZE );
      }
    }
   break;

   // ���祬 ����.
   case HIDE_ACTION:
    {
     // ����������, �뫮 �� ���� 㢥��祭�.
     SetMaximizeProperty( Frame_window );

     // ���塞 ���ﭨ� ����.
     if( !Is_Windows_window )
      {
       WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_HIDE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
      }
     else
      {
       WinSetWindowPos( Frame_window, NULLHANDLE, 0, 0, 0, 0, SWP_HIDE );
      }
    }
   break;

   // ���ࠥ� ���� ������.
   case ROLLUP_ACTION:
    {
     // �᫨ �� ������ �맮� - ������.
     if( Recursive_calling ) return 0;

     // �᫨ ���� �� �࠭� ������:
     if( Frame_window != RolledWindow() )
      {
       // �᫨ ���� ��㣮� ����, ���஥ �࠭� ������:
       if( RolledWindow() != NULLHANDLE )
        if( WinIsWindow( WinQueryAnchorBlock( RolledWindow() ), RolledWindow() ) )
         {
          // ������ �ᯮ������� � ���ﭨ� ����.
          SWP Window_placement = {0}; WinQueryWindowPos( RolledWindow(), &Window_placement );

          // �᫨ ���� 㢥��祭�:
          if( Window_placement.fl & SWP_MAXIMIZE )
           {
            // �᫨ ���� ����� ��饥 த�⥫�᪮� ���� - ��뢠�� ����, ���஥ �뫮 �࠭� ������
            if( WinQueryWindow( RolledWindow(), QW_PARENT ) == WinQueryWindow( Frame_window, QW_PARENT ) )
             {
              // ������ ���ﭨ� ������.
              LONG Buttons = 0; FindProperty( RolledWindow(), PRP_BUTTONS, &Buttons );

              // ���뢠�� ���� ��� ����⠭�������� ���.
              INT Command = 0;
              if( Buttons & MINIMIZE_ACTION ) Command = MINIMIZE_ACTION;
              else if( Buttons & HIDE_ACTION ) Command = HIDE_ACTION;
              else if( Buttons & RESTORE_ACTION ) Command = RESTORE_ACTION;

              // �믮��塞 ��।������� ����⢨�. ���뫠�� ᮮ�饭�� � ��⮪.
              WinPostQueueMsg( Enhancer.Modules.WindowManager->Message_queue, SM_PERFORM_ACTION, (MPARAM) RolledWindow(), (MPARAM) Command );

              // ���� - �������⭮.
              RememberRolledWindow( NULLHANDLE );
             }
            // ���� - �����頥� ��� � ���筮� ���ﭨ�.
            else
             {
              // �����頥� ���� � ���筮� ���ﭨ�.
              Performer_UnrollWindow( RolledWindow() );
             }
           }
         }

       // ������ �ᯮ������� ����.
       SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

       // ���������� ���� � ��� �ᯮ�������.
       RememberRolledWindow( Frame_window, &Window_placement );

       // ������ ࠧ��� த�⥫�᪮�� ����.
       HWND Parent_window = WinQueryWindow( Frame_window, QW_PARENT );
       RECT Parent_rectangle = {0}; WinQueryWindowRect( Parent_window, &Parent_rectangle );
       // �⮡� ����� �뫮 �ࠢ������ �窨, 㬥��蠥� ���祭�� �� �������.
       Parent_rectangle.xRight --; Parent_rectangle.yTop --;

       // �᫨ ���� ����㯠�� �� �।��� த�⥫�᪮�� ���� - 㬥��蠥� ��אַ㣮�쭨�.
       INT Top_point = Window_placement.y + Window_placement.cy;
       if( Top_point > Parent_rectangle.yTop )
        {
         INT Offset = Top_point - Parent_rectangle.yTop;
         Window_placement.y -= Offset; Top_point -= Offset;
        }
       if( Window_placement.cx > Parent_rectangle.xRight )
        {
         Window_placement.x = 0;
         Window_placement.cx = Parent_rectangle.xRight + 1;
        }

       // ������ ࠧ��� ����.
       RECT Rectangle = {0}; WinQueryWindowRect( Frame_window, &Rectangle );
       // �⮡� ����� �뫮 �ࠢ������ �窨, 㬥��蠥� ���祭�� �� �������.
       Rectangle.xRight --; Rectangle.yTop --;

       // ������ ��אַ㣮�쭨� ��� ������, ����� ���ᮢ��� � ����.
       RECT All_buttons = {0}; INT Size = CalculateButtonRectangles( Frame_window, &Rectangle, NULLHANDLE, NULL, NULL, NULL, NULL, NULL, &All_buttons );

       // ������뢠�� �窨.
       INT Offset = Rectangle.yTop - All_buttons.yTop + 1;
       INT Height = Size + Offset + Offset - 1;
       Window_placement.cy = Height;
       Window_placement.y = Top_point - Window_placement.cy + 1;

       // ��।������ ���� ࠬ��.
       WinSetWindowPos( Frame_window, NULLHANDLE, Window_placement.x, Window_placement.y, Window_placement.cx, Window_placement.cy, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       // �஢��塞, ��� �ᯮ������ ����.
       SWP New_placement = {0}; WinQueryWindowPos( Frame_window, &New_placement );

       // �᫨ ���� ��諮 �� �।��� த�⥫�᪮�� ����:
       INT Limit = Offset * 2;
       if( New_placement.y + New_placement.cy > Parent_rectangle.yTop + Limit )
        {
         // ����⠭�������� ����.
         Performer_PerformAction( Frame_window, RESTORE_ACTION, RECURSIVE_CALLING );

         // ���� - �������⭮.
         RememberRolledWindow( NULLHANDLE );

         // ������.
         return 0;
        }

       // �᫨ � ���� ����� �ᮢ��� ��-� �஬� ���������:
       if( PermissionForCompleteDrawing( Frame_window ) )
        {
         // ������ �ࠢ��쭮� �ᯮ������� ���� ���⨭��, ��������� � ��㣨� ����. ���뫠�� ᮮ�饭�� � ��⮪.
         WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_PREPARE_CONTROLS, (MPARAM) Frame_window, 0 );
        }

       // ������ ��࠭�� ���� � �।��� �࠭�.
       ActivateWindowInCenter();
      }
     // � �᫨ ���� �࠭� ������ - �����頥� ��� � ���筮� ���ﭨ�.
     else
      {
       Performer_UnrollWindow( Frame_window );
      }

     // ������塞 ����, �⮡� �� �뫮 ����.
     UpdateWindow( Frame_window );
    }
   break;

   // ����뢠�� ����.
   case CLOSE_ACTION:
    {
     // ���ࠢ�塞 ᮮ�饭�� � ����.
     WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, MPFROM2SHORT( CMDSRC_MENU, 0 ) );
    }
   break;
  }

 // ������ ����⢨�, ���஥ �믮������ � �����.
 BYTE Performed_action = 0; FindProperty( Frame_window, PRP_PERFORMED_ACTION, &Performed_action );

 BYTE Action_completed = 1;

 // �᫨ ���� ����� ��� �����襭��:
 if( Performed_action )
  {
   // ����, ���� ��� �㤥� �믮�����.
   Action_completed = Performer_WaitForNewWindowState( Frame_window, Performed_action );

   // ����뢠�� �� �易��� � ��� ᢮��⢠.
   Performed_action = 0; SetProperty( Frame_window, PRP_PERFORMED_ACTION, &Performed_action );

   INT Width = -1;  SetProperty( Frame_window, PRP_PREVIOUS_WIDTH, &Width );
   INT Height = -1; SetProperty( Frame_window, PRP_PREVIOUS_HEIGHT, &Height );
  }

 // ������.
 return Action_completed;
}

