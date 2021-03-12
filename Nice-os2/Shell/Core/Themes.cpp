// Методы для заполнения страниц-"закладок".
#define ShowWPSColorPalette          Themes_ShowWPSColorPalette
#define RecognizeSelectedTheme       Themes_RecognizeSelectedTheme

// ─── Метод для подключения класса ───

VOID Themes_Start (VOID)
{
  #ifdef Themes
  bzero (&Themes, sizeof (Themes));
  #endif

  // Возврат.
  return;
}
