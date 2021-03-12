// ��⮤� ��� ᫥����� �� ⥪�⮢묨 ������.

// ��� ��⮤ ��� ������祭�� ����� ���

VOID VIOMonitor_Start (VOID)
{
  #ifdef VIOMonitor
  bzero (&VIOMonitor, sizeof (VIOMonitor));
  #endif

  // ������ ����ﭭ� ����稭�.
  VIOMonitor.Constants.Retards_when_VIO_monitoring = 100;

  // ������ 㪠��⥫� � ᯨ᪥ ��⠢����� ����⥫�.
  MODULE Item; PresetModuleItem (&Item);

  Item.StartThread = VIOMonitor_StartThread;
  Item.PostQuitMsg = VIOMonitor_PostQuitMsg;
  Item.TuneModule  = VIOMonitor_Tune;

  RememberModuleItem (Enhancer.Modules.VIOMonitor, &Item);

  // ������.
  return;
}

