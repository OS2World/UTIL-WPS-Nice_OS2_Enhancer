
// ─── Сообщение ───

// String - строка, которую надо показать.
VOID Krnl_MessageBox_MessageBox( PCHAR String )
{
 // Если вызвана заставка - возврат.
 if( SystemIsLocked() ) return;

 // Показываем строку.
 CHAR Title[ SIZE_OF_TITLE ] = ""; GetEnhancerWindowTitle( Title );
 WinMessageBox( QueryDesktopWindow(), QueryDesktopWindow(), String, Title, NULLHANDLE, NULLHANDLE );

 // Возврат.
 return;
}
