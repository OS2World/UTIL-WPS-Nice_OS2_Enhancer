
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
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) == EQUALLY ) Normalize_priority = 1;
   if( stricmpe( Exe_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) == EQUALLY ) Normalize_priority = 1;
  }

 // ������ ���� ࠡ�祩 ������ ��� ���� ࠬ��.
 HWND Client_window = WinWindowFromID( Frame_window, FID_CLIENT );

 // �᫨ ��� ����:
 if( Client_window != NULLHANDLE )
  {
   // ������ ���, ��� ����� ��।����� ���� ࠡ�祩 ������.
   CHAR Window_name[ SIZE_OF_NAME ] = ""; WinQueryClassName( Client_window, SIZE_OF_NAME, Window_name );

   // �஢��塞, ���� �� ���� � ᯨ᪥ �᪫�祭��.
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name ) == EQUALLY ) Normalize_priority = 1;
   if( strcmp( Window_name, PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name ) == EQUALLY ) Normalize_priority = 1;
  }

 // ������ ���� ���祭��, �᫨ �� �ॡ����.
 // � ��⨢��� ��砥 ��⠢�塞 �� ��� ���������.
 if( Normalize_priority )
  {
   *Class = PRTYC_IDLETIME;
   *Delta = PRTYD_NORMAL;
   return;
  }

 // ������.
 return;
}

// ��� �������� ��饭�� ᯨ᮪ ������� �ਫ������ � RTSettings ���

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

// Action - ����⢨�, ���஥ ���� �믮�����, Active_window - ��࠭��� ����.
VOID PriorityManager_SetDynamicPriorityLevels( LONG Action, HWND Active_window = NULLHANDLE )
{
 // �᫨ ������ �ਮ���� �� ���� - ������.
 if( !PriorityManager.Settings.Dynamic_priority ) return;

 // ������ ᯨ᮪ ������� �ਫ������.
 PriorityManager_CopyWindowListToRTSettings();

 // ������ �ਫ������, ���஥ ᥩ�� ��࠭�.
 PID Active_process = 0;

 if( Action == SDPL_FORCE_ACTIVE_PROCESS || Action == SDPL_SUPPRESS_ACTIVE_PROCESS )
  {
   // ������ ����, ���஥ ᥩ�� ��࠭�.
   if( Active_window == NULLHANDLE ) Active_window = WinQueryActiveWindow( QueryDesktopWindow() );

   // �᫨ ��� ����:
   if( Active_window != NULLHANDLE )
    {
     // ������ �ਫ������, ���஥ ᥩ�� ��࠭�.
     Active_process = QueryWindowRealProcessID( Active_window );
    }
  }

 // �᫨ ���� ������� �ਮ���� ��� ��� �ਫ������:
 if( Action == SDPL_FORCE_ACTIVE_PROCESS && Active_process != 0 )
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

   // ������ ������࠭�� �ਫ������ �।��� �ਮ���.
   for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �᫨ �ਫ������ ���� � ����� �࠭ - �����砥� ��� �।��� �ਮ���.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_FULLSCREEN )
      {
       // ������뢠�� �ਮ��� ��� �ਫ������.
       LONG Class = PRTYC_IDLETIME;
       LONG Delta = PRTYD_MAXIMUM;

       if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, &Class, &Delta );

       // ���塞 ��� ᢮��⢠ � ᯨ᪥.
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = Class;
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = Delta;
      }
    }

   // ������ �ਫ������, ����騬 ������ ����, ��訩 �ਮ���.
   for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �᫨ ���� ������ - �⠢�� �ਫ������ ��訩 �ਮ���.
     if( WinIsWindowShowing( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window ) )
      {
       // ������ �ਫ������, ᮧ���襥 �� ����.
       PID Inactive_process = PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID;

       // ������뢠�� �ਮ��� ��� �ਫ������.
       LONG Class = PRTYC_REGULAR;
       LONG Delta = PRTYD_MINIMUM;

       if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, &Class, &Delta );

       // ���塞 ��� ᢮��⢠ � ᯨ᪥.
       for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
        if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Inactive_process )
         {
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_class = Class;
          PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_delta = Delta;
         }
      }
    }

   // ������ ��᮪�� �ਮ��� �ਫ������, � ����� ࠡ�⠥� ���짮��⥫�.
   LONG Class = PRTYC_REGULAR;
   LONG Delta = PRTYD_NORMAL;

   if( PriorityManager.Settings.Normalize_priority ) PriorityManager_CalculatePriorityLevel( Active_window, &Class, &Delta );

   // ���塞 ��� ᢮��⢠ � ᯨ᪥.
   for( INT Pointer = 0; Pointer < SIZE_OF_VISPROCLIST; Pointer ++ )
    if( PriorityManager.RTSettings.Visible_processes[ Pointer ].Process_ID == Active_process )
     {
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_class = Class;
      PriorityManager.RTSettings.Visible_processes[ Pointer ].Priority_delta = Delta;
     }
  }

 // �᫨ ���� ᭨���� �ਮ��� ������ �ਫ������:
 if( Action == SDPL_SUPPRESS_ACTIVE_PROCESS && Active_process != 0 )
  {
   // ������ �ਫ������ ������ �ਮ���. ��⠫�� �ਫ������ �� �ண���.
   for( INT Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
    {
     // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

     // �⠢�� �ਮ��� ��࠭���� �ਫ������.
     if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == Active_process )
      {
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
       PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_MINIMUM;
      }
     // ����塞 �� ᯨ᪠ ��⠫�� �ਫ������.
     else
      {
       PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = 0;
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
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class = PRTYC_REGULAR;
     PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta = PRTYD_MINIMUM;
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

 // ��⠭�������� �ਮ���� ��� ⥪�⮢�� �ਫ������.
 for( Count = 0; Count < SIZE_OF_VISPROCLIST; Count ++ )
  {
   // �᫨ ������ ��祣� �� ᮤ�ন� - �த������ ��ᬮ�� ᯨ᪠.
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID == 0 ) continue;

   // �᫨ �� ⥪�⮢�� �ਫ������:
   if( PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_FULLSCREEN ||
       PriorityManager.RTSettings.Visible_processes[ Count ].Program_type == PROG_WINDOWABLEVIO )
    {
     // ��⠭�������� �ਮ���.
     SetPriorityLevel( PriorityManager.RTSettings.Visible_processes[ Count ].Frame_window, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_class, PriorityManager.RTSettings.Visible_processes[ Count ].Priority_delta );

     // ����뢠�� �ਫ������ �� ᯨ᪠.
     PriorityManager.RTSettings.Visible_processes[ Count ].Process_ID = 0;
    }
  }

 // ��⠭�������� �ਮ���� ��� ������� �ਫ������.
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
