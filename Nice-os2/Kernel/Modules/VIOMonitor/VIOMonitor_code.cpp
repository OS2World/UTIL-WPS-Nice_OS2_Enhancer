
// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID VIOMonitor_VIOMonitorMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.VIOMonitor->Priority = MAKELONG( Class, Delta );
  }

 // ����, ����� �⠭�� �����⭮ �ਫ������, ᮧ���襥 ⥪�⮢�� ����.
 if( Message->msg == SM_MONITOR_VIO )
  {
   // ������ ���� ࠬ��.
   HWND Frame_window = (HWND) Message->mp1;

   // �᫨ ���� ��� - ������.
   if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;

   // ����, ����� �⠭�� �����⭮ �ਫ������, ᮧ���襥 ����.
   for( INT Count = 0; Count < VIOMonitor.Constants.Retards_when_VIO_monitoring; Count ++ )
    {
     // ������ ��� �ਫ������, ᮧ���襣� ����.
     CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

     // �᫨ ��� 㤠���� ��।�����:
     if( Exe_name[ 0 ] != 0 )
      {
       // ����頥� ��㣨� ��⮪�� � ⮬, �� ��� �ਫ������ �����⭮.
       LONG Command = (LONG) Message->mp2; HMQ Thread_queue = NULLHANDLE;

       switch( Command )
        {
         case SM_CHANGE_VIO_FONT: Thread_queue = Enhancer.Modules.Changer->Message_queue; break;
        }

       if( Thread_queue != NULLHANDLE ) WinPostQueueMsg( Thread_queue, Command, (MPARAM) Frame_window, 0 );

       // ������.
       return;
      }

     // ���� �����஥ �६�.
     Retard();

     // �᫨ ���� ��� - ������.
     if( !WinIsWindow( WinQueryAnchorBlock( Frame_window ), Frame_window ) ) return;
    }
  }

 // ������.
 return;
}

// ��� ��⮪ ��� ᫥����� �� ⥪�⮢묨 ������ ���

VOID VIOMonitor_VIOMonitorThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.VIOMonitor->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.VIOMonitor->Message_queue == NULLHANDLE )
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
   VIOMonitor_VIOMonitorMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
