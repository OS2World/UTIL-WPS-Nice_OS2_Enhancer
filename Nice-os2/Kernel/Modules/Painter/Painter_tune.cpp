
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Painter_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Painter_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Painter_ReadSettings (Ini_file);

  // Создаем изображения для закрашивания заголовка.
  Painter_CreateTitleBarImages ();

  // Задаем правила для рисования.
  if (Painter.Settings.Draw_frames) Painter_SetDrawingRules ();

  // Задаем путь к узору для заполнения заголовков.
  if (stristr ("\\Enhancer\\Bitmap\\", Painter.Settings.TitleBar_pattern))
  {
    CHAR New_path[SIZE_OF_PATH] = "";

    GetCurrentPath (New_path);
    strcat (New_path, "\\Bitmap\\Themes\\");
    strcat (New_path, FindNameInPath (Painter.Settings.TitleBar_pattern));

    strcpy (Painter.Settings.TitleBar_pattern, New_path);
  }

  // Загружаем значки для окон.
  for (INT Count = 0; Count < RC_ICONS_QUANTITY; Count ++)
  {
    if (Resources.Default_icons[Count] != NULLHANDLE) WinDestroyPointer (Resources.Default_icons[Count]);
    Resources.Default_icons[Count] = WinLoadPointer (QueryDesktopWindow (), Enhancer.Module, RC_DEFAULT_ICON + Count);
  }

  // Запоминаем, что потоки должны быть созданы.
  if (Painter.Settings.Draw_frames)
  {
    Enhancer.Modules.Painter->Required = 1;
    Enhancer.Modules.Diver->Required = 1;
  }

  // Возврат.
  return;
}
