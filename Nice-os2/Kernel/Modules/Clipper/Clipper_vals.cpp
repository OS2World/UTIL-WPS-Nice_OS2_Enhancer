
// ��� ����頥� � ⮬, ����� ����ன�� � �����窥 OS/2 ������ ���� �������� ���

// Request_pointer - 㪠��⥫� �� ᯨ᮪ ����஥�, ����� ����⥫� 㬥�� ��������.
VOID Clipper_SysValuesChangeReporter( PVOID Request_pointer )
{
 // �����ࠥ� 㪠��⥫�.
 PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

 // �஢��塞 ���.
 if( Request->cb != sizeof( PREFERRED_SYSTEM_VALUES ) ) return;

 // �᫨ � ⥪�⮢�� ����� ���� �믮����� ����⢨� � ������� ���:
 if( Clipper.Settings.Mouse_in_VIO )
  {
   // �����塞 ���譨� ᯨ᮪.
   Request->Disable_VIO_mouse_actions = 1;
  }

 // ������.
 return;
}