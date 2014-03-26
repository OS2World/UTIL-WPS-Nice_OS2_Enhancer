// Методы для распознавания окружения.
#define HasShellWindowControls   Workplace_HasShellWindowControls
#define HasShellPlacement        Workplace_HasShellPlacement
#define QueryShellWindow         Workplace_QueryShellWindow

#define ShellIsAvailable         Workplace_ShellIsAvailable
#define GetDetectedShellWindow   Workplace_GetDetectedShellWindow
#define RememberShellWindow      Workplace_RememberShellWindow

// ─── Метод для подключения класса ───

VOID Workplace_Start( VOID )
{
 #ifdef Workplace
 bzero( &Workplace, sizeof( Workplace ) );
 #endif

 // Возврат.
 return;
}
