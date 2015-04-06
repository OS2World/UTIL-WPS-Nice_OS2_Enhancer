// Методы для проверки настроек PM и записи отчета в окно "Log".
#define CheckPMSettingsAndWriteLog          SysCheck_CheckPMSettingsAndWriteLog
#define CheckPrioritySettingsAndWriteLog    SysCheck_CheckPrioritySettingsAndWriteLog
#define AddCompletiveLogMessage             SysCheck_AddCompletiveLogMessage

// ─── Метод для подключения класса ───

VOID SysCheck_Start( VOID )
{
 #ifdef SysCheck
 bzero( &SysCheck, sizeof( SysCheck ) );
 #endif

 // Возврат.
 return;
}
