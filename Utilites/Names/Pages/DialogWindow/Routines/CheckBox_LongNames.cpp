
// ��� �믮���� ����⢨� ���

VOID DialogWindow_LongNamesCheckBox (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // ������, ��࠭� �� ������.
  ULONG Button_is_checked = (ULONG) WinSendDlgItemMsg (Window, WM_Control_Window_ID, BM_QUERYCHECK, 0, 0);

  // ��४��砥� ����ன��.
  if (Button_is_checked) Names.Task.Revise_differences = 0;
  else Names.Task.Revise_differences = 1;

  // ����������, �� ����ன�� ��������.
  Names.Settings.Settings_are_changed = 1;

  // ������.
  return;
}

