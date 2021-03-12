
// ��� ��뢠���� �� �����襭�� �ਫ������ ���

VOID APIENTRY Loader_ExitListHook (ULONG Termination_code)
{
  // ��뢠�� Nice-os2.dll � ᮮ�饭��� � �����襭�� �ਫ������.
  if (Loader.Dll_calls.ApplicationIsKilled) Loader.Dll_calls.ApplicationIsKilled ();

  // ��室.
  DosExit (EXIT_PROCESS, 0);
}

// ��� ������� ��⮪�, ��⠭�������� ��ࠡ��稪� ᮡ�⨩ ���

// Application ��।���� �ਫ������. �����頥� 1 ��� 0.
BYTE Loader_NiceLoadEnhancer (HAB Application, BYTE Nice_is_visible, HWND Launcher_window)
{
  // ������ ��⠫��, � ���஬ ࠡ�⠥� �ਫ������.
  CHAR Path_to_module[SIZE_OF_PATH] = ""; GetCurrentPath (Path_to_module);

  // ������塞 ��� � ᯨ᮪ ��⠫���� "LIBPATH".
  DosSetExtLIBPATH (Path_to_module, BEGIN_LIBPATH);

  // ������ ����� ���� � Nice-os2.dll.
  if (strlen (Path_to_module) > 3) strcat (Path_to_module, "\\");
  strcat (Path_to_module, "Nice-os2.dll");

  // ����㦠�� Nice-os2.dll � ������砥� �맮��.
  if (DosLoadModule (NULL, 0, Path_to_module, &Loader.Dll_calls.Module) != NO_ERROR) return 0;

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_StartKernel", (PFN*) &Loader.Dll_calls.StartKernel);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_HeyHoLetsGo", (PFN*) &Loader.Dll_calls.HeyHoLetsGo);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ShutdownKernel", (PFN*) &Loader.Dll_calls.ShutdownKernel);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ApplicationIsKilled", (PFN*) &Loader.Dll_calls.ApplicationIsKilled);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ReadSettings", (PFN*) &Loader.Dll_calls.ReadSettings);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Krnl_ReadRepository", (PFN*) &Loader.Dll_calls.ReadRepository);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_InputHook", (PFN*) &Loader.Dll_calls.InputHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_KbdInputHook", (PFN*) &Loader.Dll_calls.KbdInputHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_SendMsgHook", (PFN*) &Loader.Dll_calls.SendMsgHook);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Hook_LockupHook", (PFN*) &Loader.Dll_calls.LockupHook);

  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanMessageDialog", (PFN*) &Loader.Dll_calls.ScanMessageDialog);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanIncompleteDialog", (PFN*) &Loader.Dll_calls.ScanIncompleteDialog);
  DosQueryProcAddr (Loader.Dll_calls.Module, 0, "Applier_ScanLogonDialog", (PFN*) &Loader.Dll_calls.ScanLogonDialog);

  // �᫨ �� �� ��⮤� ��� ����᪠ ����⥫� �뫨 ����㦥�� - ������.
  if (!Loader.Dll_calls.StartKernel || !Loader.Dll_calls.HeyHoLetsGo) return 0;

  // ����砥� ����⥫�.
  Loader.Dll_calls.StartKernel (Application, Loader.Dll_calls.Module, Nice_is_visible, Launcher_window);
  Loader.Dll_calls.StartKernel = NULL;

  // ��⠭�������� ��ࠡ��稪� ᮡ�⨩. ��� ���� ����⢮���� ��� ��� ��।�� ᮮ�饭��,
  // � ��� ��� ����. ����� ����� �⠢��� ᢮� ��ࠡ��稪 ��� ������ ��।�, � �᫨ ����
  // � OS/2 �㤥� ���஥�� �����-����� "����" ��� � Windows NT, � ����� ⠪ � ����㯨��.
  if (Loader.Dll_calls.InputHook)
  {
    Loader.Hooks.InputHook_type = HK_INPUT;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.InputHook_type, (PFN) Loader.Dll_calls.InputHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.KbdInputHook)
  {
    Loader.Hooks.KbdInputHook_type = HK_PREACCEL;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.KbdInputHook_type, (PFN) Loader.Dll_calls.KbdInputHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.SendMsgHook)
  {
    Loader.Hooks.SendMsgHook_type = HK_SENDMSG;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.SendMsgHook_type, (PFN) Loader.Dll_calls.SendMsgHook, Loader.Dll_calls.Module);
  }

  if (Loader.Dll_calls.LockupHook)
  {
    Loader.Hooks.LockupHook_type = HK_LOCKUP;
    WinSetHook (Application, ALL_QUEUES, Loader.Hooks.LockupHook_type, (PFN) Loader.Dll_calls.LockupHook, Loader.Dll_calls.Module);
  }

  // ��⠭�������� ��ࠡ��稪 �᪫�祭��, ����� ������ ��뢠���� � ��砥,
  // �᫨ ����⥫� �ਡ����� � WatchCat ��� � ������� ���譥� ������� "Kill".
  DosExitList (EXLST_ADD, Loader_ExitListHook);

  // ������.
  return 1;
}


