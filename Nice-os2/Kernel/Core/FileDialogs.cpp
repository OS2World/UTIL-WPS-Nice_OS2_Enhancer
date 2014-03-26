// Методы для работы с окнами открытия и сохранения файлов.
#define FindFieldInFileDialog   FileDialogs_FindFieldInFileDialog

// ─── Метод для подключения класса ───

VOID FileDialogs_Start( VOID )
{
 #ifdef FileDialogs
 bzero( &FileDialogs, sizeof( FileDialogs ) );
 #endif

 // Возврат.
 return;
}

