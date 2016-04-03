
// ��� ��뢠�� ���� ᬥ�� ���� ���

// Frame_window - ⥪�⮢�� ����.
VOID VIOFontManager_OpenVIOFontMetricsDialog( HWND Frame_window )
{
 // �᫨ �� �࠭� 㦥 ���� ���� �롮� ���� - ������.
 if( SystemWindowIsPresent( FIND_VIO_FONT_DIALOG, FIND_VISIBLE_WINDOW ) ) return;

 // ������ ���� ���⨭��.
 HWND SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );

 // �᫨ ��� ��� - ������.
 if( !WinIsWindow( WinQueryAnchorBlock( SysMenu_window ), SysMenu_window ) ) return;

 // ������, ���� �� � ���� ��ப� ��� �맮�� ���� ᬥ�� ����.
 BYTE Menu_item_is_present = (LONG) WinSendMsg( SysMenu_window, MM_ISITEMVALID, MPFROM2SHORT( SM_VIO_FONT, INCLUDE_SUBMENUS ), 0 );

 // �᫨ ��� ����:
 if( Menu_item_is_present )
  {
   // ���뢠�� ����.
   WinShowWindow( Frame_window, 0 );

   // ���뫠�� � ���� ᮮ�饭�� �� ����.
   WinPostMsg( Frame_window, WM_SYSCOMMAND, (MPARAM) SM_VIO_FONT, MPFROM2SHORT( CMDSRC_MENU, 0 ) );

   // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� ������.
   HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SET_VIO_FONT, (MPARAM) Frame_window );
  }

 // ������.
 return;
}

// ��� �롨ࠥ� � ��� �ॡ㥬� ���� � �ਬ���� ��� ���

