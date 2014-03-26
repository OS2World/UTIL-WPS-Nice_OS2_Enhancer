
// ��� ����� ���箪 ���� ���

// Frame_window - ���� ࠬ��, New_icon - ���� ���箪.
VOID Changer_ChangeWindowIcon( HWND Frame_window, HPOINTER New_icon )
{
 // ������ ���箪, ����� �ᯮ������ ᥩ��.
 HPOINTER Current_icon = (HPOINTER) WinSendMsg( Frame_window, WM_QUERYICON, 0, 0 );

 // ���塞 ���.
 if( Current_icon != New_icon )
  {
   // ������ ���� ���箪.
   WinSendMsg( Frame_window, WM_SETICON, (MPARAM) New_icon, 0 );

   // ���뫠�� ᮮ�饭�� � ��⮪ �ᮢ����.
   WinPostQueueMsg( Enhancer.Modules.Painter->Message_queue, SM_DRAW_FRAME, (MPARAM) Frame_window, (MPARAM) WT_SYSMENU );
  }

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Changer_ChangerMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Changer->Priority = MAKELONG( Class, Delta );
  }

 // ���塞 ���箪 ����.
 if( Message->msg == SM_CHANGE_ICON )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;
   // ������ ���箪, ����� ������ ���� ��⠭�����.
   HPOINTER New_icon = (HPOINTER) Message->mp2;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ���塞 ���箪.
   Changer_ChangeWindowIcon( Frame_window, New_icon );
  }

 // ����뢠�� ���箪, ����� �� ����㦥� � ��᪠.
 if( Message->msg == SM_FREE_FILE_ICON )
  {
   // ������ ���箪.
   HPOINTER Icon = (HPOINTER) Message->mp1;

   // �᢮������� ������.
   WinFreeFileIcon( Icon );
  }

 // ������ ���� ����㯭� ��� ������㯭� ��� ��४��祭��.
 if( Message->msg == SM_SET_JUMPABLE )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ������ ᢮��⢮.
   ULONG Jumpable = (ULONG) Message->mp2;

   // ���塞 ���.
   if( Frame_window != GetDetectedShellWindow() ) SetJumpableFlag( Frame_window, Jumpable );
  }

 // ���塞 ���� ��� ⥪�⮢�� ���� - ���� � ��ன 蠣�.
 if( Message->msg == SM_CHANGE_VIO_FONT || Message->msg == SM_APPLY_VIO_FONT )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ������ �� ���� - ������.
   if( !VIOFontMustBeChanged( Frame_window ) ) return;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ��� ����: ��뢠�� ���� ᬥ�� ���� � ���� ��� ������.
   if( Message->msg == SM_CHANGE_VIO_FONT )
    {
     // �஢��塞 ���ﭨ� ����.
     BYTE VIO_font_dialog = 0; FindProperty( Frame_window, PRP_VIO_FONT_DIALOG, &VIO_font_dialog );
     // �᫨ ��� �⮣� ���� 㦥 �� �맢�� ������ �롮� ���� - ������.
     if( VIO_font_dialog ) return;

     // ��뢠�� ���� ᬥ�� ����.
     OpenVIOFontMetricsDialog( Frame_window );

     // ����������, �� ���� �뫮 ��������.
     VIO_font_dialog = 1; SetProperty( Frame_window, PRP_VIO_FONT_DIALOG, &VIO_font_dialog );
    }

   // ��� ��ன: �롨ࠥ� � ��� ���� � �ਬ��塞 ���.
   if( Message->msg == SM_APPLY_VIO_FONT )
    {
     // �롨ࠥ� ����.
     SubmitVIOFontMetricsDialog( Frame_window );
    }
  }

 // ������ ���� ������.
 if( Message->msg == SM_SHOW_AND_ARRANGE )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ������ ���� ������.
   if( !WinIsWindowVisible( Frame_window ) ) WinShowWindow( Frame_window, 1 );

   // �᫨ ���� ��ࠢ������ ⥪�⮢� ����:
   if( ArrangeVIOWindows() )
    {
     // ���뫠�� � ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� ��ࠢ������.
     WinPostMsg( Frame_window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) SM_ARRANGE_VIO );
    }
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ��������� ᢮��� ���� ���

VOID Changer_ChangerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Changer->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Changer->Message_queue == NULLHANDLE )
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
   Changer_ChangerMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
