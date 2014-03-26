
// ─── Создает страницу для набора закладок ───

VOID Scrolling_Exceptions_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Scrolling_exceptions;

 // Создаем страницу.
 CHAR Page_class_name[] = "Scrolling_Exceptions_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) Scrolling_Exceptions_WndProc, 0, 0 );
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
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Container_Kbd_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = XC_BOX_BRICK_HEIGHT; Box_brick.prpGap = XC_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick ); 

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK List_brick; LitPrepareBrick( &List_brick );
   List_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.List_Kbd_ID, NULL, NULL );
   List_brick.prpWidthInParent = XC_LST_BRICK_WIDTH; List_brick.prpHeightInParent = XC_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &List_brick );

   LTBRICK AddRemove_brick; LitPrepareBrick( &AddRemove_brick );
   AddRemove_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   AddRemove_brick.prpWidthInParent = ( 1 - XC_LST_BRICK_WIDTH ); AddRemove_brick.prpHeightInParent = XC_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &AddRemove_brick ); 

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = XC_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick ); 

    LitCompleteRow( &( Page->Layout ) );

    LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Add_button_Kbd_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_Add );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_Add );
    LitJoinBrick( &( Page->Layout ), &Button_brick ); 

    LitCompleteRow( &( Page->Layout ) );

    LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Remove_button_Kbd_ID, NULL, NULL );
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
   if( Code_page == RUSSIAN ) WinSetWindowText( Caption_brick.hwnd, StrConst_RU_Pages_Scrolling_exceptions_Caption_Kbd );
   else WinSetWindowText( Caption_brick.hwnd, StrConst_EN_Pages_Scrolling_exceptions_Caption_Kbd );
   LitJoinBrick( &( Page->Layout ), &Caption_brick ); 

   LitCompleteRow( &( Page->Layout ) );
  }
 }

 {
  LTBRICK Box_brick; LitPrepareBrick( &Box_brick );
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Container_Mou_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = XC_BOX_BRICK_HEIGHT; Box_brick.prpGap = XC_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick ); 

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK List_brick; LitPrepareBrick( &List_brick );
   List_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.List_Mou_ID, NULL, NULL );
   List_brick.prpWidthInParent = XC_LST_BRICK_WIDTH; List_brick.prpHeightInParent = XC_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &List_brick );

   LTBRICK AddRemove_brick; LitPrepareBrick( &AddRemove_brick );
   AddRemove_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   AddRemove_brick.prpWidthInParent = ( 1 - XC_LST_BRICK_WIDTH ); AddRemove_brick.prpHeightInParent = XC_LST_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &AddRemove_brick ); 

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
    Rectangle_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Rectangle_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Rectangle_brick.prpHeightInParent = XC_RCT_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Rectangle_brick ); 

    LitCompleteRow( &( Page->Layout ) );

    LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Add_button_Mou_ID, NULL, NULL );
    Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_Add );
    else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_Add );
    LitJoinBrick( &( Page->Layout ), &Button_brick ); 

    LitCompleteRow( &( Page->Layout ) );

    LitPrepareBrick( &Button_brick );
    Button_brick.hwnd = WinCreateWindow( AddRemove_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Scrolling_Exceptions.Settings.Remove_button_Mou_ID, NULL, NULL );
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
   if( Code_page == RUSSIAN ) WinSetWindowText( Caption_brick.hwnd, StrConst_RU_Pages_Scrolling_exceptions_Caption_Mou );
   else WinSetWindowText( Caption_brick.hwnd, StrConst_EN_Pages_Scrolling_exceptions_Caption_Mou );
   LitJoinBrick( &( Page->Layout ), &Caption_brick ); 

   LitCompleteRow( &( Page->Layout ) );
  }
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_Scrolling_exceptions_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_Scrolling_exceptions_Prompt );

 CompleteCreation( Page );

 // Возврат.
 return;
}

