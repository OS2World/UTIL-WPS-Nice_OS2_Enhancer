
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Clipper_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 Clipper_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Clipper_ReadSettings( Ini_file );

 // ����������, �� ��⮪ ������ ���� ᮧ���.
 if( Clipper.Settings.CopyPaste_keys_in_VIO || Clipper.Settings.Mouse_in_VIO ) Enhancer.Modules.Clipper->Required = 1;

 // ������.
 return;
}
