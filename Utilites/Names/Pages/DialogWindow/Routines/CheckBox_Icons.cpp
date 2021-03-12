
// ─── Выполняет действие ───

VOID DialogWindow_IconsCheckBox (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Узнаем, выбрана ли кнопка.
  ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

  // Переключаем настройки.
  if (Button_is_checked) Names.Task.Remove_images = 0;
  else Names.Task.Remove_images = 1;

  // Запоминаем, что настройки изменены.
  Names.Settings.Settings_are_changed = 1;

  // Возврат.
  return;
}

