
// ─── Создает страницу для набора закладок ───

VOID Rooms_Allocations_CreatePage (VOID)
{
  // Указатель на страницу.
  PPAGE Page = Enhancer.Pages.Rooms_allocations;

  // Создаем страницу.
  CHAR Page_class_name[] = "Rooms_Allocations_WndClass";
  WinRegisterClass (Enhancer.Application, Page_class_name, (PFNWP) Rooms_Allocations_WndProc, 0, 0);
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
    Box_brick.hwnd = WinCreateWindow (Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.AppList_Container_ID, NULL, NULL);
    Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = XC_BLK_BRICK_HEIGHT; Box_brick.prpGap = XC_BLK_BRICK_GAP;
    LitJoinBrick (&(Page->Layout), &Box_brick);

    LitCompleteRow (&(Page->Layout));

    {
      FLOAT Total_height = RMS_LST_BRICK_HEIGHT + RMS_CTL_BRICK_HEIGHT;

      LTBRICK SelectBox_brick; LitPrepareBrick (&SelectBox_brick);
      SelectBox_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.SelectBox_ID, NULL, NULL);
      SelectBox_brick.prpWidthInParent = XC_LST_BRICK_WIDTH; SelectBox_brick.prpHeightInParent = Total_height;
      LitJoinBrick (&(Page->Layout), &SelectBox_brick);

      LTBRICK AddRemove_brick; LitPrepareBrick (&AddRemove_brick);
      AddRemove_brick.hwnd = WinCreateWindow (Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.AddRemove_ID, NULL, NULL);
      AddRemove_brick.prpWidthInParent = (1 - XC_LST_BRICK_WIDTH); AddRemove_brick.prpHeightInParent = Total_height;
      LitJoinBrick (&(Page->Layout), &AddRemove_brick);

      LitCompleteRow (&(Page->Layout));

      {
        LTBRICK Label_brick; LitPrepareBrick (&Label_brick);
        Label_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL);
        Label_brick.prpWidthInParent = RMS_LBL_BRICK_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
        SetCommonEnhancerColors (Label_brick.hwnd);
        if (Code_page == RUSSIAN) WinSetWindowText (Label_brick.hwnd, StrConst_RU_Pages_Rooms_allocations_Room);
        else WinSetWindowText (Label_brick.hwnd, StrConst_EN_Pages_Rooms_allocations_Room);
        LitJoinBrick (&(Page->Layout), &Label_brick);

        LTBRICK Combobox_brick; LitPrepareBrick (&Combobox_brick);
        Combobox_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.Selected_room_cmbox_ID, NULL, NULL);
        Combobox_brick.prpWidthInParent = RMS_SWCBOX_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
        LitJoinBrick (&(Page->Layout), &Combobox_brick);

        LitCompleteRow (&(Page->Layout));

        LTBRICK List_brick; LitPrepareBrick (&List_brick);
        List_brick.hwnd = WinCreateWindow (SelectBox_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.Application_list_ID, NULL, NULL);
        List_brick.prpWidthInParent = LTM_FULL_WIDTH; List_brick.prpHeightInParent = RMS_LST_BRICK_HEIGHT;
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
        Button_brick.hwnd = WinCreateWindow (AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.Application_Add_ID, NULL, NULL);
        Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
        if (Code_page == RUSSIAN) WinSetWindowText (Button_brick.hwnd, StrConst_RU_Buttons_Add);
        else WinSetWindowText (Button_brick.hwnd, StrConst_EN_Buttons_Add);
        LitJoinBrick (&(Page->Layout), &Button_brick);

        LitCompleteRow (&(Page->Layout));

        LitPrepareBrick (&Button_brick);
        Button_brick.hwnd = WinCreateWindow (AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.Application_Remove_ID, NULL, NULL);
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
      if (Code_page == RUSSIAN) WinSetWindowText (Caption_brick.hwnd, StrConst_RU_Pages_Rooms_allocations_Caption);
      else WinSetWindowText (Caption_brick.hwnd, StrConst_EN_Pages_Rooms_allocations_Caption);
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
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.KnownApps_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Rooms_allocations_Known_button);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Rooms_allocations_Known_button);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

  {
    LTBRICK Checkbox_brick; LitPrepareBrick (&Checkbox_brick);
    Checkbox_brick.hwnd = WinCreateWindow (Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Allocations.Settings.Allocate_button_ID, NULL, NULL);
    Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
    SetCommonEnhancerColors (Checkbox_brick.hwnd);
    if (Code_page == RUSSIAN) WinSetWindowText (Checkbox_brick.hwnd, StrConst_RU_Pages_Rooms_allocations_Allocate_button);
    else WinSetWindowText (Checkbox_brick.hwnd, StrConst_EN_Pages_Rooms_allocations_Allocate_button);
    LitJoinBrick (&(Page->Layout), &Checkbox_brick);

    LitCompleteRow (&(Page->Layout));
  }

   if (Code_page == RUSSIAN)
    CreatePromptText (Page, StrConst_RU_Pages_Rooms_allocations_Prompt);
   else
    CreatePromptText (Page, StrConst_EN_Pages_Rooms_allocations_Prompt);

   CompleteCreation (Page);

   // Заполняем список комнат.
   {
     // Задаем строки.
     INT Max_strings = 5; PCHAR Strings[5]; INT Count;
     for (Count = 0; Count < Max_strings; Count ++) DosAllocMem ((PPVOID) &Strings[Count], 256, PAG_ALLOCATE);

     strcpy (Strings[0], "");

     if (Code_page == RUSSIAN)
     {
       strcpy (Strings[1], StrConst_RU_Pages_Rooms_allocations_Room_name_1);
       strcpy (Strings[2], StrConst_RU_Pages_Rooms_allocations_Room_name_2);
       strcpy (Strings[3], StrConst_RU_Pages_Rooms_allocations_Room_name_3);
       strcpy (Strings[4], StrConst_RU_Pages_Rooms_allocations_Room_name_4);
     }
     else
     {
       strcpy (Strings[1], StrConst_EN_Pages_Rooms_allocations_Room_name_1);
       strcpy (Strings[2], StrConst_EN_Pages_Rooms_allocations_Room_name_2);
       strcpy (Strings[3], StrConst_EN_Pages_Rooms_allocations_Room_name_3);
       strcpy (Strings[4], StrConst_EN_Pages_Rooms_allocations_Room_name_4);
     }

     // Передаем строки окну списка.
     {
       HWND ComboBox_window = WinWindowFromID (WinWindowFromID (WinWindowFromID (Page->Window, Rooms_Allocations.Settings.AppList_Container_ID), Rooms_Allocations.Settings.SelectBox_ID), Rooms_Allocations.Settings.Selected_room_cmbox_ID);

       INT Selected_room = Rooms_Allocations.Settings.Selected_room;
       for (Count = 0; Count < Max_strings; Count ++) { WinSendMsg (ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP (Strings[Count])); }
       Rooms_Allocations.Settings.Selected_room = Selected_room;
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

