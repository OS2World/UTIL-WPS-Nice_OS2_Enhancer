
// ─── Создает страницу для набора закладок ───

VOID Rooms_Colors_CreatePage( VOID )
{
 // Указатель на страницу.
 PPAGE Page = Enhancer.Pages.Rooms_colors;

 // Создаем страницу.
 CHAR Page_class_name[] = "Rooms_Colors_WndClass";
 WinRegisterClass( Enhancer.Application, Page_class_name, (PFNWP) Rooms_Colors_WndProc, 0, 0 );
 Page->Window = WinCreateWindow( Enhancer.Client_window, Page_class_name, NULL, 0, 0, 0, 0, 0, NULLHANDLE, HWND_TOP, 0, NULL, NULL );

 // Задаем шрифт.
 SetCommonEnhancerFont( Page->Window );

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 // Создаем поля ввода.
 LitCreateLayout( &Page->Layout, Page->Window );

 CreateCtlButtons( Page );

 {
  LTBRICK FileBox_brick; LitPrepareBrick( &FileBox_brick );
  FileBox_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Wallpaper_filebox_ID, NULL, NULL );
  FileBox_brick.prpWidthInParent = LTM_FULL_WIDTH; FileBox_brick.prpHeightInParent = FILEBOX_BRICK_HEIGHT; FileBox_brick.prpGap = FILEBOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &FileBox_brick );

  {
   LTBRICK Label_brick; LitPrepareBrick( &Label_brick );
   Label_brick.hwnd = WinCreateWindow( FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Wallpaper_label_ID, NULL, NULL );
   Label_brick.prpWidthInParent = FILEBOX_LABEL_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
   SetCommonEnhancerColors( Label_brick.hwnd );
   if( Code_page == RUSSIAN ) WinSetWindowText( Label_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Wallpaper_text );
   else WinSetWindowText( Label_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Wallpaper_text );
   LitJoinBrick( &( Page->Layout ), &Label_brick );

   LTBRICK Name_brick; LitPrepareBrick( &Name_brick );
   Name_brick.hwnd = WinCreateWindow( FileBox_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Wallpaper_name_ID, NULL, NULL );
   Name_brick.prpWidthInParent = FILEBOX_NAME_WIDTH; Name_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
   ULONG Blue_color = RGB_DARKBLUE; WinSetPresParam( Name_brick.hwnd, PP_FOREGROUNDCOLOR, sizeof( Blue_color ), (PVOID) &Blue_color );
   if( Code_page == RUSSIAN ) WinSetWindowText( Name_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Wallpaper_name );
   else WinSetWindowText( Name_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Wallpaper_name );
   LitJoinBrick( &( Page->Layout ), &Name_brick );

   LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( FileBox_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Wallpaper_button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = FILEBOX_BUTTON_WIDTH; Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT;
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Wallpaper_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Wallpaper_button );
   LitJoinBrick( &( Page->Layout ), &Button_brick );

   LitCompleteRow( &( Page->Layout ) );
  }
 }

 {
  LTBRICK Box_brick; LitPrepareBrick( &Box_brick );
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = PLT_BOX_BRICK_HEIGHT; Box_brick.prpGap = PLT_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick );

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Palette_brick; LitPrepareBrick( &Palette_brick );
   Palette_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Palette_ID, NULL, NULL );
   Palette_brick.prpWidthInParent = PLT_SQRS_BRICK_WIDTH; Palette_brick.prpHeightInParent = LTM_FULL_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Palette_brick );

   LTBRICK Space_brick; LitPrepareBrick( &Space_brick );
   Space_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
   Space_brick.prpWidthInParent = ( 1 - PLT_SQRS_BRICK_WIDTH ); Space_brick.prpHeightInParent = PLT_SPACE_BRICK_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Space_brick );

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Inactive_1_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Inactive_2_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Inactive_3_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitCompleteRow( &( Page->Layout ) );
   }

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Active_1_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Active_2_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.NeonPalette_Active_3_ID, NULL, NULL );
    Square_brick.prpWidthInParent = PLT_SQRE_BRICK_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
  }
 }

 {
  LTBRICK Box_brick; LitPrepareBrick( &Box_brick );
  Box_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.WinTitles_Container_ID, NULL, NULL );
  Box_brick.prpWidthInParent = LTM_FULL_WIDTH; Box_brick.prpHeightInParent = PLT_BOX_BRICK_HEIGHT; Box_brick.prpGap = PLT_BOX_BRICK_GAP;
  LitJoinBrick( &( Page->Layout ), &Box_brick );

  LitCompleteRow( &( Page->Layout ) );

  {
   LTBRICK Palette_brick; LitPrepareBrick( &Palette_brick );
   Palette_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_STATIC, NULL, SS_TEXT, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.WinTitles_Palette_ID, NULL, NULL );
   Palette_brick.prpWidthInParent = PLT_SQRS_BRICK_WIDTH; Palette_brick.prpHeightInParent = LTM_FULL_HEIGHT;
   LitJoinBrick( &( Page->Layout ), &Palette_brick );

   LTBRICK Button_brick; LitPrepareBrick( &Button_brick );
   Button_brick.hwnd = WinCreateWindow( Box_brick.hwnd, WC_BUTTON, NULL, BS_PUSHBUTTON, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.WinTitles_Button_ID, NULL, NULL );
   Button_brick.prpWidthInParent = ( 1 - PLT_SQRS_BRICK_WIDTH ); Button_brick.prpHeightInParent = LTM_BUTTON_HEIGHT * 2;
   if( Code_page == RUSSIAN ) WinSetWindowText( Button_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Palette_button );
   else WinSetWindowText( Button_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Palette_button );
   LitJoinBrick( &( Page->Layout ), &Button_brick );

   LitCompleteRow( &( Page->Layout ) );

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.WinTitles_Inactive_ID, NULL, NULL );
    Square_brick.prpWidthInParent = LTM_FULL_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Square_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Inactive_text );
    else WinSetWindowText( Square_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Inactive_text );
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitCompleteRow( &( Page->Layout ) );
   }

   {
    LTBRICK Square_brick; LitPrepareBrick( &Square_brick );
    Square_brick.hwnd = WinCreateWindow( Palette_brick.hwnd, WC_STATIC, NULL, SS_TEXT | DT_CENTER | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.WinTitles_Active_ID, NULL, NULL );
    Square_brick.prpWidthInParent = LTM_FULL_WIDTH; Square_brick.prpHeightInParent = PLT_SQRE_BRICK_HEIGHT;
    if( Code_page == RUSSIAN ) WinSetWindowText( Square_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Active_text );
    else WinSetWindowText( Square_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Active_text );
    LitJoinBrick( &( Page->Layout ), &Square_brick );

    LitCompleteRow( &( Page->Layout ) );
   }
  }
 }

 {
  LTBRICK Label_brick; LitPrepareBrick( &Label_brick );
  Label_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_RIGHT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Label_brick.prpWidthInParent = RMS_LBL_BRICK_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Label_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Label_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Settings_1 );
  else WinSetWindowText( Label_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Settings_1 );
  LitJoinBrick( &( Page->Layout ), &Label_brick );

  LTBRICK Combobox_brick; LitPrepareBrick( &Combobox_brick );
  Combobox_brick.hwnd = WinCreateWindow( Page->Window, WC_COMBOBOX, NULL, CBS_DROPDOWNLIST, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Selected_room_cmbox_ID, NULL, NULL );
  Combobox_brick.prpWidthInParent = RMS_SWCBOX_WIDTH; Combobox_brick.prpHeightInParent = LTM_COMBOBOX_HEIGHT; Combobox_brick.ulBoxHeight = LTM_COMBOBOX_LIST;
  LitJoinBrick( &( Page->Layout ), &Combobox_brick );

  LitPrepareBrick( &Label_brick );
  Label_brick.hwnd = WinCreateWindow( Page->Window, WC_STATIC, NULL, SS_TEXT | DT_LEFT | DT_VCENTER, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, 0, NULL, NULL );
  Label_brick.prpWidthInParent = RMS_LBL_BRICK_WIDTH; Label_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  if( Code_page == RUSSIAN ) WinSetWindowText( Label_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Settings_2 );
  else WinSetWindowText( Label_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Settings_2 );
  LitJoinBrick( &( Page->Layout ), &Label_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 {
  LTBRICK Checkbox_brick; LitPrepareBrick( &Checkbox_brick );
  Checkbox_brick.hwnd = WinCreateWindow( Page->Window, WC_BUTTON, NULL, BS_CHECKBOX, LTM_X, LTM_Y, LTM_CX, LTM_CY, Page->Window, HWND_TOP, Rooms_Colors.Settings.Create_rooms_button_ID, NULL, NULL );
  Checkbox_brick.prpWidthInParent = LTM_COMMON_WIDTH; Checkbox_brick.prpHeightInParent = LTM_COMMON_HEIGHT;
  SetCommonEnhancerColors( Checkbox_brick.hwnd );
  if( Code_page == RUSSIAN ) WinSetWindowText( Checkbox_brick.hwnd, StrConst_RU_Pages_Rooms_colors_Create_rooms );
  else WinSetWindowText( Checkbox_brick.hwnd, StrConst_EN_Pages_Rooms_colors_Create_rooms );  
  LitJoinBrick( &( Page->Layout ), &Checkbox_brick );

  LitCompleteRow( &( Page->Layout ) );
 }

 if( Code_page == RUSSIAN )
  CreatePromptText( Page, StrConst_RU_Pages_Rooms_colors_Prompt );
 else
  CreatePromptText( Page, StrConst_EN_Pages_Rooms_colors_Prompt );

 CompleteCreation( Page );

 // Задаем выбранную комнату.
 Rooms_Colors.RTSettings.Selected_room = NORTHERN_ROOM;

 // Заполняем список комнат.
 {
  // Задаем строки.
  INT Max_strings = 5; PCHAR Strings[ 5 ]; INT Count;
  for( Count = 0; Count < Max_strings; Count ++ ) DosAllocMem( (PPVOID) &Strings[ Count ], 256, PAG_ALLOCATE );

  if( Code_page == RUSSIAN )
   {
    strcpy( Strings[ 0 ], StrConst_RU_Pages_Rooms_colors_Room_titles_1 );
    strcpy( Strings[ 1 ], StrConst_RU_Pages_Rooms_colors_Room_titles_2 );
    strcpy( Strings[ 2 ], StrConst_RU_Pages_Rooms_colors_Room_titles_3 );
    strcpy( Strings[ 3 ], StrConst_RU_Pages_Rooms_colors_Room_titles_4 );
    strcpy( Strings[ 4 ], StrConst_RU_Pages_Rooms_colors_Room_titles_5 );
   }
  else
   {
    strcpy( Strings[ 0 ], StrConst_EN_Pages_Rooms_colors_Room_titles_1 );
    strcpy( Strings[ 1 ], StrConst_EN_Pages_Rooms_colors_Room_titles_2 );
    strcpy( Strings[ 2 ], StrConst_EN_Pages_Rooms_colors_Room_titles_3 );
    strcpy( Strings[ 3 ], StrConst_EN_Pages_Rooms_colors_Room_titles_4 );
    strcpy( Strings[ 4 ], StrConst_EN_Pages_Rooms_colors_Room_titles_5 );
   }

  {
   // Передаем строки окну списка.
   HWND ComboBox_window = WinWindowFromID( Page->Window, Rooms_Colors.Settings.Selected_room_cmbox_ID );

   INT Selected_room = Rooms_Colors.RTSettings.Selected_room;
   for( Count = 0; Count < Max_strings; Count ++ ) WinSendMsg( ComboBox_window, LM_INSERTITEM, (MPARAM) LIT_END, MPFROMP( Strings[ Count ] ) );
   Rooms_Colors.RTSettings.Selected_room = Selected_room;

   // Делаем выбранной первую строку списка.
   WinSendMsg( ComboBox_window, LM_SELECTITEM, MPFROMLONG( LIT_NONE ), MPFROMLONG( 1 ) );
   WinSendMsg( ComboBox_window, LM_SELECTITEM, MPFROMLONG( 0 ), MPFROMLONG( 1 ) );
  }

  // Освобождаем память.
  for( Count = 0; Count < Max_strings; Count ++ ) { DosFreeMem( Strings[ Count ] ); Strings[ Count ] = NULL; }
 }

 // Читаем цвета.
 {
  CHAR Settings_file_name[ SIZE_OF_PATH ] = ""; GetSettingsFileName( Settings_file_name );
  HINI Ini_file = OpenIniProfile( Enhancer.Application, Settings_file_name );

  ReadPainterSettingsForRooms( Ini_file );

  PrfCloseProfile( Ini_file );
 }

 // Возврат.
 return;
}

