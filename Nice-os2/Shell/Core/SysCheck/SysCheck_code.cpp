
// ─── Проверяет настройки PM и оставляет запись в окне "Log" ───

VOID SysCheck_CheckPMSettingsAndWriteLog( VOID )
{
 // Проверяем настройку "Restart Objects" оболочки WPS.
 {
  BYTE RestartObjects_is_correct = 1;

  PCHAR RestartObjects_ptr = NULL; DosScanEnv( "RESTARTOBJECTS", (PPCSZ) &RestartObjects_ptr );
  if( RestartObjects_ptr == NULL ) RestartObjects_is_correct = 0;
  else if( !strfind( "STARTUPFOLDERSONLY", RestartObjects_ptr ) ) RestartObjects_is_correct = 0;

  if( !RestartObjects_is_correct )
   {
    if( Enhancer.Code_page == RUSSIAN ) PrintLogMessage( StrConst_RU_Pages_Log_RestartObjects );
    else PrintLogMessage( StrConst_EN_Pages_Log_RestartObjects );
   }
 }

 // Добавляем сообщение о том, что это необязательные требования.
 if( !LogIsEmpty() )
  {
   if( Enhancer.Code_page == RUSSIAN ) PrintLogMessage( StrConst_RU_Pages_Log_Note );
   else PrintLogMessage( StrConst_RU_Pages_Log_Note );
  }

 // Возврат.
 return;
}
