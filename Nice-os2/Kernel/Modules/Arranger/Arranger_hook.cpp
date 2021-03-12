
// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ArrangerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // Выравниваем окна по середине экрана. Это сообщение посылается в окно в SendMsgHook ()
  // при обработке сообщения о том, что оно будет показано. Очередь для этого использовать
  // не получилось - мало места для параметров, можно передать всего 2 значения LONG.
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
        // Посылаем сообщение в поток.
        LONG Action = (LONG) Message->mp2; HWND Frame_window = Message->hwnd;
        WinPostQueueMsg (Enhancer.Modules.Arranger->Message_queue, Action, (MPARAM) Frame_window, 0);
      }
  }

  // Возврат.
  return;
}

// ─── Слежение за сообщениями ───

// Все переменные - внешние.
VOID ArrangerSendMsgHook (HAB Application, PSMHSTRUCT Message)
{
  // Выравниваем окна по середине экрана.
  if (Arranger.Settings.Arrange_VIO_windows     || 
      Arranger.Settings.Arrange_WindowList      || 
      Arranger.Settings.Arrange_WPS_windows     || 
      Arranger.Settings.Arrange_Browser_windows || 
      Arranger.Settings.Arrange_Network_windows ||
      Arranger.Settings.Arrange_XWP_windows)
  {
    if (!ArrangerMustBeDisabled ()) if (!RoomsChangeIsInProcess ())
    {
      // Выбираем сообщение в зависимости от того, что происходит.
      LONG Mark = 0; HWND Frame_window = NULLHANDLE;

      // Выравниваем окна. Это надо делать когда окно рамки становится видимым.
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

      // Выравниваем список окон после того, как пользователь скрывает его.
      if (!Mark) if (Arranger.Settings.Arrange_WindowList)
       if (TopFrameWindowIsInactivating (Message))
       {
         Frame_window = QueryFrameWindow (Message->hwnd);
         if (IsWinListWindow (Frame_window)) if (!MouseIsUnderPressure ()) Mark = SM_ARRANGE_WIN_LIST;
       }

      // Выравниваем окна FC/2, когда они меняют свое расположение:
      if (!Mark) if (Arranger.Settings.Arrange_VIO_windows) if (Arranger.Settings.Arrange_FC2_windows)
       if (TopFrameWindowIsMoving (Message))
       {
         Frame_window = QueryFrameWindow (Message->hwnd);
         if (IsVIOWindow (Frame_window)) if (WindowIsCreatedBy (APP_FC, Frame_window))
           if (!VIOFontMustBeChanged (Frame_window)) Mark = SM_ARRANGE_FC2;
       }

      // Если окно надо выравнивать:
      if (Mark)
      {
        // Узнаем текуще время и время выравнивания окна, если оно было.
        ULONG Time = 0; DosQuerySysInfo (QSV_MS_COUNT, QSV_MS_COUNT, (PULONG) &Time, sizeof (Time));
        ULONG Arranged_at = 0; FindProperty (Frame_window, PRP_TIME_OF_ARRANGE, &Arranged_at);

        // Проверяем, сколько времени прошло.
        // Список окон и текстовые окна в увеличенном виде выравниваем в любом случае.
        BYTE Arrange_window = 0;
        if (Arranged_at == 0) Arrange_window = 1;
        if (Time > Arranged_at && Time - Arranged_at < ARRANGER_DELAY_VIO) Arrange_window = 1;
        if (Mark == SM_ARRANGE_WIN_LIST) Arrange_window = 1;
        if (Mark == SM_ARRANGE_VIO)
        {
          SWP Window_placement = {0}; WinQueryWindowPos (Frame_window, &Window_placement);
          if (Window_placement.fl & SWP_MAXIMIZE) Arrange_window = 1;
        }

        // Если окно действительно надо выравнивать:
        if (Arrange_window)
        {
          // Запоминаем время выравнивания окна (для окон FC/2 этих действий может быть несколько).
          SetProperty (Frame_window, PRP_TIME_OF_ARRANGE, &Time);

          // Посылаем в окно сообщение WM_MARK. Когда оно будет получено, окно можно будет выравнивать.
          WinPostMsg (Frame_window, WM_MARK, (MPARAM) MRK_ARRANGE_WINDOW, (MPARAM) Mark);
        }
      }
    }
  }

  // Возврат.
  return;
}
