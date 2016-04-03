
// ��� ��室�� � �������� ���� ������ ��ᬮ�� ���

// Window - ����, Type - ����� ������ ���� ����, ���祭�� "SBS_*".
// Target_window_placement - �ᯮ������� ����, ��� ���ண� ������ ���� ������� ����᪠.
// �����頥��� ���祭��: ���� ����᪨ ��ᬮ�� ��� NULLHANDLE.
HWND Scroller_FindScrollBar( HWND Window, BYTE Type, PSWP Target_window_placement = NULL )
{
 // �᫨ �ᯮ������� ���� �� 㪠���� - ������ ����� ���祭��.
 HWND Desktop = QueryDesktopWindow();

 INT X_Screen = WinQuerySysValue( Desktop, SV_CXSCREEN );
 INT Y_Screen = WinQuerySysValue( Desktop, SV_CYSCREEN );

 SWP Default_placement = { 0, Y_Screen * 2, X_Screen * 2, Y_Screen * (-1), X_Screen * (-1), NULLHANDLE, NULLHANDLE, 0, 0 };
 if( Target_window_placement == NULL ) Target_window_placement = &Default_placement;

 // ����砫쭮 ���� ����᪨ �������⭮.
 HWND Scroll_bar = NULLHANDLE;

 {
  // ��ॡ�ࠥ� ����, ���� �� ������ ������.
  HENUM Enumeration = WinBeginEnumWindows( Window ); HWND Current_window = NULLHANDLE; 
  while( ( Current_window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // �᫨ ���� �� ����:
    if( WinIsWindowVisible( Current_window ) )
     {
      // �᫨ �� ����᪠ ��ᬮ��:
      if( IsScrollBarWindow( Current_window ) )
       {
        // ������, ��� ��� �ᯮ������.
        SWP Rectangle = {0}; WinQueryWindowPos( Current_window, &Rectangle );

        // �᫨ �� �饬 ��� ࠧ ⠪�� ������ - �����蠥� ��ॡ�� ����.
        if( Type == SBS_VERT ) if( Rectangle.cy > Rectangle.cx )
         if( Rectangle.y + Rectangle.cy / 2 > Target_window_placement->y )
          if( Rectangle.y + Rectangle.cy / 2 < Target_window_placement->y + Target_window_placement->cy )
           { Scroll_bar = Current_window; break; }

        if( Type == SBS_HORZ ) if( Rectangle.cx > Rectangle.cy )
         if( Rectangle.x + Rectangle.cx / 2 > Target_window_placement->x )
          if( Rectangle.x + Rectangle.cx / 2 < Target_window_placement->x + Target_window_placement->cx )
           { Scroll_bar = Current_window; break; }
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // �����頥� 㪠��⥫� �� ������, �᫨ ��� �뫠 �������, ��� NULLHANDLE.
 return Scroll_bar;
}

// ��� ������ ���ﭨ� ����᪨ ��ᬮ�� ���

// ScrollBar - ���� ����᪨ ��ᬮ��, �� ���ﭨ� ���� ������ � SB_State.
// �� ������� ������ �ᯮ�������� � ࠧ���塞�� �����, ���� ��������� �訡��.
VOID Scroller_QueryScrollBarState( HWND ScrollBar, PSBCDATA SB_State )
{
 // ����᪠ ��ᬮ�� ����� ���� �⪫�祭�.
 SB_State->sHilite = WinIsWindowEnabled( ScrollBar );

 // ������ �᫮ �������. ���祭�� posLast >= posFirst >= 0.
 MRESULT Bounds = WinSendMsg( ScrollBar, SBM_QUERYRANGE, 0, 0 );
 SB_State->posFirst = SHORT1FROMMP( Bounds );
 SB_State->posLast  = SHORT2FROMMP( Bounds );

 // ������ ��������� ������ � ����᪥.
 MRESULT Slider = WinSendMsg( ScrollBar, SBM_QUERYPOS, 0, 0 );
 SB_State->posThumb = SHORT1FROMMP( Slider );

 // ������.
 return;
}
