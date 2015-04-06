
// ��� ������뢠�� ���祭�� �ਮ��� ��� �ਫ������ ���

// Frame_window - ���� �ਫ������, Class � Delta - ���祭�� �ਮ���.
// �᫨ �ਮ��� �� �㤥� ����⠭, �� ���祭�� �������� �� ������.
VOID PriorityManager_CalculatePriorityLevel( HWND Frame_window, PLONG Class, PLONG Delta )
{
 // ��� �������� �ਫ������ ���� ��ࠢ������ �ਮ���.
 BYTE Normalize_priority = 0;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // �஢��塞, ���� �� �ਫ������ � ᯨ᪥ �᪫�祭��.
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) ) Normalize_priority = 1;
   if( stric( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) ) Normalize_priority = 1;
  }

 // ������ ���� ࠡ�祩 ������ ��� ���� ࠬ��.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) ) Normalize_priority = 1;
   if( strc( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) ) Normalize_priority = 1;
  }

 // ������ ���� ���祭��, �᫨ �� �ॡ����.
 // � ��⨢��� ��砥 ��⠢�塞 �� ��� ���������.
 if( Normalize_priority )
  {
   *Class = PRTYC_IDLETIME;
   *Delta = PRTYD_NORMAL;
  }

 // ������.
 return;
}

// ��� �������� ᯨ᮪ ������� �ਫ������ � RTSettings ���

// Visible_processes - ᯨ᮪, ����� ���� ���������.
VOID PriorityManager_CopyWindowListToRTSettings( VOID )
{
 // ����뢠�� �� ���祭�� � ᯨ᪥ ������� �ਫ������.
 PriorityManager.RTSettings.Visible_processes_quantity = 0;
 bzero( PriorityManager.RTSettings.Visible_processes, sizeof( VISIBLEPROCESS ) * SIZE_OF_VISPROCLIST );

 // ������ ᯨ᮪ ����.
 PSWBLOCK SWBlock = NULL; QuerySwitchList( &SWBlock );

 // ��७�ᨬ ���祭�� � ᯨ᮪ ������� �ਫ������ ��� ��᫥���饣� �ᯮ�짮�����.
 if( SWBlock->cswentry > SIZE_OF_VISPROCLIST ) SWBlock->cswentry = SIZE_OF_VISPROCLIST;

 for( INT Count = 0; Count < SWBlock->cswentry; Count ++ )
  if( SWBlock->aswentry[ Count ].swctl.uchVisibility == SWL_VISIBLE )
   if( SWBlock->aswentry[ Count ].swctl.hwnd != NULLHANDLE )
    if( WinIsWindow( WinQueryAnchorBlock( SWBlock->aswentry[ Count ].swctl.hwnd ), SWBlock->aswentry[ Count ].swctl.hwnd ) )
     {
      PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = SWBlock->aswentry[ Count ].swctl.idProcess;
      PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window = SWBlock->aswentry[ Count ].swctl.hwnd;

      PriorityManager.RTSettings.Visible_processes[ Count ].Program_type = SWBlock->aswentry[ Count ].swctl.bProgType;
      strcpy( PriorityManager.RTSettings.Visible_processes[ Count ].Title, SWBlock->aswentry[ Count ].swctl.szSwtitle );

      PriorityManager.RTSettings.Visible_processes_quantity = Count;
     }

 // �᢮������� ������.
 FreeSwitchListMemory( SWBlock ); SWBlock = NULL;

 // ������.
 return;
}

// ��� ���⠢��� �ਮ���� �ᥬ ������ �ਫ������ ���

// Action - ����⢨�, ���஥ ���� �믮�����.
VOID PriorityManager_SetDynamicPriorityLevels( LONG Action )
{
 // �᫨ ������ �ਮ���� �� ���� - ������.
 if( !PriorityManager.Settings.Dynamic_priority ) return;

 // ������ ᯨ᮪ ������� �ਫ������.
 PriorityManager_CopyWindowListToRTSettings();

 // �᫨ ���� ������� �ਮ���� ��� ��� �ਫ������ � �������
 // �ਮ��� ⮣� �ਫ������, � ����� ࠡ�⠥� ���짮��⥫�:
 if( Action == SDPL_FORCE_ACTIVE_PROCESS )
  {
   // �����砥� ������ �ਮ��� �ᥬ �ਫ������.
   // �� ���祭�� ��⠭���� ��� ��������� �ਫ������.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �⠢�� �ਮ���.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_IDLETIME;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_NORMAL;
    }

   // ������ �ਫ������, ����騬 ������ ����, �।��� �ਮ���, �
   // �ਫ������, � ����� ࠡ�⠥� ���짮��⥫� - ��᮪�� �ਮ���.
   for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �᫨ ���� �� ���� � ��� �� ���� ��� ����� �� �࠭�:
     if( WinIsWindowVisible( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) &&
         WinIsWindowShowing( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) )
      {
       // ������ �ਫ������, ᮧ���襥 �� ����.
       PID Inactive_process = PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID;

       // ������뢠�� �ਮ��� ��� �ਫ������.
       LONG Class = PRTYC_IDLETIME;
       LONG Delta = PRTYD_QUICK;

       if( WindowIsActive( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) )
        {
         Class = PRTYC_REGULAR;
         Delta = PRTYD_NORMAL;
        }

       if( PriorityManager.Settings.Normalize_priority ) 
        {
         PriorityManager_CalculatePriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, &Class, &Delta );
        }

       // ���塞 ��� ᢮��⢠ � ᯨ᪥.
       for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
        if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Inactive_process )
         {
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_class = Class;
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_delta = Delta;
         }
      }
    }
  }

 // �᫨ ���� ������ �ᥬ �ਫ������ ������ �ਮ���:
 if( Action == SDPL_SUPPRESS_ALL_PROCESSES )
  {
   // ������ �ᥬ �ਫ������ ������ �ਮ���.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �⠢�� �ਮ���.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_IDLETIME;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_NORMAL;
    }
  }

 // �᫨ ���� ������ �ᥬ �ਫ������ ����� �ਮ���:
 if( Action == SDPL_RESTORE_ALL_PROCESSES )
  {
   // ������ �ᥬ �ਫ������ ����� �ਮ���.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �⠢�� �ਮ���.
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_NORMAL;
    }
  }

 // ����뢠�� �ਫ������, ����� �ண��� �� ����.
 for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // �᫨ ������ �ਮ��� ����� - 㤠�塞 �� ����� ��� �⮣� �ਫ������.
   if( !PriorityManager_PermissionForPriorityActions( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) ||
       !PriorityManager_PermissionForDynamicPriorityActions( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Title ) )
    {
     // ������ �ਫ������, ���஥ ����� �ண���.
     PID Excepted_process = PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID;

     // ����塞 ��� �� ᯨ᪠.
     for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
      if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Excepted_process )
       PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID = 0;

     // ����塞 �� ᯨ᪠ ⥪���� ������.
     PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = 0;
    }
  }

 // ����뢠�� ������.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // ����뢠�� ������.
   for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
    if( Pointer != Count )
     if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID )
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID = 0;
  }

 // ��⠭�������� �ਮ����.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // ��⠭�������� �ਮ���.
   SetPriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta );
  }

 // ������.
 return;
}
