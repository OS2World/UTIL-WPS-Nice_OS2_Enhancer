
// ��� �����頥� 㪠��⥫� �� ������ � ᯨ᪥ ��⠢����� ����⥫� ���

// Position - ����� �����.
PMODULE ModList_GetModListEntry( INT Position )
{
 // �஢��塞 ���祭��.
 if( Position < 0 || Position >= MODLIST_LENGTH ) return NULL;

 // ����砥� 㪠��⥫�.
 PMODULE Pointer = &Enhancer.ModList[ Position ];

 // �஢��塞 ���.
 if( Pointer->cb != sizeof( MODULE ) ) Pointer = NULL;

 // ������.
 return Pointer;
}

// ��� �����⠢������ ���祭�� ��� ����ᥭ�� � ᯨ᮪ ���

// Item - ���祭�� ��� ᯨ᪠.
VOID ModList_PresetModuleItem( PMODULE Item )
{
 // ������塞 ��६����� ��ﬨ.
 bzero( Item, sizeof( MODULE ) );

 // ���������� ����� ��������.
 Item->cb = sizeof( MODULE );

 // ������.
 return;
}

// ��� ������ ���祭�� � ᯨ᮪ ���

// Pointer - �㤠 �������� ���祭�� ��� ᯨ᪠, Item - ᠬ� ���祭��.
VOID ModList_RememberModuleItem( PMODULE Pointer, PMODULE Item )
{
 // �᫨ ���祭�� ����୮ - ������.
 if( Item->cb != sizeof( MODULE ) ) return;

 // �᫨ � ᯨ᪥ 㦥 ��-� ���� - ������.
 if( Pointer->cb ) return;

 // ���������� ���祭��.
 memcpy( Pointer, Item, sizeof( MODULE ) );

 // ������.
 return;
}

