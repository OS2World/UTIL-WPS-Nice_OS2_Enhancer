// ��⮤� ��� �஢�ન ����஥� PM � ����� ���� � ���� "Log".
#define CheckPMSettingsAndWriteLog          SysCheck_CheckPMSettingsAndWriteLog
#define CheckPrioritySettingsAndWriteLog    SysCheck_CheckPrioritySettingsAndWriteLog
#define AddCompletiveLogMessage             SysCheck_AddCompletiveLogMessage

// ��� ��⮤ ��� ������祭�� ����� ���

VOID SysCheck_Start( VOID )
{
 #ifdef SysCheck
 bzero( &SysCheck, sizeof( SysCheck ) );
 #endif

 // ������.
 return;
}
