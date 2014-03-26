
// ─── Сообщает, надо ли выравнивать текстовые окна ───

BYTE Arranger_ArrangeVIOWindows( VOID )
{
 // Проверяем, надо ли выравнивать текстовые окна.
 if( Arranger.Settings.Arrange_VIO_windows ) return 1;

 // Возврат.
 return 0;
}
