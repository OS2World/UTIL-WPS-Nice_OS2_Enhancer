// ─── Устанавливает переключатели на клавиатуре ───

VOID Controller_SetNumLock (VOID)
{
  //
  // Этот метод можно вызывать только в потоке расширителя, но не в обработчиках сообщений,
  // направляемых окнам, так как если какое-то приложение будет запущено по команде "Detach",
  // метод DosDevIOCtl работать не будет, и при изменении состояния переключателей они так и
  // останутся выключенными. Состояние всех остальных клавиш можно менять где угодно.
  //

  // Первое действие: обращаемся к драйверу клавиатуры "KBD$".
  {
    // Устанавливаем соединение с драйвером.
    ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
    ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

    HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
    DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

    // Если драйвер открыт:
    if (Keyboard)
    {
      // Узнаем состояние клавиатуры.
      SHIFTSTATE Shift_state = {0}; ULONG Length = sizeof (Shift_state); ULONG No_data = 0; APIRET Result = ERROR_OPEN_FAILED;
      Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_GETSHIFTSTATE, NULL, 0, &No_data, &Shift_state, sizeof (Shift_state), &Length);

      // Если оно получено:
      if (Result == NO_ERROR)
      {
        // Включаем или выключаем Num Lock.
        if (Controller.Settings.Turn_Num_Lock == 1) Shift_state.fsState |=  NUMLOCK_ON;
        if (Controller.Settings.Turn_Num_Lock == 2) Shift_state.fsState &= ~NUMLOCK_ON;

        // Выключаем CapsLock и ScrollLock (иначе оконная оболочка может заставить их "мигать").
        Shift_state.fsState &= ~CAPSLOCK_ON;
        Shift_state.fsState &= ~SCROLLLOCK_ON;

        // Включаем Insert.
        Shift_state.fsState |= INSERT_ON;

        // Устанавливаем новое состояние клавиатуры.
        ULONG Length = sizeof (Shift_state); ULONG No_data = 0;
        DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSHIFTSTATE, &Shift_state, sizeof (Shift_state), &Length, NULL, 0, &No_data);
      }

      DosClose (Keyboard); Keyboard = NULLHANDLE;
    }
  }

  // Второе действие: меняем настройки оконной оболочки.
  {
    // Узнаем состояние клавиатуры.
    HWND Desktop = QueryDesktopWindow ();

    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

    // Сбрасываем состояние всех переключателей (иначе оконная оболочка может заставить их "мигать").
    Keyboard_state[VK_NUMLOCK]  = 0;
    Keyboard_state[VK_CAPSLOCK] = 0;
    Keyboard_state[VK_SCRLLOCK] = 0;
    Keyboard_state[VK_INSERT]   = 0;

    // Включаем или выключаем Num Lock.
    if (Controller.Settings.Turn_Num_Lock == 1) Keyboard_state[VK_NUMLOCK] |= SET_KEY_TOGGLED;

    // Устанавливаем новое состояние клавиатуры.
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);

    // Устанавливаем настройки OS/2.
    WinSetSysValue (Desktop, SV_INSERTMODE, 1);
    WinSetSysValue (Desktop, SV_SETLIGHTS, 1);
  }

  // Возврат.
  return;
}

// ─── Выключает клавиши "Shift" на клавиатуре ───

VOID Controller_ResetShiftKeys (VOID)
{
  //
  // Этот метод надо вызывать в потоке расширителя, иначе "DosDevIOCtl" не работает.
  //

  // Первое действие: обращаемся к драйверу клавиатуры "KBD$".
  {
    // Устанавливаем соединение с драйвером.
    ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
    ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

    HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
    DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

    // Если драйвер открыт:
    if (Keyboard)
    {
      // Узнаем состояние клавиатуры.
      SHIFTSTATE Shift_state = {0}; ULONG Length = sizeof (Shift_state); ULONG No_data = 0; APIRET Result = ERROR_OPEN_FAILED;
      Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_GETSHIFTSTATE, NULL, 0, &No_data, &Shift_state, sizeof (Shift_state), &Length);

      // Если оно получено:
      if (Result == NO_ERROR)
      {
        // Выключаем Shift.
        Shift_state.fsState &= ~LEFTSHIFT;
        Shift_state.fsState &= ~RIGHTSHIFT;

        // Устанавливаем новое состояние клавиатуры.
        ULONG Length = sizeof (Shift_state); ULONG No_data = 0;
        DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSHIFTSTATE, &Shift_state, sizeof (Shift_state), &Length, NULL, 0, &No_data);
      }

      DosClose (Keyboard); Keyboard = NULLHANDLE;
    }
  }

  // Второе действие: меняем настройки оконной оболочки.
  {
    // Узнаем состояние клавиатуры.
    HWND Desktop = QueryDesktopWindow ();

    BYTE Keyboard_state[256]; bzero (Keyboard_state, sizeof (BYTE) * 256);
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 0);

    // Сбрасываем состояние Shift.
    Keyboard_state[VK_SHIFT] = 0;

    // Устанавливаем новое состояние клавиатуры.
    WinSetKeyboardStateTable (Desktop, Keyboard_state, 1);
  }

  // Возврат.
  return;
}

// ─── Выполняет "разгон" клавиатуры ───

VOID Controller_SpeedUpKeyboard (VOID)
{
  //
  // Этот метод надо вызывать в потоке расширителя, иначе "DosDevIOCtl" не работает.
  //

  // Устанавливаем соединение с драйвером клавиатуры.
  ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

  HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
  DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

  // Если драйвер открыт:
  if (Keyboard)
  {
    // Задаем состояние клавиатуры.
    RATEDELAY RateDelay = {0};
    RateDelay.usRate = Controller.Settings.Keyboard_rate;
    RateDelay.usDelay = 0;

    ULONG Length = sizeof (RateDelay); ULONG No_data = 0;
    DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETTYPAMATICRATE, &RateDelay, sizeof (RateDelay), &Length, NULL, 0, &No_data);

    DosClose (Keyboard); Keyboard = NULLHANDLE;
  }

  // Возврат.
  return;
}

// ─── Устанавливает переключатели на клавиатуре для окон VIO ───

VOID Controller_SetVIONumLock (VOID)
{
  //
  // Окна VIO принадлежат OS/2 Presentation Manager, но сами приложения исполняются
  // в глубине OS/2, и переключатели для них может установить только приложение VIO.
  //

  // Вызываем приложение.
  CHAR NumLock_exe[SIZE_OF_PATH] = ""; GetCurrentPath (NumLock_exe); strcat (NumLock_exe, "\\Control\\NumLock.exe");
  CHAR Error_string[1] = ""; RESULTCODES Return_codes;
  DosResetBuffer (-1); DosExecPgm (Error_string, sizeof (Error_string), EXEC_SYNC, NULL, NULL, &Return_codes, NumLock_exe);

  // Возврат.
  return;
}
