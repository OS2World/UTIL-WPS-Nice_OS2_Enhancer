
// ��� �஢����, ����� �� �ᮢ��� ��-�, �஬� ��������� ���

// Frame_window - ���� ࠬ��.
BYTE Painter_PermissionForCompleteDrawing( HWND Frame_window )
{
 // �᫨ ���� �� ������ - ������.
 if( Frame_window == NULLHANDLE ) return 0;

 // ��� ���� ODIN ���� �ᮢ��� ⮫쪮 ���������.
 if( IsWindowsWindow( Frame_window ) ) return 0;

 // �� �� ᠬ�� - ��� ���� WarpVision.
 if( IsVideoPlayerWindow( Frame_window ) ) return 0;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �� �� ��࠭�祭�� - ��� ���� PMMail.
   if( WindowIsCreatedBy( APP_PMMAIL, Frame_window ) ) return 0;

   // � ��� ���� VisualAge C++ 4.x � Embellish.
   if( WindowIsCreatedBy( APP_VACPP, Frame_window ) ) return 0;
   if( WindowIsCreatedBy( APP_EMBELLISH, Frame_window ) ) return 0;

   // � ��� �������� ���� PM123.
   if( WinWindowFromID( Frame_window, FID_TITLEBAR ) == NULLHANDLE )
    if( WindowIsCreatedBy( APP_PM123, Frame_window ) ) return 0;

   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.BorderDrawing_8 ) == EQUALLY ) return 0;
  }

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.BorderDrawing_8 ) == EQUALLY ) return 0;
  }

 // ������ PID �ਫ������, ᮧ���襣� ����.
 PID Process_ID = 0; TID Thread_ID = 0;
 WinQueryWindowProcess( Frame_window, &Process_ID, &Thread_ID );

 // �஢��塞 ���.
 if( Process_ID )
  {
   for( INT Process_count = 0; Process_count < PAINTER_STUBBORN_PID_TABLE; Process_count ++)
    if( Painter.RTSettings.Stubborn_processes[ Process_count ] == Process_ID ) return 0;
  }

 // ������.
 return 1;
}

// ��� �஢����, ����� �� �ᮢ��� ��� ���� ���� ������ ���

// Frame_window - ���� ࠬ��.
BYTE Painter_PermissionForButtonsDrawing( HWND Frame_window )
{
 // �஢�ઠ �㦭� ⮫쪮 � ��砥, �᫨ ���� ������� ������ ��� - ⮣��
 // ����� ���������� ����ﭭ�� �ᮢ����, ���஥ �룫廊� ��� "�������" ࠬ��.
 if( WinWindowFromID( Frame_window, FID_MINMAX ) != NULLHANDLE ) return 1;

 // ��� �������� ���� �ᮢ��� ������ �� ����.
 if( WindowIsCreatedBy( APP_WORDPRO, Frame_window ) ) return 0;

 // ������.
 return 1;
}

// ��� �஢����, ����� �� �ᮢ��� ������ "����� ������" ���

// Frame_window - ���� ࠬ��.
BYTE Painter_PermissionForRolling( HWND Frame_window )
{
 // �᫨ த�⥫�᪮� ���� - �� ���� ࠡ�祣� �⮫�, � �ᮢ��� ������ �� ����.
 if( WinQueryWindow( Frame_window, QW_PARENT ) != QueryDesktopWindow() ) return 0;

 // ��� ⥪�⮢�� ���� �ᮢ���� �⮩ ������ ������ ���� �⪫�祭�.
 if( !Painter.Settings.Rollup_VIO_windows ) if( IsVIOWindow( Frame_window ) ) return 0;

 // � ��� �������� ��㣨� ����.
 if( IsHobWindow( Frame_window ) ) return 0;
 if( IsEPMEditorWindow( Frame_window ) ) return 0;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_1 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_2 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_3 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_4 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_5 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_6 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_7 ) == EQUALLY ) return 0;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Rolling_8 ) == EQUALLY ) return 0;
  }

 // ������ ���� ࠡ�祩 ������.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Rolling_8 ) == EQUALLY ) return 0;
  }

 // ������.
 return 1;
}

// ��� ������, ��� ���� �ᮢ��� ࠬ�� ��� ���� ����ﭭ��� ࠧ��� ���

