
// ─── Создает страницу для набора закладок ───

VOID Scrolling_Settings_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Scrolling_settings;

  // Создаем страницу.
  CHAR Page_class_name[] = "Scrolling_Settings_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Scrolling_Settings_WndProc, 0, 0);
  Page->Window = WinCreateWindow (Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Задаем шрифт.
  SetCommonEnhancerFont (Page->Window);

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  // Создаем поля ввода.
  LitCreateLayout (&Page->Layout, Page->Window);

  CreateCtlButtons (Page);

  {
    LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LTBRICK Combobox_brick; LitPrepareBrick (&Combobox_brick);
    Combobox_brick.hwnd = WinCreateWindow (Page->Window, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID, NULL, NULL);
    Combobox_brick.prpWidthInParent = LTM_COMBOBOX_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
    LitJoinBrick (&(Page->Layout), &Combobox_brick);

    LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Mouse_pointer_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Scrolling_settings_Mouse_pointer);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Scrolling_settings_Mouse_pointer);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LTBRICK Combobox_brick; LitPrepareBrick (&Combobox_brick);
    Combobox_brick.hwnd = WinCreateWindow (Page->Window, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID, NULL, NULL);
    Combobox_brick.prpWidthInParent = LTM_COMBOBOX_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
    LitJoinBrick (&(Page->Layout), &Combobox_brick);

    LitPrepareBrick (&Rectangle_brick);
    Rectangle_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
    Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Rectangle_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Mouse_scrolling_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Scrolling_settings_Mouse_scrolling);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Scrolling_settings_Mouse_scrolling);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Keyboard_scrolling_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Scrolling_settings_Keyboard_scrolling);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Scrolling_settings_Keyboard_scrolling);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Settings.Settings.Smooth_scrolling_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Scrolling_settings_Smooth_scrolling);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Scrolling_settings_Smooth_scrolling);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_Scrolling_settings_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_Scrolling_settings_Prompt);

  CompleteCreation (Page);

  // Заполняем первый список.
  {
    // Задаем строки.
    INT Max_strings = 3; PCHAR Strings[3]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    if (Code_page == RUSSIAN)
    {
      strcpy (Strings[0], StrConst_RU_Pages_Scrolling_settings_Mouse_action_name_1);
      strcpy (Strings[1], StrConst_RU_Pages_Scrolling_settings_Mouse_action_name_2);
      strcpy (Strings[2], StrConst_RU_Pages_Scrolling_settings_Mouse_action_name_3);
    }
    else
    {
      strcpy (Strings[0], StrConst_EN_Pages_Scrolling_settings_Mouse_action_name_1);
      strcpy (Strings[1], StrConst_EN_Pages_Scrolling_settings_Mouse_action_name_2);
      strcpy (Strings[2], StrConst_EN_Pages_Scrolling_settings_Mouse_action_name_3);
    }

    // Передаем строки окну списка.
    {
      HWND ComboBox_window = WinWindowFromID (Page->Window, Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID);

      BYTE Image_dragging = Scroller.Settings.Image_dragging;
      for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count])); }
      Scroller.Settings.Image_dragging = Image_dragging;
    }

    // Освобождаем память.
    for (Count = 0; Count < Max_strings; Count ++) 
    { 
      DosFreeMem (Strings[Count]); Strings[Count] = NULL; 
    }
  }

  // Заполняем второй список.
  {
    // Задаем строки.
    INT Max_strings = 4; PCHAR Strings[4]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    if (Code_page == RUSSIAN)
    {
      strcpy (Strings[0], StrConst_RU_Pages_Scrolling_settings_Mouse_pointer_name_1);
      strcpy (Strings[1], StrConst_RU_Pages_Scrolling_settings_Mouse_pointer_name_2);
      strcpy (Strings[2], StrConst_RU_Pages_Scrolling_settings_Mouse_pointer_name_3);
      strcpy (Strings[3], StrConst_RU_Pages_Scrolling_settings_Mouse_pointer_name_4);
    }
    else
    {
      strcpy (Strings[0], StrConst_EN_Pages_Scrolling_settings_Mouse_pointer_name_1);
      strcpy (Strings[1], StrConst_EN_Pages_Scrolling_settings_Mouse_pointer_name_2);
      strcpy (Strings[2], StrConst_EN_Pages_Scrolling_settings_Mouse_pointer_name_3);
      strcpy (Strings[3], StrConst_EN_Pages_Scrolling_settings_Mouse_pointer_name_4);
    }

    // Передаем строки окну списка.
    {
      HWND ComboBox_window = WinWindowFromID (Page->Window, Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID);

      INT Number_of_pointer = Scroller.Settings.Number_of_pointer;
      for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count])); }
      Scroller.Settings.Number_of_pointer = Number_of_pointer;
    }

    // Освобождаем память.
    for (Count = 0; Count < Max_strings; Count ++) 
    { 
      DosFreeMem (Strings[Count]); Strings[Count] = NULL; 
    }
  }

  // Возврат.
  return;
}

