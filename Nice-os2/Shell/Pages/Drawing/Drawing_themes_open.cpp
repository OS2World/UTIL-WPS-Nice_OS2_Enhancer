
// ─── Создает страницу для набора закладок ───

VOID Drawing_Themes_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Drawing_themes;

  // Создаем страницу.
  CHAR Page_class_name[] = "Drawing_Themes_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Drawing_Themes_WndProc, 0, 0);
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
    Box_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Container_ID, NULL, NULL);
    Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = NM_BOX_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Box_brick);

    LitCompleteRow (&(Page->Layout));

    {
      LTBRICK Space_brick; LitPrepareBrick (&Space_brick);
      Space_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
      Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
      LitJoinBrick (&(Page->Layout), &Space_brick);

      LitCompleteRow (&(Page->Layout));
    }

    {
      LTBRICK FileBox_brick; LitPrepareBrick (&FileBox_brick);
      FileBox_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Texture_filebox_ID, NULL, NULL);
      FileBox_brick.prpWidthInParent = LTM_FULL_WIDTH; FileBox_brick.prpHeightInParent = FILEBOX_BRICK_HEIGHT; FileBox_brick.prpGap = FILEBOX_BRICK_GAP;
      LitJoinBrick (&(Page->Layout), &FileBox_brick);

      {
        LTBRICK Label_brick; LitPrepareBrick (&Label_brick);
        Label_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Texture_label_ID, NULL, NULL);
        Label_brick.prpWidthInParent = FILEBOX_LABEL_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
        SetCommonEnhancerColors (Label_brick.hwnd);
        if (Code_page == RUSSIAN) WinSetWindowText (Label_brick.hwnd, StrConst_RU_Pages_Drawing_themes_Texture_text);
        else WinSetWindowText (Label_brick.hwnd, StrConst_EN_Pages_Drawing_themes_Texture_text);
        LitJoinBrick (&(Page->Layout), &Label_brick);

        LTBRICK Name_brick; LitPrepareBrick (&Name_brick);
        Name_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Texture_name_ID, NULL, NULL);
        Name_brick.prpWidthInParent = FILEBOX_NAME_WIDTH; Name_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
        ULONG Blue_color = RGB_DARKBLUE; WinSetPresParam (Name_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof (Blue_color), (PVOID) &Blue_color);
        if (Code_page == RUSSIAN) WinSetWindowText (Name_brick.hwnd, StrConst_RU_Pages_Drawing_themes_Texture_name);
        else WinSetWindowText (Name_brick.hwnd, StrConst_EN_Pages_Drawing_themes_Texture_name);
        LitJoinBrick (&(Page->Layout), &Name_brick);

        LTBRICK Button_brick; LitPrepareBrick (&Button_brick);
        Button_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Texture_button_ID, NULL, NULL);
        Button_brick.prpWidthInParent = FILEBOX_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
        if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Pages_Drawing_themes_Texture_button);
        else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Pages_Drawing_themes_Texture_button);
        LitJoinBrick (&(Page->Layout), &Button_brick);

        LitCompleteRow (&(Page->Layout));
      }
    }

    {
      LTBRICK List_brick; LitPrepareBrick (&List_brick);
      List_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Theme_list_ID, NULL, NULL);
      List_brick.prpWidthInParent = NM_LST_BRICK_WIDTH; List_brick.prpHeightInParent = NM_LST_BRICK_HEIGHT;
      LitJoinBrick (&(Page->Layout), &List_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Themes.Settings.Theme_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Drawing_themes_Draw_frames);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Drawing_themes_Draw_frames);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_Drawing_themes_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_Drawing_themes_Prompt);

  CompleteCreation (Page);

  // Заполняем список тем.
  {
    // Задаем строки.
    INT Max_strings = 6; PCHAR Strings[6]; INT Count;
    for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

    if (Code_page == RUSSIAN)
    {
      strcpy (Strings[0], StrConst_RU_Pages_Drawing_themes_TName_Phoenix);
      strcpy (Strings[1], StrConst_RU_Pages_Drawing_themes_TName_BlueLion);
      strcpy (Strings[2], StrConst_RU_Pages_Drawing_themes_TName_eComStation);
      strcpy (Strings[3], StrConst_RU_Pages_Drawing_themes_TName_Classic);
      strcpy (Strings[4], StrConst_RU_Pages_Drawing_themes_TName_NeonBars);
      strcpy (Strings[5], StrConst_RU_Pages_Drawing_themes_TName_WhiteSnow);
    }
    else
    {
      strcpy (Strings[0], StrConst_EN_Pages_Drawing_themes_TName_Phoenix);
      strcpy (Strings[1], StrConst_EN_Pages_Drawing_themes_TName_BlueLion);
      strcpy (Strings[2], StrConst_EN_Pages_Drawing_themes_TName_eComStation);
      strcpy (Strings[3], StrConst_EN_Pages_Drawing_themes_TName_Classic);
      strcpy (Strings[4], StrConst_EN_Pages_Drawing_themes_TName_NeonBars);
      strcpy (Strings[5], StrConst_EN_Pages_Drawing_themes_TName_WhiteSnow);
    }

    // Передаем строки окну списка.
    {
      HWND Theme_list_window = WinWindowFromID (WinWindowFromID (Page->Window, Drawing_Themes.Settings.Container_ID), Drawing_Themes.Settings.Theme_list_ID);

      Drawing_Themes.Settings.Theme_list_is_locked = 1; WinShowWindow (Theme_list_window, 0);
      for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (Theme_list_window, LM_INSERTITEM, MPFROMSHORT (LIT_END), MPFROMP (Strings[Count])); }
      Drawing_Themes.Settings.Theme_list_is_locked = 0; WinShowWindow (Theme_list_window, 1);
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
