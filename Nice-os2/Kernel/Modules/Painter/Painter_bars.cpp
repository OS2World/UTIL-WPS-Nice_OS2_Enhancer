
// ��� ��।����, ����� ������ ���� �ᮢ��� � ��砥, �᫨ �� ��ப� ���� ������㯭� ���

// Frame_window - ���� ࠬ��.
LONG Painter_PossibleAllowedActions( HWND Frame_window )
{
 // ��� �������� ���� ������ �㦭� �ᥣ��.
 if( IsRZApiWindow( Frame_window ) ) return ALL_ACTIONS;

 // ������.
 return NO_ACTION;
}

// ��� ��।����, ���� �� �ᮢ��� ��� ���� ������ 㬥��襭�� ���

// Frame_window - ���� ࠬ��.
BYTE Painter_MinimizeActionIsAllowed( HWND Frame_window )
{
 // ��� ������ ����� �⪫���� ��� ���� WPS.
 if( Painter.Settings.Accelerate_folders_closing )
  {
   // �᫨ �� ���� �� ���� WPS ��� MDesk - ������ �ᮢ��� �� ����, ������.
   if( IsFolderWindow( Frame_window ) ) return 0;
   if( IsJobCnrWindow( Frame_window ) ) return 0;
   if( IsMDeskWindow( Frame_window ) ) return 0;
  }

 // ������.
 return 1;
}

// ��� ��।����, ���� �� �ᮢ��� ��� ���� ⮫쪮 ������ ������� ���

// Frame_window - ���� ࠬ��.
LONG Painter_OneActionIsAllowed( HWND Frame_window )
{
 // ��� ���� WPS:
 if( Painter.Settings.Accelerate_folders_closing )
  {
   if( IsWinListWindow( Frame_window ) ) return HIDE_ACTION;
   if( IsPaletteWindow( Frame_window ) ) return CLOSE_ACTION;
  }

 // ��� ���� Java:
 if( IsJavaWindow( WinWindowFromID( Frame_window, FID_CLIENT ) ) &&
     WindowIsCreatedBy( APP_APPLETVIEWER, Frame_window ) ) return CLOSE_ACTION;

 // ������.
 return NO_ACTION;
}

// ��� ������ ���ﭨ� ������ � �ࠢ�� ���孥� 㣫� ���� ���

