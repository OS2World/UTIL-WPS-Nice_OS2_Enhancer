
// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Patcher_Tune( HINI Ini_file )
{
 // ��⠥� ����ன��.
 Patcher_SetPreDefinedSettings( SET_ALL_SETTINGS );
 Patcher_ReadSettings( Ini_file );

 // �⪫�砥� ���⠢�� ��� ���� �����窨.
 if( Patcher.Settings.Limited_animation ) Patcher_DisableAnimation( GetDetectedShellWindow() );

 // ������.
 return;
}