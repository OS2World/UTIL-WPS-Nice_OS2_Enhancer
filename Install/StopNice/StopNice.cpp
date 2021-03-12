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

// ─── Приложение ───

INT Main (INT argc, CHAR *argv[])
{
  // Определяем приложение в системе.
  HAB Application = WinInitialize (0);

  // Если это сделать не удалось - выход.
  if (Application == NULLHANDLE)
  {
    // Звук - ошибка.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // Выход.
    return 0;
  }

  // Создаем очередь сообщений.
  HMQ Message_queue = WinCreateMsgQueue (Application, 0);

  // Если очередь создать не удалось - выход.
  if (Message_queue == NULLHANDLE)
  {
    // Звук - ошибка.
    WinAlarm (HWND_DESKTOP, WA_ERROR);
    // Выход.
    WinTerminate (Application); return 0;
  }

  // Задаем список приложений.
  Repository_Start ();

  // Узнаем окно рабочего стола.
  HWND Desktop = WinQueryDesktopWindow (Application, NULLHANDLE);

  {
    // Перебираем окна в окне рабочего стола.
    HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
    while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
    {
      // Если это окно расширителя - закрываем его.
      if (IsFrameWindow (Window))
       if (WindowIsCreatedBy (APP_NICE_ENHANCER, Window) || WindowIsCreatedBy (APP_NICE_ENHANCER_SHELL, Window))
        WinPostMsg (Window, WM_SYSCOMMAND, (MPARAM) SC_CLOSE, 0);
    }
    WinEndEnumWindows (Enumeration);
  }

  // Сбрасываем очередь сообщений.
  WinDestroyMsgQueue (Message_queue);

  // Выход.
  WinTerminate (Application); return 0;
}
