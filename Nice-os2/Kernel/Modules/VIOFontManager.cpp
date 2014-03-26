// Методы для изменения шрифтов в текстовых окнах.
#define VIOFontMustBeChanged          VIOFontManager_VIOFontMustBeChanged

#define OpenVIOFontMetricsDialog      VIOFontManager_OpenVIOFontMetricsDialog
#define SubmitVIOFontMetricsDialog    VIOFontManager_SubmitVIOFontMetricsDialog

#define FontsCanBeChangedInVIOWindows VIOFontManager_FontsCanBeChangedInVIOWindows

// ─── Метод для подключения класса ───

VOID VIOFontManager_Start( VOID )
{
 #ifdef VIOFontManager
 bzero( &VIOFontManager, sizeof( VIOFontManager ) );
 #endif

 // Задаем указатели в списке составляющих расширителя.
 MODULE Item; PresetModuleItem( &Item );

 Item.TuneModule = VIOFontManager_Tune;

 RememberModuleItem( Enhancer.Modules.VIOFontManager, &Item );

 // Возврат.
 return;
}