// �� ��६���� - ���譨�, �����頥��� ���祭�� - ���� �� �ᮢ��� ����७��� ࠬ��.
BYTE Painter_PermissionForInnerFrameDrawing( HWND Frame_window, HWND Window, PRECT Rectangle )
{
 // �᫨ � ���� ����ﭭ��� ࠧ��� ���� ���� - �ᮢ��� ����७��� ࠬ�� �� ����.
 if( WinWindowFromID( Frame_window, FID_MENU ) != NULLHANDLE ) return 0;

 // ������ �ਭ� ࠬ�� ����.
 INT Const_frame = 0; FindProperty( Frame_window, PRP_BORDER, &Const_frame );
 if( !Const_frame ) Const_frame = FrameWidth( Frame_window );

 // ������ ����� ���� ���������.
 HWND TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
 RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );

 // �஢��塞 ����.
 while( Window != Frame_window && Window != NULLHANDLE )
  {
   // ������ �ᯮ������� ����.
   SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

   // �᫨ ���� �㤥� ����� ����७��� ࠬ�� - �� ���� ����ᮢ���.
   INT Limit = Rectangle->yTop - Const_frame - TitleBar_rectangle.yTop;
   if( Window_placement.y + Window_placement.cy == Limit )
    if( WinIsWindowVisible( Window ) ) return 1;

   // ������ த�⥫�᪮� ����.
   Window = WinQueryWindow( Window, QW_PARENT );
  }

 // ������.
 return 0;
}

// ��� �롨ࠥ� ���� ��� �ᮢ���� ���

// �� ��६���� - ���譨�.
HWND Painter_ChooseWindowForDrawing( HWND Window, PLONG Window_type )
{
 // ������ ��� ����.
 *Window_type = WT_UNKNOWN;
 switch( WindowType( Window ) )
  {
   // �᫨ �� ���� ࠬ�� - �஢��塞 ���.
   case WT_BORDER:
    {
     // ������, ��� �룫廊� ࠬ�� ����.
     LONG Frame_type = FrameType( Window );

     // �᫨ ࠬ�� �� ���ᮢ��� - ��祣� �ᮢ��� �� ����.
     if( Frame_type == FT_RECT ) return NULLHANDLE;

     // �᫨ ࠡ��� ������� ���� - ���� Win-OS/2 ��� Odin, � ��祣� �ᮢ��� �� ����.
     if( IsWindowsWindow( Window ) ) return NULLHANDLE;

     // ���� - �ᮢ��� �����.
     *Window_type = WT_BORDER; return Window;
    }
   break;

   // �᫨ �� ���� ���⨭�� - �ᮢ��� �����.
   case WT_SYSMENU:
    if( Painter.Settings.Draw_system_menus ) { *Window_type = WT_SYSMENU; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // �᫨ �� ���� ��������� - �ᮢ��� �����.
   case WT_TITLEBAR:
    if( Painter.Settings.Draw_titles ) { *Window_type = WT_TITLEBAR; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // �᫨ �� ���� ������ - �ᮢ��� �����.
   case WT_MINMAX:
    if( Painter.Settings.Draw_buttons ) { *Window_type = WT_MINMAX; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // �᫨ �� ���� ���� - �ᮢ��� �����.
   case WT_MENU:
    if( Painter.Settings.Draw_menus ) { *Window_type = WT_MENU; return WinQueryWindow( Window, QW_PARENT ); }
   break;

   // ���� - ��祣� �ᮢ��� �� ����.
   default:
   return NULLHANDLE;
  }

 // ������.
 return NULLHANDLE;
}

// ��� �஢����, ����� �� ����ᮢ��� ����. �����頥� ��� ࠬ�� ���� ���

// Window - ����. �����頥��� ���祭��: NULLHANDLE - �᫨ �����, ���� - ࠬ�� ����.
// ��६����� Window_type �㤥� 㪠�뢠�� �� �, ����� �� ���� - ࠬ��, ���������, � �.�.
HWND Painter_PermissionForDrawing( HWND Window, PLONG Window_type = NULL )
{
 // �롨ࠥ� ���� ��� �ᮢ����.
 LONG Type = WT_UNKNOWN; if( Window_type == NULL ) Window_type = &Type;
 HWND Frame_window = Painter_ChooseWindowForDrawing( Window, Window_type );

 // �᫨ ���� �������⭮ - ������.
 if( Frame_window == NULLHANDLE ) return NULLHANDLE;

 // ��� �������� ���� �ᮢ��� ࠬ�� �� ����.
 if( IslSwitcherWindow( Frame_window ) ) return NULLHANDLE;
 if( IsSmartBarWindow( Frame_window ) ) return NULLHANDLE;
 if( IsVideoViewerWindow( Frame_window ) ) return NULLHANDLE;

 // ��� �������� ���� ���� �ᮢ��� ⮫쪮 ���������. �� ��⠫�� ������ ��ᥪ�����.
 if( *Window_type != WT_TITLEBAR )
  if( !Painter_PermissionForCompleteDrawing( Frame_window ) )
   return NULLHANDLE;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_1 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_2 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_3 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_4 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_5 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_6 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_7 ) == EQUALLY ) return NULLHANDLE;
   if( stricmpe( Exe_name, Painter.Settings.Exceptions.Drawing_8 ) == EQUALLY ) return NULLHANDLE;
  }

 // ������ ���� ࠡ�祩 ������ ��� ���� ࠬ��.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_1 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_2 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_3 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_4 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_5 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_6 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_7 ) == EQUALLY ) return 0;
   if( strcmp( Window_name, Painter.Settings.Exceptions.Drawing_8 ) == EQUALLY ) return 0;
  }

 // ������.
 return Frame_window;
}

