#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSERRORS

#include <OS2.h>

#include "..\\Shared\\General.h"
#pragma pack(4)

#include "..\\Shared\\Mciapi.cpp"

HAB Application_in_DATA_segment = NULLHANDLE;
CHAR File_name_in_DATA_segment[] = "Keyboard.wav";

MRESULT EXPENTRY ClientWindowProc (HWND, ULONG, MPARAM, MPARAM);

#define MY_PLAY_WAVE WM_USER + 100

// ��� �ਫ������ ���

INT Main (INT argc, CHAR *argv[])
{
  // �᫨ �ਫ������ 㦥 ���� - ��室.
  {
    CHAR Semaphore_name[] = "\\SEM32\\KBDCLICKER";
    HMTX hmtxAlreadyRunning = NULLHANDLE;

    if (DosOpenMutexSem (Semaphore_name, &hmtxAlreadyRunning) == NO_ERROR)
     DosExit (EXIT_PROCESS, 0);
    else
     DosCreateMutexSem (Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1);
  }

  // ����㦠�� �����প� ��㪠.
  LoadMMOS2 ();
  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (!MMOS2IsLoaded ()) DosExit (EXIT_PROCESS, 0);

  // ��।��塞 �ਫ������ � ��⥬�.
  Application_in_DATA_segment = WinInitialize (0);
  // �᫨ �� ᤥ���� �� 㤠���� - ��室.
  if (Application_in_DATA_segment == NULLHANDLE)
  {
    // ��室.
    DosExit (EXIT_PROCESS, 0);
  }

  // ������� ��।� ᮮ�饭��.
  HMQ Message_queue = WinCreateMsgQueue (Application_in_DATA_segment, 0);
  // �᫨ ��।� ᮧ���� �� 㤠���� - ��室.
  if (Message_queue == NULLHANDLE)
  {
    // ��室.
    WinTerminate (Application_in_DATA_segment);
    DosExit (EXIT_PROCESS, 0);
  }

  // ������� ���� ࠡ�祩 ������.
  CHAR Class_name[] = "KbdClickerWindowClass";
  WinRegisterClass (Application_in_DATA_segment, Class_name, (PFNWP) ClientWindowProc, 0, 0);

  // ������� ���� ࠬ��.
  CHAR MainWindow_title[] = ""; ULONG Creation_flags = 0; HWND Client_window = NULLHANDLE;
  HWND Frame_window = WinCreateStdWindow (HWND_DESKTOP, CS_FRAME, &Creation_flags, Class_name, MainWindow_title, 0, NULLHANDLE, 0, &Client_window);
  WinShowWindow (Frame_window, 0);

  // �롨ࠥ� ᮮ�饭�� �� ��।�.
  QMSG Message = {0};
  while (WinGetMsg (Application_in_DATA_segment, &Message, 0, 0, 0)) WinDispatchMsg (Application_in_DATA_segment, &Message);

  // ����뢠�� ����.
  WinDestroyWindow (Client_window);
  WinDestroyWindow (Frame_window);

  // �⪫�砥� �����প� ��㪠.
  UnloadMMOS2 ();

  // ��室.
  WinTerminate (Application_in_DATA_segment);
  DosExit (EXIT_PROCESS, 0); return 0;
}

// ��� �ਭ����� ᮮ�饭��, ����� ��室�� � ���� �ਫ������ ���

// WinDispatchMsg ��뢠�� WinProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
MRESULT EXPENTRY ClientWindowProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // �������� ����:
  if (Message == WM_CREATE)
  {
    // ���뫠�� � ���� ᮮ�饭�� � ⮬, �� ���� ���ந����� ���.
    WinPostMsg (Window, MY_PLAY_WAVE, 0, 0);

    // ������.
    return 0;
  }

  // ���ந�������� ��㪠:
  if (Message == MY_PLAY_WAVE)
  {
    // ����᪠�� �� ��直� ��砩 ���稪 �६���.
    WinStartTimer (Application_in_DATA_segment, Window, 1, 1000);

    // ����㦠�� ��� � ������ � ���������� ���.
    HSOUND Sound = LoadSound (File_name_in_DATA_segment);

    // �᫨ ��� �� ����㦥� - ����뢠�� ����.
    if (!Sound) WinPostMsg (Window, WM_CLOSE, 0, 0);

    // �᫨ ��� ����:
    if (Sound)
    {
      // ���ந������ ���.
      ULONG Success = PlaySound (Sound, Window);
      // �᫨ ��� �� ���ந�������� - ����뢠�� ����.
      if (!Success) WinPostMsg (Window, WM_CLOSE, 0, 0);
    }

    // ������.
    return 0;
  }

  // ����饭�� � ⮬, �� ��� ���ந������,
  // � ⠪�� ᮮ�饭�� �� ���稪� �६���:
  if (Message == MM_MCINOTIFY || Message == WM_TIMER)
  {
    // �᢮������� ������.
    HSOUND Sound = SHORT1FROMMP (Second_parameter); DeleteSound (Sound);

    // ����뢠�� ����.
    WinPostMsg (Window, WM_CLOSE, 0, 0);

    // ������.
    return 0;
  }

  // ��ᮢ���� ����:
  if (Message == WM_PAINT)
  {
    // ��祣� �� ������.
    RECTL Rectangle = {0};
    WinEndPaint (WinBeginPaint (Window, NULLHANDLE, &Rectangle));

    // ������.
    return 0;
  }

  // ��㣮� ᮮ�饭�� - �� ��ࠡ��뢠����.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
