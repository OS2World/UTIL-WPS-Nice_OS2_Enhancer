
// ��� ����饭�� ���

// String - ��ப�, ������ ���� ��������.
VOID Krnl_MessageBox_MessageBox( PCHAR String )
{
 // �᫨ �맢��� ���⠢�� - ������.
 if( SystemIsLocked() ) return;

 // �����뢠�� ��ப�.
 CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
 WinMessageBox( QueryDesktopWindow(), QueryDesktopWindow(), String, Title, NULLHANDLE, NULLHANDLE );

 // ������.
 return;
}
