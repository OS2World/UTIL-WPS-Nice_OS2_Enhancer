
// ��� �஢���� ᯨ᮪ ���� ��� 㤠����� ���

BYTE Remover_RemovingListIsEmpty( VOID )
{
 // �஢��塞 ᯨ᮪.
 if( Remover.Settings.WinListNames.Remove_from_list_1_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_2_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_3_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_4_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_5_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_6_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_7_name[ 0 ] == 0 )
 if( Remover.Settings.WinListNames.Remove_from_list_8_name[ 0 ] == 0 ) return 1;

 // ������.
 return 0;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID RemoverSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // ���뢠�� ��ப� � ᯨ᪥ ����.
 // �� ����� ������ ����� ᯨ᮪ ���� �⠭������ ��࠭��.
 if( Remover.Settings.Remove_items_from_Window_list ) if( !RoomsChangeIsInProcess() )
  if( TopFrameWindowIsActivating( Message ) )
   if( Remover.Settings.Hide_known_applications || !Remover_RemovingListIsEmpty() )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ �� ᯨ᮪ ����:
     if( IsWinListWindow( Frame_window ) )
      {
       // ���뫠�� ᮮ�饭�� � ��⮪.
       WinPostQueueMsg( Enhancer.Modules.Remover->Message_queue, SM_REMOVE_ITEMS, 0, 0 );
      }
    }

 // ������.
 return;
}
