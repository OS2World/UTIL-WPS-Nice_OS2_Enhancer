// Окно настроек.
typedef struct _PRTYVARPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG Calculate_ID;
    ULONG VIO_ID;
    ULONG lSwitcher_ID;
  }
  INRSTS; INRSTS Settings;
}
PRTYVARPAGE;

PRTYVARPAGE Priority_Variable;
