
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ApplierInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // �᫨ ���� �믮����� ����⢨� � ������ ��������:
 if( Applier.Settings.Script_after_Logon || Applier.Settings.Remember_dialog_fields || Applier.Settings.Send_Yes )
  {
   // ���������� ���� ����� ��஫�. �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook() �� ��ࠡ�⪥ ��㣮�� ᮮ�饭��.
   if( Applier.Settings.Script_after_Logon )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_LOGON_WINDOW )
     {
      // ���뫠�� ᮮ�饭�� � ��⮪.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_WINDOW, (MPARAM) Frame_window, 0 );
     }

   // ���������� ���祭�� � ����� ����� ��஫�. �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook() �� ��ࠡ�⪥ ��㣮�� ᮮ�饭��.
   if( Applier.Settings.Script_after_Logon )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_LOGON_VALUES )
     {
      // ���뫠�� ᮮ�饭�� � ��⮪.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_VALUES, (MPARAM) Frame_window, 0 );
     }

   // ����⠭�������� ���� ����� � ����� ��������. �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook() �� ��ࠡ�⪥ ��㣮�� ᮮ�饭��.
   if( Applier.Settings.Remember_dialog_fields )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_COMPLETE_DIALOG )
     {
      // ���뫠�� ᮮ�饭�� � ��⮪.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_COMPLETE_DIALOG, (MPARAM) Frame_window, 0 );
     }

   // ����뢠�� ���� ��������. �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook() �� ��ࠡ�⪥ ��㣮�� ᮮ�饭��.
   if( Applier.Settings.Send_Yes )
    if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SEND_YES )
     {
      // ���뫠�� ᮮ�饭�� � ��⮪.
      HWND Frame_window = (HWND) Message->mp2;
      WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_SEND_YES, (MPARAM) Frame_window, 0 );
     }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID ApplierKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ���������� ���祭�� � ���� ����� ��஫�.
 if( Applier.Settings.Script_after_Logon ) if( Applier.RTSettings.Logon_in_process )
  {
   // ������ �� �����ﬨ �� ������.
   if( Message->msg == WM_CHAR )
    {
     // ����ਬ, ����� ������ �����.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // �᫨ ���� �⦠⨥ ������:
     if( State & KC_KEYUP )
      {
       // �஢��塞 �������.
       BYTE Latin_key = 0;

       if( Scan_code != 0 )
        if( !( State & KC_CTRL ) ) if( !( State & KC_ALT ) )
         Latin_key = 1;

       // �᫨ �� ��⨭᪠� ������:
       if( Latin_key )
        {
         // ������ ���� ࠬ��.
         HWND Frame_window = QueryFrameWindow( Message->hwnd );

         // �᫨ ��� ���� � ᯨ᪥ ��᫥�������� ����:
         for( INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count -- )
          if( Applier.RTDlgMemory.Logon_windows[ Count ].Window == Frame_window )
           {
            // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� �����⮢�� ���祭�� � ���� �����.
            HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
            WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_LOGON_VALUES, (MPARAM) Frame_window );
            break;
           }
        }
      }
    }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ApplierSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // �᫨ ���� �믮����� ����⢨� � ������ ��������:
 if( Applier.Settings.Script_after_Logon || Applier.Settings.Remember_dialog_fields || Applier.Settings.Send_Yes ) if( !RoomsChangeIsInProcess() )
  {
   // �᫨ ���� ࠬ�� �⠭������ ������:
   if( TopFrameWindowIsShowing( Message ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ ⠪�� ���� ᮤ�ন� ���� ��� ����� ��஫� � �� ���祭�� ���� ������:
     if( Applier.Settings.Script_after_Logon ) if( Applier_WindowIsPresentInLogonDialogList( Frame_window, 0 ) )
      {
       // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� �����⮢�� �� ᢮� ������ � ����� �㤥� �஢����� ��� ���������.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_LOGON_WINDOW, (MPARAM) Frame_window );
      }

     // �᫨ � ⠪�� ���� ���� ��������� ���� �� ��� ������:
     if( Applier.Settings.Remember_dialog_fields ) if( Applier_WindowIsPresentInIncompleteDialogList( Frame_window, 0 ) )
      {
       // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� �����⮢�� �� ᢮� ������ � ����� �㤥� �஢����� ��� ���������.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_COMPLETE_DIALOG, (MPARAM) Frame_window );
      }

     // �᫨ �� ���� ���� ����뢠�� �� ������:
     if( Applier.Settings.Send_Yes ) if( Applier_WindowIsPresentInMessageDialogList( Frame_window, 0 ) )
      {
       // ���뫠�� � ��।� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� �����⮢�� �� ᢮� ������ � ����� �㤥� �஢����� ��� ���������.
       HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
       WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SEND_YES, (MPARAM) Frame_window );
      }
    }

   // �᫨ ���� ���� ��� ����� ��஫� � ���� �� ���� ����뢠����:
   if( Applier.RTSettings.Logon_in_process ) if( Message->msg == WM_DESTROY )
    {
     // �᫨ ���� ���� � ᯨ᪥ ��᫥�������� ����:
     for( INT Count = APPLIER_MONITORING_LOGON_WINDOWS - 1; Count >= 0; Count -- )
      if( Applier.RTDlgMemory.Logon_windows[ Count ].Window == Message->hwnd )
       {
        // ���뫠�� ᮮ�饭�� � ��⮪. �� �믮���� �� ����室��� �஢�ન.
        WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_ACTION, (MPARAM) Message->hwnd, 0 );
        break;
       }
    }

   // �᫨ ���� ���� ��� ����� ��஫� � ���� �� ���� �⠭������ ��࠭��:
   if( Applier.RTSettings.Logon_in_process ) if( TopFrameWindowIsActivating( Message ) )
    {
     // ���뫠�� � ��⮪ ᮮ�饭�� � ⮬, �� ���� �஢���� ����⢮����� ���� ����� ��஫�.
     WinPostQueueMsg( Enhancer.Modules.Applier->Message_queue, SM_LOGON_CHECK, 0, 0 );
    }
  }

 // ������.
 return;
}
