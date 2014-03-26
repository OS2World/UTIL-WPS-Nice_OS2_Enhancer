
// ─── Сообщает, включена ли настройка для окон VIO ───

BYTE Clipper_CopyPasteKeysCanBeUsedInVIOWindows( VOID )
{
 // Проверяем настройки.
 if( Clipper.Settings.CopyPaste_keys_in_VIO ) return 1;

 // Возврат.
 return 0;
}
