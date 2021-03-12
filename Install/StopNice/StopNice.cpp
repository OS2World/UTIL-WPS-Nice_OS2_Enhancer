#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>
#include <StdLib.h>

#define INCLUDED_BY_SHELL

#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

#include "..\\..\\Nice-os2\\Shared\\SysState.h"
#pragma pack(4)

#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment.cpp"

#include "..\\..\\Nice-os2\\Shared\\Repository.h"
#include "..\\..\\Nice-os2\\Shared\\Repository\\Repository_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Repository\\Repository_base.cpp"
#include "..\\..\\Nice-os2\\Shared\\Repository\\Repository_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Repository.cpp"

// ��� �ਫ������ ���

INT Main (INT argc, CHAR *argv[])
{
  // ��।��塞 �ਫ������ � ��⥬�.
  HAB Application = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Application == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    return 0;
  }

  // ������� ��।� ᮮ�饭��.
  HMQ Message_queue = WinCreateMsgQueue (Application, 0);

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Message_queue == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    WinTerminate (Application); return 0;
  }

  // ������ ᯨ᮪ �ਫ������.
  Repository_Start ();

  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = WinQueryDesktopWindow (Application, NULLHANDLE);

  {
    // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
    HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
    while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
    {
      // �᫨ �� ���� ����⥫� - ����뢠�� ���.
      if (IsFrameWindow (Window))
       if (WindowIsCreatedBy (APP_NICE_ENHANCER, Window) || WindowIsCreatedBy (APP_NICE_ENHANCER_SHELL, Window))
        WinPostMsg (Window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, 0);
    }
    WinEndEnumWindows (Enumeration);
  }

  // ����뢠�� ��।� ᮮ�饭��.
  WinDestroyMsgQueue (Message_queue);

  // ��室.
  WinTerminate (Application); return 0;
}
