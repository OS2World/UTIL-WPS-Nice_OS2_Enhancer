
// ─── Выполняет действие ───

VOID DialogWindow_ShowSettings (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // Отображаем настройки.
  BYTE Value = 0; if (Names.Task.Convert_names) Value = 1;
  WinSendDlgItemMsg (Window, ID_MAINWNDFORM_NAMES_CHECKBOX, BM_SETCHECK, MPFROMLONG (Value), 0);

  Value = 0; if (Names.Task.Revise_differences) Value = 1;
  WinSendDlgItemMsg (Window, ID_MAINWNDFORM_LONGNAMES_CHECKBOX, BM_SETCHECK, MPFROMLONG (Value), 0);

  Value = 0; if (Names.Task.Remove_images) Value = 1;
  WinSendDlgItemMsg (Window, ID_MAINWNDFORM_ICONS_CHECKBOX, BM_SETCHECK, MPFROMLONG (Value), 0);

  Value = 0; if (Names.Task.Remove_types) Value = 1;
  WinSendDlgItemMsg (Window, ID_MAINWNDFORM_TYPE_CHECKBOX, BM_SETCHECK, MPFROMLONG (Value), 0);

  Value = 0; if (Names.Task.Turn_OFF_ReadOnly) Value = 1;
  WinSendDlgItemMsg (Window, ID_MAINWNDFORM_READONLY_CHECKBOX, BM_SETCHECK, MPFROMLONG (Value), 0);

  Names.Settings.InputField_is_locked = 1;
  WinSetWindowText (WinWindowFromID (Window, ID_MAINWNDFORM_PATH_FIELD), Names.Task.Root_directory);
  Names.Settings.InputField_is_locked = 0;

  // Возврат.
  return;
}

