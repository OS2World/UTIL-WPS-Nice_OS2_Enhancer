
// ��� �����頥� �६� ��᫥����� ������ �� �।��� ������ ��� ���

ULONG MouseMapper_WMMBDownTime( VOID )
{
 // �����頥� �६�.
 return MouseMapper.RTSettings.WM_MB_Down_time;
}

// ��� ����뢠�� �६� ��᫥����� ������ �� �।��� ������ ��� ���

VOID MouseMapper_DiscardWMMBDownTime( VOID )
{
 // ����뢠�� ���祭��.
 MouseMapper.RTSettings.WM_MB_Down_time = 0;

 // ������.
 return;
}
