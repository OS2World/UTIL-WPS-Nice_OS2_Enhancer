
// ─── Создает страницу для набора закладок ───

VOID Log_CreatePage (VOID)
{
  // Создаем страницу.
  Enhancer.Pages.Log->Window = WinCreateWindow (Enhancer.Client_window, WC_STATIC, NULL, WS_VISIBLE, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Создаем поля ввода.
  LitCreateLayout (&Enhancer.Pages.Log->Layout, Enhancer.Pages.Log->Window);

  {
    LTBRICK Field_brick; LitPrepareBrick (&Field_brick);
    Field_brick.hwnd = WinCreateWindow (Enhancer.Pages.Log->Window, WC_MLE, NULL, WS_VISIBLE | MLS_BORDER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Enhancer.Pages.Log->Window, HWND_TOP, Log.Settings.Field_ID, NULL, NULL);
    Field_brick.prpWidthInParent = LOG_LIST_WIDTH; Field_brick.prpHeightInParent = LOG_LIST_HEIGHT;
    WinSendMsg (Field_brick.hwnd, MLM_SETREADONLY, (MPARAM) 1, 0);
    SetCommonEnhancerFont (Field_brick.hwnd);
    LitJoinBrick (&(Enhancer.Pages.Log->Layout), &Field_brick);
  }

  // Возврат.
  return;
}

// ─── Ничего не делают ───

VOID Log_DoNothing (LONG Parameter = 0) { return; }
VOID Log_DoNothing (HINI Parameter = 0) { return; }
