// ����ﭭ� ����稭�.
#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

// �맮�� C/C++.
#include "..\\..\\Nice-os2\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\StdLib.cpp"

// ����� � ��ப���.
#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

// ����� � 䠩����.
#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// ��ᯮ������� ����.
#include "..\\..\\Nice-os2\\Shared\\WindowTree.h"
#include "..\\..\\Nice-os2\\Shared\\WindowTree\\WindowTree_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\WindowTree.cpp"

#include "..\\..\\Nice-os2\\Shared\\Layout.h"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_list.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout.cpp"

// ��६���� �।�.
#define INCLUDED_BY_SHELL

#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment.cpp"

#include "..\\..\\Nice-os2\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\EnhancerProperties.cpp"

// ����� �ਫ������.
typedef struct _INSTALLER
{
  // �ਫ������.
  HAB Application;

  // ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
  ULONG Code_page;

  // ���� ࠬ��.
  HWND Frame_window;
  CHAR Frame_window_title[SIZE_OF_TITLE];
  // ���� ࠡ�祩 ������.
  HWND Client_window;
}
INSTALLER; INSTALLER Installer;

// ��ப� � ����ࠦ����.
#include "Resources\\Resources.h"
#include "Resources\\StrConst.h"

// ����७��� ᮮ�饭��.
#define MY_CREATE          (WM_USER +  1)

#define MY_APPLY_LAYOUT    (WM_USER + 10)
#define MY_ENABLE_BUTTONS  (WM_USER + 20)

// ����⢨�.
#define NIA_INSTALL 1
#define NIA_REMOVE  0

// �㭪樨 ��� ����᪠ ��⮪�� �ਫ������.
#include "Threads\\InstallerThread.h"

// ���� �ਫ������.
#include "Pages\\Controls.h"

#include "Pages\\ClientWindow\\ClientWindow_data.cpp"
#include "Pages\\ClientWindow\\ClientWindow_open.cpp"
#include "Pages\\ClientWindow\\ClientWindow_page.cpp"
#include "Pages\\ClientWindow.cpp"

// ��⮪� �ਫ������.
#include "Threads\\InstallerThread.c"

// ��� �ਫ������ ���

INT Main (INT argc, PCHAR argv[])
{
  // ����뢠�� ᢮��⢠ �ਫ������.
  bzero (&Installer, sizeof (INSTALLER));

  // ��।��塞 �ਫ������ � ��⥬�.
  Installer.Application = WinInitialize (0);

  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Installer.Application == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    return 0;
  }

  // ������� ��।� ᮮ�饭��.
  HMQ Message_queue = WinCreateMsgQueue (Installer.Application, 0);

  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Message_queue == NULLHANDLE)
  {
    // ��� - �訡��.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // ��室.
    WinTerminate (Installer.Application); return 0;
  }

  // ����᪠�� ��⠢���騥 �ਫ������.
  StdLib_Start ();
  Strings_Start ();
  Files_Start ();

  WindowTree_Start ();
  Layout_Start ();
  Environment_Start ();
  EnhancerProperties_Start ();

  // �᫨ ���� �ਫ������ 㦥 ���� - ��室.
  {
    CHAR Semaphore_name[] = "\\SEM32\\N2ENSTALLER";
    HMTX hmtxAlreadyRunning = NULLHANDLE;

    if (DosOpenMutexSem (Semaphore_name, &hmtxAlreadyRunning) == NO_ERROR)
    {
      WinDestroyMsgQueue (Message_queue);
      WinTerminate (Installer.Application);
      return 0;
    }
    else
    {
      DosCreateMutexSem (Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1);
    }
  }

  // ������ ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
  if (argc == 2 && stristr ("english", argv[1])) Installer.Code_page = ENGLISH;
  else Installer.Code_page = QuerySystemCodePage ();

  // ������塞 �������� ������, �ᯮ��㥬�� ������.
  ClientWindow_Start ();

  // ������� ���� ࠡ�祩 ������.
  CHAR Class_name[] = "InstallerWndClass";
  WinRegisterClass (Installer.Application, Class_name, (PFNWP) Installer_ClientWindowProc, 0, 0);

  // ������� ���� ࠬ��.
  ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU | FCF_BORDER | FCF_NOBYTEALIGN;
  Installer.Frame_window = WinCreateStdWindow (HWND_DESKTOP, CS_FRAME | WS_VISIBLE, &Creation_flags, Class_name, StrConst_EN_Title, 0, NULLHANDLE, 0, &Installer.Client_window);

  // �롨ࠥ� ᮮ�饭�� �� ��।�.
  QMSG Message; bzero (&Message, sizeof (QMSG));
  while (WinGetMsg (Installer.Application, &Message, 0, 0, 0)) WinDispatchMsg (Installer.Application, &Message);

  // ����뢠�� ����.
  WinDestroyWindow (Installer.Client_window);
  WinDestroyWindow (Installer.Frame_window);

  // ����뢠�� ��।� ᮮ�饭��.
  WinDestroyMsgQueue (Message_queue);

  // ��室.
  WinTerminate (Installer.Application); return 0;
}

