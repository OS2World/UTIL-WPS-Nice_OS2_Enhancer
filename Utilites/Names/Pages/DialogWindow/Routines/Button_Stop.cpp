
// ─── Выполняет действие ───

VOID DialogWindow_StopButton (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Если работает поток - завершаем его.
  if (Names.Processing)
  {
    // Поток должен быть завершен.
    Names.Processing = 0;

    // Сообщение.
    if (Names.Settings.Code_page == RUSSIAN)
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
    else
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
  }
  // А если поток не работает - закрываем окно.
  else
  {
    WinSendMsg (Window, WM_CLOSE, 0, 0);
  }

  // Возврат.
  return;
}

