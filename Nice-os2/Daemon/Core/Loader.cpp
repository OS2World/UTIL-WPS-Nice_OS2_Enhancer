// Методы для загрузки расширителя.
#define NiceLoadEnhancer           Loader_NiceLoadEnhancer
#define NiceRunEnhancer            Loader_NiceRunEnhancer
#define NiceReleaseEnhancer        Loader_NiceReleaseEnhancer

#define NiceReadSettings           Loader_NiceReadSettings
#define NiceReadRepository         Loader_NiceReadRepository

#define NiceScanLogonDialog        Loader_NiceScanLogonDialog
#define NiceScanIncompleteDialog   Loader_NiceScanIncompleteDialog
#define NiceScanMessageDialog      Loader_NiceScanMessageDialog

// ─── Метод для подключения класса ───

VOID Loader_Start( VOID )
{
 #ifdef Loader
 bzero( &Loader, sizeof( Loader ) );
 #endif

 // Возврат.
 return;
}
