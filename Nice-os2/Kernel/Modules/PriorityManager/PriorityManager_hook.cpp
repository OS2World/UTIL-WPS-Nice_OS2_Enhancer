
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PriorityManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ������� �ਮ���� �ਫ������ �� �����⨨ ����.
 if( PriorityManager.Settings.Dynamic_priority )
  {
   // �᫨ ���� ����뢠����:
   if( FrameWindowIsClosing( Message ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ � ���� ����� ��४������� �� ᯨ᪠ ����:
     if( WindowIsTouchable( Frame_window ) )
      {
       // �᫨ த�⥫�᪮� ���� - ࠡ�稩 �⮫:
       if( WinQueryWindow( Frame_window, QW_PARENT ) == QueryDesktopWindow() )
        {
         // ��⠭�������� �ਫ������ �������訩 �ਮ���.
         PriorityManager_SetDynamicPriorityLevels( SDPL_SUPPRESS_ACTIVE_PROCESS, Frame_window );
        }
      }
    }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PriorityManagerSendMsgHook( HAB Application, PSMHSTRUCT Message )
{
 // ���塞 �ਮ���� �ਫ������ �� ��४��祭�� ����� ������.
 if( PriorityManager.Settings.Normalize_priority || PriorityManager.Settings.Dynamic_priority ) if( !RoomsChangeIsInProcess() )
  {
   // �᫨ ���� ࠬ�� �⠭������ ��࠭��:
   if( TopFrameWindowIsActivating( Message ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // ��⠭�������� ���祭�� �ਮ��⮢.
     BYTE Priority_is_changed = 0;

     // �᫨ ���� �⠢��� �ਮ���� ��� ��� �ਫ������:
     if( PriorityManager.Settings.Dynamic_priority )
      {
       // ��⠭�������� ��.
       PriorityManager_SetDynamicPriorityLevels( SDPL_FORCE_ACTIVE_PROCESS, Frame_window );

       // ����������, �� �� ᤥ����.
       Priority_is_changed = 1;
      }

     // � �᫨ �⮣� ������ �� ���� - ����� ������ �ਮ���� ��� �ਫ������, 㪠������ ���짮��⥫��.
     if( !Priority_is_changed ) if( PriorityManager.Settings.Normalize_priority )
      if( PriorityManager_PermissionForPriorityActions( Frame_window ) )
       {
        // ������뢠�� �ਮ��� ��� �ਫ������.
        LONG Class = PRTYC_NOCHANGE;
        LONG Delta = PRTYD_INFINITY;

        PriorityManager_CalculatePriorityLevel( Frame_window, &Class, &Delta );

        // �����塞 ���, �᫨ �� �ॡ����.
        if( Class != PRTYC_NOCHANGE && Delta != PRTYD_INFINITY ) SetPriorityLevel( Frame_window, Class, Delta );
       }
    }
  }

 // ������� �ਮ��� �ਫ������, ���஥ ����⠥� ���� ��࠭��.
 // �� �������� �� �� ⮣�, ��� ��࠭�� �⠭�� ��㣮� �ਫ������.
 if( PriorityManager.Settings.Dynamic_priority )
  if( !RoomsChangeIsInProcess() ) if( TopFrameWindowIsInactivating( Message ) )
   {
    // ��⠭�������� �ਫ������ �������訩 �ਮ���.
    HWND Frame_window = QueryFrameWindow( Message->hwnd );
    PriorityManager_SetDynamicPriorityLevels( SDPL_SUPPRESS_ACTIVE_PROCESS, Frame_window );
   }

 // ������.
 return;
}
