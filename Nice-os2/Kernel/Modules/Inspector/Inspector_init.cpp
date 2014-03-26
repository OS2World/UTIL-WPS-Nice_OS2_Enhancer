
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Inspector_SetPreDefinedSettings( LONG Division )
{
 // ������ ����⢨� ��� ᯨ᪠ �������� �ਫ������.
 if( Division == SET_ALL_SETTINGS || Division == SET_KEYBOARD )
  {
   Inspector.Settings.Check_Repository = 1;
  }

 // ������.
 return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Inspector_ReadSettings( HINI Ini_file )
{
 // ��⠥� ����ன��.
 ULONG Byte = 0; ULONG Byte_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Repository", "Check Repository", &Byte_data, &Byte ) ) Inspector.Settings.Check_Repository = Byte_data;

 // ������.
 return;
}
