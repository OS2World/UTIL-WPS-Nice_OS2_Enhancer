
// ��� �஢����, ����� �� ��ࠢ������ ���� ��㧥� ���

// Frame_window - ���� ࠬ��.
BYTE Arranger_PermissionForBrowsers (HWND Frame_window, BYTE Recursive_calling = 0)
{
  // �᫨ ���� �� ������ - ������.
  if (Frame_window == NULLHANDLE) return 0;

  // ������, ��� �룫廊� ࠬ�� ����.
  ULONG Frame_style = WinQueryWindowULong (Frame_window, QWL_STYLE);

  // ���� ����� ��ࠢ������, ⮫쪮 �᫨ ��� ����� ������ ࠬ��.
  // �᫨ � ���� ��㣠� ࠬ�� - ������.
  if (!(Frame_style & FS_SIZEBORDER)) return 0;

  // ������, ���� �� ���� � ᯨ᪥ ����. 
  // �᫨ ��� ⠬ ��� ��� � ���� ����� ��४������� - ������.
  if (!FrameWindowIsAccessible (Frame_window)) return 0;

  // ������ ���ﭨ� ������ � ����.
  LONG Buttons_state = QueryButtonsState (Frame_window, MINIMIZE_ACTION | HIDE_ACTION, 1);

  // �᫨ � ���� ��� ������ ᮪���� � ��� ������ 㬥��襭�� � ���箪 - ������.
  if (!(Buttons_state & MINIMIZE_ACTION) && !(Buttons_state & HIDE_ACTION)) return 0;

  // �᫨ � ���� ��� ������ 㢥��祭�� �� ���� �࠭ - ������.
  if (!(Buttons_state & MAXIMIZE_ACTION)) return 0;

  // �᫨ �� �� ४��ᨢ�� �맮�:
  if (!Recursive_calling)
  {
    // ������ ��� �ਫ������, ᮧ���襣� ����.
    CHAR Exe_name[SIZE_OF_NAME] = ""; GetDetectedExeName (Frame_window, Exe_name);

    // �᫨ ��� 㤠���� ��।�����:
    if (Exe_name[0] != 0)
    {
      // ��⠥�, �� ���� ��ࠢ������ �����.
      BYTE Permission = 1;

      // ��ॡ�ࠥ� ���� � ���� ࠡ�祣� �⮫�.
      HENUM Enumeration = WinBeginEnumWindows (QueryDesktopWindow ()); HWND Window = NULLHANDLE;
      while ((Window = WinGetNextWindow (Enumeration)) != NULLHANDLE)
      {
        // �᫨ �� � �� ᠬ�� ���� - �த������ ��ॡ�� ����.
        if (Window == Frame_window) continue;

        // �᫨ �� �� ���� ࠬ�� - �த������ ��ॡ�� ����.
        if (!IsFrameWindow (Window)) continue;

        // ������ ��� �ਫ������, ᮧ���襣� ����.
        CHAR Exe_name_2[SIZE_OF_NAME] = ""; GetDetectedExeName (Window, Exe_name_2);
  
        // �᫨ ����� ᮢ������:
        if (strc (Exe_name, Exe_name_2))
        {
          // �᫨ � ��㣮� ���� ����� ��ࠢ������ �� ⥬ �� �ࠢ���� - �����, 
          // ⠪�� �� ���� 㦥 ��������� �� �࠭� � ����� ��祣� ������ �� ����.
          if (Arranger_PermissionForBrowsers (Window, RECURSIVE_CALLING))
          {
            Permission = 0; break;
          }
        }
      }
      WinEndEnumWindows (Enumeration);

      // �᫨ ���� ��ࠢ������ ����� - ������.
      if (!Permission) return 0;
    }
  }

  // �᫨ �� �஢�ન �ன���� - ����⢨� ��������.
  return 1;
}