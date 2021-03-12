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

// ��� �ਫ������ ���

VOID Main (INT argc, CHAR *argv[])
{
  // �᫨ �� ������ ��� 䠩�� - ��室.
  if (argc < 2) DosExit (EXIT_PROCESS, 0);

  // �믮��塞 Unlock.
  PCHAR File_name = argv[1];
  DosReplaceModule (File_name, NULL, NULL);

  // ��室.
  DosExit (EXIT_PROCESS, 0);
}
