
// ─── Выравнивает некоторые окна ───

// Desktop - окно рабочего стола.
VOID ArrangeSomeWindows (HWND Desktop)
{
  // Перебираем окна в окне рабочего стола.
  HENUM Enumeration = WinBeginEnumWindows (Desktop); HWND Window = NULLHANDLE;
  while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
  {
    // Некоторые окна надо выравнивать при запуске расширителя.
    if (Arranger.Settings.Arrange_Network_windows)
     if (IsSafeFireWindow (Window)) if (WindowIsCreatedBy (APP_SAFEFIRE, Window))
     {
       // Посылаем сообщение в поток.
       WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_NW_DIALER, (MPARAM) Window, 0);
     }

    if (Arranger.Settings.Arrange_XWP_windows)
     if (IsXWPPagerWindow (Window))
     {
       // Посылаем сообщение в поток.
       WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, SM_ARRANGE_XWP_PAGER, (MPARAM) Window, 0);
     }
  }
  WinEndEnumWindows (Enumeration);

  // Возврат.
  return;
}