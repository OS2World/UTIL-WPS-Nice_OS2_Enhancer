#ifdef DEBUG_VERSION

// ��� ���⪨� ��� ���

VOID Krnl_Debug_Bzz( VOID )
{
 // ���.
 DosBeep( 50, 50 );

 // ������.
 return;
}

// ��� ���� ᮮ�饭�� � 䠩� �� ��᪥ ���

// Title � String - ��ப�, ����� ���� �������.
VOID Krnl_Debug_Log( PCHAR Title, PCHAR String )
{
 // �᫨ 䠩�� ��� - ᮧ���� ���.
 HFILE File = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_WRITEONLY;

 CHAR Log_file_name[ SIZE_OF_PATH ] = "";
 GetCurrentPath( Log_file_name ); strcat( Log_file_name, "\\_log.txt" );

 DosOpen( Log_file_name, &File, &Report, New_size, FILE_COMMON_ATTRIBUTES, Action, Mode, EAs );

 // �����뢠�� ��ப�.
 if( Report != FILE_CREATED )
  {
   DosSetFilePtr( File, 0, FILE_END, &Report );
   DosWrite( File, "\n", strlen( "\n" ), &Report );
  }

 if( Title[ 0 ] != 0 )
  {
   DosWrite( File, Title, strlen( Title ), &Report );
   DosWrite( File, ": ", strlen( ": " ), &Report );
  }

 DosWrite( File, String, strlen( String ), &Report );

 // ����뢠�� 䠩�.
 DosClose( File ); File = NULLHANDLE;

 // ������.
 return;
}

// ��� ���� ᮮ�饭�� � 䠩� �� ��᪥ ���

// String - ��ப�, ������ ���� �������.
VOID Krnl_Debug_Log( PCHAR String )
{
 // �����뢠�� ��ப�.
 Krnl_Debug_Log( "", String );

 // ������.
 return;
}

// ��� ���� ᮮ�饭�� � 䠩� �� ��᪥ ���

// Value � String - ���祭�� � ��ப�, ������ ���� �������.
VOID Krnl_Debug_Log( FLOAT Value, PCHAR String )
{
 // �८�ࠧ㥬 �᫮ � ��ப�.
 CHAR V_String[ 25 ] = ""; gcvt( Value, 5, V_String );

 INT End_of_string = strlen( V_String ) - 1;
 if( V_String[ End_of_string ] == '.' ) V_String[ End_of_string ] = 0;

 // �����뢠�� ��ப�.
 Krnl_Debug_Log( V_String, String );

 // ������.
 return;
}

// ��� ���� ᮮ�饭�� � 䠩� �� ��᪥ ���

// String � Value - ��ப� � ���祭��, ���஥ ���� �������.
VOID Krnl_Debug_Log( PCHAR String, FLOAT Value )
{
 // �८�ࠧ㥬 �᫮ � ��ப�.
 CHAR V_String[ 25 ] = ""; gcvt( Value, 5, V_String );

 INT End_of_string = strlen( V_String ) - 1;
 if( V_String[ End_of_string ] == '.' ) V_String[ End_of_string ] = 0;

 // �����뢠�� ��ப�.
 Krnl_Debug_Log( String, V_String );

 // ������.
 return;
}

// ��� ���� ᮮ�饭�� � 䠩� �� ��᪥ ���

// Value - ���祭�� � �窮�, ���஥ ���� �������.
VOID Krnl_Debug_Log( FLOAT Value )
{
 // �८�ࠧ㥬 �᫮ � ��ப�.
 CHAR String[ 25 ] = ""; gcvt( Value, 5, String );

 INT End_of_string = strlen( String ) - 1;
 if( String[ End_of_string ] == '.' ) String[ End_of_string ] = 0;

 // �����뢠�� ��ப�.
 Krnl_Debug_Log( String );

 // ������.
 return;
}

#endif