
// ─── Создает страницу для набора закладок ───

VOID Drawing_Titlebars_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Drawing_titlebars;

 // Создаем страницу.
 CHAR Page_class_name[] = "Drawing_Titlebars_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) Drawing_Titlebars_WndProc, 0, 0 );
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
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = PLT_BOX_BRICK_HEIGHT; Box_brick.prpGap = PLT_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick ); 

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Palette_brick; LitPrepareBrick( &Palette_brick );
   Palette_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Palette_ID, NULL, NULL );
   Palette_brick.prpWidthInParent = PLT_SQRS_BRICK_WIDTH; Palette_brick.prpHeightInParent = LTM_FULL_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Palette_brick );

   LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
   Space_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   Space_brick.prpWidthInParent = ( 1 - PLT_SQRS_BRICK_WIDTH ); Space_brick.prpHeightInParent = PLT_SPACE_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Space_brick ); 

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Inactive_1_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Inactive_2_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Inactive_3_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick ); 

    LitCompleteRow( &( Page->Layout ) );
   }

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Active_1_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Active_2_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_Active_3_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick ); 

    LitCompleteRow( &( Page->Layout ) );
   }
  }
 }

 {
  LTBRICK Caption_brick; LitPrepareBrick( &Caption_brick );
  Caption_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.NeonPalette_FillTB_ID, NULL, NULL );
  Caption_brick.prpWidthInParent = LTM_COMMON_WIDTH; Caption_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Caption_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Caption_brick.hwnd, StrConst_RU_Pages_Drawing_titlebars_Fill_titlebars );
  else WinSetWindowText( Caption_brick.hwnd, StrConst_EN_Pages_Drawing_titlebars_Fill_titlebars );
  LitJoinBrick( &( Page->Layout ), &Caption_brick ); 

  LitCompleteRow( &( Page->Layout ) );
 }

 {
  LTBRICK Box_brick; LitPrepareBrick( &Box_brick );
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = PLT_BOX_BRICK_HEIGHT; Box_brick.prpGap = PLT_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick ); 

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Palette_brick; LitPrepareBrick( &Palette_brick );
   Palette_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_Palette_ID, NULL, NULL );
   Palette_brick.prpWidthInParent = PLT_SQRS_BRICK_WIDTH; Palette_brick.prpHeightInParent = LTM_FULL_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Palette_brick );

   LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_Button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = ( 1 - PLT_SQRS_BRICK_WIDTH ); Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT * 2;
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_Drawing_titlebars_Palette_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_Drawing_titlebars_Palette_button );
   LitJoinBrick( &( Page->Layout ), &Button_brick ); 

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_Inactive_ID, NULL, NULL );
    Square_brick.prpWidthInParent = LTM_FULL_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Square_brick.hwnd, StrConst_RU_Pages_Drawing_titlebars_Inactive_text );
    else WinSetWindowText( Square_brick.hwnd, StrConst_EN_Pages_Drawing_titlebars_Inactive_text );
    LitJoinBrick( &( Page->Layout ), &Square_brick ); 

    LitCompleteRow( &( Page->Layout ) );
   }

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_Active_ID, NULL, NULL );
    Square_brick.prpWidthInParent = LTM_FULL_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Square_brick.hwnd, StrConst_RU_Pages_Drawing_titlebars_Active_text );
    else WinSetWindowText( Square_brick.hwnd, StrConst_EN_Pages_Drawing_titlebars_Active_text );
    LitJoinBrick( &( Page->Layout ), &Square_brick ); 

    LitCompleteRow( &( Page->Layout ) );
   }
  }
 }

 {
  LTBRICK Caption_brick; LitPrepareBrick( &Caption_brick );
  Caption_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Drawing_Titlebars.Settings.WinTitles_DrawText_ID, NULL, NULL );
  Caption_brick.prpWidthInParent = LTM_COMMON_WIDTH; Caption_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Caption_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Caption_brick.hwnd, StrConst_RU_Pages_Drawing_titlebars_Draw_text );
  else WinSetWindowText( Caption_brick.hwnd, StrConst_EN_Pages_Drawing_titlebars_Draw_text );
  LitJoinBrick( &( Page->Layout ), &Caption_brick ); 

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_Drawing_titlebars_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_Drawing_titlebars_Prompt );

 CompleteCreation( Page );

 // Возврат.
 return;
}

