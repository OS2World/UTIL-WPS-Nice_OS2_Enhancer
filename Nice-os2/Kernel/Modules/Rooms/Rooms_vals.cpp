
// ��� ����頥� � ⮬, ����� 梥� � �����窥 OS/2 ������ ���� �������� ���

// Request_pointer - 㪠��⥫� �� ᯨ᮪ 梥⮢, ����� ����⥫� 㬥�� ��������.
VOID Rooms_SysColorsChangeReporter (PVOID Request_pointer)
{
  // �����ࠥ� 㪠��⥫�.
  PPREFERRED_SYSTEM_COLORS Request = (PPREFERRED_SYSTEM_COLORS) Request_pointer;

  // �஢��塞 ���.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_COLORS)) return;

  // ������ 梥�.
  if (Rooms.Settings.Create_Rooms)
  {
    Request->Set_black_desktop_background = 1;
  }

  // ������.
  return;
}
