
// ��� �஢����, ����� �� �믮����� �뤥����� ��ப � ⥪�⮢�� ���� ���

// Frame_window - ⥪�⮢�� ����.
BYTE Clipper_PermissionForMarking (HWND Frame_window)
{
  // ������� �ਫ������ 㬥�� �롨��� � ���������� ��ப� ᠬ����⥫쭮.
  if (WindowIsUsedTo (DO_MANAGE_FILES, Frame_window)) return 0;
  if (IsGoldEdWindow (Frame_window)) return 0;

  // �� � ���浪�, ������.
  return 1;
}
