
// ─── Запоминает строку в Clipboard ───

// Application - приложение, String - строка, Byte_* - данные и их формат.
VOID Clipboard_PutStringIntoClipboard( HAB Application, PCHAR String, PBYTE Byte_array = NULL, ULONG Byte_array_length = 0, PCHAR Byte_array_format = NULL )
{
 // Если строка ничего не содержит - возврат.
 if( String == NULL || String[ 0 ] == 0 ) return;

 // Открываем Clipboard.
 WinOpenClipbrd( Application );

 // Очищаем Clipboard.
 WinEmptyClipbrd( Application );

 // Переносим строку в Clipboard.
 // Функция "WinSetClipbrdData()" работает только с выдаваемой SHAREMEM,
 // и область памяти с данными для Clipboard надо каждый раз создавать заново.
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

 // Закрываем Clipboard.
 WinCloseClipbrd( Application );

 // Возврат.
 return;
}

// ─── Выбирает строку из Clipboard ───

// Application - приложение, String - строка, String_length - ее длина, Byte_* - данные и их формат.
VOID Clipboard_GetStringFromClipboard( HAB Application, PCHAR String, INT String_length, PBYTE Byte_array = NULL, ULONG Byte_array_length = 0, PCHAR Byte_array_format = NULL )
{
 // Открываем Clipboard.
 WinOpenClipbrd( Application );

 // Забираем строку из Clipboard.
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

 // Закрываем Clipboard.
 WinCloseClipbrd( Application );

 // Возврат.
 return;
}
