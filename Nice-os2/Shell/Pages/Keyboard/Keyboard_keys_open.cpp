
// ─── Создает страницу для набора закладок ───

VOID Keyboard_Keys_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Keyboard_keys;

  // Создаем страницу.
  CHAR Page_class_name[] = "Keyboard_Keys_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Keyboard_Keys_WndProc, 0, 0);
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
    Box_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Keys.Settings.Container_ID, NULL, NULL);
    Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = NM_BOX_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Box_brick);

    LitCompleteRow (&(Page->Layout));

    {
      LTBRICK Space_brick; LitPrepareBrick (&Space_brick);
      Space_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
      Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
      LitJoinBrick (&(Page->Layout), &Space_brick);

      LitCompleteRow (&(Page->Layout));

      {
        LTBRICK Rectangle_brick; LitPrepareBrick (&Rectangle_brick);
        Rectangle_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
        Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
        LitJoinBrick (&(Page->Layout), &Rectangle_brick);

        LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
        Checkbox_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Keys.Settings.Use_button_ID, NULL, NULL);
        Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
        SetCommonEnhancerColors (Checkbox_brick.hwnd);
        if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_keys_Use_button);
        else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_keys_Use_button);
        LitJoinBrick (&(Page->Layout), &Checkbox_brick);

        LitCompleteRow (&(Page->Layout));
      }

      LTBRICK List_brick; LitPrepareBrick (&List_brick);
      List_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Keys.Settings.Kbd_list_ID, NULL, NULL);
      List_brick.prpWidthInParent = NM_LST_BRICK_WIDTH; List_brick.prpHeightInParent = NM_LST_BRICK_HEIGHT;
      LitJoinBrick (&(Page->Layout), &List_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Keys.Settings.Define_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Keyboard_keys_Define_button);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Keyboard_keys_Define_button);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_Keyboard_keys_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_Keyboard_keys_Prompt);

  CompleteCreation (Page);

  // Заполняем список.
  {
    // Задаем строки.
    INT Max_strings = 14; PCHAR Strings[14]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    if (Code_page == RUSSIAN)
    {
      strcpy (Strings[ 0], StrConst_RU_Pages_Keyboard_keys_Key_name_1);
      strcpy (Strings[ 1], StrConst_RU_Pages_Keyboard_keys_Key_name_2);
      strcpy (Strings[ 2], StrConst_RU_Pages_Keyboard_keys_Key_name_3);
      strcpy (Strings[ 3], StrConst_RU_Pages_Keyboard_keys_Key_name_4);
      strcpy (Strings[ 4], StrConst_RU_Pages_Keyboard_keys_Key_name_5);
      strcpy (Strings[ 5], StrConst_RU_Pages_Keyboard_keys_Key_name_6);
      strcpy (Strings[ 6], StrConst_RU_Pages_Keyboard_keys_Key_name_7);
      strcpy (Strings[ 7], StrConst_RU_Pages_Keyboard_keys_Key_name_8);
      strcpy (Strings[ 8], StrConst_RU_Pages_Keyboard_keys_Key_name_9);
      strcpy (Strings[ 9], StrConst_RU_Pages_Keyboard_keys_Key_name_A);
      strcpy (Strings[10], StrConst_RU_Pages_Keyboard_keys_Key_name_B);
      strcpy (Strings[11], StrConst_RU_Pages_Keyboard_keys_Key_name_C);
      strcpy (Strings[12], StrConst_RU_Pages_Keyboard_keys_Key_name_D);
      strcpy (Strings[13], StrConst_RU_Pages_Keyboard_keys_Key_name_E);
    }
    else
    {
      strcpy (Strings[ 0], StrConst_EN_Pages_Keyboard_keys_Key_name_1);
      strcpy (Strings[ 1], StrConst_EN_Pages_Keyboard_keys_Key_name_2);
      strcpy (Strings[ 2], StrConst_EN_Pages_Keyboard_keys_Key_name_3);
      strcpy (Strings[ 3], StrConst_EN_Pages_Keyboard_keys_Key_name_4);
      strcpy (Strings[ 4], StrConst_EN_Pages_Keyboard_keys_Key_name_5);
      strcpy (Strings[ 5], StrConst_EN_Pages_Keyboard_keys_Key_name_6);
      strcpy (Strings[ 6], StrConst_EN_Pages_Keyboard_keys_Key_name_7);
      strcpy (Strings[ 7], StrConst_EN_Pages_Keyboard_keys_Key_name_8);
      strcpy (Strings[ 8], StrConst_EN_Pages_Keyboard_keys_Key_name_9);
      strcpy (Strings[ 9], StrConst_EN_Pages_Keyboard_keys_Key_name_A);
      strcpy (Strings[10], StrConst_EN_Pages_Keyboard_keys_Key_name_B);
      strcpy (Strings[11], StrConst_EN_Pages_Keyboard_keys_Key_name_C);
      strcpy (Strings[12], StrConst_EN_Pages_Keyboard_keys_Key_name_D);
      strcpy (Strings[13], StrConst_EN_Pages_Keyboard_keys_Key_name_E);
    }

    // Передаем строки окну списка.
    {
      HWND List_window = WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Kbd_list_ID);

      Keyboard_Keys.Settings.Key_list_is_locked = 1; WinShowWindow (List_window, 0);
      for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (List_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Strings[Count])); }
      Keyboard_Keys.Settings.Key_list_is_locked = 0; WinShowWindow (List_window, 1);
    }

    // Освобождаем память.
    for (Count = 0; Count < Max_strings; Count ++) 
    { 
      DosFreeMem (Strings[Count]); Strings[Count] = NULL; 
    }
  }

  // Делаем выбранной первую строку списка.
  {
    HWND List_window = WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Keys.Settings.Container_ID), Keyboard_Keys.Settings.Kbd_list_ID);
    INT String_to_select = 0;
    WinSendMsg (List_window, LM_SELECTITEM, MPFROMLONG (String_to_select), MPFROMLONG (1));
  }

  // Возврат.
  return;
}

