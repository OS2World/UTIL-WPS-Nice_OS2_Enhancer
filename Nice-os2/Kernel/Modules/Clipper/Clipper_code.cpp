
// ─── Узнает, идет ли выделение в текстовом окне ───

// Frame_window - текстовое окно.
BYTE Clipper_VIOMarkingIsInProcess (HWND Frame_window)
{
  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Если строка меню для включения выделения есть она и выбрана - в окне идет выделение.
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK))
   if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
    return 1;

  // Возврат.
  return 0;
}

// ─── Вставляет текст в окно ───

// Frame_window - текстовое окно.
VOID Clipper_PasteTextToVIOWindow (HWND Frame_window)
{
  // Если в Clipboard есть какие-то строки:
  CHAR Short_string[4] = ""; GetStringFromClipboard (Enhancer.Application, Short_string, 4);

  if (Short_string[0] != 0)
  {
    // Сбрасываем Clipboard и запоминаем строки еще раз как CF_TEXT.
    // Это необходимо делать потому, что если строки были взяты из другого текстового окна,
    // то при нажатой клавише Shift другие текстовые окна не могут вставить последние буквы.

    // Отводим память для текста.
    PCHAR Clipboard_text = NULL; INT Length = 16384;
    if (DosAllocMem ((PPVOID) &Clipboard_text, Length, PAG_ALLOCATE) != NO_ERROR) return;

    // Забираем текст из Clipboard и тут же добавляем его в Clipboard.
    GetStringFromClipboard (Enhancer.Application, Clipboard_text, Length); PutStringIntoClipboard (Enhancer.Application, Clipboard_text);

    // Освобождаем память.
    DosFreeMem (Clipboard_text); Clipboard_text = NULL;

    // Узнаем окно картинки.
    HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

    // Если в меню есть строка для вставки текста - посылаем в окно команду от нее.
    if (MenuItemIsPresent (SysMenu_window, SM_VIO_PASTE))
     WinPostMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_PASTE, MPFROM2SHORT (CMDSRC_MENU, 0));
  }

  // Возврат.
  return;
}

// ─── Выключает выделение строк в текстовом окне ───

// Frame_window - текстовое окно.
VOID Clipper_EndVIOMarkingAndCopyText (HWND Frame_window)
{
  // Узнаем окно картинки.
  HWND SysMenu_window = WinWindowFromID (Frame_window, FID_SYSMENU);

  // Если окна нет - возврат.
  if (!WinIsWindow (WinQueryAnchorBlock (SysMenu_window), SysMenu_window)) return;

  // Если в меню есть строки для включения выделения:
  if (MenuItemIsPresent (SysMenu_window, SM_VIO_MARK) &&
      MenuItemIsPresent (SysMenu_window, SM_VIO_MOUSE))
  {
    // Если обе строки меню для включения выделения выбраны:
    if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK) &&
        MenuItemIsChecked (SysMenu_window, SM_VIO_MOUSE))
    {
      // Запоминаем выделенный текст. При этом строка для включения выделения должна перестать быть включенной.
      if (MenuItemIsPresent (SysMenu_window, SM_VIO_COPY))
       WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_COPY, MPFROM2SHORT (CMDSRC_MENU, 0));

      // Выключаем выделение с помощью мыши.
      WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MOUSE, MPFROM2SHORT (CMDSRC_MENU, 0));
      WinSendMsg (SysMenu_window, MM_SETITEMATTR, MPFROM2SHORT (SM_VIO_MOUSE, INCLUDE_SUBMENUS), MPFROM2SHORT (MIA_CHECKED, 0));

      // Если строка меню для включения выделения все еще выбрана:
      if (MenuItemIsChecked (SysMenu_window, SM_VIO_MARK))
      {
        // Выключаем выделение с помощью клавиатуры.
        WinSendMsg (Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_MARK, MPFROM2SHORT (CMDSRC_MENU, 0));
        WinSendMsg (SysMenu_window, MM_SETITEMATTR, MPFROM2SHORT (SM_VIO_MARK, INCLUDE_SUBMENUS), MPFROM2SHORT (MIA_CHECKED, 0));
      }
    }
  }

  // Возврат.
  return;
}

// ─── Вставляет текст в окно Mozilla при нажатии FireFox-клавиши ───

