
// ��� �⪫�砥� ���⠢�� �� ����⨨ ���� ���

// Window - ����, ��� ���ண� ���� �⪫���� ���⠢��.
VOID Patcher_DisableAnimation (HWND Window)
{
  // �᫨ ���� �������⭮ - ������.
  if (Window == NULLHANDLE) return;

  // ������ ᢮��⢠ ����.
  ULONG Window_style = WinQueryWindowULong (Window, QWL_STYLE);

  // �᫨ ���⠢�� �⪫�祭� - ������.
  if (!(Window_style & WS_ANIMATE)) return;

  // �⪫�砥� ���⠢��.
  Window_style = Window_style & ~WS_ANIMATE;

  // ��⠭�������� ᢮��⢠ ࠬ�� ����.
  WinSetWindowULong (Window, QWL_STYLE, Window_style);

  // ������.
  return;
}
