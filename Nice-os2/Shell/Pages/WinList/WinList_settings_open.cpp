
// ─── Создает страницу для набора закладок ───

VOID WinList_Settings_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.WinList_settings;

 // Создаем страницу.
 CHAR Page_class_name[] = "WinList_Settings_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) WinList_Settings_WndProc, 0, 0 );
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
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = WL_BOX_BRICK_HEIGHT; Box_brick.prpGap = WL_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick );

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
   Space_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Space_brick );

   LitCompleteRow( &( Page->Layout ) );
  }

  {
   LTBRICK List_brick; LitPrepareBrick( &List_brick );
   List_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Visible_list_ID, NULL, NULL );
   List_brick.prpWidthInParent = WL_LST_BRICK_WIDTH; List_brick.prpHeightInParent = WL_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &List_brick );

   LTBRICK Buttons_brick; LitPrepareBrick( &Buttons_brick );
   Buttons_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Visible_buttons_ID, NULL, NULL );
   Buttons_brick.prpWidthInParent = ( 1 - WL_LST_BRICK_WIDTH ); Buttons_brick.prpHeightInParent = WL_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Buttons_brick );

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = WL_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

    LitCompleteRow( &( Page->Layout ) );

    LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Visible_Refresh_button_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_WinList_settings_Refresh );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_WinList_settings_Refresh );
    LitJoinBrick( &( Page->Layout ), &Button_brick );

    LitCompleteRow( &( Page->Layout ) );

    LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Visible_Move2H_button_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_WinList_settings_Move2H );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_WinList_settings_Move2H );
    LitJoinBrick( &( Page->Layout ), &Button_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
  }

  {
   LTBRICK List_brick; LitPrepareBrick( &List_brick );
   List_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Hidden_list_ID, NULL, NULL );
   List_brick.prpWidthInParent = WL_LST_BRICK_WIDTH; List_brick.prpHeightInParent = WL_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &List_brick );

   LTBRICK Buttons_brick; LitPrepareBrick( &Buttons_brick );
   Buttons_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Hidden_buttons_ID, NULL, NULL );
   Buttons_brick.prpWidthInParent = ( 1 - WL_LST_BRICK_WIDTH ); Buttons_brick.prpHeightInParent = WL_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Buttons_brick );

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = WL_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

    LitCompleteRow( &( Page->Layout ) );

    LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Hidden_Move2V_button_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_WinList_settings_Move2V );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_WinList_settings_Move2V );
    LitJoinBrick( &( Page->Layout ), &Button_brick );

    LitCompleteRow( &( Page->Layout ) );

    Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( Buttons_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = WL_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
  }
 }

 {
  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, WinList_Settings.Settings.Modify_WinList_button_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_WinList_settings_Modify );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_WinList_settings_Modify );
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_WinList_settings_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_WinList_settings_Prompt );

 CompleteCreation( Page );

 // Возврат.
 return;
}