// Input_window - окно, Command - какие буквы надо вставить.
VOID Clipper_PasteFireFoxCharacters (HWND Input_window, ULONG Command)
{
  // Запоминаем содержимое Clipboard. Для работы с FireFox требуется не только
  // обыкновеннай текст, но и текст в кодировке UCS2, которую понимает Mozilla.
  if (Clipper.RTSettings.Clipboard_data_Text != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_Text); Clipper.RTSettings.Clipboard_data_Text = NULL; }
  if (Clipper.RTSettings.Clipboard_data_UCS2 != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_UCS2); Clipper.RTSettings.Clipboard_data_UCS2 = NULL; }

  {
    Clipper.RTSettings.Clipboard_data_Text_length = 0;
    Clipper.RTSettings.Clipboard_data_UCS2_length = 0;

    INT Max_length = 16384; PBYTE Text = NULL;
    if (DosAllocMem ((PPVOID) &Text, Max_length, PAG_ALLOCATE) != NO_ERROR) return;

    GetStringFromClipboard (Enhancer.Application, Text, Max_length);
    INT Real_length = strlen (Text) + 1;

    DosFreeMem (Text); Text = NULL;

    Clipper.RTSettings.Clipboard_data_Text_length = Real_length;
    Clipper.RTSettings.Clipboard_data_UCS2_length = Real_length * 2;
  }

  if (DosAllocMem ((PPVOID) &Clipper.RTSettings.Clipboard_data_Text, Clipper.RTSettings.Clipboard_data_Text_length, PAG_ALLOCATE) != NO_ERROR) return;
  if (DosAllocMem ((PPVOID) &Clipper.RTSettings.Clipboard_data_UCS2, Clipper.RTSettings.Clipboard_data_UCS2_length, PAG_ALLOCATE) != NO_ERROR) return;

  bzero (Clipper.RTSettings.Clipboard_data_Text, Clipper.RTSettings.Clipboard_data_Text_length);
  bzero (Clipper.RTSettings.Clipboard_data_UCS2, Clipper.RTSettings.Clipboard_data_UCS2_length);

  CHAR Mozilla_internal_format[] = "text/unicode";

  GetStringFromClipboard (Enhancer.Application,
                          Clipper.RTSettings.Clipboard_data_Text,
                          Clipper.RTSettings.Clipboard_data_Text_length,
                          Clipper.RTSettings.Clipboard_data_UCS2,
                          Clipper.RTSettings.Clipboard_data_UCS2_length,
                          Mozilla_internal_format);

  // Задаем новую строку в обычном виде и в виде UCS2-строки.
  BYTE Common_string[3] = { 0x00, 0x00, 0x00 };
  BYTE UCS2LittleEndian_string[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  LONG UCS2LittleEndian_string_length = 0;

  #include "Modules\\Clipper\\Clipper_ffx.cpp"

  if (Command == SM_FFX_PASTE_DASH)
  {
    Common_string[0] = '-';
    Common_string[1] = 0x00;

    UCS2LittleEndian_string[0] = Dash_in_Unicode[1];
    UCS2LittleEndian_string[1] = Dash_in_Unicode[0];
    UCS2LittleEndian_string[2] = 0x00;
    UCS2LittleEndian_string[3] = 0x00;

    UCS2LittleEndian_string_length = 4;
  }

  if (Command == SM_FFX_PASTE_QUOTES_1)
  {
    Common_string[0] = '"';
    Common_string[1] = '"';
    Common_string[2] = 0x00;

    UCS2LittleEndian_string[0] = Primary_quote_1_in_Unicode[1];
    UCS2LittleEndian_string[1] = Primary_quote_1_in_Unicode[0];
    UCS2LittleEndian_string[2] = Primary_quote_2_in_Unicode[1];
    UCS2LittleEndian_string[3] = Primary_quote_2_in_Unicode[0];
    UCS2LittleEndian_string[4] = 0x00;
    UCS2LittleEndian_string[5] = 0x00;

    UCS2LittleEndian_string_length = 6;
  }

  if (Command == SM_FFX_PASTE_QUOTES_2)
  {
    Common_string[0] = '"';
    Common_string[1] = '"';
    Common_string[2] = 0x00;

    UCS2LittleEndian_string[0] = Secondary_quote_1_in_Unicode[1];
    UCS2LittleEndian_string[1] = Secondary_quote_1_in_Unicode[0];
    UCS2LittleEndian_string[2] = Secondary_quote_2_in_Unicode[1];
    UCS2LittleEndian_string[3] = Secondary_quote_2_in_Unicode[0];
    UCS2LittleEndian_string[4] = 0x00;
    UCS2LittleEndian_string[5] = 0x00;

    UCS2LittleEndian_string_length = 6;
  }

  PutStringIntoClipboard (Enhancer.Application,
                          Common_string,
                          UCS2LittleEndian_string,
                          UCS2LittleEndian_string_length,
                          Mozilla_internal_format);

  // Посылаем в очередь окна сообщение WM_MARK. При его получении можно
  // будет изменить состояние клавиатуры и направить в окно сообщение WM_CHAR.
  HMQ Message_queue = WinQueryWindowULong (Input_window, QWL_HMQ);
  WinPostQueueMsg (Message_queue, WM_MARK, (MPARAM) MRK_POST_CTRL_V, (MPARAM) Input_window);

  // Возврат.
  return;
}

