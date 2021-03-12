
// ─── Вызывает драйвер клавиатуры ───

BYTE KbdLocks_CallKeyboardDriverForToggleCAD (VOID)
{
  //
  // Как и SetNumLock, этот метод можно вызывать только в потоке расширителя, так как
  // метод DosDevIOCtl получает доступ к устройствам только если он вызван приложением
  // для Presentation Manager. В обработчиках событий он не сможет работать правильно,
  // если окно создано приложением, которое запущено по команде "Detach".
  //

  // Вызываем драйвер.
  HOTKEY Keyboard_parameters = { 0, 0, 0, 0xFFFF };

  ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW;
  ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYWRITE | OPEN_ACCESS_READWRITE;

  HFILE Keyboard = NULLHANDLE; ULONG Report = 0;
  DosOpen ("\\Dev\\Kbd$", &Keyboard, &Report, 0, 0, Action, Mode, 0);

  ULONG Length = sizeof (Keyboard_parameters); ULONG No_data = 0;
  APIRET Result = DosDevIOCtl (Keyboard, IOCTL_KEYBOARD, KBD_SETSESMGRHOTKEY, &Keyboard_parameters, Length, &Length, NULL, 0, &No_data);

  DosClose (Keyboard); Keyboard = NULLHANDLE;

  // Если произошла ошибка - возвращаем 0.
  if (Result != NO_ERROR) return 0;

  // Все в порядке, возврат.
  return 1;
}

// ─── Разрешает или запрещает Ctrl + Alt + Del ───

// Allow_CAD - разрешить или запретить клавиши.
VOID KbdLocks_SetCtrlAltDel (BYTE Allow_CAD)
{
  // Ctrl + Alt + Del можно только переключать.
  BYTE Toggle_CAD = 0;

  // Если клавиши включены - их можно отключить.
  if (!KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) if (!Allow_CAD) Toggle_CAD = 1;

  // Если клавиши выключены - их можно включить.
  if (KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) if (Allow_CAD) Toggle_CAD = 1;

  // Переключаем Ctrl + Alt + Del.
  if (Toggle_CAD)
  {
    // Переключаем клавиши и запоминаем новое состояние.
    if (KbdLocks_CallKeyboardDriverForToggleCAD ())
    {
      if (KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled) KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled = 0;
      else KbdLocks.RTSettings.Ctrl_Alt_Del_is_disabled = 1;
    }
  }

  // Возврат.
  return;
}
