
// Внутренние переменные.
typedef struct _STRINGS
{
  // Работа со строками.
  typedef struct _INRSTS
  {
    // Страна, в которой работает приложение.
    COUNTRYCODE Country;

    // Карта для перевода.
    CHAR Case_map[255];
  }
  INRSTS; INRSTS Inner_settings;
}
STRINGS; typedef STRINGS* PSTRINGS;

// Переменные должны быть расположены в разделяемой области памяти.
STRINGS Strings_static_data; PSTRINGS Strings = &Strings_static_data;
