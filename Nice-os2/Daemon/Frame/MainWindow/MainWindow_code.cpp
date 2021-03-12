
// ��� ���� �ਫ������ ���

MRESULT EXPENTRY Enhancer_MainWindowProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // ����ਬ �� ��襤襥 ᮮ�饭�� � �믮��塞 ����⢨�.
  switch (Message)
  {
    // �������� ����:
    case WM_CREATE:
    {
      // ����頥� ���� � ⮬, ����� ����⢨� ���� �� �믮�����.
      WinPostMsg (Window, SM_HIDE_ENHANCER, 0, 0);
    }
    return 0;

    // �����⨥ ����:
    case SM_HIDE_ENHANCER:
    {
      // ���祬 ���� �� �।��� �࠭�.
      HWND Desktop = QueryDesktopWindow ();
      INT X_Screen = WinQuerySysValue (Desktop, SV_CXSCREEN);
      INT Y_Screen = WinQuerySysValue (Desktop, SV_CYSCREEN);

      WinSetWindowPos (Enhancer.Frame_window, NULLHANDLE, X_Screen * (-10), Y_Screen * (-10), 0, 0, SWP_MOVE | SWP_SIZE | SWP_NOADJUST);
      WinShowWindow (Enhancer.Frame_window, 0);
    }
    return 0;

    // �᫨ �ॡ���� ������ ����ன�� � ��।��� �� ����⥫�:
    case SM_RECEIVE_SETTINGS:
    {
      // �᫨ �맢�� ����⥫�:
      if (Enhancer.Enhancer_mode)
      {
        // ��뢠�� ���, �⮡� �� ��祫 ����ன��.
        // ��� ��⮤ �믮������ ����� Nice-os2.dll, �� ��, �� �� ������, ��ᮥ������� � ������� �ਫ������.
        LONG Update_windows = (LONG) First_parameter;
        LONG Arrange_windows = (LONG) Second_parameter;

        NiceReadSettings (Update_windows, Arrange_windows);
      }
    }
    return 0;

    // �᫨ �ॡ���� ������ ᯨ᮪ �ਫ������ � ��।��� ��� ����⥫�:
    case SM_RECEIVE_REPOSITORY:
    {
      // �᫨ �맢�� ����⥫�:
      if (Enhancer.Enhancer_mode)
      {
        // ��뢠�� ���, �⮡� �� ��祫 ᯨ᮪ �ਫ������.
        NiceReadRepository ();
      }
    }
    return 0;

    // �᫨ �ॡ���� 㧭��� ��-����� ��� ���� ����஥� �� �६� ࠡ���:
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

    // �᫨ ����⥫� �����蠥��� � ᮮ�頥�, �� �� � ���浪�:
    case LM_REPORT_ENHANCER_IS_TERMINATED:
    {
      // ����������, �� �� � ���浪�.
      Enhancer.Enhancer_is_terminated_normally = 1;
    }
    return 0;

    // ��ᮢ���� ����:
    case WM_PAINT:
    {
      // ����訢��� ����࠭�⢮ ����.
      RECT Rectangle = {0};
      HPS Presentation_space = WinBeginPaint (Window, 0, &Rectangle);
      WinFillRect (Presentation_space, &Rectangle, CLR_PALEGRAY);
      WinEndPaint (Presentation_space);
    }
    return 0;
  }

  // ������.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
