// Методы для работы со справочниками.
#define Help                  HelpPages_Help 
#define CloseExistingHelpPage HelpPages_CloseExistingHelpPage

// ─── Метод для подключения класса ───

VOID HelpPages_Start( VOID )
{
 #ifdef HelpPages
 bzero( &HelpPages, sizeof( HelpPages ) );
 #endif

 // Возврат.
 return;
}
