
// ─── Завершение работы ───

VOID Rooms_ShutdownAll (VOID)
{
  // Узнаем окно рабочего стола.
  HWND Desktop = QueryDesktopWindow ();

  // Если есть окно, которое убрано наверх - восстанавливаем его.
  if (RolledWindow ()) UnrollWindow (RolledWindow ());

  // Переходим в комнату с окном оболочки.
  if (GetCurrentOrNextRoom () != SHELL_ROOM) Rooms_GoToRoom (SHELL_ROOM);

  // Закрываем окна рабочего стола, расположенные в комнатах.
  Rooms_RestoreAndCloseOuterWPSWindows (Desktop);

  // Делаем все окна доступными для переключения.
  SetAllWindowsJumpable (Desktop);

  // Сбрасываем изображения для закрашивания рабочего стола.
  Rooms_DeleteDesktopWallpaper ();

  // Возврат.
  return;
}