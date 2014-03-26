
// ─── Сообщает, включена ли настройка для окон VIO ───

BYTE VIOFontManager_FontsCanBeChangedInVIOWindows( VOID )
{
 // Проверяем настройки.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) return 1;

 // Возврат.
 return 0;
}
