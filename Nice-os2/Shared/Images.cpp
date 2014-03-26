// Методы для работы с изображениями.
#define CreatePresentationSpace Images_CreatePresentationSpace
#define CreateBitmap            Images_CreateBitmap
#define LoadBitmap              Images_LoadBitmap

// ─── Метод для подключения класса ───

VOID Images_Start( VOID )
{
 #ifdef Images
 bzero( &Images, sizeof( Images ) );
 #endif

 // Возврат.
 return;
}

