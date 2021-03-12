
// ─── Сообщает о том, какие цвета в оболочке OS/2 должны быть изменены ───

// Request_pointer - указатель на список цветов, которые расширитель умеет заменять.
VOID Rooms_SysColorsChangeReporter (PVOID Request_pointer)
{
  // Разбираем указатель.
  PPREFERRED_SYSTEM_COLORS Request = (PPREFERRED_SYSTEM_COLORS) Request_pointer;

  // Проверяем его.
  if (Request->cb != sizeof (PREFERRED_SYSTEM_COLORS)) return;

  // Задаем цвета.
  if (Rooms.Settings.Create_Rooms)
  {
    Request->Set_black_desktop_background = 1;
  }

  // Возврат.
  return;
}
