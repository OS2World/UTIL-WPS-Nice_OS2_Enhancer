// Методы для работы с окнами.
#define WindowIsActive                   WindowManagement_WindowIsActive

#define WindowIsOutOfTheScreen           WindowManagement_WindowIsOutOfTheScreen
#define PermissionForSwitching           WindowManagement_PermissionForSwitching
#define FrameWindowIsAccessible          WindowManagement_FrameWindowIsAccessible

#define MoveWindowAbove                  WindowManagement_MoveWindowAbove
#define HideWindowAway                   WindowManagement_HideWindowAway

#define WindowInCenter                   WindowManagement_WindowInCenter
#define ActivateWindowInCenter           WindowManagement_ActivateWindowInCenter

// ─── Метод для подключения класса ───

VOID WindowManagement_Start( VOID )
{
 #ifdef WindowManagement
 bzero( &WindowManagement, sizeof( WindowManagement ) );
 #endif

 // Возврат.
 return;
}

