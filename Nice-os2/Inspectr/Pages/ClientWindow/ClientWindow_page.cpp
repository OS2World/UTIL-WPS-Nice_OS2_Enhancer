
// ��� ��ࠡ��稪 ᮮ�饭�� ��� ���� ���

// ��⮪ �ਫ������ ��뢠�� WindowProc ��直� ࠧ, ����� ��� ���� ���� ᮮ�饭��.
// Window - ����, Message - ᮮ�饭��, *_parameter - �����, ����� ��।����� ����� � ᮮ�饭���.
MRESULT EXPENTRY Inspector_ClientWindowProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  switch (Message)
  {
    // �믮��塞 ����⢨� �� ᮧ����� ����.
    case WM_CREATE:
    {
      WinPostMsg (Window, MY_CREATE, 0, 0);
    }
    return 0;

    case MY_CREATE:
    {
      // ������ ��������� ���� �ਫ������.
      if (Inspector.Code_page == RUSSIAN) strcpy (Inspector.Frame_window_title, StrConst_RU_Title);
      else strcpy (Inspector.Frame_window_title, StrConst_EN_Title);

      WinSetWindowText (Inspector.Frame_window, Inspector.Frame_window_title);

      // ��⠭�������� ���⨭�� � ����� ���孥� 㣫� ����.
      WinSendMsg (Inspector.Frame_window, WM_SETICON, (MPARAM) WinLoadPointer (HWND_DESKTOP, NULLHANDLE, 1), 0);

      // ������ �ᯮ������� ����.
      {
        INT X_Screen = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN);
        INT Y_Screen = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN);

        INT Window_width  = X_Screen / 3; INT Window_position_X = (X_Screen - Window_width) / 2;
        INT Window_height = Y_Screen / 2; INT Window_position_Y = (Y_Screen - Window_height) / 2 + (Y_Screen - Window_height) / 4 / 2;

        WinSetWindowPos (Inspector.Frame_window, HWND_TOP, Window_position_X, Window_position_Y, Window_width, Window_height, SWP_ZORDER | SWP_MOVE | SWP_SIZE | SWP_NOADJUST);
        WinSetActiveWindow (HWND_DESKTOP, Inspector.Frame_window);
      }

      // ������塞 ��� � ᯨ᮪ ����.
      {
        SWCNTRL Task; HSWITCH Switch_handle = NULLHANDLE;

        bzero (&Task, sizeof (SWCNTRL));
        Task.hwnd = Inspector.Frame_window;
        Task.hwndIcon = (HPOINTER) WinSendMsg (Inspector.Frame_window, WM_QUERYICON, 0, 0);
        WinQueryWindowProcess (Inspector.Frame_window, &Task.idProcess, NULL);
        strcpy (Task.szSwtitle, Inspector.Frame_window_title);

        Task.uchVisibility = SWL_VISIBLE;
        Task.fbJump = SWL_JUMPABLE;

        Switch_handle = WinCreateSwitchEntry (Inspector.Application, &Task);
        WinChangeSwitchEntry (Switch_handle, &Task);
      }

      // ������� ���� ����� � ���� ࠡ�祩 ������.
      ClientWindow_CreatePage (Inspector.Client_window);
    }
    return 0;

    // ��।������ ���� �����.
    case MY_APPLY_LAYOUT:
    {
      LitApplyLayout (&Client_Window.Layout);
    }
    return 0;

    // ������� ��ன ��⮪.
    case MY_START_THREAD:
    {
      StartProcessing ();
    }
    return 0;

    // ����訢��� ����࠭�⢮ ����.
    case WM_PAINT:
    {
      RECT Rectangle = {0};
      HPS Presentation_space = WinBeginPaint (Window, 0, &Rectangle);

      if (Presentation_space)
      {
        LONG Color_table[256]; bzero (Color_table, sizeof (Color_table));
        GpiQueryLogColorTable (Presentation_space, 0, 0, 256, Color_table);

        LONG Color_index = (256 - 1);
        WinQueryPresParam (Window, PP_BACKGROUNDCOLOR, 0, NULL, sizeof (Color_table[Color_index]), &Color_table[Color_index], QPF_NOINHERIT);
        GpiCreateLogColorTable (Presentation_space, 0, LCOLF_CONSECRGB, 0, 256, Color_table);

        WinFillRect (Presentation_space, &Rectangle, Color_index);
        WinEndPaint (Presentation_space);
      }
    }
    return 0;

    // ����頥� ���� ࠬ��, �� ᮤ�ন��� ���� ࠡ�祩 ������ ����訢��� �� ᫥���.
    case WM_ERASEBACKGROUND:
    return (MPARAM) 0;

    // �믮��塞 ����⢨� �� ����⨨ �� ������ ������� ����.
    case WM_CLOSE:
    {
      // ���ࠥ� ���� �ਫ������ �� ᯨ᪠ ����.
      WinRemoveSwitchEntry (WinQuerySwitchHandle (Inspector.Frame_window, 0));

      // ��।��� ᮮ�饭�� ��ࠡ��稪�.
      WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
    }
    return 0;
  }

  // ������.
  return WinDefWindowProc (Window, Message, First_parameter, Second_parameter);
}
