
// ��� ��⠭�������� ����ன�� �� 㬮�砭�� ���

// Division - ����� ����ன�� ���� ��⠭�����.
VOID Applier_SetPreDefinedSettings( LONG Division )
{
 // ������ ����ன��.
 if( Division == SET_ALL_SETTINGS || Division == SET_DIALOG_BOXES )
  {
   Applier.Settings.Script_after_Logon = 0;
   Applier.Settings.Remember_dialog_fields = 0;
   Applier.Settings.Send_Yes = 0;
  }

 #ifndef INCLUDED_BY_SHELL

 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &Applier.Settings.Dialogs, sizeof( DIALOGS ) );
  }

 #endif

 // ������.
 return;
}

// ��� ��⠥� ����ன�� ���

// Ini_file - 䠩� ����஥�.
VOID Applier_ReadSettings( HINI Ini_file )
{
 // ��⠥� ����ன��.
 ULONG Byte = 0; ULONG Byte_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Script after Logon", &Byte_data, &Byte ) ) Applier.Settings.Script_after_Logon = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Remember dialog fields", &Byte_data, &Byte ) ) Applier.Settings.Remember_dialog_fields = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Send Yes", &Byte_data, &Byte ) ) Applier.Settings.Send_Yes = Byte_data;

 // ������.
 return;
}