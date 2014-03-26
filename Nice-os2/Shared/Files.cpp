// Методы для работы с файлами.
#define FileExists                Files_FileExists
#define GetCurrentPath            Files_GetCurrentPath
#define OpenIniProfile            Files_OpenIniProfile

#define QueryDriveLabel           Files_QueryDriveLabel
#define DriveLabelHasSpecialChars Files_DriveLabelHasSpecialChars
#define DriveIsAvailable          Files_DriveIsAvailable
#define FindRAMDrive              Files_FindRAMDrive

#define DriveNumberFromPath       Files_DriveNumberFromPath
#define FindNameInPath            Files_FindNameInPath
#define CutNameInPath             Files_CutNameInPath
#define CutLastSlash              Files_CutLastSlash

#define Execute                   Files_Execute

// ─── Метод для подключения класса ───

VOID Files_Start( VOID )
{
 #ifdef Files
 bzero( &Files, sizeof( Files ) );
 #endif

 // Возврат.
 return;
}
