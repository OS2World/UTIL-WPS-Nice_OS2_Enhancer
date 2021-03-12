
// ��� �믮���� ����⢨� ���

VOID DialogWindow_StopButton (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter, ULONG WM_Control_Window_ID = 0)
{
  // �᫨ ࠡ�⠥� ��⮪ - �����蠥� ���.
  if (Names.Processing)
  {
    // ��⮪ ������ ���� �����襭.
    Names.Processing = 0;

    // ����饭��.
    if (Names.Settings.Code_page == RUSSIAN)
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_RU_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
    else
     WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, StrConst_EN_Thread_stopped, Names.Frame_window_title, NULLHANDLE, NULLHANDLE);
  }
  // � �᫨ ��⮪ �� ࠡ�⠥� - ����뢠�� ����.
  else
  {
    WinSendMsg (Window, WM_CLOSE, 0, 0);
  }

  // ������.
  return;
}

