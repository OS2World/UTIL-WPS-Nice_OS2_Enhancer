
// ��� ��⮤ ��� ������祭�� ����� ���

VOID Inspector_Start (VOID)
{
  #ifdef Inspector
  bzero (&Inspector, sizeof (Inspector));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread  = Inspector_StartThread;
  Item.PostQuitMsg  = Inspector_PostQuitMsg;
  Item.TuneModule   = Inspector_Tune;

  RememberModuleItem (Enhancer.Modules.Inspector, &Item);

  // ������.
  return;
}

