
// ─── Создает страницу для набора закладок ───

VOID Keyboard_Actions_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Keyboard_actions;

  // Создаем страницу.
  CHAR Page_class_name[] = "Keyboard_Actions_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Keyboard_Actions_WndProc, 0, 0);
  Page->Window = WinCreateWindow (Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Задаем шрифт.
  SetCommonEnhancerFont (Page->Window);

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  // Создаем поля ввода.
  LitCreateLayout (&Page->Layout, Page->Window);

  CreateCtlButtons (Page);

  {
    LTBRICK FileBox_brick; LitPrepareBrick (&FileBox_brick);
    FileBox_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.ExeName_filebox_ID, NULL, NULL);
    FileBox_brick.prpWidthInParent = LTM_FULL_WIDTH; FileBox_brick.prpHeightInParent = FILEBOX_BRICK_HEIGHT; FileBox_brick.prpGap = FILEBOX_BRICK_GAP;
    LitJoinBrick (&(Page->Layout), &FileBox_brick);

    {
      LTBRICK Label_brick; LitPrepareBrick (&Label_brick);
      Label_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.ExeName_label_ID, NULL, NULL);
      Label_brick.prpWidthInParent = FILEBOX_LABEL_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
      SetCommonEnhancerColors (Label_brick.hwnd);
      if (Code_page == RUSSIAN) WinSetWindowText (Label_brick.hwnd, StrConst_RU_Pages_Keyboard_actions_ExeName);
      else WinSetWindowText (Label_brick.hwnd, StrConst_EN_Pages_Keyboard_actions_ExeName);
      LitJoinBrick (&(Page->Layout), &Label_brick);

      LTBRICK Name_brick; LitPrepareBrick (&Name_brick);
      Name_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.ExeName_name_ID, NULL, NULL);
      Name_brick.prpWidthInParent = FILEBOX_NAME_WIDTH; Name_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
      ULONG Blue_color = RGB_DARKBLUE; WinSetPresParam (Name_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof (Blue_color), (PVOID) &Blue_color);
      if (Code_page == RUSSIAN) WinSetWindowText (Name_brick.hwnd, StrConst_RU_Pages_Keyboard_actions_ExeName_text);
      else WinSetWindowText (Name_brick.hwnd, StrConst_EN_Pages_Keyboard_actions_ExeName_text);
      LitJoinBrick (&(Page->Layout), &Name_brick);

      LTBRICK Button_brick; LitPrepareBrick (&Button_brick);
      Button_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.ExeName_button_ID, NULL, NULL);
      Button_brick.prpWidthInParent = FILEBOX_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
      if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Pages_Keyboard_actions_ExeName_button);
      else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Pages_Keyboard_actions_ExeName_button);
      LitJoinBrick (&(Page->Layout), &Button_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  {
    LTBRICK Button_brick; LitPrepareBrick (&Button_brick);
    Button_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.Detect_button_ID, NULL, NULL);
    Button_brick.prpWidthInParent = KBD_DETECT_BTN_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Pages_Keyboard_actions_Detect);
    else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Pages_Keyboard_actions_Detect);
    LitJoinBrick (&(Page->Layout), &Button_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK SplitView_brick; LitPrepareBrick (&SplitView_brick);
    SplitView_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.SplitView_ID, NULL, NULL);
    SplitView_brick.prpWidthInParent = LTM_FULL_WIDTH; SplitView_brick.prpHeightInParent = KBD_SPLITVIEW_HEIGHT;
    LitJoinBrick (&(Page->Layout), &SplitView_brick);

    LitCompleteRow (&(Page->Layout));

    {
      LTBRICK List_brick; LitPrepareBrick (&List_brick);
      List_brick.hwnd = WinCreateWindow (SplitView_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.Key_list_ID, NULL, NULL);
      List_brick.prpWidthInParent = LTM_VSPLIT_WIDTH; List_brick.prpHeightInParent = LTM_FULL_HEIGHT;
      LitJoinBrick (&(Page->Layout), &List_brick);

      List_brick; LitPrepareBrick (&List_brick);
      List_brick.hwnd = WinCreateWindow (SplitView_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Keyboard_Actions.Settings.Action_list_ID, NULL, NULL);
      List_brick.prpWidthInParent = LTM_VSPLIT_WIDTH; List_brick.prpHeightInParent = LTM_FULL_HEIGHT;
      LitJoinBrick (&(Page->Layout), &List_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_Keyboard_actions_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_Keyboard_actions_Prompt);

  CompleteCreation (Page);

  // Заполняем списки.
  #include "Pages\\Keyboard\\Keyboard_actions_list.cpp"

  // Делаем выбранной первую строку списка.
  {
    HWND List_window = WinWindowFromID (WinWindowFromID (Page->Window, Keyboard_Actions.Settings.SplitView_ID), Keyboard_Actions.Settings.Key_list_ID);
    INT String_to_select = 0;
    WinSendMsg (List_window, LM_SELECTITEM, MPFROMLONG (String_to_select), MPFROMLONG (1));
  }

  // Возврат.
  return;
}

