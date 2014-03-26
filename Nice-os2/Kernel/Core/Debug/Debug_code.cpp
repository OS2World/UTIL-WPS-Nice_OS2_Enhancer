#ifdef DEBUG_VERSION

// ─── Короткий звук ───

VOID Krnl_Debug_Bzz( VOID )
{
 // Звук.
 DosBeep( 50, 50 );

 // Возврат.
 return;
}

// ─── Сброс сообщения в файл на диске ───

// Title и String - строки, которые надо записать.
VOID Krnl_Debug_Log( PCHAR Title, PCHAR String )
{
 // Если файла нет - создаем его.
 HFILE File = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_WRITEONLY;

 CHAR Log_file_name[ SIZE_OF_PATH ] = "";
 GetCurrentPath( Log_file_name ); strcat( Log_file_name, "\\_log.txt" );

 DosOpen( Log_file_name, &File, &Report, New_size, FILE_COMMON_ATTRIBUTES, Action, Mode, EAs );

 // Записываем строку.
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

 // Закрываем файл.
 DosClose( File ); File = NULLHANDLE;

 // Возврат.
 return;
}

// ─── Сброс сообщения в файл на диске ───

// String - строка, которую надо записать.
VOID Krnl_Debug_Log( PCHAR String )
{
 // Записываем строку.
 Krnl_Debug_Log( "", String );

 // Возврат.
 return;
}

// ─── Сброс сообщения в файл на диске ───

// Value и String - значение и строка, которую надо записать.
VOID Krnl_Debug_Log( FLOAT Value, PCHAR String )
{
 // Преобразуем число в строку.
 CHAR V_String[ 25 ] = ""; gcvt( Value, 5, V_String );

 INT End_of_string = strlen( V_String ) - 1;
 if( V_String[ End_of_string ] == '.' ) V_String[ End_of_string ] = 0;

 // Записываем строки.
 Krnl_Debug_Log( V_String, String );

 // Возврат.
 return;
}

// ─── Сброс сообщения в файл на диске ───

// String и Value - строка и значение, которое надо записать.
VOID Krnl_Debug_Log( PCHAR String, FLOAT Value )
{
 // Преобразуем число в строку.
 CHAR V_String[ 25 ] = ""; gcvt( Value, 5, V_String );

 INT End_of_string = strlen( V_String ) - 1;
 if( V_String[ End_of_string ] == '.' ) V_String[ End_of_string ] = 0;

 // Записываем строки.
 Krnl_Debug_Log( String, V_String );

 // Возврат.
 return;
}

// ─── Сброс сообщения в файл на диске ───

// Value - значение с точкой, которое надо записать.
VOID Krnl_Debug_Log( FLOAT Value )
{
 // Преобразуем число в строку.
 CHAR String[ 25 ] = ""; gcvt( Value, 5, String );

 INT End_of_string = strlen( String ) - 1;
 if( String[ End_of_string ] == '.' ) String[ End_of_string ] = 0;

 // Записываем строку.
 Krnl_Debug_Log( String );

 // Возврат.
 return;
}

#endif