// Frame_window - ���� ࠬ��, Target - ����� ������ ���� �஢����, Consider_all_settings - ���뢠�� �� ����ன�� ��� ������.
LONG Painter_QueryButtonsState( HWND Frame_window, ULONG Target, BYTE Consider_all_settings )
{
 // ������ ����� ���� ������ ���ࠢ��쭮.
 if( Target & RESTORE_ACTION || Target & ROLLUP_ACTION )
  {
   Target &= ~RESTORE_ACTION;
   Target &= ~ROLLUP_ACTION;

   Target |= MAXIMIZE_ACTION;
  }

 // ������ ���� ���⨭�� � ����� ���孥� 㣫� ����.
 HWND SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );

 // ������ ���� ������ ������.
 HWND MinMax_window = WinWindowFromID( Frame_window, FID_MINMAX );

 // �᫨ ���� ���⨭�� � ���� ������ ������ ��� - �ᮢ��� ���� ������ �� ����. �ਫ������ �����
 // ���� ᥡ� ��� 㣮���, ���ਬ��, Regedit ���ਭ����� ����⨥ �� ������ ������� ��� ����⨥ "��".
 if( SysMenu_window == NULLHANDLE ) if( MinMax_window == NULLHANDLE ) return NO_ACTION;

 // �᫨ ���� ���� ���⨭�� - 㧭��� ���ﭨ� ����, ���஥ ������ �� ����⨨ �� ���.
 // �᫨ ���� ���⨭�� ���, �� ���� ���� ������ ������ - 㧭��� �� ���ﭨ�.
 BYTE Ask_SysMenu = 0; if( SysMenu_window != NULLHANDLE ) Ask_SysMenu = 1;
 BYTE Ask_MinMax = 0; if( SysMenu_window == NULLHANDLE ) if( MinMax_window != NULLHANDLE ) Ask_MinMax = 1;

 // �᫨ ������ �ᮢ��� ����� - ������.
 if( !Painter_PermissionForButtonsDrawing( Frame_window ) ) return NO_ACTION;

 // ������ ���ﭨ� ������.
 LONG Draw_maximize_button = 0; LONG Draw_minimize_button = 0; LONG Draw_close_button = 0;
 LONG Draw_rollup_button = 0; LONG Draw_restore_button = 0; LONG Draw_hide_button = 0;

 // �᫨ ����訢����� ���ﭨ� ���� - �஢��塞, �������� �� ���⨭�� � ���������.
 if( Ask_SysMenu )
  {
   // �᫨ ���� ���⨭�� �� �������� - �ᮢ��� ������ �� ����, ������.
   if( !WindowIsPresent( SysMenu_window ) ) return NO_ACTION;

   // ������ ���� ���������.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

   // �᫨ ���� ��������� �� �������� - �ᮢ��� ������ �� ����, ������.
   if( !WindowIsPresent( TitleBar_window ) ) return NO_ACTION;
  }

 // �᫨ ����訢����� ���ﭨ� ������ - �஢��塞, ������� �� ���������.
 if( Ask_MinMax )
  {
   // ������ ���� ���������.
   HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

   // �᫨ ���� ��������� �� �������� - �ᮢ��� ������ �� ����, ������.
   if( !WindowIsPresent( TitleBar_window ) ) return NO_ACTION;
  }

 // ��� �������� ���� ���� �ᮢ��� ⮫쪮 ������ �������.
 if( Consider_all_settings )
  {
   // ������, ⠪ �� ��.
   LONG Action = Painter_OneActionIsAllowed( Frame_window );
   if( Action != NO_ACTION ) return Action;
  }

 // ������ ⥪�饥 ���ﭨ� ������.
 LONG Current_state = NO_ACTION; FindProperty( Frame_window, PRP_BUTTONS, &Current_state );

 // �᫨ ��� �������⭮ � ������ ���� �ᮢ��� - ���� 㧭��� ���ﭨ� ��ப ���� ��� ����.
 if( Current_state == NO_ACTION )
  if( Painter.Settings.Draw_frames ) if( Painter.Settings.Draw_buttons )
   Target = ALL_ACTIONS;

 if( Target & MAXIMIZE_ACTION )
  {
   if( Ask_SysMenu ) Draw_maximize_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MAXIMIZE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_maximize_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MAXIMIZE, 0 ), 0 );
  }
 else
  {
   Draw_maximize_button = Current_state & MAXIMIZE_ACTION;
   Draw_rollup_button = Current_state & ROLLUP_ACTION;
  }

 if( Target & MINIMIZE_ACTION )
  {
   if( Ask_SysMenu ) Draw_minimize_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MINIMIZE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_minimize_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_MINIMIZE, 0 ), 0 );
  }
 else
  {
   Draw_minimize_button = Current_state & MINIMIZE_ACTION;
  }

 if( Target & CLOSE_ACTION )
  {
   if( Ask_SysMenu ) Draw_close_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_CLOSE, INCLUDE_SUBMENUS ), 0 );
   if( Ask_MinMax ) Draw_close_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_CLOSE, 0 ), 0 );
  }
 else
  {
   Draw_close_button = Current_state & CLOSE_ACTION;
  }

 // ����� ������ 㬥��襭�� ����� ���� ������ ᮪����.
 if( !Draw_minimize_button )
  {
   if( Target & MINIMIZE_ACTION )
    {
     if( Ask_SysMenu ) Draw_hide_button = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_HIDE, INCLUDE_SUBMENUS ), 0 );
     if( Ask_MinMax ) Draw_hide_button = (LONG) WinSendMsg( MinMax_window, MM_ISITEMVALID, MPFROM2SHORT( SM_HIDE, 0 ), 0 );
    }
   else
    {
     Draw_hide_button = Current_state & HIDE_ACTION;
    }
  }

 // ��� �������� ���� �� ������ �ᮢ��� �� ����.
 if( Consider_all_settings ) if( Draw_minimize_button || Draw_hide_button )
  if( !Painter_MinimizeActionIsAllowed( Frame_window ) )
   Draw_minimize_button = Draw_hide_button = 0;

 // �᫨ ���� 㢥��祭� - ���� �ᮢ��� ������ "����⠭�����" � "����� ������".
 // �᫨ ������ 㢥��祭�� ��� - ������ ���� ��� ��㣨� ������.
 if( !Draw_maximize_button )
  {
   // ������ �ᯮ������� ���� � ��� ���ﭨ�.
   SWP Window_placement = {0}; WinQueryWindowPos( Frame_window, &Window_placement );

   // �᫨ ��� 㢥��祭� - ���� �ᮢ��� ������ "����⠭�����" � "����� ������".
   if( Window_placement.fl & SWP_MAXIMIZE )
    {
     Draw_rollup_button = 1;
     Draw_restore_button = 1;
    }
  }

 // ��� �������� ���� �ᮢ��� ������ "����� ������" �� ����.
 if( Consider_all_settings ) if( Draw_rollup_button )
  Draw_rollup_button = Painter_PermissionForRolling( Frame_window );

 // ��� ���� ����ﭭ��� ࠧ��� �� ���� �ᮢ��� ������ 㢥��祭��.
 if( Draw_maximize_button || Draw_restore_button )
  if( FrameType( Frame_window ) == FT_CONST )
   Draw_maximize_button = Draw_restore_button = Draw_rollup_button = 0;

 // �᫨ ����訢����� ���ﭨ� ���� � �� ��� ��ப� ������㯭� - ���� �ᮢ��� ������ �� 㬮�砭��.
 if( Ask_SysMenu )
  if( !Draw_maximize_button && !Draw_minimize_button && !Draw_rollup_button && !Draw_close_button )
   return Painter_PossibleAllowedActions( Frame_window );

 // ������ ���ﭨ� ������.
 LONG Buttons_state = NO_ACTION;
 if( Draw_maximize_button ) Buttons_state |= MAXIMIZE_ACTION;
 if( Draw_minimize_button ) Buttons_state |= MINIMIZE_ACTION;
 if( Draw_hide_button ) Buttons_state |= HIDE_ACTION;
 if( Draw_restore_button ) Buttons_state |= RESTORE_ACTION;
 if( Draw_rollup_button ) Buttons_state |= ROLLUP_ACTION;
 if( Draw_close_button ) Buttons_state |= CLOSE_ACTION;

 // ������.
 return Buttons_state;
}
