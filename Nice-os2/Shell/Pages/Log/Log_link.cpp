
// ��� �����頥� ���� ���� ����� ���

HWND Log_LogWindow (VOID)
{
  // �����頥� ����.
  return WinWindowFromID (Enhancer.Pages.Log->Window, Log.Settings.Field_ID);
}

// ��� �஢����, �뫮 �� ��������� � ���� ����� ��� ���� ᮮ�饭�� ���

BYTE Log_LogIsEmpty (VOID)
{
  // �஢��塞 ᮤ�ন��� ���� �����.
  if (Log.RTSettings.Field_is_changed) return 0;

  // ������.
  return 1;
}

// ��� �������� ᮮ�饭�� � ���� ����� ���

// Message - ᮮ�饭��.
VOID Log_PrintLogMessage (PCHAR Message)
{
  // �⢮��� ������ ��� ⥪��.
  PCHAR Window_text = NULL; INT Length = 65536;
  if (DosAllocMem ((PPVOID) &Window_text, Length, PAG_ALLOCATE) != NO_ERROR) return;

  // ������ ⥪�� � ���� �����.
  HWND Field = Log_LogWindow (); WinQueryWindowText (Field, Length, Window_text);

  // ������塞 ᮮ�饭�� � ���� �����.
  strcat (Window_text, Message); strcat (Window_text, "\n");

  WinEnableWindowUpdate (Field, 0);
  WinSetWindowText (Field, Window_text);
  WinEnableWindowUpdate (Field, 1);

  // �᢮������� ������.
  DosFreeMem (Window_text); Window_text = NULL;

  // ����������, �� ���� ����� ��������.
  Log.RTSettings.Field_is_changed = 1;

  // ������.
  return;
}
