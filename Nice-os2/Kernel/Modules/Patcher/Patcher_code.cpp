
// ─── Отключает заставку при открытии окна ───

// Window - окно, для которого надо отключить заставку.
VOID Patcher_DisableAnimation (HWND Window)
{
  // Если окно неизвестно - возврат.
  if (Window == NULLHANDLE) return;

  // Узнаем свойства окна.
  ULONG Window_style = WinQueryWindowULong (Window, QWL_STYLE);

  // Если заставка отключена - возврат.
  if (!(Window_style & WS_ANIMATE)) return;

  // Отключаем заставку.
  Window_style = Window_style & ~WS_ANIMATE;

  // Устанавливаем свойства рамки окна.
  WinSetWindowULong (Window, QWL_STYLE, Window_style);

  // Возврат.
  return;
}
