
// ��� ����頥� � ⮬, ����� ����ன�� � �����窥 OS/2 ������ ���� �������� ���

// Request_pointer - 㪠��⥫� �� ᯨ᮪ ����஥�, ����� ����⥫� 㬥�� ��������.
VOID Definer_SysValuesChangeReporter( PVOID Request_pointer )
{
 // �����ࠥ� 㪠��⥫�.
 PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

 // �஢��塞 ���.
 if( Request->cb != sizeof( PREFERRED_SYSTEM_VALUES ) ) return;

 // �᫨ ������ PrtScr �뫠 ��८�।�����:
 if( Definer.Settings.Keys.PrtScr || Definer.Settings.Keys.SysRq )
  {
   // �����塞 ���譨� ᯨ᮪.
   Request->Disable_PrintScreen = 1;
  }

 // ������.
 return;
}