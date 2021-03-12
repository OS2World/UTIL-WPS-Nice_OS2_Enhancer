// Методы для получения имен файлов с настройками, заголовков для окон и других свойств расширителя.
#define GetSettingsFileName            EnhancerProperties_GetSettingsFileName

#define GetEnhancerWindowTitle         EnhancerProperties_GetEnhancerWindowTitle
#define GetLoaderWindowTitle           EnhancerProperties_GetLoaderWindowTitle

#define SetCommonEnhancerFont          EnhancerProperties_SetCommonEnhancerFont
#define SetCommonEnhancerColors        EnhancerProperties_SetCommonEnhancerColors

// ─── Метод для подключения класса ───

VOID EnhancerProperties_Start (VOID)
{
  #ifdef EnhancerProperties
  bzero (&EnhancerProperties, sizeof (EnhancerProperties));
  #endif

  // Возврат.
  return;
}

