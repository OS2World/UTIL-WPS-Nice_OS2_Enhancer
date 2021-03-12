
// ��� ��室�� � ���� ������ 䠩�� ���室�饥 ���� ����� ���

// Frame_window - ���� ࠬ��.
HWND FileDialogs_FindFieldInFileDialog (HWND Frame_window)
{
  // ������ ���� ����� ��� ����� 䠩��, �ᯮ���� ���祭��, �� ���஬� ��� ����� ���� ������ � ���筮� �������.
  HWND Field = WinWindowFromID (Frame_window, FDLG_ENTRY_FIELD);

  // �᫨ �� �� ���� ����� - ���� ���� ��� ��㣨� ᯮᮡ��.
  if (Field == NULLHANDLE || !IsEntryFieldWindow (Field))
  {
    // ��⠥�, �� ���� ����� �������⭮.
    if (Field != NULLHANDLE) Field = NULLHANDLE;

    // ��ॡ�ࠥ� ���� � ���� ࠬ��.
    HENUM Enumeration = WinBeginEnumWindows (Frame_window); HWND Window = NULLHANDLE;
    while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
    {
      // �᫨ �� ���� �����:
      if (IsEntryFieldWindow (Window))
      {
        // �᫨ �뫮 ������� ��᪮�쪮 ����� ����� - �४�頥� ��ॡ�� ����.
        if (Field != NULLHANDLE) { Field = NULLHANDLE; break; }

        // ���������� ���� �����.
        Field = Window;
      }
    }
    WinEndEnumWindows (Enumeration);
  }

  // ������.
  return Field;
}
