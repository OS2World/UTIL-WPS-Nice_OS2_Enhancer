// Методы для распознавания предопределенных свойств окон.
#define FrameWidth               PMMetrics_FrameWidth

// ─── Метод для подключения класса ───

VOID PMMetrics_Start( VOID )
{
 #ifdef PMMetrics
 bzero( &PMMetrics, sizeof( PMMetrics ) );
 #endif

 // Возврат.
 return;
}
