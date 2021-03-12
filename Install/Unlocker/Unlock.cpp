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

VOID Main (INT argc, CHAR *argv[])
{
  // Если не задано имя файла - выход.
  if (argc < 2) DosExit (EXIT_PROCESS, 0);

  // Выполняем Unlock.
  PCHAR File_name = argv[1];
  DosReplaceModule (File_name, NULL, NULL);

  // Выход.
  DosExit (EXIT_PROCESS, 0);
}
