// Методы для распознавания окружения.
#define ShellIsFileBar           Krnl_Environment_ShellIsFileBar
#define ShellIsWPS               Krnl_Environment_ShellIsWPS

#define QueryCodePage            Krnl_Environment_QueryCodePage

#define SystemIsLocked           Krnl_Environment_SystemIsLocked
#define LockupFrame              Krnl_Environment_LockupFrame
#define ScreenSaverCanBeClosed   Krnl_Environment_ScreenSaverCanBeClosed

#define StartupCmdIsPresent      Krnl_Environment_StartupCmdIsPresent

// ─── Метод для подключения класса ───

VOID Krnl_Environment_Start( VOID )
{
 #ifdef Krnl_Environment
 bzero( &Krnl_Environment, sizeof( Krnl_Environment ) );
 #endif

 // Возврат.
 return;
}
