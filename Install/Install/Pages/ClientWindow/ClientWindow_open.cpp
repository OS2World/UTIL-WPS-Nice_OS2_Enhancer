
// ─── Создает страницу для набора закладок ───

VOID ClientWindow_CreatePage( HWND Window )
{
 // Задаем цвет окна (закрашивать его при получении "WM_PAINT" будем в любом случае).
 // Это свойство применится и к тем окнам, для которых "Window" будет "владельцем", в
 // том числе и для окна "WC_STATIC" с изображением.
 ULONG Blue_color = RGB_SMOKY_BLUE; WinSetPresParam( Window, PP_BACKGROUNDCOLOR, sizeof( Blue_color ), (PVOID) &Blue_color );

 // Задаем шрифт.
 SetCommonEnhancerFont( Window );

 // Создаем поля ввода.
 LitCreateLayout( &Client_Window.Layout, Window );

 {
  LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
  Space_brick.hwnd = WinCreateWindow( Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, 0, NULL, NULL );
  Space_brick.prpWidthInParent = LTM_FULL_WIDTH; Space_brick.prpHeightInParent = EMPTY_LINE_HEIGHT;
  LitJoinBrick( &Client_Window.Layout, &Space_brick );

  LitCompleteRow( &Client_Window.Layout );
 }

 {
  LTBRICK Container_brick; LitPrepareBrick( &Container_brick );
  Container_brick.hwnd = WinCreateWindow( Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.Buttons_brick_ID, NULL, NULL );
  Container_brick.prpWidthInParent = LTM_FULL_WIDTH; Container_brick.prpHeightInParent = BTN_BRICK_HEIGHT; Container_brick.prpGap = BTN_BRICK_GAP;
  LitJoinBrick( &Client_Window.Layout, &Container_brick );

  LitCompleteRow( &Client_Window.Layout );

  {
   ULONG Gray_color = RGB_PALEGRAY;
   ULONG Inst_color = RGB_DARKBLUE;
   ULONG Rmve_color = RGB_DARKRED;
   ULONG Exit_color = RGB_DARKGREEN;

   LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.Install_button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Inst_color ), (PVOID) &Inst_color );
   WinSetPresParam( Button_brick.hwnd, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
   if( Installer.Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Install_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Install_button );
   LitJoinBrick( &Client_Window.Layout, &Button_brick );

   LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.Remove_button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Rmve_color ), (PVOID) &Rmve_color );
   WinSetPresParam( Button_brick.hwnd, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
   if( Installer.Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Remove_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Remove_button );
   LitJoinBrick( &Client_Window.Layout, &Button_brick );

   LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Container_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.Cancel_button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = LTM_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   WinSetPresParam( Button_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Exit_color ), (PVOID) &Exit_color );
   WinSetPresParam( Button_brick.hwnd, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
   if( Installer.Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Cancel_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Cancel_button );
   LitJoinBrick( &Client_Window.Layout, &Button_brick );

   LitCompleteRow( &Client_Window.Layout );
  }
 }

 {
  LTBRICK Bitmap_brick; LitPrepareBrick( &Bitmap_brick );
  Bitmap_brick.hwnd = WinCreateWindow( Window, WC_STATIC, RC_BITMAP_STR, SS_BITMAP, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, 0, NULL, NULL );
  Bitmap_brick.prpWidthInParent = LTM_FULL_WIDTH; Bitmap_brick.prpHeightInParent = BMP_BRICK_HEIGHT;
  LitJoinBrick( &( Client_Window.Layout ), &Bitmap_brick );

  LitCompleteRow( &( Client_Window.Layout ) );
 }

 WinSendMsg( Window, MY_APPLY_LAYOUT, 0, 0 );

 // Возврат.
 return;
}

