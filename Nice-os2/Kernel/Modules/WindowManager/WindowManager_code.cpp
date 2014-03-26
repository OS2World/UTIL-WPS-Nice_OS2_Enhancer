
// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID WindowManager_WindowManagerMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.WindowManager->Priority = MAKELONG( Class, Delta );
  }

 // �믮��塞 ��।������� ����⢨�.
 if( Message->msg == SM_PERFORM_ACTION )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;
   LONG Command = (LONG) Message->mp2;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // �믮��塞 ����⢨�.
   PerformAction( Frame_window, Command, 0, PA_METHOD_CALLED_BY_WINDOW_MANAGER );
  }

 // ���뢠�� ��� ���祬 ����.
 if( Message->msg == SM_HIDE_WINDOW_AWAY )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ࠬ�� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // �믮��塞 ����⢨�.
   HideWindowAway( Frame_window );
  }

 // ������ ��࠭�� ���� � �।��� �࠭�.
 if( Message->msg == SM_ACTIVATE_ANYTHING )
  {
   // ���� �����஥ �६�.
   Retard();

   // ������ ��࠭�� ���� � �।��� �࠭�.
   ActivateWindowInCenter();
  }

 // ������ ��࠭�� ���� � �।��� �࠭� ��᫥ ᬥ�� ������.
 if( Message->msg == SM_RETARD_AND_ACTIVATE )
  {
   // ������ �������, ��࠭��� ���짮��⥫��.
   INT Room = GetCurrentOrNextRoom();

   // �����蠥� �ਮ���.
   DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MINIMUM, 0 );

   // ���� �����஥ �६�.
   for( INT Count = 0; Count < 5; Count ++ ) Retard();

   // ����⠭�������� �ਮ���.
   LONG Class = SHORT1FROMLONG( Enhancer.Modules.WindowManager->Priority );
   LONG Delta = SHORT2FROMLONG( Enhancer.Modules.WindowManager->Priority );
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // �᫨ ���짮��⥫� ��ࠫ ����� �������, �맢�� ���� WarpCenter ��� ᯨ᮪ ���� - ��祣� ������ �� ����.
   BYTE Activate_window_in_center = 1;
   if( Activate_window_in_center ) if( Room != GetCurrentOrNextRoom() ) Activate_window_in_center = 0;
   if( Activate_window_in_center ) if( SystemWindowIsPresent( FIND_SYSMSG_WINDOW | FIND_ALL_TOOLBAR_MENUS | FIND_WINDOW_LIST | FIND_LSWITCHER_PANEL, FIND_VISIBLE_WINDOW ) ) Activate_window_in_center = 0;

   // ������ ��࠭�� ���� � �।��� �࠭�.
   if( Activate_window_in_center ) ActivateWindowInCenter();

   // ���⠢�塞 �ਮ���� ��� �ਫ������.
   SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS );
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ��ࠡ�⪨ ����⨩ �� ������ ���

VOID WindowManager_WindowManagerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.WindowManager->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.WindowManager->Message_queue == NULLHANDLE )
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
   WindowManager_WindowManagerMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
