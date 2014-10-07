
// ��� �����頥� ��� 䠩�� ����஥� ���

// File_name - 㪠��⥫� �� ��� 䠩��.
VOID EnhancerProperties_GetSettingsFileName( PCHAR File_name )
{
 // ������ ��� 䠩��.
 GetCurrentPath( File_name ); strcat( File_name, "\\Nice-os2.ini" );

 // ������.
 return;
}

// ��� �����頥� ��������� ��� ���� ����⥫� ���

// Title - 㪠��⥫� �� ���������.
VOID EnhancerProperties_GetEnhancerWindowTitle( PCHAR Title )
{
 // ������ ��������� ����.
 strcpy( Title, "Nice Enhancer" );

 // ������.
 return;
}

// ��� �����頥� ��������� ��� ���� ����⥫� ���

// Title - 㪠��⥫� �� ���������.
VOID EnhancerProperties_GetLoaderWindowTitle( PCHAR Title )
{
 // ������ ��������� ����.
 strcpy( Title, "Nice Launcher" );

 // ������.
 return;
}

// ��� ������ ����, �ᯮ��㥬� � ����� ����⥫� ���

// Window - ����, ��� ���ண� ���� ������ ����.
VOID EnhancerProperties_SetCommonEnhancerFont( HWND Window )
{
 // ������, �ᯮ���� �� Presentation Manager ����訥 �����.
 BYTE Large_fonts_enabled = 0;

 PCHAR FontSize_ptr = NULL; DosScanEnv( "SDDFONTSIZE", (PPCSZ) &FontSize_ptr );
 if( !FontSize_ptr || !strstr( "SMALL", FontSize_ptr ) ) Large_fonts_enabled = 1;

 PCHAR FontDPI_ptr = NULL; DosScanEnv( "SDDFONTDPI", (PPCSZ) &FontDPI_ptr );
 if( !FontDPI_ptr || !strstr( "96", FontDPI_ptr ) ) Large_fonts_enabled = 1;

 // ������ ����.
 if( !Large_fonts_enabled )
  {
   CHAR Font_name[] = "8.Helv"; WinSetPresParam( Window, PP_FONTNAMESIZE, strlen( Font_name ) + 1, Font_name );
  }
 else
  {
   CHAR Font_name[] = "9.WarpSans"; WinSetPresParam( Window, PP_FONTNAMESIZE, strlen( Font_name ) + 1, Font_name );
  }

 // ������.
 return;
}

// ��� ������ 梥�, �ᯮ��㥬� � ����� ����⥫� ���

// Window - ����, ��� ���ண� ���� ������ ����.
VOID EnhancerProperties_SetCommonEnhancerColors( HWND Window )
{
 // ������ 梥�.
 ULONG Gray_color = RGB_PALEGRAY; ULONG Clr_gray = CLR_PALEGRAY;
 WinSetPresParam( Window, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
 WinSetPresParam( Window, PP_BACKGROUNDCOLORINDEX, sizeof( Clr_gray ), (PVOID) &Clr_gray );
 WinSetPresParam( Window, PP_DISABLEDBACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
 WinSetPresParam( Window, PP_DISABLEDBACKGROUNDCOLORINDEX, sizeof( Clr_gray ), (PVOID) &Clr_gray );

 // ������.
 return;
}
