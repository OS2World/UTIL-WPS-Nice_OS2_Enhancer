
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Arranger_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 Arranger_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Arranger_ReadSettings( Ini_file );

 // ����������, �� ��⮪ ������ ���� ᮧ���.
 Enhancer.Modules.Arranger->Required = 1;

 // ������.
 return;
}
