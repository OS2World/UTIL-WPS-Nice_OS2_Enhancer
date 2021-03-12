
// ��� �����襭�� ࠡ��� ���

VOID Rooms_ShutdownAll (VOID)
{
  // ������ ���� ࠡ�祣� �⮫�.
  HWND Desktop = QueryDesktopWindow ();

  // �᫨ ���� ����, ���஥ �࠭� ������ - ����⠭�������� ���.
  if (RolledWindow ()) UnrollWindow (RolledWindow ());

  // ���室�� � ������� � ����� �����窨.
  if (GetCurrentOrNextRoom () != SHELL_ROOM) Rooms_GoToRoom (SHELL_ROOM);

  // ����뢠�� ���� ࠡ�祣� �⮫�, �ᯮ������� � �������.
  Rooms_RestoreAndCloseOuterWPSWindows (Desktop);

  // ������ �� ���� ����㯭묨 ��� ��४��祭��.
  SetAllWindowsJumpable (Desktop);

  // ����뢠�� ����ࠦ���� ��� ����訢���� ࠡ�祣� �⮫�.
  Rooms_DeleteDesktopWallpaper ();

  // ������.
  return;
}