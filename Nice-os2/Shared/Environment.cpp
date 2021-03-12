// Методы для распознавания окружения.
#define SMPSystem                   Environment_SMPSystem

#define ActiveApplication           Environment_ActiveApplication
#define QueryDesktopWindow          Environment_QueryDesktopWindow

#define QuerySystemCodePage         Environment_QuerySystemCodePage
#define DBCSSupportIsEnabled        Environment_DBCSSupportIsEnabled

#define QueryTempDirectory          Environment_QueryTempDirectory

// ─── Метод для подключения класса ───

VOID Environment_Start (VOID)
{
  #ifdef Environment
  bzero (&Environment, sizeof (Environment));
  #endif

  // Возврат.
  return;
}
