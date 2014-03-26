// ��� ���ந������ ��� �� ����⨨ �� ������� ���

VOID Clicker_KeyboardEcho( VOID )
{
 // ��뢠�� �ந��뢠⥫�.
 if( FileExists( Clicker.RTSettings.Keyboard_exe ) )
  {
   CHAR Current_directory[ SIZE_OF_PATH ] = ""; GetCurrentPath( Current_directory );

   CHAR Player_path[ SIZE_OF_PATH ] = "";
   strcpy( Player_path, Clicker.RTSettings.Keyboard_exe ); CutNameInPath( Player_path );

   DosSetDefaultDisk( DriveNumberFromPath( Player_path ) ); DosSetCurrentDir( Player_path );
   CHAR Error_string[ 1 ] = ""; RESULTCODES Return_codes;
   DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_BACKGROUND, NULL, NULL, &Return_codes, Clicker.RTSettings.Keyboard_exe );
   DosSetDefaultDisk( DriveNumberFromPath( Current_directory ) ); DosSetCurrentDir( Current_directory );
  }

 // ������.
 return;
}

// ��� ��७��� 䠩� � ��㪮� �� ���������� �� ��� � ����� ���

VOID Clicker_CopyEchoFileToRAMDrive( VOID )
{
 // ������ ��� � �����.
 CHAR Memory_drive_directory[ SIZE_OF_PATH ] = ""; FindRAMDrive( Memory_drive_directory );

 // �᫨ �� ����:
 if( Memory_drive_directory[ 0 ] != 0 )
  {
   // ������ �६���� ��⠫��.
   CHAR Temp_directory[ SIZE_OF_PATH ] = ""; QueryTempDirectory( Temp_directory );

   // �᫨ �� �� ����� - ��⠥�, �� �� ��७� RAM-��᪠.
   if( Temp_directory[ 0 ] == 0 ) strcpy( Temp_directory, Memory_drive_directory );

   // �᫨ �६���� ��⠫�� �ᯮ����� �� RAM-��᪥ - �ᯮ��㥬 ���.
   // �� �ࠢ��� �ਬ������ � � ��砥, �᫨ �뫮 �믮����� �।��饥 ����⢨�.
   UpperCase( Temp_directory );
   if( Temp_directory[ 0 ] == Memory_drive_directory[ 0 ] )
    strcpy( Memory_drive_directory, Temp_directory );

   // ����� � �६���� ��⠫���� ��祣� ������ �� ����.
   Temp_directory[ 0 ] = 0;

   // ����塞 ��������� ���� � ���� ��ப�, �᫨ ��� ����.
   CutLastSlash( Memory_drive_directory );

   // ��७�ᨬ 䠩� � ��㪮� � �ந��뢠⥫�, � ⠪�� ���������� ����� �ᯮ�������.
   for( INT Count = 0; Count < 2; Count ++ )
    {
     PCHAR Source_name = "";
     if( Count == 0 ) Source_name = Clicker.RTSettings.Keyboard_wav;
     if( Count == 1 ) Source_name = Clicker.RTSettings.Keyboard_exe;

     CHAR New_name[ SIZE_OF_PATH ] = "";
     strcpy( New_name, Memory_drive_directory ); strcat( New_name, "\\" );
     strcat( New_name, FindNameInPath( Source_name ) );

     DosForceDelete( New_name );
     DosCopy( Source_name, New_name, 0 );

     strcpy( Source_name, New_name );
    }
  }

 // ������.
 return;
}

// ��� ��ࠡ��稪 ᮮ�饭��, ����� �뫨 ��।��� � ��⮪ ���

// Message ��।���� ��襤襥 ᮮ�饭��.
VOID Clicker_ClickerMessageProcessing( PQMSG Message )
{
 // ��⠭�������� �ਮ��� ��⮪�.
 if( Message->msg == SM_PRIORITY )
  {
   // ��⠭�������� �ਮ���.
   LONG Class = (LONG) Message->mp1;
   LONG Delta = (LONG) Message->mp2;
   DosSetPriority( PRTYS_THREAD, Class, Delta, 0 );

   // ���������� �ਮ���.
   Enhancer.Modules.Clicker->Priority = MAKELONG( Class, Delta );
  }

 // ���ந������ ���.
 if( Message->msg == SM_CLICK ) if( Clicker.Settings.Keyboard_echo ) Clicker_KeyboardEcho();

 // ������.
 return;
}

// ��� ��⮪ ��� ���ந�������� ��㪠 �� ����⨨ �� ������� ���

VOID Clicker_ClickerThread( VOID )
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
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 ); Enhancer.Modules.Clicker->Message_queue = Message_queue;

 // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
 if( Enhancer.Modules.Clicker->Message_queue == NULLHANDLE )
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
   Clicker_ClickerMessageProcessing( &Message );
  }

 // �����蠥� ࠡ��� ��⮪�.
 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );
 DosExit( EXIT_THREAD, 0 );
}
