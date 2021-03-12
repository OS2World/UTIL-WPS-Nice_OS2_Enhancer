
// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID Scroller_Tune (HINI Ini_file)
{
  // Читаем настройки.
  Scroller_SetPreDefinedSettings (SET_ALL_SETTINGS);
  Scroller_ReadSettings (Ini_file);

  // Если включено передвижение изображения:
  if (Scroller.Settings.Key_scrolling || Scroller.Settings.Image_dragging)
  {
    // Читаем имена окон для передвижения изображения.
    Scroller_ReadScrList (Ini_file);
    Scroller_CompleteScrList ();

    // Загружаем указатели.
    if (Resources.Pointer_for_dragging != NULLHANDLE) 
    { 
      WinDestroyPointer (Resources.Pointer_for_dragging); Resources.Pointer_for_dragging = NULLHANDLE; 
    }

    if (Scroller.Settings.Number_of_pointer) 
    {
      Resources.Pointer_for_dragging = WinLoadPointer (QueryDesktopWindow (), Enhancer.Module, Scroller.Settings.Number_of_pointer);
    }
  }

  // Запоминаем, что поток должен быть создан.
  if (Scroller.Settings.Key_scrolling || Scroller.Settings.Image_dragging) Enhancer.Modules.Scroller->Required = 1;

  // Возврат.
  return;
}
