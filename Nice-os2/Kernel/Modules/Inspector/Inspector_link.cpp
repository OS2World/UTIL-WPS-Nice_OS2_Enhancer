
// ��� ����頥�, ���� �� �஢����� ᯨ᮪ �ਫ������ ���

BYTE Inspector_RepositoryCheckIsRequired( VOID )
{
 // �஢��塞 ����ன��.
 if( Inspector.Settings.Check_Repository ) return 1;

 // ������.
 return 0;
}

