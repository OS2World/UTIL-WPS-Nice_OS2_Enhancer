#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>
#include <Stdio.h>

#include "..\\Shared\\General.h"
#pragma pack(4)

#include "..\\Shared\\Strings.h"
#include "..\\Shared\\Strings\\Strings_data.cpp"
#include "..\\Shared\\Strings\\Strings_code.cpp"
#include "..\\Shared\\Strings.cpp"

// ─── Вызывает компилятор ───

VOID main( VOID )
{
 // ********************************************************** //

 // Можно создать приложение, *.dll или *.obj.
 CHAR Target[] = "/Ge+ /Ss+";    // Приложение.
 // CHAR Target[] = "/C /Ss+";   // Object.
 // CHAR Target[] = "/Ge- /Ss+"; // Library.

 // Процессор - Pentium.
 CHAR Processor[] = "/G5 /Gf+ /Gi+";

 // Оптимизация - по скорости.
 CHAR Optimization[] = "/Gs+ /O+ /Oi+";

 // Размер стека - как и у всех потоков.
 CHAR Stack_size[] = "/B\"/ST:32768\"";

 // Имена файлов.
 CHAR CPP_Name[] = "Inspectr.cpp";
 CHAR DEF_Name[] = "Inspectr.def";
 CHAR LIB_Name[] = "..\\Shared\\DosCalls\\Doscalls.lib";

 CHAR RC_Name[] =  "Resources\\Resources.rc";
 CHAR RES_Name[] = "Resources\\Resources.res";

 CHAR OBJ_Name[] = "Inspectr.obj";
 CHAR TGT_Name[] = "Inspectr.exe ";

 // ********************************************************** //

 // Задаем параметры.
 CHAR Compiler[] = "Icc.exe"; CHAR Parameters[ 255 ] = "";
 strcpy( Parameters, Compiler );     strcat( Parameters, "|" );
 strcat( Parameters, Target );       strcat( Parameters, " " );
 strcat( Parameters, CPP_Name );     strcat( Parameters, " " );
 strcat( Parameters, DEF_Name );     strcat( Parameters, " " );
 strcat( Parameters, LIB_Name );     strcat( Parameters, " " );
 strcat( Parameters, Processor );    strcat( Parameters, " " );
 strcat( Parameters, Optimization ); strcat( Parameters, " " );
 strcat( Parameters, Stack_size );
 strchg( Parameters, '|', 0x00 );

 // Удаляем файлы, которые требуется получить.
 DosForceDelete( TGT_Name );

 // Вызываем IBM VA C++.
 CHAR Error_string[ 1 ]; RESULTCODES Return_codes;
 DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_SYNC, Parameters, NULL, &Return_codes, Compiler );

 // Задаем параметры для Resource Compiler.
 // RC.exe - 16-разрядное приложение, и его надо вызвать как "Cmd /C RC.exe".
 CHAR RC_starter[] = "Cmd.exe"; Parameters[ 0 ] = 0;
 strcpy( Parameters, RC_starter );   strcat( Parameters, "|" );
 strcat( Parameters, "/C RC.exe" );  strcat( Parameters, " " );
 strcat( Parameters, RC_Name );      strcat( Parameters, " " );
 strcat( Parameters, TGT_Name );
 strchg( Parameters, '|', 0x00 );

 // Вызываем Resource Compiler.
 DosResetBuffer( -1 ); DosExecPgm( Error_string, sizeof( Error_string ), EXEC_SYNC, Parameters, NULL, &Return_codes, RC_starter );

 // Удаляем временные файлы.
 DosForceDelete( OBJ_Name ); DosForceDelete( RES_Name );

 // Звук.
 WinAlarm( HWND_DESKTOP, WA_NOTE );

 // Выход.
 return;
}

