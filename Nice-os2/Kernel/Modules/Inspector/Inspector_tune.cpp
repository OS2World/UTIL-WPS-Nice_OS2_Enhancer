
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Inspector_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 Inspector_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Inspector_ReadSettings( Ini_file );

 // ����������, �� ��⮪ ������ ���� ᮧ���.
 Enhancer.Modules.Inspector->Required = 1;

 // ������.
 return;
}
