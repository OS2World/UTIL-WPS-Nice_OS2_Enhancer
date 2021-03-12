
// ��� �஢����, ����� �� ��४������� � ���� �� ��८�।������ ������ ���

// Window - ����. �����頥��� ���祭��: 1, �᫨ �����, 0, �᫨ �����.
BYTE Launcher_PermissionForHotKeySwitching (HWND Window)
{
  // �᫨ � ���� ����� ����� ��४������� - ������.
  if (!PermissionForSwitching (Window)) return 0;

  // �᫨ �� �� ���� ������� � � ���� ����� ��४������� �� Alt + Tab - ������.
  if (!WindowIsAppDialog (Window)) if (!WindowIsJumpable (Window)) return 0;

  // �᫨ �� �� ���� Win-OS/2 ��� Odin:
  if (!IsWindowsWindow (Window))
  {
    // �᫨ ���� ��������� �� �������� - ��४������� �� ����, ������.
    if (!WindowIsPresent (WinWindowFromID (Window, FID_TITLEBAR))) return 0;
  }

  // �᫨ ���� �࠭� ������ - ��४������� �� ����, ������.
  if (WindowIsRolled (Window)) return 0;

  // ������.
  return 1;
}
