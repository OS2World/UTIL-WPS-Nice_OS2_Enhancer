// ��⮤� ��� ࠡ��� � ������.
#define PutStringIntoClipboard           Clipboard_PutStringIntoClipboard
#define GetStringFromClipboard           Clipboard_GetStringFromClipboard

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Clipboard_Start (VOID)
{
  #ifdef Clipboard
  bzero (&Clipboard, sizeof (Clipboard));
  #endif

  // ������.
  return;
}

