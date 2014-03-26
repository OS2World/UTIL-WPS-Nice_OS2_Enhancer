
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID VIOFontManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ���塞 ����� ��� ⥪�⮢�� ����.
 if( VIOFontManager.Settings.Change_VIO_font_metrics )
  {
   // ��⠭�������� ���� � ����.
   if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SET_VIO_FONT )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = (HWND) Message->mp2;

     // ���뫠�� ᮮ�饭�� � ��⮪.
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_APPLY_VIO_FONT, (MPARAM) Frame_window, 0 );
    }

   // ������ ���� ������ � ��ࠢ������ ��� �� �।��� �࠭�.
   if( Message->msg == WM_MARK ) if( Message->mp1 == (MPARAM) MRK_SHOW_AND_ARRANGE )
    {
     // ���뫠�� ᮮ�饭�� � ��⮪.
     HWND Frame_window = (HWND) Message->mp2;
     WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_SHOW_AND_ARRANGE, (MPARAM) Frame_window, 0 );
    }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID VIOFontManagerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // ���塞 ����� ��� ⥪�⮢�� ����.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) if( !RoomsChangeIsInProcess() )
  {
   // �᫨ ���� ࠬ�� �⠭������ ������:
   if( TopFrameWindowIsShowing( Message ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ �� ⥪�⮢�� ����:
     if( IsVIOWindow( Frame_window ) )
      {
       // ������ ��� �ਫ������, ᮧ���襣� ����.
       CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

       // �᫨ ��� 㤠���� ��।�����:
       if( Exe_name[ 0 ] != 0 )
        {
         // �᫨ � ���� ���� ������ ���� - ���뫠�� ᮮ�饭�� � ��⮪, ����� �� ᤥ����.
         if( VIOFontManager_VIOFontMustBeChanged( Frame_window ) )
          WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_CHANGE_VIO_FONT, (MPARAM) Frame_window, 0 );
        }
       // � �᫨ ��� �������⭮ - ���뫠�� ᮮ�饭�� � ��⮪, ����� �������� ��� �����஥ �६�.
       else
        {
         WinPostQueueMsg( Enhancer.Modules.VIOMonitor->Message_queue, SM_MONITOR_VIO, (MPARAM) Frame_window, (MPARAM) SM_CHANGE_VIO_FONT );
        }
      }
    }
  }

 // ������.
 return;
}
