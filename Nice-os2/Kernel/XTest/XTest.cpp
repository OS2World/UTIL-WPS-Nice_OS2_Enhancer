#define DEBUG_VERSION
#include "Nice-os2.cpp"

// ─── Приложение ───

VOID XTest (HAB Application)
{
  /*

  // Узнаем высоту заголовка и картинки.
  INT TitleBar_height = WinQuerySysValue (QueryDesktopWindow (), SV_CYMINMAXBUTTON);

  Log ("TitleBar height:"); Log (TitleBar_height);

  */


  /*

  // Ждем, пока будет включен "Scroll Lock".
  while (1)
  {
    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (QueryDesktopWindow (), Keyboard_state, 0);

    if (Keyboard_state[VK_SCRLLOCK]) break;
    else DosSleep (1);
  }

  // Узнаем окно, над которым расположен указатель мыши.
  POINT Pointer = {0}; WinQueryPointerPos (QueryDesktopWindow (), &Pointer);
  HWND Window = WinWindowFromPoint (QueryDesktopWindow (), &Pointer, 1);
  HWND Frame_window = QueryFrameWindow (Window);

  // Если это окно VirtualPC и оно выбрано:
  if (IsOdinFrameWindow (Frame_window) && WindowIsActive (Frame_window))
  {
    // Посылаем сообщения в окно.
    while (1)
    {
      // Узнаем расположение окна рамки.
      SWP Wp = {0}; WinQueryWindowPos (Frame_window, &Wp);

      // Посылаем окну сообщения от клавиатуры и мыши.
      WinSetPointerPos (QueryDesktopWindow (), Wp.x + 1010, Wp.y + 35);
      WinPostMsg (Window, WM_BUTTON1DOWN, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));
      WinPostMsg (Window, WM_BUTTON1UP, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));

      DosSleep (250);

      WinSetPointerPos (QueryDesktopWindow (), Wp.x + 285, Wp.y + 75);
      WinPostMsg (Window, WM_BUTTON1DOWN, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));
      WinPostMsg (Window, WM_BUTTON1UP, MRFROM2SHORT (0, 0), MRFROM2SHORT (HT_NORMAL, KC_NONE));

      DosSleep (100);

      MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
      MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
      ComposeWMCharMessage (&First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_DELETE, 0, 0);
      WinPostMsg (Window, WM_CHAR, First_parameter_1, Second_parameter_1);
      WinPostMsg (Window, WM_CHAR, First_parameter_2, Second_parameter_2);

      DosSleep (1000);

      // Проверяем, включен ли еще "Scroll Lock".
      BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
      WinSetKeyboardStateTable (QueryDesktopWindow (), Keyboard_state, 0);

      if (!Keyboard_state[VK_SCRLLOCK]) break;
    }
  }

  */


  /*

  // Узнаем содержимое Clipboard.
  BYTE Common_string[1024] = "";
  LONG Common_string_length = 1024;
  BYTE UCS2LittleEndian_format[] = "text/unicode";
  BYTE UCS2LittleEndian_string[2048] = "";
  LONG UCS2LittleEndian_string_length = 2048;

  GetStringFromClipboard (Application,
                          Common_string,
                          Common_string_length,
                          UCS2LittleEndian_string,
                          UCS2LittleEndian_string_length,
                          UCS2LittleEndian_format);

  Log (Common_string);

  Log (UCS2LittleEndian_string[0]);
  Log (UCS2LittleEndian_string[1]);
  Log (UCS2LittleEndian_string[2]);
  Log (UCS2LittleEndian_string[3]);
  Log (UCS2LittleEndian_string[4]);
  Log (UCS2LittleEndian_string[5]);
  Log (UCS2LittleEndian_string[6]);
  Log (UCS2LittleEndian_string[7]);
  Log (UCS2LittleEndian_string[8]);

  */


  /*

  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // ...
  }
  WinEndEnumWindows (Enumeration);

  */

  // Возврат.
  return;
}

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

  WinMessageBox (HWND_DESKTOP, NULLHANDLE, "Ready...", "", 0, 0);

  /*

  InitKernel (Application, 0, NULLHANDLE);
  SetPreDefinedSettings (SET_ALL_SETTINGS);

  */

  // Выполняем действие.
  DosForceDelete ("_log.txt");
  Enhancer.Application = Application; XTest (Application);

  // Сбрасываем очередь сообщений.
  WinDestroyMsgQueue (Message_queue);

  // Выход.
  WinTerminate (Application); return 0;
}
