
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID VIOMenuManager_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 VIOMenuManager_SetPreDefinedSettings( SET_ALL_SETTINGS );
 VIOMenuManager_ReadSettings( Ini_file );

 // ����������, �� ��⮪ ������ ���� ᮧ���.
 if( VIOMenuManager.Settings.SSH_Commands ) Enhancer.Modules.VIOMenuManager->Required = 1;

 // ������.
 return;
}

