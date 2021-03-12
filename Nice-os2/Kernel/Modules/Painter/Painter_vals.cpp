
// ─── Сообщает о том, какие настройки в оболочке OS/2 должны быть изменены ───

// Request_pointer - указатель на список настроек, которые расширитель умеет заменять.
VOID Painter_SysValuesChangeReporter (PVOID Request_pointer)
{
  // Разбираем указатель.
  PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

  // Проверяем его.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_VALUES)) return;

  // Если надо рисовать обычные рамки:
  if (Painter.Settings.Draw_frames)
  {
    // Задаем для рамок другую ширину.
    INT Border_width = 0;

    switch (Painter.Settings.Theme)
    {
      case PAINTER_THEME_CLASSIC_GRAY:
      case PAINTER_THEME_CLASSIC_RGB:
      {
        Border_width = 5;
      }
      break;

      case PAINTER_THEME_WHITE_SNOW:
      {
        Border_width = 4;
      }
      break;
    }

    // Изменяем внешний список, если это требуется.
    if (Border_width)
    {
      Request->Change_border_width = 1;
      Request->New_border_width = Border_width;
    }
  }

  // Возврат.
  return;
}

// ─── Сообщает о том, какие цвета в оболочке OS/2 должны быть изменены ───

// Request_pointer - указатель на список цветов, которые расширитель умеет заменять.
VOID Painter_SysColorsChangeReporter (PVOID Request_pointer)
{
  // Разбираем указатель.
  PPREFERRED_SYSTEM_COLORS Request = (PPREFERRED_SYSTEM_COLORS) Request_pointer;

  // Проверяем его.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_COLORS)) return;

  // Задаем цвета.
  if (Painter.Settings.Draw_frames && !Painter.Settings.Keep_frame_colors)
  {
    Request->Normalize_window_background = 1;
  }

  // Возврат.
  return;
}