// ─── Восстанавливает содержимое Clipboard ───

VOID Clipper_RestoreClipboard (VOID)
{
  // Переносим в Clipboard предыдущие данные.
  CHAR Mozilla_internal_format[] = "text/unicode";

  PutStringIntoClipboard (Enhancer.Application,
                          Clipper.RTSettings.Clipboard_data_Text,
                          Clipper.RTSettings.Clipboard_data_UCS2,
                          Clipper.RTSettings.Clipboard_data_UCS2_length,
                          Mozilla_internal_format);

  // Освобождаем память.
  if (Clipper.RTSettings.Clipboard_data_Text != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_Text); Clipper.RTSettings.Clipboard_data_Text = NULL; }
  if (Clipper.RTSettings.Clipboard_data_UCS2 != NULL) { DosFreeMem (Clipper.RTSettings.Clipboard_data_UCS2); Clipper.RTSettings.Clipboard_data_UCS2 = NULL; }

  Clipper.RTSettings.Clipboard_data_Text_length = 0;
  Clipper.RTSettings.Clipboard_data_UCS2_length = 0;

  // Возврат.
  return;
}

// ─── Обработчик сообщений, которые были переданы в поток ───

// Message определяет пришедшее сообщение.
VOID Clipper_ClipperMessageProcessing (PQMSG Message)
{
  // Устанавливаем приоритет потока.
  if (Message->msg == SM_PRIORITY)
  {
    // Устанавливаем приоритет.
    LONG Class = (LONG) Message->mp1;
    LONG Delta = (LONG) Message->mp2;
    DosSetPriority (PRTYS_THREAD, Class, Delta, 0);

    // Запоминаем приоритет.
    Enhancer.Modules.Clipper->Priority = MAKELONG (Class, Delta);
  }

  // Включаем выделение в текстовом окне.
  if (Message->msg == SM_BEGIN_VIO_MARKING || Message->msg == SM_END_VIO_MARKING)
  {
    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Включаем и выключаем выделение.
    if (Message->msg == SM_BEGIN_VIO_MARKING) Clipper_BeginVIOMarking (Frame_window);
    if (Message->msg == SM_END_VIO_MARKING) Clipper_EndVIOMarkingAndCopyText (Frame_window);
  }

  // Запоминаем выделенный текст.
  if (Message->msg == SM_COPY_VIO_TEXT)
  {
    // Если в текстовых окнах не надо запоминать текст - возврат.
    if (!Clipper.Settings.Mouse_in_VIO) return;

    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Если выделение текста еще не начато - начинаем его.
    if (!Clipper_VIOMarkingIsInProcess (Frame_window)) Clipper_BeginVIOMarking (Frame_window);
    // Иначе - завершаем выделение и запоминаем текст.
    else Clipper_EndVIOMarkingAndCopyText (Frame_window);
  }

  // Вставляем текст в окно.
  if (Message->msg == SM_PASTE_VIO_TEXT)
  {
    // Если в текстовых окнах не надо запоминать текст - возврат.
    if (!Clipper.Settings.Mouse_in_VIO) return;

    // Узнаем окно рамки.
    HWND Frame_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Frame_window), Frame_window)) return;

    // Если в окне не идет выделение текста - вставляем текст.
    if (!Clipper_VIOMarkingIsInProcess (Frame_window)) Clipper_PasteTextToVIOWindow (Frame_window);
  }

  // Запоминаем текст при нажатии средней кнопки мыши.
  if (Message->msg == SM_MB_CLICK)
  {
    // Узнаем окно, с которым работает пользователь.
    HWND Input_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Узнаем время, достаточное для двойного нажатия на кнопку мыши.
    LONG DblClk_delta = WinQuerySysValue (Desktop, SV_DBLCLKTIME);

    // Выполняем задержку, чтобы избежать двойного нажатия.
    while (1)
    {
      // Если время последнего нажатия на среднюю кнопку мыши неизвестно - произошло двойное нажатие, возврат.
      // В это время в очереди потока уже лежит следующее сообщение - SM_MB_DOUBLECLICK.
      if (WMMBDownTime () == 0)
      {
        // Освобождаем указатель мыши.
        ResetPointer ();

        // Возврат.
        return;
      }

      // Узнаем текущее время.
      LONG Current_time = WinGetCurrentTime (Enhancer.Application);

      // Если прошло достаточно много времени - все в порядке.
      if (Current_time > WMMBDownTime ())
       if (Current_time - WMMBDownTime () > DblClk_delta)
        break;

      // Если время прошло через ноль - возврат.
      if (Current_time < WMMBDownTime ())
      {
        // Освобождаем указатель мыши.
        ResetPointer ();

        // Возврат.
        return;
      }

      // Через некоторое время - устанавливаем указатель мыши "прозрачная стрелка".
      if (Current_time - WMMBDownTime () > (DblClk_delta / 2))
       if (Resources.Pointer_for_CopyPaste != NULLHANDLE)
        WinSetPointer (QueryDesktopWindow (), Resources.Pointer_for_CopyPaste);

      // Выполняем задержку.
      Retard ();
    }

    // Освобождаем указатель мыши.
    ResetPointer ();

    // Время последнего нажатия на среднюю кнопку мыши - неизвестно.
    DiscardWMMBDownTime ();

    // Узнаем ускоритель для этого окна.
    LONG Accelerator = (LONG) Message->mp2;

    // Запоминаем текст в окне.
    ClipboardMouseAction (Input_window, MOUSE_CLIPBOARD_COPY, Accelerator);
  }

  // Вставляем текст в окно при нажатии средней кнопки мыши.
  if (Message->msg == SM_MB_DOUBLECLICK)
  {
    // Узнаем окно, с которым работает пользователь.
    HWND Input_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // Если кнопка мыши снова была нажата - возврат.
    if (WMMBDownTime ()) return;

    // Узнаем ускоритель для этого окна.
    LONG Accelerator = (LONG) Message->mp2;

    // Вставляем текст в окно.
    ClipboardMouseAction (Input_window, MOUSE_CLIPBOARD_PASTE, Accelerator);
  }

  // Вставляем текст в окно Mozilla при нажатии FireFox-клавиши.
  if (Message->msg >= SM_FFX_PASTE_FIRST && Message->msg <= SM_FFX_PASTE_LAST)
  {
    // Узнаем окно, с которым работает пользователь.
    HWND Input_window = (HWND) Message->mp1;

    // Если окна нет - возврат.
    if (!WinIsWindow (WinQueryAnchorBlock (Input_window), Input_window)) return;

    // Вставляем текст в окно.
    Clipper_PasteFireFoxCharacters (Input_window, Message->msg);
  }

  // Восстанавливаем содержимое Clipboard.
  if (Message->msg == SM_RESTORE_CLIPBOARD) Clipper_RestoreClipboard ();

  // Возврат.
  return;
}

