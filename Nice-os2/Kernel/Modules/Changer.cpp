// ��⮤� ��� ��������� ᢮��� ����.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Changer_Start (VOID)
{
  #ifdef Changer
  bzero (&Changer, sizeof (Changer));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Changer_StartThread;
  Item.PostQuitMsg = Changer_PostQuitMsg;
  Item.TuneModule  = Changer_Tune;

  RememberModuleItem (Enhancer.Modules.Changer, &Item);

  // ������.
  return;
}

