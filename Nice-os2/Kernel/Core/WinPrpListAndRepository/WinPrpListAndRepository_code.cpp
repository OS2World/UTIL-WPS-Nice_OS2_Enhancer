
// ��� ������ �������� �ਫ������, ᮧ���襣� ����, � ���������� ��� � ᯨ᪥ ᢮��� ���

// Frame_window - ���� ࠬ��, Name - ��ப� ��� ��������.
VOID WinPrpListAndRepository_GetDetectedExeName (HWND Frame_window, PCHAR Name)
{
  // ������, ���� �� ��� �ਫ������ � ᯨ᪥.
  Name[0] = 0; FindProperty (Frame_window, PRP_EXENAME, Name);

  // �᫨ ��� ���:
  if (Name[0] == 0)
  {
    // ������ ��� � ���������� � ᯨ᪥.
    WinPrpListAndRepository_RememberExeNameAndPath (Frame_window);

    // �롨ࠥ� ��� �� ᯨ᪠ �� ࠧ. ��� �� ࠢ�� ����� ���� �����.
    FindProperty (Frame_window, PRP_EXENAME, Name);
  }

  // ������.
  return;
}

// ��� ������ ���� � �ਫ������, ᮧ���襬� ����, � ���������� ��� � ᯨ᪥ ᢮��� ���

// Frame_window - ���� ࠬ��, Path - ��ப� ��� ��� � �ਫ������.
VOID WinPrpListAndRepository_GetDetectedExePath (HWND Frame_window, PCHAR Path)
{
  // ������, ���� �� ���� � �ਫ������ � ᯨ᪥.
  Path[0] = 0; FindProperty (Frame_window, PRP_EXEPATH, Path);

  // �᫨ ��� ���:
  if (Path[0] == 0)
  {
    // ������ ��� � ���������� � ᯨ᪥.
    WinPrpListAndRepository_RememberExeNameAndPath (Frame_window);

    // �롨ࠥ� ��� �� ᯨ᪠ �� ࠧ. ���� �� ࠢ�� ����� ���� �����.
    FindProperty (Frame_window, PRP_EXEPATH, Path);
  }

  // ������.
  return;
}

// ��� �롨ࠥ� ��������� ���� �� ᯨ᪠ ᢮��� ��� 㧭��� ��� ���

// Frame_window - ���� ࠬ��, Title - ��ப� ��� ���������.
VOID WinPrpListAndRepository_GetDetectedWindowTitle (HWND Frame_window, PCHAR Title)
{
  // �஡㥬 ���� ���� � ᯨ᪥ ᢮��� � 㧭��� ��� ���������.
  Title[0] = 0; FindProperty (Frame_window, PRP_TITLE, Title);

  // �᫨ �� ᤥ���� �� 㤠���� - 㧭��� ��������� ����.
  if (Title[0] == 0) QueryWindowTitle (Frame_window, WinWindowFromID (Frame_window, FID_TITLEBAR), Title, 0);

  // ������.
  return;
}
