
// ��� ������ �㪢� �������묨, �ᯮ���� ���������� OS/2 ���

VOID Strings_CaseTranslator( PCHAR Bytes, INT Length )
{
 // �᫨ ��ப� �� ������ - ������.
 if( Bytes == NULL ) return;
 if( Length <= 0 ) return;

 // �᫨ ������ ������㯭� - ������.
 if( Strings == NULL ) return;

 // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
 if( !Strings->Inner_settings.Country.codepage )
  {
   ULONG Size_of_list = 0;
   DosQueryCp( sizeof( Strings->Inner_settings.Country.codepage ), &Strings->Inner_settings.Country.codepage, &Size_of_list );
  }

 // �᫨ ���� ��� ��ॢ��� �� ��⮢� - ᮧ���� ��.
 if( Strings->Inner_settings.Case_map[ 0 ] == 0 )
  {
   INT Count;
   for( Count = 0; Count < 255; Count ++ ) Strings->Inner_settings.Case_map[ Count ] = Count + 1;

   DosMapCase( 255, &Strings->Inner_settings.Country, Strings->Inner_settings.Case_map );
  }

 // �믮��塞 ��ॢ��, ����⠢��� ���祭��. ��� 0x01 ������ �㫥��� ���祭�� � �. �.
 {
  INT Offset;
  for( Offset = 0; Offset < Length; Offset ++ ) Bytes[ Offset ] = Strings->Inner_settings.Case_map[ Bytes[ Offset ] - 1 ];
 }

 return;
}

// ��� ������ ����� ��ப� ���

// String - ��ப�.
INT Strings_strlen( PCHAR String )
{
 if( String == NULL ) return 0;

 {
  INT strlen = 0; while( String[ strlen ] != 0 ) strlen ++;

  return strlen;
 }
}

// ��� ��७��� ���� ��ப� � ����� ���

// Source - ���筨�, Target - �����祭��, Length - ����� ��ப�.
VOID Strings_strncpy( PCHAR Target, PCHAR Source, INT Length )
{
 if( Target == NULL ) return;
 if( Source == NULL ) return;
 if( Length <= 0 ) return;

 {
  INT Count = 0;

  while( Source[ Count ] != 0 && Count < Length )
   {
    Target[ Count ] = Source[ Count ];
    Count ++;
   }

  Target[ Count ] = 0;
 }

 return;
}

// ��� ��७��� ���� ��ப� � ����� ���

// Source - ���筨�, Target - �����祭��.
VOID Strings_strcpy( PCHAR Target, PCHAR Source )
{
 Strings_strncpy( Target, Source, INT_MAX );

 return;
}

// ��� �������� ��ப� ���

// String_1, String_2 - ��ப�.
VOID Strings_strcat( PCHAR String_1, PCHAR String_2 )
{
 if( String_1 == NULL ) return;
 if( String_2 == NULL ) return;

 {
  INT Count = 0;
  INT strlen = Strings_strlen( String_1 );

  while( String_2[ Count ] != 0 )
   {
    String_1[ strlen + Count ] = String_2[ Count ];
    Count ++;
   }

  String_1[ strlen + Count ] = 0;
 }

 return;
}

// ��� �ࠢ������ ��ப� ���

// *_string - ��ப�.
INT Strings_strcmp( PCHAR First_string, PCHAR Second_string )
{
 if( First_string == NULL ) return STRINGNE;
 if( Second_string == NULL ) return STRINGNE;

 if( Strings_strlen( First_string ) != Strings_strlen( Second_string ) ) return STRINGNE;

 {
  INT Count = 0;
  while( First_string[ Count ] != 0 || Second_string[ Count ] != 0 )
   {
    if( First_string[ Count ] != Second_string[ Count ] ) return STRINGNE;

    Count ++;
   }
 }

 return EQUALLY;
}

// ��� �ࠢ������ ��ப� �� ࠧ���� �������� � ����� �㪢� ���

// *_string - ��ப�.
INT Strings_stricmpe( PCHAR First_string, PCHAR Second_string )
{
 if( First_string == NULL ) return STRINGNE;
 if( Second_string == NULL ) return STRINGNE;

 if( Strings_strlen( First_string ) != Strings_strlen( Second_string ) ) return STRINGNE;

 {
  INT Count = 0;
  while( First_string[ Count ] != 0 || Second_string[ Count ] != 0 )
   {
    CHAR Character_1 = First_string[ Count ];
    CHAR Character_2 = Second_string[ Count ];
    Strings_CaseTranslator( &Character_1, 1 );
    Strings_CaseTranslator( &Character_2, 1 );

    if( Character_1 != Character_2 ) return STRINGNE;

    Count ++;
   }
 }

 return EQUALLY;
}

// ��� ����뢠�� ���⮪ ����� ���

