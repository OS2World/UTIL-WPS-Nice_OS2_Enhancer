// ��⮤� ��� ���������� ��࠭��-"��������".
#define ShowWPSColorPalette          Themes_ShowWPSColorPalette
#define RecognizeSelectedTheme       Themes_RecognizeSelectedTheme

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Themes_Start (VOID)
{
  #ifdef Themes
  bzero (&Themes, sizeof (Themes));
  #endif

  // ������.
  return;
}
