#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>
#include <Stdio.h>

#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

// ��� ��뢠�� ��������� ���

VOID Main (VOID)
{
  // ********************************************************** //

  // ����� ᮧ���� �ਫ������, *.dll ��� *.obj.
  CHAR Target[] = "/Ge+ /Ss+";    // �ਫ������.
  // CHAR Target[] = "/C /Ss+";   // Object.
  // CHAR Target[] = "/Ge- /Ss+"; // Library.

  // ������ - Pentium.
  CHAR Processor[] = "/G5 /Gf+ /Gi+";

  // ��⨬����� - �� ᪮���.
  CHAR Optimization[] = "/Gs+ /O+ /Oi+";

  // ����� 䠩���.
  CHAR CPP_Name[] = "StopNice.cpp";
  CHAR DEF_Name[] = "StopNice.def";
  CHAR LIB_Name[] = "..\\..\\Nice-os2\\Shared\\DosCalls\\Doscalls.lib";

  CHAR OBJ_Name[] = "StopNice.obj";
  CHAR RC_Name[]  = "StopNice.rc";
  CHAR TGT_Name[] = "StopNice.exe ";
  CHAR RES_Name[] = "StopNice.res";

  // ********************************************************** //

  // ������ ��ࠬ����.
  CHAR Compiler[] = "Icc.exe"; CHAR Parameters[255] = "";
  strcpy (Parameters, Compiler);     strcat (Parameters, "|");
  strcat (Parameters, Target);       strcat (Parameters, " ");
  strcat (Parameters, CPP_Name);     strcat (Parameters, " ");
  strcat (Parameters, DEF_Name);     strcat (Parameters, " ");
  strcat (Parameters, LIB_Name);     strcat (Parameters, " ");
  strcat (Parameters, Processor);    strcat (Parameters, " ");
  strcat (Parameters, Optimization);
  strchg (Parameters, '|', 0x00);

  // ��뢠�� IBM VA C++.
  CHAR Error_string[1]; RESULTCODES Return_codes;
  DosResetBuffer (-1); DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, Parameters, NULL, &Return_codes, Compiler);

  // ������ ��ࠬ���� ��� Resource Compiler.
  // RC.exe - 16-ࠧ�來�� �ਫ������, � ��� ���� �맢��� ��� "Cmd /C RC.exe".
  CHAR RC_starter[] = "Cmd.exe"; Parameters[0] = 0;
  strcpy (Parameters, RC_starter);   strcat (Parameters, "|");
  strcat (Parameters, "/C RC.exe");  strcat (Parameters, " ");
  strcat (Parameters, RC_Name);      strcat (Parameters, " ");
  strcat (Parameters, TGT_Name);
  strchg (Parameters, '|', 0x00);

  // ��뢠�� Resource Compiler.
  DosResetBuffer (-1); DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, Parameters, NULL, &Return_codes, RC_starter);

  // ����塞 �६���� 䠩��.
  DosForceDelete (OBJ_Name); DosForceDelete (RES_Name);

  // ���.
  WinAlarm (HWND_DESKTOP, WA_NOTE);

  // ��室.
  return;
}

