// ��⮤� ��� ࠡ��� � ������ ��������.
#define ScanDialogWindow          Krnl_DlgBox_ScanDialogWindow
#define RestoreDialogFields       Krnl_DlgBox_RestoreDialogFields

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Krnl_DlgBox_Start( VOID )
{
 #ifdef Krnl_DlgBox
 bzero( &Krnl_DlgBox, sizeof( Krnl_DlgBox ) );
 #endif

 // ������.
 return;
}

