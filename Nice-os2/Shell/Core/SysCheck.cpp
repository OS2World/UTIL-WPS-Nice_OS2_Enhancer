// ��⮤� ��� �஢�ન ����஥� PM � ����� ���� � ���� "Log".
#define CheckPMSettingsAndWriteLog          SysCheck_CheckPMSettingsAndWriteLog

// ��� ��⮤ ��� ������祭�� ����� ���

VOID SysCheck_Start( VOID )
{
 #ifdef SysCheck
 bzero( &SysCheck, sizeof( SysCheck ) );
 #endif

 // ������.
 return;
}