// ��� ����砥� ᫥����� �� ᮮ�饭�ﬨ ���

VOID Loader_NiceRunEnhancer (VOID)
{
  // ����砥� ᫥����� �� ᮮ�饭�ﬨ.
  if (Loader.Dll_calls.HeyHoLetsGo)
  {
    Loader.Dll_calls.HeyHoLetsGo ();
    Loader.Dll_calls.HeyHoLetsGo = NULL;
  }

  // ������.
  return;
}

// ��� ��⠥� ����ன�� ���

// ��뢠���� �� ��������� ����஥� ���짮��⥫��.
// Update_windows - ���� �� �������� �� ����.
VOID Loader_NiceReadSettings (BYTE Update_windows = 0, BYTE Arrange_windows = 0)
{
  // ��⠥� ����ன��, ����� ᮤ�ঠ��� � Nice-OS2.ini.
  if (Loader.Dll_calls.ReadSettings) Loader.Dll_calls.ReadSettings (Update_windows, Arrange_windows);

  // ������.
  return;
}

// ��� ��⠥� ᯨ᮪ �ਫ������ ���

// ��뢠���� �� ��������� ᯨ᪠ �ਫ������.
VOID Loader_NiceReadRepository (VOID)
{
  // ��⠥� ����ன��, ����� ᮤ�ঠ��� � Nice-OS2.ini.
  if (Loader.Dll_calls.ReadRepository) Loader.Dll_calls.ReadRepository ();

  // ������.
  return;
}

// ��� ����ࠥ� ᢥ����� �� ���� ����� ��஫� ���

// Window - ���� ����� ��஫�.
VOID Loader_NiceScanLogonDialog (HWND Window)
{
  // ������ ᢥ����� �� ����.
  if (Loader.Dll_calls.ScanLogonDialog) Loader.Dll_calls.ScanLogonDialog (Window);

  // ������.
  return;
}

// ��� ����ࠥ� ᢥ����� �� ���� ������� ���

// Window - ���� �������.
VOID Loader_NiceScanIncompleteDialog (HWND Window)
{
  // ������ ᢥ����� �� ����.
  if (Loader.Dll_calls.ScanIncompleteDialog) Loader.Dll_calls.ScanIncompleteDialog (Window);

  // ������.
  return;
}

// ��� ����ࠥ� ᢥ����� �� ���� ᮮ�饭�� ���

// Window - ���� ᮮ�饭��.
VOID Loader_NiceScanMessageDialog (HWND Window)
{
  // ������ ᢥ����� �� ����.
  if (Loader.Dll_calls.ScanMessageDialog) Loader.Dll_calls.ScanMessageDialog (Window);

  // ������.
  return;
}

// ��� �⪫�砥� ��ࠡ��稪� ᮡ�⨩, �����蠥� ࠡ��� ��⮪�� ���

// Application ��।���� �ਫ������, Nice_is_visible - ����㯭� �� ���� Nice ���짮��⥫�.
VOID Loader_NiceReleaseEnhancer (HAB Application, BYTE Nice_is_visible)
{
  // �⪫�砥� ��ࠡ��稪 �᪫�祭��.
  DosExitList (EXLST_REMOVE, Loader_ExitListHook);

  // �⪫�砥� ��ࠡ��稪� ᮡ�⨩.
  if (Loader.Hooks.InputHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.InputHook_type, (PFN) Loader.Dll_calls.KbdInputHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.KbdInputHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.KbdInputHook_type, (PFN) Loader.Dll_calls.InputHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.SendMsgHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.SendMsgHook_type, (PFN) Loader.Dll_calls.SendMsgHook, Loader.Dll_calls.Module);
  if (Loader.Hooks.LockupHook_type) WinReleaseHook (Application, ALL_QUEUES, Loader.Hooks.LockupHook_type, (PFN) Loader.Dll_calls.LockupHook, Loader.Dll_calls.Module);

  // �����蠥� ࠡ��� ��⮪�� ����� ����⥫�.
  if (Loader.Dll_calls.ShutdownKernel)
  {
    Loader.Dll_calls.ShutdownKernel (Nice_is_visible);
    Loader.Dll_calls.ShutdownKernel = NULL;
  }

  // ����뢠�� �� ����७��� ��६���� � 㪠��⥫� �� �맮��.
  bzero (&Loader, sizeof (LOADER));

  // ����� ���� �⪫���� Nice-os2.dll... �� � �������� ����� �� ��뢠�� �訡��.
  // ����⭮, DLL ����⥫� �⪫�砥��� ᠬ�� �����窮�.
  /* DosFreeModule (Loader.Dll_calls.Module); */

  // ������.
  return;
}