// Pointer - 㪠��⥫�, Init_byte - ���祭��, Length - ����� ���⪠ �����.
VOID Strings_memset( PVOID Pointer, BYTE Init_byte, INT Length )
{
 if( Pointer == NULL ) return;
 if( Length <= 0 ) return;

 if( Init_byte != 0 )
  {
   PBYTE Target_pointer = (PBYTE) Pointer;
   INT Count;

   for( Count = 0; Count < Length; Count ++ ) Target_pointer[ Count ] = Init_byte;
  }
 else
  {
   if( Length == sizeof( ULONG ) )
    {
     PULONG Target_pointer = (PULONG) Pointer;
     Target_pointer[ 0 ] = 0;

     return;
    }

   {
    INT Remainder = Length;
    INT Pass_point = 0;

    if( Length > sizeof( ULONG ) )
     {
      Remainder = Length % sizeof( ULONG );
      Pass_point = Length - Remainder;

      {
       PULONG Target_pointer = (PULONG) Pointer;
       INT Count;

       INT Steps = Pass_point / sizeof( ULONG );

       for( Count = 0; Count < Steps; Count ++ ) Target_pointer[ Count ] = 0;
      }
     }

    if( Remainder != 0 )
     {
      PBYTE Target_pointer = (PBYTE) Pointer;
      INT Count;

      for( Count = Pass_point; Count < Pass_point + Remainder; Count ++ ) Target_pointer[ Count ] = 0;
     }
   }
  }

 return;
}

// ��� ����뢠�� ���⮪ ����� ���

// Pointer - 㪠��⥫�, Length - ����� ���⪠ �����.
VOID Strings_bzero( PVOID Pointer, INT Length )
{
 if( Pointer == NULL ) return;
 if( Length <= 0 ) return;

 Strings_memset( Pointer, 0, Length );

 return;
}

// ��� ��७��� ���⮪ ����� �� ������ ���� � ��㣮� ���

// Source, Target - 㪠��⥫�, Length - ����� ���⪠ �����.
VOID Strings_memcpy( PVOID Target, PVOID Source, INT Length )
{
 if( Target == NULL ) return;
 if( Source == NULL ) return;
 if( Length <= 0 ) return;

 if( Length == sizeof( ULONG ) )
  {
   PULONG Target_pointer = (PULONG) Target;
   PULONG Source_pointer = (PULONG) Source;

   Target_pointer[ 0 ] = Source_pointer[ 0 ];

   return;
  }

 {
  INT Remainder = Length;
  INT Pass_point = 0;

  if( Length > sizeof( ULONG ) )
   {
    Remainder = Length % sizeof( ULONG );
    Pass_point = Length - Remainder;

    {
     PULONG Target_pointer = (PULONG) Target;
     PULONG Source_pointer = (PULONG) Source;
     INT Count;

     INT Steps = Pass_point / sizeof( ULONG );

     for( Count = 0; Count < Steps; Count ++ ) Target_pointer[ Count ] = Source_pointer[ Count ];
    }
   }

  if( Remainder != 0 )
   {
    PBYTE Target_pointer = (PBYTE) Target;
    PBYTE Source_pointer = (PBYTE) Source;
    INT Count;

    for( Count = Pass_point; Count < Pass_point + Remainder; Count ++ ) Target_pointer[ Count ] = Source_pointer[ Count ];
   }
 }

 return;
}

// ��� ��室�� ��ப� � ��㣮� ��ப� ���

// Key - ��ப� ��� ���᪠, String - ��� �� �᪠��.
PCHAR Strings_strfind( PCHAR Key, PCHAR String )
{
 if( Key == NULL ) return NULL;
 if( String == NULL ) return NULL;

 {
  INT strlen = Strings_strlen( String );
  INT Keylen = Strings_strlen( Key );

  if( Keylen > strlen ) return NULL;
  if( Strings_strcmp( Key, String ) == EQUALLY ) return String;

  {
   INT Offset;
   for( Offset = 0; Offset <= strlen - Keylen + 1; Offset ++ )
    {
     BYTE Strings_is_equally = 1; INT Count;
     for( Count = 0; Count < Keylen; Count ++ )
      if( Key[ Count ] != String[ Offset + Count ] )
       {
        Strings_is_equally = 0;
        break;
       }

     if( Strings_is_equally ) return &String[ Offset ];
    }
  }
 }

 return NULL;
}

// ��� ��室�� ��ப� � ��㣮� ��ப� �� ࠧ���� �������� � ����� �㪢� ���

// Key - ��ப� ��� ���᪠, String - ��� �� �᪠��.
PCHAR Strings_strifind( PCHAR Key, PCHAR String )
{
 if( Key == NULL ) return NULL;
 if( String == NULL ) return NULL;

 {
  INT strlen = Strings_strlen( String );
  INT Keylen = Strings_strlen( Key );

  if( Keylen > strlen ) return NULL;
  if( Strings_stricmpe( Key, String ) == EQUALLY ) return String;

  {
   INT Offset;
   for( Offset = 0; Offset <= strlen - Keylen + 1; Offset ++ )
    {
     BYTE Strings_is_equally = 1; BYTE Leave = 0; INT Count;
     for( Count = 0; Count < Keylen; Count ++ )
      {
       CHAR Character_from_key = Key[ Count ];
       CHAR Character_from_string = String[ Offset + Count ];
       Strings_CaseTranslator( &Character_from_key, 1 );
       Strings_CaseTranslator( &Character_from_string, 1 );

       if( Character_from_key != Character_from_string )
        {
         Strings_is_equally = 0;
         break;
        }
      }

     if( Strings_is_equally ) return &String[ Offset ];
    }
  }
 }

 return NULL;
}

