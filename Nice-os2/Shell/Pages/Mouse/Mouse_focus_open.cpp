
// ─── Создает страницу для набора закладок ───

VOID Mouse_Focus_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Mouse_focus;

 // Создаем страницу.
 CHAR Page_class_name[] = "Mouse_Focus_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) Mouse_Focus_WndProc, 0, 0 );
 Page->Window = WinCreateWindow( Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL );

 // Задаем шрифт.
 SetCommonEnhancerFont( Page->Window );

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Создаем поля ввода.
 LitCreateLayout( &Page->Layout, Page->Window );

 CreateCtlButtons( Page );

 {
  for( INT Count = 0; Count < 5; Count ++ )
   {
    LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
    Space_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
    Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Space_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
 }

 {
  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Mouse_Focus.Settings.Scrolling_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_Mouse_focus_Scrolling );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_Mouse_focus_Scrolling );
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_Mouse_focus_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_Mouse_focus_Prompt );

 CompleteCreation( Page );

 // Возврат.
 return;
}

