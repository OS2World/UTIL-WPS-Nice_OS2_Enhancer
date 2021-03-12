// ��⮤� ��� �믮������ ����⢨� � ������ ��������.
#define MakeLogonWindowTitle   Applier_MakeLogonWindowTitle

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Applier_Start (VOID)
{
  #ifdef Applier
  bzero (&Applier, sizeof (Applier));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread  = Applier_StartThread;
  Item.PostQuitMsg  = Applier_PostQuitMsg;
  Item.TuneModule   = Applier_Tune;
  Item.JumpBeforeGo = Applier_Jump;

  RememberModuleItem (Enhancer.Modules.Applier, &Item);

  // ������.
  return;
}

