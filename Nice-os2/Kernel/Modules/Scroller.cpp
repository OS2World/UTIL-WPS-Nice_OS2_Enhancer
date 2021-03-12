// ��⮤� ��� ��।������� ����ࠦ���� � �����.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Scroller_Start (VOID)
{
  #ifdef Scroller
  bzero (&Scroller, sizeof (Scroller));
  #endif

  // ������ ����ன�� �� 㬮�砭��.
  Scroller.RTSettings.Step_of_scrolling = 1;

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = Scroller_StartThread;
  Item.PostQuitMsg = Scroller_PostQuitMsg;
  Item.TuneModule  = Scroller_Tune;

  RememberModuleItem (Enhancer.Modules.Scroller, &Item);

  // ������.
  return;
}

