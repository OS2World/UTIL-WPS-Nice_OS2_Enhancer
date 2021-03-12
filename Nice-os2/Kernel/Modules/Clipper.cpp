// ��⮤� ��� �뤥����� ��ப � �����.
#define PermissionForMarking               Clipper_PermissionForMarking
#define CopyPasteKeysCanBeUsedInVIOWindows Clipper_CopyPasteKeysCanBeUsedInVIOWindows

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Clipper_Start (VOID)
{
  #ifdef Clipper
  bzero (&Clipper, sizeof (Clipper));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Clipper_StartThread;
  Item.PostQuitMsg = Clipper_PostQuitMsg;
  Item.TuneModule  = Clipper_Tune;
  Item.SysValuesChangeReporter = Clipper_SysValuesChangeReporter;

  RememberModuleItem (Enhancer.Modules.Clipper, &Item);

  // ������.
  return;
}

