
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Krnl_Repository_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 Krnl_Repository_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Krnl_Repository_ReadSettings( Ini_file );

 // ����������, �� ᯨ᮪ �ਫ������ �� ���⥭.
 Krnl_Repository.RTSettings.Repository_is_ready = 1;

 // ������.
 return;
}