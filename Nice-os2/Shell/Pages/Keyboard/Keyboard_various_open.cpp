
// ─── Создает страницу для набора закладок ───

VOID Keyboard_Various_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Keyboard_various;

  // Создаем страницу.
  CHAR Page_class_name[] = "Keyboard_Various_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Keyboard_Various_WndProc, 0, 0);
  Page->Window = WinCreateWindow (Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Задаем шрифт.
  SetCommonEnhancerFont (Page->Window);

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  // Создаем поля ввода.
  LitCreateLayout (&Page->Layout, Page->Window);

  CreateCtlButtons (Page);

  {
    for (INT Count = 0; Count < 3; Count ++)
    {
      LTBRICK Space_brick; LitPrepareBrick (&Space_brick);
      Space_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
      Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
      LitJoinBrick (&(Page->Layout), &Space_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.F3, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_F3);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_F3);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.Alt_F9, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_Alt_F9);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_Alt_F9);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.WPS_Enter, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_WPS_Enter);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_WPS_Enter);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.Ctrl_CV, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_Clipboard);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_Clipboard);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Space_brick; LitPrepareBrick (&Space_brick);
    Space_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Space_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.NumKeys, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_NumKeys);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_NumKeys);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.Keep_NumLock, NULL, NULL);
    Checkbox_brick.prpWidthInParent = CBCB_TEXT_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_various_Keep_NumLock);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_various_Keep_NumLock);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LTBRICK Combobox_brick; LitPrepareBrick (&Combobox_brick);
    Combobox_brick.hwnd = WinCreateWindow (Page->Window, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Various.Settings.NumLock_cbox, NULL, NULL);
    Combobox_brick.prpWidthInParent = CBCB_LIST_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
    LitJoinBrick (&(Page->Layout), &Combobox_brick);

    LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LitCompleteRow (&(Page->Layout));
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_Keyboard_various_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_Keyboard_various_Prompt);

  CompleteCreation (Page);

  // Заполняем список.
  {
    // Задаем строки.
    INT Max_strings = 2; PCHAR Strings[2]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    if (Code_page == RUSSIAN)
    {
      strcpy (Strings[0], StrConst_RU_Pages_Keyboard_various_KeepON);
      strcpy (Strings[1], StrConst_RU_Pages_Keyboard_various_KeepOFF);
    }
    else
    {
      strcpy (Strings[0], StrConst_EN_Pages_Keyboard_various_KeepON);
      strcpy (Strings[1], StrConst_EN_Pages_Keyboard_various_KeepOFF);
    }

    // Передаем строки окну списка.
    {
      BYTE Turn_Num_Lock = Keyboard_Various.Settings.Turn_Num_Lock;
      for (Count = 0; Count < Max_strings; Count ++) WinSendDlgItemMsg (Page->Window, Keyboard_Various.Settings.NumLock_cbox, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count]));
      Keyboard_Various.Settings.Turn_Num_Lock = Turn_Num_Lock;
    }

    // Освобождаем память.
    for (Count = 0; Count < Max_strings; Count ++) { DosFreeMem (Strings[Count]); Strings[Count] = NULL; }
  }

  // Возврат.
  return;
}

