
// ─── Изменяет значение приоритета для приложения ───

// Frame_window - окно приложения, Class и Delta - значения приоритета.
VOID Priority_SetPriorityLevel (HWND Frame_window, LONG Class, LONG Delta)
{
  // Если это окно создано самой оболочкой Presentation Manager - возврат.
  if (IsPMShellAuxiliaryWindow (Frame_window)) return;

  // Узнаем приложение, создавшее окно.
  // Для окон VIO здесь возвращается их настоящий PID, а не PID окна (оно создаётся оболочкой PM).
  PID Process_ID = QueryWindowRealProcessID (Frame_window);

  // Пробуем изменить приоритет на месте.
  APIRET Result = NO_ERROR; if (Process_ID != 0) Result = DosSetPriority (PRTYS_PROCESSTREE, Class, Delta, Process_ID);

  // Если это сделать не удалось:
  if (Result != NO_ERROR)
  {
    // Запоминаем значения приоритета для окна.
    SetProperty (Frame_window, PRP_PRIORITY_CLASS, &Class);
    SetProperty (Frame_window, PRP_PRIORITY_DELTA, &Delta);

    // Узнаем окно рабочего стола.
    HWND Desktop = QueryDesktopWindow ();

    // Посылаем в очередь окна рабочего стола сообщение WM_MARK. Приоритет можно будет изменить во время его получения.
    HMQ Desktop_queue = WinQueryWindowULong (Desktop, QWL_HMQ);
    WinPostQueueMsg (Desktop_queue, WM_MARK, (MPARAM) MRK_SET_PRIORITY, (MPARAM) Frame_window);

    // Посылаем такое же сообщение в очередь окна. Текстовые окна используют ту же очередь, что и окно рабочего стола, поэтому второй раз посылать им сообщение не надо.
    HMQ Window_queue = WinQueryWindowULong (Frame_window, QWL_HMQ);
    if (Window_queue != Desktop_queue) WinPostQueueMsg (Window_queue, WM_MARK, (MPARAM) MRK_SET_PRIORITY, (MPARAM) Frame_window);
  }

  // Возврат.
  return;
}
