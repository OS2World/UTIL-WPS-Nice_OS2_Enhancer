// Методы для распознавания окон.
#define WindowIsPresent WindowTypes_WindowIsPresent

#define WindowType WindowTypes_WindowType
#define FrameType  WindowTypes_FrameType

// ─── Метод для подключения класса ───

VOID WindowTypes_Start( VOID )
{
 #ifdef WindowTypes
 bzero( &WindowTypes, sizeof( WindowTypes ) );
 #endif

 // Возврат.
 return;
}

