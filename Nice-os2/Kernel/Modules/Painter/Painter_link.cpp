
// ��� ����頥�, ����祭� �� �ᮢ���� ࠬ�� ���

BYTE Painter_DrawFramesSettingIsON( VOID )
{
 // �஢��塞 ����ன��.
 if( Painter.Settings.Draw_frames ) return 1;

 // ������.
 return 0;
}

// ��� ����頥�, ����祭� �� �ᮢ���� ���窮� � ���������� ���

BYTE Painter_DrawSystemMenusSettingIsON( VOID )
{
 // �஢��塞 ����ன��.
 if( Painter.Settings.Draw_system_menus ) return 1;

 // ������.
 return 0;
}

// ��� ����頥�, ����祭� �� �ᮢ���� ������ � ���������� ���

BYTE Painter_DrawButtonsSettingIsON( VOID )
{
 // �஢��塞 ����ன��.
 if( Painter.Settings.Draw_buttons ) return 1;

 // ������.
 return 0;
}

// ��� �⪫�砥� �ᮢ���� ࠬ�� ���

VOID Painter_DisableFrameDrawing( VOID )
{
 // �⪫�砥� ����ன�� ��� �ᮢ����.
 Painter.Settings.Draw_frames = 0;

 // ������.
 return;
}