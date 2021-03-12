// Методы для изменения цветов и настроек оболочки OS/2.
#define ChangeSystemColors    SysValues_ChangeSystemColors
#define RestoreSystemColors   SysValues_RestoreSystemColors

#define ChangeSystemValues    SysValues_ChangeSystemValues
#define RestoreSystemValues   SysValues_RestoreSystemValues

// ─── Метод для подключения класса ───

VOID SysValues_Start (VOID)
{
  #ifdef SysValues
  bzero (&SysValues, sizeof (SysValues));
  #endif

  // Возврат.
  return;
}
