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

// ─── Приложение ───

INT Main (INT argc, CHAR *argv[])
{
  // Если приложение уже есть - выход.
  {
    CHAR Semaphore_name[] = "\\SEM32\\KBDCLICKER";
    HMTX hmtxAlreadyRunning = NULLHANDLE;

    if (DosOpenMutexSem (Semaphore_name, &hmtxAlreadyRunning) == NO_ERROR)
     DosExit (EXIT_PROCESS, 0);
    else
     DosCreateMutexSem (Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1);
  }

  // Загружаем поддержку звука.
  LoadMMOS2 ();
  // Если это сделать не удалось - выход.
  if (!MMOS2IsLoaded ()) DosExit (EXIT_PROCESS, 0);

  // Определяем приложение в системе.
  Application_in_DATA_segment = WinInitialize (0);
  // Если это сделать не удалось - выход.
  if (Application_in_DATA_segment == NULLHANDLE)
  {
    // Выход.
    DosExit (EXIT_PROCESS, 0);
  }

  // Создаем очередь сообщений.
  HMQ Message_queue = WinCreateMsgQueue (Application_in_DATA_segment, 0);
  // Если очередь создать не удалось - выход.
  if (Message_queue == NULLHANDLE)
  {
    // Выход.
    WinTerminate (Application_in_DATA_segment);
    DosExit (EXIT_PROCESS, 0);
  }

  // Создаем окно рабочей области.
  CHAR Class_name[] = "KbdClickerWindowClass";
  WinRegisterClass (Application_in_DATA_segment, Class_name, (PFNWP) ClientWindowProc, 0, 0);

  // Создаем окно рамки.
  CHAR MainWindow_title[] = ""; ULONG Creation_flags = 0; HWND Client_window = NULLHANDLE;
  HWND Frame_window = WinCreateStdWindow (HWND_DESKTOP, CS_FRAME, &Creation_flags, Class_name, MainWindow_title, 0, NULLHANDLE, 0, &Client_window);
  WinShowWindow (Frame_window, 0);

  // Выбираем сообщения из очереди.
  QMSG Message = {0};
  while (WinGetMsg (Application_in_DATA_segment, &Message, 0, 0, 0)) WinDispatchMsg (Application_in_DATA_segment, &Message);

  // Закрываем окна.
  WinDestroyWindow (Client_window);
  WinDestroyWindow (Frame_window);

  // Отключаем поддержку звука.
  UnloadMMOS2 ();

  // Выход.
  WinTerminate (Application_in_DATA_segment);
  DosExit (EXIT_PROCESS, 0); return 0;
}

// ─── Принимает сообщения, которые приходят в окно приложения ───

// WinDispatchMsg вызывает WinProc всякий раз, когда для окна есть сообщение.
MRESULT EXPENTRY ClientWindowProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Создание окна:
  if (Message == WM_CREATE)
  {
    // Посылаем в окно сообщение о том, что надо воспроизвести звук.
    WinPostMsg (Window, MY_PLAY_WAVE, 0, 0);

    // Возврат.
    return 0;
  }

  // Воспроизведение звука:
  if (Message == MY_PLAY_WAVE)
  {
    // Запускаем на всякий случай счетчик времени.
    WinStartTimer (Application_in_DATA_segment, Window, 1, 1000);

    // Загружаем звук в память и запоминаем его.
    HSOUND Sound = LoadSound (File_name_in_DATA_segment);

    // Если звук не загружен - закрываем окно.
    if (!Sound) WinPostMsg (Window, WM_CLOSE, 0, 0);

    // Если звук есть:
    if (Sound)
    {
      // Воспроизводим звук.
      ULONG Success = PlaySound (Sound, Window);
      // Если звук не воспроизводится - закрываем окно.
      if (!Success) WinPostMsg (Window, WM_CLOSE, 0, 0);
    }

    // Возврат.
    return 0;
  }

  // Сообщение о том, что звук воспроизведен,
  // а также сообщение от счетчика времени:
  if (Message == MM_MCINOTIFY || Message == WM_TIMER)
  {
    // Освобождаем память.
    HSOUND Sound = SHORT1FROMMP (Second_parameter); DeleteSound (Sound);

    // Закрываем окно.
    WinPostMsg (Window, WM_CLOSE, 0, 0);

    // Возврат.
    return 0;
  }

  // Рисование окна:
  if (Message == WM_PAINT)
  {
    // Ничего не делаем.
    RECTL Rectangle = {0};
    WinEndPaint (WinBeginPaint (Window, NULLHANDLE, &Rectangle));

    // Возврат.
    return 0;
  }

  // Другое сообщение - не обрабатывается.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
