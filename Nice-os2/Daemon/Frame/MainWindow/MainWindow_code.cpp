
// ─── Окно приложения ───

MRESULT EXPENTRY Enhancer_MainWindowProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Смотрим на пришедшее сообщение и выполняем действие.
  switch (Message)
  {
    // Создание окна:
    case WM_CREATE:
    {
      // Сообщаем окну о том, какие действия надо еще выполнить.
      WinPostMsg (Window, SM_HIDE_ENHANCER, 0, 0);
    }
    return 0;

    // Сокрытие окна:
    case SM_HIDE_ENHANCER:
    {
      // Прячем окно за пределы экрана.
      HWND Desktop = QueryDesktopWindow ();
      INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
      INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

      WinSetWindowPos (Enhancer.Frame_window, NULLHANDLE, X_Screen * (-10), Y_Screen * (-10), 0, 0, SWP_MOVE | SWP_SIZE | SWP_NOADJUST);
      WinShowWindow (Enhancer.Frame_window, 0);
    }
    return 0;

    // Если требуется прочесть настройки и передать их расширителю:
    case SM_RECEIVE_SETTINGS:
    {
      // Если вызван расширитель:
      if (Enhancer.Enhancer_mode)
      {
        // Вызываем его, чтобы он прочел настройки.
        // Этот метод выполняется внутри Nice-os2.dll, но все, что он делает, присоединяется к данному приложению.
        LONG Update_windows = (LONG) First_parameter;
        LONG Arrange_windows = (LONG) Second_parameter;

        NiceReadSettings (Update_windows, Arrange_windows);
      }
    }
    return 0;

    // Если требуется прочесть список приложений и передать его расширителю:
    case SM_RECEIVE_REPOSITORY:
    {
      // Если вызван расширитель:
      if (Enhancer.Enhancer_mode)
      {
        // Вызываем его, чтобы он прочел список приложений.
        NiceReadRepository ();
      }
    }
    return 0;

    // Если требуется узнать что-нибудь для окна настроек во время работы:
    case SM_SCAN_LOGON_DIALOG:
    {
      if (Enhancer.Enhancer_mode) NiceScanLogonDialog ((HWND) First_parameter);
    }
    return 0;

    case SM_SCAN_INCOMPLETE_DIALOG:
    {
      if (Enhancer.Enhancer_mode) NiceScanIncompleteDialog ((HWND) First_parameter);
    }
    return 0;

    case SM_SCAN_MESSAGE_DIALOG:
    {
      if (Enhancer.Enhancer_mode) NiceScanMessageDialog ((HWND) First_parameter);
    }
    return 0;

    // Если расширитель завершается и сообщает, что все в порядке:
    case LM_REPORT_ENHANCER_IS_TERMINATED:
    {
      // Запоминаем, что все в порядке.
      Enhancer.Enhancer_is_terminated_normally = 1;
    }
    return 0;

    // Рисование окна:
    case WM_PAINT:
    {
      // Закрашиваем пространство окна.
      RECT Rectangle = {0};
      HPS Presentation_space = WinBeginPaint (Window, 0, &Rectangle);
      WinFillRect (Presentation_space, &Rectangle, CLR_PALEGRAY);
      WinEndPaint (Presentation_space);
    }
    return 0;
  }

  // Возврат.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
