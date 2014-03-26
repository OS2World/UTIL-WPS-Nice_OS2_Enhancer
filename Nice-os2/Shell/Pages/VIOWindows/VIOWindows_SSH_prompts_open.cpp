
// ─── Создает страницу для набора закладок ───

VOID VIOWindows_SSH_Prompts_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.VIOWindows_SSH_prompts;

 // Создаем страницу.
 CHAR Page_class_name[] = "VIOWindows_SSH_Prompts_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) VIOWindows_SSH_Prompts_WndProc, 0, 0 );
 Page->Window = WinCreateWindow( Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL );

 // Задаем шрифт.
 SetCommonEnhancerFont( Page->Window );

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Создаем поля ввода.
 LitCreateLayout( &Page->Layout, Page->Window );

 CreateCtlButtons( Page );

 {
  LTBRICK Box_brick; LitPrepareBrick( &Box_brick );
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.FileList_Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = XC_BLK_BRICK_HEIGHT; Box_brick.prpGap = XC_BLK_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick );

  LitCompleteRow( &( Page->Layout ) );

  {
   FLOAT Total_height = VIO_FILES_BRICK_HEIGHT;

   LTBRICK SelectBox_brick; LitPrepareBrick( &SelectBox_brick );
   SelectBox_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.SelectBox_ID, NULL, NULL );
   SelectBox_brick.prpWidthInParent = XC_LST_BRICK_WIDTH; SelectBox_brick.prpHeightInParent = Total_height;
   LitJoinBrick( &( Page->Layout ), &SelectBox_brick );

   LTBRICK AddRemove_brick; LitPrepareBrick( &AddRemove_brick );
   AddRemove_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.AddRemove_ID, NULL, NULL );
   AddRemove_brick.prpWidthInParent = ( 1 - XC_LST_BRICK_WIDTH ); AddRemove_brick.prpHeightInParent = Total_height;
   LitJoinBrick( &( Page->Layout ), &AddRemove_brick );

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK List_brick; LitPrepareBrick( &List_brick );
    List_brick.hwnd = WinCreateWindow( SelectBox_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.File_list_ID, NULL, NULL );
    List_brick.prpWidthInParent = LTM_FULL_WIDTH; List_brick.prpHeightInParent = VIO_FILES_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &List_brick );

    LitCompleteRow( &( Page->Layout ) );
   }

   {
    LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = XC_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

    LitCompleteRow( &( Page->Layout ) );

    LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.File_Add_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_Add );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_Add );
    LitJoinBrick( &( Page->Layout ), &Button_brick );

    LitCompleteRow( &( Page->Layout ) );

    LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.File_Remove_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_Remove );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_Remove );
    LitJoinBrick( &( Page->Layout ), &Button_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
  }

  {
   LTBRICK Caption_brick; LitPrepareBrick( &Caption_brick );
   Caption_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   Caption_brick.prpWidthInParent = LTM_COMMON_WIDTH; Caption_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
   SetCommonEnhancerColors( Caption_brick.hwnd );
   if( Code_page == RUSSIAN ) WinSetWindowText( Caption_brick.hwnd, StrConst_RU_Pages_VIOWindows_SSH_prompts_Caption );
   else WinSetWindowText( Caption_brick.hwnd, StrConst_EN_Pages_VIOWindows_SSH_prompts_Caption );
   LitJoinBrick( &( Page->Layout ), &Caption_brick );

   LitCompleteRow( &( Page->Layout ) );
  }
 }

 {
  LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
  Space_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
  LitJoinBrick( &( Page->Layout ), &Space_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 {
  LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
  Rectangle_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
  LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.Use_AltTilde_button_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_VIOWindows_SSH_prompts_AltTilde_button );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_VIOWindows_SSH_prompts_AltTilde_button );
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 {
  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, VIOWindows_SSH_Prompts.Settings.SSH_Commands_button_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_VIOWindows_SSH_prompts_Commands_button );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_VIOWindows_SSH_prompts_Commands_button );
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_VIOWindows_SSH_prompts_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_VIOWindows_SSH_prompts_Prompt );

 CompleteCreation( Page );

 // Возврат.
 return;
}



