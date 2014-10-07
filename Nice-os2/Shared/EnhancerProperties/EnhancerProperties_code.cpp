
// ─── Возвращает имя файла настроек ───

// File_name - указатель на имя файла.
VOID EnhancerProperties_GetSettingsFileName( PCHAR File_name )
{
 // Задаем имя файла.
 GetCurrentPath( File_name ); strcat( File_name, "\\Nice-os2.ini" );

 // Возврат.
 return;
}

// ─── Возвращает заголовок для окна расширителя ───

// Title - указатель на заголовок.
VOID EnhancerProperties_GetEnhancerWindowTitle( PCHAR Title )
{
 // Задаем заголовок окна.
 strcpy( Title, "Nice Enhancer" );

 // Возврат.
 return;
}

// ─── Возвращает заголовок для окна расширителя ───

// Title - указатель на заголовок.
VOID EnhancerProperties_GetLoaderWindowTitle( PCHAR Title )
{
 // Задаем заголовок окна.
 strcpy( Title, "Nice Launcher" );

 // Возврат.
 return;
}

// ─── Задает шрифт, используемый в окнах расширителя ───

// Window - окно, для которого надо задать шрифт.
VOID EnhancerProperties_SetCommonEnhancerFont( HWND Window )
{
 // Узнаем, использует ли Presentation Manager большие шрифты.
 BYTE Large_fonts_enabled = 0;

 PCHAR FontSize_ptr = NULL; DosScanEnv( "SDDFONTSIZE", (PPCSZ) &FontSize_ptr );
 if( !FontSize_ptr || !strstr( "SMALL", FontSize_ptr ) ) Large_fonts_enabled = 1;

 PCHAR FontDPI_ptr = NULL; DosScanEnv( "SDDFONTDPI", (PPCSZ) &FontDPI_ptr );
 if( !FontDPI_ptr || !strstr( "96", FontDPI_ptr ) ) Large_fonts_enabled = 1;

 // Задаем шрифт.
 if( !Large_fonts_enabled )
  {
   CHAR Font_name[] = "8.Helv"; WinSetPresParam( Window, PP_FONTNAMESIZE, strlen( Font_name ) + 1, Font_name );
  }
 else
  {
   CHAR Font_name[] = "9.WarpSans"; WinSetPresParam( Window, PP_FONTNAMESIZE, strlen( Font_name ) + 1, Font_name );
  }

 // Возврат.
 return;
}

// ─── Задает цвета, используемые в окнах расширителя ───

// Window - окно, для которого надо задать шрифт.
VOID EnhancerProperties_SetCommonEnhancerColors( HWND Window )
{
 // Задаем цвета.
 ULONG Gray_color = RGB_PALEGRAY; ULONG Clr_gray = CLR_PALEGRAY;
 WinSetPresParam( Window, PP_BACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
 WinSetPresParam( Window, PP_BACKGROUNDCOLORINDEX, sizeof( Clr_gray ), (PVOID) &Clr_gray );
 WinSetPresParam( Window, PP_DISABLEDBACKGROUNDCOLOR, sizeof( Gray_color ), (PVOID) &Gray_color );
 WinSetPresParam( Window, PP_DISABLEDBACKGROUNDCOLORINDEX, sizeof( Clr_gray ), (PVOID) &Clr_gray );

 // Возврат.
 return;
}