// ��� ������� �㪢� � ��ப� ���

// Key � Replacement - �㪢� ��� ������, String - ��� �� �᪠��.
VOID Strings_strchg( PCHAR String, CHAR Key, CHAR Replacement )
{
 if( String == NULL ) return;

 {
  INT strlen = Strings_strlen( String );

  INT Count;
  for( Count = 0; Count < strlen; Count ++ )
   if( String[ Count ] == Key ) String[ Count ] = Replacement;
 }

 return;
}

// ��� ������� ���� ��ப� �� ����� ���

// Key � Replacement - ᫮�� ��� ������, String - ��� �� �᪠��.
VOID Strings_strschg( PCHAR String, PCHAR Key, PCHAR Replacement )
{
 if( String == NULL ) return;
 if( Key == NULL ) return;
 if( Replacement == NULL ) return;

 {
  INT strlen = Strings_strlen( String );
  INT Keylen = Strings_strlen( Key );

  PCHAR Pointer = String;
  PCHAR Current_pointer = String;

  PCHAR Result = NULL;
  PCHAR Buffer = NULL;

  INT Count;

  DosAllocMem( (PPVOID) &Result, strlen, PAG_COMMIT | PAG_READ | PAG_WRITE );
  if( Result == NULL ) return;

  DosAllocMem( (PPVOID) &Buffer, strlen, PAG_COMMIT | PAG_READ | PAG_WRITE );
  if( Buffer == NULL ) return;

  for( Count = 0; Count < strlen; Count ++ ) { Result[ Count ] = 0; Buffer[ Count ] = 0; }

  while( Current_pointer != NULL )
   {
    Current_pointer = Strings_strfind( Key, Pointer ); if( Current_pointer == NULL ) break;

    Strings_strncpy( Buffer, Pointer, Current_pointer - Pointer );
    Strings_strcat( Result, Buffer ); Strings_strcat( Result, Replacement );

    Pointer = Current_pointer + Keylen;
   }
  Strings_strcat( Result, Pointer );

  Strings_strcpy( String, Result );

  DosFreeMem( Buffer ); Buffer = NULL;
  DosFreeMem( Result ); Result = NULL;
 }

 return;
}

// ��� ������ �� �㪢� �������묨 ���

// String - ��ப� ��� �८�ࠧ������.
VOID Strings_UpperCase( PCHAR String )
{
 if( String == NULL ) return;

 Strings_CaseTranslator( String, Strings_strlen( String ) );

 return;
}

// ��� ������ �� �㪢� ����묨 ���

// String - ��ப� ��� �८�ࠧ������.
VOID Strings_LowerCase( PCHAR String )
{
 if( String == NULL ) return;

 {
  INT strlen = Strings_strlen( String );

  INT Offset;
  for( Offset = 0; Offset < strlen; Offset ++ )
   {
    CHAR Character = 0; INT Count;
    for( Count = 1; Count <= 255; Count ++ )
     {
      Character = (CHAR) Count; Strings_CaseTranslator( &Character, 1 );

      if( Character == String[ Offset ] ) String[ Offset ] = (CHAR) Count;
     }
   }
 }

 return;
}

// ��� ������ ����� �㪢� ���������, ��⠫�� ����묨 ���

// String - ��ப� ��� �८�ࠧ������.
VOID Strings_MixedCase( PCHAR String )
{
 if( String == NULL ) return;

 {
  CHAR First_character[ 2 ] = { String[ 0 ], 0 };

  Strings_UpperCase( First_character ); String[ 0 ] = First_character[ 0 ];

  Strings_LowerCase( &String[ 1 ] );
 }

 return;
}

// ��� ������ �� ��ப� ������� �㪢� ���

// String - ��ப� ��� �८�ࠧ������, Bound_* - �� 㤠����.
VOID Strings_DeleteCharset( PCHAR String, INT Bound_1, INT Bound_2 )
{
 if( String == NULL ) return;
 if( Bound_1 < 0 || Bound_1 > 255 ) return;
 if( Bound_2 < 0 || Bound_2 > 255 ) return;

 {
  INT Count = 0;

  while( String[ Count ] != 0 )
   {
    if( String[ Count ] >= Bound_1 && String[ Count ] <= Bound_2 )
     {
      Strings_strcpy( &String[ Count ], &String[ Count + 1 ] );
      continue;
     }

    Count ++;
   }
 }

 return;
}

// ��� ������ �� ��ப� �� ���� ���

// String - ��ப� ��� �८�ࠧ������.
VOID Strings_DeleteNumbers( PCHAR String )
{
 if( String == NULL ) return;

 Strings_DeleteCharset( String, '0', '9' );

 return;
}


