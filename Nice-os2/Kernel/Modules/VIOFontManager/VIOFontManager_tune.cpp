
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID VIOFontManager_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 VIOFontManager_SetPreDefinedSettings( SET_ALL_SETTINGS );
 VIOFontManager_ReadSettings( Ini_file );

 // ����������, ����� ��⮪� �� ������ ���� ᮧ����.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) Enhancer.Modules.VIOMonitor->Required = 1;

 // ������.
 return;
}
