// ��⮤� ��� ����祭�� ᮮ�饭�� �� ����⨨ �� ������.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID MMKbdListener_Start (VOID)
{
  #ifdef MMKbdListener
  bzero (&MMKbdListener, sizeof (MMKbdListener));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = MMKbdListener_StartThread;
  Item.PostQuitMsg = MMKbdListener_PostQuitMsg;
  Item.TuneModule  = MMKbdListener_Tune;

  RememberModuleItem (Enhancer.Modules.MMKbdListener, &Item);

  // ������.
  return;
}

