
// ─── Создает страницу для набора закладок ───

VOID SysPatches_Background_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.SysPatches_background;

  // Создаем страницу.
  CHAR Page_class_name[] = "SysPatches_Background_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) SysPatches_Background_WndProc, 0, 0);
  Page->Window = WinCreateWindow (Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Задаем шрифт.
  SetCommonEnhancerFont (Page->Window);

  // Узнаем страну, в которой работает приложение.
  LONG Code_page = Enhancer.Code_page;

  // Создаем поля ввода.
  LitCreateLayout (&Page->Layout, Page->Window);

  CreateCtlButtons (Page, 0);

  {
    LTBRICK Comment_brick; LitPrepareBrick (&Comment_brick);
    Comment_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_WORDBREAK, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Comment_ID, NULL, NULL);
    Comment_brick.prpWidthInParent = LTM_FULL_WIDTH; Comment_brick.prpHeightInParent = SYS_TXT_BRICK_HEIGHT;
    ULONG Red_color = RGB_DARKRED; WinSetPresParam (Comment_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof (Red_color), (PVOID) &Red_color);
    if (Code_page == RUSSIAN) WinSetWindowText (Comment_brick.hwnd, StrConst_RU_Pages_SysPatches_background_Restart);
    else WinSetWindowText (Comment_brick.hwnd, StrConst_EN_Pages_SysPatches_background_Restart);
    LitJoinBrick (&(Page->Layout), &Comment_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    for (INT Count = 0; Count < 5; Count ++)
    {
      LTBRICK Space_brick; LitPrepareBrick (&Space_brick);
      Space_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
      Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
      LitJoinBrick (&(Page->Layout), &Space_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  {
    LTBRICK Example_brick; LitPrepareBrick (&Example_brick);
    Example_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_GROUPBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Example_ID, NULL, NULL);
    Example_brick.prpWidthInParent = SYS_BMP_BRICK_WIDTH; Example_brick.prpHeightInParent = SYS_BMP_BRICK_HEIGHT;
    LitJoinBrick (&(Page->Layout), &Example_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK FileBox_brick; LitPrepareBrick (&FileBox_brick);
    FileBox_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Wallpaper_filebox_ID, NULL, NULL);
    FileBox_brick.prpWidthInParent = LTM_FULL_WIDTH; FileBox_brick.prpHeightInParent = FILEBOX_BRICK_HEIGHT; FileBox_brick.prpGap = FILEBOX_BRICK_GAP;
    LitJoinBrick (&(Page->Layout), &FileBox_brick);

    {
      LTBRICK Label_brick; LitPrepareBrick (&Label_brick);
      Label_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Wallpaper_label_ID, NULL, NULL);
      Label_brick.prpWidthInParent = FILEBOX_LABEL_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
      SetCommonEnhancerColors (Label_brick.hwnd);
      if (Code_page == RUSSIAN) WinSetWindowText (Label_brick.hwnd, StrConst_RU_Pages_SysPatches_background_Wallpaper_text);
      else WinSetWindowText (Label_brick.hwnd, StrConst_EN_Pages_SysPatches_background_Wallpaper_text);
      LitJoinBrick (&(Page->Layout), &Label_brick);

      LTBRICK Name_brick; LitPrepareBrick (&Name_brick);
      Name_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Wallpaper_name_ID, NULL, NULL);
      Name_brick.prpWidthInParent = FILEBOX_NAME_WIDTH; Name_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
      ULONG Blue_color = RGB_DARKBLUE; WinSetPresParam (Name_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof (Blue_color), (PVOID) &Blue_color);
      if (Code_page == RUSSIAN) WinSetWindowText (Name_brick.hwnd, StrConst_RU_Pages_SysPatches_background_Wallpaper_name);
      else WinSetWindowText (Name_brick.hwnd, StrConst_EN_Pages_SysPatches_background_Wallpaper_name);
      LitJoinBrick (&(Page->Layout), &Name_brick);

      LTBRICK Button_brick; LitPrepareBrick (&Button_brick);
      Button_brick.hwnd = WinCreateWindow (FileBox_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, SysPatches_Background.Settings.Wallpaper_button_ID, NULL, NULL);
      Button_brick.prpWidthInParent = FILEBOX_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
      if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Pages_SysPatches_background_Wallpaper_button);
      else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Pages_SysPatches_background_Wallpaper_button);
      LitJoinBrick (&(Page->Layout), &Button_brick);

      LitCompleteRow (&(Page->Layout));
    }
  }

  if (Code_page == RUSSIAN)
   CreatePromptText (Page, StrConst_RU_Pages_SysPatches_background_Prompt);
  else
   CreatePromptText (Page, StrConst_EN_Pages_SysPatches_background_Prompt);

  CompleteCreation (Page);

  {
    // Читаем предопределенные настройки из "OS2.ini".
    ULONG Path = SIZE_OF_PATH; SysPatches_Background.Settings.Folder_background_name[0] = 0;
    PrfQueryProfileData (HINI_USERPROFILE, "PM_SystemBackground", "DefaultFolderBackground", SysPatches_Background.Settings.Folder_background_name, &Path);

    // Если они есть:
    if (SysPatches_Background.Settings.Folder_background_name[0] != 0)
    {
      // Ставим после имени файла признак конца строки.
      PCHAR Point = stristr (".bmp", SysPatches_Background.Settings.Folder_background_name);
      if (Point != NULL) *(Point + 4) = 0;

      // Загружаем изображение.
      LoadBitmap (Enhancer.Application, SysPatches_Background.Settings.Folder_background_name, &SysPatches_Background.Settings.Folder_background, &SysPatches_Background.Settings.Folder_background_width, &SysPatches_Background.Settings.Folder_background_height);
    }
  }

  // Отключаем кнопку "Настройки по умолчанию".
  WinEnableWindow (WinWindowFromID (WinWindowFromID (Page->Window, BUTTONS_BRICK_ID), PD_BUTTON_ID), 0);

  // Запускаем счетчик времени.
  WinStartTimer (Enhancer.Application, Page->Window, 1, 50);

  // Возврат.
  return;
}

// ─── Ничего не делают ───

VOID SysPatches_Background_DoNothing (LONG Parameter = 0) { return; }
VOID SysPatches_Background_DoNothing (HINI Parameter = 0) { return; }
