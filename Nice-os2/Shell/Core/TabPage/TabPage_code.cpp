// ─── Создает кнопки для сохранения настроек и вызова справочника ───

VOID TabPage_CreateCtlButtons( PPAGE Page, BYTE Create_space_brick = 1 )
{
 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Создаем прямоугольник и кнопки.
 {
  LTBRICK Container_brick; LitPrepareBrick( &Container_brick );
  Container_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, BUTTONS_BRICK_ID, NULL, NULL );
  Container_brick.prpWidthInParent = LTM_FULL_WIDTH; Container_brick.prpHeightInParent = BUTTONS_BRICK_HEIGHT; Container_brick.prpGap = BUTTONS_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Container_brick );

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, OK_BUTTON_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   ULONG Blue_color = RGB_DARKBLUE; WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Blue_color ), (PVOID) &Blue_color );
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_OK );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_OK );
   LitJoinBrick( &( Page->Layout ), &Button_brick );

   LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, PD_BUTTON_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   ULONG Red_color = RGB_DARKRED; WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Red_color ), (PVOID) &Red_color );
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_PreDefined );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_PreDefined );
   LitJoinBrick( &( Page->Layout ), &Button_brick );

   LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, HP_BUTTON_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   ULONG Green_color = RGB_DARKGREEN; WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Green_color ), (PVOID) &Green_color );
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Buttons_Help );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Buttons_Help );
   LitJoinBrick( &( Page->Layout ), &Button_brick );

   LitCompleteRow( &( Page->Layout ) );
  }
 }

 if( Create_space_brick )
  {
   LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
   Space_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = SPACE_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Space_brick );

   LitCompleteRow( &( Page->Layout ) );
  }

 // Возврат.
 return;
}

// ─── Создает полоску с краткой подсказкой ───

VOID TabPage_CreatePromptText( PPAGE Page, CONST PCHAR Prompt_string )
{
 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Создаем полоску.
 LTBRICK Prompt_brick; LitPrepareBrick( &Prompt_brick );
 Prompt_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_WORDBREAK, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, PROMPT_RECTANGLE_ID, NULL, NULL );
 Prompt_brick.prpWidthInParent = LTM_FULL_WIDTH; Prompt_brick.prpHeightInParent = PROMPT_BRICK_HEIGHT;
 SetCommonEnhancerColors( Prompt_brick.hwnd );
 WinSetWindowText( Prompt_brick.hwnd, Prompt_string );
 LitJoinBrick( &( Page->Layout ), &Prompt_brick );

 LitCompleteRow( &( Page->Layout ) );

 // Возврат.
 return;
}

// ─── Завершает создание окна страницы ───

VOID TabPage_CompleteCreation( PPAGE Page )
{
 // Задаем настройки окна страницы.
 LTBRICK Page_brick; LitPrepareBrick( &Page_brick );
 Page_brick.hwnd = Page->Window;
 Page_brick.prpWidthInParent = LTM_FULL_WIDTH;
 Page_brick.prpHeightInParent = LTM_FULL_HEIGHT;
 Page_brick.prpMargin = NOTEBOOK_PAGE_MARGIN;
 Page_brick.prpGap = NOTEBOOK_PAGE_GAP;
 LitJoinBrick( &( Page->Layout ), &Page_brick );

 // Возврат.
 return;
}

// ─── Завершает создание окна страницы ───

VOID TabPage_UpdatePageWindow( PPAGE Page )
{
 // Скрываем и показываем окно.
 if( WinIsWindowVisible( Page->Window ) && WinIsWindowShowing( Page->Window ) )
  {
   WinShowWindow( Page->Window, 0 );
   WinShowWindow( Page->Window, 1 );
  }

 // Возврат.
 return;
}

// ─── Отправляет страницам сообщения "show & recognize settings" ───

VOID TabPage_BroadcastRSMessages( VOID )
{
 // Отправляем сообщения страницам.
 BroadcastMessage( SM_SHOW_SETTINGS );
 BroadcastMessage( SM_CHECK_OTHER_SETTINGS );
 BroadcastMessage( SM_RECOGNIZE_THEME );

 BroadcastMessage( SM_READ_LIST );
 BroadcastMessage( SM_UPDATE_LIST );

 BroadcastMessage( SM_RECOGNIZE_SELECTION );
 BroadcastMessage( SM_RECOGNIZE_L2_SELECTION );

 // Возврат.
 return;
}

