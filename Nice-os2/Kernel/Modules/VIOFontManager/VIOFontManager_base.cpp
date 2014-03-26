// ��� �஢����, ������ �� ��� �⮣� ���� ���� ����� �����쪨� ���� ���

// Frame_window - ⥪�⮢�� ����.
BYTE VIOFontManager_VIOFontIsPreDefined( HWND Frame_window )
{
 // �᫨ ���� ��� �������� ����⥫� ���� ������ �� ���� - ������.
 if( !VIOFontManager.Settings.Change_fonts_for_known_applications ) return 0;

 // ��� �������� ���� �㦥� �����쪨� ����.
 if( WindowIsCreatedBy( APP_DN, Frame_window ) ) return 1;
 if( WindowIsCreatedBy( APP_SSH, Frame_window ) ) return 1;
 if( WindowIsCreatedBy( APP_ZMP3, Frame_window ) ) return 1;

 // ������.
 return 0;
}

// ��� �஢����, ����� �� ���� ��� ⥪�⮢��� ���� ���

// Frame_window - ⥪�⮢�� ����.
BYTE VIOFontManager_VIOFontMustBeChanged( HWND Frame_window )
{
 // �᫨ ����ன�� �⪫�祭� - ������.
 if( !VIOFontManager.Settings.Change_VIO_font_metrics ) return 0;

 // ����ਬ, ���� �� ������ ����.
 BYTE Change_font = 0;

 // ��� �������� ���� ����� ������ ��࠭��.
 if( VIOFontManager_VIOFontIsPreDefined( Frame_window ) ) Change_font = 1;

 // ������ ��� �ਫ������, ᮧ���襣� ����.
 CHAR Exe_name[ SIZE_OF_NAME ] = ""; GetDetectedExeName( Frame_window, Exe_name );

 // �᫨ ��� 㤠���� ��।�����:
 if( Exe_name[ 0 ] != 0 )
  {
   // ����ਬ, ���� �� ��� � ᯨ᪥.
   if( ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_1_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_1 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_1 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_2_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_2 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_2 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_3_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_3 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_3 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_4_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_4 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_4 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_5_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_5 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_5 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_6_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_6 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_6 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_7_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_7 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_7 != 0 ) ||
       ( strcmp( VIOFontManager.Settings.VIOFontMetrics.Shell_8_name, Exe_name ) == EQUALLY && VIOFontManager.Settings.VIOFontMetrics.X_8 != 0 && VIOFontManager.Settings.VIOFontMetrics.Y_8 != 0 ) )
    {
     Change_font = 1;
    }
  }

 // ������.
 return Change_font;
}
