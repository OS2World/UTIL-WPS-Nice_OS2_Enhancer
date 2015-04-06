
// ��� ��稭��� ��ᬮ�� ���窮� �� ࠡ�祬 �⮫� ���

VOID ObserverE_ExploreDesktop( VOID )
{
 // ������ �ਫ������ � ������� ��� ����.
 CHAR Rexx_script[ SIZE_OF_PATH ] = "";
 strcpy( Rexx_script, Inspector.Current_directory );
 strcat( Rexx_script, "\\Explore.cmd" );

 // �஢��塞 ����⢮����� �ਫ������.
 if( !FileExists( Rexx_script ) ) return;

 // ���������� �ᯮ��㥬� ⥪�⮢� ��⮪� �����/�뢮�� � ᮧ���� ����.
 Inspector.Saved_StdInHandle  = -1; HFILE New_StdInHandle  = STD_IN;
 Inspector.Saved_StdOutHandle = -1; HFILE New_StdOutHandle = STD_OUT;
 Inspector.Saved_StdErrHandle = -1; HFILE New_StdErrHandle = STD_ERR;

 Inspector.Pipe_ReadHandle_1 = NULLHANDLE; Inspector.Pipe_WriteHandle_1 = NULLHANDLE;
 Inspector.Pipe_ReadHandle_2 = NULLHANDLE; Inspector.Pipe_WriteHandle_2 = NULLHANDLE;

 DosDupHandle( STD_IN,  &Inspector.Saved_StdInHandle );
 DosDupHandle( STD_OUT, &Inspector.Saved_StdOutHandle );
 DosDupHandle( STD_ERR, &Inspector.Saved_StdErrHandle );

 DosCreatePipe( &Inspector.Pipe_ReadHandle_1, &Inspector.Pipe_WriteHandle_1, 4096 );
 DosCreatePipe( &Inspector.Pipe_ReadHandle_2, &Inspector.Pipe_WriteHandle_2, 4096 );

 DosDupHandle( Inspector.Pipe_ReadHandle_1,  &New_StdInHandle );
 DosDupHandle( Inspector.Pipe_WriteHandle_2, &New_StdOutHandle );
 DosDupHandle( Inspector.Pipe_WriteHandle_2, &New_StdErrHandle );

 // ������塞 � ���� ��ப�, �⮡� ��㣮� ��⮪ ��砫 ��� ����.
 {
  CHAR First_line[] = ">>\n\n"; ULONG Report = 0;
  DosWrite( Inspector.Pipe_WriteHandle_2, First_line, strlen( First_line ), &Report );
 }

 // ������� ��⮪, ����� �㤥� ���� ����.
 StartObserverReportReading();

 // ����᪠�� �ਫ������ � ���ࠢ�塞 ��� ��ப�, �⮡� ������� ����.
 {
  CHAR Command[] = "<<\n"; ULONG Report = 0;
  DosWrite( Inspector.Pipe_WriteHandle_1, Command, strlen( Command ), &Report );

  CHAR Rexx_parameters[ SIZE_OF_PATH ] = "--action=explore-desktop";

  {
   CHAR Rexx_launcher[] = "Cmd.exe";
   CHAR Launcher_parameters[ SIZE_OF_PATH ] = "";

   strcpy( Launcher_parameters, Rexx_launcher );   strcat( Launcher_parameters, "|" );
   strcat( Launcher_parameters, "/C" );            strcat( Launcher_parameters, " \"" );
   strcat( Launcher_parameters, Rexx_script );     strcat( Launcher_parameters, " " );
   strcat( Launcher_parameters, Rexx_parameters ); strcat( Launcher_parameters, "\"" );
   strchg( Launcher_parameters, '|', 0x00 );

   CHAR Error_string[ 1 ] = ""; RESULTCODES Return_codes;
   DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_SYNC, Launcher_parameters, NULL, &Return_codes, Rexx_launcher );
  }
 }

 // ������塞 �ਧ��� ���� ����.
 {
  CHAR Empty_line[] = "\n"; BYTE End_mark = 0x00; ULONG Report = 0;
  DosWrite( Inspector.Pipe_WriteHandle_2, Empty_line, strlen( Empty_line ), &Report );
  DosWrite( Inspector.Pipe_WriteHandle_2, &End_mark, 1, &Report );
 }

 // ������.
 return;
}

// ��� ��⮪ ��� ��ᬮ�� ���窮� �� ࠡ�祬 �⮫� ���

VOID ObserverE_ObserverThread( VOID )
{
 // ��।��塞 ��⮪ � ��⥬�.
 HAB Thread = WinInitialize( 0 );

 // ������� ��।� ᮮ�饭�� - ��� ������ ���� � ������ ��⮪�.
 HMQ Message_queue = WinCreateMsgQueue( Thread, 0 );

 // �᫨ �� ᤥ���� �� 㤠���� - ��室.
 if( Thread == NULLHANDLE || Message_queue == NULLHANDLE ) DosExit( EXIT_THREAD, 0 );

 // �⪫�砥� ��ப� ����, ����� ��뢠�� �����⨥ ����.
 WinSendMsg( WinWindowFromID( Inspector.Frame_window, FID_SYSMENU ), MM_SETITEMATTR, MPFROM2SHORT( SM_CLOSE, INCLUDE_SUBMENUS ), MPFROM2SHORT( MIA_DISABLED, MIA_DISABLED ) );

 // ��稭��� ��ᬮ�� ���窮� �� ࠡ�祬 �⮫�. �� ��ᬮ�� �㤥� ����祭 ����, ����� ���⠥� ��㣮� ��⮪
 DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, 0, 0 );
 ObserverE_ExploreDesktop();
 DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, 0, 0 );

 // ����砥� ��ப� ����, ����� ��뢠�� �����⨥ ����.
 WinSendMsg( WinWindowFromID( Inspector.Frame_window, FID_SYSMENU ), MM_SETITEMATTR, MPFROM2SHORT( SM_CLOSE, INCLUDE_SUBMENUS ), MPFROM2SHORT( MIA_DISABLED, 0 ) );

 // �����蠥� ��⮪.
 Inspector.Observing = 0;

 WinDestroyMsgQueue( Message_queue );
 WinTerminate( Thread );

 DosExit( EXIT_THREAD, 0 );
}

// ��� ����᪠�� ��⮪ ��� ��ᬮ�� ���窮� �� ࠡ�祬 �⮫� ���

VOID StartObserving( VOID )
{
 // �᫨ ��ࠡ�⪠ 㦥 ���� - ������.
 if( Inspector.Observing ) return;

 // ������� ��⮪.
 {
  TID Thread_ID = 0; DosCreateThread( &Thread_ID, (PFNTHREAD) ObserverE_ObserverThread, 0, 0, 32768 );
 }

 // ����������, �� �� ࠡ�⠥�.
 Inspector.Observing = 1;

 // ������.
 return;
}

