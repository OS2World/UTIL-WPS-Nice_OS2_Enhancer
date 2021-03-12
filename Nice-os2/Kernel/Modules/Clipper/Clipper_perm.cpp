
// ─── Проверяет, можно ли выполнять выделение строк в текстовом окне ───

// Frame_window - текстовое окно.
BYTE Clipper_PermissionForMarking (HWND Frame_window)
{
  // Некоторые приложения умеют выбирать и запоминать строки самостоятельно.
  if (WindowIsUsedTo (DO_MANAGE_FILES, Frame_window)) return 0;
  if (IsGoldEdWindow (Frame_window)) return 0;

  // Все в порядке, возврат.
  return 1;
}
