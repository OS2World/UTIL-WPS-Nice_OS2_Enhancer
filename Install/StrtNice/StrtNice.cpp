#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>
#include <StdLib.h>

#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// ─── Приложение ───

INT main( VOID )
{
 // Определяем приложение в системе.
 HAB Application = WinInitialize( 0 );

 // Если это сделать не удалось - выход.
 if( Application == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   return 0;
  }

 // Создаем очередь сообщений.
 HMQ Message_queue = WinCreateMsgQueue( Application, 0 );

 // Если очередь создать не удалось - выход.
 if( Message_queue == NULLHANDLE )
  {
   // Звук - ошибка.
   WinAlarm( HWND_DESKTOP, WA_ERROR );
   // Выход.
   WinTerminate( Application ); return 0;
  }

 // Узнаем рабочий каталог.
 CHAR Current_directory[ SIZE_OF_PATH ] = "";

 ULONG Current_drive = 0; ULONG Drive_map = 0; ULONG Length = SIZE_OF_PATH - 3;
 DosQueryCurrentDisk( &Current_drive, &Drive_map );
 Current_directory[ 0 ] = (CHAR) Current_drive + 64;
 Current_directory[ 1 ] = ':';
 Current_directory[ 2 ] = '\\';
 DosQueryCurrentDir( 0, &Current_directory[ 3 ], &Length );

 // Находим файл расширителя и запускаем его.
 for( INT Count = 0; Count < 2; Count ++ )
  {
   // Пробуем найти файл.
   CHAR Path[ SIZE_OF_PATH ] = ""; strcpy( Path, Current_directory ); CutNameInPath( Path );

   if( Count == 0 ) strcat( Path, "\\Enhancer" );
   if( Count == 1 ) strcat( Path, "\\Nice\\Enhancer" );

   CHAR Exe_file[ SIZE_OF_PATH ] = ""; strcpy( Exe_file, Path ); strcat( Exe_file, "\\" );
   CHAR Exe_name[] = "Nice-os2.exe"; strcat( Exe_file, Exe_name );

   // Если файл найден - запускаем расширитель.
   if( FileExists( Exe_file ) )
    {
     CHAR Parameters[ SIZE_OF_PATH ] = "";
     strcpy( Parameters, Exe_name );
     strcat( Parameters, "|" );
     strcat( Parameters, "launcher" );
     strchg( Parameters, '|', 0x00 );

     DosSetDefaultDisk( DriveNumberFromPath( Path ) ); DosSetCurrentDir( Path );
     CHAR Error_string[ 1 ] = ""; RESULTCODES Return_codes;
     DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_ASYNC, Parameters, NULL, &Return_codes, Exe_file );
    }
  }

 // Сбрасываем очередь сообщений.
 WinDestroyMsgQueue( Message_queue );

 // Выход.
 WinTerminate( Application ); return 0;
}
