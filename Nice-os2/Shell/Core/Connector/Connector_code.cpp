
// ─── Предлагает расширителю прочесть настройки ───

// Вызывается при изменении настроек пользователем.
// Update_windows - надо ли обновить все окна.
VOID Connector_NiceReadSettings (BYTE Update_windows = 0, BYTE Arrange_windows = 0)
{
  // Посылаем сообщение.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_RECEIVE_SETTINGS, (MPARAM) Update_windows, (MPARAM) Arrange_windows);

  // Возврат.
  return;
}

// ─── Предлагает расширителю прочесть список приложений ───

// Вызывается при изменении списка приложений.
VOID Connector_NiceReadRepository (VOID)
{
  // Посылаем сообщение.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_RECEIVE_REPOSITORY, 0, 0);

  // Возврат.
  return;
}

// ─── Предлагает расширителю собрать сведения об окне ввода пароля ───

// Window - окно ввода пароля.
VOID Connector_NiceScanLogonDialog (HWND Window)
{
  // Посылаем сообщение.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_LOGON_DIALOG, (MPARAM) Window, 0);

  // Возврат.
  return;
}

// ─── Предлагает расширителю собрать сведения об окне диалога ───

// Window - окно диалога.
VOID Connector_NiceScanIncompleteDialog (HWND Window)
{
  // Посылаем сообщение.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_INCOMPLETE_DIALOG, (MPARAM) Window, 0);

  // Возврат.
  return;
}

// ─── Предлагает расширителю собрать сведения об окне сообщения ───

// Window - окно сообщения.
VOID Connector_NiceScanMessageDialog (HWND Window)
{
  // Посылаем сообщение.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_MESSAGE_DIALOG, (MPARAM) Window, 0);

  // Возврат.
  return;
}
