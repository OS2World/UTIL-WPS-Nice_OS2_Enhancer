
// ��� �⮡ࠦ��� � ���� ᯨ᪠ ��ப�, ��������� � ᯨ᪥ ���� ���

VOID WindowList_ShowSwitchListItems( HWND ListBox_window )
{
 // ������ ᯨ᮪ ����.
 PSWBLOCK SWBlock = NULL; QuerySwitchList( &SWBlock );

 // �⮡ࠦ��� ���.
 {
  INT Count;

  WinSendMsg( ListBox_window, LM_DELETEALL, 0, 0 );

  for( Count = 0; Count < SWBlock->cswentry; Count ++ )
   if( SWBlock->aswentry[ Count ].swctl.uchVisibility == SWL_VISIBLE )
    if( SWBlock->aswentry[ Count ].swctl.hwnd != NULLHANDLE )
     if( WinIsWindow( WinQueryAnchorBlock( SWBlock->aswentry[ Count ].swctl.hwnd ), SWBlock->aswentry[ Count ].swctl.hwnd ) )
      WinSendMsg( ListBox_window, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( SWBlock->aswentry[ Count ].swctl.szSwtitle ) );
 }

 // �᢮������� ������.
 FreeSwitchListMemory( SWBlock ); SWBlock = NULL;

 // ������.
 return;
}
