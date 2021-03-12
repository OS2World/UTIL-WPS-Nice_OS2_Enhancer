
// ─── Создает страницу для набора закладок ───

VOID VIOWindows_Fonts_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.VIOWindows_fonts;

  // Создаем страницу.
  CHAR Page_class_name[] = "VIOWindows_Fonts_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) VIOWindows_Fonts_WndProc, 0, 0);
  Page->Window = WinCreateWindow (Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Задаем шрифт.
  SetCommonEnhancerFont (Page->Window);

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  // Создаем поля ввода.
  LitCreateLayout (&Page->Layout, Page->Window);

  CreateCtlButtons (Page);

  {
    LTBRICK Box_brick; LitPrepareBrick (&Box_brick);
    Box_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.AppList_Container_ID, NULL, NULL);
    Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = XC_BLK_BRICK_HEIGHT; Box_brick.prpGap = XC_BLK_BRICK_GAP;
    LitJoinBrick (&(Page->Layout), &Box_brick);

    LitCompleteRow (&(Page->Layout));

    {
      FLOAT Total_height = VIO_LST_BRICK_HEIGHT + VIO_CTL_BRICK_HEIGHT;

      LTBRICK SelectBox_brick; LitPrepareBrick (&SelectBox_brick);
      SelectBox_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.SelectBox_ID, NULL, NULL);
      SelectBox_brick.prpWidthInParent = XC_LST_BRICK_WIDTH; SelectBox_brick.prpHeightInParent = Total_height;
      LitJoinBrick (&(Page->Layout), &SelectBox_brick);

      LTBRICK AddRemove_brick; LitPrepareBrick (&AddRemove_brick);
      AddRemove_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.AddRemove_ID, NULL, NULL);
      AddRemove_brick.prpWidthInParent = (1 - XC_LST_BRICK_WIDTH); AddRemove_brick.prpHeightInParent = Total_height;
      LitJoinBrick (&(Page->Layout), &AddRemove_brick);

      LitCompleteRow (&(Page->Layout));

      {
        LTBRICK Label_brick; LitPrepareBrick (&Label_brick);
        Label_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
        Label_brick.prpWidthInParent = VIO_LBL_BRICK_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
        SetCommonEnhancerColors (Label_brick.hwnd);
        if (Code_page == RUSSIAN) WinSetWindowText (Label_brick.hwnd, StrConst_RU_Pages_VIOWindows_fonts_Font);
        else WinSetWindowText (Label_brick.hwnd, StrConst_EN_Pages_VIOWindows_fonts_Font);
        LitJoinBrick (&(Page->Layout), &Label_brick);

        LTBRICK Combobox_brick; LitPrepareBrick (&Combobox_brick);
        Combobox_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.Selected_font_cmbox_ID, NULL, NULL);
        Combobox_brick.prpWidthInParent = VIO_SWCBOX_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
        LitJoinBrick (&(Page->Layout), &Combobox_brick);

        LitCompleteRow (&(Page->Layout));

        LTBRICK List_brick; LitPrepareBrick (&List_brick);
        List_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.Application_list_ID, NULL, NULL);
        List_brick.prpWidthInParent = LTM_FULL_WIDTH; List_brick.prpHeightInParent = VIO_LST_BRICK_HEIGHT;
        LitJoinBrick (&(Page->Layout), &List_brick);

        LitCompleteRow (&(Page->Layout));
      }

      {
        LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
        Rectangle_brick.hwnd = WinCreateWindow (AddRemove_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
        Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = XC_RCT_BRICK_HEIGHT;
        LitJoinBrick (&(Page->Layout), &Rectangle_brick);

        LitCompleteRow (&(Page->Layout));

        LTBRICK Button_brick; LitPrepareBrick (&Button_brick);
        Button_brick.hwnd = WinCreateWindow (AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.Application_Add_ID, NULL, NULL);
        Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
        if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Buttons_Add);
        else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Buttons_Add);
        LitJoinBrick (&(Page->Layout), &Button_brick);

        LitCompleteRow (&(Page->Layout));

        LitPrepareBrick (&Button_brick);
        Button_brick.hwnd = WinCreateWindow (AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.Application_Remove_ID, NULL, NULL);
        Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
        if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Buttons_Remove);
        else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Buttons_Remove);
        LitJoinBrick (&(Page->Layout), &Button_brick);

        LitCompleteRow (&(Page->Layout));
      }
    }

    {
      LTBRICK Caption_brick; LitPrepareBrick (&Caption_brick);
      Caption_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
      Caption_brick.prpWidthInParent = LTM_COMMON_WIDTH; Caption_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
      SetCommonEnhancerColors (Caption_brick.hwnd);
      if (Code_page == RUSSIAN) WinSetWindowText (Caption_brick.hwnd, StrConst_RU_Pages_VIOWindows_fonts_Caption);
      else WinSetWindowText (Caption_brick.hwnd, StrConst_EN_Pages_VIOWindows_fonts_Caption);
      LitJoinBrick (&(Page->Layout), &Caption_brick);

      LitCompleteRow (&(Page->Layout));
    }
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
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.KnownApps_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_VIOWindows_fonts_Known_button);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_VIOWindows_fonts_Known_button);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_Fonts.Settings.SetFont_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_VIOWindows_fonts_SetFont_button);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_VIOWindows_fonts_SetFont_button);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_VIOWindows_fonts_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_VIOWindows_fonts_Prompt);

  CompleteCreation (Page);

  // Заполняем список шрифтов в окне "combo-box".
  {
    // Задаем строки.
    INT Max_strings = 8; PCHAR Strings[8]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    strcpy (Strings[0], "10 x 6");
    strcpy (Strings[0], "14 x 6");
    strcpy (Strings[1], "12 x 8");
    strcpy (Strings[2], "15 x 7");
    strcpy (Strings[3], "14 x 8");
    strcpy (Strings[4], "16 x 8");
    strcpy (Strings[5], "18 x 8");
    strcpy (Strings[6], "18 x 10");

    // Передаем строки окну списка.
    {
      HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Page->Window, VIOWindows_Fonts.Settings.AppList_Container_ID), VIOWindows_Fonts.Settings.SelectBox_ID), VIOWindows_Fonts.Settings.Selected_font_cmbox_ID);

      VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 1;
      for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count])); }
      VIOWindows_Fonts.Settings.FontMetrics_list_is_locked = 0;
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

