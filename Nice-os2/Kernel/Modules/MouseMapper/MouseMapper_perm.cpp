
// ��� �஢����, ����� �� ��४����� ���� �� ���������� � ���� ���

// Frame_window - ���� ࠬ��, � ���஬ ���� �����⢨�� ��४��祭�� ����� �� ����������.
BYTE MouseMapper_PermissionForInputFocusMoving (HWND Frame_window)
{
  // � �������� ����� ��४����� ���� �� ����.
  if (WindowIsCreatedBy (APP_PMDIFF, Frame_window)) return 0;

  // ������.
  return 1;
}

