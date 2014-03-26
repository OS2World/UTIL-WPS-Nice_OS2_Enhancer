
// ��� ������, ������ �� �� ���� 㤠������ �� ᯨ᪠ ���� ���

// WinList_title - �������� � ᯨ᪥ ����.
BYTE Remover_WindowWillBeHidden( PCHAR WinList_title )
{
 // �᫨ ���� 㤠���� ��ப� �� ᯨ᪠ ����:
 if( Remover.Settings.Remove_items_from_Window_list )
  {
   // �஢��塞 ����.
   for( INT Item_count = 0; Item_count < 8; Item_count ++ )
    {
     PCHAR Item_name = Remover.Settings.WinListNames.Remove_from_list_1_name;
     if( Item_count == 1 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_2_name;
     if( Item_count == 2 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_3_name;
     if( Item_count == 3 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_4_name;
     if( Item_count == 4 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_5_name;
     if( Item_count == 5 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_6_name;
     if( Item_count == 6 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_7_name;
     if( Item_count == 7 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_8_name;

     if( Item_name[ 0 ] != 0 )
      if( strifind( Item_name, WinList_title ) ) return 1;
    }
  }

 // ������.
 return 0;
}

// ��� ���뢠�� ��� �����뢠�� ��ப� � ᯨ᪥ ���� ���

// Show_items - ����� ��� �������� ��ப�, Hide_known_applications - ����� ������� �ਫ������.
VOID Remover_ShowAllItemsInSwitchList( BYTE Show_or_hide, BYTE Hide_known_applications = 0 )
{
 // ���� �����窨 ������ �����.
 PCHAR Shell_window_item = NULL;

 if( ShellIsWPS() )
  {
   // ������ ���� �����窨.
   HWND Shell_window = GetDetectedShellWindow();

   if( Shell_window != NULLHANDLE )
    {
     // ������, ���� �� ��� � ᯨ᪥ ����.
     HSWITCH Switch_handle = WinQuerySwitchHandle( Shell_window, NULLHANDLE );
     SWCNTRL Task; bzero( &Task, sizeof( SWCNTRL ) );

     // �᫨ ��� ��� - ������塞 ���.
     if( Switch_handle == NULLHANDLE )
      {
       Task.hwnd = Shell_window;
       GetDefaultShellTitle( Task.szSwtitle );

       Task.uchVisibility = SWL_VISIBLE;
       Task.fbJump = SWL_JUMPABLE;

       HSWITCH Switch_handle = WinAddSwitchEntry( &Task );
      }
     // �᫨ ��� ���� - ������ ��� ������ � ᯨ᪥.
     else
      {
       WinQuerySwitchEntry( Switch_handle, &Task );

       if( Task.uchVisibility != SWL_VISIBLE || Task.fbJump != SWL_JUMPABLE )
        ShowItemInSwitchList( Switch_handle, Task, 1 );
      }

     // ���������� ��ப�.
     Shell_window_item = Task.szSwtitle;
    }
  }

 // ������ ᯨ᮪ ����.
 PSWBLOCK SWBlock = NULL; QuerySwitchList( &SWBlock );

 // �����뢠�� ��� ��뢠�� ��ப�.
 {
  INT Count; INT Item_count;

  for( Count = 0; Count < SWBlock->cswentry; Count ++ )
   {
    BYTE Hide_this_item = 0;

    // ���뢠�� �ਫ������, ������� ����⥫�.
    if( Hide_known_applications )
     {
      HWND Frame_window = SWBlock->aswentry[ Count ].swctl.hwnd;

      if( !Hide_this_item && IsECenterWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IsWarpCenterWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IsLaunchPadWindow( Frame_window ) ) Hide_this_item = 1;
      if( !Hide_this_item && IslSwitcherWindow( Frame_window ) ) Hide_this_item = 1;

      if( !Hide_this_item && ShellIsWPS() )
       {
        if( WindowIsUsedTo( DO_IMPROVE_WORKPLACE, Frame_window ) )
         if( !WindowIsCreatedBy( APP_NICE, Frame_window ) )
          Hide_this_item = 1;

        if( !Hide_this_item && IsSysTrayWindow( Frame_window ) ) Hide_this_item = 1;
        if( !Hide_this_item && IsSmartBarWindow( Frame_window ) ) Hide_this_item = 1;
       }
     }

    // ���뢠�� �ਫ������, ������� ���짮��⥫��.
    for( Item_count = 0; Item_count < 8; Item_count ++ )
     {
      PCHAR Item_name = Remover.Settings.WinListNames.Remove_from_list_1_name;
      if( Item_count == 1 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_2_name;
      if( Item_count == 2 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_3_name;
      if( Item_count == 3 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_4_name;
      if( Item_count == 4 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_5_name;
      if( Item_count == 5 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_6_name;
      if( Item_count == 6 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_7_name;
      if( Item_count == 7 ) Item_name = Remover.Settings.WinListNames.Remove_from_list_8_name;

      if( Item_name[ 0 ] != 0 )
       {
        PCHAR Title = SWBlock->aswentry[ Count ].swctl.szSwtitle;

        #ifndef INCLUDED_BY_SHELL

        if( Shell_window_item != NULL )
         if( strcmp( Title, Shell_window_item ) == EQUALLY ) continue;

        #endif

        if( strcmp( Title, Item_name ) == EQUALLY ) Hide_this_item = 1;
       }

       if( Hide_this_item ) break;
     }

    // ���뢠�� ��ப�.
    if( Hide_this_item )
     {
      HSWITCH Switch_handle = SWBlock->aswentry[ Count ].hswitch;
      SWCNTRL Task = SWBlock->aswentry[ Count ].swctl;

      ShowItemInSwitchList( Switch_handle, Task, Show_or_hide );
     }
   }
 }

 // �᢮������� ������.
 FreeSwitchListMemory( SWBlock ); SWBlock = NULL;

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Remover_RemoverMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Remover->Priority = MAKELONG( Class, Delta );
  }

 // ���뢠�� ��ப� � ᯨ᪥ ����.
 if( Message->msg == SM_REMOVE_ITEMS ) Remover_ShowAllItemsInSwitchList( 0, Remover.Settings.Hide_known_applications );

 // ������.
 return;
}


// ��� ��⮪ ��� 㤠����� ��ப �� ᯨ᪠ ���� ���

VOID Remover_RemoverThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Remover->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Remover->Message_queue == NULLHANDLE )
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
   Remover_RemoverMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
