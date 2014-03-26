
// ─── Создает страницу для набора закладок ───

VOID ClientWindow_CreatePage( HWND Window )
{
 // Задаем цвет окна (закрашивать его при получении "WM_PAINT" будем в любом случае).
 // Это свойство применится и к тем окнам, для которых "Window" будет "владельцем".
 ULONG Gray_color = RGB_PALEGRAY; WinSetPresParam( Window, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );

 // Задаем шрифт.
 SetCommonEnhancerFont( Window );

 // Создаем поля ввода.
 LitCreateLayout( &Client_Window.Layout, Window );

 {
  LTBRICK Label_brick; LitPrepareBrick( &Label_brick );
  Label_brick.hwnd = WinCreateWindow( Window, WC_STATIC, ">>", SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.Text_ID, NULL, NULL );
  Label_brick.prpWidthInParent = TEXT_BRICK_WIDTH; Label_brick.prpHeightInParent = TEXT_BRICK_HEIGHT;
  SetCommonEnhancerColors( Label_brick.hwnd );
  ULONG Red_color = RGB_DARKRED; WinSetPresParam( Label_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Red_color ), (PVOID) &Red_color );
  LitJoinBrick( &Client_Window.Layout, &Label_brick );

  LitCompleteRow( &Client_Window.Layout );
 }

 {
  LTBRICK List_brick; LitPrepareBrick( &List_brick );
  List_brick.hwnd = WinCreateWindow( Window, WC_LISTBOX, NULL, 0, LTM_X, LTM_Y, LTM_CX, LTM_CY, Window, HWND_TOP, Client_Window.Settings.List_ID, NULL, NULL );
  List_brick.prpWidthInParent = LIST_BRICK_WIDTH; List_brick.prpHeightInParent = LIST_BRICK_HEIGHT;
  LitJoinBrick( &Client_Window.Layout, &List_brick );

  LitCompleteRow( &Client_Window.Layout );
 }

 WinSendMsg( Window, MY_APPLY_LAYOUT, 0, 0 );

 // Возврат.
 return;
}

