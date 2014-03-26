
// ��� �����頥� 㪠��⥫� �� ������ � ᯨ᪥ ��࠭�� ����⥫� ���

// Position - ����� �����.
PPAGE PageList_GetPageListEntry( INT Position )
{
 // �஢��塞 ���祭��.
 if( Position < 0 || Position >= PAGELIST_LENGTH ) return NULL;

 // ����砥� 㪠��⥫�.
 PPAGE Pointer = &Enhancer.PageList[ Position ];

 // �஢��塞 ���.
 if( Pointer->cb != sizeof( PAGE ) ) Pointer = NULL;

 // ������.
 return Pointer;
}

// ��� �����⠢������ ���祭�� ��� ����ᥭ�� � ᯨ᮪ ���

// Item - ���祭�� ��� ᯨ᪠.
VOID PageList_PresetPageItem( PPAGE Item )
{
 // ������塞 ��६����� ��ﬨ.
 bzero( Item, sizeof( PAGE ) );

 // ���������� ����� ��������.
 Item->cb = sizeof( PAGE );

 // ������.
 return;
}

// ��� ������ ���祭�� � ᯨ᮪ ���

// Pointer - �㤠 �������� ���祭�� ��� ᯨ᪠, Item - ᠬ� ���祭��.
VOID PageList_RememberPageItem( PPAGE Pointer, PPAGE Item )
{
 // �᫨ ���祭�� ����୮ - ������.
 if( Item->cb != sizeof( PAGE ) ) return;

 // �᫨ � ᯨ᪥ 㦥 ��-� ���� - ������.
 if( Pointer->cb ) return;

 // ���������� ���祭��.
 memcpy( Pointer, Item, sizeof( PAGE ) );

 // ������.
 return;
}

// ��� ����뫠�� ᮮ�饭�� �ᥬ ����� ��࠭�� ���

VOID PageList_BroadcastMessage( ULONG Message, MPARAM First_parameter = 0, MPARAM Second_parameter = 0 )
{
 // ��ᬠ�ਢ��� ᯨ᮪ ��࠭�� � ���뫠�� ᮮ�饭��.
 for( INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
  {
   PPAGE Page = PageList_GetPageListEntry( Page_count );
   if( Page != NULL )
    if( Page->Present && Page->Window )
     {
      WinPostMsg( Page->Window, Message, First_parameter, Second_parameter );
     }
  }

 // ������.
 return;
}

