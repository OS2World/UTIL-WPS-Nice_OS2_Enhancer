
// ��� ��ᯮ����� ⥬� ��� ࠬ�� ���

INT Themes_NeonTitleBarsDrawingRule( VOID )
{
  // ��ᯮ����� ⥬� ��� ࠬ��.
  BYTE Show_neon_color_controls = 0;

  if( Painter.Settings.Theme == PAINTER_THEME_CLASSIC_RGB ||
      Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW ) Show_neon_color_controls = 1;

 // ������.
 return Show_neon_color_controls;
}

// ��� ��ᯮ����� ⥬� ��� ࠬ�� ���

INT Themes_WinterTitleBarsDrawingRule( VOID )
{
  // ��ᯮ����� ⥬� ��� ࠬ��.
  BYTE Show_all_color_controls = Themes_NeonTitleBarsDrawingRule();

  if( Painter.Settings.Theme == PAINTER_THEME_WHITE_SNOW ) Show_all_color_controls = 0;

 // ������.
 return Show_all_color_controls;
}

// ��� �����뢠�� ���� ������� ���

VOID Themes_ShowWPSColorPalette( VOID )
{
 // �����뢠�� �������.
 CHAR Palette_name[ SIZE_OF_NAME ] = "";

 for( INT Step = 0; Step < 2; Step ++)
  {
   if( Step == 0 ) strcpy( Palette_name, "<WP_HIRESCLRPAL>" );
   if( Step == 1 ) strcpy( Palette_name, "<WP_LORESCLRPAL>" );

   HOBJECT Object = WinQueryObject( Palette_name );

   if( Object != NULLHANDLE )
    {
     WinOpenObject( Object, 0, 1 );
     break;
    }
  }

 // ������.
 return;
}

// ��� ���뢠�� ��� �����뢠�� "�������" � ���� ���

VOID Themes_RecognizeSelectedTheme( PTHEMEPAGEDEF Input_fields )
{
 // ���뢠�� ��� �����뢠�� ���� �����.
 BYTE Rule = Themes_NeonTitleBarsDrawingRule();

 WinShowWindow( Input_fields->NeonPalette_FillTB_window, Rule );
 WinShowWindow( Input_fields->NeonPalette_Container_window, Rule );

 Rule = Themes_WinterTitleBarsDrawingRule();

 WinShowWindow( Input_fields->NeonPalette_Active_1_window, Rule );
 WinShowWindow( Input_fields->NeonPalette_Active_3_window, Rule );
 WinShowWindow( Input_fields->NeonPalette_Inactive_1_window, Rule );
 WinShowWindow( Input_fields->NeonPalette_Inactive_3_window, Rule );

 // ������.
 return;
}

