// ��⮤� ��� �믮������ ����⢨� �� ����⨨ �� ������.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Definer_Start (VOID)
{
  #ifdef Definer
  bzero (&Definer, sizeof (Definer));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.TuneModule = Definer_Tune;
  Item.SysValuesChangeReporter = Definer_SysValuesChangeReporter;

  RememberModuleItem (Enhancer.Modules.Definer, &Item);

  // ������.
  return;
}