// ─── Поток для выделения строк в окнах ───

VOID Clipper_ClipperThread (VOID)
{
  // Определяем поток в системе.
  HAB Thread = WinInitialize (0);

  // Если это сделать не удалось - выход.
  if (Thread == NULLHANDLE)
  {
    // При создании потока произошла ошибка.
    Thread_responds.Thread_is_created = -1;

    // Выход.
    return;
  }

  // Создаем очередь сообщений - она должна быть в каждом потоке.
  HMQ Message_queue = WinCreateMsgQueue (Thread, 0); Enhancer.Modules.Clipper->Message_queue = Message_queue;

  // Если очередь создать не удалось - выход.
  if (Enhancer.Modules.Clipper->Message_queue == NULLHANDLE)
  {
    // Завершаем работу потока.
    WinTerminate (Thread);

    // При создании потока произошла ошибка.
    Thread_responds.Thread_is_created = -1;

    // Выход.
    return;
  }

  // Поток создан успешно.
  Thread_responds.Thread_is_created = 1;

  // Получение и обработка сообщений, приходящих в поток.
  QMSG Message = {0};
  while (WinGetMsg (Thread, &Message, 0, 0, 0))
  {
    // Проверяем, не идет ли следом такое же сообщение.
    QMSG Next_message = {0};
    WinPeekMsg (Thread, &Next_message, NULLHANDLE, Message.msg, Message.msg, PM_NOREMOVE);
    if (Next_message.msg == Message.msg)
     if (Next_message.mp1 == Message.mp1)
      if (Next_message.mp2 == Message.mp2)
       if (Next_message.hwnd == Message.hwnd) continue;

    // Обрабатываем сообщение.
    Clipper_ClipperMessageProcessing (&Message);
  }

  // Завершаем работу потока.
  WinDestroyMsgQueue (Message_queue);
  WinTerminate (Thread);
  DosExit (EXIT_THREAD, 0);
}
