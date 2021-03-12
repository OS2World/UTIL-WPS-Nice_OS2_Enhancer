
// ─── Останавливает приложение ───

// Process_ID - приложение.
VOID TerminateProcess_KillProcess (PID Process_ID)
{
  // Проверяем, есть ли приложение.
  BYTE Process_is_exists = 1; if (DosVerifyPidTid (Process_ID, 1) != NO_ERROR) Process_is_exists = 0;

  // Если оно есть:
  if (Process_is_exists)
  {
    // Делаем попытку прибить его.
    APIRET Result = DosKillProcess (DKP_PROCESSTREE, Process_ID);

    // Если это сделать не удалось:
    if (Result != NO_ERROR)
    {
      // Посылаем в очередь окна рабочего стола сообщение WM_MARK. 
      // Приложение можно будет прибить во время его получения.
      HMQ Desktop_queue = WinQueryWindowULong (QueryDesktopWindow (), QWL_HMQ);
      WinPostQueueMsg (Desktop_queue, WM_MARK, (MPARAM) MRK_KILL_PROCESS, (MPARAM) Process_ID);
    }
  }

  // Возврат.
  return;
}
