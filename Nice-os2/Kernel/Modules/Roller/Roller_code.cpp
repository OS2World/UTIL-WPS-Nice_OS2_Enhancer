
// ─── Запоминает окно, которое убрано наверх ───

// Все переменные - внешние.
VOID Roller_RememberRolledWindow (HWND Rolled_window, PSWP Rolled_window_placement = NULL)
{
  // Запоминаем окно.
  Roller.Rolled_window = Rolled_window;

  // Запоминаем расположение окна.
  if (Rolled_window_placement != NULL) memcpy (&Roller.Rolled_window_placement, Rolled_window_placement, sizeof (SWP));
  else bzero (&Roller.Rolled_window_placement, sizeof (SWP));

  // Возврат.
  return;
}

// ─── Возвращает окно, которое убрано наверх ───

HWND Roller_RolledWindow (VOID)
{
  // Возвращаем окно.
  return Roller.Rolled_window;
}

// ─── Возвращает расположение окна, которое убрано наверх ───

VOID Roller_GetRolledWindowPlacement (PINT X, PINT Y, PINT Width, PINT Height)
{
  *X = Roller.Rolled_window_placement.x;
  *Y = Roller.Rolled_window_placement.y;
  *Width = Roller.Rolled_window_placement.cx;
  *Height = Roller.Rolled_window_placement.cy;

  // Возврат.
  return;
}