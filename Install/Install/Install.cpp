// Постоянные величины.
#include "..\\..\\Nice-os2\\Shared\\General.h"
#pragma pack(4)

// Вызовы C/C++.
#include "..\\..\\Nice-os2\\Shared\\StdLib\\StdLib_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\StdLib.cpp"

// Работа со строками.
#include "..\\..\\Nice-os2\\Shared\\Strings.h"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings\\Strings_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Strings.cpp"

// Работа с файлами.
#include "..\\..\\Nice-os2\\Shared\\Files\\Files_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Files.cpp"

// Расположение окон.
#include "..\\..\\Nice-os2\\Shared\\WindowTree.h"
#include "..\\..\\Nice-os2\\Shared\\WindowTree\\WindowTree_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\WindowTree.cpp"

#include "..\\..\\Nice-os2\\Shared\\Layout.h"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_list.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout\\Layout_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Layout.cpp"

// Переменные среды.
#define INCLUDED_BY_SHELL

#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_data.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment\\Environment_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\Environment.cpp"

#include "..\\..\\Nice-os2\\Shared\\EnhancerProperties\\EnhancerProperties_code.cpp"
#include "..\\..\\Nice-os2\\Shared\\EnhancerProperties.cpp"

// Данные приложения.
typedef struct _INSTALLER
{
  // Приложение.
  HAB Application;

  // Страна, в которой работает приложение.
  ULONG Code_page;

  // Окно рамки.
  HWND Frame_window;
  CHAR Frame_window_title[SIZE_OF_TITLE];
  // Окно рабочей области.
  HWND Client_window;
}
INSTALLER; INSTALLER Installer;

// Строки и изображения.
#include "Resources\\Resources.h"
#include "Resources\\StrConst.h"

// Внутренние сообщения.
#define MY_CREATE          (WM_USER +  1)

#define MY_APPLY_LAYOUT    (WM_USER + 10)
#define MY_ENABLE_BUTTONS  (WM_USER + 20)

// Действия.
#define NIA_INSTALL 1
#define NIA_REMOVE  0

// Функции для запуска потоков приложения.
#include "Threads\\InstallerThread.h"

// Окна приложения.
#include "Pages\\Controls.h"

#include "Pages\\ClientWindow\\ClientWindow_data.cpp"
#include "Pages\\ClientWindow\\ClientWindow_open.cpp"
#include "Pages\\ClientWindow\\ClientWindow_page.cpp"
#include "Pages\\ClientWindow.cpp"

// Потоки приложения.
#include "Threads\\InstallerThread.c"

// ─── Приложение ───

INT Main (INT argc, PCHAR argv[])
{
  // Сбрасываем свойства приложения.
  bzero (&Installer, sizeof (INSTALLER));

  // Определяем приложение в системе.
  Installer.Application = WinInitialize (0);

  // Если это сделать не удалось - выход.
  if (Installer.Application == NULLHANDLE)
  {
    // Звук - ошибка.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // Выход.
    return 0;
  }

  // Создаем очередь сообщений.
  HMQ Message_queue = WinCreateMsgQueue (Installer.Application, 0);

  // Если очередь создать не удалось - выход.
  if (Message_queue == NULLHANDLE)
  {
    // Звук - ошибка.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // Выход.
    WinTerminate (Installer.Application); return 0;
  }

  // Запускаем составляющие приложения.
  StdLib_Start ();
  Strings_Start ();
  Files_Start ();

  WindowTree_Start ();
  Layout_Start ();
  Environment_Start ();
  EnhancerProperties_Start ();

  // Если окно приложения уже есть - выход.
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

  // Узнаем страну, в которой работает приложение.
  if (argc == 2 && stristr ("english", argv[1])) Installer.Code_page = ENGLISH;
  else Installer.Code_page = QuerySystemCodePage ();

  // Заполняем структуры данных, используемых окнами.
  ClientWindow_Start ();

  // Создаем окно рабочей области.
  CHAR Class_name[] = "InstallerWndClass";
  WinRegisterClass (Installer.Application, Class_name, (PFNWP) Installer_ClientWindowProc, 0, 0);

  // Создаем окно рамки.
  ULONG Creation_flags = FCF_TITLEBAR | FCF_SYSMENU | FCF_BORDER | FCF_NOBYTEALIGN;
  Installer.Frame_window = WinCreateStdWindow (HWND_DESKTOP, CS_FRAME | WS_VISIBLE, &Creation_flags, Class_name, StrConst_EN_Title, 0, NULLHANDLE, 0, &Installer.Client_window);

  // Выбираем сообщения из очереди.
  QMSG Message; bzero (&Message, sizeof (QMSG));
  while (WinGetMsg (Installer.Application, &Message, 0, 0, 0)) WinDispatchMsg (Installer.Application, &Message);

  // Закрываем окна.
  WinDestroyWindow (Installer.Client_window);
  WinDestroyWindow (Installer.Frame_window);

  // Сбрасываем очередь сообщений.
  WinDestroyMsgQueue (Message_queue);

  // Выход.
  WinTerminate (Installer.Application); return 0;
}

