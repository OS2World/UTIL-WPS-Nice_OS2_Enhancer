// ��⮤� ��� �ਬ������ "�����⮪" � �����窥 OS/2.
#define DisableAnimation Patcher_DisableAnimation

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Patcher_Start (VOID)
{
  #ifdef Patcher
  bzero (&Patcher, sizeof (Patcher));
  #endif

  // ������ ����ﭭ� ����稭�.
  Patcher.Constants.Big_WarpCenter = 26;
  Patcher.Constants.Big_WarpCenter_X1 = 50;
  Patcher.Constants.Big_WarpCenter_X2 = 77;

  Patcher.Constants.Small_WarpCenter = 22;
  Patcher.Constants.Small_WarpCenter_X1 = 41;
  Patcher.Constants.Small_WarpCenter_X2 = 64;

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.TuneModule = Patcher_Tune;

  RememberModuleItem (Enhancer.Modules.Patcher, &Item);

  // ������.
  return;
}

