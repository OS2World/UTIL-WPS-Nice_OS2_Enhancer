
// ─── Сообщает, было ли отключено выравнивание окон ───

BYTE Performer_ArrangerMustBeDisabled( VOID )
{
 // Если выравнивание окон было отключено - сообщаем об этом.
 if( Performer.RTSettings.Performer_disables_arranger ) return 1;

 // Возврат.
 return 0;
}
