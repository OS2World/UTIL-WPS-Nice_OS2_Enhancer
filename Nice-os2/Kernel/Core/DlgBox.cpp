// Методы для работы с окнами диалогов.
#define ScanDialogWindow          Krnl_DlgBox_ScanDialogWindow
#define RestoreDialogFields       Krnl_DlgBox_RestoreDialogFields

// ─── Метод для подключения класса ───

VOID Krnl_DlgBox_Start( VOID )
{
 #ifdef Krnl_DlgBox
 bzero( &Krnl_DlgBox, sizeof( Krnl_DlgBox ) );
 #endif

 // Возврат.
 return;
}

