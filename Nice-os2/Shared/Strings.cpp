// Методы для работы со строками.
#define strlen    Strings_strlen
#define strncpy   Strings_strncpy
#define strcpy    Strings_strcpy
#define strcat    Strings_strcat
#define strc      Strings_strc
#define stric     Strings_stric

#define memset    Strings_memset
#define bzero     Strings_bzero
#define memcpy    Strings_memcpy

#define strstr    Strings_strstr
#define stristr   Strings_stristr
#define strchg    Strings_strchg
#define strschg   Strings_strschg

#define UpperCase Strings_UpperCase
#define LowerCase Strings_LowerCase
#define MixedCase Strings_MixedCase

#define DeleteNumbers Strings_DeleteNumbers

// ─── Метод для подключения класса ───

VOID Strings_Start (VOID)
{
  #ifdef Strings
  bzero (&Strings, sizeof (Strings));
  #endif

  // Возврат.
  return;
}

