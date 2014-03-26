// Методы для работы со строками.
#define strlen    Strings_strlen
#define strncpy   Strings_strncpy
#define strcpy    Strings_strcpy
#define strcat    Strings_strcat
#define strcmp    Strings_strcmp
#define stricmpe  Strings_stricmpe

#define memset    Strings_memset
#define bzero     Strings_bzero
#define memcpy    Strings_memcpy

#define strfind   Strings_strfind
#define strifind  Strings_strifind
#define strchg    Strings_strchg
#define strschg   Strings_strschg

#define UpperCase Strings_UpperCase
#define LowerCase Strings_LowerCase
#define MixedCase Strings_MixedCase

#define DeleteNumbers Strings_DeleteNumbers

// ─── Метод для подключения класса ───

VOID Strings_Start( VOID )
{
 #ifdef Strings
 bzero( &Strings, sizeof( Strings ) );
 #endif

 // Возврат.
 return;
}

