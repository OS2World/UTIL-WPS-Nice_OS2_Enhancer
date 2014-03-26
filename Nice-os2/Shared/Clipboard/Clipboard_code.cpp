
// ��� ���������� ��ப� � Clipboard ���

// Application - �ਫ������, String - ��ப�, Byte_* - ����� � �� �ଠ�.
VOID Clipboard_PutStringIntoClipboard( HAB Application, PCHAR String, PBYTE Byte_array = NULL, ULONG Byte_array_length = 0, PCHAR Byte_array_format = NULL )
{
 // �᫨ ��ப� ��祣� �� ᮤ�ন� - ������.
 if( String == NULL || String[ 0 ] == 0 ) return;

 // ���뢠�� Clipboard.
 WinOpenClipbrd( Application );

 // ��頥� Clipboard.
 WinEmptyClipbrd( Application );

 // ��७�ᨬ ��ப� � Clipboard.
 // �㭪�� "WinSetClipbrdData()" ࠡ�⠥� ⮫쪮 � �뤠������ SHAREMEM,
 // � ������� ����� � ����묨 ��� Clipboard ���� ����� ࠧ ᮧ������ ������.
 if( String )
  {
   PVOID Data = NULL; INT Data_length = strlen( String ) + 2;
   DosAllocSharedMem( (PPVOID) &Data, NULL, Data_length, PAG_ALLOCATE | OBJ_GIVEABLE );
   bzero( Data, Data_length );

   strcpy( (PCHAR) Data, String );
   WinSetClipbrdData( Application, (ULONG) Data, CF_TEXT, CFI_POINTER );

   DosFreeMem( Data ); Data = NULL;
  }

 if( Byte_array && Byte_array_length )
  {
   PVOID Data = NULL; INT Data_length = Byte_array_length + 2;
   DosAllocSharedMem( (PPVOID) &Data, NULL, Data_length, PAG_ALLOCATE | OBJ_GIVEABLE );
   bzero( Data, Data_length );

   ATOM Format = WinAddAtom( WinQuerySystemAtomTable(), Byte_array_format );

   memcpy( (PCHAR) Data, Byte_array, Byte_array_length );
   WinSetClipbrdData( Application, (ULONG) Data, Format, CFI_POINTER );

   WinDeleteAtom( WinQuerySystemAtomTable(), Format );

   DosFreeMem( Data ); Data = NULL;
  }

 // ����뢠�� Clipboard.
 WinCloseClipbrd( Application );

 // ������.
 return;
}

// ��� �롨ࠥ� ��ப� �� Clipboard ���

// Application - �ਫ������, String - ��ப�, String_length - �� �����, Byte_* - ����� � �� �ଠ�.
VOID Clipboard_GetStringFromClipboard( HAB Application, PCHAR String, INT String_length, PBYTE Byte_array = NULL, ULONG Byte_array_length = 0, PCHAR Byte_array_format = NULL )
{
 // ���뢠�� Clipboard.
 WinOpenClipbrd( Application );

 // ����ࠥ� ��ப� �� Clipboard.
 if( String && String_length )
  {
   PCHAR Pointer = (PCHAR) WinQueryClipbrdData( Application, CF_TEXT );
   if( Pointer != 0 ) strncpy( String, Pointer, String_length - 1 );
  }

 if( Byte_array && Byte_array_length )
  {
   ATOM Format = WinAddAtom( WinQuerySystemAtomTable(), Byte_array_format );

   PCHAR Pointer = (PCHAR) WinQueryClipbrdData( Application, Format );
   if( Pointer != 0 ) memcpy( Byte_array, Pointer, Byte_array_length );

   WinDeleteAtom( WinQuerySystemAtomTable(), Format );
  }

 // ����뢠�� Clipboard.
 WinCloseClipbrd( Application );

 // ������.
 return;
}
