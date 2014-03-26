// Методы для рисования.
#define ForceColorPaletteToRGB                  GpiExt_ForceColorPaletteToRGB

// ─── Метод для подключения класса ───

VOID GpiExt_Start( VOID )
{
 #ifdef GpiExt
 bzero( &GpiExt, sizeof( GpiExt ) );
 #endif

 // Возврат.
 return;
}

