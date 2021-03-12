// ��⮤� ��� �믮������ ����⢨� �� ����⨨ �� ������ � ��������� ����.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID WindowManager_Start (VOID)
{
  #ifdef WindowManager
  bzero (&WindowManager, sizeof (WindowManager));
  #endif

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = WindowManager_StartThread;
  Item.PostQuitMsg = WindowManager_PostQuitMsg;
  Item.TuneModule  = WindowManager_Tune;

  RememberModuleItem (Enhancer.Modules.WindowManager, &Item);

  // ������.
  return;
}