// Frame_window - ⥪�⮢�� ����.
VOID VIOFontManager_SubmitVIOFontMetricsDialog( HWND Frame_window )
{
 // ��室�� ���� � ᯨ᪮� ���⮢.
 HWND Font_dialog = NULLHANDLE;

 // ������ ���� ࠡ�祣� �⮫�.
 HWND Desktop = QueryDesktopWindow();

 {
  // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
  HENUM Enumeration = WinBeginEnumWindows( Desktop ); HWND Window = NULLHANDLE;
  while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // �᫨ ���� ���� - �த������ ��ॡ�� ����.
    if( !WinIsWindowVisible( Window ) ) continue;

    // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
    if( !IsFrameWindow( Window ) ) continue;

    // �᫨ �� ���� ��� �롮� ����:
    if( IsVIOFontMetricsDialog( Window ) )
     {
      // ������ ��� ��������:
      HWND Owner_frame = QueryFrameWindow( WinQueryWindow( Window, QW_OWNER ) );

      // �᫨ �� ⥪�⮢�� ����, ��� ���ண� ���� ������ ����:
      if( Owner_frame == Frame_window )
       {
        // ���������� ���� ��� �롮� ����.
        Font_dialog = Window;

        // �����蠥� ��ॡ�� ����.
        break;
       }
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // �᫨ ���� �������:
 if( Font_dialog != NULLHANDLE )
  {
   // ������ ࠧ��� ����.
   INT X = 0; INT Y = 0;

   // ��� �������� ���� ࠧ��� ���� ��࠭��.
   if( VIOFontManager_VIOFontIsPreDefined( Frame_window ) ) { X = 10; Y = 6; }

   // ������ ��� �ਫ������, ᮧ���襣� ����.
   CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

   // �᫨ ��� 㤠���� ��।�����:
   if( Exe_name[ 0 ] != 0 )
    {
     // ���������� ࠧ��� ����
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_1; Y = VIOFontManager.Settings.VIOFontMetrics.Y_1; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_2; Y = VIOFontManager.Settings.VIOFontMetrics.Y_2; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_3; Y = VIOFontManager.Settings.VIOFontMetrics.Y_3; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_4; Y = VIOFontManager.Settings.VIOFontMetrics.Y_4; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_5; Y = VIOFontManager.Settings.VIOFontMetrics.Y_5; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_6; Y = VIOFontManager.Settings.VIOFontMetrics.Y_6; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_7; Y = VIOFontManager.Settings.VIOFontMetrics.Y_7; }
     if( strc( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Exe_name ) ) { X = VIOFontManager.Settings.VIOFontMetrics.X_8; Y = VIOFontManager.Settings.VIOFontMetrics.Y_8; }
    }

   // �᫨ ���� �����:
   if( X != 0 && Y != 0 )
    {
     // �᫨ � ���� ������� �롮� ���⮢ ���� ���� ࠡ�祩 ������ - �ᯮ��㥬 ���.
     HWND Client_window = WinWindowFromID( Font_dialog, FID_CLIENT );
     if( Client_window != NULLHANDLE ) Font_dialog = Client_window;

     // ���⠢�塞 ��ப� ��� �롮� � ᯨ᪥.
     // ��ப ���, ⠪ ��� � ࠧ��� ������ OS/2 ����� �������� ��-ࠧ����.
     CHAR Metrics_X[ 25 ] = ""; itoa( X, Metrics_X, 10 );
     CHAR Metrics_Y[ 25 ] = ""; itoa( Y, Metrics_Y, 10 );

     CHAR String_without_spaces[ 25 ] = "";
     strcat( String_without_spaces, Metrics_X );
     strcat( String_without_spaces, " x " );
     strcat( String_without_spaces, Metrics_Y );

     CHAR String_with_spaces[ 25 ] = "";
     if( strlen( Metrics_X ) == 1 ) strcat( String_with_spaces, " " );
     strcat( String_with_spaces, Metrics_X );
     strcat( String_with_spaces, " x " );
     if( strlen( Metrics_Y ) == 1 ) strcat( String_with_spaces, " " );
     strcat( String_with_spaces, Metrics_Y );

     // ��室�� ��ப� � ᯨ᪥.
     HWND List_field = FindFontListField( Font_dialog ); LONG Index = LIT_NONE;

     if( Index == LIT_NONE )
      {
       strcpy( VIOFontManager.RTSettings.Item_text, String_without_spaces );
       Index = (LONG) WinSendMsg( List_field, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), VIOFontManager.RTSettings.Item_text );
      }

     if( Index == LIT_NONE )
      {
       strcpy( VIOFontManager.RTSettings.Item_text, String_with_spaces );
       Index = (LONG) WinSendMsg( List_field, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), VIOFontManager.RTSettings.Item_text );
      }

     // �᫨ ��� ����:
     if( Index != LIT_NONE )
      {
       // ������ �� ��࠭���.
       WinSendMsg( List_field, LM_SELECTITEM, (MPARAM) Index, (MPARAM) 1 );

       // ���⠢�塞 ᮮ�饭�� � ����⨨ ������ Enter.
       MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
       MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;
       ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, SC_NUM_ENTER, 0, 0 );

       // ���뫠�� ���.
       WinPostMsg( List_field, WM_CHAR, First_parameter_1, Second_parameter_1 );
       WinPostMsg( List_field, WM_CHAR, First_parameter_2, Second_parameter_2 );

       // ���� �����஥ �६�.
       for( INT Step = 0; Step < 12; Step ++ )
        {
         // ��⠭�������� �믮������ ��⮪�.
         Retard();
         // �᫨ ���� �롮� ���� �� �࠭� ��� - �४�頥� ��������.
         if( !SystemWindowIsPresent( FIND_VIO_FONT_DIALOG, FIND_VISIBLE_WINDOW ) ) break;
        }
      }

     // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���� ����� �㤥� ᤥ���� ������ � ��஢���� �� �।��� �࠭�.
     HMQ Message_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
     WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_SHOW_AND_ARRANGE, (MPARAM) Frame_window );
    }
  }

 // ������.
 return;
}
