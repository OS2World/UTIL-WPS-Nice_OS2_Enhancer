
// ��� �������� ��� � ���� � ᯨ᮪ ᢮��� ���

// Frame_window - ���� ࠬ��.
VOID WinPrpListAndRepository_RememberExeNameAndPath (HWND Frame_window)
{
  // ������ ���� � �ਫ������, ᮧ���襬� ����.
  PROCESSINFO Process_info = {0}; QueryProcessInfo (Frame_window, &Process_info, 0);

  PCHAR Name = Process_info.Exe_name;
  PCHAR Path = Process_info.Exe_path;

  // �᫨ ��� �� 㤠���� ��।����� - ������.
  if (Path[0] == 0) return;

  // �᫨ �� �ᯮ���⥫� ������ ��� ���� �� ��� �ᯮ����⥫��� �ணࠬ� - ������.
  if (IsCommandExecutorWindow (Process_info.Exe_name)) return;

  // ��⠭�������� ᢮��⢠.
  SetProperty (Frame_window, PRP_EXENAME, Name);
  SetProperty (Frame_window, PRP_EXEPATH, Path);

  // ������.
  return;
}
