
// ─── Возвращает окно поля ввода ───

HWND Log_LogWindow (VOID)
{
  // Возвращаем окно.
  return WinWindowFromID (Enhancer.Pages.Log->Window, Log.Settings.Field_ID);
}

// ─── Проверяет, было ли добавлено в поле ввода хоть одно сообщение ───

BYTE Log_LogIsEmpty (VOID)
{
  // Проверяем содержимое поля ввода.
  if (Log.RTSettings.Field_is_changed) return 0;

  // Возврат.
  return 1;
}

// ─── Добавляет сообщение в поле ввода ───

// Message - сообщение.
VOID Log_PrintLogMessage (PCHAR Message)
{
  // Отводим память для текста.
  PCHAR Window_text = NULL; INT Length = 65536;
  if (DosAllocMem ((PPVOID) &Window_text, Length, PAG_ALLOCATE) != NO_ERROR) return;

  // Узнаем текст в поле ввода.
  HWND Field = Log_LogWindow (); WinQueryWindowText (Field, Length, Window_text);

  // Добавляем сообщение в поле ввода.
  strcat (Window_text, Message); strcat (Window_text, "\n");

  WinEnableWindowUpdate (Field, 0);
  WinSetWindowText (Field, Window_text);
  WinEnableWindowUpdate (Field, 1);

  // Освобождаем память.
  DosFreeMem (Window_text); Window_text = NULL;

  // Запоминаем, что поле ввода изменено.
  Log.RTSettings.Field_is_changed = 1;

  // Возврат.
  return;
}
