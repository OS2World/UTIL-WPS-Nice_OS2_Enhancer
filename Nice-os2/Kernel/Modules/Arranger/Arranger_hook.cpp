
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ArrangerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // ��ࠢ������ ���� �� �।��� �࠭�. �� ᮮ�饭�� ���뫠���� � ���� � SendMsgHook ()
  // �� ��ࠡ�⪥ ᮮ�饭�� � ⮬, �� ��� �㤥� ��������. ��।� ��� �⮣� �ᯮ�짮����
  // �� ����稫��� - ���� ���� ��� ��ࠬ��஢, ����� ��।��� �ᥣ� 2 ���祭�� LONG.
  if (Arranger.Settings.Arrange_VIO_windows     || 
      Arranger.Settings.Arrange_WindowList      || 
      Arranger.Settings.Arrange_WPS_windows     || 
      Arranger.Settings.Arrange_Browser_windows || 
      Arranger.Settings.Arrange_Network_windows ||
      Arranger.Settings.Arrange_XWP_windows)
  { 
    if (Message->msg == WM_MARK) 
     if (Message->mp1 == (MPARAM) MRK_ARRANGE_WINDOW)
      if (IsFrameWindow (Message->hwnd))
      {
        // ���뫠�� ᮮ�饭�� � ��⮪.
        LONG Action = (LONG) Message->mp2; HWND Frame_window = Message->hwnd;
        WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, Action, (MPARAM) Frame_window, 0);
      }
  }

  // ������.
  return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ArrangerSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // ��ࠢ������ ���� �� �।��� �࠭�.
  if (Arranger.Settings.Arrange_VIO_windows     || 
      Arranger.Settings.Arrange_WindowList      || 
      Arranger.Settings.Arrange_WPS_windows     || 
      Arranger.Settings.Arrange_Browser_windows || 
      Arranger.Settings.Arrange_Network_windows ||
      Arranger.Settings.Arrange_XWP_windows)
  {
    if (!ArrangerMustBeDisabled ()) if (!RoomsChangeIsInProcess ())
    {
      // �롨ࠥ� ᮮ�饭�� � ����ᨬ��� �� ⮣�, �� �ந�室��.
      LONG Mark = 0; HWND Frame_window = NULLHANDLE;

      // ��ࠢ������ ����. �� ���� ������ ����� ���� ࠬ�� �⠭������ ������.
      BYTE Top_frame_window_is_showing = TopFrameWindowIsShowing (Message);
      if (Top_frame_window_is_showing) Frame_window = QueryFrameWindow (Message->hwnd);

      if (!Mark) if (Arranger.Settings.Arrange_VIO_windows)
       if (Top_frame_window_is_showing)
        if (IsVIOWindow (Frame_window))
         if (!VIOFontMustBeChanged (Frame_window))
          Mark = SM_ARRANGE_VIO;

      if (!Mark) if (Arranger.Settings.Arrange_WPS_windows)
       if (Top_frame_window_is_showing) 
       {
         if (IsFolderWindow (Frame_window)) Mark = SM_ARRANGE_WPS;
       }

      if (!Mark) if (Arranger.Settings.Arrange_Browser_windows)
       if (Top_frame_window_is_showing)
       {
         if (WindowIsUsedTo (DO_BROWSE_WEB_PAGES, Frame_window)) Mark = SM_ARRANGE_BROWSER;
         if (WindowIsUsedTo (DO_BROWSE_IPF_HELP, Frame_window)) Mark = SM_ARRANGE_IPF_HELP;
       }

      if (!Mark) if (Arranger.Settings.Arrange_Network_windows)
       if (Top_frame_window_is_showing)
       {
         if (IsSafeFireWindow (Frame_window)) if (WindowIsCreatedBy (APP_SAFEFIRE, Frame_window))
          Mark = SM_ARRANGE_NW_DIALER;
       }

      if (!Mark) if (Arranger.Settings.Arrange_XWP_windows)
       if (Top_frame_window_is_showing)
       {
         if (IsXWPPagerWindow (Frame_window)) Mark = SM_ARRANGE_XWP_PAGER;
       }

      // ��ࠢ������ ᯨ᮪ ���� ��᫥ ⮣�, ��� ���짮��⥫� ��뢠�� ���.
      if (!Mark) if (Arranger.Settings.Arrange_WindowList)
       if (TopFrameWindowIsInactivating (Message))
       {
         Frame_window = QueryFrameWindow (Message->hwnd);
         if (IsWinListWindow (Frame_window)) if (!MouseIsUnderPressure ()) Mark = SM_ARRANGE_WIN_LIST;
       }

      // ��ࠢ������ ���� FC/2, ����� ��� ������ ᢮� �ᯮ�������:
      if (!Mark) if (Arranger.Settings.Arrange_VIO_windows) if (Arranger.Settings.Arrange_FC2_windows)
       if (TopFrameWindowIsMoving (Message))
       {
         Frame_window = QueryFrameWindow (Message->hwnd);
         if (IsVIOWindow (Frame_window)) if (WindowIsCreatedBy (APP_FC, Frame_window))
           if (!VIOFontMustBeChanged (Frame_window)) Mark = SM_ARRANGE_FC2;
       }

      // �᫨ ���� ���� ��ࠢ������:
      if (Mark)
      {
        // ������ ⥪�� �६� � �६� ��ࠢ������� ����, �᫨ ��� �뫮.
        ULONG Time = 0; DosQuerySysInfo (QSV_MS_COUNT, QSV_MS_COUNT, (PULONG) &Time, sizeof (Time));
        ULONG Arranged_at = 0; FindProperty (Frame_window, PRP_TIME_OF_ARRANGE, &Arranged_at);

        // �஢��塞, ᪮�쪮 �६��� ��諮.
        // ���᮪ ���� � ⥪�⮢� ���� � 㢥��祭��� ���� ��ࠢ������ � �� ��砥.
        BYTE Arrange_window = 0;
        if (Arranged_at == 0) Arrange_window = 1;
        if (Time > Arranged_at && Time - Arranged_at < ARRANGER_DELAY_VIO) Arrange_window = 1;
        if (Mark == SM_ARRANGE_WIN_LIST) Arrange_window = 1;
        if (Mark == SM_ARRANGE_VIO)
        {
          SWP Window_placement = {0}; WinQueryWindowPos (Frame_window, &Window_placement);
          if (Window_placement.fl & SWP_MAXIMIZE) Arrange_window = 1;
        }

        // �᫨ ���� ����⢨⥫쭮 ���� ��ࠢ������:
        if (Arrange_window)
        {
          // ���������� �६� ��ࠢ������� ���� (��� ���� FC/2 ��� ����⢨� ����� ���� ��᪮�쪮).
          SetProperty (Frame_window, PRP_TIME_OF_ARRANGE, &Time);

          // ���뫠�� � ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� ��ࠢ������.
          WinPostMsg (Frame_window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) Mark);
        }
      }
    }
  }

  // ������.
  return;
}
