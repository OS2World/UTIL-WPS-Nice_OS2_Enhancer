
// ─── Создает страницу для набора закладок ───

VOID Mouse_Clipboard_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Mouse_clipboard;

 // Создаем страницу.
 CHAR Page_class_name[] = "Mouse_Clipboard_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) Mouse_Clipboard_WndProc, 0, 0 );
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
  LTBRICK Rectangle_brick; LitPrepareBrick( &Rectangle_brick );
  Rectangle_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
  LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

  LTBRICK Label_brick; LitPrepareBrick( &Label_brick );
  Label_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Label_brick.prpWidthInParent = MSE_LBL_BRICK_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Label_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Label_brick.hwnd, StrConst_RU_Pages_Mouse_clipboard_Mouse_type );
  else WinSetWindowText( Label_brick.hwnd, StrConst_EN_Pages_Mouse_clipboard_Mouse_type );
  LitJoinBrick( &( Page->Layout ), &Label_brick );

  LTBRICK Combobox_brick; LitPrepareBrick( &Combobox_brick );
  Combobox_brick.hwnd = WinCreateWindow( Page->Window, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Mouse_Clipboard.Settings.Mouse_cmbox_ID, NULL, NULL );
  Combobox_brick.prpWidthInParent = MSE_CBOX_BRICK_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
  LitJoinBrick( &( Page->Layout ), &Combobox_brick );

  LitPrepareBrick( &Rectangle_brick );
  Rectangle_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Rectangle_brick.prpWidthInParent = BLKQT_RCT_BRICK_WIDTH; Rectangle_brick.prpHeightInParent = BLKQT_RCT_BRICK_HEIGHT;
  LitJoinBrick( &( Page->Layout ), &Rectangle_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 {
  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Mouse_Clipboard.Settings.Use_MB_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_Mouse_clipboard_Use_middle_button );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_Mouse_clipboard_Use_middle_button );
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_Mouse_clipboard_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_Mouse_clipboard_Prompt );

 CompleteCreation( Page );

 // Заполняем список.
 {
  // Задаем строки.
  INT Max_strings = 2; PCHAR Strings[ 2 ]; INT Count;
  for( Count = 0; Count < Max_strings; Count ++ ) DosAllocMem( (PPVOID) &Strings[ Count ], 256, PAG_ALLOCATE );

  if( Code_page == RUSSIAN )
   {
    strcpy( Strings[ 0 ], StrConst_RU_Pages_Mouse_clipboard_Mouse_type_PS2 );
    strcpy( Strings[ 1 ], StrConst_RU_Pages_Mouse_clipboard_Mouse_type_PCSystems );
   }
  else
   {
    strcpy( Strings[ 0 ], StrConst_EN_Pages_Mouse_clipboard_Mouse_type_PS2 );
    strcpy( Strings[ 1 ], StrConst_EN_Pages_Mouse_clipboard_Mouse_type_PCSystems );
   }

  // Передаем строки окну списка.
  {
   HWND ComboBox_window = WinWindowFromID( Page->Window, Mouse_Clipboard.Settings.Mouse_cmbox_ID );

   BYTE Mouse_usage = MouseMapper.Settings.Use_middle_button_for_CopyPaste;
   for( Count = 0; Count < Max_strings; Count ++ ) WinSendMsg( ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP( Strings[ Count ] ) );
   MouseMapper.Settings.Use_middle_button_for_CopyPaste = Mouse_usage;
  }

  // Освобождаем память.
  for( Count = 0; Count < Max_strings; Count ++ ) { DosFreeMem( Strings[ Count ] ); Strings[ Count ] = NULL; }
 }

 // Возврат.
 return;
}

