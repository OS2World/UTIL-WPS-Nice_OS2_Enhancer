// ��⮤� ��� �믮������ ࠧ����� ����⢨�.
#define HideShellToolbarMenu        Launcher_HideShellToolbarMenu

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Launcher_Start (VOID)
{
  #ifdef Launcher
  bzero (&Launcher, sizeof (Launcher));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Launcher_StartThread;
  Item.PostQuitMsg = Launcher_PostQuitMsg;
  Item.TuneModule  = Launcher_Tune;

  RememberModuleItem (Enhancer.Modules.Launcher, &Item);

  // ������.
  return;
}

